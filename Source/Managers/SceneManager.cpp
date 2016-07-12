
#pragma once
#include "SceneManager.hpp"
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

SceneManager::SceneManager(CameraHandle* _pCameraHndl, ContextHandle* _pContextHndl
    , WindowHandle* _pWindowHndl, WorldHandle* _pWorldHndl) 
{ 
    assert(_pCameraHndl != nullptr);
    assert(_pContextHndl != nullptr);
    assert(_pWindowHndl != nullptr);
    assert(_pWindowHndl != nullptr);

    m_pCameraHndl = _pCameraHndl;
    m_pContextHndl = _pContextHndl;
    m_pWindowHndl = _pWindowHndl;
    m_pWorldHndl = _pWorldHndl;
}

SceneManager::~SceneManager(void) { Dispose(); }

void SceneManager::Dispose(void) 
{ 
    m_pContextHndl = nullptr;
    m_pContextHndl = nullptr;
    m_pWindowHndl = nullptr;
    m_pWorldHndl = nullptr;
}

bool SceneManager::Load(const std::string& _path)
{
    return Leadwerks::Map::Load(_path);
}

void SceneManager::Unload(void)
{
    auto pWorld = this->m_pWorldHndl->getInst();

    pWorld->Clear(true);
}

std::list<Leadwerks::Entity*> SceneManager::Entities(void)
{
    auto pWorld = this->m_pWorldHndl->getInst();

    return pWorld->entities;
}

std::list<Leadwerks::Entity*> SceneManager::GetWhere(std::function<bool(Leadwerks::Entity*)> _expression)
{
    auto pWorld = this->m_pWorldHndl->getInst();
    std::list<Leadwerks::Entity*> res;

    auto iter = pWorld->entities.begin();
    while (iter != pWorld->entities.end())
    {
        if (_expression(*iter)) { res.push_back(*iter); }
        ++iter;
    }

    return res;
}

void SceneManager::Update(float dt)
{

}