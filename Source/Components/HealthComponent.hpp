#ifndef _HEALTH_COMPONENT_HPP_
	#define _HEALTH_COMPONENT_HPP_
	
#pragma once
#include "Component.hpp"

class HealthComponent : public Component {
public:

	HealthComponent(void);
	~HealthComponent(void);

protected:

	double m_nTotalHealth;
	double m_nCurrentHealth;	

}; // < end class.
	
HealthComponent::HealthComponent(void) { }

HealthComponent::~HealthComponent(void) { }

#endif _HEALTH_COMPONENT_HPP_