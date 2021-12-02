#pragma once
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Architect
{
	class VertexArray
	{
	private:
		unsigned int VertexArrayID;

	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(VertexBuffer& buffer, VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;
	};
}

