#include "ZoneManager.h"

USING_NS_CC;

ZoneManager::ZoneManager() :
screenSize_(Director::sharedDirector()->getVisibleSize()),
zoneBegin("Start", "begin zone.png", *this, Function::BEGIN),
zoneEnd("End", "end zone.png", *this, Function::END),
zoneObstacle("Obstacle", "block zone.png", *this, Function::OBSTACLE),
pathfinder_(zoneDict)
{
	curFunction_ = Function::NOTHING;
	start_ = &zoneBegin;
	end_ = &zoneEnd;
}

ZoneManager::~ZoneManager()
{

}

void ZoneManager::setLayerRef(cocos2d::Layer &layer)
{
	layer_ = &layer;
}

void ZoneManager::updateZone(Zone *zone)
{
	if (zone == start_)
		start_ = &zoneBegin;
	else if (zone == end_)
		end_ = &zoneEnd;
	if (curFunction_ == Function::BEGIN)
	{
		if (!start_->isAnObstacle())
			start_->setAvailable();
		start_ = zone;
	}
	else if (curFunction_ == Function::END)
	{
		if (!end_->isAnObstacle())
			end_->setAvailable();
		end_ = zone;
	}
}

void ZoneManager::onClick(Point position)
{
	//Find the touched node
	auto it = std::find_if(zoneList.begin(), zoneList.end(), [&position](const Zone* z) {
		return z->containsPoint(position);
	});
	if (it != zoneList.end())
	{
		(*it)->onClick(curFunction_);
		updateZone(*it);
	}

	//Clear path
	for (auto &z : currentPathIds_)
		if (z != end_->id() && !zoneDict[z].isAnObstacle())
			zoneDict[z].setAvailable();
	currentPathIds_.clear();

	//Start the pathfinding
	if (start_->id() != -1 && end_->id() != -1 && start_->id() != end_->id())
	{
		pathfinder_.findPath(start_->id(), end_->id());
		currentPathIds_ = pathfinder_.getResult();

		for (auto &z : currentPathIds_)
			zoneDict[z].setInUse();
	}
}


void ZoneManager::changeFunction(Function function)
{
	curFunction_ = function;
}

void ZoneManager::addNeighbours(int curId, Zone &temp, int lineInScreen, 
	int zonePerLine, int i, int j, int completeLineModifier)
{
	if (!(i == 0 && completeLineModifier == 0))
	{
		temp.addNeighbour(curId - 8);
		if (j < lineInScreen)
			temp.addNeighbour(curId + 7);
	}
	if (i != zonePerLine - 1)
	{
		if (j < lineInScreen)
			temp.addNeighbour(curId + 8);
		if (j != 0)
			temp.addNeighbour(curId - 7);
	}
	if (j > 1)
		temp.addNeighbour(curId - 15);
	if (j < lineInScreen - 1)
		temp.addNeighbour(curId + 15);
}

void ZoneManager::spawnMap()
{
	int startX, startY(50);
	float width = zoneBegin.width();
	float heigth = zoneBegin.heigth();

	float spareSpaceHorizontal = 1.5;
	float spareSpaceVertical = 2;

	int zonePerLine = (screenSize_.height / width) ;
	int lineInScreen = (screenSize_.width / heigth);
	int completeLineModifier(0);
	startX = (screenSize_.width - width*(zonePerLine-1)*spareSpaceHorizontal) / 2;

	Zone temp;
	int curId = 1;
	for (int j(0); j <= lineInScreen; ++j)
	{
		for (int i(0); i < zonePerLine - completeLineModifier; ++i)
		{
			temp = spawnZone(startX + i*width*spareSpaceHorizontal + completeLineModifier*width*0.75, j*heigth / spareSpaceVertical + startY);
			temp.setId(curId);

			addNeighbours(curId, temp, lineInScreen, zonePerLine, i, j, completeLineModifier);
			
			zoneDict[curId] = temp;
			zoneDict[curId].addToLayer(*layer_);
			zoneList.push_back(&zoneDict[curId]);
			curId++;
		}
		if (completeLineModifier == 0)
			completeLineModifier = 1;
		else
			completeLineModifier = 0;
	}

	zoneBegin.setPosition(Vec2(screenSize_.width / 2 - spareSpaceHorizontal * width, screenSize_.height - heigth/1.5));
	zoneEnd.setPosition(Vec2(screenSize_.width / 2, screenSize_.height - heigth/1.5));
	zoneObstacle.setPosition(Vec2(screenSize_.width / 2 + spareSpaceHorizontal * width, screenSize_.height - heigth/1.5));

	zoneList.push_back(&zoneBegin);
	zoneList.push_back(&zoneEnd);
	zoneList.push_back(&zoneObstacle);

	zoneBegin.addToLayer(*layer_);
	zoneEnd.addToLayer(*layer_);
	zoneObstacle.addToLayer(*layer_);
}

void ZoneManager::update(float delta)
{

}

Zone ZoneManager::spawnZone(cocos2d::Vec2 position)
{
	return Zone(position);
}

Zone ZoneManager::spawnZone(float x, float y)
{
	return spawnZone(Vec2(x, y));
}