#ifndef _APPEARANCE_COMPONENT_TABLE_HPP_
	#define _APPEARANCE_COMPONENT_TABLE_HPP_

#pragma once
#include "Table.hpp"

#include "../../Components/Appearance.hpp"
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
    void Table<Components::Appearance>::CreateTable(IDbConnection* const _pConnection)
    {
        if (TableExists(_pConnection->Database(), "Appearance")) { return; }

        auto createTableQuery = std::string
        (
            "CREATE TABLE [Appearance]"
            "("
            " Id INTEGER PRIMARY KEY NOT NULL,"
            " ModelPath CHAR(128) NULL,"
            " ComponentId INTEGER NOT NULL,"
            " CreatedDate DATETIME NOT NULL DEFAULT (DATETIME('now', 'localtime')),"
            " ModifiedDate DATETIME NULL,"
            " FOREIGN KEY ([ComponentId]) REFERENCES [Component] ([Id]) ON DELETE CASCADE"
            ");"
        );

        auto pCommand = std::unique_ptr<DbCommand>(
            _pConnection->CreateCommand(new DbQuery(createTableQuery)));

        pCommand->ExecuteNonQuery();
    }
} // < end namespace.

#endif _APPEARANCE_COMPONENT_TABLE_HPP_