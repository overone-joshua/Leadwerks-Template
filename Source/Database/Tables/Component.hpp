#ifndef _COMPONENT_TABLE_HPP_
	#define _COMPONENT_TABLE_HPP_

#pragma once
#include "Table.hpp"

#include "../../Components/Component.hpp"
#include "../../Components/World.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbQuery.hpp>
#include <sqlite-persistence/Sqlite3Helper.hpp>

#include <memory>
#include <string>

namespace Database
{
	template <>
	void Table<Components::Component>::CreateTable(IDbConnection* const _pConnection)
	{
        if (TableExists(_pConnection->Database(), "Component")) { return; }

        std::string createTableQuery =
            "CREATE TABLE [Component]"
            " ("
            " Id INTEGER PRIMARY KEY NOT NULL,"
            " Name CHAR(100) NULL,"
            " EntityId INTEGER NOT NULL,"
            " CreatedDate DATETIME NOT NULL DEFAULT (DATETIME('now', 'localtime')),"
            " ModifiedDate DATETIME NULL"
            " );";

        auto pCommand = std::unique_ptr<DbCommand>(
            _pConnection->CreateCommand(new DbQuery(createTableQuery)));

        pCommand->ExecuteNonQuery();
	}

} // < end namespace.

#endif _COMPONENT_TABLE_HPP_
