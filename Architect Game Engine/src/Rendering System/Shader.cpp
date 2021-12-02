#include "Shader.h"
#include "GL/glew.h"
#include "../Debug System/OpenGLDebugger.h"
#include "../Logger/Logger.h"
#include <sstream>
#include <fstream>

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
    std::vector<ShaderUniformData> GetUniformDatasFromShader(unsigned int shaderID);

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

    Shader Shader::CreateDefult()
    {
        return Shader(DefultVertexShader, DefultFragmentShader);
    }

    Shader Shader::CreateFromFile(const std::string& filePath)
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

        return Shader(ss.str());
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

    void Shader::Bind()
    {
        GLCall(glUseProgram(ShaderProgramId));
    }

    void Shader::Unbind()
    {
        GLCall(glUseProgram(0));
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(ShaderProgramId));
    }

    // ----------- NON MEMBER FUNCTIONS -------------
    
    ShaderUniformData CreateShaderUniformData(const std::string& uniformName, int uniformType)
    {
        ShaderUniformType type = ShaderUniformType::Unknown;

        switch (uniformType)
        {
        case GL_FLOAT_VEC4:
            type = ShaderUniformType::Vec4;
            break;
        case GL_FLOAT:
            type = ShaderUniformType::Float;
            break;
        default:
            ARC_ENGINE_ERROR("Could not find uniform type: {0}", uniformType);
            break;
        }

        return ShaderUniformData(uniformName, type);
    }

    std::string TrimString(const std::string& line)
    {
        const char* WhiteSpace = " \t\v\r\n";
        std::size_t start = line.find_first_not_of(WhiteSpace);
        std::size_t end = line.find_last_not_of(WhiteSpace);
        return start == end ? std::string() : line.substr(start, end - start + 1);
    }

    std::vector<ShaderUniformData> GetUniformDatasFromShader(unsigned int shaderID)
    {
        int count;
        GLCall(glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &count));

        const unsigned int maxNameLength = Shader::MAX_UNIFORM_NAME_LENGTH;
        char uniformName[maxNameLength];

        int uniformNameLength;
        int uniformSize;
        unsigned int uniformType;

        std::vector<ShaderUniformData> shaderUniformDatas;

        for (int i = 0; i < count; i++)
        {
            GLCall(glGetActiveUniform(shaderID, i, maxNameLength, &uniformNameLength, &uniformSize, &uniformType, uniformName));
            std::string uniformNameStr(uniformName);
            uniformNameStr = TrimString(uniformNameStr);
            
            ShaderUniformData data = CreateShaderUniformData(uniformNameStr, uniformType);
            shaderUniformDatas.emplace_back(data);
        }

        return shaderUniformDatas;
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