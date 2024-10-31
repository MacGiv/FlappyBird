#include "pipe.h"

#include <cstdlib>

#include "engine.h"

float Pipe::actualSpacing = maxSpacing;

void Pipe::Movement(PipeSet& pipeSet, float deltaTime)
{
	pipeSet.top.rect.x -= speed * deltaTime;
	pipeSet.bottom.rect.x -= speed * deltaTime;
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
