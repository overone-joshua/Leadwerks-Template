#pragma once
#include "World.hpp"

#include "Component.hpp"
#include "ComponentDictionary.hpp"

namespace Components
{
	World::World(std::string cName) : m_nRunningIndex(0), Component(cName) { }

	World::~World(void) { }

	unsigned& World::Get(unsigned entity)
	{
		return m_entityMasks[entity];
	}

	unsigned World::CreateEntity(World* pWorld)
	{
		unsigned index = pWorld->m_nRunningIndex;

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

	void World::DestroyEntity(World* pWorld, unsigned entity)
	{
		if (entity < pWorld->m_entityMasks.size())
		{
			pWorld->m_entityMasks[entity] = COMPONENT_NONE;
			pWorld->m_availableEntities.push(entity);
		}
	}

} // < end namespace.