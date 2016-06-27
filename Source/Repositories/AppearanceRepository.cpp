
#pragma once
#include "AppearanceRepository.hpp"

#include "../Common.hpp"
#include "../Components/Appearance.hpp"
#include "../Components/Persistence/Appearance.hpp"
#include "../Mapping/Inbound/AppearanceToAppearanceConverter.hpp"
#include "../Mapping/Outbound/AppearanceToAppearanceConverter.hpp"
#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbQuery.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <string>
#include <vector>

using namespace Components;

const std::string AppearanceRepository::Query_FindByEntityId = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId], a.[ModelPath]"
    " FROM [Component] AS c"
    " JOIN [Appearance] AS a"
    "  ON a.[ComponentId] = c.[Id]"
    " WHERE c.[EntityId] = {EntityId};"
);

const std::string AppearanceRepository::Query_DeleteComponentById = std::string(
    "DELETE FROM [Component]"
    " WHERE [Id] = {Id};"
);

const std::string AppearanceRepository::Query_DeleteAppearanceByComponentId = std::string
(
    "DELETE FROM [Appearance]"
    " WHERE [ComponentId] = {ComponentId};"
);

const std::string AppearanceRepository::Query_FindById = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId], a.[ModelPath]"
    " FROM [Component] AS c"
    " JOIN [Appearance] AS a"
    "  ON a.[ComponentId] = c.[Id]"
    " WHERE c.[Id] = {Id};"
);

const std::string AppearanceRepository::Query_FindByName = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId], a.[ModelPath]"
    " FROM [Component] AS c"
    " JOIN [Appearance] AS a"
    "  ON a.[ComponentId] = c.[Id]"
    " WHERE c.[Name] = {Name};"
);

const std::string AppearanceRepository::Query_InsertComponent = std::string
(
    "INSERT INTO [Component]"
    " ([Name], [EntityId]) VALUES"
    " ({Name}, {EntityId});"
);

const std::string AppearanceRepository::Query_InsertAppearance = std::string
(
    "INSERT INTO [Appearance]"
    " ([ComponentId], [ModelPath]) VALUES"
    " ({ComponentId}, {ModelPath});"
);

const std::string AppearanceRepository::Query_UpdateComponent = std::string
(
    "UPDATE [Component] SET"
    " [EntityId] = {EntityId},"
    " [Name] = {Name}"
    " WHERE [Id] = {Id};"
);

const std::string AppearanceRepository::Query_UpdateAppearance = std::string
(
    "UPDATE [Appearance] SET"
    " [ModelPath] = {ModelPath}"
    " WHERE [ComponentId] = {ComponentId};"
);

AppearanceRepository::AppearanceRepository(IDbConnection* _pConnection)
    : DbRepository<Appearance>(_pConnection) { }

AppearanceRepository::~AppearanceRepository(void) { }

void AppearanceRepository::DeleteById(uint64_t _id)
{
    auto compId = std::to_string(_id);

    auto deleteQuery = Query_DeleteComponentById;
    Replace("{Id}", compId, deleteQuery);

    ExecuteNonQuery(deleteQuery);

    deleteQuery = Query_DeleteAppearanceByComponentId;
    Replace("{ComponentId}", compId, deleteQuery);

    this->m_pCurrentCommand->setQueryText(deleteQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();
}

DbReader<Persistence::Appearance>* AppearanceRepository::ExecuteReader(const std::string& _query)
{
    m_pCurrentCommand = this->m_pConnection->CreateCommand(new DbQuery(_query));

    return this->m_pCurrentCommand->ExecuteReader<Persistence::Appearance>();
}

std::vector<Appearance> AppearanceRepository::FindByEntityId(uint64_t _entityId)
{
    auto findQuery = Query_FindByEntityId;

    Replace("{EntityId}", std::to_string(_entityId), findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Appearance, Appearance>(res);
}

Appearance AppearanceRepository::FindById(uint64_t _id)
{
    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_id), findQuery);

    auto res = this->Find(findQuery, true).front();
    return TypeConverter::Convert<Persistence::Appearance, Appearance>(res);
}

std::vector<Appearance> AppearanceRepository::FindByName(const std::string& _name)
{
    auto findQuery = Query_FindByName;

    ReplaceWithLiteral("{Name}", _name, findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Appearance, Appearance>(res);
}

std::vector<Persistence::Appearance> AppearanceRepository::Find(const std::string& _query, bool _single)
{
    auto pReader = this->ExecuteReader(_query);

    auto res = std::vector<Persistence::Appearance>();
    while (pReader->Read(&AppearanceRepository::Map))
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

Persistence::Appearance AppearanceRepository::Insert(const Persistence::Appearance& _comp)
{
    auto insertQuery = Query_InsertComponent;

    ReplaceWithLiteral("{Name}", _comp.cName, insertQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), insertQuery);

    this->ExecuteNonQuery(insertQuery);
    auto id = this->m_pConnection->LastInsertRowId();

    insertQuery = Query_InsertAppearance;

    // < Copy the component's id to satisfy the FK
    // * constraint on table Appearance.
    Replace("{ComponentId}", std::to_string(id), insertQuery);
    ReplaceWithLiteral("{ModelPath}", _comp.cModelPath, insertQuery);

    this->m_pCurrentCommand->setQueryText(insertQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(id), findQuery);

    return this->Find(findQuery, true).front();
}

Persistence::Appearance AppearanceRepository::Update(const Persistence::Appearance& _comp)
{
    auto updateQuery = Query_UpdateComponent;

    Replace("{Id}", std::to_string(_comp.nId), updateQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), updateQuery);
    ReplaceWithLiteral("{Name}", _comp.cName, updateQuery);

    this->ExecuteNonQuery(updateQuery);

    updateQuery = Query_UpdateAppearance;

    Replace("{ComponentId}", std::to_string(_comp.nId), updateQuery);
    ReplaceWithLiteral("{ModelPath}", _comp.cModelPath, updateQuery);

    this->m_pCurrentCommand->setQueryText(updateQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_comp.nId), findQuery);

    return this->Find(findQuery, true).front();
}

Appearance AppearanceRepository::Save(const Appearance& _comp)
{
    Persistence::Appearance current;
    Persistence::Appearance original;
    uint64_t compId = _comp.nId;

    current = TypeConverter::Convert<Appearance, Persistence::Appearance>(_comp);

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

    return TypeConverter::Convert<Persistence::Appearance, Appearance>(current);
}