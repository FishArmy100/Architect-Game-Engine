#include "VertexArray.h"
#include "GL/glew.h"
#include "../Debug-System/OpenGLDebugger.h"

namespace Architect
{
	VertexArray::VertexArray()
	{
		GLCall(glCreateVertexArrays(1, &VertexArrayID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &VertexArrayID));
	}

	void VertexArray::AddBuffer(VertexBuffer& buffer, VertexBufferLayout& layout)
	{
		Bind();
		buffer.Bind();

		const std::vector<VertexBufferLayoutElement> elements = layout.GetElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			
			GLboolean normalized = element.Normalized ? GL_TRUE : GL_FALSE;

			GLCall(glVertexAttribPointer(i, element.Count, element.Type, normalized, layout.GetStride(), (const void*)offset));

			offset += element.Count * element.TypeByteSize;
		}
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(VertexArrayID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
}