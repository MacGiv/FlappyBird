#pragma once

#include <list>

#include "pipe.h"
#include "Engine/engine.h"

namespace Player
{
	struct Player
	{
		Vector2 pos = { screenWidth / 5, screenHeight / 2 };

		Rectangle frameRec = {};

		float velocityY = 0;

		int points = 0;

		int currentFrame = 0;
		float framesCounter = 0;

		float size = 64;
		float radius = size / 2;

		bool animate = false;
		bool collide = false;
	};

	void Movement(Player& player, Texture2D& playerSheet, float deltaTime);
	void Anitmation(Player& player, Texture2D& playerSheet, float deltaTime);
	void AddPoint(float posX, int& points, std::list<Pipe::PipeSet>& pipes);
	void DidPlayerDied(Player& player, std::list<Pipe::PipeSet>& pipes);
}