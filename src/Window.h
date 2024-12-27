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
	// ��ʶ�Ƿ���Ҫ�رմ���
	bool mShouldClose = false;

	// ����״̬��
	char mKeys[KeysLen];

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
public:
	Window(int width = 1280, int height = 960, const std::string& title = "Hello Triangle")
		: mWidth(width), mHeight(height), mTitle(title), mKeys{} {
		InitWindow();
		RegisterHandler(std::bind(&Window::OnEvent, this, std::placeholders::_1));
	}

	// ÿһ����Ⱦ����Ҫ����
	void OnUpdate();
	bool ShouldClose() const;

	~Window();

	// ע��ҵ�񷽵��¼��ص�����
	void RegisterHandler(std::function<void(Event&)>);
	// ����ʹ�õ�һ���ص�����
	void OnEvent(Event&);
	// ���������ص�
	void OnEventKeyPressed(EventKeyPressed&);
};