#pragma once

#include <list>

#include "pipe.h"
#include "engine.h"

namespace Player
{
	struct Player
	{
		Vector2 pos = { screenWidth / 5, screenHeight / 2 };

		float velocityY = 0;

		float size = 64;
		float radius = size / 2;
		bool collide = false;
	};

	void Movement(Player& player, float deltaTime);
	void DidPlayerDied(Player& player, std::list<Pipe::PipeSet>& pipes);
}