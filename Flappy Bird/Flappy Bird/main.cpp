#include <list>
#include <time.h>

#include "raylib.h"

#include "player.h"
#include "engine.h"
#include "pipe.h"

int main()
{
	Player::Player player = {};

	std::list<Pipe::PipeSet> pipeSets = {};

	float timer = 0;

#pragma warning(disable:4244)
	srand(time(NULL));
#pragma warning(default:4244)

	InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Flappy Bird");

	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();

		if (!player.collide)
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
			Player::DidPlayerDied(player, pipeSets);
		}

		BeginDrawing();

		ClearBackground(BLACK);

		DrawCircle(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), player.radius, PURPLE);

		for (auto& pipeSetIt : pipeSets)
		{
			DrawRectangleRec(pipeSetIt.top.rect, GREEN);
			DrawRectangleRec(pipeSetIt.bottom.rect, RED);
		}

		EndDrawing();

	}

	CloseWindow();

	return 0;
}