#include "Window.h"
#include "events/EventDispatcher.h"

void Window::InitWindow()
{
	if (!glfwInit()) {
		std::cout << "Failed to init glfw\n";
		throw new std::runtime_error("Failed to init glfw");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
	if (!mWindow)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		throw new std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(mWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw new std::runtime_error("Failed to initialize GLAD");
	}
	glfwSetWindowUserPointer(mWindow, (void*)(this));
	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventWindowClose event;
		w->OnEventCallback(event);
		});
	glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventWindowSize event(width, height);
		w->OnEventCallback(event);
		});
	glfwSetFramebufferSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventFrameBufferSize event(width, height);
		w->OnEventCallback(event);
		});
	glfwSetWindowPosCallback(mWindow, [](GLFWwindow* window, int xpos, int ypos) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventWindowPosition event(xpos, ypos);
		w->OnEventCallback(event);
		});
	glfwSetWindowMaximizeCallback(mWindow, [](GLFWwindow* window, int maximized) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		if (maximized > 0)
		{
			EventWindowMaximize event;
			w->OnEventCallback(event);
		}
		else
		{
			EventWindowMinimize event;
			w->OnEventCallback(event);
		}
		});
	glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* window, int focused) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		if (focused > 0)
		{
			EventWindowGetFocus event;
			w->OnEventCallback(event);
		}
		else
		{
			EventWindowLoseFocus event;
			w->OnEventCallback(event);
		}
		});
	glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventCursorPosition event(xpos, ypos);
		w->OnEventCallback(event);
		});
	glfwSetCursorEnterCallback(mWindow, [](GLFWwindow* window, int entered) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		if (entered > 0)
		{
			EventCursorEntered event;
			w->OnEventCallback(event);
		}
		else
		{
			EventCursorOutered event;
			w->OnEventCallback(event);
		}
		});
	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mode) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS)
		{
			EventMouseButtonPressed event(button, mode);
			w->OnEventCallback(event);
		}
		else if (action == GLFW_RELEASE)
		{
			EventMouseButtonReleased event(button, mode);
			w->OnEventCallback(event);
		}
		});
	glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		EventMouseScroll event(xoffset, yoffset);
		w->OnEventCallback(event);
		});
    glEnable(GL_DEPTH_TEST);
}

void Window::OnEventCallback(Event& event)
{
	for (auto& handle : mHandlers) {
		handle(event);
	}
}

void Window::ProcessKeys()
{
	for (int i = 0; i < KeysLen; ++i) {
		int oldState = int(mKeys[i]);
		int curState = glfwGetKey(mWindow, i);
		if (curState == GLFW_RELEASE) {
			if (oldState == GLFW_RELEASE) {
				continue;
			}
			mKeys[i] = char(curState);
			EventKeyReleased e(i);
			OnEventCallback(e);
		}
		else if (curState == GLFW_PRESS) {
			if (oldState == GLFW_PRESS) {
				EventKeyRepeated e(i);
				OnEventCallback(e);
			}
			else {
				mKeys[i] = char(curState);
				EventKeyPressed e(i);
				OnEventCallback(e);
			}
		}
	}
}

void Window::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<EventWindowSize>(std::bind(&Window::OnEventWindowSize, this, std::placeholders::_1));
}

void Window::OnEventWindowSize(EventWindowSize& event)
{
	mWidth = event.GetWidth();
	mHeight = event.GetHeight();
}

void Window::OnUpdate()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
	ProcessKeys();
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::RegisterHandler(std::function<void(Event&)> func)
{
	mHandlers.push_back(func);
}
