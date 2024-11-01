#pragma once

#include "raylib.h"

namespace Sprites
{
	struct Sprites
	{
		Texture2D playerSheet;
		Texture2D pipeImage;
	};

	void initSprites(Sprites& sprites, Texture2D& playerSprite);
	void unloadSprites(Sprites& sprites, Texture2D& playerSprite);
}