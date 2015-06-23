#include "InputController.h"
#include "InputState.h"

using namespace cocos2d;

InputController::InputController(InputState* inputState, EventDispatcher* dispatcher)
	: _inputState(inputState), _dispatcher(dispatcher)
{
	_keyboardListener = EventListenerKeyboard::create();

	_keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		_inputState->_keyStates[(int)keyCode] = 1;
	};

	_keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		_inputState->_keyStates[(int)keyCode] = 0;
	};

	_dispatcher->addEventListenerWithFixedPriority(_keyboardListener, 1);
}

InputController::~InputController()
{
	_dispatcher->removeEventListener(_keyboardListener);
	_keyboardListener = nullptr;
}
