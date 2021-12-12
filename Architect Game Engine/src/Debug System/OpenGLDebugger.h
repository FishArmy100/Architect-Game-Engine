#pragma once
#include "GL/glew.h"

#define GLCall(x) Architect::OpenGLDebugger::GLClearError();\
	x;\
	Architect::OpenGLDebugger::GLLogErrors(#x, __FILE__, __LINE__);

namespace Architect
{
	class OpenGLDebugger
	{
	public:
		static void GLClearError();
		static void GLLogErrors(const char* functionName, const char* fileName, int line);
	};
}

