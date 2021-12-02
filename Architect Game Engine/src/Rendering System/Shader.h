#pragma once
#include <string>
#include <vector>

namespace Architect
{
	enum class ShaderUniformType
	{
		Unknown = -1,
		Float,
		Vec4
	};

	struct ShaderUniformData
	{
		ShaderUniformData(const std::string& name, ShaderUniformType type) : Name(name), Type(type) { }

		std::string Name;
		ShaderUniformType Type;
	};

	class Shader
	{
	private:
		unsigned int ShaderProgramId;
		std::vector<ShaderUniformData> UniformDatas;

	public:
		const static std::string DefultVertexShader;
		const static std::string DefultFragmentShader;
		const static unsigned int MAX_UNIFORM_NAME_LENGTH = 256;

		static Shader CreateDefult();
		static Shader CreateFromFile(const std::string& filePath);

		Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
		Shader(const std::string& shaderCode);

		~Shader();

		void Bind();
		void Unbind();

		void SetShaderUniformV4(const std::string& name, float x, float y, float z, float t);
		void SetShaderUniformFloat(const std::string& name, float f);

		inline unsigned int GetShaderId() { return ShaderProgramId; }
		inline const std::vector<ShaderUniformData>& GetUniformData() { return UniformDatas; }
	};
}

