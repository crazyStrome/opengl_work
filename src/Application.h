#pragma once

#include "Window.h"
#include "Camera.h"

#include "events/Event.h"
#include "layers/LayerStack.h"

class Application
{
private:
	bool mShouldClose;

	Window mWindow;
	LayerStack mLayerStack;
	Camera mCamera;

	double mLastFrameUpdateTime;

	void OnEventKeyPressed(EventKeyPressed&);
	void OnEventWindowSize(EventWindowSize&);
public:
	Application();
	~Application();

	void Run();
	void OnEvent(Event&);

	void AddLayer(Layer*);
};

