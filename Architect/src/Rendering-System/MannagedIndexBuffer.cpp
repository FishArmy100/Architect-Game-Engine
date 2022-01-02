#include "MannagedIndexBuffer.h"

namespace Architect
{
	MannagedIndexBuffer::MannagedIndexBuffer(const unsigned int* indicies, int count)
	{
		m_Buffer = std::make_shared<IndexBuffer>(indicies, count);
	}

	void MannagedIndexBuffer::Bind() const
	{
		m_Buffer->Bind();
	}

	void MannagedIndexBuffer::Unbind() const
	{
		m_Buffer->Unbind();
	}
}
