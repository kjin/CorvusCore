#ifndef CAMERA_VIEW_H_
#define CAMERA_VIEW_H_

#include "View.h"

class CameraModel;

class CameraView : public View
{
protected:
	CameraModel* _modelAsCamera;
	cocos2d::Camera* _nodeAsCamera;
protected:
	bool init(const Model* model, cocos2d::Node* node) override;
public:
	static CameraView* create(const CameraModel* cameraModel);

	void update(float deltaTime) override;
};

#endif
