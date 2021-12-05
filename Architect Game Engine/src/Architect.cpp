#include "raylib.h"
#include "WindowsDefines.h" // fixes nameing issues with windows.h and raylib, also must be included after raylib
#include "Logger/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Architect.h"

#include "User Input/InputSystem.h"
#include "User Input/GLFWInputHandler.h"
#include "Debug System/OpenGLDebugger.h"

#include "Rendering System/Rendering.h"

namespace Architect
{
    bool InitializeOpenGL(GLFWwindow*& window);
    void InitalizeInputSystem(GLFWwindow* window);

    bool Init(void (*onUpdate)())
    {
        Logger::Init();

        GLFWwindow* window;

        bool initalized = InitializeOpenGL(window);
        if (!initalized)
            return false;

        InitalizeInputSystem(window);

        float positions[8] = 
        {
            -0.5f, -0.5,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        };

        unsigned int indicies[6] =
        {
            0, 1, 2,
            2, 3, 0
        };

        { // will delete vertex buffer before glfwTerminate()
            VertexBuffer vb = VertexBuffer(positions, 8 * sizeof(float));

            VertexArray va;

            VertexBufferLayout layout = VertexBufferLayout();
            layout.PushFloats(2, false);

            va.AddBuffer(vb, layout);

            IndexBuffer ib = IndexBuffer(indicies, 6);

            Shader shader = Shader::CreateFromFile("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\shaders\\Test.shader");

            vb.Unbind();
            ib.Unbind();
            shader.Unbind();
            va.Unbind(); 

            shader.SetShaderUniformV4("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

            Renderer renderer;

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                onUpdate();

                renderer.AddDrawCall(va, ib, shader);
                renderer.Draw();

                /* Swap front and back buffers */
                GLCall(glfwSwapBuffers(window));

                /* Poll for and process events */
                GLCall(glfwPollEvents());
            }
        }
        glfwTerminate();
        ARC_ENGINE_INFO("Architect shutting down");
        return true;
    }

    void InitalizeInputSystem(GLFWwindow* window)
    {
        std::shared_ptr<IInputHandler> handler = std::shared_ptr<IInputHandler>(new GLFWInputHandler(window));
        InputSystem::Init(handler);
    }

    bool InitializeOpenGL(GLFWwindow*& window)
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
        return true;
    }
}