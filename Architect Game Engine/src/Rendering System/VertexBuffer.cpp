#include "VertexBuffer.h"
#include "GL/glew.h"
#include"../Debug System/OpenGLDebugger.h"

namespace Architect
{
	VertexBuffer::VertexBuffer(const void* data, unsigned int sizeInBytes)
	{
		GLCall(glGenBuffers(1, &BufferId));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferId));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, BufferId));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &BufferId))
	}
}