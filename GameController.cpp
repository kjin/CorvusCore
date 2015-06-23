#include "GameController.h"
#include <vector>
#include "GameState.h"
#include "GameView.h"
#include "InputController.h"
#include "Controller.h"

using namespace std;
USING_NS_CC;

// on "init" you need to initialize your instance
bool GameController::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	scheduleUpdate();
	_gameState = nullptr;
	_gameView = nullptr;
	_inputController = nullptr;
    return true;
}

void GameController::update(float deltaTime)
{
	if (_gameState != nullptr && _inputController == nullptr)
	{
		_inputController = InputController::create(_gameState->getInputState(), _eventDispatcher);
		_inputController->retain();
	}
	for (Controller* controller : _modelControllers)
	{
		controller->update(deltaTime);
	}
}

void GameController::setGameState(GameState* gameState)
{
	if (_gameState != nullptr)
	{
		_gameState->release();
		_gameState = nullptr;
	}
	gameState->retain();
	_gameState = gameState;
}

void GameController::setGameView(GameView* gameView)
{
	if (_gameView != nullptr)
	{
		_gameView->release();
		removeChild(_gameView);
		_gameView = nullptr;
	}
	addChild(gameView);
	_gameView = gameView;
}

void GameController::addController(Controller* gameController)
{
	gameController->retain();
	_modelControllers.push_back(gameController);
}

void GameController::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
