#include "pipe.h"

#include <cstdlib>

#include "Engine/engine.h"

float Pipe::actualSpacing = maxSpacing;

void Pipe::Movement(PipeSet& pipeSet, float deltaTime)
{
	pipeSet.top.rect.x -= speed * deltaTime;
	pipeSet.bottom.rect.x = pipeSet.top.rect.x;
}

Pipe::PipeSet Pipe::Creator()
{
	PipeSet newPipeSet = {};

	const float pipeWidth = 80;
	const float pipeHeight = screenHeight;

	newPipeSet.top.rect.x = screenWidth + newPipeSet.top.rect.width;

#pragma warning(disable:4244)
	newPipeSet.top.rect.y = rand() % (static_cast<int>(screenHeight - actualSpacing)) - pipeHeight;
#pragma warning(default:4244)

	newPipeSet.bottom.rect.x = newPipeSet.top.rect.x;
	newPipeSet.bottom.rect.y = newPipeSet.top.rect.y + pipeHeight + actualSpacing;


	newPipeSet.top.rect.width = pipeWidth;
	newPipeSet.bottom.rect.width = pipeWidth;

	newPipeSet.top.rect.height = pipeHeight;
	newPipeSet.bottom.rect.height = pipeHeight;

	return newPipeSet;
}

void Pipe::Destructor(std::list<PipeSet>& pipeSets)
{
	if (!pipeSets.empty())
	{
		for (auto pipeSetIt = pipeSets.begin(); pipeSetIt != pipeSets.end(); pipeSetIt++)
		{
			if (pipeSetIt->top.rect.x + pipeSetIt->top.rect.width <= 0.0f)
			{
				pipeSets.erase(pipeSetIt);
				break;
			}
		}
	}
}
