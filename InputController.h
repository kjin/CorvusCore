#ifndef _BOP_INPUT_CONTROLLER_H_
#define _BOP_INPUT_CONTROLLER_H_

#include "cocos2d.h"

class InputState;

class InputController : public cocos2d::Ref
{
private:
	InputState* _inputState; // the state variable we modify

	cocos2d::EventDispatcher* _dispatcher;
	cocos2d::EventListenerKeyboard* _keyboardListener;
protected:
	InputController(InputState* inputState, cocos2d::EventDispatcher* dispatcher);

	~InputController();
public:
	static InputController* create(InputState* inputState, cocos2d::EventDispatcher* dispatcher)
	{
		InputController* inputController = new InputController(inputState, dispatcher);
		if (inputController != nullptr)
		{
			inputController->autorelease();
			return inputController;
		}
		return nullptr;
	}
};

#endif