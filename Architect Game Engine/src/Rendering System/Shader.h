#pragma once
#include <string>

namespace Architect
{
	class Shader
	{
	private:
		unsigned int ShaderProgramId;

	public:
		const static std::string DefultVertexShader;
		static const std::string DefultFragmentShader;

		Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
		Shader(const std::string& shaderCode);
		static Shader CreateDefult();
		static Shader CreateFromFile(const std::string& filePath);

		void SetAsCurrent();
		inline unsigned int GetShaderId() { return ShaderProgramId; }

		~Shader();
	};
}

