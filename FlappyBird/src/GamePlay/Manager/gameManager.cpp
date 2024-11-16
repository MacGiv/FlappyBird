#include "gameManager.h"

void GameManager::ResetGame(Player::Player& p1, Player::Player& p2, Texture2D& playerOneSheet, Texture2D& playerTwoSheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause)
{
	p1 = Player::Player();
	p2 = Player::Player();
	p1.id = 1;
	p2.id = 2;
	p1.frameRec = { 0.0f, 0.0f, (float)playerOneSheet.width / 3, (float)playerOneSheet.height };
	p2.frameRec = { 0.0f, 0.0f, (float)playerOneSheet.width / 3, (float)playerTwoSheet.height };

	pipeSets.clear();

	spawnTimer = 0;

	pause = false;
}

void GameManager::ShouldResetGame(Menu::Menus& gameState, Player::Player& p1, Player::Player& p2, Texture2D& p1Sheet, Texture2D& p2Sheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause)
{
	switch (gameState)
	{
	case Menu::Menus::MainMenu:

		GameManager::ResetGame(p1, p2, p1Sheet, p2Sheet, pipeSets, spawnTimer, pause);
		break;

	case Menu::Menus::Replay:

		GameManager::ResetGame(p1, p2, p1Sheet, p2Sheet, pipeSets, spawnTimer, pause);
		gameState = Menu::Menus::Playing;
		break;

	case Menu::Menus::Exit:
		break;
	default:
		break;
	}
}
