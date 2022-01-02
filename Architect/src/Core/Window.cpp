#include "Window.h"
#include "Debug-System/OpenGLDebugger.h"
#include "WindowEvents.h"

namespace Architect
{
	bool Window::s_GLFWInitialized = false;

	Window* Window::Create(unsigned int width, unsigned int height, const std::string& title)
	{
        GLFWwindow* window = CreateGLFWWindow(width, height, title);
        return new Window(window, title);
	}

	Window::~Window()
	{
        glfwTerminate();
	}

    Window::Window(GLFWwindow* window, const std::string& title)
    {
        m_Window = window;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        m_WindowData = WindowData(width, height, title, [&](IWindowEvent* eventData, std::function<void(IWindowEvent*)> deleteFunc) 
        {
            m_WindowEventHandler.Invoke(eventData);
            deleteFunc(eventData);
        });

        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        InitilizeWindowEvents(m_Window);
    }

	void Window::Update()
	{
        GLCall(glfwSwapBuffers(m_Window));
        GLCall(glfwPollEvents());
        m_WindowUpdateEventHandler.Invoke();
	}

	void Window::Clear()
	{
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

    void Window::SetTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_Window, title.c_str());
        m_WindowData.Title = title;
        IWindowEvent* eventData = new WindowTitleRenamedEvent(title);
        m_WindowEventHandler.Invoke(eventData);
        delete (WindowTitleRenamedEvent*)eventData;
    }

    GLFWwindow* Window::CreateGLFWWindow(unsigned int width, unsigned int height, const std::string& title)
    {
        if (!s_GLFWInitialized)
        {
            if (!glfwInit())
            {
                ARC_ENGINE_ERROR("Could Not Initalize GLFW");
                return nullptr;
            }

            ARC_ENGINE_INFO("Initialized GLFW");
        }

        GLFWwindow* glfwWindow = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
        if (!glfwWindow)
        {
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(glfwWindow);

        if (!s_GLFWInitialized)
        {
            GLenum err = glewInit();
            if (GLEW_OK != err)
            {
                ARC_ENGINE_ERROR("Problem: glewInit failed, something is seriously wrong");
                return nullptr;
            }
            else
            {
                ARC_ENGINE_INFO("Initialized GLEW");
            }

            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
            s_GLFWInitialized = true;
        }

        return glfwWindow;
    }

    void Window::InitilizeWindowEvents(GLFWwindow* window)
    {
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
            windowData->Width = width;
            windowData->Height = height;
            windowData->OnWindowEvent(new WindowResizeEvent(width, height), 
                [](IWindowEvent* data) {delete (WindowResizeEvent*)data; });
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
            windowData->OnWindowEvent(new WindowCloseEvent(),
                [](IWindowEvent* data) {delete (WindowCloseEvent*)data; });
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                windowData->OnWindowEvent(new KeyPressedEvent(key, scancode, mods),
                    [](IWindowEvent* data) {delete (KeyPressedEvent*)data; });
                break;
            case GLFW_RELEASE:
                windowData->OnWindowEvent(new KeyRelesedEvent(key, scancode, mods),
                    [](IWindowEvent* data) {delete (KeyRelesedEvent*)data; });
                break;
            case GLFW_REPEAT:
                windowData->OnWindowEvent(new KeyRepeatEvent(key, scancode, mods),
                    [](IWindowEvent* data) {delete (KeyRepeatEvent*)data; });
                break;
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
                windowData->OnWindowEvent(new MouseButtonPressedEvent(button, mods),
                    [](IWindowEvent* data) {delete (MouseButtonPressedEvent*)data; });
                break;
            case GLFW_RELEASE:
                windowData->OnWindowEvent(new MouseButtonReleasedEvent(button, mods),
                    [](IWindowEvent* data) {delete (MouseButtonReleasedEvent*)data; });
                break;
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
            windowData->OnWindowEvent(new MouseScrollEvent(xOffset, yOffset),
                [](IWindowEvent* data) {delete (MouseScrollEvent*)data; });
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
            windowData->OnWindowEvent(new MouseMovedEvent(xPos, yPos),
                [](IWindowEvent* data) {delete (MouseMovedEvent*)data; });
        });
    }
}