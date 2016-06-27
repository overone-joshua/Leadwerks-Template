#ifndef _PLACEMENT_COMPONENT_TABLE_HPP_
	#define _PLACEMENT_COMPONENT_TABLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "Table.hpp"

#include "../../Components/Placement.hpp"
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
    void Table<Components::Placement>::CreateTable(IDbConnection* const _pConnection)
    {
        if (TableExists(_pConnection->Database(), "Placement")) { return; }

        auto createTableQuery = std::string
        (
            "CREATE TABLE [Placement]"
            "("
            " ID INTEGER PRIMARY KEY NOT NULL,"
            " ForwardX INTEGER NOT NULL,"
            " ForwardY INTEGER NOT NULL,"
            " ForwardZ INTEGER NOT NULL,"
            " RightX INTEGER NOT NULL,"
            " RightY INTEGER NOT NULL,"
            " RightZ INTEGER NOT NULL,"
            " TranslationX INTEGER NOT NULL,"
            " TranslationY INTEGER NOT NULL,"
            " TranslationZ INTEGER NOT NULL,"
            " RotationX INTEGER NOT NULL,"
            " RotationY INTEGER NOT NULL,"
            " RotationZ INTEGER NOT NULL,"
            " VelocityX INTEGER NOT NULL,"
            " VelocityY INTEGER NOT NULL,"
            " VelocityZ INTEGER NOT NULL,"
            " SpinX INTEGER NOT NULL,"
            " SpinY INTEGER NOT NULL,"
            " SpinZ INTEGER NOT NULL,"
            " Friction INTEGER NOT NULL,"
            " Visible INTEGER NOT NULL,"
            " Ghost INTEGER NOT NULL,"
            " IgnoreCollision INTEGER NOT NULL,"
            " TouchingGround INTEGER NOT NULL,"
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

#endif _PLACEMENT_COMPONENT_TABLE_HPP_