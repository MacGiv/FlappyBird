#include <iostream>

#include "Engine/button.h"
#include "Scenes/menus.h"
namespace Buttons
{

void DrawButton(Rectangle rect, const std::string text, Color color, Color outline, Font font)
{
	DrawRectangleRec(rect, color);
	DrawRectangleLinesEx(rect, 2, outline);

	Vector2 textSize = MeasureTextEx(font, text.c_str(), Menu::textFontSize, 1);

	Vector2 textPosition = {
		rect.x + (rect.width - textSize.x) / 2,
		rect.y + (rect.height - textSize.y) / 2
	};

	DrawTextPro(font,
		text.c_str(),
		textPosition,
		Vector2{ 0,0 },
		0,
		Menu::textFontSize,
		0,
		BLACK);
}


} // namespace Buttons