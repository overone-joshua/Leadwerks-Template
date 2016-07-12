#ifndef _SCENE_MANAGER_HPP_
    #define _SCENE_MANAGER_HPP_

#pragma once
#include "Leadwerks.h"

#include "../Utilities/CameraHandle.hpp"
#include "../Utilities/ContextHandle.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Manager.hpp"
#include "../Utilities/WindowHandle.hpp"
#include "../Utilities/WorldHandle.hpp"

#include <cassert>
#include <functional>
#include <list>
#include <string>

class SceneManager : public Manager
{
    CLASS_TYPE(SceneManager);

public:

    SceneManager(CameraHandle* _pCameraHndl, ContextHandle* _pContextHndl
        , WindowHandle* _pWindowHndl, WorldHandle* _pWorldHndl);
    ~SceneManager(void);

    void Dispose(void);

    bool Load(const std::string& _path);
    void Unload(void);

    void Update(float deltaTime);

protected:

    std::list<Leadwerks::Entity*> Entities(void);

    std::list<Leadwerks::Entity*> GetWhere(std::function<bool(Leadwerks::Entity*)> _expression);

private:

    CameraHandle* m_pCameraHndl;
    ContextHandle* m_pContextHndl;
    WindowHandle* m_pWindowHndl;
    WorldHandle* m_pWorldHndl;

}; // < end class.

#endif _SCENE_MANAGER_HPP_