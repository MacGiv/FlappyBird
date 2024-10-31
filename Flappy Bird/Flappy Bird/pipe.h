#pragma once

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
		Pipe top = {};
		Pipe bottom = {};
	};

	const float speed = 64;

	const float maxSpacing = 384;
	extern float actualSpacing;
	const float minSpacing = 70;

	void Movement(PipeSet& pipe, float deltaTime);
	PipeSet Creator();
}