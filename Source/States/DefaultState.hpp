#ifndef _DEFAULT_STATE_HPP_
	#define _DEFAULT_STATE_HPP_

#pragma once
#include "State.hpp"

class DefaultState : public State {

	CLASS_TYPE(DefaultState);

public:		

	DefaultState(void);

	void Load(void);
	void Close(void);

	bool Update(float deltaTime);

}; // < end class.

DefaultState::DefaultState(void) { }

void DefaultState::Load(void) { }

void DefaultState::Close(void) { }

bool DefaultState::Update(float dt) { 

	return true;

}

#endif _DEFAULT_STATE_HPP_