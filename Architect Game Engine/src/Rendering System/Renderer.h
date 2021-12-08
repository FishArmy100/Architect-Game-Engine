#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include <vector>
#include <glm/glm.hpp>

namespace Architect
{
	struct DrawCallData
	{
	public:
		DrawCallData(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& drawMaterial, glm::mat4& transform)
		{
			m_VertexArray = &vertexArray;
			m_IndexBuffer = &indexBuffer;
			m_Material = &drawMaterial;
			m_Transform = &transform;
		}

		glm::mat4* m_Transform;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Material* m_Material;
	};

	class Renderer
	{
	private:
		std::vector<DrawCallData> DrawCalls;

	public:
		void AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& material, glm::mat4& transform);
		void Draw();
	};
}

