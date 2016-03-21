#ifndef _EVENT_H_
	#define _EVENT_H_

#pragma once
#include "Leadwerks.h"
#include "Factory.hpp"
#include "ParameterMap.hpp"

/* MACROS */
#define REGISTER_EVENT(eventClass)	{ gEventFactory.Register(eventClass); }
#define CREATE_EVENT(eventType)		{ gEventFactory.Create(eventType); }

// -----

typedef const char* EventType;

/* Base Event */
class BaseEventData : public ParameterMap {
public:
	explicit BaseEventData(const float nTimeStamp = 0.0f)
		: m_nTimeStamp(nTimeStamp) { }
	
	virtual const char*	ObjectType() = 0;
	const float	TimeStamp() { return m_nTimeStamp; }

protected:

private:
	float	m_nTimeStamp; // The time the event was created.

}; // end class EventBase.

/* Mouse Hit Event */
class Event_MouseHit : public BaseEventData {
	CLASS_TYPE(Event_MouseHit);

public:
	Event_MouseHit() : BaseEventData(Leadwerks::Time::GetCurrent()) { 
		Set("vMousePosition", Leadwerks::Vec3(-1.0f, -1.0f, 0.0f))->
		Set("nMouseButton", -1);
	}

	Leadwerks::Vec3 MousePosition(void) { 
		auto val = this->GetVec3("vMousePosition");
		if (val != this->GetVec3Map().end()) { return val->second; }
		else { return Leadwerks::Vec3(-1.0f, -1.0f, 0.0f); }
	}

	int MouseButton(void) { 
		auto val = this->GetInt("nMouseButton");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Mouse Down Event */
class Event_MouseDown : public BaseEventData {
	CLASS_TYPE(Event_MouseDown);

public:
	Event_MouseDown() : BaseEventData(Leadwerks::Time::GetCurrent()) {
		Set("vMousePosition", Leadwerks::Vec3(-1.0f, -1.0f, 0.0f))->
			Set("nMouseButton", -1);
	}

	Leadwerks::Vec3 MousePosition(void) {
		auto val = this->GetVec3("vMousePosition");
		if (val != this->GetVec3Map().end()) { return val->second; }
		else { return Leadwerks::Vec3(-1.0f, -1.0f, 0.0f); }
	}

	int MouseButton(void) {
		auto val = this->GetInt("nMouseButton");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Mouse Up Event */
class Event_MouseUp : public BaseEventData {
	CLASS_TYPE(Event_MouseUp);

public:
	Event_MouseUp() : BaseEventData() {
		Set("vMousePosition", Leadwerks::Vec3(-1.0f, -1.0f, 0.0f))->
			Set("nMouseButton", -1);
	}

	Leadwerks::Vec3 MousePosition(void) {
		auto val = this->GetVec3("vMousePosition");
		if (val != this->GetVec3Map().end()) { return val->second; }
		else { return Leadwerks::Vec3(-1.0f, -1.0f, 0.0f); }
	}

	int MouseButton(void) {
		auto val = this->GetInt("nMouseButton");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Key Hit Event */
class Event_KeyHit : public BaseEventData {
	CLASS_TYPE(Event_KeyHit);

public:
	Event_KeyHit() : BaseEventData() {
		Set("nKey", -1);
	}

	int Key(void) {
		auto val = this->GetInt("nKey");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Key Down Event */
class Event_KeyDown : public BaseEventData {
	CLASS_TYPE(Event_KeyDown);

public:
	Event_KeyDown() : BaseEventData() {
		Set("nKey", -1);
	}

	int Key(void) {
		auto val = this->GetInt("nKey");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Key Up Event */
class Event_KeyUp : public BaseEventData {
	CLASS_TYPE(Event_KeyUp);

public:
	Event_KeyUp() : BaseEventData() {
		Set("nKey", -1);
	}

	int Key(void) {
		auto val = this->GetInt("nKey");
		if (val != this->GetIntMap().end()) { return val->second; }
		else { return -1; }
	}
};

/* Mouse Move Event */
class Event_MouseMove: public BaseEventData {
    CLASS_TYPE(Event_MouseMove);

public:
    Event_MouseMove() : BaseEventData()
    {
        Set("vOriginal", Leadwerks::Vec3(0.0f, 0.0f, 0.0f));
        Set("vCurrent", Leadwerks::Vec3(0.0f, 0.0f, 0.0f));
        Set("vDelta", Leadwerks::Vec3(0.0f, 0.0f, 0.0f));        
    }

    Leadwerks::Vec3 Original()
    {
        auto val = this->GetVec3("vOriginal");
        if (val != this->GetVec3Map().end()) { return val->second; }
        else { throw; } // < Unable to access value;
    }

    Leadwerks::Vec3 Current()
    {
        auto val = this->GetVec3("vCurrent");
        if (val != this->GetVec3Map().end()) { return val->second; }
        else { throw; } // < Unable to access value;
    }

    Leadwerks::Vec3 Delta()
    {
        auto val = this->GetVec3("vDelta");
        if (val != this->GetVec3Map().end()) { return val->second; }
        else { throw; } // < Unable to access value;
    }

    int Key(void) {
        auto val = this->GetInt("nKey");
        if (val != this->GetIntMap().end()) { return val->second; }
        else { return -1; }
    }
};

/* Externals */
extern Factory<BaseEventData>					gEventFactory;												// The global event factory handle.

// -----

#endif // _EVENT_H_