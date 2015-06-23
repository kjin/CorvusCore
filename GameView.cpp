#include "GameView.h"
#include "View.h"

bool GameView::init(const GameState* gameState)
{
	scheduleUpdate();
	return true;
}

void GameView::update(float deltaTime)
{
	for (unsigned i = 0; i < _views.size(); i++)
	{
		_views[i]->update(deltaTime);
	}
}

void GameView::addView(View* view)
{
	_views.push_back(view);
	view->retain();
	addChild(view->getNode());
}

GameView::~GameView()
{
	for (unsigned i = 0; i < _views.size(); i++)
	{
		_views[i]->release();
	}
	removeAllChildren();
}
