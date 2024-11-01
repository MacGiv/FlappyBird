#include "sprites.h"

void Sprites::initSprites(Sprites& sprites, Texture2D& playerSprite)
{
	playerSprite = LoadTexture("res/birdSpriteSheet.png");
	sprites.pipeImage = LoadTexture("res/pipe.png");
}

void Sprites::unloadSprites(Sprites& sprites, Texture2D& playerSprite)
{
	UnloadTexture(playerSprite);
	UnloadTexture(sprites.pipeImage);
}
