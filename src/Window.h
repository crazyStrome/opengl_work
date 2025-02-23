#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <functional>
#include <unordered_map>

#include "events/Event.h"

const int KeysLen = GLFW_KEY_LAST + 1;

class Window {
	//GLFW_KEY_0
private:
	int mWidth; // 窗口宽
	int mHeight; // 窗口高
	std::string mTitle; // 窗口标题

	// 按键状态表
	char mKeys[KeysLen];

	// 上一次窗口更新时间
	double mLastUpdateTime;

	// GLFW 的窗口对象
	GLFWwindow* mWindow;

	// 注册的事件回调函数
	std::vector<std::function<void(Event&)>> mHandlers;

	// 初始化 GLFW 窗口、注册 GLFW 的事件回调
	void InitWindow();
	// 统一接收 GLFW 的事件回调并分发的入口函数
	void OnEventCallback(Event&);
	// 主动轮询按键情况
	void ProcessKeys();

	// 统一接收 Window 的事件
	void OnEvent(Event&);
	// 更新 Window 的宽高
	void OnEventWindowSize(EventWindowSize&);
public:
	Window(int width = 1280, int height = 960, const std::string& title = "Hello Triangle")
		: mWidth(width), mHeight(height), mTitle(title), mKeys{} {
		InitWindow();
		RegisterHandler(std::bind(&Window::OnEvent, this, std::placeholders::_1));
	}

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	// 每一次渲染后都需要更新
	void OnUpdate();

	// 清屏
	void Clear();

	~Window();

	// 注册业务方的事件回调函数
	void RegisterHandler(std::function<void(Event&)>);
};
