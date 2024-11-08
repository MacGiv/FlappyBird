#include <list>
#include <time.h>
#include <string>
#include <iostream>

#include "raylib.h"

#include "Engine/engine.h"
#include "Engine/Sprites/sprites.h"
#include "Scenes/menus.h"
#include "Scenes/scene.h"
#include "GamePlay/Manager/gameManager.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"

int main()
{
	bool pause = false;

	Player::Player player = {};

	std::list<Pipe::PipeSet> pipeSets = {};

	float spawmTimer = 0;

	Menus gameState = Menus::MainMenu;
	Menus previusMenu = Menus::MainMenu;

	Texture2D texture = {};

	Sprites::Sprites sprites = {};
	Sprites::SpriteMovement spriteMovement = {};

#pragma warning(disable:4244)
	srand(time(NULL));
#pragma warning(default:4244)

	InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Flappy Bird");

	Sprites::initSprites(sprites);

	player.frameRec = { 0.0f, 0.0f, (float)sprites.playerSheet.width / 3, (float)sprites.playerSheet.height };

	//SetTargetFPS(60);

	SetExitKey(0);

	while (!WindowShouldClose() && gameState != Menus::Exit)
	{
		float deltaTime = GetFrameTime();

		switch (gameState)
		{
		case Menus::MainMenu:

			if (IsKeyPressed(KEY_ESCAPE))
				gameState = Menus::WantToExit;
			break;

		case Menus::WantToExit:

			if (IsKeyPressed(KEY_ESCAPE))
				gameState = previusMenu;
			break;

		case Menus::Rules:
		case Menus::Credits:

			if (IsKeyPressed(KEY_ESCAPE))
				gameState = Menus::MainMenu;
			break;
		case Menus::Playing:

			previusMenu = Menus::Playing;

			if (!player.collide && gameState == Menus::Playing)
			{
				if (IsKeyPressed(KEY_ESCAPE))
					pause = !pause;

				if (!pause)
				{
					if (spawmTimer <= 0)
					{
						pipeSets.push_back(Pipe::Creator());
						spawmTimer = 6;
					}
					else
						spawmTimer -= deltaTime;

					for (auto& pipeSetIt : pipeSets)
					{
						Pipe::Movement(pipeSetIt, deltaTime);
					}

					Player::Movement(player, sprites.playerSheet, deltaTime);
					Player::AddPoint(player.pos.x, player.points, pipeSets);
					Player::DidPlayerDied(player, pipeSets);
					Pipe::Destructor(pipeSets);

					spriteMovement.sky -= 10 * deltaTime;
					spriteMovement.backBuildings -= 30.0f * deltaTime;
					spriteMovement.frontBuildings -= 50.0f * deltaTime;
					spriteMovement.fence -= 100.0f * deltaTime;

					if (spriteMovement.sky <= -screenWidth)
						spriteMovement.sky = 0;

					if (spriteMovement.backBuildings <= -screenWidth)
						spriteMovement.backBuildings = 0;

					if (spriteMovement.frontBuildings <= -screenWidth)
						spriteMovement.frontBuildings = 0;

					if (spriteMovement.fence <= -screenWidth)
						spriteMovement.fence = 0;

				}
			}

			break;

		default:
			break;
		}

		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case Menus::MainMenu:

			Scene::DrawMainMenu(gameState, GetFontDefault(), texture);
			break;

		case Menus::Playing:

			if (player.collide)
			{
				Scene::DrawGameOver(gameState, GetFontDefault());

				GameManager::ShouldResetGame(gameState, player, sprites.playerSheet, pipeSets, spawmTimer, pause);
			}
			else
			{
				if (pause)
				{
					Color semiTransparentBlack = { 0, 0, 0, 150 };
					DrawRectangle(0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight), semiTransparentBlack);
				}

				Scene::DrawGamePlay(player, pipeSets, sprites, spriteMovement, pause);

				if (pause)
				{
					Scene::DrawPauseMenu(gameState, GetFontDefault(), pause);

					if (gameState == Menus::MainMenu)
						GameManager::ResetGame(player, sprites.playerSheet, pipeSets, spawmTimer, pause);
				}

			}

			break;

		case Menus::Rules:

			Scene::DrawGameRules(gameState, GetFontDefault());
			break;

		case Menus::Credits:

			Scene::DrawCredits(gameState, GetFontDefault());
			break;

		case Menus::WantToExit:

			Scene::DrawConfirmExit(gameState, GetFontDefault(), previusMenu);
			break;

		default:
			break;
		}

		EndDrawing();

	}

	Sprites::unloadSprites(sprites);

	CloseWindow();

	return 0;
}