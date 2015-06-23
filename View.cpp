#include "View.h"
#include "Model.h"

bool View::init(const Model* model, cocos2d::Node* node)
{
	_model = model;
	_sceneGraphNode = node;
	_sceneGraphNode->retain();
	return true;
}

View::~View()
{
	_sceneGraphNode->release();
}

void View::update(float deltaTime)
{
	if (_model->getModelHealth() > 0)
	{
		_sceneGraphNode->setVisible(true);
		_sceneGraphNode->setPosition3D(_model->getModelPosition());
	}
	else if (_sceneGraphNode->isVisible())
	{
		_sceneGraphNode->setVisible(false);
	}
}
