#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "cocos2d.h"
#include "ZoneSelection.h"

#include "Zone.h"
#include "enumFunction.h"
#include "Pathfinder.h"

/**
* @fn		ZoneManager creates and manages the zones
* @author	Vincent
*/

class ZoneManager : public cocos2d::Layer
{
public:
	/**
	*	@fn ZoneManager()
	*	@brief Default constructor.
	*/
	ZoneManager();
	~ZoneManager();

	/**
	*	@fn void update(float delta)
	*	@brief function called each frame.
	*	@param delta the time spent since the last frame
	*/
	void update(float delta);

	/**
	*	@fn void setLayerRef(cocos2d::Layer &layer)
	*	@brief Set the layer where the zone need to be created.
	*	@param layer a reference to the layer
	*/
	void setLayerRef(cocos2d::Layer &layer);

	/**
	*	@fn void spawnMap()
	*	@brief Called once when the game starts. Creates all the zones.
	*/
	void spawnMap();

	/**
	*	@fn void onClick(cocos2d::Point position)
	*	@brief Called each time the player touch/click. The ZoneManager 
			forwards th event to the corresponding zone.
	*	@param position The position of the zone.
	*/
	void onClick(cocos2d::Point position);

	/**
	*	@fn void changeFunction(Function function)
	*	@brief Modify the function the player want to use on click.
	*	@param function the given function.
	*/
	void changeFunction(Function function);

private:

	/**
	*	@fn Zone spawnZone(cocos2d::Vec2 position)
	*	@brief Create a zone a the position.
	*	@param position The position of the zone.
	*	@return The created Zone.
	*/
	Zone spawnZone(cocos2d::Vec2 position);

	/**
	*	@fn Zone spawnZone(float x, float y)
	*	@brief Create a zone a the position.
	*	@param x,y The position of the zone.
	*	@return The created Zone.
	*/
	Zone spawnZone(float x, float y);

	/**
	*	@fn updateZone(Zone *zone)
	*	@brief Update this zone depending on the current function.
	*	@param zone pointer to the zone
	*/
	void updateZone(Zone *zone);

	/**
	*	@fn void addNeighbours(int curId, Zone &temp, int lineInScreen, int zonePerLine, int i, int j, int completeLineModifier)
	*	@brief Update this zone depending on the current function.
	*	@param curId The id of the zone
	*	@param temp A reference to the zone.
	*	@param zonePerLine Number of zones that can fit in a line.
	*	@param lineInScreen Number of lines that can fit in the screen.
	*	@param i, j The "position" of the zone.
	*	@param completeLineModifier Lines have differents size, this variable indicates where we are.
	*/
	void addNeighbours(int curId, Zone &temp, int lineInScreen, int zonePerLine, int i, int j, int completeLineModifier);

	std::map<int, Zone> zoneDict;
	std::vector<Zone*> zoneList;
	ZoneSelection zoneBegin;
	ZoneSelection zoneEnd;
	ZoneSelection zoneObstacle;

	Zone *start_;
	Zone *end_;

	cocos2d::Layer *layer_;
	cocos2d::Size screenSize_;
	Function curFunction_;

	Pathfinder pathfinder_;
	std::vector<int> currentPathIds_;
};

