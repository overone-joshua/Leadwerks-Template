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

        // < Model information.
        Table::AddDefinition("Model", "BLOB", "NULL", tableDef);

		// < FK ComponentId
		Table::AddDefinition("ComponentId", "INTEGER", "NOT NULL REFERENCES Component(Id) ON UPDATE NO ACTION", tableDef);

        // < Audit Data.
        Table::AddAuditDefinitions(tableDef);

		db->CreateTable("AppearanceComponent", tableDef);

	}
} // < end namespace.

#endif _APPEARANCE_COMPONENT_TABLE_HPP_