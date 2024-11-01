#pragma once

#include "raylib.h"

namespace Sprites
{
	struct Sprites
	{
		Texture2D playerSheet;
		Texture2D pipeImage;
	};

	void initSprites(Sprites& sprites);
	void unloadSprites(Sprites& sprites);
}