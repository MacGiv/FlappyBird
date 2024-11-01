#include <list>
#include <time.h>
#include <string>

#include "raylib.h"

#include "Engine/engine.h"
#include "Engine/Sprites/sprites.h"
#include "Scenes/menus.h"
#include "Scenes/scene.h"
#include "GamePlay/Manager/gameManager.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"
#include <iostream>

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

#pragma warning(disable:4244)
	srand(time(NULL));
#pragma warning(default:4244)

	InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Flappy Bird");

	Sprites::initSprites(sprites, player.texture);

	player.frameRec = { 0.0f, 0.0f, (float)player.texture.width / 3, (float)player.texture.height };

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

					Player::Movement(player, deltaTime);
					Player::AddPoint(player.pos.x, player.points, pipeSets);
					Player::DidPlayerDied(player, pipeSets);
					Pipe::Destructor(pipeSets);

					player.framesCounter++;

					if (player.framesCounter >= (60 / player.framesSpeed))
					{
						player.framesCounter = 0;
						player.currentFrame++;

						if (player.currentFrame > 2) 
							player.currentFrame = 0;

						player.frameRec.x = (float)player.currentFrame * (float)player.texture.width / 3;
					}
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

				GameManager::ShouldResetGame(gameState, player, pipeSets, spawmTimer, pause);
			}
			else
			{
				if (pause)
				{
					Color semiTransparentBlack = { 0, 0, 0, 150 };
					DrawRectangle(0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight), semiTransparentBlack);
				}

				Scene::DrawGamePlay(player, pipeSets, sprites, pause);

				if (pause)
				{
					Scene::DrawPauseMenu(gameState, GetFontDefault(), pause);

					if (gameState == Menus::MainMenu)
						GameManager::ResetGame(player, pipeSets, spawmTimer, pause);
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

	Sprites::unloadSprites(sprites, player.texture);

	CloseWindow();

	return 0;
}