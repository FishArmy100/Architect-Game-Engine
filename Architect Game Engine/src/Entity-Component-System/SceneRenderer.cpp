#include "SceneRenderer.h"

namespace Architect
{
	void SceneRenderer::RenderScene(Scene* scene, Renderer* renderer)
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
            OnSpriteEntity(t, sr, renderer, indicies, positions);
        });
	}

    void SceneRenderer::OnSpriteEntity(TransformComponent& transform, SpriteRendererComponent& spriteRenderer, Renderer* renderer, unsigned int indicies[6], float positions[16])
    {
        VertexBuffer* vb = new VertexBuffer(positions, 16 * sizeof(float));

        VertexBufferLayout layout = VertexBufferLayout();
        layout.PushFloats(2, false);
        layout.PushFloats(2, true);

        IndexBuffer* ib = new IndexBuffer(indicies, 6);

        vb->Unbind();
        ib->Unbind();

        DrawCallData* data = new DrawCallData(vb, layout, ib, spriteRenderer.SpriteMaterial, transform.GetTransformMatrix());
        renderer->AddDrawCall(data);
    }
}

