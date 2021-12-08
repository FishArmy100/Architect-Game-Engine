#include "Shader.h"
#include "GL/glew.h"
#include "../Debug System/OpenGLDebugger.h"
#include "../Logger/Logger.h"
#include <sstream>
#include <fstream>
#include <algorithm>

namespace Architect
{
    struct ShaderCodeData
    {
        std::string vertexShaderCode;
        std::string fragmentShaderCode;
    };

    const std::string Shader::DefultVertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
            "gl_Position = position;\n"
        "}\n";

    const std::string Shader::DefultFragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
            "color = vec4(1.0, 1.0, 1.0, 1.0);\n"
        "}\n";

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderCodeData ParseShader(const std::string& shader);
    void ReplaceEmptyShaders(ShaderCodeData& data);
    void DisplayCouldNotFindShaderError(const std::string& filePath);
    std::map<std::string, ShaderUniformData> GetUniformDatasFromShader(unsigned int shaderID);

	Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{
        ShaderProgramId = CreateShader(vertexShaderCode, fragmentShaderCode);
        UniformDatas = GetUniformDatasFromShader(ShaderProgramId);
	}

    Shader::Shader(const std::string& shaderCode)
    {
        ShaderCodeData data = ParseShader(shaderCode);
        ReplaceEmptyShaders(data);
        ShaderProgramId = CreateShader(data.vertexShaderCode, data.fragmentShaderCode);
        UniformDatas = GetUniformDatasFromShader(ShaderProgramId);
    }

    Shader::Shader() : Shader(DefultVertexShader, DefultFragmentShader) {}

    std::shared_ptr<Shader> Shader::CreateDefult()
    {
        return std::make_shared<Shader>(DefultVertexShader, DefultFragmentShader);
    }

    std::shared_ptr<Shader> Shader::CreateFromFile(const std::string& filePath)
    {
        if (filePath.substr(filePath.find_last_of(".") + 1) != "shader")
        {
            DisplayCouldNotFindShaderError(filePath);
            return Shader::CreateDefult();
        }

        std::ifstream fileStream;
        fileStream.open(filePath);
        if (!fileStream)
        {
            DisplayCouldNotFindShaderError(filePath);
            return Shader::CreateDefult();
        }

        std::stringstream ss;
        std::string line;
        // reads from file
        while (std::getline(fileStream, line))
        {
            ss << line;
            if (line.length() > 0)
                ss << "\n";
        }

        return std::make_shared<Shader>(ss.str());
    }

    void Shader::SetShaderUniformV4(const std::string& name, float x, float y, float z, float t)
    {
        int uniformLocation = glGetUniformLocation(ShaderProgramId, name.c_str());

        if (uniformLocation == -1)
        {
            ARC_ENGINE_ERROR("Could not find shader uniform: {0}", name);
            return;
        }

        Bind();
        GLCall(glUniform4f(uniformLocation, x, y, z, t));
    }

    void Shader::SetShaderUniformFloat(const std::string& name, float f)
    {
        int uniformLocation = glGetUniformLocation(ShaderProgramId, name.c_str());

        if (uniformLocation == -1)
        {
            ARC_ENGINE_ERROR("Could not find shader uniform: {0}", name);
            return;
        }

        Bind();
        GLCall(glUniform1f(uniformLocation, f));
    }

    void Shader::SetShaderUniformInt(const std::string& name, int value)
    {
        int uniformLocation = glGetUniformLocation(ShaderProgramId, name.c_str());

        if (uniformLocation == -1)
        {
            ARC_ENGINE_ERROR("Could not find shader uniform: {0}", name);
            return;
        }

        Bind();
        GLCall(glUniform1i(uniformLocation, value));
    }

