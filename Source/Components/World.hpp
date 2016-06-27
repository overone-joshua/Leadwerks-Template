/*-------------------------------------------------------
                    <copyright>

    File: World.hpp
    Language: C++

    (C) Copyright Eden Softworks

    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net

    Description: Header file for World component.

---------------------------------------------------------*/

#ifndef _WORLD_HPP_
	#define _WORLD_HPP_

#pragma once
#include "Leadwerks.h"
#include "../Utilities/Macros.hpp"

#include "Component.hpp"
#include "../Repositories/DbRepository.hpp"
#include "../Repositories/ComponentRepository.hpp"

#include <sqlite-persistence/DbConnection.hpp>

#include <map>
#include <string>
#include <queue>
#include <vector>

namespace Components
{
	/** A World component..
	 *  The World component is the entrypoint to component access,
	 *  creation and deletion.
	*/
	class World : public Component
	{
		CLASS_TYPE(World);

	public:

		explicit World(IDbConnection* _pConnection, uint64_t _nEntityId, std::string cName = "");
		~World(void);

		uint64_t CreateEntity(const std::string& name);

		void DeleteEntity(uint64_t entity);

	protected:

		void Dispose(void);

	private:

		IDbConnection*  m_pConnection;

        std::vector<uint64_t> m_entityMasks;
        std::queue<uint64_t> m_availableEntities;

        uint64_t m_nRunningIndex;

	}; // < end struct.

} // < end namespace.

#endif _WORLD_HPP_