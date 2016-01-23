#ifndef _HEALTH_COMPONENT_HPP_
	#define _HEALTH_COMPONENT_HPP_
	
#pragma once
#include "Component.hpp"

#include <queue>

class HealthComponent : public Component {
public:

	HealthComponent(long _id);
	~HealthComponent(void);

protected:

	double m_nTotalHealth;
	double m_nCurrentHealth;

	std::queue<double> m_damagePoints;
	std::queue<double> m_healingPoints;

}; // < end class.
	
#endif _HEALTH_COMPONENT_HPP_