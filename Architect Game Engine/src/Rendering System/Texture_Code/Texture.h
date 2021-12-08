#pragma once
#include <string>

namespace Architect
{
	class Texture
	{
	private:
		unsigned int TextureID;
		std::string FilePath;
		unsigned char* LocalBuffer;
		int Width, Height, BPP;

	public:
		Texture(const std::string& path);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return Width; }
		inline int GetHeight() const { return Height; }
	};
}

