#include "sprites.h"

void Sprites::initSprites(Sprites& sprites)
{
	sprites.playerOneSheet = LoadTexture("res/birdSpriteSheet.png");
	sprites.playerTwoSheet = LoadTexture("res/birdSpriteSheet_2.png");
	sprites.pipeImage = LoadTexture("res/pipe.png");

	sprites.sky = LoadTexture("res/Paralax/night sky.png");
	sprites.backBuildings = LoadTexture("res/Paralax/night buildings back.png");
	sprites.frontBuildings = LoadTexture("res/Paralax/night buildings front.png");
	sprites.fence = LoadTexture("res/Paralax/night fence.png");
}

void Sprites::unloadSprites(Sprites& sprites)
{
	UnloadTexture(sprites.playerOneSheet);
	UnloadTexture(sprites.pipeImage);

	UnloadTexture(sprites.backBuildings);
	UnloadTexture(sprites.frontBuildings);
	UnloadTexture(sprites.fence);
}
