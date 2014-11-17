#pragma once

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <assert.h>

#include "GameState.h"
#include "GameStateIntro.h"
#include "..\EventManager.hpp"
#include "../../entity/Player.h"
#include "../../Interface/UInterface.h"

/**
	 * @fn	Le GameStateManager permet de gérer l'évolution des différents état de jeu (démarrage, jeu, pause, fin de partie) 
	 * 		Chaque état est un GameState (interface) et possède sa propre classe qui redéfinie les fonctions d'inputs (appelé par l'InputManager via le GameStateManager) 
	 * 		et les fonctions de transitions. 
	 *
	 * @author	Vincent
	 * @date	09/06/2014
	 *
	 */

class GameStateManager
{
public:
	GameStateManager(Player &player, UInterface& interface);
	void changeState(std::string state);
	void clear();

	void inputKeyReturn();
	void inputKeyEscape();
	void inputKeyUp();
	void inputKeyDown();


private:
	std::shared_ptr<GameState> m_currentState;
	std::map< std::string, std::shared_ptr<GameState> > m_stateList;
	Player &m_player;
	UInterface &m_interface;
};
