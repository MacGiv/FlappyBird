#pragma once

#include <list>

#include "Scenes/menus.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"

namespace GameManager
{
	void ResetGame(Player::Player& p1, Player::Player& p2, Texture2D& playerOneSheet, Texture2D& playerTwoSheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause);
	void ShouldResetGame(Menu::Menus& gameState, Player::Player& p1, Player::Player& p2, Texture2D& p1Sheet, Texture2D& p2Sheet,std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause);
}