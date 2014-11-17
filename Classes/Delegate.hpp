#pragma once

#include <vector>
#include <functional>
#include <utility>

/**
 * @class	Delegate
 *
 * @brief	A delegate class that stores functions.
 *
 * @author	Vincent
 * @date	11/06/2014
 *
 * @typeparam	The list of arguments for the functions.
 */
template<typename... Arguments> class Delegate
{
public:

	/**
	 * @fn	void Delegate::add(std::function<void(Arguments...)> func)
	 *
	 * @brief	Adds a function to the delegate
	 *
	 * @param	A pointer to a function.
	 */
	void add(std::function<void(Arguments...)> func)
	{
		funcs.push_back(func);
	}

	/**
	 * @fn	void Delegate::call(Arguments... t)
	 *
	 * @brief	Calls the given t.
	 *
	 * @param	Calls all of the stored function with the specified parameter list
	 */
	void call(Arguments... t)
	{
		for (auto f : funcs)
			f(t ...);
	}

private:
	std::vector<std::function<void(Arguments...)> > funcs;
};

/**
* @class	Delegate
*
* @brief	A specialisation of the variadic template for the case when there is no argument
*
* @author	Vincent
* @date	11/06/2014
*
*/
template<> class Delegate<void>
{
public:

	/**
	 * @fn	void Delegate<void>::add(std::function < void()> func)
	 *
	 * @brief	Adds func.
	 *
	 * @param	A function pointer.
	 */
	void add(std::function < void()> func)
	{
		funcs.push_back(func);
	}

	/**
	 * @fn	void Delegate<void>::call()
	 *
	 * @brief	Calls all of the stored functions
	 *
	 */
	void call()
	{
		for (auto f : funcs)
			f();
	}

private:
	std::vector<std::function<void()> > funcs;
};


