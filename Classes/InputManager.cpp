#include "InputManager.h"

USING_NS_CC;

InputManager::InputManager()
{
}

void InputManager::initEvent(ZoneManager* zoneManager, cocos2d::Layer* layer)
{
	mouseListener_ = EventListenerTouchOneByOne::create();
	mouseListener_->onTouchBegan = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());

		zoneManager->onClick(locationInNode);

		return false;

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener_, layer);
}

InputManager::~InputManager()
{
}
