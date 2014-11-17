#include "Zone.h"

USING_NS_CC;
#define ABS(x) (((x) < 0) ? -(x) : (x))

Zone::Zone()
{
	position_ = Vec2(0, 0);
	init();
}

Zone::Zone(float x, float y)
{
	position_ = Vec2(x, y);
	init();
}

Zone::Zone(cocos2d::Vec2 position)
{
	position_ = position;
	init();
}

bool Zone::operator== (Zone const &z)
{
	return (id_ == z.id());
}

void Zone::init()
{
	//Get a pointer for each sprite that can be used on this zone
	zoneTexture_ = TextureCache::sharedTextureCache()->addImage("available zone.png");
	useZoneTexture_ = TextureCache::sharedTextureCache()->addImage("use zone.png");
	beginZoneTexture_ = TextureCache::sharedTextureCache()->addImage("begin zone.png");
	endZoneTexture_ = TextureCache::sharedTextureCache()->addImage("end zone.png");
	obstacleZoneTexture_ = TextureCache::sharedTextureCache()->addImage("block zone.png");

	sprite_ = Sprite::createWithTexture(zoneTexture_);
	sprite_->setPosition(position_);
	lockedSprite_ = false;
	G_ = 0;
	H_ = 0;
	isObstacle_ = false;
}

bool Zone::isSpriteLocked()
{
	return lockedSprite_;
}

void Zone::update(float delta)
{

}

void Zone::addToLayer(cocos2d::Layer &layer)
{
	layer.addChild(sprite_, 1);
	layer.addChild(idLabel_, 1);
}

void Zone::setId(int id)
{
	id_ = id;
	idLabel_ = LabelTTF::create(std::to_string(id_).c_str(), "Arial", 24);
	idLabel_->setPosition(Vec2(position_.x, position_.y));
}

void Zone::toggleObstacle()
{
	if (isObstacle_)
		sprite_->setTexture(zoneTexture_);
	else
		sprite_->setTexture(obstacleZoneTexture_);
	isObstacle_ = !isObstacle_;
}

void Zone::setAvailable()
{
	sprite_->setTexture(zoneTexture_);
	isObstacle_ = false;
}

void Zone::setInUse()
{
	sprite_->setTexture(useZoneTexture_);
	isObstacle_ = false;
}


void Zone::onClick(Function curFunction)
{
	switch (curFunction)
	{
	case Function::BEGIN:
		sprite_->setTexture(beginZoneTexture_);
		isObstacle_ = false;
		break;
	case Function::END:
		sprite_->setTexture(endZoneTexture_);
		isObstacle_ = false;
		break;
	case Function::OBSTACLE:
		toggleObstacle();
		break;
	}
	/*DEBUG ID
	for (int i(0); i < neighbours_.size(); ++i)
		std::cout << neighbours_[i] << " ";
	std::cout <<  std::endl;*/
}

float Zone::width() const
{
	return sprite_->getContentSize().width;
}

float Zone::heigth() const
{
	return sprite_->getContentSize().height;
}

int Zone::id() const
{
	return id_;
}

std::vector<int> Zone::neighbours() const
{
	return neighbours_;
}

bool Zone::isAnObstacle()
{
	return isObstacle_;
}

void Zone::addNeighbour(int id)
{
	neighbours_.push_back(id);
}

bool Zone::containsPoint(Point pos) const
{
	return (sqrt(pow(pos.x - position_.x, 2) + pow(pos.y - position_.y, 2)) < width() / 2);
}

Zone::~Zone()
{

}

int Zone::getF()
{
	return G_ + H_;
}

//Distance depuis la node actuelle jusqu'à l'objectif
void Zone::manHattanDistance(const Zone &nodeEnd)
{
	int x = ABS(position_.x - nodeEnd.position_.x);
	int y = ABS(position_.y - nodeEnd.position_.y);
	H_ = x + y;
	//std::cout << id_ << " " << H << std::endl;
}

void Zone::setPosition(cocos2d::Vec2 pos)
{
	position_ = pos;
	sprite_->setPosition(pos);
	idLabel_->setPosition(pos);
}