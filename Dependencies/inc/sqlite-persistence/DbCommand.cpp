#pragma once
#include "DbCommand.hpp"

#include "DbConnection.hpp"
#include "DbReader.hpp"
#include "IDbConnection.hpp"
#include "IDbQuery.hpp"
#include "IDbTransaction.hpp"
#include "Sqlite3Helper.hpp"

#include "sqlite/sqlite3.h"

#include <iostream>
#include <cassert>
#include <string>

DbCommand::DbCommand(IDbQuery* const _pQuery, IDbConnection* const _pConnection, IDbTransaction* const _pTransaction)
    : m_pQuery(_pQuery), m_pConnection(_pConnection), m_pTransaction(_pTransaction), m_pStatement(nullptr)
    , m_bPrepared(false) { }

DbCommand::~DbCommand(void)
{
    if (this->m_pStatement != nullptr)
    {
        // < Just in case.
        this->FinalizeStmt();

        this->m_bPrepared = false;
    }
}

IDbConnection* const DbCommand::Connection(void) { return this->m_pConnection; }

IDbQuery* const DbCommand::getQuery(void) { return this->m_pQuery; }

sqlite3_stmt* DbCommand::getStmt(void) { return this->m_pStatement; }

const bool DbCommand::isPrepared(void) { return this->m_bPrepared; }

void DbCommand::FinalizeStmt(void)
{
    auto res = sqlite3_finalize(this->m_pStatement);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = this->m_pConnection->ErrorMessage();
        if (err != "not an error")
        {
            throw err;
        }
    }

    this->m_pStatement = nullptr;
}

const std::string DbCommand::getErr(void) { return this->m_pConnection->ErrorMessage(); }

void DbCommand::setQueryText(const std::string& _query)
{
    if (this->m_bPrepared)
    {
        FinalizeStmt();
        this->m_bPrepared = false;  // < This will force the stmt to be recompiled.
    }
    this->m_pQuery->Set(_query);
}

void DbCommand::Cancel(void)
{
	if (!m_pConnection->HasAnyConnectionState(CONNECTION_CLOSING | CONNECTION_CLOSED))
	{
		sqlite3_interrupt(m_pConnection->Database());
	}
}

void DbCommand::ExecuteNonQuery(void)
{
    if (!this->m_bPrepared) { this->Prepare(); }

    auto res = sqlite3_exec(this->m_pConnection->Database(), this->m_pQuery->Text().c_str(), 0, 0, nullptr);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = this->m_pConnection->ErrorMessage();
        if (err != "not an error")
        {
            this->FinalizeStmt();
            throw err;
        }
    }

    this->FinalizeStmt();
    this->m_bPrepared = false;
}

sqlite3_stmt* const  DbCommand::Prepare(void)
{
    if (this->m_pConnection->HasConnectionState(CONNECTION_CLOSED)) { this->m_pConnection->Open(); }

    // < No need to prepare the statement a second time.
    if (this->m_bPrepared) { return this->m_pStatement; }

    auto res = sqlite3_prepare_v2((m_pConnection->Database()), m_pQuery->Text().c_str(), -1, &this->m_pStatement, 0);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = this->m_pConnection->ErrorMessage();
        if (err != "not an error")
        {
            this->FinalizeStmt();
            throw err;
        }
    }

    this->m_bPrepared = true;
    return this->m_pStatement;
}