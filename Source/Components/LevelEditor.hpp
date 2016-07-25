#ifndef _LEVEL_EDITOR_HPP_
    #define _LEVEL_EDITOR_HPP_

#pragma once
#include "EditorConfig.hpp"
#include "Leadwerks.h"
#include "../Common.hpp"
#include "../Components/Level.hpp"
#include "../Managers/InputManager.hpp"
#include "../Utilities/Bitmask.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/Voxel.hpp"

#include <list>

namespace Components
{
    typedef struct Component_LevelEditor
    {
        typedef enum EditorState { EDITOR_STATE_SCULPT, EDITOR_STATE_PLACE };

        CLASS_TYPE(LevelEditor);

        InputManager* pInputMgr;
        Leadwerks::Camera* pCamera;
        Leadwerks::World* pWorld;
        Level* pLevel;

        EditorState state;

        Leadwerks::Material* pCursorMaterial;
        Leadwerks::Material* pDeleteIndicatingMaterial;
        Leadwerks::Material* pSelectIndicatingMaterial;

        Voxel* pCurrentVoxel;

        std::list<Leadwerks::Material*> materialCollection;
        std::list<Voxel*> voxelPresets;

        Bitmask inputMask;

        explicit Component_LevelEditor(const EditorConfig& _config, uint64_t _nEntityId, const string& _cName)
        {
            assert(_config.pInputMgr != nullptr);
            assert(_config.pCamera != nullptr);
            assert(_config.pWorld != nullptr);
            assert(_config.pLevel != nullptr);

            assert(_config.pCursorMaterial != nullptr);
            assert(_config.pDeleteIndicatingMaterial != nullptr);
            assert(_config.pSelectIndicatingMaterial != nullptr);

            pInputMgr = _config.pInputMgr;
            pCamera = _config.pCamera;
            pWorld = _config.pWorld;
            pLevel = _config.pLevel;

            state = EDITOR_STATE_SCULPT;

            pCurrentVoxel = _config.pCurrentVoxel;
            pCursorMaterial = _config.pCursorMaterial;
            pDeleteIndicatingMaterial = _config.pDeleteIndicatingMaterial;
            pSelectIndicatingMaterial = _config.pSelectIndicatingMaterial;

            inputMask = Bitmask();
        }

        ~Component_LevelEditor(void)
        {
            pInputMgr = nullptr;
            pCamera = nullptr;
            pWorld = nullptr;
            pLevel = nullptr;

            if (pCurrentVoxel != nullptr)
            {
                delete pCurrentVoxel;
                pCurrentVoxel = nullptr;
            }

            if (pCursorMaterial != nullptr)
            {
                pCursorMaterial->Release();
                delete pCursorMaterial;
                pCursorMaterial = nullptr;
            }

            if (pDeleteIndicatingMaterial != nullptr)
            {
                pDeleteIndicatingMaterial->Release();
                delete pDeleteIndicatingMaterial;
                pDeleteIndicatingMaterial = nullptr;
            }

            if (pSelectIndicatingMaterial != nullptr)
            {
                pSelectIndicatingMaterial->Release();
                delete pSelectIndicatingMaterial;
                pSelectIndicatingMaterial = nullptr;
            }

            inputMask.SetStatus(0);
        }

    } LevelEditor;
} // < end namespace.

#endif _LEVEL_EDITOR_HPP_
