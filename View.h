// View.h
// 6/20/2015

#ifndef VIEW_H_
#define VIEW_H_

#include "cocos2d.h"

#define VIEW_CREATE_FUNC(x) static x* create(const Model* model, cocos2d::Node* node) { x* pRet = new x(); if (pRet != nullptr && pRet->init(model, node)) { pRet->autorelease(); return pRet; } delete pRet; return nullptr; }

class Model;

class View : public cocos2d::Ref
{
protected:
	const Model* _model;
	cocos2d::Node* _sceneGraphNode;

	~View();
public:
	virtual bool init(const Model* model, cocos2d::Node* node);

	VIEW_CREATE_FUNC(View);

	cocos2d::Node* getNode() { return _sceneGraphNode; }

	virtual void update(float deltaTime);
};

#endif