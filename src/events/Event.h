#pragma once

enum class EventType {
	Event,

	EventWindowClose, EventWindowSize, 
	EventWindowPosition, 
	EventWindowMaximize, EventWindowMinimize, 
	EventWindowGetFocus, EventWindowLoseFocus,

	EventFrameBufferSize,

	EventKeyPressed, EventKeyReleased, EventKeyRepeated,

	EventCursorPosition, EventCursorEntered, EventCursorOutered, 

	EventMouseButtonPressed, EventMouseButtonReleased, EventMouseScroll,
};

#include <iostream>

class Event {
public:
	virtual ~Event() {};
	virtual EventType GetType() {
		return EventType::Event;
	}
};

#define SUB_EVENT_TYPE(name)\
	~name() {}\
	virtual EventType GetType() override { return EventType::name; }

class EventWindowClose: public Event{
public:
	SUB_EVENT_TYPE(EventWindowClose)
};

class EventWindowSize : public Event {
private:
	int m_width, m_height;
public:
	EventWindowSize(int width, int height) :
		m_width(width), m_height(height) {}

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	SUB_EVENT_TYPE(EventWindowSize)
};

class EventFrameBufferSize : public Event {
private:
	int m_width, m_height;
public:
	EventFrameBufferSize(int width, int height) :
		m_width(width), m_height(height) {
	}

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	SUB_EVENT_TYPE(EventFrameBufferSize)
};

class EventWindowPosition : public Event {
private:
	int m_xpos, m_ypos;
public:
	EventWindowPosition(int xpos, int ypos) :
		m_xpos(xpos), m_ypos(ypos) {
	}
	int GetXpos() const { return m_xpos; }
	int GetYpos() const { return m_ypos; }
	SUB_EVENT_TYPE(EventWindowPosition)
};

class EventWindowMaximize : public Event {
public:
	EventWindowMaximize() {}
	SUB_EVENT_TYPE(EventWindowMaximize)
};

class EventWindowMinimize : public Event {
private:
	bool m_maximized;
public:
	EventWindowMinimize() {}
	SUB_EVENT_TYPE(EventWindowMinimize)
};

class EventWindowGetFocus : public Event {
public:
	EventWindowGetFocus() {}
	SUB_EVENT_TYPE(EventWindowGetFocus)
};

class EventWindowLoseFocus : public Event {
public:
	EventWindowLoseFocus() {}
	SUB_EVENT_TYPE(EventWindowLoseFocus)
};

class EventKeyPressed : public Event {
private:
	int m_key, m_mode;
public:
	EventKeyPressed(int key, int mode) :
		m_key(key), m_mode(mode) {
	}
	int GetKey() const { return m_key; }
	int GetMode() const { return m_mode; }

	SUB_EVENT_TYPE(EventKeyPressed)
};

class EventKeyReleased : public Event {
private:
	int m_key, m_mode;
public:
	EventKeyReleased(int key, int mode) :
		m_key(key), m_mode(mode) {
	}
	int GetKey() const { return m_key; }
	int GetMode() const { return m_mode; }

	SUB_EVENT_TYPE(EventKeyReleased)
};

class EventKeyRepeated : public Event {
private:
	int m_key, m_mode;
public:
	EventKeyRepeated(int key, int mode) :
		m_key(key), m_mode(mode) {
	}
	int GetKey() const { return m_key; }
	int GetMode() const { return m_mode; }

	SUB_EVENT_TYPE(EventKeyRepeated)
};

class EventCursorPosition : public Event {
private:
	double m_xpos, m_ypos;
public:
	EventCursorPosition(double xpos, double ypos)
		: m_xpos(xpos), m_ypos(ypos) {
	}
	double GetXpos() const { return m_xpos; }
	double GetYpos() const { return m_ypos; }

	SUB_EVENT_TYPE(EventCursorPosition)
};

class EventCursorEntered: public Event {
public:
	EventCursorEntered() {}
	SUB_EVENT_TYPE(EventCursorEntered)
};

class EventCursorOutered : public Event {
public:
	EventCursorOutered() {}
	SUB_EVENT_TYPE(EventCursorOutered)
};

class EventMouseButtonPressed : public Event {
private:
	int m_button, m_mode;
public:
	EventMouseButtonPressed(int button, int mode) :
		m_button(button), m_mode(mode) {
	}
	int GetButton() const { return m_button; }
	int GetMode() const { return m_mode; }
	SUB_EVENT_TYPE(EventMouseButtonPressed)
};

class EventMouseButtonReleased : public Event {
private:
	int m_button, m_mode;
public:
	EventMouseButtonReleased(int button, int mode) :
		m_button(button), m_mode(mode) {
	}
	int GetButton() const { return m_button; }
	int GetMode() const { return m_mode; }
	SUB_EVENT_TYPE(EventMouseButtonReleased)
};

class EventMouseScroll : public Event {
private:
	double m_xoffset, m_yoffset;
public:
	EventMouseScroll(double xoffset, double yoffset) :
		m_xoffset(xoffset), m_yoffset(yoffset) {
	}
	double GetXoffset() const { return m_xoffset; }
	double GetYoffset() const { return m_yoffset; }

	SUB_EVENT_TYPE(EventMouseScroll)
};
