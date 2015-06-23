#ifndef _BOP_GAME_CONTROLLER_H_
#define _BOP_GAME_CONTROLLER_H_

#include "cocos2d.h"

class GameState;
class GameView;
class InputController;
class Controller;

class GameController : public cocos2d::Layer
{
private:
	// State
	GameState* _gameState;
	GameView* _gameView;

	// Controller
	InputController* _inputController;
	std::vector<Controller*> _modelControllers;

	void update(float deltaTime) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameController);
protected:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void setGameState(GameState* gameState);

	void setGameView(GameView* gameView);

	void addController(Controller* controller);
};

#endif // __HELLOWORLD_SCENE_H__
