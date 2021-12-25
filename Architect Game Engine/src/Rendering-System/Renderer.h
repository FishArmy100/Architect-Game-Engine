#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include <vector>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Core.h"

namespace Architect
{
	struct DrawCallData
	{
	public:
		DrawCallData(VertexBuffer* vertexBuffer, VertexBufferLayout layout, IndexBuffer* indexBuffer, Material drawMaterial, glm::mat4 transform)
		{
			m_VertexBuffer = vertexBuffer;
			m_Layout = layout;
			m_IndexBuffer = indexBuffer;
			m_Material = drawMaterial;
			m_Transform = transform;

			m_VertexArray = new VertexArray();
			m_VertexArray->AddBuffer(*vertexBuffer, layout);
		}

		VertexBuffer* m_VertexBuffer;
		VertexBufferLayout m_Layout;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Material m_Material;
		glm::mat4 m_Transform;

		~DrawCallData()
		{
			delete m_VertexBuffer;
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	};

	class Renderer
	{
	private:
		std::vector<DrawCallData*> m_DrawCalls;
		void DeleteDrawCalls();

		Camera* m_Camera;
		glm::mat4 m_CameraTransform;

	public:
		Renderer(Camera* camera, glm::mat4 cameraTransform);
		~Renderer();

		void AddDrawCall(DrawCallData* drawCallData);
		void Draw();
		void SetCamera(Camera* camera, glm::mat4 transform);
	};
}

