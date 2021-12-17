#include "IndexBuffer.h"
#include "GL/glew.h"
#include "../Debug-System/OpenGLDebugger.h"
#include "../Logger/Logger.h"

namespace Architect
{
	IndexBuffer::IndexBuffer(const unsigned int* indicies, unsigned int count)
	{
		Count = count;

		GLCall(glGenBuffers(1, &BufferId));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indicies, GL_STATIC_DRAW));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferId));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &BufferId));
	}
}