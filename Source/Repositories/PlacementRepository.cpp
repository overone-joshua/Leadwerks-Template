
#pragma once
#include "PlacementRepository.hpp"

#include "../Common.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Persistence/Placement.hpp"
#include "../Mapping/Inbound/PlacementToPlacementConverter.hpp"
#include "../Mapping/Outbound/PlacementToPlacementConverter.hpp"
#include "../Utilities/StringExtensions.hpp"

#include <sqlite-persistence/DbCommand.hpp>
#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbQuery.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <string>
#include <vector>

using namespace Components;

const std::string PlacementRepository::Query_FindByEntityId = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId],"
    " p.[ForwardX], p.[ForwardY], p.[ForwardZ],"
    " p.[RightX], p.[RightY], p.[RightZ],"
    " p.[TranslationX], p.[TranslationY], p.[TranslationZ],"
    " p.[RotationX], p.[RotationY], p.[RotationZ],"
    " p.[VelocityX], p.[VelocityY], p.[VelocityZ],"
    " p.[SpinX], p.[SpinY], p.[SpinZ],"
    " p.[Friction], p.[Visible], p.[Ghost],"
    " p.[IgnoreCollision], p.[TouchingGround]"
    " FROM [Component] AS c"
    " JOIN [Placement] AS p"
    "  ON p.[ComponentId] = c.[Id]"
    " WHERE c.[EntityId] = {EntityId};"
);

const std::string PlacementRepository::Query_DeleteComponentById = std::string(
    "DELETE FROM [Component]"
    " WHERE [Id] = {Id};"
);

const std::string PlacementRepository::Query_DeletePlacementByComponentId = std::string
(
    "DELETE FROM [Placement]"
    " WHERE [ComponentId] = {ComponentId};"
);

const std::string PlacementRepository::Query_FindById = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId],"
    " p.[ForwardX], p.[ForwardY], p.[ForwardZ],"
    " p.[RightX], p.[RightY], p.[RightZ],"
    " p.[TranslationX], p.[TranslationY], p.[TranslationZ],"
    " p.[RotationX], p.[RotationY], p.[RotationZ],"
    " p.[VelocityX], p.[VelocityY], p.[VelocityZ],"
    " p.[SpinX], p.[SpinY], p.[SpinZ],"
    " p.[Friction], p.[Visible], p.[Ghost],"
    " p.[IgnoreCollision], p.[TouchingGround]"
    " FROM [Component] AS c"
    " JOIN [Placement] AS p"
    "  ON p.[ComponentId] = c.[Id]"
    " WHERE c.[Id] = {Id};"
);

const std::string PlacementRepository::Query_FindByName = std::string
(
    "SELECT c.[Id], c.[Name], c.[EntityId],"
    " p.[ForwardX], p.[ForwardY], p.[ForwardZ],"
    " p.[RightX], p.[RightY], p.[RightZ],"
    " p.[TranslationX], p.[TranslationY], p.[TranslationZ],"
    " p.[RotationX], p.[RotationY], p.[RotationZ],"
    " p.[VelocityX], p.[VelocityY], p.[VelocityZ],"
    " p.[SpinX], p.[SpinY], p.[SpinZ],"
    " p.[Friction], p.[Visible], p.[Ghost],"
    " p.[IgnoreCollision], p.[TouchingGround]"
    " FROM [Component] AS c"
    " JOIN [Placement] AS p"
    "  ON p.[ComponentId] = c.[Id]"
    " WHERE c.[Name] = {Name};"
);

const std::string PlacementRepository::Query_InsertComponent = std::string
(
    "INSERT INTO [Component]"
    " ([Name], [EntityId]) VALUES"
    " ({Name}, {EntityId});"
);

const std::string PlacementRepository::Query_InsertPlacement = std::string
(
    "INSERT INTO [Placement]"
    " ([ComponentId], [ForwardX], [ForwardY], [ForwardZ],"
    " [RightX], [RightY], [RightZ], [TranslationX], [TranslationY],"
    " [TranslationZ], [RotationX], [RotationY], [RotationZ],"
    " [VelocityX], [VelocityY], [VelocityZ], [SpinX], [SpinY],"
    " [SpinZ], [Friction], [Visible], [Ghost], [IgnoreCollision],"
    " [TouchingGround]) VALUES"
    " ({ComponentId}, {ForwardX}, {ForwardY}, {ForwardZ},"
    " {RightX}, {RightY}, {RightZ}, {TranslationX}, {TranslationY},"
    " {TranslationZ}, {RotationX}, {RotationY}, {RotationZ},"
    " {VelocityX}, {VelocityY}, {VelocityZ}, {SpinX}, {SpinY},"
    " {SpinZ}, {Friction}, {Visible}, {Ghost}, {IgnoreCollision},"
    " {TouchingGround});"
);

