#ifndef _TABLE_HPP_
	#define _TABLE_HPP_

#pragma once
#include "../../Services/DatabaseController.hpp"

#include <string>

namespace Database
{
	template <class C>
	class Table
	{
	public:

		static void CreateTable(IDatabaseController* const db);

		static inline void AddDefinition(std::string _col, std::string _typ, std::string _nul, DataTable& const _outTable)
		{
			std::tuple<std::string, std::string, std::string> rowDef;

			rowDef = std::make_tuple(_col, _typ, _nul);
			_outTable.push_back(rowDef);
		}

        static inline void AddAuditDefinitions(DataTable& const _outTable)
        {
            // < Audit Data.
            Table::AddDefinition("CreatedDate", "DATETIME", " NOT NULL DEFAULT (DATETIME('now', 'localtime'))", _outTable);
            Table::AddDefinition("ModifiedDate", "DATETIME", "NULL", _outTable);
        }

		static inline void AddFKConstraint(const std::string& _col, const std::string& _fkTbl, const std::string& _fkCol, IDatabaseController* db)
		{
			db->CreateFKConstraint(_col, _fkTbl, _fkCol);
		}

	protected:

		Table(IDatabaseController* _db) : m_pDb(_db), db(_db) { }

	private:

	}; // < end class.

} // < end namespace.

#endif _TABLE_HPP_