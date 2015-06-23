#include "Controller.h"
#include "Model.h"

void Controller::update(float deltaTime)
{
	_model->update(deltaTime);
}
