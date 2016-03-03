/*-------------------------------------------------------
                    <copyright>
    
    File: State.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for base State class.
                 The State class provides a base 
                 implementation for all further 
                 application states to build from.                                               

---------------------------------------------------------*/

#ifndef _STATE_HPP_
	#define _STATE_HPP_

#pragma once
#include "../Utilities/Container.hpp"
#include "../Utilities/Event.hpp"
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

	virtual void OnMouseHit(Event_MouseHit* pData) {}
	virtual void OnMouseDown(Event_MouseDown* pData) {}
	virtual void OnMouseUp(Event_MouseUp* pData) {}

	virtual void OnKeyHit(Event_KeyHit* pData) {}
	virtual void OnKeyDown(Event_KeyDown* pData) {}
	virtual void OnKeyUp(Event_KeyUp* pData) {}

}; // < end class.

extern Factory<State> gStateFactory;

#endif _STATE_HPP_