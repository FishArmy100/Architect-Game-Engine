#include "EditorLayer.h"
#include "Entity-Component-System/SceneManager.h"
#include "Entity-Component-System/SceneRenderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Application.h"
#include "Entity-Component-System/ScriptUpdator.h"
#include "Entity-Component-System/EntityNativeScript.h"
#include "User-Input/Input.h"

namespace Architect
{
    class MoveScript : public EntityNativeScript
    {
    public:
        void OnCreate() override
        {
            ARC_ENGINE_TRACE("Script Created");
        }

        void OnUpdate(float timestep) override
        {
            if (Input::GetKeyDown(KeyCode::A))
            {
                GetEntity().GetTransform().Translate({ -timestep / 2, 0, 0 });
            }

            if (Input::GetKeyDown(KeyCode::D))
            {
                GetEntity().GetTransform().Translate({ timestep / 2, 0, 0 });
            }

            if (Input::GetKeyDown(KeyCode::W))
            {
                GetEntity().GetTransform().Translate({ 0, timestep / 2, 0 });
            }

            if (Input::GetKeyDown(KeyCode::S))
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
		m_Renderer = new Renderer();

        Scene* scene = new Scene;
        SceneManager::SetActiveScene(scene);

        std::shared_ptr<Shader> shader = Shader::CreateFromFile("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\shaders\\Test.shader");
        shader->Unbind();
        Texture* texture = new Texture("C:\\dev\\Architect Game Engine\\Architect Game Engine\\res\\images\\CalvinAndHobbs.png");
        Material mat = Material(shader);
        mat.SetTexture("u_Texture", std::shared_ptr<Texture>(texture));

        Renderer* renderer = new Renderer();

        Entity e = scene->CreateEntity("Test Entity");
        e.AddComponent<SpriteRendererComponent>(mat);
        e.AddComponent<NativeScriptComponent>().Bind<MoveScript>();

        Camera* camera = new Camera(-2.0f, 2.0f, -1.5f, 1.5f);
        m_CameraEntity = scene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>(camera);

        m_ExampleWindow = new UI::ExampleWindow("Test Window");
	}

	void EditorLayer::OnUpdate(float timestep)
	{
        ScriptUpdator::UpdateScripts(SceneManager::GetActiveScene(), timestep);

        SceneRenderer::RenderScene(SceneManager::GetActiveScene(), m_Renderer);
        Camera* camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
        m_Renderer->Draw(camera, glm::mat4(1.0f));
	}

    void EditorLayer::OnImGuiRender()
    {
        m_ExampleWindow->RenderWindow();
    }

    void EditorLayer::OnActiveSceneChanged(Scene* scene)
    {
        scene->AddLisenerToOnComponentDestroyed<NativeScriptComponent>([](NativeScriptComponent& nsc)
        {
            ScriptUpdator::OnScriptDestroyed(nsc);
        });
    }
}