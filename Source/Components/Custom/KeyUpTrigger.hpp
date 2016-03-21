#ifndef _KEY_UP_TRIGGER_COMPONENT_HPP_
	#define _KEY_UP_TRIGGER_COMPONENT_HPP_

#pragma once
#include "../../Common.hpp"
#include "../../Utilities/Event.hpp"
#include "../../Utilities/Macros.hpp"

#include "../World.hpp"
#include "../Trigger.hpp"

namespace Components
{
	template <typename T>
	struct KeyUpTrigger : public Trigger<Components::World&, T, Event_KeyUp*>
	{
        typedef Delegate<Components::World&, T, Event_KeyUp*> KeyUpEvent;

		CLASS_TYPE(KeyUpTrigger);

		KeyUpTrigger(KeyUpEvent _callback, std::string _cName = "")
			: Trigger(_callback, _cName) { }

	}; // < end class.

} // < end namespace.

#endif _KEY_UP_TRIGGER_COMPONENT_HPP_