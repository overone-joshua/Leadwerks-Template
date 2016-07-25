
#pragma once
#include "LevelSystem.hpp"

namespace Systems
{
    MemoryRepository<Level>* LevelSystem::_pLevelRepository = nullptr;
    bool LevelSystem::_bInitialized = false;

    Leadwerks::Model* LevelSystem::_pFloor = nullptr;
    Leadwerks::Material* LevelSystem::_pFloorMaterial = nullptr;
}