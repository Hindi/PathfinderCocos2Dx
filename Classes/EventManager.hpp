#pragma once
#include <map>
#include <string>
#include <utility>
#include <map>
#include <functional>
#include "Delegate.hpp"


template<typename... Arguments> class EventManager
{
public:
	/**
	 * @fn	void EventManager::addListener(std::string name, std::function<void(Arguments...)> func)
	 *
	 * @brief	Adds a listener to the event named "name" and link it with the function "func" that'll be called when the event trigers.
	 *
	 * @param	name	The name of the event that'll call this function on trigger.
	 * @param	func	A pointer to the function to store
	 */
	void addListener(std::string name, std::function<void(Arguments...)> func)
	{
		funcs[name].add(func);
	}

	/**
	 * @fn	void EventManager::call(std::string evtName, Arguments... t)
	 *
	 * @brief	Calls the functions registered for the event evtName.
	 *
	 * @param	evtName	Name of the event.
	 * @param	t		List of the arguments necessary to call these functions.
	 */
	void call(std::string evtName, Arguments... t)
	{
		if (funcs.find(evtName) != funcs.end())
			funcs[evtName].call(t ...);
	}

	/**
	 * @fn	static EventManager<Arguments...>& EventManager::getInstance()
	 *
	 * @brief	Gets the instance of the singleton.
	 *
	 * @return	The instance.
	 */
	static EventManager<Arguments...>& getInstance()
	{
		static EventManager<Arguments...> manager;
		return manager;
	}

private:

	EventManager(){}
	std::map< std::string, Delegate<Arguments...> > funcs;
};

/**
 * @class	EventManager<void>
 *
 * @brief	Specialisation for 0 parameters
 *
 */
template<> class EventManager<void>
{
public:
	/**
	* @fn	void EventManager::addListener(std::string name, std::function<void(Arguments...)> func)
	*
	* @brief	Adds a listener to the event named "name" and link it with the function "func" that'll be called when the event trigers.
	*
	* @param	name	The name of the event.
	* @param	func	The function.
	*/
	void addListener(std::string name, std::function<void()> func)
	{
		funcs[name].add(func);
	}

	/**
	* @fn	void EventManager::call(std::string evtName, Arguments... t)
	*
	* @brief	Calls the functions registered for the event evtName.
	*
	* @param	evtName	Name of the event.
	*/
	void call(std::string evtName)
	{
		if (funcs.find(evtName) != funcs.end())
			funcs[evtName].call();
	}

	/**
	* @fn	static EventManager<Arguments...>& EventManager::getInstance()
	*
	* @brief	Gets the instance of the singleton.
	*
	* @return	The instance.
	*/
	static EventManager<void>& getInstance()
	{
		static EventManager manager;
		return manager;
	}

private:

	EventManager(){}
	std::map< std::string, Delegate<>  > funcs;
};