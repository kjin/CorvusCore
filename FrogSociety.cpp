#include "FrogSociety.h"

bool FrogGameState::init()
{
	if (!GameState::init())
	{
		return false;
	}
	return true;
}

bool FrogGameView::init(const GameState* gameState)
{
	if (!GameView::init(gameState))
	{
		return false;
	}
	return true;
}

bool FrogGameController::init(GameState* gameState)
{
	if (!GameController::init(gameState))
	{
		return false;
	}
	return true;
}
