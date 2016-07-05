#ifndef _COMPONENT_REPOSITORY_HPP
    #define _COMPONENT_REPOSITORY_HPP

#pragma once
#include "DbRepository.hpp"

#include "../Common.hpp"
#include "../Components/Component.hpp"
#include "../Components/Persistence/Component.hpp"
#include "../Utilities/Macros.hpp"

#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <string>
#include <vector>

using namespace Components;

class ComponentRepository : public DbRepository<Component>
{
    CLASS_TYPE(ComponentRepository);

public:

    explicit ComponentRepository(IDbConnection* _pConnection);

    ~ComponentRepository(void);

    void DeleteById(uint64_t _id);

    std::vector<Component> FindByEntityId(uint64_t _entityId);

    Component FindById(uint64_t _id);

    std::vector<Component> FindByName(const std::string& _name);

    Component Save(const Component& _comp);

    Component SaveDeferred(const Component& _comp);

    void Update(void);

protected:

    DbReader<Persistence::Component>* ExecuteReader(const std::string& _query);

    std::vector<Persistence::Component> Find(const std::string& _query, bool _single = false);

    Persistence::Component Insert(const Persistence::Component& _comp);

    static inline bool Map(DbReader<Persistence::Component>* _pReader, sqlite3_stmt* _pStmt, Persistence::Component& _result);

    Persistence::Component Update(const Persistence::Component& _comp);

private:

    static const std::string Query_DeleteComponentById;

    static const std::string Query_FindByEntityId;

    static const std::string Query_FindById;

    static const std::string Query_FindByName;

    static const std::string Query_InsertComponent;

    static const std::string Query_UpdateComponent;

}; // < end class.

bool ComponentRepository::Map(DbReader<Persistence::Component>* _pReader, sqlite3_stmt* _pStmt, Persistence::Component& _result)
{
    auto id = ((uint64_t)sqlite3_column_int64(_pStmt, 0));
    auto name = ((char*)sqlite3_column_text(_pStmt, 1));
    auto entityId = ((uint64_t)sqlite3_column_int64(_pStmt, 2));

    _result = Persistence::Component();
    _result.nId = id;
    _result.nEntityId = entityId;
    _result.cName = name;

    return true;
}

#endif _COMPONENT_REPOSITORY_HPP
