#include "Logger/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Architect.h"

#include "User Input/InputSystem.h"
#include "User Input/GLFWInputHandler.h"
#include "Debug System/OpenGLDebugger.h"

#include "Rendering System/Rendering.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core.h"
#include "GameEngine.h"
#include "ExampleLayer.h"

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

        float positions[] = 
        {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
             0.5f, -0.5f, 1.0f, 0.0f, // 1
             0.5f,  0.5f, 1.0f, 1.0f, // 2
            -0.5f,  0.5f, 0.0f, 1.0f  // 3
        };

        unsigned int indicies[6] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        { // will delete vertex buffer before glfwTerminate()
            VertexBuffer vb = VertexBuffer(positions, 16 * sizeof(float));

            VertexArray va;

            VertexBufferLayout layout = VertexBufferLayout();
            layout.PushFloats(2, false);
            layout.PushFloats(2, true);

            va.AddBuffer(vb, layout);

            IndexBuffer ib = IndexBuffer(indicies, 6);

            std::shared_ptr<Shader> shader = Shader::CreateFromFile("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\shaders\\Test.shader");

            glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

            //shader->SetShaderUniformMat4f("u_MVP", proj);

            ARC_ENGINE_INFO("Contians uniform: {0}", shader->ContainsUniform("u_MVP", ShaderUniformType::Mat4x4f));

            vb.Unbind();
            ib.Unbind();
            shader->Unbind();
            va.Unbind();

            Camera camera(-2.0f, 2.0f, -1.5f, 1.5f);
            camera.SetPosition(glm::vec3(1, 0, 0));
            Renderer renderer;

            Texture* texture = new Texture("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\images\\CalvinAndHobbs.png");

            Material mat = Material(shader);
            mat.SetTexture("u_Texture", std::shared_ptr<Texture>(texture));

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                onUpdate();

                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
                renderer.AddDrawCall(va, ib, mat, transform);
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