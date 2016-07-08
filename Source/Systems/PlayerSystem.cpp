
#pragma once
#include "PlayerSystem.hpp"

namespace Systems
{
    MemoryRepository<Placement>* PlayerSystem::_pPlacementRepository = nullptr;
    MemoryRepository<Player>* PlayerSystem::_pPlayerRepository = nullptr;

    bool PlayerSystem::bInitialized = false;

} // < end namespace.