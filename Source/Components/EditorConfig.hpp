#ifndef _EDITOR_CONFIG_HPP_
    #define _EDITOR_CONFIG_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Components/Level.hpp"
#include "../Managers/InputManager.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Voxel.hpp"

#include <list>

namespace Components
{
    typedef struct Component_EditorConfig
    {
        CLASS_TYPE(EditorConfig);

        InputManager* pInputMgr;

        Leadwerks::Camera* pCamera;
        Leadwerks::World* pWorld;
        Level* pLevel;

        Leadwerks::Material* pCursorMaterial;
        Leadwerks::Material* pDeleteIndicatingMaterial;
        Leadwerks::Material* pSelectIndicatingMaterial;

        Voxel* pCurrentVoxel;

        std::list<Leadwerks::Material*> materialCollection;
        std::list<Voxel*> voxelPresets;

        explicit Component_EditorConfig(InputManager* _pInputManager, Leadwerks::Camera* const _pCamera, Leadwerks::World* const _pWorld, Level* const _pLevel, uint64_t _nEntityId, const string& _cName)
            : pInputMgr(_pInputManager), pCamera(_pCamera), pWorld(_pWorld), pLevel(_pLevel), pCurrentVoxel(nullptr)
        {

        }

    } EditorConfig;
} // < end namespace.

#endif _EDITOR_CONFIG_HPP_
