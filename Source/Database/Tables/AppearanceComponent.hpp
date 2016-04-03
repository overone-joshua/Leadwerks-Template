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
		Table::AddDefinition("ModelPath", "CHAR(100)", "NULL", tableDef);

		db->CreateTable("AppearanceComponent", tableDef);
	}
} // < end namespace.

#endif _APPEARANCE_COMPONENT_TABLE_HPP_