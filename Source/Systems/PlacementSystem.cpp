
#pragma once
#include "PlacementSystem.hpp"

namespace Systems
{
    MemoryRepository<Placement>* PlacementSystem::_pPlacementRepository = nullptr;
    bool PlacementSystem::bInitialized = false;

} // < end namespace.