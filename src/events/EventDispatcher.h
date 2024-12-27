#pragma once
#include "Event.h"

class EventDispatcher {
private:
	Event& mEvent;
public:
	EventDispatcher(Event& event)
		: mEvent(event) {
	}
	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (mEvent.GetType() != T::GetStaticType()) {
			return false;
		}
		T& event = dynamic_cast<T&>(mEvent);
		func(event);
		return true;
	}
};
