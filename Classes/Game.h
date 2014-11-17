#pragma once

#include "cocos2d.h"
#include "InputManager.h"
#include "Zone\ZoneManager.h"


/**
* @fn		Game This is where the game start.
* @author	Cocos2D team
*/
class Game : public cocos2d::Layer
{
public:

	/**
	*	@fn bool init() override
	*	@brief Called once to initialize the object
	*/
	bool init() override;


	/**
	*	@fn static cocos2d::Scene* createScene()
	*	@brief there's no 'id' in cpp, so we recommend returning the class instance pointer
	*/
	static cocos2d::Scene* createScene();

	/**
	*	@fn static cocos2d::Scene* createScene()
	*	@brief a selector callback
	*/
	void menuCloseCallback(cocos2d::Ref* pSender);

	/**
	*	@fn static cocos2d::Scene* createScene()
	*	@brief implement the "static node()" method manually
	*/
	CREATE_FUNC(Game);

	/**
	*	@fn void update(float delta) override
	*	@brief Called each frame
	*	@param delta Time spent since the last frame.
	*	@author Vincent
	*/
	void update(float delta) override;

private:
	ZoneManager zoneManager_;
	InputManager inputManager_;
};