#include "EditorLayer.h"
#include "Entity-Component-System/SceneManager.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Core/Application.h"
#include "Entity-Component-System/EntityNativeScript.h"
#include "User-Input/Input.h"
#include "Editor-UI/ConsoleWindow.h"
#include "Editor-UI/EditorViewportWindow.h"
#include "Editor-UI/HierarchyWindow.h"
#include "Editor-Utils/EditorSelection.h"
#include "Editor-UI/InspectorEditorWindow.h"
#include <functional>
#include "Entity-Component-System/Entity-Systems/EntitySystems.h"
#include "Entity-Component-System/Entity-Systems/SpriteRendererSystem.h"
#include "Entity-Component-System/Entity-Systems/ScriptUpdateSystem.h"
#include "Entity-Component-System/Entity-Systems/TransformUpdateMatrixSystem.h"
#include "Entity-Component-System/HierarchyUtils.h"
#include "Mathmatics/Math.h"
#include "Editor-Utils/EditorSettings.h"

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

            if (Input::GetKey(KeyCode::Q))
            {
                GetEntity().GetTransform().Rotate({ 0, 0, -timestep * 40 });
            }

            if (Input::GetKey(KeyCode::E))
            {
                GetEntity().GetTransform().Rotate({ 0, 0, timestep * 40 });
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

        Entity e = scene->CreateEntity("Test Entity 1");
        e.AddComponent<SpriteRendererComponent>(mat);
        e.AddComponent<NativeScriptComponent>().Bind<MoveScript>();

        Entity e2 = scene->CreateEntity("Test Entity 2");
        e2.AddComponent<SpriteRendererComponent>(mat);
        e2.GetTransform().Dilate(0.5f);
        e2.GetTransform().Translate({ 0, -1.5f, 0 });

        Camera camera = Camera(4.0f / 3.0f, 2);
        m_CameraEntity = scene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>(camera);

        EditorWindow::AddWindow(std::make_shared<EditorViewportWindow>());
        EditorWindow::AddWindow(std::make_shared<ConsoleWindow>());
        EditorWindow::AddWindow(std::make_shared<HierarchyWindow>());
        EditorWindow::AddWindow(std::make_shared<InspectorEditorWindow>());

        auto transformSystem = std::make_shared<TransformUpdateMatrixSystem>();
        m_EditorSystems.push_back(transformSystem->GetName());

        EntitySystems::AddRenderSystem(std::make_shared<SpriteRendererSystem>());
        EntitySystems::AddUpdateSystem(transformSystem);
        EntitySystems::AddUpdateSystem(std::make_shared<ScriptUpdateSystem>());

        EditorSettings::GetSettings().Mode = EditorMode::Edit;
	}

	void EditorLayer::OnUpdate(float timestep)
	{
        EditorSettings settings = EditorSettings::GetSettings();

        if(settings.Mode == EditorMode::Play && !settings.IsPaused)
            EntitySystems::OnUpdate(SceneManager::GetActiveScene(), timestep);

        if (settings.Mode == EditorMode::Edit)
        {
            EntitySystems::OnUpdate(SceneManager::GetActiveScene(), timestep,
                [&](std::shared_ptr<UpdateEntitySystem> system)
                {
                    return std::find(m_EditorSystems.begin(), m_EditorSystems.end(), system->GetName()) != m_EditorSystems.end();
                });
        }
        
        
        
        EditorWindow::UpdateWindows(timestep);
	}

    void EditorLayer::OnImGuiRender(float timestep)
    {
        DrawMainMenu();
        DrawDockSpace();
        static bool isOpen = true;
        ImGui::ShowDemoWindow(&isOpen);
        EditorWindow::RenderWindows();
    }

    bool EditorLayer::OnEvent(IApplicationEvent* appEvent)
    {
        return false;
    }

    void EditorLayer::OnActiveSceneChanged(std::shared_ptr<Scene> scene)
    {

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