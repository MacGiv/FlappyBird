#pragma once

#include <list>

#include "raylib.h"

#include "Scenes/menus.h"
#include "Engine/Sprites/sprites.h"
#include "GamePlay/Entities/player.h"

namespace Drawers
{
	void DrawGamePlay(Menu::Menus gameState, Player::Player player, Player::Player playerTwo, std::list<Pipe::PipeSet>& pipeSets, Sprites::Sprites& sprites, Sprites::SpriteMovement spriteMovement, bool pause);
	void DrawCredits(Menu::Menus& gameState, Font font);
	void DrawMainMenu(Menu::Menus& gameState, Font font, Texture2D gamesTitle);
	void DrawGameRules(Menu::Menus& gameState, Font customFont);
	void DrawGameOver(Menu::Menus& gameState, Font font);
	void DrawPauseMenu(Menu::Menus& gameState, Font font, bool& pause);
	void DrawConfirmExit(Menu::Menus& gameState, Font font, Menu::Menus previusMenu);
	void DrawHowToPlay(Menu::Menus& gameState, Font font);
}