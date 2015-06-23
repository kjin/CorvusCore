#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include "cocos2d.h"
#include <vector>

class GameState;
class View;

#define GAME_VIEW_CREATE_FUNC(x) static x* x::create(const GameState* gameState) { x* pRet = new x(); if (pRet != nullptr && pRet->init(gameState)) { pRet->autorelease(); return pRet; } delete pRet; return nullptr; }

class GameView : public cocos2d::Node
{
private:
	std::vector<View*> _views;
protected:
	virtual bool init(const GameState* gameState);

	void update(float deltaTime) override;

	void addView(View* view);

	~GameView();
};

#endif