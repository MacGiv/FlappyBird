#include "player.h"

void Player::Movement(Player& player, float deltaTime)
{
	const float jumpForce = -300.0f;
	const float gravity = 500.0f;

	if (IsKeyPressed(KEY_SPACE))
	{
		player.velocityY = jumpForce;
	}

	player.velocityY += gravity * deltaTime;
	player.pos.y += player.velocityY * deltaTime;

	if (player.pos.y > screenHeight - player.radius)
	{
		player.pos.y = screenHeight - player.radius;
		player.velocityY = 0;
	}

	if (player.pos.y < player.radius)
	{
		player.pos.y = player.radius;
		player.velocityY = 0;
	}
}

void Player::AddPoint(float posX, int& points, std::list<Pipe::PipeSet>& pipes)
{
	for (auto& pipe : pipes)
	{
		if (!pipe.counted && posX >= pipe.top.rect.x)
		{
			points++;
			pipe.counted = true;
			break;
		}
	}
}

void Player::DidPlayerDied(Player& player, std::list<Pipe::PipeSet>& pipes)
{
	//Rect Circle Collition

	for (const auto& pipe : pipes)
	{
		float closestX = std::max(pipe.top.rect.x, std::min(player.pos.x, pipe.top.rect.x + pipe.top.rect.width));
		float closestY = std::max(pipe.top.rect.y, std::min(player.pos.y, pipe.top.rect.y + pipe.top.rect.height));

		float distanceX = player.pos.x - closestX;
		float distanceY = player.pos.y - closestY;

		if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius))
		{
			player.collide = true;
			break;
		}

		closestX = std::max(pipe.bottom.rect.x, std::min(player.pos.x, pipe.bottom.rect.x + pipe.bottom.rect.width));
		closestY = std::max(pipe.bottom.rect.y, std::min(player.pos.y, pipe.bottom.rect.y + pipe.bottom.rect.height));

		distanceX = player.pos.x - closestX;
		distanceY = player.pos.y - closestY;

		if ((distanceX * distanceX + distanceY * distanceY) <= (player.radius * player.radius))
		{
			player.collide = true;
			break;
		}
	}
}