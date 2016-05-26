#pragma once
#include "World.hpp"
#include "../Common.hpp"
#include "../Services/DatabaseController.hpp"

#include "Component.hpp"
#include "ComponentDictionary.hpp"

namespace Components
{
	World::World(IDatabaseController* databaseController, std::string cName)
		: Component(cName), m_nRunningIndex(0)
	{
		m_pDatabaseCtrl = databaseController;
	}

	World::~World(void) { Dispose(); }

	uint64_t World::CreateEntity(const std::string& name)
	{
        uint64_t index = this->m_nRunningIndex;

        if (!m_availableEntities.empty())
        {
            index = this->m_availableEntities.front();
            this->m_availableEntities.pop();
        }
        else
        {
            this->m_entityMasks.push_back(COMPONENT_NONE);
            this->m_nRunningIndex += 1;
        }

        return index;
	}

	unsigned long World::DeleteEntity(uint64_t entity)
	{
        if (entity < this->m_entityMasks.size())
        {
            this->m_entityMasks[entity] = COMPONENT_NONE;
            this->m_availableEntities.push(entity);

            auto where = std::vector<WhereClause>(1, std::make_tuple("EntityId", "=", std::to_string(entity)));
            return m_pDatabaseCtrl->DeleteRecords("Component", where);
        }
	}

	void World::Dispose(void)
	{
		// < Delete all entities.
		m_pDatabaseCtrl->ExecuteNoQuery("DELETE FROM Entity;");
		m_pDatabaseCtrl = nullptr;
	}

} // < end namespace.