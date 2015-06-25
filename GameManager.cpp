#include "GameManager.h"
#include "GameState.h"
#include "GameView.h"
#include "GameController.h"

using namespace std;
USING_NS_CC;

// on "init" you need to initialize your instance
bool GameManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_gameState = nullptr;
	_gameView = nullptr;
	_gameController = nullptr;
	return true;
}

void GameManager::setGameState(GameState* gameState)
{
	if (_gameState != nullptr)
	{
		_gameState->release();
		_gameState = nullptr;
	}
	gameState->retain();
	_gameState = gameState;
}

void GameManager::setGameView(GameView* gameView)
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

void GameManager::setGameController(GameController* gameController)
{
	if (_gameController != nullptr)
	{
		_gameController->release();
		removeChild(_gameController);
		_gameController = nullptr;
	}
	addChild(gameController);
	_gameController = gameController;
}

void GameManager::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
