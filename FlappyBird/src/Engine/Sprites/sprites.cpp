#include "sprites.h"

void Sprites::initSprites(Sprites& sprites)
{
	sprites.playerSheet = LoadTexture("res/birdSpriteSheet.png");
	sprites.pipeImage = LoadTexture("res/pipe.png");
}

void Sprites::unloadSprites(Sprites& sprites)
{
	UnloadTexture(sprites.playerSheet);
	UnloadTexture(sprites.pipeImage);
}
