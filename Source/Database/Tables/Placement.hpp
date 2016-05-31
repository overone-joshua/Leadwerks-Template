#ifndef _PLACEMENT_COMPONENT_TABLE_HPP_
	#define _PLACEMENT_COMPONENT_TABLE_HPP_

#pragma once
#include "Leadwerks.h"
#include "../../Services/DatabaseController.hpp"
#include "Table.hpp"

#include "../../Components/Placement.hpp"
#include "../../Components/World.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace Database
{
	template <>
	void Table<Components::Placement>::CreateTable(IDatabaseController* const db)
	{
		DataTable tableDef;

		// < Primary key.
		Table::AddDefinition("Id", "INTEGER PRIMARY KEY", "NOT NULL", tableDef);

		// < Forward vector.
		Table::AddDefinition("ForwardX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("ForwardY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("ForwardZ", "INTEGER", "NOT NULL", tableDef);

		// < Right vector.
		Table::AddDefinition("RightX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("RightY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("RightZ", "INTEGER", "NOT NULL", tableDef);

		// < Translation vector.
		Table::AddDefinition("TranslationX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("TranslationY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("TranslationZ", "INTEGER", "NOT NULL", tableDef);

		// < Rotation vector.
		Table::AddDefinition("RotationX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("RotationY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("ROtationZ", "INTEGER", "NOT NULL", tableDef);

		// < Velocity vector.
		Table::AddDefinition("VelocityX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("VelocityY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("VelocityZ", "INTEGER", "NOT NULL", tableDef);

		// < Spin vector.
		Table::AddDefinition("SpinX", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("SpinY", "INTEGER", "NOT NULL", tableDef);
		Table::AddDefinition("SpinZ", "INTEGER", "NOT NULL", tableDef);

		// < Friction.
		Table::AddDefinition("Friction", "INTEGER", "NOT NULL", tableDef);

		// < Visible.
		Table::AddDefinition("Visible", "INTEGER", "NOT NULL", tableDef);

		// < Ghost.
		Table::AddDefinition("Ghost", "INTEGER", "NOT NULL", tableDef);

		// < Ignore collision.
		Table::AddDefinition("IgnoreCollision", "INTEGER", "NOT NULL", tableDef);

		// < Touching ground.
		Table::AddDefinition("TouchingGround", "INTEGER", "NOT NULL", tableDef);

		// < FK Component.
		Table::AddDefinition("ComponentId", "INTEGER", "NOT NULL REFERENCES Component(Id) ON DELETE CASCADE", tableDef);

		// < Audit data.
		Table::AddAuditDefinitions(tableDef);

		db->CreateTable("Placement", tableDef);
	}

	template <>
	std::vector<std::string> Table<Components::Placement>::Serialize(const Components::Placement& component)
	{
		auto result = Table<Components::Component>::Serialize(component);

		auto fwdX = std::to_string(component.vForward.x);
		auto fwdY = std::to_string(component.vForward.y);
		auto fwdZ = std::to_string(component.vForward.z);

		auto rhtX = std::to_string(component.vRight.x);
		auto rhtY = std::to_string(component.vRight.y);
		auto rhtZ = std::to_string(component.vRight.z);

		auto transX = std::to_string(component.vTranslation.x);
		auto transY = std::to_string(component.vTranslation.y);
		auto transZ = std::to_string(component.vTranslation.z);

		auto rotX = std::to_string(component.vRotation.x);
		auto rotY = std::to_string(component.vRotation.y);
		auto rotZ = std::to_string(component.vRotation.z);

		auto velX = std::to_string(component.vVelocity.x);
		auto velY = std::to_string(component.vVelocity.y);
		auto velZ = std::to_string(component.vVelocity.z);

		auto spnX = std::to_string(component.vSpin.x);
		auto spnY = std::to_string(component.vSpin.y);
		auto spnZ = std::to_string(component.vSpin.z);

		auto fric = std::to_string(component.nFriction);

		auto vis = std::to_string(component.bVisible);
		auto ghst = std::to_string(component.bGhost);
		auto ignCol = std::to_string(component.bIgnoreCollision);
		auto tchGnd = std::to_string(component.bTouchingGround);

		result.push_back(fwdX);
		result.push_back(fwdY);
		result.push_back(fwdZ);

		result.push_back(rhtX);
		result.push_back(rhtY);
		result.push_back(rhtZ);

		result.push_back(transX);
		result.push_back(transY);
		result.push_back(transZ);

		result.push_back(rotX);
		result.push_back(rotY);
		result.push_back(rotZ);

		result.push_back(velX);
		result.push_back(velY);
		result.push_back(velZ);

		result.push_back(spnX);
		result.push_back(spnY);
		result.push_back(spnZ);

		result.push_back(fric);

		result.push_back(vis);
		result.push_back(ghst);
		result.push_back(ignCol);
		result.push_back(tchGnd);

		return result;
	}

	template <>
	Components::Placement Table<Components::Placement>::Deserialize(const std::vector<std::string>& component)
	{
		auto id = std::stoi(component[0]);
		auto name = component[1];
		auto forward = Leadwerks::Vec3(std::stof(component[2]), std::stof(component[3]), std::stof(component[4]));
		auto right = Leadwerks::Vec3(std::stof(component[5]), std::stof(component[6]), std::stof(component[7]));
		auto translation = Leadwerks::Vec3(std::stof(component[8]), std::stof(component[9]), std::stof(component[10]));
		auto rotation = Leadwerks::Vec3(std::stof(component[11]), std::stof(component[12]), std::stof(component[13]));
		auto velocity = Leadwerks::Vec3(std::stof(component[14]), std::stof(component[15]), std::stof(component[16]));
		auto spin = Leadwerks::Vec3(std::stof(component[17]), std::stof(component[18]), std::stof(component[19]));
		auto friction = std::stof(component[20]);
		bool visible = std::stoi(component[21]);
		bool ghost = std::stoi(component[22]);
		bool ignoreCollision = std::stoi(component[23]);
		bool touchingGround = std::stoi(component[24]);

		auto result = Components::Placement();

		result.nId = id;
		result.cName = name;
		result.vForward = forward;
		result.vRight = right;
		result.vTranslation = translation;
		result.vRotation = rotation;
		result.vVelocity = velocity;
		result.vSpin = spin;
		result.nFriction = friction;
		result.bVisible = visible;
		result.bGhost = ghost;
		result.bIgnoreCollision = ignoreCollision;
		result.bTouchingGround = touchingGround;

		return result;
	}

} // < end namespace.

namespace Components
{
	template <>
	std::vector<Components::Placement> World::FetchComponents<Components::Placement>(uint64_t entity, const std::vector<WhereClause>& expression, bool bSingle /* = false */)
	{
		// < TODO: Add columns.
		std::string query = " \\
			SELECT c.[Id], c.[Name], p.[ForwardX], p.[ForwardY], p.[ForwardZ] \\
			, p.[RightX], p.[RightY], p.[RightZ], p.[TranslationX], p.[TranslationY] \\
			, p.[TranslationZ], p.[RotationX], p.[RotationY], p.[RotationZ] \\
			, p.[VelocityX], p.[VelocityY], p.[VelocityZ], p.[SpinX], p.[SpinY] \\
			, p.[SpinZ], p.[Friction], p.[Visible], p.[Ghost], p.[IgnoreCollision] \\
			, p.[TouchingGround] \\
			FROM [Placement] AS p \\
			LEFT JOIN [Component] AS c \\
			ON c.[Id] = p.[ComponentId] \\
			WHERE c.[EntityId] = " + std::to_string(entity) + ";";

		std::vector<Components::Placement> components;
		auto results = m_pDatabaseCtrl->ExecuteQuery(query);
		auto iter = results.begin();

		do
		{
			auto row = (*iter);
			auto comp = Database::Table<Components::Placement>::Deserialize(row);
			components.push_back(comp);
			iter++;
		} while (!bSingle || iter != results.end());

		return components;
	}

	template <>
	Components::Placement World::Merge<Components::Placement>(const Components::Placement& current, const Components::Placement& original)
	{
		auto result = current;

		result.nId = original.nId;

		return result;
	}

	template <>
	Components::Placement World::AddComponent<Components::Placement>(uint64_t entity, const Components::Placement& component)
	{
		std::string tableName = Components::Placement::ClassType();

		auto comp = World::AddComponent<Components::Component>(entity, component);

		// < TODO: Add columns and values.
		auto columns = ColumnCollection(1, "ForwardX");
		columns.push_back("ForwardY");
		columns.push_back("ForwardZ");
		columns.push_back("RightX");
		columns.push_back("RightY");
		columns.push_back("RightZ");
		columns.push_back("TranslationX");
		columns.push_back("TranslationY");
		columns.push_back("TranslationZ");
		columns.push_back("RotationX");
		columns.push_back("RotationY");
		columns.push_back("RotationZ");
		columns.push_back("VelocityX");
		columns.push_back("VelocityY");
		columns.push_back("VelocityZ");
		columns.push_back("SpinX");
		columns.push_back("SpinY");
		columns.push_back("SpinZ");
		columns.push_back("Friction");
		columns.push_back("Visible");
		columns.push_back("Ghost");
		columns.push_back("IgnoreCollision");
		columns.push_back("TouchingGround");
		columns.push_back("ComponentId");

		auto values = ValueCollection(1, std::to_string(component.vForward.x));
		values.push_back(std::to_string(component.vForward.y));
		values.push_back(std::to_string(component.vForward.z));
		values.push_back(std::to_string(component.vRight.x));
		values.push_back(std::to_string(component.vRight.y));
		values.push_back(std::to_string(component.vRight.z));
		values.push_back(std::to_string(component.vTranslation.x));
		values.push_back(std::to_string(component.vTranslation.y));
		values.push_back(std::to_string(component.vTranslation.z));
		values.push_back(std::to_string(component.vRotation.x));
		values.push_back(std::to_string(component.vRotation.y));
		values.push_back(std::to_string(component.vRotation.z));
		values.push_back(std::to_string(component.vVelocity.x));
		values.push_back(std::to_string(component.vVelocity.y));
		values.push_back(std::to_string(component.vVelocity.z));
		values.push_back(std::to_string(component.vSpin.x));
		values.push_back(std::to_string(component.vSpin.y));
		values.push_back(std::to_string(component.vSpin.z));
		values.push_back(std::to_string(component.nFriction));
		values.push_back(std::to_string((int)component.bVisible));
		values.push_back(std::to_string((int)component.bGhost));
		values.push_back(std::to_string((int)component.bIgnoreCollision));
		values.push_back(std::to_string((int)component.bTouchingGround));
		values.push_back(std::to_string(comp.nId));

		auto id = std::to_string(m_pDatabaseCtrl->InsertRecord(tableName, columns, values));

		// < Select and return the new component.
		auto where = std::vector<WhereClause>(1, std::make_tuple("Id", "=", id));
		auto result = FetchComponents<Components::Placement>(entity, where, true).front();

		return result;
	}

	template <>
	Components::Placement World::UpdateComponent<Components::Placement>(uint64_t entity, const Components::Placement& component)
	{
		auto original = World::FetchComponents<Components::Placement>(entity, std::vector<WhereClause>(), true).front();

		auto current = World::Merge<Components::Placement>(component, original);

		auto comp = World::UpdateComponent<Components::Component>(entity, current);

		// < TODO: Add columns and values.
		auto values = KeyValCollection(1, std::make_pair("ForwardX", std::to_string(component.vForward.x)));
		values.push_back(std::make_pair("ForwardY", std::to_string(component.vForward.y)));
		values.push_back(std::make_pair("ForwardZ", std::to_string(component.vForward.z)));
		values.push_back(std::make_pair("RightX", std::to_string(component.vRight.x)));
		values.push_back(std::make_pair("RightY", std::to_string(component.vRight.y)));
		values.push_back(std::make_pair("RightZ", std::to_string(component.vRight.z)));
		values.push_back(std::make_pair("TranslationX", std::to_string(component.vTranslation.x)));
		values.push_back(std::make_pair("TranslationY", std::to_string(component.vTranslation.y)));
		values.push_back(std::make_pair("TranslationZ", std::to_string(component.vTranslation.z)));
		values.push_back(std::make_pair("RotationX", std::to_string(component.vRotation.x)));
		values.push_back(std::make_pair("RotationY", std::to_string(component.vRotation.y)));
		values.push_back(std::make_pair("RotationZ", std::to_string(component.vRotation.z)));
		values.push_back(std::make_pair("VelocityX", std::to_string(component.vVelocity.x)));
		values.push_back(std::make_pair("VelocityY", std::to_string(component.vVelocity.y)));
		values.push_back(std::make_pair("VelocityZ", std::to_string(component.vVelocity.z)));
		values.push_back(std::make_pair("SpinX", std::to_string(component.vSpin.x)));
		values.push_back(std::make_pair("SpinY", std::to_string(component.vSpin.y)));
		values.push_back(std::make_pair("SpinZ", std::to_string(component.vSpin.z)));
		values.push_back(std::make_pair("Friction", std::to_string(component.nFriction)));
		values.push_back(std::make_pair("Visible", std::to_string((int)component.bVisible)));
		values.push_back(std::make_pair("Ghost", std::to_string((int)component.bGhost)));
		values.push_back(std::make_pair("IgnoreCollision", std::to_string((int)component.bIgnoreCollision)));
		values.push_back(std::make_pair("TouchingGround", std::to_string((int)component.bTouchingGround)));

		auto clause = std::vector<WhereClause>(1, std::make_tuple("ComponentId", "=", std::to_string(comp.nId)));

		m_pDatabaseCtrl->UpdateRecord("Placement", values, clause);

		auto updated = World::FetchComponents<Components::Placement>(entity, clause, true).front();
		return updated;
	}
} // < end namespace.

#endif _PLACEMENT_COMPONENT_TABLE_HPP_