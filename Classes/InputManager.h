#pragma once

#include <iostream>
#include "cocos2d.h"

#include "Zone\ZoneManager.h"

class InputManager : public cocos2d::Layer
{
public:
	InputManager();
	void initEvent(ZoneManager* zoneManager, cocos2d::Layer *layer);
	~InputManager();

private:
	cocos2d::EventListenerTouchOneByOne* mouseListener_;
	ZoneManager* zoneManager_;
};

