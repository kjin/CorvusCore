#include "GameState.h"
#include "InputState.h"
#include "cocos2d.h"
#include "Model.h"

using namespace cocos2d;

bool GameState::init()
{
	_inputState = new InputState();

	_models = new Array2D<Model*>();
	return true;
}

void GameState::addModel(Model* model, unsigned vectorID, unsigned itemID)
{
	model->retain();
	_models->addItem(model, vectorID, itemID);
}

GameState::~GameState()
{
	delete _inputState;
	for (unsigned i = 0; i < _models->getNumRows(); i++)
	{
		for (unsigned j = 0; j < _models->getNumItems(i); j++)
		{
			if (_models->getItem(i, j) != nullptr)
			{
				_models->getItem(i, j)->release();
			}
		}
		_models->clearItems(i);
	}
	delete _models;
}
