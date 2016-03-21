#ifndef _INPUT_ENTITY_HPP_
	#define _INPUT_ENTITY_HPP_

#pragma once
#include "../Common.hpp"
#include "../Utilities/Event.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/luatables/luatables.h"

#include "../Components/Component.hpp"
#include "../Components/ComponentDictionary.hpp"
#include "../Components/Trigger.hpp"
#include "../Components/World.hpp"

#include "../Components/Custom/MouseMoveTrigger.hpp"
#include "../Components/Custom/MouseHitTrigger.hpp"
#include "../Components/Custom/MouseDownTrigger.hpp"
#include "../Components/Custom/MouseUpTrigger.hpp"
#include "../Components/Custom/KeyHitTrigger.hpp"
#include "../Components/Custom/KeyDownTrigger.hpp"
#include "../Components/Custom/KeyUpTrigger.hpp"

#include <vector>

namespace Entities
{
	const uint64_t MASK_INPUT = COMPONENT_TRIGGER;

	template <typename T>
	class Input
	{
		CLASS_TYPE(Input);

	public:
		Input(void) 
		{
			mouseMoveTriggers = nullptr;
			mouseHitTriggers = nullptr;
			mouseDownTriggers = nullptr;
			mouseUpTriggers = nullptr;

			keyHitTriggers = nullptr;
			keyDownTriggers = nullptr;
			keyUpTriggers = nullptr;
		}		

		Components::Component component;
		
		std::vector<Components::MouseMoveTrigger<T>>* mouseMoveTriggers;
		std::vector<Components::MouseHitTrigger<T>>* mouseHitTriggers;			
		std::vector<Components::MouseDownTrigger<T>>* mouseDownTriggers;		
		std::vector<Components::MouseUpTrigger<T>>* mouseUpTriggers;		
		std::vector<Components::KeyHitTrigger<T>>* keyHitTriggers;		
		std::vector<Components::KeyDownTrigger<T>>* keyDownTriggers;		
		std::vector<Components::KeyUpTrigger<T>>* keyUpTriggers;

        static void OnMouseMove(Components::World& world, uint64_t entity, Event_MouseMove* pEvent)
        {
            auto res = Components::World::Get<T>(world, entity);

            auto iter = res.mouseMoveTriggers->begin();
            while (iter != res.mouseMoveTriggers->end())
            {
                auto trigger = (*iter);

                trigger.callback.Invoke(world, res, pEvent);

                ++iter;
            }
        }

        static void OnKeyDown(Components::World& world, uint64_t entity, Event_KeyDown* pEvent)
        {
            auto res = Components::World::Get<T>(world, entity);

            auto iter = res.keyDownTriggers->begin();
            while (iter != res.keyDownTriggers->end())
            {
                auto trigger = (*iter);

                trigger.callback.Invoke(world, res, pEvent);

                ++iter;
            }            
        }

        static void OnKeyUp(Components::World& world, uint64_t entity, Event_KeyUp* pEvent)
        {
            auto res = Components::World::Get<T>(world, entity);

            auto iter = res.keyUpTriggers->begin();
            while (iter != res.keyUpTriggers->end())
            {
                auto trigger = (*iter);

                trigger.callback.Invoke(world, res, pEvent);

                ++iter;
            }
        }

	}; // < end class.

} // < end namespace.

#endif _INPUT_ENTITY_HPP_