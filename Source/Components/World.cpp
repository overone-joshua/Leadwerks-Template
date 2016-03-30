#pragma once
#include "World.hpp"
#include "../Common.hpp"

#include "Component.hpp"
#include "ComponentDictionary.hpp"

namespace Components
{
	World::World(std::string cName) : m_nRunningIndex(0), Component(cName) { }

	World::~World(void) { Dispose(); }

	uint64_t& World::GetEntityMask(uint64_t entity)
	{
        // < TODO: Rework component indexing to use GUID.
		return m_entityMasks[entity];
	}

	std::vector<uint64_t> World::GetEntities(World* pWorld, uint64_t entityMask)
	{
		std::vector<uint64_t> results;
		uint64_t entity = 0;

		while (entity < pWorld->m_entityMasks.size())
		{
			if ( (pWorld->m_entityMasks[entity] & entityMask) == entityMask) { results.push_back(entity); }

			entity += 1;
		}

		return results;
	}

	uint64_t World::CreateEntity(World* pWorld)
	{
		uint64_t index = pWorld->m_nRunningIndex;

		if (!m_availableEntities.empty())
		{
			index = pWorld->m_availableEntities.front();
			pWorld->m_availableEntities.pop();
		}
		else
		{
			pWorld->m_entityMasks.push_back(COMPONENT_NONE);
			pWorld->m_nRunningIndex += 1;
		}

		return index;
	}

	void World::DestroyEntity(World* pWorld, uint64_t entity)
	{
		if (entity < pWorld->m_entityMasks.size())
		{
			pWorld->m_entityMasks[entity] = COMPONENT_NONE;
			pWorld->m_availableEntities.push(entity);

            pWorld->RemoveComponents(pWorld, entity);
		}
	}

    void World::RemoveComponents(World* pWorld, uint64_t entity)
    {
        auto iter = m_components.begin();
        while (iter != m_components.end())
        {
            auto index = iter->first.first;

            // < Is this a component list for the given entity?
            if (index == entity)
            {
                // < We don't know what type of component we are dealing with
                // * however, we do know that the contents of a vector are
                // * stored within an array so we can delete the contents
                // * through a SAFE_DELETE_ARRAY.
                SAFE_DELETE_ARRAY(iter->second);
                iter = m_components.erase(iter);
            }

            if (iter != m_components.end()) { iter++; }
        }

    }

	void World::Dispose(void)
	{
		auto iter = m_components.begin();
		while (iter != m_components.end())
		{
			SAFE_DELETE(iter->second);
			iter = m_components.erase(iter);

			if (iter != m_components.end()) { iter++; }
		}
		m_components.clear();

		while (!m_availableEntities.empty())
		{
			m_availableEntities.pop();
		}

		m_entityMasks.clear();

		m_nRunningIndex = 0;
	}

} // < end namespace.