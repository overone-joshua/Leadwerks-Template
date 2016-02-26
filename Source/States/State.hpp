#ifndef _STATE_HPP_
	#define _STATE_HPP_

#pragma once
#include "../Utilities/Container.hpp"
#include "../Utilities/Factory.hpp"

class State {
public:

	virtual const char* ObjectType(void) = 0;	

	State(void) { }

	virtual void Configure(Container* pContainer) = 0;
	virtual void Load(void) { }
	virtual void Close(void) { }

	virtual void preUpdate(void) { }
	virtual void postUpdate(void) { }
	virtual bool Update(float deltaTime) = 0;

	virtual void preRender(void) { }
	virtual void postRender(void) { }
	virtual void Render(void) { }

	virtual void preDraw(void) { }
	virtual void postDraw(void) { }
	virtual void Draw(void) { }

}; // < end class.

extern Factory<State> gStateFactory;

#endif _STATE_HPP_