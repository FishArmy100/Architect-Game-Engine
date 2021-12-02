#include "VertexBufferLayout.h"
#include "GL/glew.h"

namespace Architect
{
	VertexBufferLayout::VertexBufferLayout()
	{
		Stride = 0;
	}

	void VertexBufferLayout::PushFloats(int count, bool normalized)
	{
		Elements.emplace_back(count, GL_FLOAT, normalized, sizeof(GLfloat));
		Stride += count * sizeof(GLfloat);
	}

	void VertexBufferLayout::PushUnsignedInts(int count)
	{
		Elements.emplace_back(count, GL_UNSIGNED_INT, false, sizeof(GLfloat));
		Stride += count * sizeof(GLuint);
	}
}