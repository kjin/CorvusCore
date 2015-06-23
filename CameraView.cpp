#include "CameraModel.h"
#include "CameraView.h"

using namespace cocos2d;

CameraView* CameraView::create(const CameraModel* cameraModel)
{
	CameraView* pRet = new CameraView();
	if (pRet != nullptr && pRet->init((const Model*)cameraModel, nullptr))
	{
		pRet->autorelease();
		return pRet;
	}
	delete pRet;
	return nullptr;
}

bool CameraView::init(const Model* model, Node* node)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_nodeAsCamera = cocos2d::Camera::createPerspective(45, visibleSize.width / visibleSize.height, 0.1f, 10000);
	_nodeAsCamera->setCameraFlag(CameraFlag::USER1);
	if (!View::init(model, _nodeAsCamera))
	{
		return false;
	}
	_modelAsCamera = (CameraModel*)model;
	return true;
}

void CameraView::update(float deltaTime)
{
	View::update(deltaTime);
	_nodeAsCamera->lookAt(_modelAsCamera->getCameraTarget(), _modelAsCamera->getCameraUp());
}
