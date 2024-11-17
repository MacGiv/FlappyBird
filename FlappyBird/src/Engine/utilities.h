#pragma once

#include <string>

#include "raylib.h"

namespace Tools
{
	bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);
	bool CheckMouseButtonCollision(Vector2 mouse, Rectangle button);
}