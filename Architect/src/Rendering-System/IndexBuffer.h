#pragma once

namespace Architect
{
	class IndexBuffer
	{
	private:
		unsigned int BufferId;
		unsigned int Count;

	public:
		IndexBuffer(const unsigned int* indicies, unsigned int count);
		IndexBuffer() = default;
		IndexBuffer(const IndexBuffer& other) = delete; 
		void Bind() const;
		void Unbind() const;
		
		inline unsigned int GetCount() const { return Count; }

		~IndexBuffer();
	};
}

