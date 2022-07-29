#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug-System/OpenGLDebugger.h"
#include "../Logger/Logger.h"

namespace Architect
{
	void Renderer::Begin(Camera camera, glm::mat4 cameraTransform)
	{
		m_DrawCalls.clear();
		m_Camera = camera;
		m_CameraTransform = cameraTransform;
	}

	void Renderer::Begin(Camera camera, glm::mat4 cameraTransform, std::shared_ptr<Framebuffer> framebuffer)
	{
		m_ActiveFrameBuffer = framebuffer;
		Begin(camera, cameraTransform); 
	}

	void Renderer::AddDrawCall(MannagedVertexArray& va, std::shared_ptr<IndexBuffer> ib, Material& mat, glm::mat4& transform, int id)
	{
		m_DrawCalls.emplace_back(va, ib, mat, transform, id);
	}

	void Renderer::End()
	{
		if (m_ActiveFrameBuffer != nullptr)
		{
			m_ActiveFrameBuffer->Bind();
		}

		for (DrawCallData& data : m_DrawCalls)
		{
			data.VertexArray.Bind();
			data.IndexBuffer->Bind();
			data.Mat.Bind();

			glm::mat4 viewProjection = m_Camera.GetProjectionMatrix() * glm::inverse(m_CameraTransform);
			glm::mat4 mvp = viewProjection * (data.Transform);

			data.Mat.GetShader()->SetShaderUniformMat4f("u_MVP", mvp);
			data.Mat.GetShader()->SetShaderUniformInt("u_EntityID", data.ID);

			int indiciesCount = data.IndexBuffer->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}

		if (m_ActiveFrameBuffer != nullptr)
		{
			m_ActiveFrameBuffer->Unbind();
			m_ActiveFrameBuffer = nullptr;
		}
	}
}
