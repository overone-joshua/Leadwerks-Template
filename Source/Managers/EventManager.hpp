/*-------------------------------------------------------
                    <copyright>
    
    File: EventManager.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for EventManager.
                 The EventManager class provides a clean
                 interface for adding event processing
                 support, driving a subscription model
                 for event delegation.

    Functions: 1. bool AddListener(const EventListenerDelegate& eventDelegate, const EventType& type);
    
               2. bool RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);
               
               3. bool TriggerEvent(BaseEventData& pEvent);
               
               4. bool QueueEvent(BaseEventData& pEvent);
               
               5. bool AbortEvent(const EventType& type, bool bAll = false);
               
               6. template <void(*Function)(BaseEventData*)>
	              bool Bind(const EventType& type);
                   
               7. template <class C, void(C::*Function)(BaseEventData*)>
	              bool Bind(C* instance, const EventType& type);

               8. template <void(*Function)(BaseEventData*)>
	              bool Unbind(const EventType& type);
                  
               9. template <class C, void(C::*Function)(BaseEventData*)>
	              bool Unbind(C* instance, const EventType& type);

---------------------------------------------------------*/

#ifndef _EVENTMANAGER_H_
	#define _EVENTMANAGER_H_

#pragma once
#include "Leadwerks.h"
#include "..\Utilities\Delegate.hpp"
#include "..\Utilities\Event.hpp"
#include "..\Utilities\Macros.hpp"

#include <list>
#include <map>

/* Define the number of queues the event manager uses internally to process events.*/
#define	NUM_QUEUES 2

typedef Delegate<BaseEventData*>						EventListenerDelegate;																		// Definition fora delegate, specifically used for events.

class EventManager {

	CLASS_TYPE(EventManager);

	enum eConstants { KINFINITE = 0xffffffff };
	typedef std::list<EventListenerDelegate>			EventListenerList;																			// Definition for a list of event-listener delegates.
	typedef std::map<EventType, EventListenerList>		EventMap;																					// Definition for event-listeners, seperated by event-type.
	typedef std::list<BaseEventData*>					EventQueue;																					// Definition for a queue of event-data.

public:
														EventManager();																				// Event manager constructor.
														~EventManager();																			// Event manager destructor.

	bool												Update(unsigned long nMaxMillis = 20);															// Processes any events within the event-manager's event queue
																																					// for the given amount of time, per frame.
	void												Render();																					// Performs any 3d-rendering for the event manager.
	void												Draw();																						// Performs any 2d-rendering for the event manager.

	bool												AddListener(const EventListenerDelegate& eventDelegate, const EventType& type);				// Adds the given delegate to the event-listener list of the
																																					// - given event-type.
	bool												RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type);			// Removes the given delegate from the event-listener list
																																					// - of the given event-type.

	bool												TriggerEvent(BaseEventData& pEvent);														// Immediataly triggers the given event, calling all currently
																																					// - registered listeners to the event.
	bool												QueueEvent(BaseEventData& pEvent);															// Queues the given event to processed during the event-
																																					// - manager's processing queue.
	bool												AbortEvent(const EventType& type, bool bAll = false);										// Aborts the execution of the given event. If bAll is true,
																																					// - all events of the given type are removed from processing.	

	template <void(*Function)(BaseEventData*)>
	bool Bind(const EventType& type) {
		EventListenerDelegate eventDelegate;
		eventDelegate.Bind<Function>();

		return AddListener(eventDelegate, type);
	}
	
	template <class C, void(C::*Function)(BaseEventData*)>
	bool Bind(C* instance, const EventType& type) {
		EventListenerDelegate eventDelegate;
		eventDelegate.Bind<C, Function>(instance);

		return AddListener(eventDelegate, type);
	}

	template <void(*Function)(BaseEventData*)>
	bool Unbind(const EventType& type) {
		EventListenerDelegate eventDelegate;
		eventDelegate.Bind<Function>();

		return RemoveListener(eventDelegate, type);
	}

	template <class C, void(C::*Function)(BaseEventData*)>
	bool Unbind(C* instance, const EventType& type) {
		EventListenerDelegate eventDelegate;
		eventDelegate.Bind<C, Function>(instance);

		return RemoveListener(eventDelegate, type);
	}	

protected:

private:	
	EventMap											m_eventListeners;																			// Contains all event-listeners, seperated by event type.
	EventQueue											m_queues[NUM_QUEUES];																		// Contains all events needing to be processed.
	int													m_nActiveQueue;																				// Indicates which event-processing queue is currently being used.	

}; // end class EventManager.

#endif // _EVENTMANAGER_H_