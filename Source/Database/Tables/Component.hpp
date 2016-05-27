#ifndef _COMPONENT_TABLE_HPP_
	#define _COMPONENT_TABLE_HPP_

#pragma once
#include "Table.hpp"
#include "../../Services/DatabaseController.hpp"

#include "../../Components/Component.hpp"
#include "../../Components/World.hpp"

namespace Database
{
	template <>
	void Table<Components::Component>::CreateTable(IDatabaseController* const db)
	{
		DataTable tableDef;

		// < Primary Key.
		Table::AddDefinition("Id", "INTEGER PRIMARY KEY", "NOT NULL", tableDef);

		// < Name.
		Table::AddDefinition("Name", "CHAR(100)", "NULL", tableDef);

		// < FK EntityId.
		Table::AddDefinition("EntityId", "INTEGER", "NOT NULL", tableDef);

		// < Audit data.
		Table::AddAuditDefinitions(tableDef);

		db->CreateTable("Component", tableDef);
	}

    template <>
    std::vector<std::string> Table<Components::Component>::Serialize(const Components::Component& component)
    {
        auto result = std::vector<std::string>();

        auto id = std::to_string(component.nId);
        auto name = component.cName;

        result.push_back(id);
        result.push_back(name);

        return result;
    }

    template <>
    Components::Component Table<Components::Component>::Deserialize(const std::vector<std::string>& component)
    {
        auto result = Components::Component();
        auto id = component[0];
        auto name = component[1];

        result.nId = std::stoi(id);
        result.cName = name;

        return result;
    }

} // < end namespace.

namespace Components
{
    template <>
    std::vector<Components::Component> World::FetchComponents<Components::Component>(uint64_t entity, const std::vector<WhereClause>& expression, bool bSingle /* = false */)
    {
        std::string tableName = Components::Component::ClassType();

        auto columns = ColumnCollection(1, "Id");
        columns.push_back("Name");

        auto clause = std::vector<WhereClause>(1, std::make_tuple("EntityId", "=", std::to_string(entity)));

        std::vector<Components::Component> components;
        auto results = m_pDatabaseCtrl->SelectRecords(tableName, columns, clause);
        auto iter = results.begin();

        do
        {
            auto row = (*iter);
            auto comp = Database::Table<Components::Component>::Deserialize(row);
            components.push_back(comp);
            iter++;

        } while (!bSingle || iter != results.end());

        return components;
    }

    template <>
    Components::Component World::Merge<Components::Component>(const Components::Component& current, const Components::Component& original)
    {
        auto result = current;

        result.nId = original.nId;

        return result;
    }

	template <>
	Components::Component World::AddComponent<Components::Component>(uint64_t entity, const Component& component)
	{
		std::string tableName = Components::Component::ClassType();

		auto columns = ColumnCollection(1, "Name");
		columns.push_back("EntityId");

		auto values = ValueCollection(1, "\"" + component.cName + "\"");
		values.push_back(std::to_string(entity));

		auto id = std::to_string(m_pDatabaseCtrl->InsertRecord(tableName, columns, values));

		// < Select and return the new component.
        auto where = std::vector<WhereClause>(1, std::make_tuple("Id", "=", id));
        auto result = World::FetchComponents<Components::Component>(entity, where, true).front();

        return result;
	}

	template <>
	void World::DeleteComponent<Components::Component>(uint64_t entity, const std::vector<WhereClause>& expression)
	{
		std::string tableName = Components::Component::ClassType();

		m_pDatabaseCtrl->DeleteRecords(tableName, expression);
	}

	template <>
    Components::Component World::UpdateComponent<Components::Component>(uint64_t entity, const Components::Component& component)
	{
		std::string tableName = Components::Component::ClassType();

		auto componentId = std::to_string(component.nId);
		auto entityId = std::to_string(entity);

		// < Select the original component.
		auto clause = std::vector<WhereClause>(1, std::make_tuple("Id", "=", componentId));
		clause.push_back(std::make_tuple("EntityId", "=",entityId));

		// < Merge the current with the original.
		auto original = World::FetchComponents<Components::Component>(entity, clause, true).front();
		auto current = World::Merge<Components::Component>(component, original);

		componentId = std::to_string(current.nId);

		auto values = KeyValCollection(1, std::make_pair("Id", componentId));
		values.push_back(std::make_pair("Name", "\""+ current.cName + "\""));
		values.push_back(std::make_pair("EntityId", entityId));

		// < Update the original component.
		clause = std::vector<WhereClause>(1, std::make_tuple("Id", "=", componentId));
		m_pDatabaseCtrl->UpdateRecord(tableName, values, clause);

		// < Fetch and return the updated component.
		auto updated = World::FetchComponents<Components::Component>(entity, clause, true).front();
		return updated;
	}

} // < end namespace.

#endif _COMPONENT_TABLE_HPP_
