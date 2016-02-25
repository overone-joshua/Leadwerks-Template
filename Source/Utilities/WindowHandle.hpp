#ifndef _WINDOW_HANDLE_HPP_
	#define _WINDOW_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Macros.hpp"

class WindowHandle {

	CLASS_TYPE(Window);

public:

	WindowHandle(Leadwerks::Window* pWindow) 
		:m_pWindow(pWindow){

	}

	~WindowHandle(void) {

		SAFE_RELEASE(m_pWindow);
		SAFE_DELETE(m_pWindow);

	}

	Leadwerks::Window* getInst(void) { return m_pWindow; }

private:

	Leadwerks::Window* m_pWindow;

}; // < end class.

#endif _WINDOW_HANDLE_HPP_