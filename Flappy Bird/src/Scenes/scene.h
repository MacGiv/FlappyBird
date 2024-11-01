#pragma once

#include <list>

#include "raylib.h"

#include "menus.h"
#include "GamePlay/Entities/player.h"

namespace Scene
{
	void DrawGamePlay(Player::Player player, std::list<Pipe::PipeSet>& pipeSets);
	void DrawCredits(Menus& gameState, Font font);
	void DrawMainMenu(Menus& gameState, Font font, Texture2D gamesTitle);
	void DrawGameRules(Menus& gameState, Font customFont);
	void DrawGameOver(Menus& gameState, Font font);
	void DrawPauseMenu(Menus& gameState, Font font, bool& pause);
	void DrawConfirmExit(Menus& gameState, Font font, Menus previusMenu);
}