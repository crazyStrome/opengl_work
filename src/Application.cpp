#include "Application.h"
#include "events/EventDispatcher.h"

void Application::OnEventKeyPressed(EventKeyPressed& event)
{
    if (event.GetKey() == GLFW_KEY_ESCAPE) {
        mShouldClose = true;
    }
}

void Application::OnEventWindowSize(EventWindowSize& event)
{
    glViewport(0, 0, event.GetWidth(), event.GetHeight());
}

Application::Application()
    : mWindow(), mLayerStack(),
    mShouldClose(false), mCamera(),
    mLastFrameUpdateTime(0.0)
{
    mWindow.RegisterHandler(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    mWindow.RegisterHandler(std::bind(&Camera::OnEvent, &mCamera, std::placeholders::_1));
}

Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{
    while (!mShouldClose) {
        mWindow.Clear();

        LayerUpdateArgs args{
            mCamera.GetView(),
            mCamera.GetProjection(
                float(mWindow.GetWidth()) / float(mWindow.GetHeight()), 
                mNearZpos, mFarZpos),
            mWindow.GetWidth(),
            mWindow.GetHeight(),
            mNearZpos,
            mFarZpos,
        };

        for (auto begin = mLayerStack.Begin(); 
            begin != mLayerStack.End(); 
            ++begin) {
            (**begin).OnUpdate(args);
        }

        double curTime = glfwGetTime();
        if (mLastFrameUpdateTime == 0.0f) {
            mLastFrameUpdateTime = curTime;
        }
        double deltaTime = curTime - mLastFrameUpdateTime;
        mLastFrameUpdateTime = curTime;

        mCamera.OnUpdate(deltaTime);
        mWindow.OnUpdate();
    }
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<EventKeyPressed>(std::bind(&Application::OnEventKeyPressed, this, std::placeholders::_1));
    dispatcher.Dispatch<EventWindowSize>(std::bind(&Application::OnEventWindowSize, this, std::placeholders::_1));
}

void Application::AddLayer(Layer* layer)
{
    mLayerStack.PushLayer(layer);
    mWindow.RegisterHandler(std::bind(&Layer::OnEvent, layer, std::placeholders::_1));
}
