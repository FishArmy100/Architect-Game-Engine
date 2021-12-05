#pragma once
#include "Rendering.h"


namespace Architect
{
	struct DrawCallData
	{
	public:
		DrawCallData(VertexArray& VertexArray, IndexBuffer& IndexBuffer, Shader& DrawShader)
		{
			vertexArray = &VertexArray;
			indexBuffer = &IndexBuffer;
			shader = &DrawShader;
		}

		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		Shader* shader;
	};

	class Renderer
	{
	private:
		std::vector<DrawCallData> DrawCalls;

	public:
		void AddDrawCall(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader);
		void Draw();
	};
}

