#pragma once

#include <iostream>
#include "cocos2d.h"

#include "enumFunction.h"


/**
* @fn		Zone "unit" that is used to create the map
* @author	Vincent
*/
class Zone
{
	friend class Pathfinder;
public:
	/**
	*	@fn Zone()
	*	@brief Default constructor.
	*/
	Zone();

	/**
	*	@fn Zone(float x, float y)
	*	@brief Constructor with position.
	*	@param x,y position with floats
	*/
	Zone(float x, float y);

	/**
	*	@fn Zone(cocos2d::Vec2 position)
	*	@brief Constructor with position.
	*	@param position Position with Vec2
	*/
	Zone(cocos2d::Vec2 position);
	~Zone();

	/**
	*	@fn bool operator== (Zone const &z)
	*	@brief Equality operator.
	*	@param z the other zone.
	*/
	bool operator== (Zone const &z);

	/**
	*	@fn void update(float delta)
	*	@brief Called each frame.
	*	@param delta The time spent since last frame.
	*/
	void update(float delta);

	/**
	*	@fn void update(float delta)
	*	@brief Add sprite_ to the layer.
	*	@param layer The layer.
	*/
	void addToLayer(cocos2d::Layer &layer);
	void setId(int id);

	/**
	*	@fn void setInUse()
	*	@brief Set the zone as used.
	*/
	virtual void setInUse();

	/**
	*	@fn void setAvailable()
	*	@brief Set the zone as available.
	*/
	virtual void setAvailable();

	/**
	*	@fn bool isSpriteLocked()
	*	@brief Check if the sprite of this zone can be changed.
	*	@return true if the sprite can be changed.
	*/
	bool isSpriteLocked();

	/**
	*	@fn virtual void onClick(Function curFunction)
	*	@brief Called each time the player click on this zone.
	*	@param curFunction The function the player is currently using.
	*/
	virtual void onClick(Function curFunction);


	/**
	*	@fn float width() const
	*	@brief Return the width of the sprite.
	*	@return sprite_.width
	*/
	float width() const;

	/**
	*	@fn float heigth() const
	*	@brief Return the heigth of the sprite.
	*	@return sprite_.heigth
	*/
	float heigth() const;

	/**
	*	@fn float id() const
	*	@brief Return the id of the sprite.
	*	@return id_
	*/
	int id() const;

	/**
	*	@fn float neighbours() const
	*	@brief Return the vector containing the neighbours' ids.
	*	@return neighbours_
	*/
	std::vector<int> neighbours() const;

	/**
	*	@fn void toggleObstacle()
	*	@brief Toggle the zon into an obstacle or available.
	*/
	void toggleObstacle();

	/**
	*	@fn void addNeighbour(int id)
	*	@brief Add the id of a neighbour to the vector.
	*	@param id The id of the neighbours.
	*/
	void addNeighbour(int id);

	/**
	*	@fn bool containsPoint(cocos2d::Point pos) const
	*	@brief Check weither this zone contains a point or not.
	*	@param pos the position of the point.
	*	@return true if the position is inside the zone.
	*/
	bool containsPoint(cocos2d::Point pos) const;

	/**
	*	@fn bool isAnObstacle()
	*	@brief Check weither this zone is an obstacle or not.
	*	@return true if the zone is an obstacle.
	*/
	bool isAnObstacle();

	/**
	*	@fn void setPosition(cocos2d::Vec2 pos)
	*	@brief Changes the position of the zone.
	*	@param curFunction The currently used function.
	*/
	void setPosition(cocos2d::Vec2 pos);

protected:
	/**
	*	@fn void init()
	*	@brief Initializes the zone.
	*/
	virtual void init();

	/**
	*	@fn void manHattanDistance(const Zone &nodeEnd)
	*	@brief Assign the value of the manhanttan distance to H.
	*/
	void manHattanDistance(const Zone &nodeEnd);

	/**
	*	@fn void init()
	*	@brief Initializes the zone.
	*/
	int getF();

	cocos2d::Sprite *sprite_;
	cocos2d::Texture2D* zoneTexture_;
	cocos2d::Texture2D* useZoneTexture_;
	cocos2d::Texture2D* endZoneTexture_;
	cocos2d::Texture2D* obstacleZoneTexture_; 
	cocos2d::Texture2D* beginZoneTexture_;
	cocos2d::Vec2 position_;

	bool lockedSprite_;
	int id_; 
	cocos2d::LabelTTF* idLabel_;

	//For the pathfinder
	std::vector<int> neighbours_;
	int parentId_;
	int H_;
	int G_;
	bool isObstacle_;
};

