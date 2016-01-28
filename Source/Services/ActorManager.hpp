#ifndef _ACTOR_MANAGER_HPP_
	#define _ACTOR_MANAGER_HPP_
	
#pragma once
#include "../Utilities/Macros.hpp"
#include "../Components/Component.hpp"
#include "../Common.hpp"

#include <cassert>
#include <map>
#include <vector>

class Actor;

class ActorManager {	

	template <typename T1, typename T2>
	struct ActorComponentKeyComparer {
		bool operator () (const std::pair<T1, T2>& x, const std::pair<T1, T2>& y) {
			return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
		}
	};

	typedef std::pair<uint64_t, const char*> ActorComponentKey;
	typedef std::map<ActorComponentKey, std::vector<const Component*>, ActorComponentKeyComparer<uint64_t, const char*>> ActorComponentMap;

public:

	ActorManager(Factory<Component> pComponentFactory);
	~ActorManager(void);	

	const Actor* Fetch(uint64_t _id);

	uint64_t Create(void);

	void Delete(uint64_t _id);

	template <typename T>
	void AddComponent(uint64_t _id);

protected:
	uint64_t GetNextId(void);

private:	
	Factory<Component> m_pComponentFactory;
	uint64_t m_nRunningIndex;

	std::map<uint64_t, Actor*> m_actors;	

	//const ActorComponentMap m_actorComponents;
	ActorComponentMap m_actorComponents;

}; // < end class.

template <typename T>
void ActorManager::AddComponent(uint64_t _id) {

	// < Are we attempting to add a component to an non-existing
	// * actor?
	auto actor = this->Fetch(_id);
	assert(actor != nullptr);

	auto type = T::ClassType();
	T* newComponent = (T*)(gComponentFactory.Create(type));
	newComponent->setId(_id);

	auto actorComponents = m_actorComponents[make_pair(_id, type)];
	actorComponents.push_back(newComponent);

}

#endif _ACTOR_MANAGER_HPP_