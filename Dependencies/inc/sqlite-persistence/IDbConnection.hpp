#ifndef _IDBCONNECTION_HPP_
	#define _IDBCONNECTION_HPP_

#pragma once
#include "ClassType.hpp"
#include "DbCommand.hpp"
#include "DbConnectionState.hpp"
#include "DbConnectionString.hpp"
#include "DbConnectionOptions.hpp"
#include "IDbTransaction.hpp"
#include "IDbQuery.hpp"
#include "IsolationLevel.hpp"

#include "sqlite/sqlite3.h"

#include <string>

class IDbConnection
{
    CLASS_TYPE(IDbConnection);

public:
    virtual ~IDbConnection(void) { }

	virtual IDbTransaction* const BeginTransaction(const std::string& _trans = "") = 0;
	virtual IDbTransaction* const BeginTransaction(const IsolationLevel& _isolationLevel, const std::string& _trans = "") = 0;

	virtual void ChangeDatabase(const DbConnectionString& _connectionString) = 0;

	virtual void Close(void) = 0;
	virtual DbCommand* CreateCommand(IDbQuery* const _pQuery) = 0;
	virtual void Open(void) = 0;

	virtual bool HasConnectionState(const unsigned& _connectionStateMask) = 0;
	virtual bool HasAnyConnectionState(const unsigned& _connectionStateMask) = 0;

    virtual std::string ErrorMessage(void) = 0;
    virtual long long LastInsertRowId(void) = 0;

	virtual sqlite3* const Database(void) = 0;
	virtual const DbConnectionString ConnectionString(void) = 0;
	virtual const DbConnectionState ConnectionState(void) = 0;
	virtual const DbConnectionOptions ConnectionOptions(void) = 0;

}; // < end interface.

#endif _IDBCONNECTION_HPP_