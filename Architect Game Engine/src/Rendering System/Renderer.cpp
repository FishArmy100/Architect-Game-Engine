#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug System/OpenGLDebugger.h"

namespace Architect
{
	void Renderer::AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& material)
	{
		DrawCallData data = DrawCallData(vertexArray, indexBuffer, material);
		DrawCalls.emplace_back(data);
	}

	void Renderer::Draw()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (DrawCallData& data : DrawCalls)
		{
			data.m_VertexArray->Bind();
			data.m_IndexBuffer->Bind();
			data.m_Material->Bind();

			int indiciesCount = data.m_IndexBuffer->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}

		DrawCalls.clear();
	}
}
