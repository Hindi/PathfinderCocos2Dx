#include "GameStateManager.h"

/**
 * @fn	GameStateManager::GameStateManager()
 *
 * @brief	Default constructor.
 *
 */
GameStateManager::GameStateManager(Player &player, UInterface& interface) :
m_player(player),
m_interface(interface)
{
	m_stateList["intro"] = std::make_shared<GameStateIntro>((*this), m_interface);
	m_stateList["pause"] = std::make_shared<GameStatePause>((*this), m_interface);
	m_stateList["game"] = std::make_shared<GameStateGame>((*this), m_player);
	m_stateList["end"] = std::make_shared<GameStateEndGame>((*this), m_interface);
	m_currentState = m_stateList["intro"];
	m_currentState->start();
}

/**
 * @fn	void GameStateManager::changeState(std::shared_ptr<GameState> state)
 *
 * @brief	Change state to "state". Use the end() function of the previous state and start() of the new one.
 *
 * @param	state	The state.
 */
void GameStateManager::changeState(std::string state)
{
	m_currentState->end(); 
	m_currentState = m_stateList[state];
	m_currentState->start();
}

/**
 * @fn	void GameStateManager::inputKeyReturn()
 *
 * @brief	Called by the inputManager for return key event
 *
 */
void GameStateManager::inputKeyReturn()
{
	m_currentState->inputKeyReturn();
}

/**
* @fn	void GameStateManager::inputKeyEscape()
*
* @brief	Called by the inputManager for escape key event
*
*/
void GameStateManager::inputKeyEscape()
{
	m_currentState->inputKeyEscape();
}

/**
* @fn	void GameStateManager::inputKeyUp()
*
* @brief	Called by the inputManager for up key event
*
*/
void GameStateManager::inputKeyUp()
{
	m_currentState->inputKeyUp();
}

/**
* @fn	void GameStateManager::inputKeyDown()
*
* @brief	Called by the inputManager for down key event
*
*/
void GameStateManager::inputKeyDown()
{
	m_currentState->inputKeyDown();
}