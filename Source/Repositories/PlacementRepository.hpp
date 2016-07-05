#ifndef _PLACEMENT_REPOSITORY_HPP_
    #define _PLACEMENT_REPOSITORY_HPP_

#pragma once
#include "DbRepository.hpp"

#include "../Common.hpp"
#include "../Components/Placement.hpp"
#include "../Components/Persistence/Placement.hpp"
#include "../Utilities/Macros.hpp"

#include <sqlite-persistence/DbConnection.hpp>
#include <sqlite-persistence/DbReader.hpp>
#include <sqlite-persistence/sqlite/sqlite3.h>

#include <deque>
#include <string>
#include <vector>

using namespace Components;

// < TODO: Add CacheCollection support.
// * [X] Inserting a new component should add the component to the cache.
// * [X] Accessing a new component should add the component to the cache.
// * [ ] Components should be saved to the database in a deferred way.
class PlacementRepository : public DbRepository<Placement>
{

    CLASS_TYPE(PlacementRepository);

public:

    explicit PlacementRepository(IDbConnection* _pConnection);

    ~PlacementRepository(void);

    void DeleteById(uint64_t _id);

    std::vector<Placement> FindByEntityId(uint64_t _entityId);

    Placement FindById(uint64_t _id);

    std::vector<Placement> FindByName(const std::string& _name);

    Placement Save(const Placement& _comp);

    Placement SaveDeferred(const Placement& _comp);

    void Update(void);

protected:

    DbReader<Persistence::Placement>* ExecuteReader(const std::string& _query);

    std::vector<Persistence::Placement> Find(const std::string& _query, bool _single = false);

    Persistence::Placement Insert(const Persistence::Placement& _comp);

    static inline bool Map(DbReader<Persistence::Placement>* _pReader, sqlite3_stmt* _pStmt, Persistence::Placement& _result);

    void SaveDeferredAsync(void);

    Persistence::Placement Update(const Persistence::Placement& _comp);

private:

    std::deque<uint64_t> m_savingQueue;

    static const std::string Query_DeleteComponentById;

    static const std::string Query_DeletePlacementByComponentId;

    static const std::string Query_FindByEntityId;

    static const std::string Query_FindById;

    static const std::string Query_FindByName;

    static const std::string Query_InsertComponent;

    static const std::string Query_InsertPlacement;

    static const std::string Query_UpdateComponent;

    static const std::string Query_UpdatePlacement;

}; // < end class.

bool PlacementRepository::Map(DbReader<Persistence::Placement>* _pReader, sqlite3_stmt* _pStmt, Persistence::Placement& _result)
{
    auto id = ((uint64_t)sqlite3_column_int64(_pStmt, 0));
    auto name = ((char*)sqlite3_column_text(_pStmt, 1));
    auto entityId = ((uint64_t)sqlite3_column_int64(_pStmt, 2));

    auto forwardX = ((float)sqlite3_column_double(_pStmt, 3));
    auto forwardY = ((float)sqlite3_column_double(_pStmt, 4));
    auto forwardZ = ((float)sqlite3_column_double(_pStmt, 5));
    auto rightX = ((float)sqlite3_column_double(_pStmt, 6));
    auto rightY = ((float)sqlite3_column_double(_pStmt, 7));
    auto rightZ = ((float)sqlite3_column_double(_pStmt, 8));
    auto translationX = ((float)sqlite3_column_double(_pStmt, 9));
    auto translationY = ((float)sqlite3_column_double(_pStmt, 10));
    auto translationZ = ((float)sqlite3_column_double(_pStmt, 11));
    auto rotationX = ((float)sqlite3_column_double(_pStmt, 12));
    auto rotationY = ((float)sqlite3_column_double(_pStmt, 13));
    auto rotationZ = ((float)sqlite3_column_double(_pStmt, 14));
    auto velocityX = ((float)sqlite3_column_double(_pStmt, 15));
    auto velocityY = ((float)sqlite3_column_double(_pStmt, 16));
    auto velocityZ = ((float)sqlite3_column_double(_pStmt, 17));
    auto spinX = ((float)sqlite3_column_double(_pStmt, 18));
    auto spinY = ((float)sqlite3_column_double(_pStmt, 19));
    auto spinZ = ((float)sqlite3_column_double(_pStmt, 20));
    auto friction = ((float)sqlite3_column_double(_pStmt, 21));
    auto visible = (sqlite3_column_int(_pStmt, 22) == 1);
    auto ghost = (sqlite3_column_int(_pStmt, 23) == 1);
    auto ignoreCollision = (sqlite3_column_int(_pStmt, 24) == 1);
    auto touchingGround = (sqlite3_column_int(_pStmt, 25) == 1);

    _result = Persistence::Placement();
    _result.nId = _result.nComponentId = id;
    _result.nEntityId = entityId;
    _result.cName = name;

    _result.vForward = Leadwerks::Vec3(forwardX, forwardY, forwardZ);
    _result.vRight = Leadwerks::Vec3(rightX, rightY, rightZ);
    _result.vTranslation = Leadwerks::Vec3(translationX, translationY, translationZ);
    _result.vRotation = Leadwerks::Vec3(rotationX, rotationY, rotationZ);
    _result.vVelocity = Leadwerks::Vec3(velocityX, velocityY, velocityZ);
    _result.vSpin = Leadwerks::Vec3(spinX, spinY, spinZ);
    _result.nFriction = friction;
    _result.bVisible = visible;
    _result.bGhost = ghost;
    _result.bIgnoreCollision = ignoreCollision;
    _result.bTouchingGround = touchingGround;

    return true;
}

#endif _PLACEMENT_REPOSITORY_HPP_
