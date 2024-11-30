#include "EventDispatcher.h"

EventDispatcher::EventDispatcher(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, (void*)(this));
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventWindowClose event;
		dispatcher->HandleEvent(event);
		});
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventWindowSize event(width, height);
		dispatcher->HandleEvent(event);
		});
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventFrameBufferSize event(width, height);
		dispatcher->HandleEvent(event);
		});
	glfwSetWindowPosCallback(window, [](GLFWwindow* window, int xpos, int ypos) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventWindowPosition event(xpos, ypos);
		dispatcher->HandleEvent(event);
		});
	glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int maximized) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		if (maximized > 0)
		{
			EventWindowMaximize event;
			dispatcher->HandleEvent(event);
		}
		else
		{
			EventWindowMinimize event;
			dispatcher->HandleEvent(event);
		}
		});
	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		if (focused > 0)
		{
			EventWindowGetFocus event;
			dispatcher->HandleEvent(event);
		}
		else
		{
			EventWindowLoseFocus event;
			dispatcher->HandleEvent(event);
		}
		});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mode) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
		{
			EventKeyPressed event(key, mode);
			dispatcher->HandleEvent(event);
		}
		else if (action == GLFW_RELEASE)
		{
			EventKeyReleased event(key, mode);
			dispatcher->HandleEvent(event);
		}
		else
		{
			EventKeyRepeated event(key, mode);
			dispatcher->HandleEvent(event);
		}
		});
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventCursorPosition event(xpos, ypos);
		dispatcher->HandleEvent(event);
		});
	glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int entered) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		if (entered > 0)
		{
			EventCursorEntered event;
			dispatcher->HandleEvent(event);
		}
		else
		{
			EventCursorOutered event;
			dispatcher->HandleEvent(event);
		}
		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mode) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
		{
			EventMouseButtonPressed event(button, mode);
			dispatcher->HandleEvent(event);
		}
		else if (action == GLFW_RELEASE)
		{
			EventMouseButtonReleased event(button, mode);
			dispatcher->HandleEvent(event);
		}
		});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		EventDispatcher* dispatcher = (EventDispatcher*)glfwGetWindowUserPointer(window);
		EventMouseScroll event(xoffset, yoffset);
		dispatcher->HandleEvent(event);
		});
}

void EventDispatcher::HandleEvent(Event& event)
{
	auto begin = m_handlers.lower_bound(event.GetType());
	auto end = m_handlers.upper_bound(event.GetType());
	for (auto& iter = begin; iter != end; ++iter)
	{
		iter->second(event);
	}
}

void EventDispatcher::RegisterHandler(EventType etype, std::function<void(Event&)> handler)
{
	m_handlers.insert({etype, handler});
}
