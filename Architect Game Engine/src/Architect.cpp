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

    static unsigned int CompileShader(const std::string& source, unsigned int type)
    {
        unsigned int id = glCreateShader(type);
        const char* rawString = source.c_str();
        glShaderSource(id, 1, &rawString, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            ARC_ENGINE_ERROR("Failed to Compile Shader: {0}", message);
            return 0;
        }

        return id;
    }

    static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

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

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

            IndexBuffer ib = IndexBuffer(indicies, 6);

            std::string vertexShader =
                "#version 330 core\n"
                "\n"
                "layout(location = 0) in vec4 position;\n"
                "\n"
                "void main()\n"
                "{\n"
                "   gl_Position = position;\n"
                "}\n";

            std::string fragmentShader =
                "#version 330 core\n"
                "\n"
                "layout(location = 0) out vec4 color;\n"
                "\n"
                "void main()\n"
                "{\n"
                "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                "}\n";

            unsigned int shader = CreateShader(vertexShader, fragmentShader);
            glUseProgram(shader);

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                onUpdate();

                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw call 

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
            }

            glDeleteProgram(shader);
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