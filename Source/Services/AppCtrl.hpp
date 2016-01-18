#ifndef _APP_CONTROLLER_HPP_
    #define _APP_CONTROLLER_HPP_

#pragma once
#include "leadwerks.h"

class App;

class AppCtrl {
public:
                            AppCtrl                 (App* pApp);                // < Constructor.
                            ~AppCtrl                (void);                     // < Destructor.

    const std::string       getAppName              (void) const;               // < Gets the describing name of this application.

    const Leadwerks::Window&      getWindow               (void) const;               // < Gets the current window
    const Leadwerks::Context&     getContext              (void) const;               // < Gets the current rendering context.
    const Leadwerks::World&       getWorld                (void) const;               // < Gets the current world.
    const Leadwerks::Camera&      getCamera               (void) const;               // < Gets the current camera.

    const int               getWindowFlags          (void) const;
    const int               getRenderingContextFlags(void) const;

    const Leadwerks::Vec2   screen_upperLeft        (void) const;               // < Gets the upper-left screen coordinate.
    const Leadwerks::Vec2   screen_lowerRight       (void) const;               // < Gets the lower-right screen coordinate.

    const bool              isFullScreen            (void) const;               // < Indicates whether the application is currently in full-screen mode.

	const bool              Initialize(const std::string appName, unsigned int ulX, unsigned int ulY
									, unsigned int nWidth, unsigned int nHeight, int windowFlags
									, int contextFlags);						// < Performs bootstrapping of application.
    void                    Shutdown                (void);                     // < Performs safe shutdown of application.

    void                    preUpdate               (void);
    bool              Update                  (float deltaTime) ;    // < Performs all application logical updates every frame.
    void                    postUpdate              (void);

    void                    preDraw                 (void);
    void                    Draw                    (void);                     // < Performs all application 2D-rendering every frame.
    void                    postDraw                (void);

    void                    preRender               (void);
    void                    Render                  (void);                     // < Performs all application 3D-rendering every frame.
    void                    postRender              (void);

private:
    const bool              CreateWindowAndContext  (std::string name, unsigned nX = 0, unsigned nY = 0, unsigned nWidth = 1024, unsigned nHeight = 768, int windowFlags = 0, int contextFlags = 0);
    const bool              CreateWorld             (void);
    const bool              CreateCamera            (void);

	void					ReleaseApplication		(void);
    void                    ReleaseWindowAndContext   (void);
    void                    ReleaseWorld              (void);
    void                    ReleaseCamera             (void);

    std::string             m_appName;                                          // < Represents the describing name of the application.
    App*                    m_pApp;                                             // < Application handle.

    int                     m_windowFlags;                                      // < Holds the current bitField of window flags.
    int                     m_renderingContextFlags;                            // < Holds the current bitField of openGL rendering flags.

    Leadwerks::Window*      m_pWindow;                                          // < Application's window handle.
    Leadwerks::Context*     m_pContext;                                         // < Application's rendering context handle.
    Leadwerks::World*       m_pWorld;                                           // < Application's 3D-world handle.
    Leadwerks::Camera*      m_pCamera;                                          // < Application's camera handle.
    
    bool                    m_bExitAppThisFrame;                                // < Indicates whether the application will begin closing within the current frame.    
}; // end class.

#endif _APP_COONTROLLER_HPP_