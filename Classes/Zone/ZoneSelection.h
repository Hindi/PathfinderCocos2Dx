#pragma once

#include "cocos2d.h"
#include "Zone.h"
#include "enumFunction.h"


/**
* @fn		The ZoneSelection objects are zones that allow
			the player to select a function.
* @author	Vincent
*/

class ZoneManager;

class ZoneSelection : public Zone
{
public:

	/**
	*	@fn ZoneSelection(std::string function, std::string filename, ZoneManager &mgr, Function curFunction)
	*	@brief Constructor
	*	@param function The string used in the displayed label.
	*	@param filename The path to the sprite.
	*	@param mgr A reference to the ZoneManager.
	*	@param curFunction Enum that will be set to the ZoneManager on click.
	*/
	ZoneSelection(std::string function, std::string filename, ZoneManager &mgr, Function curFunction);
	~ZoneSelection();

	/**
	*	@fn void onClick(Function curFunction)
	*	@brief Inherited from Zone, this function is called when the user click on the zone.
	*	@param curFunction The currently used function.
	*/
	void onClick(Function curFunction) override;

	/**
	*	@fn void setInUse()
	*	@brief Set the zone as used.
	*/
	void setInUse() override;

	/**
	*	@fn void setAvailable()
	*	@brief Set the zone as available.
	*/
	void setAvailable() override;

protected:
	/**
	*	@fn void init()
	*	@brief Initializes the zone.
	*/
	void init() override;
	ZoneManager &zoneManager_;
	Function currentFunction_;
};