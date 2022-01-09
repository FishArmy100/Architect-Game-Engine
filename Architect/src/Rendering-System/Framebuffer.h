#pragma once
namespace Architect
{
	struct FramebufferSpecification
	{
		unsigned int Width = 0;
		unsigned int Height = 0;
		unsigned int Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(FramebufferSpecification& spesification);
		~Framebuffer();
		Framebuffer(const Framebuffer& other) = delete;

		const FramebufferSpecification& GetSpecification() { return m_Spesification; }
		unsigned int GetColorAttachmentID() { return m_ColorAttachment; }

		void Clear();
		void Bind() const;
		void Unbind() const;

		void Resize(unsigned int width, unsigned int height);

	private:
		void Invalidate();

	private:
		FramebufferSpecification m_Spesification {};
		unsigned int m_ColorAttachment = 0;
		unsigned int m_DepthAttachment = 0;
		unsigned int m_FrameBufferID = 0;
	};
}

