#ifndef _APPEARANCE_REPOSITORY_HPP
    #define _APPEARANCE_REPOSITORY_HPP

#pragma once
#include "DbRepository.hpp"

#include "../Common.hpp"
#include "../Components/Appearance.hpp"
#include "../Components/Persistence/Appearance.hpp"
#include "../Utilities/Macros.hpp"

#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <string>
#include <vector>

using namespace Components;

class AppearanceRepository : public DbRepository<Appearance>
{
    CLASS_TYPE(AppearanceRepository);

public:

    explicit AppearanceRepository(IDbConnection* _pConnection);

    ~AppearanceRepository(void);

    void DeleteById(uint64_t _id);

    std::vector<Appearance> FindByEntityId(uint64_t _entityId);

    Appearance FindById(uint64_t _id);

    std::vector<Appearance> FindByName(const std::string& _name);

    Appearance Save(const Appearance& _comp);

    Appearance SaveDeferred(const Appearance& _comp);

    void Update(void);

protected:

    DbReader<Persistence::Appearance>* ExecuteReader(const std::string& _query);

    std::vector<Persistence::Appearance> Find(const std::string& _query, bool _single = false);

    Persistence::Appearance Insert(const Persistence::Appearance& _comp);

    static inline bool Map(DbReader<Persistence::Appearance>* _pReader, sqlite3_stmt* _pStmt, Persistence::Appearance& _result);

    Persistence::Appearance Update(const Persistence::Appearance& _comp);

private:

    static const std::string Query_DeleteComponentById;

    static const std::string Query_DeleteAppearanceByComponentId;

    static const std::string Query_FindByEntityId;

    static const std::string Query_FindById;

    static const std::string Query_FindByName;

    static const std::string Query_InsertComponent;

    static const std::string Query_InsertAppearance;

    static const std::string Query_UpdateComponent;

    static const std::string Query_UpdateAppearance;

};

bool AppearanceRepository::Map(DbReader<Persistence::Appearance>* _pReader, sqlite3_stmt* _pStmt, Persistence::Appearance& _result)
{
    auto id = ((uint64_t)sqlite3_column_int64(_pStmt, 0));
    auto name = ((char*)sqlite3_column_text(_pStmt, 1));
    auto entityId = ((uint64_t)sqlite3_column_int64(_pStmt, 2));
    auto modelPath = ((char*)sqlite3_column_text(_pStmt, 3));

    _result = Persistence::Appearance();
    _result.nId = _result.nComponentId = id;
    _result.nEntityId = entityId;
    _result.cName = name;
    _result.cModelPath = modelPath;

    return true;
}

#endif _APPEARANCE_REPOSITORY_HPP