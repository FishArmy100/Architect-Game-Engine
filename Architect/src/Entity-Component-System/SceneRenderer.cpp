#include "SceneRenderer.h"

namespace Architect
{
	void SceneRenderer::RenderScene(std::shared_ptr<Scene> scene)
	{
        float positions[16] =
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

        scene->GetEntitiesWithComponent<SpriteRendererComponent>([&](Entity e, SpriteRendererComponent src)
        {
            OnSpriteEntity(e, src, indicies, positions);
        });
	}

    void SceneRenderer::OnSpriteEntity(Entity e, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16])
    {
        if (!e.IsActive())
            return;

        VertexBufferLayout layout = VertexBufferLayout();
        layout.PushFloats(2, false);
        layout.PushFloats(2, true);

        std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(indicies, 6);
        MannagedVertexArray va = MannagedVertexArray(positions, 16 * sizeof(float), layout);

        va.Unbind();
        ib->Unbind();

        glm::mat4 transformMatrix = e.GetTransform().GetTransformMatrix();
        Renderer::AddDrawCall(va, ib, spriteRenderer.SpriteMaterial, transformMatrix, (int)(entt::entity)e);
    }
}

