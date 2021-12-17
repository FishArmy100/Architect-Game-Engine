#pragma once
#include <vector>

namespace Architect
{
	struct VertexBufferLayoutElement
	{
		VertexBufferLayoutElement(unsigned int count, unsigned int type, bool normalized, unsigned int typeByteSize)
		{
			Count = count;
			Type = type;
			Normalized = normalized;
			TypeByteSize = typeByteSize;
		}

		unsigned int Count;
		unsigned int Type;
		bool Normalized;
		unsigned int TypeByteSize;
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferLayoutElement> Elements;
		unsigned int Stride;

	public:
		VertexBufferLayout();
		void PushFloats(int count, bool normalized);
		void PushUnsignedInts(int count);

		inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return Elements; }
		inline unsigned int GetStride() const { return Stride; }
	};
}

