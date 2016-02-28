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

		template <typename T1, typename T2>
		struct ComponentKeyComparer {
			bool operator () (const std::pair<T1, T2>& x, const std::pair<T1, T2>& y) {
				return x.first < y.first && x.second < y.second;
			}
		};

		typedef void* InstPtr;
		typedef std::pair<unsigned, std::string> CompKey;
		typedef std::map <CompKey, InstPtr, ComponentKeyComparer<unsigned, std::string>> ComponentMap;

	public:

		World(std::string cName = "");
		~World(void);

		unsigned CreateEntity(World* pWorld);
		void DestroyEntity(World* pWorld, unsigned entity);

		template <typename T>
		void AddComponent(World* pWorld, unsigned entity, T val);

		template <typename T>
		unsigned RemoveComponent(World* pWorld, unsigned entity, std::string cName);

		unsigned& Get(unsigned entity);

		unsigned& operator [] (int index)
		{
			return m_entityMasks[index];
		}

	protected:

		template <typename T>
		World::ComponentMap::iterator FetchInternal(World* pWorld, unsigned entity);

	private:

		std::vector<unsigned> m_entityMasks;
		std::queue<unsigned> m_availableEntities;

		unsigned m_nRunningIndex;

		ComponentMap m_components;

	}; // < end struct.

	template <typename T>
	void World::AddComponent(World* pWorld, unsigned entity, T val)
	{
		std::vector<T>* components = nullptr;

		val.nId = entity;

		auto iter = FetchInternal<T>(pWorld, entity);
		if (iter == pWorld->m_components.end()) 
		{
			auto type = T::ClassType();
			auto key = std::make_pair(entity, type);

			pWorld->m_components.insert( std::make_pair(key, (void*)(new std::vector<T>(1, val))) );
		}

		components = static_cast<std::vector<T>*>(iter->second);
		components->push_back(val);

		components->push_back(static_cast<T>(val));
	}

	template <typename T>
	unsigned World::RemoveComponent(World* pWorld, unsigned entity, std::string cName)
	{
		unsigned numRemoved = 0;

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
	World::ComponentMap::iterator World::FetchInternal(World* pWorld, unsigned entity)
	{
		auto type = T::ClassType();
		auto key = std::make_pair(entity, type);
		return pWorld->m_components.find(key);
	}

} // < end namespace.

#endif _WORLD_HPP_