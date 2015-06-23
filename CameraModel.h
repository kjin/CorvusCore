#ifndef CAMERA_MODEL_H_
#define CAMERA_MODEL_H_

#include "Model.h"

#define PMV(type, varName) protected: type my##varName; /*Gets varName.*/ public: type get##varName() const { return my##varName; } /*Sets varName.*/ void set##varName(type n##varName) { my##varName = n##varName; }

class CameraModel : public Model
{
	PMV(cocos2d::Vec3, CameraTarget);
	PMV(cocos2d::Vec3, CameraUp);
public:
	CREATE_FUNC(CameraModel);
};

#endif