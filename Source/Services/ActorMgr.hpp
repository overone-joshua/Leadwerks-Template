#ifndef _ACTOR_MANAGER_HPP_
	#define _ACTOR_MANAGER_HPP_
	
#pragma once

class ActorMgr {
public:

	ActorMgr(void);
	~ActorMgr(void);

	long GenerateId(void);

private:

	long m_nRunningIndex;

}; // < end class.

#endif _ACTOR_MANAGER_HPP_