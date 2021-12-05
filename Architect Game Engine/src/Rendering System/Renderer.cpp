#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug System/OpenGLDebugger.h"

namespace Architect
{
	void Renderer::AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader)
	{
		DrawCallData data = DrawCallData(vertexArray, indexBuffer, shader);
		DrawCalls.emplace_back(data);
	}

	void Renderer::Draw()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (DrawCallData& data : DrawCalls)
		{
			data.vertexArray->Bind();
			data.indexBuffer->Bind();
			data.shader->Bind();

			int indiciesCount = data.indexBuffer->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}

		DrawCalls.clear();
	}
}
