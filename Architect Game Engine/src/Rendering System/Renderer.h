#pragma once
#include "Rendering.h"

namespace Architect
{
	struct DrawCallData
	{
	public:
		DrawCallData(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& drawMaterial)
		{
			m_VertexArray = &vertexArray;
			m_IndexBuffer = &indexBuffer;
			m_Material = &drawMaterial;
		}

		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		Material* m_Material;
	};

	class Renderer
	{
	private:
		std::vector<DrawCallData> DrawCalls;

	public:
		void AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Material& material);
		void Draw();
	};
}

