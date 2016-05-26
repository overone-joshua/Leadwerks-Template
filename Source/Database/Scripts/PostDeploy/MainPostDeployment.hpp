#ifndef _MAIN_POST_DEPLOYMENT_HPP_
	#define _MAIN_POST_DEPLOYMENT_HPP_

#pragma once
#include "../../../Services/DatabaseController.hpp"

#include "../../Tables/Table.hpp"
#include "../../Tables/Component.hpp"
#include "../../Tables/Appearance.hpp"

namespace Database
{
	static inline bool Deploy(IDatabaseController* const db)
	{

		Table<Components::Component>::CreateTable(db);
		Table<Components::Appearance>::CreateTable(db);

		return true;
	}

} // < end namespace.

#endif _MAIN_POST_DEPLOYMENT_HPP_