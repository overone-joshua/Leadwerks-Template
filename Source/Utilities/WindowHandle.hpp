/*-------------------------------------------------------
                    <copyright>

    File: WindowHandle.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for WindowHandle utility.
                 The WindowHandle is a wrapper around
                 the Leadwerks::Window object.

    Functions: 1. Leadwerks::Window* getInst(void);

---------------------------------------------------------*/

#ifndef _WINDOW_HANDLE_HPP_
	#define _WINDOW_HANDLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Disposable.hpp"
#include "Macros.hpp"

class WindowHandle : public Disposable
{
	CLASS_TYPE(Window);

public:

	explicit WindowHandle(Leadwerks::Window* pWindow)
		:m_pWindow(pWindow){

	}

	~WindowHandle(void)
    {
        Dispose();
	}

    void Dispose(void)
    {
        SAFE_RELEASE(m_pWindow);
        SAFE_DELETE(m_pWindow);
    }

	Leadwerks::Window* getInst(void) { return m_pWindow; }

private:

	Leadwerks::Window* m_pWindow;

}; // < end class.

#endif _WINDOW_HANDLE_HPP_