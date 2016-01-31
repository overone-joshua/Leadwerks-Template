#ifndef _STATE_HPP_
	#define _STATE_HPP_

#pragma once
#include "../Utilities/Factory.hpp"

class State {
public:

	virtual const char* ObjectType(void) = 0;

	State(void);

	virtual void Load(void);
	virtual void Close(void);

	virtual void preUpdate(void);
	virtual void postUpdate(void);
	virtual bool Update(float deltaTime) = 0;

	virtual void preRender(void);
	virtual void postRender(void);
	virtual void Render(void);

	virtual void preDraw(void);
	virtual void postDraw(void);
	virtual void Draw(void);

}; // < end class.

State::State(void) { }

void State::Load(void) { }

void State::Close(void) { }

void State::preUpdate(void) { }

void State::postUpdate(void) { }

void State::preRender(void) { }

void State::Render(void) { }

void State::postRender(void) { }

void State::preDraw(void) { }

void State::Draw(void) { }

void State::postDraw(void) { }

Factory<State> gComponentFactory;

#endif _STATE_HPP_