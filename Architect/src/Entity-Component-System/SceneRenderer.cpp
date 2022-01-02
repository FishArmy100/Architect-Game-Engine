#include "SceneRenderer.h"

namespace Architect
{
	void SceneRenderer::RenderScene(Scene* scene)
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

        scene->RunFuncOnEntites<TransformComponent, SpriteRendererComponent>([&](TransformComponent& t, SpriteRendererComponent& sr)
        {
            OnSpriteEntity(t, sr, indicies, positions);
        });
	}

    void SceneRenderer::OnSpriteEntity(TransformComponent& transform, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16])
    {
        VertexBufferLayout layout = VertexBufferLayout();
        layout.PushFloats(2, false);
        layout.PushFloats(2, true);

        MannagedIndexBuffer ib = MannagedIndexBuffer(indicies, 6);
        MannagedVertexArray va = MannagedVertexArray(positions, 16 * sizeof(float), layout);

        va.Unbind();
        ib.Unbind();

        glm::mat4 transformMatrix = transform.GetTransformMatrix();
        Renderer::AddDrawCall(va, ib, spriteRenderer.SpriteMaterial, transformMatrix);
    }
}

