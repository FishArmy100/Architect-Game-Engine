#include "raylib.h"
#include "WindowsDefines.h" // fixes nameing issues with windows.h and raylib, also must be included after raylib
#include "Logger/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Architect.h"

namespace Architect
{
    bool InitializeOpenGL(GLFWwindow*& window);

    bool Init(void (*onUpdate)())
    {
        Logger::Init();

        GLFWwindow* window;

        bool initalized = InitializeOpenGL(window);
        if (!initalized)
            return false;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            onUpdate();

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(-0.0f, 0.5f);
            glVertex2f(0.5f, -0.5f);
            glEnd();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return true;
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