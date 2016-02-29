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

	class World : public Component
	{
		CLASS_TYPE(World);

		typedef void* InstPtr;
		typedef std::pair<uint64_t, std::string> CompKey;
		typedef std::map <CompKey, InstPtr> ComponentMap;

	public:

		World(std::string cName = "");
		~World(void);

		uint64_t CreateEntity(World* pWorld);
		void DestroyEntity(World* pWorld, uint64_t entity);

		template <typename T>
		void AddComponent(World* pWorld, uint64_t entity, T val);

		template <typename T>
		uint64_t RemoveComponent(World* pWorld, uint64_t entity, std::string cName);

		uint64_t& Get(uint64_t entity);

		std::vector<uint64_t> World::GetEntities(World* pWorld, uint64_t entityMask);

		template <typename T>
		std::vector<T>* GetComponents(World* pWorld, uint64_t entity);

		uint64_t& operator [] (int index)
		{
			return m_entityMasks[index];
		}

	protected:

		template <typename T>
		CompKey MakeComponentKey(uint64_t entity);

		template <typename T>
		std::vector<T>* Fetch(World* pWorld, uint64_t entity);

		template <typename T>
		World::ComponentMap::iterator FetchInternal(World* pWorld, uint64_t entity);

		void Dispose(void);

	private:

		std::vector<uint64_t> m_entityMasks;
		std::queue<uint64_t> m_availableEntities;

		uint64_t m_nRunningIndex;

		ComponentMap m_components;

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