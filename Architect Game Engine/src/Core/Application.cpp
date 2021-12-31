#include "Application.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Logger/Logger.h"
#include <memory>
#include "Entity-Component-System/SceneManager.h"
#include "Core/Events.h"
#include "User-Input/Input.h"

namespace Architect
{
    Application* Application::s_Instance;

	Application::Application(const std::string& name)
	{
        Logger::Init();
		s_Instance = this;
        m_Window = Window::Create(620, 480);
        m_Window->GetWindowEventHandler().AddLisener(&Application::OnWindowEvent, this);
        Input::Init(m_Window);

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        SceneManager::AddOnActiveSceneChangedLisener([&]()
        {
            OnSceneChanged();
        });
	}

	Application::~Application()
	{
        
	}

	void Application::PushLayer(Layer* layer)
	{
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
	}

	void Application::Close()
	{
        m_Running = false;
	}

	void Application::Run()
	{
        m_Running = true;

        while (m_Running)
        {
            float time = (float)glfwGetTime();
            float timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            m_Window->Clear();

            for (int i = 0; i < m_LayerStack.GetLength(); i++)
            {
                m_LayerStack.GetLayer(i)->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin(); 
            for (int i = 0; i < m_LayerStack.GetLength(); i++)
            {
                m_LayerStack.GetLayer(i)->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->Update();
        }
	}

    void Application::OnSceneChanged()
    {
        for (int i = 0; i < m_LayerStack.GetLength(); i++)
        {
            m_LayerStack.GetLayer(i)->OnActiveSceneChanged(SceneManager::GetActiveScene());
        }
    }

    void Application::OnWindowEvent(IWindowEvent* windowEvent)
    {
        OnEvent(windowEvent);

        if (WindowCloseEvent* e = dynamic_cast<WindowCloseEvent*>(windowEvent))
            Close();

        //ARC_ENGINE_INFO(windowEvent->GetDebugString());
    }

    void Application::OnEvent(IApplicationEvent* appEvent)
    {
        for (int i = m_LayerStack.GetLength() - 1; i >= 0; i--)
        {
            if(appEvent->IsHandled)
                m_LayerStack.GetLayer(i)->OnEvent(appEvent);
        }
    }
}
