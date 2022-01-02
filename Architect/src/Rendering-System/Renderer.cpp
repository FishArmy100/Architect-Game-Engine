#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug-System/OpenGLDebugger.h"
#include "../Logger/Logger.h"

namespace Architect
{
	std::vector<DrawCallData> Renderer::m_DrawCalls;
	Camera* Renderer::m_Camera;
	glm::mat4 Renderer::m_CameraTransform;

	void Renderer::Begin(Camera* camera, glm::mat4 cameraTransform)
	{
		m_DrawCalls.clear();
		m_Camera = camera;
		m_CameraTransform = cameraTransform;
	}

	void Renderer::AddDrawCall(MannagedVertexArray& va, MannagedIndexBuffer& ib, Material& mat, glm::mat4& transform)
	{
		m_DrawCalls.emplace_back(va, ib, mat, transform);
	}

	void Renderer::End()
	{
		for (DrawCallData& data : m_DrawCalls)
		{
			data.VertexArray.Bind();
			data.IndexBuffer.Bind();
			data.Mat.Bind();

			glm::mat4 viewProjection = m_Camera->GetProjectionMatrix() * glm::inverse(m_CameraTransform);
			glm::mat4 mvp = viewProjection * (data.Transform);

			data.Mat.GetShader()->SetShaderUniformMat4f("u_MVP", mvp);

			int indiciesCount = data.IndexBuffer.GetBuffer()->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}
	}
}
