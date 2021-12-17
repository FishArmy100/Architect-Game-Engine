#include "Logger/Logger.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/Architect.h"

#include "User-Input/InputSystem.h"
#include "User-Input/GLFWInputHandler.h"
#include "Debug-System/OpenGLDebugger.h"

#include "Rendering-System/Rendering.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GUI/GUI.h"
#include "GUI/ExampleWindow.h"

#include "Entity-Component-System/GameWorld.h"
#include "Entity-Component-System/Basic-Components/Basic-Components.h"
#include "Entity-Component-System/Entity.h"
#include "Entity-Component-System/EntitySystem.h"

namespace Architect
{
    bool InitializeOpenGL(GLFWwindow*& window);
    void InitalizeInputSystem(GLFWwindow* window);

    class TestSystem : public EntitySystem
    {
    protected:
        void OnUpdate() override 
        {
            RunFuncOnEntites<TagComponent>([](TagComponent& tag)
            {
                ARC_ENGINE_TRACE(tag.Tag);
            });
        }
    };

    class TestSystem2 : public EntitySystem
    {
    protected:
        void OnUpdate() override
        {
            RunFuncOnEntites<TagComponent, IsActiveComponent>([](TagComponent& tag, IsActiveComponent& test)
            {
                tag.Tag = "Empty";
            });
        }
    };

    bool Init(void (*onUpdate)())
    {
        Logger::Init();

        GLFWwindow* window;

        bool initalized = InitializeOpenGL(window);
        if (!initalized)
            return false;

        UI::GUI::Init(window);


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

            GameWorld gameWorld;

            Scene* scene = new Scene("Test Scene");
            scene->CreateEntity("Test Entity 1");
            scene->CreateEntity("Test Entity 2");
            scene->CreateEntity("Test Entity 3");
            scene->CreateEntity("Test Entity 4");

            gameWorld.AddScene(scene);

            EntitySystem* system1 = new TestSystem2();
            EntitySystem* system2 = new TestSystem();

            gameWorld.AddEntitySystem(system1);
            gameWorld.AddEntitySystem(system2);

            gameWorld.UpdateSystems();


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

            UI::GUIWindow* exampleWindow = new UI::ExampleWindow("Hello World");

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                onUpdate();

                UI::GUI::StartFrame();

                exampleWindow->RenderWindow();
                
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
                renderer.AddDrawCall(va, ib, mat, transform);
                renderer.Draw();

                UI::GUI::RenderFrame();

                /* Swap front and back buffers */
                GLCall(glfwSwapBuffers(window));

                /* Poll for and process events */
                GLCall(glfwPollEvents());
            }
        }

        UI::GUI::ShutDown(); 

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