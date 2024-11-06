#include "utilities.h"

#include "Scenes/menus.h"
#include "engine.h"

bool Tools::CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
{
	float distance = sqrtf(powf(center2.x - center1.x, 2) + powf(center2.y - center1.y, 2));

	return distance <= (radius1 + radius2);
}

bool Tools::CheckMouseButtonCollition(Vector2 mouse, Rectangle button)
{
	return (mouse.x >= button.x &&
		mouse.x <= button.x + button.width &&
		mouse.y >= button.y &&
		mouse.y <= button.y + button.height);
}

bool Tools::CheckIfOutOfBounds(Vector2 position, float radius)
{
	return  (position.x + radius < 0 || position.x - radius > screenWidth || position.y + radius < 0 || position.y - radius > screenHeight);
}

void Tools::DrawButton(Rectangle rect, const std::string text, Color color, Color outline, Font font)
{
	DrawRectangleRec(rect, color);
	DrawRectangleLinesEx(rect, 2, outline);

	Vector2 textSize = MeasureTextEx(font, text.c_str(), textFontSize, 1);

	Vector2 textPosition = {
		rect.x + (rect.width - textSize.x) / 2,
		rect.y + (rect.height - textSize.y) / 2
	};

	DrawTextPro(font,
		text.c_str(),
		textPosition,
		Vector2{ 0,0 },
		0,
		textFontSize,
		0,
		BLACK);
}

