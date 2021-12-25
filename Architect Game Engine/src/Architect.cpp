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

        void OnCreate() override
        {
            ARC_INFO("Move Script Created");
        }

        void OnUpdate(float timeStep) override
        {
            if(Input::GetKeyDown(KeyCode::W))
                GetEntity().GetTransform().Translate({ 0, timeStep * 0.1f, 0 });

            if (Input::GetKeyDown(KeyCode::A))
                GetEntity().GetTransform().Translate({ -timeStep * 0.1f, 0, 0 });

            if (Input::GetKeyDown(KeyCode::S))
                GetEntity().GetTransform().Translate({ 0, -timeStep * 0.1f, 0 });

            if (Input::GetKeyDown(KeyCode::D))
                GetEntity().GetTransform().Translate({ timeStep * 0.1f, 0, 0 });
        }

        void OnDestroy() override
        {
            ARC_INFO("Move Script Destroied");
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

            Camera* camera = new Camera(-2.0f, 2.0f, -1.5f, 1.5f);

            Renderer* renderer = new Renderer(camera, glm::mat4(1.0f));

            GameWorld gameWorld;

            Scene* scene = new Scene;
            gameWorld.AddScene(scene);

            Entity e = scene->CreateEntity("Test Entity");
            e.AddComponent<SpriteRendererComponent>(mat);
            //e.AddComponent<NativeScriptComponent>().Bind<MoveScript>();
            
            //e.GetTransform().Translate({ -1.0f, 0.0f, 0.0f });
            e.GetTransform().Rotate({ 0, 0, 45 });

            Entity cameraEntity = scene->CreateEntity("Camera");
            cameraEntity.AddComponent<CameraComponent>(camera);
            cameraEntity.AddComponent<NativeScriptComponent>().Bind<MoveScript>();

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

                glm::mat4 cameraTransform = cameraEntity.GetTransform().GetTransformMatrix();
                Camera* camera = cameraEntity.GetComponent<CameraComponent>().Camera;
                renderer->SetCamera(camera, cameraTransform);

                renderer->Draw(); 

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