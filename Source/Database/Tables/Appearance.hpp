#ifndef _APPEARANCE_COMPONENT_TABLE_HPP_
	#define _APPEARANCE_COMPONENT_TABLE_HPP_

#pragma once
#include "../../Services/DatabaseController.hpp"
#include "Table.hpp"

#include "../../Components/Appearance.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace Database
{
	template <>
	void Table<Components::Appearance>::CreateTable(IDatabaseController* const db)
	{
		DataTable tableDef;

		// < Primary key.
		Table::AddDefinition("Id", "INTEGER PRIMARY KEY", "NOT NULL", tableDef);

		// < Model path location.
		Table::AddDefinition("ModelPath", "CHAR(128)", "NULL", tableDef);

        // < FK componentId.
        Table::AddDefinition("ComponentId", "INTEGER", "NOT NULL REFERENCES Component(Id) ON DELETE CASCADE", tableDef);

        // < Audit Data.
        Table::AddAuditDefinitions(tableDef);

		db->CreateTable("Appearance", tableDef);

	}

    template <>
    std::vector<std::string> Table<Components::Appearance>::Serialize(const Components::Appearance& component)
    {
        auto result = Table<Components::Component>::Serialize(component);

        auto modelPath = component.cModelPath;

        result.push_back(modelPath);

        return result;
    }

    template <>
    Components::Appearance Table<Components::Appearance>::Deserialize(const std::vector<std::string>& component)
    {
        // < Id, Name, ModelPath .
        auto id = std::stoi(component[0]);
        auto name = component[1];
        auto modelPath = component[2];


        auto result = Components::Appearance(modelPath);
        result.nId = id;
        result.cName = name;

        return result;
    }
} // < end namespace.

namespace Components
{
    template <>
    std::vector<Components::Appearance> World::FetchComponents<Components::Appearance>(uint64_t entity, const std::vector<WhereClause>& expression, bool bSingle /* = false */)
    {
        std::string query = " \\
            SELECT c.[Id], c.[Name], a.[ModelPath] \\
            FROM[Appearance] AS a \\
            LEFT JOIN [Component] AS c \\
            ON c.[Id] = a.[ComponentId] \\
            WHERE c.[EntityId] = " + std::to_string(entity) + ";";

        std::vector<Components::Appearance> components;
        auto results = m_pDatabaseCtrl->ExecuteQuery(query);
        auto iter = results.begin();

        do
        {
            auto row = (*iter);
            auto comp = Database::Table<Components::Appearance>::Deserialize(row);
            components.push_back(comp);
            iter++;
        } while (!bSingle || iter != results.end());

        return components;
    }

    template <>
    Components::Appearance World::Merge<Components::Appearance>(const Components::Appearance& current, const Components::Appearance& original)
    {
        auto result = current;

        result.nId = original.nId;

        return result;
    }

    template <>
    Components::Appearance World::AddComponent<Components::Appearance>(uint64_t entity, const Components::Appearance& component)
    {
        std::string tableName = Components::Appearance::ClassType();

        auto comp = World::AddComponent<Components::Component>(entity, component);

        auto columns = ColumnCollection(1, "ModelPath");
        columns.push_back("ComponentId");

        auto values = ValueCollection(1, "\"" + component.cModelPath + "\"");
        values.push_back(std::to_string(comp.nId));

        auto id = std::to_string(m_pDatabaseCtrl->InsertRecord(tableName, columns, values));

        // < Select and return the new component.
        auto where = std::vector<WhereClause>(1, std::make_tuple("Id", "=", id));
        auto result = FetchComponents<Components::Appearance>(entity, where, true).front();

        return result;
    }

    template <>
    Components::Appearance World::UpdateComponent<Components::Appearance>(uint64_t entity, const Components::Appearance& component)
    {
        // < Fetch original.
        auto original = World::FetchComponents<Components::Appearance>(entity, std::vector<WhereClause>(), true).front();

        // < Merge original with current.
        auto current = World::Merge<Components::Appearance>(component, original);

        // < Save current.
        auto comp = World::UpdateComponent<Components::Component>(entity, current);

        auto values = KeyValCollection(1, std::make_pair("ModelPath", "\"" + component.cModelPath + "\""));
        auto clause = std::vector<WhereClause>(1, std::make_tuple("ComponentId", "=", std::to_string(comp.nId)));

        m_pDatabaseCtrl->UpdateRecord("Appearance", values, clause);

        // < Fetch updated current.
        auto updated = World::FetchComponents<Components::Appearance>(entity, clause, true).front();
        return updated;
    }

} // < end namespace.

#endif _APPEARANCE_COMPONENT_TABLE_HPP_