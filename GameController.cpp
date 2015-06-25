#include "GameController.h"
#include "GameState.h"
#include "InputController.h"
#include "Controller.h"
#include <vector>

using namespace std;

// on "init" you need to initialize your instance
bool GameController::init(GameState* _gameState)
{
	scheduleUpdate();
	_inputController = InputController::create(_gameState->getInputState(), _eventDispatcher);
	_inputController->retain();
    return true;
}

void GameController::update(float deltaTime)
{
	for (Controller* controller : _modelControllers)
	{
		controller->update(deltaTime);
	}
}

void GameController::addController(Controller* gameController)
{
	gameController->retain();
	_modelControllers.push_back(gameController);
}
