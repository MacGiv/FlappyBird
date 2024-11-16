#pragma once

#include <list>

#include "raylib.h"

namespace Pipe
{
	struct Pipe
	{
		Rectangle rect = {};
		float angle = 0;
	};

	struct PipeSet
	{
		bool counted = false;

		Pipe top = {};
		Pipe bottom = {};
	};

	const float speed = 150;

	const float maxSpacing = 250;
	extern float actualSpacing;
	const float minSpacing = 70;

	void Movement(PipeSet& pipeSets, float deltaTime);
	void HandleOutOfBounds(std::list<PipeSet>& pipeSets);
	PipeSet Creator();
}