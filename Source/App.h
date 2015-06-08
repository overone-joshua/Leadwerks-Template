#ifndef _APP_H_
	#define _APP_H_

#pragma once
#include "Leadwerks.h"
#include "Managers\EventManager.hpp"
#include "Managers\StateManager.hpp"
#include "Managers\InputManager.hpp"
#include "Managers\CameraManager.hpp"

// MACROS
#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p );   ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }

// -----

// CUSTOM ERROR Definitions
#define WINDOW_CREATION_ERROR	2
#define CONTEXT_CREATION_ERROR	4
#define WORLD_CREATION_ERROR	8
#define CAMERA_CREATION_ERROR	16

// -----

class GameObject;

class App
{
public:
										App();													// Application constructor.
	virtual								~App();													// Application destructor.
	
	virtual bool						Start();												// Called to bootstrap the application.
	virtual bool						Loop();													// The main game loop that runs every frame.

	Leadwerks::Window&					GetWindow();											// Gets the window handle.
	Leadwerks::Context&					GetContext();											// Gets the context handle.
	Leadwerks::World&					GetWorld();												// Gets the world handle.
	Leadwerks::Camera&					GetCamera();											// Gets the camera handle.

	std::string							Name();													// Gets the name of the application.
	unsigned							ScreenWidth();											// Gets the current width of the application screen.
	unsigned							ScreenHeight();											// Gets the current height of the application screen.
	bool								Fullscreen();											// Indicates whether the application is currently in full-screen.
	bool								Paused();												// Indicates whether the application is currently paused.

	void								setName(std::string name);								// Sets the name of the application.
	void								setScreenWidth(unsigned width);							// Sets the width if the application screen.
	void								setScreenHeight(unsigned height);						// Sets the height of the application screen.

	void								ToggleFullscreen();										// Toggles full-screen mode for the application.
	void								Pause();												// Pauses the application.
	void								UnPause();												// Un-pauses the application.

protected:
	int									Initialize();											// Initializes the application.
	void								Shutdown();												// Shuts down the application.
	
	void								OnLeadwerksInitialized(BaseEventData* pData);			// Method called after Leadwerks components have been initialized
																								// - using the event-manager.

	int									CreateWindow(const int flags = 0);						// Creates the application's window, using the given flags.
	int									CreateContext(const int flags = 0);						// Creates the application's rendering context, using the given flags.
	int									CreateWorld();											// Creates the application's primary world.
	int									CreateCamera(Leadwerks::Entity* pParent = nullptr);		// Create the application's primary camera, using the given parent.

private:
	bool								RegisterApplicationEvents();							// Method-place, where all application-events should be registered with the
																								// - event factory.
	Leadwerks::Window*					m_pWindow;												// The main window handle for the application.
	Leadwerks::Context*					m_pContext;												// The main rendering context handle for the application.
	Leadwerks::World*					m_pWorld;												// The main world handle for the application.
	Leadwerks::Camera*					m_pCamera;												// The main camera handle for the application.

	std::string							m_name;													// The name of the application
	unsigned							m_nScreenWidth;											// The current width, in pixels, of the screen.
	unsigned							m_nScreenHeight;										// The current height, in pixels, of the screen

	bool								m_bPaused;												// Indicates if the application is paused.
	bool								m_bFullscreen;											// Indicates if the application is rendered in full-screen mode.
	bool								m_bSettingsChangedThisFrame;							// Indicates if the application's settings were changed this frame.
	bool								m_bStateChangedThisFrame;								// Indicates whether the application experienced a change in state, this frame.

}; // end class App.

/* Externals */
extern App*								gApp;													// The global application handle.
extern EventManager*					gEventMgr;												// The global event manager handle.
extern StateManager*					gStateMgr;												// The global state manager handle.
extern InputManager*					gInputMgr;												// The global input manager handle.
extern CameraManager*					gCameraMgr;												// The global camera manager handle.

// -----

#endif // _APP_H_