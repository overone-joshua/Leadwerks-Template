/*-------------------------------------------------------
                    <copyright>
    
    File: InputManager.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for InputManager.
                 The InputManager provides a helper
                 interface around the Leadwerks::Window to 
                 simplify the input process pipeline when
                 it comes to polling and processing input.

---------------------------------------------------------*/

#ifndef _INPUTMANAGER_HPP_
	#define _INPUTMANAGER_HPP_

#pragma once
#include "..\Common.hpp"
#include "..\Utilities\Macros.hpp"
#include "..\Utilities\ParameterMap.hpp"

class EventManager;

class InputManager : ParameterMap {

	CLASS_TYPE(InputManager);

public:								
								InputManager(Leadwerks::Window* pWindow,		// InputManager constructor.
											 Leadwerks::Context* pContext,
											 EventManager* pEventManager);
								~InputManager();								// InputManager destructor.

								void Initialize(Leadwerks::Window* pWindow,
												Leadwerks::Context* pContext,
												EventManager* pEventManager);

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
	void						CenterMouse();
	void						UpdateMousePosition();

	Leadwerks::Vec3				GetMousePosition();
	Leadwerks::Vec3				GetWindowCenter();

protected:
	InputManager(void);

	void RegisterInputEvents(void);
	void UnRegisterInputEvents(void);

	void GenerateInputEvents(void);

	void CheckMouseInput(int button);
	void CheckKeyboardInput(int key);

private:
	Leadwerks::Window*			m_pWindow;										// The main window handle.
	Leadwerks::Context*			m_pContext;										// The main context handle.
	EventManager*				m_pEventManager;

	bool						m_bCenterMouse;									// Indicates whether the mouse pointer will be centered every frame.	

	bool m_currentMousePressedState[6];
	bool m_currentMouseState[6];
	bool m_previousMouseState[6];

	bool m_currentKeyboardPressedState[256];
	bool m_currentKeyboardState[256];
	bool m_previousKeyboardState[256];	

}; // end class.

#endif // _INPUTMANAGER_HPP_