#include <list>
#include <time.h>
#include <string>

#include "raylib.h"

#include "Engine/engine.h"
#include "Scenes/menus.h"
#include "Scenes/scene.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"

int main()
{
	Player::Player player = {};

	std::list<Pipe::PipeSet> pipeSets = {};

	float timer = 0;

	Menus gameState = Menus::MainMenu;
	Menus previusMenu = Menus::MainMenu;

	Texture2D texture = {};

#pragma warning(disable:4244)
	srand(time(NULL));
#pragma warning(default:4244)

	InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Flappy Bird");

	SetExitKey(0);

	while (!WindowShouldClose() && gameState != Menus::Exit)
	{
		float deltaTime = GetFrameTime();

		if (!player.collide && gameState == Menus::Playing)
		{
			if (timer <= 0)
			{
				pipeSets.push_back(Pipe::Creator());
				timer = 6;
			}
			else
				timer -= deltaTime;

			for (auto& pipeSetIt : pipeSets)
			{
				Pipe::Movement(pipeSetIt, deltaTime);
			}

			Player::Movement(player, deltaTime);
			Player::AddPoint(player.pos.x, player.points, pipeSets);
			Player::DidPlayerDied(player, pipeSets);
			Pipe::Destructor(pipeSets);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		switch (gameState)
		{
		case Menus::MainMenu:

			Scene::DrawMainMenu(gameState, GetFontDefault(), texture);
			break;

		case Menus::Playing:

			Scene::DrawGamePlay(player, pipeSets);
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

	CloseWindow();

	return 0;
}