#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

#include "cocos2d.h"

class GameState;
class GameView;
class GameController;

#define GAME_MANAGER_CREATE_FUNC(x) CREATE_FUNC(x)
#define GAME_MANAGER_CREATE_CLASS(className, gameState, gameView, gameController) class className : public GameManager { protected: bool init() override { if (GameManager::init()) { auto model = gameState::create(); setGameState(model); setGameView(gameView::create(model)); setGameController(gameController::create(model)); return true; } return false; } className() {} public: GAME_MANAGER_CREATE_FUNC(className); };
#define CREATE_GAME(x) GAME_STATE_CREATE_CLASS(x##GameState) GAME_VIEW_CREATE_CLASS(x##GameView) GAME_CONTROLLER_CREATE_CLASS(x##GameController) GAME_MANAGER_CREATE_CLASS(x##GameManager, x##GameState, x##GameView, x##GameController)

class GameManager : public cocos2d::Layer
{
private:
	GameState* _gameState;
	GameView* _gameView;
	GameController* _gameController;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
protected:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void setGameState(GameState* gameState);
	void setGameView(GameView* gameView);
	void setGameController(GameController* controller);
};

#endif
