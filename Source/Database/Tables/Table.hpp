#ifndef _TABLE_HPP_
	#define _TABLE_HPP_

#pragma once
#include <sqlite-persistence/DbConnection.hpp>

namespace Database
{
	template <class C>
	class Table
	{
	public:

		static void CreateTable(IDbConnection* const _pConnection);

	protected:

	private:

	}; // < end class.

} // < end namespace.

#endif _TABLE_HPP_