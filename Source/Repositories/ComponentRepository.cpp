
#pragma once
#include "ComponentRepository.hpp"

#include "../Common.hpp"
#include "../Components/Component.hpp"
#include "../Components/Persistence/Component.hpp"
#include "../Mapping/Inbound/ComponentToComponentConverter.hpp"
#include "../Mapping/Outbound/ComponentToComponentConverter.hpp"
#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbQuery.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <memory>
#include <string>
#include <vector>

using namespace Components;

const std::string ComponentRepository::Query_FindByEntityId = std::string
(
    "SELECT [Id], [Name], [EntityId]"
    " FROM [Component]"
    " WHERE [EntityId] = {EntityId};"
);

const std::string ComponentRepository::Query_DeleteComponentById = std::string(
    "DELETE FROM [Component]"
    " WHERE [Id] = {Id};"
);

const std::string ComponentRepository::Query_FindById = std::string
(
    "SELECT [Id], [Name], [EntityId]"
    " FROM [Component]"
    " WHERE [Id] = {Id};"
);

const std::string ComponentRepository::Query_FindByName = std::string
(
    "SELECT [Id], [Name], [EntityId]"
    " FROM [Component]"
    " WHERE [Name] = {Name};"
);

const std::string ComponentRepository::Query_InsertComponent = std::string
(
    "INSERT INTO [Component]"
    "([Name], [EntityId]) VALUES"
    "({Name}, {EntityId});"
);

const std::string ComponentRepository::Query_UpdateComponent = std::string
(
    "UPDATE [Component] SET"
    " [EntityId] = {EntityId},"
    " [Name] = {Name}"
    " WHERE [Id] = {Id};"
);

ComponentRepository::ComponentRepository(IDbConnection* _pConnection)
    : DbRepository<Component>(_pConnection) { }

ComponentRepository::~ComponentRepository(void) { }

void ComponentRepository::DeleteById(uint64_t _id)
{
    auto deleteQuery = Query_DeleteComponentById;

    Replace("{Id}", std::to_string(_id), deleteQuery);

    ExecuteNonQuery(deleteQuery);
}

DbReader<Persistence::Component>* ComponentRepository::ExecuteReader(const std::string& _query)
{
    m_pCurrentCommand = this->m_pConnection->CreateCommand(new DbQuery(_query));

    return this->m_pCurrentCommand->ExecuteReader<Persistence::Component>();
}

std::vector<Component> ComponentRepository::FindByEntityId(uint64_t _entityId)
{
    auto findQuery = Query_FindByEntityId;

    Replace("{EntityId}", std::to_string(_entityId), findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Component, Component>(res);
}

Component ComponentRepository::FindById(uint64_t _id)
{
    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_id), findQuery);

    auto res = this->Find(findQuery, true).front();
    return TypeConverter::Convert<Persistence::Component, Component>(res);
}

std::vector<Component> ComponentRepository::FindByName(const std::string& _name)
{
    auto findQuery = Query_FindByName;

    ReplaceWithLiteral("{Name}", _name, findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Component, Component>(res);
}

std::vector<Persistence::Component> ComponentRepository::Find(const std::string& _query, bool _single)
{
    auto pReader = this->ExecuteReader(_query);

    auto res = std::vector<Persistence::Component>();
    while (pReader->Read(&ComponentRepository::Map))
    {
        res.push_back(pReader->Result());

        if (_single) { break; }
    }

    delete pReader;
    pReader = nullptr;

    delete this->m_pCurrentCommand;
    this->m_pCurrentCommand = nullptr;

    return res;
}

Persistence::Component ComponentRepository::Insert(const Persistence::Component& _comp)
{
    auto insertQuery = Query_InsertComponent;

    ReplaceWithLiteral("{Name}", _comp.cName, insertQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), insertQuery);

    this->ExecuteNonQuery(insertQuery);
    auto id = this->m_pConnection->LastInsertRowId();

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(id), findQuery);

    return this->Find(findQuery, true).front();
}

Persistence::Component ComponentRepository::Update(const Persistence::Component& _comp)
{
    auto updateQuery = Query_UpdateComponent;

    Replace("{Id}", std::to_string(_comp.nId), updateQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), updateQuery);
    ReplaceWithLiteral("{Name}", _comp.cName, updateQuery);

    this->ExecuteNonQuery(updateQuery);

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_comp.nId), findQuery);

    return this->Find(findQuery, true).front();
}

Component ComponentRepository::Save(const Component& _comp)
{
    Persistence::Component current;
    Persistence::Component original;
    uint64_t compId = _comp.nId;

    current = TypeConverter::Convert<Component, Persistence::Component>(_comp);

    if (compId <= 0)
    {
        current = this->Insert(current);
    }
    else
    {
        auto findQuery = Query_FindById;
        Replace("{Id}", std::to_string(compId), findQuery);

        // < Fetch the original and merge.
        original = this->Find(findQuery, true).front();
        current = current.Merge(original);

        current = this->Update(current);
    }

    return TypeConverter::Convert<Persistence::Component, Component>(current);
}