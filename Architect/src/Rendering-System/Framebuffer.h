#pragma once
#include <vector>

namespace Architect
{
	enum class FramebufferTextureAttachmentFormat
	{
		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8
	};

	using FbTexAttachFormat = FramebufferTextureAttachmentFormat;

	struct FramebufferSpecification
	{
		unsigned int Width = 620;
		unsigned int Height = 480;
		unsigned int Samples = 1;
		std::vector<FramebufferTextureAttachmentFormat> Attachments;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(FramebufferSpecification& spesification);
		~Framebuffer();
		Framebuffer(const Framebuffer& other) = delete;

		const FramebufferSpecification& GetSpecification() { return m_Spesification; }
		unsigned int GetColorAttachmentID(int attachmentIndex);

		void Clear();
		void Bind() const;
		void Unbind() const;

		void Resize(unsigned int width, unsigned int height);
		virtual int ReadColorPixel(uint32_t attachmentIndex, int x, int y);
		virtual void ClearColorAttachment(uint32_t attachmentIndex, int value);

	private:
		void Invalidate();
		void DeleteTexturesAndFramebuffer();
		void SetTextures();
		void AddColorTexture(uint32_t internalFormat, uint32_t format, int index);
		void AddDepthStencilTexture(uint32_t format);

	private:
		FramebufferSpecification m_Spesification {};

		std::vector<uint32_t> m_ColorAttachments{};
		std::vector<FramebufferTextureAttachmentFormat> m_ColorAttachmentFormats;

		uint32_t m_DepthAttachment = 0;
		FramebufferTextureAttachmentFormat m_DepthAttachmentFormat;

		uint32_t m_FrameBufferID = 0;
	};
}

