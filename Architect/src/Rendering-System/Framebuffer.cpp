#include "FrameBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Core.h"
#include <memory>

namespace Architect
{
	namespace Utils
	{
		static GLenum FBTextureFormatToGL(FramebufferTextureAttachmentFormat format)
		{
			switch (format)
			{
			case FramebufferTextureAttachmentFormat::RGBA8:           return GL_RGBA;
			case FramebufferTextureAttachmentFormat::RED_INTEGER:	  return GL_RED_INTEGER;
			case FramebufferTextureAttachmentFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
			}

			return 0;
		}
	}

	Framebuffer::Framebuffer(FramebufferSpecification& spesification)
		: m_Spesification(spesification)
	{
		for (auto format : spesification.Attachments)
		{
			if (format != FramebufferTextureAttachmentFormat::DEPTH24STENCIL8)
				m_ColorAttachmentFormats.emplace_back(format);
			else
				m_DepthAttachmentFormat = format;
		}

		Invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		DeleteTexturesAndFramebuffer();
	}

	unsigned int Framebuffer::GetColorAttachmentID(int attachmentIndex)
	{
		return m_ColorAttachments[attachmentIndex];
	}

	void Framebuffer::Clear()
	{
		Bind();
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Unbind();
	}

	void Framebuffer::Bind() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID));
		GLCall(glViewport(0, 0, m_Spesification.Width, m_Spesification.Height));
	}

	void Framebuffer::Unbind() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	void Framebuffer::Resize(unsigned int width, unsigned int height)
	{
		m_Spesification.Width = width;
		m_Spesification.Height = height;
		Invalidate();
	}

	int Framebuffer::ReadColorPixel(uint32_t attachmentIndex, int x, int y)
	{
		Bind(); 
		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex));
		int pixelData;
		uint32_t format = Utils::FBTextureFormatToGL(m_ColorAttachmentFormats[attachmentIndex]);
		GLCall(glReadPixels(x, y, 1, 1, format, GL_INT, &pixelData));
		Unbind();
		return pixelData;
	}

	void Framebuffer::ClearColorAttachment(uint32_t attachmentIndex, int value)
	{
		auto& attachment = m_ColorAttachmentFormats[attachmentIndex];
		GLCall(glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
			Utils::FBTextureFormatToGL(attachment), GL_INT, &value));
	}

	void Framebuffer::Invalidate()
	{
		if (m_FrameBufferID)
			DeleteTexturesAndFramebuffer();

		glGenFramebuffers(1, &m_FrameBufferID);
		SetTextures();

		// TODO: make veriable size
		if (m_ColorAttachments.size() > 1)
		{
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glNamedFramebufferDrawBuffers(m_FrameBufferID, m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		Bind();
		ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		Unbind();
	}

	void Framebuffer::DeleteTexturesAndFramebuffer()
	{
		GLCall(glDeleteFramebuffers(1, &m_FrameBufferID));

		for (int index = 0; index < m_ColorAttachments.size(); index++)
		{
			GLCall(glDeleteTextures(1, &m_ColorAttachments[index]));
		}

		if(m_DepthAttachment != 0)
			GLCall(glDeleteTextures(1, &m_DepthAttachment));

		m_FrameBufferID = 0;
		m_DepthAttachment = 0;
		m_ColorAttachments.clear();
	}

	void Framebuffer::SetTextures()
	{
		Bind();
		int colorIndex = 0;

		for (auto format : m_Spesification.Attachments)
		{
			switch (format)
			{
			case FramebufferTextureAttachmentFormat::RGBA8:
				AddColorTexture(GL_RGBA8, GL_RGBA, colorIndex);
				colorIndex++;
				break;
			case FramebufferTextureAttachmentFormat::RED_INTEGER:
				AddColorTexture(GL_R32I, GL_RED_INTEGER, colorIndex);
				colorIndex++;
				break;
			case FramebufferTextureAttachmentFormat::DEPTH24STENCIL8:
				AddDepthStencilTexture(GL_DEPTH24_STENCIL8);
				break;
			default:
				break;
			}
		}

		Unbind(); 
	}

	void Framebuffer::AddColorTexture(uint32_t internalFormat, uint32_t format, int index)
	{
		uint32_t texture = 0;
		GLCall(glGenTextures(1, &texture));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Spesification.Width, m_Spesification.Height, 0, format, GL_UNSIGNED_BYTE, NULL));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture, 0));

		m_ColorAttachments.push_back(texture);
	}


	void Framebuffer::AddDepthStencilTexture(uint32_t format)
	{
		ASSERT_BREAK(m_DepthAttachment == 0, "Cannot have multiple depth attachments");

		GLCall(glGenTextures(1, &m_DepthAttachment));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, format, m_Spesification.Width, m_Spesification.Height));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));
	}
}