#include "ZoneSelection.h"

USING_NS_CC;

#include "ZoneManager.h"

ZoneSelection::ZoneSelection(std::string function, std::string filename, ZoneManager &mgr, Function curFunction) :
	zoneManager_(mgr),
	currentFunction_(curFunction)
{
	zoneTexture_ = TextureCache::sharedTextureCache()->addImage(filename);

	sprite_ = Sprite::createWithTexture(zoneTexture_);
	sprite_->setPosition(position_);

	idLabel_ = LabelTTF::create(function.c_str(), "Arial", 18);
	idLabel_->setPosition(Vec2(position_.x, position_.y));
	lockedSprite_ = true;
	id_ = -1;
}

void ZoneSelection::setAvailable()
{

}

void ZoneSelection::setInUse()
{

}

void ZoneSelection::init()
{
}


ZoneSelection::~ZoneSelection()
{

}

void ZoneSelection::onClick(Function curFunction)
{
	zoneManager_.changeFunction(currentFunction_);
}