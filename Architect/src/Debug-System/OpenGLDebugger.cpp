#include "OpenGlDebugger.h"
#include "../Logger/Logger.h"
#include <sstream>

namespace Architect
{
	void OpenGLDebugger::GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	void OpenGLDebugger::GLLogErrors(const char* functionName, const char* fileName, int line)
	{
		while (GLenum error = glGetError())
		{
			std::stringstream ss;
			ss << "OpenGL Error: #" << error << "\n Function: " 
				<< functionName << "\n File Name:" 
				<< fileName << ", Line:" << line;
			ARC_ENGINE_ERROR(ss.str());
		}
	}
}
