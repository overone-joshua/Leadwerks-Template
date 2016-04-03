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

	protected:

		Table(IDatabaseController* _db) : db(_db) { }

	private:

	}; // < end class.

} // < end namespace.

#endif _TABLE_HPP_