#pragma once

#include <map>
#include <vector>
#include <unordered_set>

#include "Zone\Zone.h"

/**
* @fn		The pathfinder uses an A* algorithm to find a path between
			the start zone and the end zone.
* @author	Vincent
*/

class Pathfinder {
public:
	/**
	*	@fn Pathfinder(std::map<int, Zone> &zoneDict)
	*	@brief Constructor
	*	@param zoneDict A map containing all the zones.
	*/
	Pathfinder(std::map<int, Zone> &zoneDict);

	/**
	*	@fn findPath(int startId, int goalId)
	*	@brief The function used to start the pathfinding
	*	@param startId The id of the start zone.
	*	@param goalId The id of the goal zone.
	*/
	void findPath(int startId, int goalId);

	/**
	*	@fn std::vector<int> getResult()
	*	@brief Allow the user to obtain the path.
	*	@return result_, the previously calculated path.
	*/
	std::vector<int> getResult();

	/**
	*	@fn int getNextZone
	*	@brief Allow the user to obtain the first zone of the path.
	*	@return The id of the first zone in the previously calculated path.
	*/
	int getNextZone();

	/**
	*	@fn void updateMap(std::map<int, Zone> &zoneDict)
	*	@brief Update the map
	*	@param zoneDict  A map containing all the zones.
	*/
	void updateMap(std::map<int, Zone> &zoneDict);

	/**
	*	@fn reverseResult()
	*	@brief Reverse the calculated path.
	*/
	void reverseResult();

private:

	/**
	*	@fn void addToOpenList(int id, int parentId)
	*	@brief Add the id of a valid zone to the openList_
	*	@param id The id to be added.
	*	@param parentId The id of the parent.
	*/
	void addToOpenList(int id, int parentId);

	/**
	*	@fn void checkNeighbourNode()
	*	@brief	Recursively call itself until the result is found.
				This function is the heart of the pathfinding.
	*/
	void checkNeighbourNode();

	int currentId_;                         //The id of our current position
	int startId_;                           //The id of the start zone
	int goalId_;                            //The id of the goal
	bool reversed_;
	std::vector<int> result_;               //The ids of all the zone in the path

	std::map<int, Zone> &zoneDict_;         //All of the zones, stored by id
	std::vector<int> openList_;             //Id of all the zones
	std::unordered_set<int> closedList_;    //The ids of the zone we already used as  current position
};
