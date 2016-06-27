#pragma once
#include "World.hpp"
#include "../Common.hpp"

#include "Component.hpp"
#include "ComponentDictionary.hpp"
#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbQuery.hpp>

#include <memory>

namespace Components
{
	World::World(IDbConnection* _pConnection, uint64_t _nEntityId, std::string cName)
		: Component(_nEntityId, cName), m_nRunningIndex(0), m_pConnection(_pConnection) { }

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

	void World::DeleteEntity(uint64_t entity)
	{
        if (entity < this->m_entityMasks.size())
        {
            this->m_entityMasks[entity] = COMPONENT_NONE;
            this->m_availableEntities.push(entity);

            auto query = std::string(
                "DELETE FROM [Components]"
                " WHERE [EntityId] = {Id};"
            );

            Replace("{Id}", std::to_string(entity), query);

            std::unique_ptr<DbCommand> pCommand(std::move(
                    m_pConnection->CreateCommand(new DbQuery(query))));

            pCommand->ExecuteNonQuery();
        }
	}

	void World::Dispose(void)
	{
        auto emptyQueue = std::queue<uint64_t>();
        std::swap(m_availableEntities, emptyQueue);

        auto emptyVector = std::vector<uint64_t>();
        std::swap(m_entityMasks, emptyVector);

        this->m_pConnection = nullptr;
        this->m_nRunningIndex = 0;
	}

} // < end namespace.