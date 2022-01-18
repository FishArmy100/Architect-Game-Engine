#include "EditorLayer.h"
#include "Entity-Component-System/SceneManager.h"
#include "Entity-Component-System/SceneRenderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Core/Application.h"
#include "Entity-Component-System/ScriptUpdator.h"
#include "Entity-Component-System/EntityNativeScript.h"
#include "User-Input/Input.h"
#include "Editor-UI/ConsoleWindow.h"
#include "Editor-UI/EditorViewportWindow.h"
#include "Editor-UI/HierarchyWindow.h"
#include "Editor-Utils/EditorSelection.h"
#include "Editor-UI/InspectorEditorWindow.h"
#include <functional>

namespace Editor
{
    using namespace Architect;

    class MoveScript : public EntityNativeScript
    {
    public:
        void OnCreate() override
        {
            ARC_ENGINE_TRACE("Script Created");
        }

        void OnUpdate(float timestep) override
        {
            if (Input::GetKey(KeyCode::A))
            {
                GetEntity().GetTransform().Translate({ -timestep / 2, 0, 0 });
            }

            if (Input::GetKey(KeyCode::D))
            {
                GetEntity().GetTransform().Translate({ timestep / 2, 0, 0 });
            }

            if (Input::GetKey(KeyCode::W))
            {
                GetEntity().GetTransform().Translate({ 0, timestep / 2, 0 });
            }

            if (Input::GetKey(KeyCode::S))
            {
                GetEntity().GetTransform().Translate({ 0, -timestep / 2, 0 });
            }
        }

        void OnDestroy() override
        {
            ARC_ENGINE_TRACE("Script Destroyed");
        }
    };

	void EditorLayer::OnAttach()
	{
        std::shared_ptr<Scene> scene = std::make_unique<Scene>();
        SceneManager::SetActiveScene(scene);

        std::shared_ptr<Shader> shader = Shader::CreateFromFile("C:\\dev\\Architect Game Engine\\Architect\\res\\shaders\\Test.shader");
        shader->Unbind();
        Texture* texture = new Texture("C:\\dev\\Architect Game Engine\\Architect\\res\\images\\CalvinAndHobbs.png");
        Material mat = Material(shader);
        mat.SetTexture("u_Texture", std::shared_ptr<Texture>(texture));

        Entity e = scene->CreateEntity("Test Entity");
        e.AddComponent<SpriteRendererComponent>(mat);
        e.AddComponent<NativeScriptComponent>().Bind<MoveScript>();

        Camera* camera = new Camera(4.0f / 3.0f, 2);
        m_CameraEntity = scene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>(camera);

        EditorWindow::AddWindow(std::make_shared<EditorViewportWindow>());
        EditorWindow::AddWindow(std::make_shared<ConsoleWindow>());
        EditorWindow::AddWindow(std::make_shared<HierarchyWindow>());
        EditorWindow::AddWindow(std::make_shared<InspectorEditorWindow>());
	}

	void EditorLayer::OnUpdate(float timestep)
	{
        ScriptUpdator::UpdateScripts(SceneManager::GetActiveScene(), timestep);

        std::function<void(Entity&, TransformComponent&, TagComponent&)> func;

        func = [](Entity& e, TransformComponent& transform, TagComponent& tag)
        {
            ARC_ENGINE_INFO("Entity {3} is at position ({0}, {1}, {2})",
                transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z, (std::string)tag);
        };

        SceneManager::GetActiveScene()->GetEntitiesWithComponent(func);
	}

    void EditorLayer::OnImGuiRender(float timestep)
    {
        DrawMainMenu();
        DrawDockSpace();
        static bool isOpen = true;
        ImGui::ShowDemoWindow(&isOpen);
        EditorWindow::RenderWindows(timestep);
    }

    bool EditorLayer::OnEvent(IApplicationEvent* appEvent)
    {
        return false;
    }

    void EditorLayer::OnActiveSceneChanged(std::shared_ptr<Scene> scene)
    {
        scene->AddLisenerToOnComponentDestroyed<NativeScriptComponent>([](NativeScriptComponent& nsc)
        {
            ScriptUpdator::OnScriptDestroyed(nsc);
        });
    }

    void EditorLayer::DrawMainMenu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Editor Windows"))
            {
                if (ImGui::MenuItem("Console Window"))
                {
                    EditorWindow::AddWindow(std::make_shared<ConsoleWindow>());
                }
                if (ImGui::MenuItem("Viewport"))
                {
                    EditorWindow::AddWindow(std::make_shared<EditorViewportWindow>());
                }
                if (ImGui::MenuItem("Hierarchy"))
                {
                    EditorWindow::AddWindow(std::make_shared<HierarchyWindow>());
                }
                if (ImGui::MenuItem("Inspector"))
                {
                    EditorWindow::AddWindow(std::make_shared<InspectorEditorWindow>());
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void EditorLayer::DrawDockSpace()
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }
}