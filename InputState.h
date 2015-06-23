// InputState.h
// Stores pollable input state.

#ifndef _BOP_INPUT_STATE_H_
#define _BOP_INPUT_STATE_H_

#include "cocos2d.h"

#define NUM_KEYS 256

class InputState
{
	friend class InputController;
private:
	unsigned int _keyStates[NUM_KEYS];
public:
	bool isKeyDown(cocos2d::EventKeyboard::KeyCode keyCode) const
	{
		return _keyStates[(int)keyCode] != 0;
	}
};

#endif