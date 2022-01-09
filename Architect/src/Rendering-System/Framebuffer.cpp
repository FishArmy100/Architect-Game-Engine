#include "FrameBuffer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Debug-System/OpenGLDebugger.h"
#include "Core.h"

namespace Architect
{
	Framebuffer::Framebuffer(FramebufferSpecification& spesification)
		: m_Spesification(spesification)
	{
		Invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		GLCall(glDeleteFramebuffers(1, &m_FrameBufferID));
		GLCall(glDeleteTextures(1, &m_ColorAttachment));
		GLCall(glDeleteTextures(1, &m_DepthAttachment));
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

	void Framebuffer::Invalidate()
	{
		if (m_FrameBufferID)
		{
			GLCall(glDeleteFramebuffers(1, &m_FrameBufferID));
			GLCall(glDeleteTextures(1, &m_ColorAttachment));
			GLCall(glDeleteTextures(1, &m_DepthAttachment));
		}

		GLCall(glCreateFramebuffers(1, &m_FrameBufferID));
		Bind();

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachment));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spesification.Width, m_Spesification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0));

		GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));

		GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Spesification.Width, m_Spesification.Height));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));

		ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)

		Unbind();
	}
}