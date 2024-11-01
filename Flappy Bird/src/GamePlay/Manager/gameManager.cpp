#include "gameManager.h"

void GameManager::ResetGame(Player::Player& player, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer, bool& pause)
{
	player = Player::Player();

	pipeSets.clear();

	spawnTimer = 0;

	pause = false;
}

void GameManager::ShouldResetGame(Menus& gameState, Player::Player& player, std::list<Pipe::PipeSet>& pipeSets, float& spawnTimer ,bool& pause)
{
	switch (gameState)
	{
	case Menus::MainMenu:

		GameManager::ResetGame(player, pipeSets, spawnTimer, pause);
		break;

	case Menus::Replay:

		GameManager::ResetGame(player, pipeSets, spawnTimer, pause);
		gameState = Menus::Playing;
		break;

	case Menus::Exit:
		break;
	default:
		break;
	}
}
