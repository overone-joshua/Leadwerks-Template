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

	~ActorManager(void);	

	Actor* Fetch(uint64_t _id);

	Actor* Create(void);

	void Delete(uint64_t _id);

protected:
	uint64_t GenerateId(void);

private:	

	uint64_t m_nRunningIndex;

}; // < end class.

#endif _ACTOR_MANAGER_HPP_