const std::string PlacementRepository::Query_UpdateComponent = std::string
(
    "UPDATE [Component] SET"
    " [EntityId] = {EntityId},"
    " [Name] = {Name}"
    " WHERE [Id] = {Id};"
);

const std::string PlacementRepository::Query_UpdatePlacement = std::string
(
    "UPDATE [Placement] SET"
    " ComponentId = {ComponentId},"
    " ForwardX = {ForwardX}, "
    " ForwardY = {ForwardY},"
    " forwardZ = {ForwardZ},"
    " RightX = {RightX},"
    " RightY = {RightY},"
    " RightZ = {RightZ},"
    " TranslationX = {TranslationX},"
    " TranslationY = {TranslationY},"
    " TranslationZ = {TranslationZ},"
    " RotationX = {RotationX},"
    " RotationY = {RotationY},"
    " RotationZ = {RotationZ},"
    " VelocityX = {VelocityX},"
    " VelocityY = {VelocityY},"
    " VelocityZ = {VelocityZ},"
    " SpinX = {SpinX},"
    " SpinY = {SpinY},"
    " SpinZ = {SpinZ},"
    " Friction = {Friction},"
    " Visible = {Visible},"
    " Ghost = {Ghost},"
    " IgnoreCollision = {IgnoreCollision},"
    " TouchingGround = {TouchingGround}"
    " WHERE [ComponentId] = {ComponentId};"
);

PlacementRepository::PlacementRepository(IDbConnection* _pConnection)
    : DbRepository<Placement>(_pConnection) { }

PlacementRepository::~PlacementRepository(void) { }

void PlacementRepository::DeleteById(uint64_t _id)
{
    auto compId = std::to_string(_id);

    auto deleteQuery = Query_DeleteComponentById;
    Replace("{Id}", compId, deleteQuery);

    ExecuteNonQuery(deleteQuery);

    deleteQuery = Query_DeletePlacementByComponentId;
    Replace("{ComponentId}", compId, deleteQuery);

    this->m_pCurrentCommand->setQueryText(deleteQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();
}

DbReader<Persistence::Placement>* PlacementRepository::ExecuteReader(const std::string& _query)
{
    m_pCurrentCommand = this->m_pConnection->CreateCommand(new DbQuery(_query));

    return this->m_pCurrentCommand->ExecuteReader<Persistence::Placement>();
}

std::vector<Placement> PlacementRepository::FindByEntityId(uint64_t _entityId)
{
    std::string findQuery = Query_FindByEntityId;

    Replace("{EntityId}", std::to_string(_entityId), findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Placement, Placement>(res);
}

Placement PlacementRepository::FindById(uint64_t _id)
{
    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_id), findQuery);

    auto res = this->Find(findQuery, true).front();
    return TypeConverter::Convert<Persistence::Placement, Placement>(res);
}

std::vector<Placement> PlacementRepository::FindByName(const std::string& _name)
{
    auto findQuery = Query_FindByName;

    ReplaceWithLiteral("{Name}", _name, findQuery);

    auto res = this->Find(findQuery, false);
    return TypeConverter::ConvertAll<Persistence::Placement, Placement>(res);
}

std::vector<Persistence::Placement> PlacementRepository::Find(const std::string& _query, bool _single)
{
    auto pReader = this->ExecuteReader(_query);

    auto res = std::vector<Persistence::Placement>();
    while (pReader->Read(&PlacementRepository::Map))
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

Persistence::Placement PlacementRepository::Insert(const Persistence::Placement& _comp)
{
    auto insertQuery = Query_InsertComponent;

    ReplaceWithLiteral("{Name}", _comp.cName, insertQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), insertQuery);

    this->ExecuteNonQuery(insertQuery);
    auto id = this->m_pConnection->LastInsertRowId();

    insertQuery = Query_InsertPlacement;

    // < Copy the component's id to satisfy the FK
    // * constraint on table Placement.
    Replace("{ComponentId}", std::to_string(id), insertQuery);
    Replace("{ForwardX}", std::to_string(_comp.vForward.x), insertQuery);
    Replace("{ForwardY}", std::to_string(_comp.vForward.y), insertQuery);
    Replace("{ForwardZ}", std::to_string(_comp.vForward.z), insertQuery);
    Replace("{RightX}", std::to_string(_comp.vRight.x), insertQuery);
    Replace("{RightY}", std::to_string(_comp.vRight.y), insertQuery);
    Replace("{RightZ}", std::to_string(_comp.vRight.z), insertQuery);
    Replace("{TranslationX}", std::to_string(_comp.vTranslation.x), insertQuery);
    Replace("{TranslationY}", std::to_string(_comp.vTranslation.y), insertQuery);
    Replace("{TranslationZ}", std::to_string(_comp.vTranslation.z), insertQuery);
    Replace("{RotationX}", std::to_string(_comp.vRotation.x), insertQuery);
    Replace("{RotationY}", std::to_string(_comp.vRotation.y), insertQuery);
    Replace("{RotationZ}", std::to_string(_comp.vRotation.z), insertQuery);
    Replace("{VelocityX}", std::to_string(_comp.vVelocity.x), insertQuery);
    Replace("{VelocityY}", std::to_string(_comp.vVelocity.y), insertQuery);
    Replace("{VelocityZ}", std::to_string(_comp.vVelocity.z), insertQuery);
    Replace("{SpinX}", std::to_string(_comp.vSpin.x), insertQuery);
    Replace("{SpinY}", std::to_string(_comp.vSpin.y), insertQuery);
    Replace("{SpinZ}", std::to_string(_comp.vSpin.z), insertQuery);
    Replace("{Friction}", std::to_string(_comp.nFriction), insertQuery);
    Replace("{Visible}", std::to_string(_comp.bVisible), insertQuery);
    Replace("{Ghost}", std::to_string(_comp.bGhost), insertQuery);
    Replace("{IgnoreCollision}", std::to_string(_comp.bIgnoreCollision), insertQuery);
    Replace("{TouchingGround}", std::to_string(_comp.bTouchingGround), insertQuery);

    this->m_pCurrentCommand->setQueryText(insertQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(id), findQuery);

    return this->Find(findQuery, true).front();
}

