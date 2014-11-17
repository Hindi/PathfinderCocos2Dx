#include "Pathfinder.h"

Pathfinder::Pathfinder(std::map<int, Zone> &zoneDict) :
zoneDict_(zoneDict)
{

}

void Pathfinder::findPath(int startId, int goalId)
{
	//Don't look for a path if goal = start
	if (startId == goalId)
	{
		result_.push_back(startId);
		return;
	}

	//Init the variables
	openList_.clear();
	closedList_.clear(); 
	result_.clear();
	reversed_ = false;

	//Update our goal and current position
	startId_ = startId;
	goalId_ = goalId;
	currentId_ = startId;

	closedList_.insert(startId);

	//Let's go !
	checkNeighbourNode();
}

void Pathfinder::checkNeighbourNode()
{
	//This is the stopping condition, true if we reached the goal
	if (currentId_ == goalId_)
	{
		//Fill the result vector with the ids of the path
		for (int id = zoneDict_[currentId_].parentId_; id != startId_; id = zoneDict_[id].parentId_)
			result_.push_back(id);
	}
	else
	{
		//Add all of the valid neighbours in the openList_
		std::vector<int> neighboursList = zoneDict_[currentId_].neighbours();
		for (int i(0); i < neighboursList.size(); ++i)
			addToOpenList(neighboursList[i], currentId_);
		//At this point if the openList_ is empty, it means that there is no solution (we tried all of the possible zones)
		if (openList_.empty())
			return;
		else
		{
			//Chose the zone with the smallest weight
			auto eraseIt = min_element(openList_.begin(), openList_.end(), [&](int i, int j) {
				return (zoneDict_[i].getF() < zoneDict_[j].getF());
			});
			//Update the current position
			currentId_ = (*eraseIt);
			//Add the zone in the closedList_ and erase it from the openList_
			closedList_.insert(currentId_);
			openList_.erase(eraseIt);
			//Here we go again !
			checkNeighbourNode();
		}
	}

}

std::vector<int> Pathfinder::getResult()
{
	return result_;
}

int  Pathfinder::getNextZone()
{
	//If there is a path
	if (!result_.empty())
	{
		//If we reversed the result
		if (reversed_)
			return result_[0];
		else
			return result_[result_.size() - 1];
	}
	else
		return startId_;
}

void Pathfinder::updateMap(std::map<int, Zone> &zoneDict)
{
	zoneDict_ = zoneDict;
}

void Pathfinder::reverseResult()
{
	reversed_ = !reversed_;
	std::reverse(result_.begin(), result_.end());
}

void Pathfinder::addToOpenList(int id, int parentId)
{
	//Do not use this zone if it's an obstacle
	if (zoneDict_[id].isObstacle_)
		return;
	//Do not use this zone if it's already in the openList_
	if (std::find(openList_.begin(), openList_.end(), id) != openList_.end())
		return;
	//Do not use this zone if it's in the closedList_
	if (std::find(closedList_.begin(), closedList_.end(), id) != closedList_.end())
		return;

	zoneDict_[id].manHattanDistance(zoneDict_[goalId_]);

	//The weight of the consecutive movements that lead to this zone
	zoneDict_[id].G_ = zoneDict_[parentId].G_ + 1;
	//The weight obtained from the manhattan distance
	zoneDict_[id].H_ += zoneDict_[parentId].H_;
	//Keep track of the parent
	zoneDict_[id].parentId_ = parentId;
	openList_.push_back(id);
}