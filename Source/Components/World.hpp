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

		typedef void*                                     InstPtr;			  /*!< A defined type aliasing a void. */
		typedef std::pair<uint64_t, std::string>          CompKey;	          /*!< A defined type aliasing a std::pair used as the key for the ComponentMap. */
		typedef std::map <CompKey, InstPtr>               ComponentMap;	      /*!< A defined type aliasing a std::map used to store components by entity relation and their containing collection. */

	public:

                                                          World(std::string cName = "");                                          /** The World component constructor. */
                                                          ~World(void);                                                           /** The World component destructor. */
		
		uint64_t                                          CreateEntity(World* pWorld);                                            /** Creates a new entity contained within the given World. */
		
		void                                              DestroyEntity(World* pWorld, uint64_t entity);                          /** Destroys the given entity from the given World. */
		
		template <typename T> void                        AddComponent(World* pWorld, uint64_t entity, T val);                    /** Adds the given Component of type T to the given World and associates the component with the given entity. */
		
		template <typename T> uint64_t                    RemoveComponent(World* pWorld, uint64_t entity, std::string cName);     /** Attempts to remove the given Component of type T from the given World that is associated with the given entity of the given name. */

		uint64_t&                                         Get(uint64_t entity);                                                   /** Returns a reference to the given entities Component bitmask. */
		
		std::vector<uint64_t>                             GetEntities(World* pWorld, uint64_t entityMask);                        /** Returns a collection of entity ids that explicitely match the given entityMask. */
				
		template <typename T> std::vector<T>*             GetComponents(World* pWorld, uint64_t entity);                          /** Returns a Component collection of type T assocated with the given entity. */

		uint64_t& operator [] (int index)
		{
			return m_entityMasks[index];
		}

	protected:
		
		template <typename T> CompKey                         MakeComponentKey(uint64_t entity);                      /** Returns a component key from the given Component type T and the given entity. */
				
		template <typename T> std::vector<T>*                 Fetch(World* pWorld, uint64_t entity);                  /** Attempts to fetch all components of type T associated with the given entity. */
				
		template <typename T> World::ComponentMap::iterator   FetchInternal(World* pWorld, uint64_t entity);          /** Attempts to return an iterator into the Worlds Component collection of type T associated with the given entity. */
		
		void                                                  Dispose(void);                                          /** Cleans up all resources used by the World. */

	private:

		std::vector<uint64_t>                                 m_entityMasks;		           /*!< A std::vector of uint64_t Component bitmasks. */
		std::queue<uint64_t>                                  m_availableEntities;	           /*!< A std::vector of uint64_t entity indexes that are available. */

		uint64_t                                              m_nRunningIndex;	               /*!< A uint64_t which is incremented by one for every new entity. */

		ComponentMap                                          m_components;	                   /*!< A std::map of Components keyed by the associated entity and the Component's ClassType. */

	}; // < end struct.

	template <typename T>
	World::CompKey World::MakeComponentKey(uint64_t entity)
	{
		std::string type = T::ClassType();
		auto key = std::make_pair(entity, type);

		return key;
	}

	template <typename T>
	void World::AddComponent(World* pWorld, uint64_t entity, T val)
	{
		std::string type = T::ClassType();
		auto key = std::make_pair(entity, type);

		val.nId = entity;
		
		auto iter = pWorld->FetchInternal<T>(pWorld, entity);
		if (iter == pWorld->m_components.end())
		{
			pWorld->m_components.insert( std::make_pair(key, (void*)(new std::vector<T>())) );
		}

		auto it = pWorld->Fetch<T>(pWorld, entity);
		it->push_back(val);
	}

	template <typename T>
	uint64_t World::RemoveComponent(World* pWorld, uint64_t entity, std::string cName)
	{
		uint64_t numRemoved = 0;

		auto iter = FetchInternal<T>(pWorld);
		if (iter == pWorld->m_components.end()) { return; }

		auto components = static_cast<std::vector<T>*>(iter->second);
		auto it = components.begin();
		while (it != components.end())
		{
			if (it.nId == entity)
			{
				if (cName.compare(it.cName) == 0) 
				{
					it = components.erase(it); 
					numRemoved += 1;
				}
			}

			it++;
		}

		return numRemoved;

	}

	template <typename T>
	std::vector<T>* World::Fetch(World* pWorld, uint64_t entity)
	{
		std::string type = T::ClassType();
		auto key = std::make_pair(entity, type);

		auto it = pWorld->m_components.find(key);
		if (it != pWorld->m_components.end()) { return static_cast<std::vector<T>*>(it->second); }

		return nullptr;

	}

	template <typename T>
	World::ComponentMap::iterator World::FetchInternal(World* pWorld, uint64_t entity)
	{
		std::string type = T::ClassType();
		auto key = std::make_pair(entity, type);

		return pWorld->m_components.find(key);

	}

	template <typename T>
	std::vector<T>* World::GetComponents(World* pWorld, uint64_t entity)
	{
		std::string type = T::ClassType();
		auto key = std::make_pair(entity, type);

		return static_cast<std::vector<T>*>( pWorld->m_components.at(key) );
		
	}

} // < end namespace.

#endif _WORLD_HPP_