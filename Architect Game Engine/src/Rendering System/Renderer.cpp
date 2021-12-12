#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug System/OpenGLDebugger.h"
#include "../Logger/Logger.h"
#include "Camera.h"

namespace Architect
{
	void Renderer::AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& material, glm::mat4& transform)
	{
		DrawCallData data = DrawCallData(vertexArray, indexBuffer, material, transform);
		DrawCalls.emplace_back(data);
	}

	void Renderer::Draw()
	{
		if (Camera::GetMainCamera() == nullptr)
		{
			ARC_ENGINE_ERROR("No Camera Exists");
			DrawCalls.clear();
			return;
		}

		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (DrawCallData& data : DrawCalls)
		{
			data.m_VertexArray->Bind();
			data.m_IndexBuffer->Bind();
			data.m_Material->Bind();

			glm::mat4 viewProjection = Camera::GetMainCamera()->GetViewProjection();
			glm::mat4 mvp = viewProjection * (*data.m_Transform);

			data.m_Material->GetShader()->SetShaderUniformMat4f("u_MVP", mvp);

			int indiciesCount = data.m_IndexBuffer->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}

		DrawCalls.clear();
	}
}
