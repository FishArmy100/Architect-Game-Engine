#include "Application.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Logger/Logger.h"
#include <memory>

#include "User-Input/InputSystem.h"
#include "User-Input/GLFWInputHandler.h"

#include "Entity-Component-System/SceneManager.h"
#include "Core/Events.h"


namespace Architect
{
    Application* Application::s_Instance;

	Application::Application(const std::string& name)
	{
		s_Instance = this;
        Logger::Init();
        InitializeOpenGL(m_Window);
        InitalizeInputSystem(m_Window);
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        SceneManager::AddOnActiveSceneChangedLisener([&]()
        {
            OnSceneChanged();
        });
	}

	Application::~Application()
	{
        ShutDownOpenGL();
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

        while (m_Running && !glfwWindowShouldClose(m_Window))
        {
            float time = (float)glfwGetTime();
            float timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

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

            // Temparary
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(Application::Get().GetWindow()));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
	}

	bool Application::InitializeOpenGL(GLFWwindow*& window)
	{
        /* Initialize the library */
        if (!glfwInit())
            return -1;

        ARC_ENGINE_INFO("Initialized GLFW");

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            //fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            ARC_ENGINE_ERROR("Problem: glewInit failed, something is seriously wrong");
            return false;
        }
        else
        {
            ARC_ENGINE_INFO("Initialized GLEW");
        }

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        return true;
	}

    void Application::ShutDownOpenGL()
    {
        ARC_ENGINE_INFO("Open GL shutting down");
        glfwTerminate();
    }

    void Application::InitalizeInputSystem(GLFWwindow* window)
    {
        std::shared_ptr<IInputHandler> handler = std::shared_ptr<IInputHandler>(new GLFWInputHandler(window));
        InputSystem::Init(handler);
    }

    void Application::OnSceneChanged()
    {
        for (int i = 0; i < m_LayerStack.GetLength(); i++)
        {
            m_LayerStack.GetLayer(i)->OnActiveSceneChanged(SceneManager::GetActiveScene());
        }
    }
}
