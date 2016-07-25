
#pragma once
#include "LevelEditorSystem.hpp"

namespace Systems
{
    Leadwerks::Material* LevelEditorSystem::_pDefaultMaterial = nullptr;
    
    const float LevelEditorSystem::_nDefaultSize = 1.0f;

    bool LevelEditorSystem::_bInitialized = false;

} // < end namespace.