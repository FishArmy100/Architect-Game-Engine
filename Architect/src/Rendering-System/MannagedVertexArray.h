#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <memory>

namespace Architect
{
	class MannagedVertexArray
	{
	private:
		std::shared_ptr<VertexBuffer> m_Buffer;
		std::shared_ptr<VertexArray> m_VertexArray;
		VertexBufferLayout m_Layout;

	public:
		MannagedVertexArray(const void* data, unsigned int sizeInBytes, VertexBufferLayout layout);
		MannagedVertexArray() = default;

		VertexBuffer* GetBuffer() const { return m_Buffer.get(); }
		VertexArray* GetVertexArray() const { return m_VertexArray.get(); }
		VertexBufferLayout GetLayout() const { return m_Layout; }

		void Bind() const;
		void Unbind() const;
	};
}

