#ifndef _DBCONNECTION_HPP_
	#define _DBCONNECTION_HPP_

#pragma once
#include "IDbConnection.hpp"

#include "ClassType.hpp"
#include "DbConnectionState.hpp"
#include "DbConnectionOptions.hpp"
#include "DbConnectionString.hpp"
#include "IDbTransaction.hpp"
#include "IsolationLevel.hpp"

#include "sqlite/sqlite3.h"

#include <string>

class DbCommand;
class IDbQuery;

class DbConnection : public IDbConnection
{
    CLASS_TYPE(DbConnection);

public:

	explicit DbConnection(const DbConnectionString& _connectionString, const DbConnectionOptions& _connectionOptions);

	~DbConnection(void);

	IDbTransaction* const BeginTransaction(const std::string& _trans = "");
	IDbTransaction* const BeginTransaction(const IsolationLevel& _isolationLevel, const std::string& _trans = "");

	void ChangeDatabase(const DbConnectionString& _connectionString);

	void Close(void);
	DbCommand* CreateCommand(IDbQuery* const _pQuery);
	void Open(void);

	bool HasConnectionState(const unsigned& _connectionStateMask);
	bool HasAnyConnectionState(const unsigned& _connectionStateMask);

    std::string ErrorMessage(void);
    long long LastInsertRowId(void);

	sqlite3* const Database(void);
	const DbConnectionString ConnectionString(void);
	const DbConnectionState ConnectionState(void);
	const DbConnectionOptions ConnectionOptions(void);

protected:

	void AddConnectionState(const unsigned& _connectionStateMask);
	void RemoveConnectionState(const unsigned& _connectionStateMask);

private:

	sqlite3* m_pDatabase;

	unsigned m_connectionState;

	DbConnectionOptions m_connectionOptions;

	DbConnectionString m_connectionString;

}; // < end class.

#endif _DBCONNECTION_HPP_