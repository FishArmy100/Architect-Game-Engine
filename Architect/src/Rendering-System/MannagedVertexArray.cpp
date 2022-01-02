#include "MannagedVertexArray.h"

namespace Architect
{
	MannagedVertexArray::MannagedVertexArray(const void* data, unsigned int sizeInBytes, VertexBufferLayout layout)
	{
		m_Buffer = std::make_shared<VertexBuffer>(data, sizeInBytes);
		m_Layout = layout;
		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->AddBuffer(*m_Buffer, layout);
	}

	void MannagedVertexArray::Bind() const
	{
		m_VertexArray->Bind();
	}

	void MannagedVertexArray::Unbind() const
	{
		m_VertexArray->Unbind();
	}
}