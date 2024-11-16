#include "utilities.h"

#include "Scenes/menus.h"
#include "engine.h"

bool Tools::CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
	float distance = sqrtf(powf(center2.x - center1.x, 2) + powf(center2.y - center1.y, 2));

	return distance <= (radius1 + radius2);
}

bool Tools::CheckMouseButtonCollision(Vector2 mouse, Rectangle button)
{
	return (mouse.x >= button.x &&
		mouse.x <= button.x + button.width &&
		mouse.y >= button.y &&
		mouse.y <= button.y + button.height);
}

//