Persistence::Placement PlacementRepository::Update(const Persistence::Placement& _comp)
{
    auto updateQuery = Query_UpdateComponent;

    Replace("{Id}", std::to_string(_comp.nId), updateQuery);
    Replace("{EntityId}", std::to_string(_comp.nEntityId), updateQuery);
    ReplaceWithLiteral("{Name}", _comp.cName, updateQuery);

    this->ExecuteNonQuery(updateQuery);

    updateQuery = Query_UpdatePlacement;

    Replace("{ComponentId}", std::to_string(_comp.nId), updateQuery);
    Replace("{ForwardX}", std::to_string(_comp.vForward.x), updateQuery);
    Replace("{ForwardY}", std::to_string(_comp.vForward.y), updateQuery);
    Replace("{ForwardZ}", std::to_string(_comp.vForward.z), updateQuery);
    Replace("{RightX}", std::to_string(_comp.vRight.x), updateQuery);
    Replace("{RightY}", std::to_string(_comp.vRight.y), updateQuery);
    Replace("{RightZ}", std::to_string(_comp.vRight.z), updateQuery);
    Replace("{TranslationX}", std::to_string(_comp.vTranslation.x), updateQuery);
    Replace("{TranslationY}", std::to_string(_comp.vTranslation.y), updateQuery);
    Replace("{TranslationZ}", std::to_string(_comp.vTranslation.z), updateQuery);
    Replace("{RotationX}", std::to_string(_comp.vRotation.x), updateQuery);
    Replace("{RotationY}", std::to_string(_comp.vRotation.y), updateQuery);
    Replace("{RotationZ}", std::to_string(_comp.vRotation.z), updateQuery);
    Replace("{VelocityX}", std::to_string(_comp.vVelocity.x), updateQuery);
    Replace("{VelocityY}", std::to_string(_comp.vVelocity.y), updateQuery);
    Replace("{VelocityZ}", std::to_string(_comp.vVelocity.z), updateQuery);
    Replace("{SpinX}", std::to_string(_comp.vSpin.x), updateQuery);
    Replace("{SpinY}", std::to_string(_comp.vSpin.y), updateQuery);
    Replace("{SpinZ}", std::to_string(_comp.vSpin.z), updateQuery);
    Replace("{Friction}", std::to_string(_comp.nFriction), updateQuery);
    Replace("{Visible}", std::to_string(_comp.bVisible), updateQuery);
    Replace("{Ghost}", std::to_string(_comp.bGhost), updateQuery);
    Replace("{IgnoreCollision}", std::to_string(_comp.bIgnoreCollision), updateQuery);
    Replace("{TouchingGround}", std::to_string(_comp.bTouchingGround), updateQuery);

    this->m_pCurrentCommand->setQueryText(updateQuery);
    this->m_pCurrentCommand->ExecuteNonQuery();

    auto findQuery = Query_FindById;

    Replace("{Id}", std::to_string(_comp.nId), findQuery);

    return this->Find(findQuery, true).front();
}

Placement PlacementRepository::Save(const Placement& _comp)
{
    Persistence::Placement current;
    Persistence::Placement original;
    uint64_t compId = _comp.nId;

    current = TypeConverter::Convert<Placement, Persistence::Placement>(_comp);

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

    return TypeConverter::Convert<Persistence::Placement, Placement>(current);
}