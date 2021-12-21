#include "SpriteRendererSystem.h"
#include "Rendering-System/Rendering.h"

namespace Architect
{
    SpriteRendererSystem::SpriteRendererSystem(Renderer* renderer)
    {
        m_Renderer = renderer;
    }

    void SpriteRendererSystem::OnUpdate(float timeStep)
	{
        ARC_ENGINE_INFO("Time Step: {0}", timeStep);

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

        RunFuncOnEntites<TransformComponent, SpriteRendererComponent>([&](TransformComponent& t, SpriteRendererComponent& sr) 
        {
            OnEntity(t, sr, indicies, positions);
        });
	}

    void SpriteRendererSystem::OnEntity(TransformComponent& transform, SpriteRendererComponent& spriteRenderer, unsigned int indicies[6], float positions[16])
    {
        VertexBuffer* vb = new VertexBuffer(positions, 16 * sizeof(float));

        VertexBufferLayout layout = VertexBufferLayout();
        layout.PushFloats(2, false);
        layout.PushFloats(2, true);

        IndexBuffer* ib = new IndexBuffer(indicies, 6);

        vb->Unbind();
        ib->Unbind();

        DrawCallData* data = new DrawCallData(vb, layout, ib, spriteRenderer.SpriteMaterial, transform.GetTransformMatrix());
        m_Renderer->AddDrawCall(data);
    }
}