    void Shader::SetShaderUniformMat4f(const std::string& name, glm::mat4& matrix)
    {
        int uniformLocation = glGetUniformLocation(ShaderProgramId, name.c_str());

        if (uniformLocation == -1)
        {
            ARC_ENGINE_ERROR("Could not find shader uniform: {0}", name);
            return;
        }

        Bind();
        GLCall(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]));
    }

    bool Shader::ContainsUniform(const std::string& name, ShaderUniformType type)
    {
        if (UniformDatas.count(name) >= 1)
        {
            if (UniformDatas[name].Type == type)
                return true;
        }

        return false;
    }

    void Shader::Bind() const
    {
        GLCall(glUseProgram(ShaderProgramId));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(ShaderProgramId));
    }

    // ----------- NON MEMBER FUNCTIONS -------------

    ShaderUniformType GetTypeFromGLUniformType(int glType)
    {
        switch (glType)
        {
        case GL_FLOAT:
            return ShaderUniformType::Float;
        case GL_FLOAT_VEC2:
            return ShaderUniformType::Float2;
        case GL_FLOAT_VEC3:
            return ShaderUniformType::Float3;
        case GL_FLOAT_VEC4:
            return ShaderUniformType::Float4;
        case GL_INT:
            return ShaderUniformType::Int;
        case GL_BOOL:
            return ShaderUniformType::Bool;
        case GL_SAMPLER_2D:
            return ShaderUniformType::Sampler2D;
        case GL_FLOAT_MAT4:
            return ShaderUniformType::Mat4x4f;
        default:
            break;
        }

        return ShaderUniformType::Unknown;
    }

    std::map<std::string, ShaderUniformData> GetUniformDatasFromShader(unsigned int shaderID)
    {
        GLint uniform_count = 0;
        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &uniform_count);

        if (uniform_count != 0)
        {
            GLint 	max_name_len = 0;
            GLsizei length = 0;
            GLsizei count = 0;
            GLenum 	type = GL_NONE;
            glGetProgramiv(shaderID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

            auto uniform_name = std::make_unique<char[]>(max_name_len);

            std::map<std::string, ShaderUniformData> uniforms;

            for (GLint i = 0; i < uniform_count; ++i)
            {
                glGetActiveUniform(shaderID, i, max_name_len, &length, &count, &type, uniform_name.get());

                std::string name = std::string(uniform_name.get(), length);
                ShaderUniformType uniformType = GetTypeFromGLUniformType(type);
                int location = glGetUniformLocation(shaderID, uniform_name.get());

                if (uniformType == ShaderUniformType::Unknown)
                    ARC_ENGINE_WARNING("Found unknown type of uniform named: {0}", name);

                uniforms[name] = ShaderUniformData(name, uniformType, location, count);
            }

            return uniforms;
        }

        return std::map<std::string, ShaderUniformData>();
    }

    void DisplayCouldNotFindShaderError(const std::string& filePath)
    {
        std::stringstream ss;
        ss << "Could not find shader at path: " << filePath << ". Using the defult shader instead.";
        ARC_ENGINE_ERROR(ss.str());
    }

    void ReplaceEmptyShaders(ShaderCodeData& data)
    {
        if (data.vertexShaderCode.length() == 0)
        {
            data.vertexShaderCode = Shader::DefultVertexShader;
            ARC_ENGINE_WARNING("No vertex shader found, using defult vertex shader");
        }

        if (data.fragmentShaderCode.length() == 0)
        {
            data.fragmentShaderCode = Shader::DefultFragmentShader;
            ARC_ENGINE_WARNING("No fragment shader found, using defult fragment shader");
        }
    }

    ShaderCodeData ParseShader(const std::string& shaderCode)
    {
        enum class ShaderType
        {
            None = -1,
            Vertex = 0,
            Fragment = 1
        };

        std::stringstream ss[2];
        ShaderType currentType = ShaderType::None;

        std::istringstream iss(shaderCode);
        std::string line;
        while (std::getline(iss, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    currentType = ShaderType::Vertex;
                else if (line.find("fragment") != std::string::npos)
                    currentType = ShaderType::Fragment;
            }
            else
            {
                ss[(int)currentType] << line << "\n";
            }
        }

        ShaderCodeData data;
        data.vertexShaderCode = ss[(int)ShaderType::Vertex].str();
        data.fragmentShaderCode = ss[(int)ShaderType::Fragment].str();

        return data;
    }

    unsigned int CompileShader(const std::string& source, unsigned int type)
    {
        unsigned int id = glCreateShader(type);
        const char* rawString = source.c_str();
        GLCall(glShaderSource(id, 1, &rawString, nullptr));
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            ARC_ENGINE_ERROR("Failed to Compile Shader: {0}", message);
            return 0;
        }

        return id;
    }

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
        unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));
        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return program;
    }
}