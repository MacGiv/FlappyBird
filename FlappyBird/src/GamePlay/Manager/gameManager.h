#pragma once

#include <list>

#include "Scenes/menus.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"

namespace GameManager
{
	void ResetGame(Player::Player& player, Texture2D& playerSheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause);
	void ShouldResetGame(Menus& gameState, Player::Player& player, Texture2D& playerSheet,std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause);
}