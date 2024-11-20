#include <time.h>

#include "gameLoop.h"

#include "Engine/engine.h"
#include "Engine/Sprites/sprites.h"
#include "Scenes/menus.h"
#include "Scenes/scene.h"
#include "GamePlay/Manager/gameManager.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"


namespace GameLoop
{

static void initGame(Sprites::Sprites& sprites);

static void update(bool& pause, float& spawmTimer, std::list<Pipe::PipeSet>& pipeSets, Sprites::Sprites& sprites, Sprites::SpriteMovement& spriteMovement);

static void draw(const Texture2D& texture, Sprites::Sprites& sprites, std::list<Pipe::PipeSet>& pipeSets, float& spawmTimer, bool& pause,
	const Sprites::SpriteMovement& spriteMovement);

static void close(Sprites::Sprites& sprites);

static Menu::Menus gameState;
static Menu::Menus previousMenu;
static Player::Player playerOne = {};
static Player::Player playerTwo = {};
static bool isSinglePlayer = true;

void mainLoop()
{
	bool pause = false;

	Player::InitializePlayer(playerOne, 1);
	Player::InitializePlayer(playerTwo, 2);

	std::list<Pipe::PipeSet> pipeSets = {};

	float spawnTimer = 0;

	gameState = Menu::Menus::MainMenu;
	previousMenu = Menu::Menus::MainMenu;

	Texture2D texture = {};

	Sprites::Sprites sprites = {};
	Sprites::SpriteMovement spriteMovement = {};
	
	initGame(sprites);

	SetExitKey(0);

	while (!WindowShouldClose() && gameState != Menu::Menus::Exit)
	{
		update(pause, spawnTimer, pipeSets, sprites, spriteMovement);

		draw(texture, sprites, pipeSets, spawnTimer, pause, spriteMovement);
	}

	close(sprites);
}

void initGame(Sprites::Sprites& sprites)
{
	

#pragma warning(disable:4244)
	srand(time(NULL));
#pragma warning(default:4244)

	InitWindow(static_cast<int>(screenWidth), static_cast<int>(screenHeight), "Flappy Bird");

	Sprites::initSprites(sprites);

	playerOne.frameRec = { 0.0f, 0.0f, (float)sprites.playerOneSheet.width / 3, (float)sprites.playerOneSheet.height };

	playerTwo.frameRec = { 0.0f, 0.0f, (float)sprites.playerTwoSheet.width / 3, (float)sprites.playerTwoSheet.height };

}

void update(bool& pause, float& spawmTimer, std::list<Pipe::PipeSet>& pipeSets, Sprites::Sprites& sprites, Sprites::SpriteMovement& spriteMovement)
{
	float deltaTime = GetFrameTime();

	switch (gameState)
	{
	case Menu::Menus::MainMenu:

		if (IsKeyPressed(KEY_ESCAPE))
			gameState = Menu::Menus::WantToExit;
		break;

	case Menu::Menus::WantToExit:

		if (IsKeyPressed(KEY_ESCAPE))
			gameState = previousMenu;
		break;

	case Menu::Menus::Rules:
	case Menu::Menus::Credits:

		if (IsKeyPressed(KEY_ESCAPE))
			gameState = Menu::Menus::MainMenu;
		break;

	case Menu::Menus::Playing:
	case Menu::Menus::PlayingTwo:

		//previousMenu = Menu::Menus::Playing;

		if ((!playerOne.collide || !playerTwo.collide) &&
			gameState == Menu::Menus::Playing || gameState == Menu::Menus::PlayingTwo)
		{
			if (IsKeyPressed(KEY_ESCAPE))
				pause = !pause;

			if (!pause)
			{
				if (spawmTimer <= 0)
				{
					pipeSets.push_back(Pipe::Creator());
					spawmTimer = 6;
				}
				else
					spawmTimer -= deltaTime;

				for (auto& pipeSetIt : pipeSets)
				{
					Pipe::Movement(pipeSetIt, deltaTime);
				}

				Pipe::HandleOutOfBounds(pipeSets);

				Player::AddPoint(playerOne.pos.x, playerOne.points, pipeSets);
				Player::Movement(playerOne, sprites.playerOneSheet, deltaTime);
				Player::PlayerPipeCollision(playerOne, pipeSets);
				if (gameState == Menu::Menus::PlayingTwo)
				{
					Player::AddPoint(playerTwo.pos.x, playerTwo.points, pipeSets);
					Player::Movement(playerTwo, sprites.playerTwoSheet, deltaTime);
					Player::PlayerPipeCollision(playerTwo, pipeSets);
				}
				
				spriteMovement.sky -= 10 * deltaTime;
				spriteMovement.backBuildings -= 30.0f * deltaTime;
				spriteMovement.frontBuildings -= 50.0f * deltaTime;
				spriteMovement.fence -= 100.0f * deltaTime;

				if (spriteMovement.sky <= -screenWidth)
					spriteMovement.sky = 0;

				if (spriteMovement.backBuildings <= -screenWidth)
					spriteMovement.backBuildings = 0;

				if (spriteMovement.frontBuildings <= -screenWidth)
					spriteMovement.frontBuildings = 0;

				if (spriteMovement.fence <= -screenWidth)
					spriteMovement.fence = 0;

			}
		}

		break;
	case Menu::Menus::HowToPlay:
		if (IsKeyPressed(KEY_ESCAPE))
			gameState = Menu::Menus::MainMenu;
		break;


	default:
		break;
	}
}


void draw(const Texture2D& texture,	Sprites::Sprites& sprites, std::list<Pipe::PipeSet>& pipeSets, float& spawmTimer, bool& pause,
	const Sprites::SpriteMovement& spriteMovement)
{
	BeginDrawing();

	ClearBackground(BLACK);

	switch (gameState)
	{
	case Menu::Menus::MainMenu:

		Drawers::DrawMainMenu(gameState, GetFontDefault(), texture);
		break;

	case Menu::Menus::Playing:
	case Menu::Menus::PlayingTwo:

		if (playerOne.collide || playerTwo.collide)
		{
			Drawers::DrawGameOver(gameState, GetFontDefault());

			GameManager::ShouldResetGame(gameState, playerOne, playerTwo, sprites.playerOneSheet, sprites.playerTwoSheet, pipeSets, spawmTimer, pause);
		}
		else
		{
			Drawers::DrawGamePlay(gameState, playerOne, playerTwo, pipeSets, sprites, spriteMovement, pause);

			if (pause)
			{
				Color semiTransparentBlack = { 0, 0, 0, 150 };
				DrawRectangle(0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight), semiTransparentBlack);

				Drawers::DrawPauseMenu(gameState, GetFontDefault(), pause);

				if (gameState == Menu::Menus::MainMenu)
					GameManager::ResetGame(playerOne, playerTwo, sprites.playerOneSheet, sprites.playerTwoSheet, pipeSets, spawmTimer, pause);
			}

		}

		break;

	case Menu::Menus::Rules:

		Drawers::DrawGameRules(gameState, GetFontDefault());
		break;

	case Menu::Menus::Credits:

		Drawers::DrawCredits(gameState, GetFontDefault());
		break;

	case Menu::Menus::WantToExit:

		Drawers::DrawConfirmExit(gameState, GetFontDefault(), previousMenu);
		break;

	default:
		break;
	}

	EndDrawing();
}

void close(Sprites::Sprites& sprites)
{
	Sprites::unloadSprites(sprites);

	CloseWindow();
}

} // namespace GameLoop