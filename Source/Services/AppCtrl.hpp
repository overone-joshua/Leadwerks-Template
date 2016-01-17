#ifndef _APP_CONTROLLER_HPP_
    #define _APP_CONTROLLER_HPP_

#pragma once
#include "leadwerks.h"

class App;

class AppCtrl {
public:
                            AppCtrl                 (App* pApp);                // < Constructor.
                            ~AppCtrl                (void);                     // < Destructor.

    const Leadwerks::Window&      getWindow               (void) const;               // < Gets the current window
    const Leadwerks::Context&     getContext              (void) const;               // < Gets the current rendering context.
    const Leadwerks::World&       getWorld                (void) const;               // < Gets the current world.
    const Leadwerks::Camera&      getCamera               (void) const;               // < Gets the current camera.

    const Leadwerks::Vec2   screen_upperLeft        (void) const;               // < Gets the upper-left screen coordinate.
    const Leadwerks::Vec2   screen_lowerRight       (void) const;               // < Gets the lower-right screen coordinate.

    const bool              isFullScreen            (void) const;               // < Indicates whether the application is currently in full-screen mode.

    const bool              Initialize              (const std::string appName) const;               // < Performs bootstrapping of application.
    void                    Shutdown                (void);                     // < Performs safe shutdown of application.

    void                    preUpdate               (void);
    const bool              Update                  (float deltaTime) const;    // < Performs all application logical updates every frame.
    void                    postUpdate              (void);

    void                    preDraw                 (void);
    void                    Draw                    (void);                     // < Performs all application 2D-rendering every frame.
    void                    postDraw                (void);

    void                    preRender               (void);
    void                    Render                  (void);                     // < Performs all application 3D-rendering every frame.
    void                    postRender              (void);

private:
    const bool              CreateWindowAndContext  (std::string name, unsigned nX = 0, unsigned nY = 0, unsigned nWidth = 1024, unsigned nHeight = 768, int windowFlags = 0, int contextFlags = 0) const;
    const bool              CreateWorld             (void) const;
    const bool              CreateCamera            (void) const;

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

    bool                    m_bFullScreen;                                      // < Indicates whether the application is currently in full-screen mode.
    bool                    m_bExitAppThisFrame;                                // < Indicates whether the application will begin closing within the current frame.

    Leadwerks::Vec2         m_vUpperLeft;                                       // < Represents the upper-left screen coordinate.
    Leadwerks::Vec2         m_vLowerRight;                                      // < Represents the lower-right screen coordinate.

}; // end class.

#endif _APP_COONTROLLER_HPP_