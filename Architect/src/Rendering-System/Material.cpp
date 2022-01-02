#include "Material.h"
#include "../Logger/Logger.h"

namespace Architect
{
	Material::Material(std::shared_ptr<Shader> shader)
	{
		m_Shader = shader;
	}

	void Material::Bind() const
	{
		m_Shader->Bind();

		for (const auto& uniform : m_Floats)
			m_Shader->SetShaderUniformFloat(uniform.first, uniform.second);

		for (const auto& uniform : m_Float4s)
			m_Shader->SetShaderUniformV4(uniform.first, uniform.second.x, uniform.second.y, uniform.second.z, uniform.second.w);

		int index = 0;
		for (const auto& uniform : m_Textures)
		{
			std::shared_ptr<Texture> texture = uniform.second;
			std::string name = uniform.first;

			texture->Bind(index);
			m_Shader->SetShaderUniformInt(name, index);
			index++;
		}
	}

	void Material::Unbind() const
	{
		m_Shader->Unbind();
		for (const auto& uniform : m_Textures)
		{
			std::shared_ptr<Texture> texture = uniform.second;
			texture->Unbind();
		}
	}

	void Material::SetFloat(const std::string& name, float value)
	{
		if (ShaderContainsUniform(name, ShaderUniformType::Float))
		{
			m_Floats[name] = value;
		}
		else
		{
			ARC_ENGINE_WARNING("Trying to set uniform {0}, witch does not exist", name);
		}
	}

	void Material::SetFloat4(const std::string& name, glm::vec4 float4)
	{
		if (ShaderContainsUniform(name, ShaderUniformType::Float4))
		{
			m_Float4s[name] = float4;
		}
		else
		{
			ARC_ENGINE_WARNING("Trying to set uniform {0}, witch does not exist", name);
		}
	}

	void Material::SetTexture(const std::string& name, std::shared_ptr<Texture> texture)
	{
		if (ShaderContainsUniform(name, ShaderUniformType::Sampler2D))
		{
			m_Textures[name] = texture;
		}
		else
		{
			ARC_ENGINE_WARNING("Trying to set uniform {0}, witch does not exist", name);
		}
	}

	bool Material::ShaderContainsUniform(const std::string& name, ShaderUniformType type) const
	{
		std::map<std::string, ShaderUniformData> uniforms = m_Shader->GetUniforms();
		
		if (uniforms.count(name) >= 1)
		{
			if (uniforms[name].Type == type)
				return true;
		}

		return false;
	}
}