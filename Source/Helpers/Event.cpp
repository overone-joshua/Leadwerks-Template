#pragma once
#include "Event.hpp"
#include "Factory.hpp"

/* Externals From Event.hpp */
Factory<BaseEventData> gEventFactory;

// -----

BaseEventData::BaseEventData(const float nTimeStamp) : m_nTimeStamp(nTimeStamp) { }

const float BaseEventData::TimeStamp() { return this->m_nTimeStamp; }

EventData_LeadwerksInitialized::EventData_LeadwerksInitialized() {
	/* EMPTY */
}