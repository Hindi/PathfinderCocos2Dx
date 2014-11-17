#include "Game.h"
#include <iostream>

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
	Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
	Game *layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Vec2 origin = Director::sharedDirector()->getVisibleOrigin();

	zoneManager_.setLayerRef(*this);
	inputManager_.initEvent(&zoneManager_, this);
	
	this->scheduleUpdate();

	zoneManager_.spawnMap();
    return true;
}

void Game::update(float delta)
{
	zoneManager_.update(delta);
}

void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}