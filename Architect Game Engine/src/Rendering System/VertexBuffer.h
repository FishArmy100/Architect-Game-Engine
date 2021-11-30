#pragma once

namespace Architect
{
	class VertexBuffer
	{
	private:
		unsigned int BufferId;

	public:
		VertexBuffer(const void* data, unsigned int sizeInBytes);
		void Bind() const;
		void Unbind() const;
		~VertexBuffer();
	};
}

