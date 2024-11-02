#include "gameManager.h"

void GameManager::ResetGame(Player::Player& player, Texture2D& playerSheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause)
{
	player = Player::Player();

	player.frameRec = { 0.0f, 0.0f, (float)playerSheet.width / 3, (float)playerSheet.height };

	pipeSets.clear();

	spawnTimer = 0;

	pause = false;
}

void GameManager::ShouldResetGame(Menus& gameState, Player::Player& player, Texture2D& playerSheet, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause)
{
	switch (gameState)
	{
	case Menus::MainMenu:

		GameManager::ResetGame(player, playerSheet, pipeSets, spawnTimer, pause);
		break;

	case Menus::Replay:

		GameManager::ResetGame(player, playerSheet, pipeSets, spawnTimer, pause);
		gameState = Menus::Playing;
		break;

	case Menus::Exit:
		break;
	default:
		break;
	}
}
