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
	int mWidth; // ���ڿ�
	int mHeight; // ���ڸ�
	std::string mTitle; // ���ڱ���

	// ����״̬��
	char mKeys[KeysLen];

	// ��һ�δ��ڸ���ʱ��
	double mLastUpdateTime;

	// GLFW �Ĵ��ڶ���
	GLFWwindow* mWindow;

	// ע����¼��ص�����
	std::vector<std::function<void(Event&)>> mHandlers;

	// ��ʼ�� GLFW ���ڡ�ע�� GLFW ���¼��ص�
	void InitWindow();
	// ͳһ���� GLFW ���¼��ص����ַ�����ں���
	void OnEventCallback(Event&);
	// ������ѯ�������
	void ProcessKeys();

	// ͳһ���� Window ���¼�
	void OnEvent(Event&);
	// ���� Window �Ŀ��
	void OnEventWindowSize(EventWindowSize&);
public:
	Window(int width = 1280, int height = 960, const std::string& title = "Hello Triangle")
		: mWidth(width), mHeight(height), mTitle(title), mKeys{} {
		InitWindow();
		RegisterHandler(std::bind(&Window::OnEvent, this, std::placeholders::_1));
	}

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	// ÿһ����Ⱦ����Ҫ����
	void OnUpdate();

	// ����
	void Clear();

	~Window();

	// ע��ҵ�񷽵��¼��ص�����
	void RegisterHandler(std::function<void(Event&)>);
};
