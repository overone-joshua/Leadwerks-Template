#ifndef _APPEARANCE_COMPONENT_TABLE_HPP_
	#define _APPEARANCE_COMPONENT_TABLE_HPP_

#pragma once
#include "../../Services/DatabaseController.hpp"
#include "Table.hpp"

#include "../../Components/Appearance.hpp"

#include <string>
#include <tuple>

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

		// < FK ComponentId
		Table::AddDefinition("ComponentId", "INTEGER", "NOT NULL REFERENCES Component(Id) ON DELETE CASCADE", tableDef);

        // < Audit Data.
        Table::AddAuditDefinitions(tableDef);

		db->CreateTable("AppearanceComponent", tableDef);

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

#endif _APPEARANCE_COMPONENT_TABLE_HPP_