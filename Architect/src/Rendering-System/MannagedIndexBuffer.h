#pragma once
#include "IndexBuffer.h"
#include <memory>

namespace Architect
{
	class MannagedIndexBuffer
	{
	private:
		std::shared_ptr<IndexBuffer> m_Buffer;

	public:
		MannagedIndexBuffer(const unsigned int* indicies, int count);
		MannagedIndexBuffer() = default;

		IndexBuffer* GetBuffer() { return m_Buffer.get(); }

		void Bind() const;
		void Unbind() const;
	};
}

