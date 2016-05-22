#ifndef _COMPONENT_TABLE_HPP_
	#define _COMPONENT_TABLE_HPP_

#pragma once
#include "Table.hpp"
#include "../../Services/DatabaseController.hpp"

#include "../../Components/Component.hpp"

namespace Database
{
	template <>
	void Table<Components::Component>::CreateTable(IDatabaseController* const db)
	{
		DataTable tableDef;

		// < Primary Key.
		Table::AddDefinition("Id", "INTEGER PRIMARY KEY", "NOT NULL", tableDef);

		// < Name.
		Table::AddDefinition("Name", "CHAR(100)", "NUL", tableDef);

		// < Audit data.
		Table::AddAuditDefinitions(tableDef);

		db->CreateTable("Component", tableDef);
	}

} // < end namesoace.

#endif _COMPONENT_TABLE_HPP_
