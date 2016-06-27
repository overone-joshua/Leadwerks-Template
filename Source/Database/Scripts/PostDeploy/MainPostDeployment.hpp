#ifndef _MAIN_POST_DEPLOYMENT_HPP_
	#define _MAIN_POST_DEPLOYMENT_HPP_

#pragma once

#include "../../Tables/Table.hpp"
#include "../../Tables/Component.hpp"
#include "../../Tables/Appearance.hpp"
#include "../../Tables/Placement.hpp"

#include <sqlite-persistence/DbConnectionState.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbJournalMode.hpp>
#include <sqlite-persistence/Sqlite3Helper.hpp>

namespace Database
{
	static inline bool Deploy(IDbConnection* const _connection)
	{
        if (_connection->HasConnectionState(CONNECTION_CLOSED)) { _connection->Open(); }

        SetJournalMode(_connection->Database(), JOURNAL_MODE_TRUNCATE);
        EnableForeignKeyConstraint(_connection->Database());

		Table<Components::Component>::CreateTable(_connection);
		Table<Components::Appearance>::CreateTable(_connection);
		Table<Components::Placement>::CreateTable(_connection);

		return true;
	}
} // < end namespace.

#endif _MAIN_POST_DEPLOYMENT_HPP_