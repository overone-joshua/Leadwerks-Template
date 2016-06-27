#ifndef _DBTRANSACTION_HPP_
	#define _DBTRANSACTION_HPP_

#pragma once
#include "IDbTransaction.hpp"

#include "ClassType.hpp"
#include "IDbConnection.hpp"

#include "sqlite/sqlite3.h"

class DbTransaction : public IDbTransaction
{
    CLASS_TYPE(DbTransaction);

public:
	DbTransaction(sqlite3* _pDatabase, const IsolationLevel& _isolationLevel = ISOLATION_LEVEL_DEFERRED);

	~DbTransaction(void);

	void Begin(std::string _trans = "");

	void Commit(std::string _trans = "");

	void Rollback(std::string _trans = "");

protected:

private:

	sqlite3* m_pDatabase;

	IsolationLevel m_isolationLevel;

}; // < end class.

#endif _DBTRANSACTION_HPP_
