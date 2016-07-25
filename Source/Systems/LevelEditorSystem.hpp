#ifndef _LEVEL_EDITOR_SYSTEM_
    #define _LEVEL_EDITOR_SYSTEM_

#pragma once
#include "Leadwerks.h"
#include "LevelSystem.hpp"
#include "../Common.hpp"
#include "../Components/InputDictionary.hpp"
#include "../Components/Level.hpp"
#include "../Components/LevelEditor.hpp"
#include "../Utilities/Math/Math.hpp"
#include "../Utilities/Voxel.hpp"
#include "../Utilities/VoxelBuffer.hpp"

#include <cassert>
#include <list>
#include <string>

using namespace Components;

namespace Systems
{
    class LevelEditorSystem
    {
    private:

        static Leadwerks::Material* _pDefaultMaterial;

        static const float _nDefaultSize;

        static bool _bInitialized;

    public:

        static int Init(void)
        {
            assert(!_bInitialized);

            _bInitialized = true;

            return 0;
        }

        static void Shutdown(void)
        {
            assert(_bInitialized);
            
            _pDefaultMaterial->Release();
            delete _pDefaultMaterial;
            _pDefaultMaterial = nullptr;

            _bInitialized = false;
        }

        static LevelEditor* Create(const EditorConfig& _config, uint64_t _nEntityId, const std::string& _cName)
        {
            auto pEditor = new LevelEditor(_config, _nEntityId, _cName);
            if (pEditor->pCurrentVoxel == nullptr)
            {
                pEditor->pCurrentVoxel = new Voxel(_pDefaultMaterial, _nDefaultSize, _nDefaultSize, _nDefaultSize);
            }

            if (pEditor->pCursorMaterial == nullptr)
            {
                pEditor->pCursorMaterial = Leadwerks::Material::Create();
                pEditor->pCursorMaterial->SetColor(255.0f, 255.0, 255.0f, 0.5f);
            }

            if (pEditor->pDeleteIndicatingMaterial == nullptr)
            {
                pEditor->pDeleteIndicatingMaterial = Leadwerks::Material::Create();
                pEditor->pDeleteIndicatingMaterial->SetColor(255.0f, 0.0f, 0.0f, 0.5f);
            }

            if (pEditor->pSelectIndicatingMaterial == nullptr)
            {
                pEditor->pSelectIndicatingMaterial = Leadwerks::Material::Create();
                pEditor->pSelectIndicatingMaterial->SetColor(0.0f, 0.0f, 255.0f, 0.5f);
            }

            return pEditor;
        }

        static void Destroy(LevelEditor* _pEditor)
        {
            if (_pEditor != nullptr)
            {
                delete _pEditor;
                _pEditor = nullptr;
            }
        }

        static void Update(LevelEditor* _editor, float dt)
        {
            CheckInput(_editor, dt);
        }

        static PickResult AddVoxel(LevelEditor* _editor, Voxel* _pVoxel)
        {
            auto vStart = _editor->pCamera->GetPosition(true);   
            auto vRot = _editor->pCamera->GetRotation();
            auto vEnd = _editor->pInputMgr->GetMousePosition();

            vEnd.z = 0.025f;
            vEnd = _editor->pCamera->UnProject(vEnd)
                .Subtract(_editor->pCamera->GetPosition(true))
                .Normalize().Multiply(100.0f);

            auto result = LevelSystem::GetVoxel(
                _editor->pWorld,
                _editor->pLevel,
                vStart,
                vEnd);

            if (result.bHit && result.pRef == nullptr)
            {
                result.pRef = new Voxel(_editor->pCurrentVoxel);
                _editor->pLevel->pBuffer.Set(result.x, result.y, result.z, result.pRef);
                
                _editor->pLevel->bDirty = true;
            }

            return result;
        }

        static PickResult RemoveVoxel(LevelEditor* _pEditor)
        {
            auto vStart = _pEditor->pCamera->GetPosition(true);
            auto vRot = _pEditor->pCamera->GetRotation();
            auto vEnd = _pEditor->pInputMgr->GetMousePosition();

            vEnd.z = 0.025f;
            vEnd = _pEditor->pCamera->UnProject(vEnd)
                .Subtract(_pEditor->pCamera->GetPosition(true))
                .Normalize().Multiply(100.0f);

            auto result = LevelSystem::GetVoxel(
                _pEditor->pWorld,
                _pEditor->pLevel,
                vStart,
                vEnd);

            if (result.bHit && result.pRef != nullptr)
            {
                DeleteVoxel(result.pRef);

                _pEditor->pLevel->bDirty = true;
            }

            return result;
        }

        static void DeleteVoxel(Voxel* _pVoxel)
        {
            if (_pVoxel != nullptr)
            {
                delete _pVoxel;
                _pVoxel = nullptr;
            }
        }

        static void CheckInput(LevelEditor* _editor, float dt)
        {
            auto& mask = _editor->inputMask;

            if (mask.HasAnyStatus(EDITOR_ACTION_ADD_VOXEL))
            {
                auto result = AddVoxel(_editor, _editor->pCurrentVoxel);
            }
        }

    }; // < end class.

} // < end namespace.

#endif _LEVEL_EDITOR_SYSTEM_
