#ifndef _SQLITE3_HELPER_HPP_
    #define _SQLITE3_HELPER_HPP_

#pragma once
#include "DbJournalMode.hpp"

#include "sqlite/sqlite3.h"

#include <iostream>
#include <string>

namespace
{
    static inline void Replace(const std::string& _key, const std::string& _val, std::string& _orig)
    {
        size_t pos = 0;
        while ((pos = _orig.find(_key, pos)) != std::string::npos)
        {
            _orig.replace(pos, _key.length(), _val);
            pos += _val.length();
        }

        if (pos == 0)
        {
            throw "Key not found!";
        }
    }

    static inline void ReplaceWithLiteral(const std::string& _key, const std::string& _val, std::string& _orig)
    {
        return Replace(_key, "'" + _val + "'", _orig);
    }
}

static int c_callback(void* param, int argc, char** argv, char** azColName)
{
    int index = 0;
    while (index < argc)
    {
        std::cerr << azColName[index] << "=" << argv[index] ? argv[index] : "NULL \n";

        ++index;
    }

    return 0;
}

static inline void EnableForeignKeyConstraint(sqlite3*_pDb)
{
    auto query = std::string( "PRAGMA foreign_keys=ON;" );

    auto res = sqlite3_exec(_pDb, query.c_str(), 0, 0, nullptr);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = sqlite3_errmsg(_pDb);
        throw err;
    }
}

static inline void SetJournalMode(sqlite3* _pDb, DbJournalMode journalMode)
{
    std::string mode;

    switch (journalMode)
    {
    case JOURNAL_MODE_DELETE: { mode = "DELETE"; break; }
    case JOURNAL_MODE_TRUNCATE: { mode = "TRUNCATE"; break; }
    case JOURNAL_MODE_PERSIST: { mode = "PERSIST"; break; }
    case JOURNAL_MODE_MEMORY: { mode = "MEMORY"; break; }
    case JOURNAL_MODE_WAL: { mode = "WAL"; break; }
    case JOURNAL_MODE_OFF: { mode = "OFF"; break; }
    default:
        throw "Invalid JournalMode!";
    }

    auto query = std::string("PRAGMA journal_mode={Mode};");
    ::Replace("{Mode}", mode, query);

    auto res = sqlite3_exec(_pDb, query.c_str(), 0, 0, nullptr);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = sqlite3_errmsg(_pDb);
        throw err;
    }
}

static inline void SetJournalSize(sqlite3* _pDb, size_t _size)
{
    auto size = std::to_string(_size);

    auto query = std::string("PRAGMA journal_size_limit={Size};");
    ::Replace("{Size}", size, query);

    auto res = sqlite3_exec(_pDb, query.c_str(), 0, 0, nullptr);
    if (res != SQLITE_OK && res != SQLITE_DONE)
    {
        auto err = sqlite3_errmsg(_pDb);
        throw err;
    }
}

static inline bool TableExists(sqlite3* _pDb, const std::string& _cTableName)
{
    std::string errMsg;

    sqlite3_stmt* pStmt;
    std::string query =
        "SELECT 1"
        " FROM sqlite_master"
        " WHERE type='table'"
        "  AND name=?;";

    auto res = sqlite3_prepare_v2(_pDb, query.c_str(), -1, &pStmt, nullptr);
    if (res != SQLITE_OK) { throw std::string(sqlite3_errmsg(_pDb)); }

    res = sqlite3_bind_text(pStmt, 1, _cTableName.c_str(), -1, SQLITE_TRANSIENT);
    if (res != SQLITE_OK)
    {
        errMsg = std::string(sqlite3_errmsg(_pDb));
        sqlite3_finalize(pStmt);
        throw errMsg;
    }

    res = sqlite3_step(pStmt);
    if (res != SQLITE_ROW && res != SQLITE_DONE)
    {
        errMsg = std::string(sqlite3_errmsg(_pDb));
        sqlite3_finalize(pStmt);
        throw errMsg;
    }

    if (res == SQLITE_DONE)
    {
        errMsg = "Table not found";
        sqlite3_finalize(pStmt);
        //throw errMsg;
        return false;
    }

    sqlite3_finalize(pStmt);
    return true;
}

#endif _SQLITE3_HELPER_HPP_
