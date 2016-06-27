#pragma once
#include "DbConnection.hpp"

#include "DbConnectionState.hpp"
#include "DbConnectionString.hpp"
#include "DbConnectionOptions.hpp"
#include "DbCommand.hpp"
#include "DbCommand.hpp"
#include "DbTransaction.hpp"
#include "IDbTransaction.hpp"
#include "IsolationLevel.hpp"

#include "sqlite/sqlite3.h"

#include <cassert>
#include <string>

DbConnection::DbConnection(const DbConnectionString& _connectionString, const DbConnectionOptions& _connectionOptions)
	: m_pDatabase(nullptr), m_connectionString(_connectionString), m_connectionOptions(_connectionOptions)
	, m_connectionState(CONNECTION_CLOSED) { }

DbConnection::~DbConnection(void)
{
    this->Close();
}

std::string DbConnection::ErrorMessage(void) { return sqlite3_errmsg(this->m_pDatabase); }

sqlite3* const DbConnection::Database(void) { return this->m_pDatabase; }

const DbConnectionString DbConnection::ConnectionString(void) { return this->m_connectionString; }

const DbConnectionState DbConnection::ConnectionState(void) { return ((DbConnectionState)this->m_connectionState); }

const DbConnectionOptions DbConnection::ConnectionOptions(void) { return this->m_connectionOptions; }

long long DbConnection::LastInsertRowId(void) { return sqlite3_last_insert_rowid(this->m_pDatabase); }

IDbTransaction* const DbConnection::BeginTransaction(const std::string& _trans)
{
	return BeginTransaction(ISOLATION_LEVEL_DEFERRED, _trans);
}

IDbTransaction* const DbConnection::BeginTransaction(const IsolationLevel& _isolationLevel, const std::string& _trans)
{
	auto trans = new DbTransaction(this->m_pDatabase, _isolationLevel);
	trans->Begin(_trans);

	return trans;
}

void DbConnection::ChangeDatabase(const DbConnectionString& _connectionString)
{
	this->Close();

	if (this->HasConnectionState(CONNECTION_CLOSED))
	{
		this->m_connectionString = _connectionString;
	}
}

void DbConnection::Close(void)
{
	if (!this->HasConnectionState(CONNECTION_CLOSING) && this->HasAnyConnectionState(CONNECTION_BROKEN | CONNECTION_OPEN))
	{
		// < If this assert triggers, something went terribly wrong
		// * with our DbConnection life cycle.
		assert(m_pDatabase != nullptr);

		this->AddConnectionState(CONNECTION_CLOSING);

		auto res = sqlite3_close(this->m_pDatabase);
        if (res != SQLITE_OK)
        {
            throw this->ErrorMessage();
        }

		this->m_connectionState = CONNECTION_CLOSED;
	}
}

DbCommand* DbConnection::CreateCommand(IDbQuery* const _pQuery)
{
    auto pCommand = new DbCommand(_pQuery, this, nullptr);
    return pCommand;
}

void DbConnection::Open(void)
{
	if (this->HasAnyConnectionState(CONNECTION_BROKEN))
	{
		this->Close();
	}

	if (this->HasConnectionState(CONNECTION_CLOSED))
	{
		this->AddConnectionState(CONNECTION_CONNECTING);

		std::string cLocation = this->m_connectionString.cServer;

		if (cLocation.find_last_of("/\\") == std::string::npos)
		{
			cLocation.append("/");
		}

		cLocation.append(this->m_connectionString.cDatabase);

		auto res = sqlite3_open(cLocation.c_str(), &this->m_pDatabase);
		assert(res == SQLITE_OK);

		this->m_connectionState = CONNECTION_OPEN;
	}
}

bool DbConnection::HasConnectionState(const unsigned& _connectionStateMask)
{
	return ((this->m_connectionState & _connectionStateMask) == _connectionStateMask);
}

bool DbConnection::HasAnyConnectionState(const unsigned& _connectionStateMask)
{
	return ((this->m_connectionState & _connectionStateMask) == 1);
}

void DbConnection::AddConnectionState(const unsigned& _connectionStateMask)
{
	this->m_connectionState |= _connectionStateMask;
}

void DbConnection::RemoveConnectionState(const unsigned& _connectionStateMask)
{
	this->m_connectionState &= ~_connectionStateMask;
}