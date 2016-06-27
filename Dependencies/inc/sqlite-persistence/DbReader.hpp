#ifndef _DBREADER_HPP_
	#define _DBREADER_HPP_

#pragma once
#include "ClassType.hpp"
#include "DbCommand.hpp"

#include "sqlite/sqlite3.h"

#include <functional>
#include <string>
#include <vector>

template <typename T>
class DbReader
{
    CLASS_TYPE(DbReader);

public:

    explicit DbReader(DbCommand* const _pCommand);
    ~DbReader(void);

    bool Read(std::function<bool(DbReader<T>*, sqlite3_stmt*, T&)> _func);

    const unsigned long Columns(void);
    const T Result(void);

protected:

    bool Prepare(void);

private:

    DbCommand* const m_pCommand;

    T m_result;

    int m_nColumns;

}; // < end class.

template <typename T>
DbReader<T>::DbReader(DbCommand* const _pCommand)
    : m_pCommand(_pCommand), m_nColumns(sqlite3_column_count(_pCommand->getStmt())) { }

template <typename T>
DbReader<T>::~DbReader(void) { }

template <typename T>
const T DbReader<T>::Result(void) { return m_result; }

template <typename T>
const unsigned long DbReader<T>::Columns(void) { return this->m_nColumns; }

template <typename T>
bool DbReader<T>::Prepare(void)
{
    auto res = sqlite3_step(this->m_pCommand->getStmt());
    if (res != SQLITE_ROW && res != SQLITE_DONE)
    {
        auto err = m_pCommand->Connection()->ErrorMessage();
        if (err != "not an error")
        {
            this->m_pCommand->FinalizeStmt();
            throw err;
        }

        this->m_pCommand->FinalizeStmt();

        // < I am unsure if it is possible to get here.
        return false;
    }

    if (res == SQLITE_DONE || this->m_nColumns <= 0)
    {
        // < Nothing to report.
        this->m_pCommand->FinalizeStmt();
        return false;
    }

    return true;
}

template <typename T>
bool DbReader<T>::Read(std::function<bool(DbReader<T>*, sqlite3_stmt*, T&)> _func)
{
    if (!this->Prepare()) { return false; }

    return _func(this, this->m_pCommand->getStmt(), this->m_result);
};

#endif _DBREADER_HPP_