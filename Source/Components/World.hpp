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
#include "../Services/DatabaseController.hpp"

#include "Component.hpp"

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

		explicit World(IDatabaseController* databaseController, std::string cName = "");
		~World(void);

		uint64_t CreateEntity(const std::string& name);

		unsigned long DeleteEntity(uint64_t entity);

		template <typename T>
		T AddComponent(uint64_t entity, const T& component);

		template <typename T>
		void DeleteComponent(uint64_t entity, const std::vector<WhereClause>& expression);

		template <typename T>
		T UpdateComponent(uint64_t entity, const T& component);

		template <typename T>
		std::vector<T> FetchComponents(uint64_t entity, const std::vector<WhereClause>& expression, bool bSingle = false);

	protected:

        template <typename T>
        T Merge(const T& current, const T& original);

		void Dispose(void);

	private:

		IDatabaseController*  m_pDatabaseCtrl;

        std::vector<uint64_t> m_entityMasks;
        std::queue<uint64_t> m_availableEntities;

        uint64_t m_nRunningIndex;

	}; // < end struct.

} // < end namespace.

#endif _WORLD_HPP_