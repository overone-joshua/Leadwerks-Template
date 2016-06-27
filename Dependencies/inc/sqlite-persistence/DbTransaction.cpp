#pragma once
#include "DbTransaction.hpp"

#include "IDbConnection.hpp"
#include "IsolationLevel.hpp"

#include "sqlite/sqlite3.h"

#include <cassert>

DbTransaction::DbTransaction(sqlite3* _pDatabase, const IsolationLevel& _isolationLevel)
	: m_pDatabase(_pDatabase), m_isolationLevel(_isolationLevel) { }

DbTransaction::~DbTransaction(void) { }

void DbTransaction::Begin(std::string _trans)
{
	std::string query;
    int res;

	query = (_trans.empty()) ? "BEGIN TRANSACTION" + this->m_isolationLevel : "SAVEPOINT " + _trans;

	res = sqlite3_exec(m_pDatabase, query.c_str(), 0, 0, 0);
    if (res == SQLITE_FULL || res == SQLITE_ERROR || res == SQLITE_NOMEM)
    {
        throw sqlite3_errmsg(this->m_pDatabase);
    }
}

void DbTransaction::Commit(std::string _trans)
{
	std::string query;
	int res;

	query = (_trans.empty()) ? "COMMIT TRANSACTION" : "RELEASE SAVEPOINT " + _trans;

	do
	{
		res = sqlite3_exec(m_pDatabase, query.c_str(), 0, 0, 0);

		if (res == SQLITE_FULL || res == SQLITE_IOERR || res == SQLITE_NOMEM)
		{
			this->Rollback(_trans);
			break;
		}

	} while (res == SQLITE_BUSY);

	assert(res != SQLITE_FULL && res != SQLITE_IOERR && res != SQLITE_NOMEM && res!= SQLITE_BUSY);

}

void DbTransaction::Rollback(std::string _trans)
{
	std::string query;
    int res;

	query = (_trans.empty()) ? "ROLLBACK TRANSACTION" : "ROLLBACK TO SAVEPOINT " + _trans;

    do
    {
        res = sqlite3_exec(m_pDatabase, query.c_str(), 0, 0, 0);

        if (res == SQLITE_FULL || res == SQLITE_IOERR || res == SQLITE_NOMEM)
        {
            this->Rollback(_trans);
            break;
        }

    } while (res == SQLITE_BUSY);

    assert(res != SQLITE_FULL && res != SQLITE_IOERR && res != SQLITE_NOMEM && res != SQLITE_BUSY);
}