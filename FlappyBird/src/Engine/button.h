#pragma once

#include "raylib.h"

#include "Scenes/menus.h"

namespace Buttons
{

const float buttonWidth = 200;
const float buttonHeight = 60;
const float buttonSpacing = 20;

struct Button
{
	Rectangle rect = { 0,0,0,0 };
	Menu::Menus option = Menu::Menus::None;
	Color color = { 255, 182, 193, 255 };
};

void DrawButton(Rectangle rect, const std::string text, Color color, Color outline, Font font);

} // namespace Buttons