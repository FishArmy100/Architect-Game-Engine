#include "Renderer.h"
#include "GL/glew.h"
#include "../Debug-System/OpenGLDebugger.h"
#include "../Logger/Logger.h"

namespace Architect
{
	void Renderer::DeleteDrawCalls()
	{
		for (DrawCallData* data : m_DrawCalls)
			delete data;

		m_DrawCalls.clear();
	}


	Renderer::Renderer(Camera* camera, glm::mat4 cameraTransform)
		: m_Camera(camera), m_CameraTransform(cameraTransform)
	{

	}

	Renderer::~Renderer()
	{
	}

	void Renderer::AddDrawCall(DrawCallData* drawCallData)
	{
		m_DrawCalls.push_back(drawCallData);
	}

	void Renderer::Draw()
	{
		if (m_Camera == nullptr)
		{
			ARC_ENGINE_ERROR("Camera Not Set");
			DeleteDrawCalls();
			return;
		}

		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		for (DrawCallData*& data : m_DrawCalls)
		{
			data->m_VertexArray->Bind();
			data->m_IndexBuffer->Bind();
			data->m_Material.Bind();

			glm::mat4 viewProjection = m_Camera->GetProjectionMatrix() * glm::inverse(m_CameraTransform);
			glm::mat4 mvp = viewProjection * (data->m_Transform);

			data->m_Material.GetShader()->SetShaderUniformMat4f("u_MVP", mvp);

			int indiciesCount = data->m_IndexBuffer->GetCount();
			GLCall(glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, nullptr));
		}

		DeleteDrawCalls();
	}

	void Renderer::SetCamera(Camera* camera, glm::mat4 transform)
	{
		m_Camera = camera;
		m_CameraTransform = transform;
	}
}
