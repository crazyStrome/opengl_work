#pragma once

#include "Window.h"
#include "Camera.h"

#include "events/Event.h"
#include "layers/LayerStack.h"

static const float defaultNearZpos = 0.1f;
static const float defaultFarZpos = 100.0f;

class Application
{
private:
	bool mShouldClose;

	Window mWindow;
	LayerStack mLayerStack;
	Camera mCamera;

	double mLastFrameUpdateTime;
	float mNearZpos = defaultNearZpos;
	float mFarZpos = defaultFarZpos;

	void OnEventKeyPressed(EventKeyPressed&);
	void OnEventWindowSize(EventWindowSize&);
public:
	Application();
	~Application();

	void Run();
	void OnEvent(Event&);

	void AddLayer(Layer*);
};

