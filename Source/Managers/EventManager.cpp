#pragma once
#include "Leadwerks.h"

#include "EventManager.hpp"
#include "..\Utilities\Delegate.hpp"
#include "..\Utilities\Event.hpp"

#include <list>
#include <map>

EventManager::EventManager()
	: m_nActiveQueue(0) {

}

EventManager::~EventManager()
{
    Dispose();
}

void EventManager::Dispose(void)
{

}

bool EventManager::Update(unsigned long nMaxMillis) {
    unsigned long currMs = 0, maxMs = 0;

    currMs = Leadwerks::Time::GetCurrent();
	maxMs = ((nMaxMillis == EventManager::KINFINITE) ? (EventManager::KINFINITE) : (currMs + maxMs));

	/* Swap active queue, clear new queue, after swap */
	int queueToProcess = this->m_nActiveQueue;
	m_nActiveQueue = (this->m_nActiveQueue + 1) % NUM_QUEUES;
	m_queues[m_nActiveQueue].clear();

	/* Process the queue */
	while (!m_queues[queueToProcess].empty()) {
		BaseEventData* pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();

		EventType eventType = pEvent->ObjectType();

		/* Find delegate functions registered for this event */
		auto find = m_eventListeners.find(eventType);
		if (find != m_eventListeners.end()) {
			const EventListenerList& eventListeners = find->second;

			/* Call each listener */
			EventListenerList::const_iterator it = eventListeners.begin();
			while (it != eventListeners.end()) {
				if (&it != nullptr) {
					it->Invoke(pEvent);
				}
				++it;
			}
		}

		/* Check to see if processing time ran out */
		currMs = Leadwerks::Time::GetCurrent();
		if (nMaxMillis != EventManager::KINFINITE && currMs >= maxMs) {
			break;
		}
	}

	/* If all events could not be processed this frame, push the remaining events to the new
	   - active queue.*/
	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed) {
		while (!m_queues[queueToProcess].empty()) {
			BaseEventData* pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_nActiveQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}

void EventManager::Render() {

}

void EventManager::Draw() {

}

bool EventManager::AddListener(const EventListenerDelegate& eventDelegate, const EventType& type) {
	EventListenerList& eventListenerList = m_eventListeners[type];
	EventListenerList::iterator it = eventListenerList.begin();
	while (it != eventListenerList.end()) {
		if (*it == eventDelegate) {
			return false;
		}
		++it;
	}

	eventListenerList.push_back(eventDelegate);
	return true;
}

bool EventManager::RemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) {
	bool success = false;

	auto find = m_eventListeners.find(type);
	if (find != m_eventListeners.end()) {
		EventListenerList& listeners = find->second;
		EventListenerList::iterator it = listeners.begin();
		while (it != listeners.end()) {
			if (*it == eventDelegate) {
				listeners.erase(it);
				success = true;
				break;
			}
			++it;
		}
	}

	return success;
}

bool EventManager::TriggerEvent(BaseEventData& pEvent) {
	bool processed = false;

	auto find = m_eventListeners.find(pEvent.ObjectType());
	if (find != m_eventListeners.end()) {
		EventListenerList& eventListenerList = find->second;
		EventListenerList::const_iterator it = eventListenerList.begin();
		while (it != eventListenerList.end()) {
			if (&it != nullptr) {
				it->Invoke(&pEvent);
				processed = true;
			}
			++it;
		}
	}

	return processed;
}

bool EventManager::QueueEvent(BaseEventData& pEvent) {
	if (&pEvent == nullptr)
		return false;

	auto find = m_eventListeners.find(pEvent.ObjectType());
	if (find != m_eventListeners.end()) {
		m_queues[m_nActiveQueue].push_back(&pEvent);
		return true;
	}
	else {
		return false;
	}
}

bool EventManager::AbortEvent(const EventType& type, bool bAll) {
	bool success = false;

	EventMap::iterator find = m_eventListeners.find(type);
	if (find != m_eventListeners.end()) {
		EventQueue& eventQueue = m_queues[m_nActiveQueue];
		EventQueue::const_iterator it = eventQueue.begin();
		while (it != eventQueue.end()) {
			auto thisIt = it;
			if ((*thisIt)->ObjectType() == type) {
				eventQueue.erase(thisIt);
				success = true;
				if (!bAll) { break; }
			}

			++it;
		}
	}

	return success;
}