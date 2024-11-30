#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <functional>

#include "Event.h"

class EventDispatcher {
private:
	std::multimap < EventType, std::function<void(Event&)>> m_handlers;
public:
	EventDispatcher(GLFWwindow* window);
	void HandleEvent(Event&);
	void RegisterHandler(EventType etype, std::function<void(Event&)> handler);
};
