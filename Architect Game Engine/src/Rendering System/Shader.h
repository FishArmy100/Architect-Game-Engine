#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Architect
{
	enum class ShaderUniformType
	{
		Unknown = -1,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Bool,
		Sampler2D
	};

	struct ShaderUniformData
	{
		ShaderUniformData(const std::string& name, ShaderUniformType type, int location, int count) 
			: Name(name), Type(type), Location(location), Count(count) { }

		ShaderUniformData() : Name(""), Type(ShaderUniformType::Unknown), Location(0), Count(0) {}

		std::string Name;
		ShaderUniformType Type;
		unsigned int Location;
		int Count;
	};

	class Shader
	{
	private:
		unsigned int ShaderProgramId;
		std::map<std::string, ShaderUniformData> UniformDatas;

	public:
		const static std::string DefultVertexShader;
		const static std::string DefultFragmentShader;

		static std::shared_ptr<Shader> CreateDefult();
		static std::shared_ptr<Shader> CreateFromFile(const std::string& filePath);

		Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
		Shader(const std::string& shaderCode);
		Shader();

		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetShaderUniformV4(const std::string& name, float x, float y, float z, float w);
		void SetShaderUniformFloat(const std::string& name, float f);
		void SetShaderUniformInt(const std::string& name, int value);

		inline unsigned int GetShaderId() { return ShaderProgramId; }
		inline const std::map<std::string, ShaderUniformData>& GetUniforms() { return UniformDatas; }
	};
}

