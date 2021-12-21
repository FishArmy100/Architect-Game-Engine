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
#include "Entity-Component-System/Entity-Components/Basic-Components.h"
#include "Entity-Component-System/Entity.h"
#include "Entity-Component-System/EntitySystem.h"
#include "Entity-Component-System/Entity-Systems/SpriteRendererSystem.h"

#include "Entity-Component-System/Entity-Systems/ScriptUpdateSystem.h"

namespace Architect
{
    bool InitializeOpenGL(GLFWwindow*& window);
    void InitalizeInputSystem(GLFWwindow* window);

    class MoveScript : public EntityNativeScript
    {
    public:
        MoveScript() {}
        ~MoveScript() {}

        void OnUpdate(float timeStep) override
        {
            if(Input::GetKeyDown(KeyCode::Space))
                GetEntity().GetTransform().Translate({ timeStep * 0.1f, 0, 0 });
        }

        void OnDestroy() override
        {
            ARC_INFO("Move Script Destroied");
        }
    };

    class MoveScript2 : public EntityNativeScript
    {
    public:
        MoveScript2() {}
        ~MoveScript2() {}

        void OnUpdate(float timeStep) override
        {
            if (Input::GetKeyDown(KeyCode::Tab))
                GetEntity().GetTransform().Translate({ -timeStep * 0.1f, 0, 0 });
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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        { // will delete vertex buffer before glfwTerminate()

            std::shared_ptr<Shader> shader = Shader::CreateFromFile("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\shaders\\Test.shader");

            shader->Unbind();

            Texture* texture = new Texture("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\images\\CalvinAndHobbs.png");

            Material mat = Material(shader);
            mat.SetTexture("u_Texture", std::shared_ptr<Texture>(texture));


            Camera camera(-2.0f, 2.0f, -1.5f, 1.5f);
            camera.SetPosition(glm::vec3(0, 0, 0));

            Renderer* renderer = new Renderer();

            GameWorld gameWorld;

            Scene* scene = new Scene;
            gameWorld.AddScene(scene);

            Entity e = scene->CreateEntity("Test Entity");
            e.AddComponent<SpriteRendererComponent>(mat);
            e.AddComponent<NativeScriptComponent>().AddScript<MoveScript>();
            e.GetComponent<NativeScriptComponent>().AddScript<MoveScript2>();
            
            e.GetTransform().Translate({ -1.0f, 0.0f, 0.0f });

            gameWorld.AddEntitySystem(new ScriptUpdateSystem());
            gameWorld.AddEntitySystem(new SpriteRendererSystem(renderer));

            float lastFrameTime = 0;

            UI::ExampleWindow exampleWindow = UI::ExampleWindow("Example Window");

            /* Loop until the user closes the window */
            while (!glfwWindowShouldClose(window))
            {
                onUpdate();

                float time = (float)glfwGetTime();
                float deltaTime = time - lastFrameTime;
                lastFrameTime = time;

                gameWorld.UpdateSystems(deltaTime); 
                renderer->Draw();
                e.RemoveComponent<NativeScriptComponent>();

                UI::GUI::StartFrame();
                exampleWindow.RenderWindow();
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