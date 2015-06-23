#ifndef _BOP_SPRITE_3D_MODEL_H_
#define _BOP_SPRITE_3D_MODEL_H_

#include "cocos2d.h"
#include "View.h"
#include <string>

class OBJ;
class Model;

class Sprite3DView : public View
{
protected:
	bool initWithModel(const Model* model);

	virtual bool initWithModelAndFile(const Model* model, const std::string& modelPath);
public:
	static Sprite3DView* createWithModelAndFile(const Model* model, const std::string& modelPath);
};

#endif