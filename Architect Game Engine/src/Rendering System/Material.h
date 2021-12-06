#pragma once
#include "Shader.h"
#include "Texture_Code/Texture.h"
#include <vector>
#include <memory>
#include "glm/vec4.hpp"
#include <map>
#include <string>

namespace Architect
{
	class Material
	{
	private:
		std::shared_ptr<Shader> m_Shader;

		std::map<std::string, std::shared_ptr<Texture>> m_Textures;

		std::map<std::string, float> m_Floats;
		std::map<std::string, glm::vec4> m_Float4s;


	public:
		Material(std::shared_ptr<Shader> shader);

		void Bind() const;
		void Unbind() const;

		void SetFloat(const std::string& name, float value);
		inline void SetFloat4(const std::string& name, float x, float y, float z, float w) { SetFloat4(name, glm::vec4(x, y, z, w)); }
		void SetFloat4(const std::string& name, glm::vec4 float4);
		
		void SetTexture(const std::string& name, std::shared_ptr<Texture> texture);

		bool ShaderContainsUniform(const std::string& name, ShaderUniformType type) const;
	};
}

