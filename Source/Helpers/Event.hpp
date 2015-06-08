#ifndef _EVENT_H_
	#define _EVENT_H_

#pragma once
#include "Leadwerks.h"
#include "Factory.hpp"

/* MACROS */
#define REGISTER_EVENT(eventClass)	{ gEventFactory.Register(eventClass); }
#define CREATE_EVENT(eventType)		{ gEventFactory.Create(eventType); }

// -----

typedef const char* EventType;

class BaseEventData {
public:
												BaseEventData(const float nTimeStamp = 0.0f);				// BaseEventData constructor.
	
	virtual const char*							ObjectType() = 0;											// Placeholder for derived events to bind them 
																											// - to the event factory.
	const float									TimeStamp();												// Gets the events creation time-stamp.

protected:

private:
	float										m_nTimeStamp;												// The time the event was created.

}; // end class EventBase.

class EventData_LeadwerksInitialized : public BaseEventData {
public:
												CLASS_TYPE(EventData_LeadwerksInitialized);					// Macro, containing methods used for binding events
																											// - to the event factory.

												EventData_LeadwerksInitialized();							// EventData_LeadwerksInitialized constructor.

protected:

private:

}; // end class EventData_LeadwerksInitialized.

/* Externals */
extern Factory<BaseEventData>					gEventFactory;												// The global event factory handle.

// -----

#endif // _EVENT_H_