#pragma once

#include <list>

#include "pipe.h"
#include "Engine/engine.h"

namespace Player
{
	struct Player
	{
		Vector2 pos = { screenWidth / 5, screenHeight / 2 };

		float velocityY = 0;

		int points = 0;

		float size = 64;
		float radius = size / 2;
		bool collide = false;
	};

	void Movement(Player& player, float deltaTime);
	void AddPoint(float posX, int& points, std::list<Pipe::PipeSet>& pipes);
	void DidPlayerDied(Player& player, std::list<Pipe::PipeSet>& pipes);
}