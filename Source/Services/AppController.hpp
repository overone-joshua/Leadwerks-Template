/*-------------------------------------------------------
                    <copyright>
    
    File: AppController.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for AppController service.
                 The AppController class provides a clean
                 and efficient wrapper around the App class
                 and its execution pipeline.

    Functions: 1. const bool Initialize(const std::string appName, unsigned int ulX, unsigned int ulY
										, unsigned int nWidth, unsigned int nHeight, int windowFlags
										, int contextFlags);
                                        
                2. void Shutdown(void);

---------------------------------------------------------*/

#ifndef _APP_CONTROLLER_HPP_
    #define _APP_CONTROLLER_HPP_

#pragma once
#include "leadwerks.h"

class App;
class Container;
class WindowHandle;
class ContextHandle;
class WorldHandle;
class CameraHandle;

class AppController {
public:
                            		AppController                 (App* pApp);                // < Constructor.
                            		~AppController                (void);                     // < Destructor.

    const std::string       		getAppName              (void) const;               // < Gets the describing name of this application.

    const Leadwerks::Window&      	getWindow               (void) const;               // < Gets the current window
    const Leadwerks::Context&     	getContext              (void) const;               // < Gets the current rendering context.
    const Leadwerks::World&       	getWorld                (void) const;               // < Gets the current world.
    const Leadwerks::Camera&      	getCamera               (void) const;               // < Gets the current camera.

    const int               		getWindowFlags          (void) const;
    const int               		getRenderingContextFlags(void) const;

    const Leadwerks::Vec2   		screen_upperLeft        (void) const;               // < Gets the upper-left screen coordinate.
    const Leadwerks::Vec2   		screen_lowerRight       (void) const;               // < Gets the lower-right screen coordinate.

    const bool              		isFullScreen            (void) const;               // < Indicates whether the application is currently in full-screen mode.

	const bool              		Initialize(const std::string appName, unsigned int ulX, unsigned int ulY	// < Performs bootstrapping of application.
										, unsigned int nWidth, unsigned int nHeight, int windowFlags
										, int contextFlags);
    void                    		Shutdown                (void);                     // < Performs safe shutdown of application.

    void                    		preUpdate               (void);
    bool              				Update                  (float deltaTime);    		// < Performs all application logical updates every frame.
    void                    		postUpdate              (void);

    void                    		preDraw                 (void);
    void                    		Draw                    (void);                     // < Performs all application 2D-rendering every frame.
    void                    		postDraw                (void);

    void                    		preRender               (void);
    void                    		Render                  (void);                     // < Performs all application 3D-rendering every frame.
    void                    		postRender              (void);

private:
    const bool              		CreateWindowAndContext  (std::string name, unsigned nX = 0, unsigned nY = 0
										, unsigned nWidth = 1024, unsigned nHeight = 768, int windowFlags = 0
										, int contextFlags = 0);
    const bool              		CreateWorld             (void);
    const bool              		CreateCamera            (void);

	void							ReleaseApplication		(void);
    void                    		ReleaseWindowAndContext	(void);
    void                    		ReleaseWorld            (void);
    void                    		ReleaseCamera           (void);

    std::string             		m_appName;                                          // < Represents the describing name of the application.
    App*                    		m_pApp;                                             // < Application handle.

    int                     		m_windowFlags;                                      // < Holds the current bitField of window flags.
    int                     		m_renderingContextFlags;                            // < Holds the current bitField of openGL rendering flags.

    WindowHandle*		      		m_pWindow;                                          // < Application's window handle.
    ContextHandle*     				m_pContext;                                         // < Application's rendering context handle.
    WorldHandle*       				m_pWorld;                                           // < Application's 3D-world handle.
    CameraHandle*      				m_pCamera;                                          // < Application's camera handle.
    
	Container*						m_pContainer;

    bool                    		m_bExitAppThisFrame;                                // < Indicates whether the application will begin closing within the current frame.
    
}; // end class.

#endif _APP_COONTROLLER_HPP_