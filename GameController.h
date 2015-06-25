#ifndef _BOP_GAME_CONTROLLER_H_
#define _BOP_GAME_CONTROLLER_H_

#include "cocos2d.h"

class GameState;
class GameView;
class InputController;
class Controller;

#define GAME_CONTROLLER_CREATE_FUNC(x) static x* x::create(GameState* gameState) { x* pRet = new x(); if (pRet != nullptr && pRet->init(gameState)) { pRet->autorelease(); return pRet; } delete pRet; return nullptr; }
#define GAME_CONTROLLER_CREATE_CLASS(x) class x : public GameController { protected: bool init(GameState* gameState) override; x() {} public: GAME_CONTROLLER_CREATE_FUNC(x); };

class GameController : public cocos2d::Node
{
private:
	// Controller
	InputController* _inputController;
	std::vector<Controller*> _modelControllers;

	void update(float deltaTime) override;
protected:
	virtual bool init(GameState* gameState);

	void addController(Controller* controller);
};

#endif // __HELLOWORLD_SCENE_H__
