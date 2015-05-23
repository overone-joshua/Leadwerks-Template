#ifndef _INPUTMANAGER_H_
	#define _INPUTMANAGER_H_

#pragma once
#include "Leadwerks.h"

class InputManager {
public:
								InputManager(Leadwerks::Window* pWindow,		// InputManager constructor.
											 Leadwerks::Context* pContext);
								~InputManager();								// InputManager destructor.

	void						Update(float deltaTime);						// InputManager Update.

	void						SetWindow(Leadwerks::Window* pWindow);			// Sets the input-manager's window handle.
	void						SetContext(Leadwerks::Context* pContext);		// Sets the input-manager's context handle.

	float						PosX();											// Gets the current x-position of the mouse pointer.
	float						PosY();											// Gets the current y-position of the mouse pointer.
	float						OldPosX();										// Gets the x-position of the mouse pointer, last frame.
	float						OldPosY();										// Gets the y-position of the mouse pointer, last frame.

	float						DeltaX();										// Gets the change in x-position between the last frame, and the current frame.
	float						DeltaY();										// Gets the change in y-position between the last frame, and the current frame.

	float						CenterX();										// Gets the center x-position of the window.
	float						CenterY();										// Gets the center y-position of the window.

	void						ToggleMouseCenter();							// Toggles between clamping the mouse pointer to the center of the window.

protected:

private:
	Leadwerks::Window*			m_pWindow;										// The main window handle.
	Leadwerks::Context*			m_pContext;										// The main context handle.

	bool						m_bCenterMouse;									// Indicates whether the mouse pointer will be centered every frame.

	float						m_nOldPosX;										// The x-position of the mouse pointer, last frame.
	float						m_nOldPosY;										// The y-position of the mouse pointer, last frame.

	float						m_nDeltaX;										// The change in x-position between the last frame, and the current frame.
	float						m_nDeltaY;										// The change in y-position between the last frame, and the current frame.

}; // end class InputManager.

#endif // _INPUTMANAGER_H_