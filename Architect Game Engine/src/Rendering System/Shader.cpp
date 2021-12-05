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
    std::vector<ShaderUniformData> GetUniformDatasFromVertexAndFragmentShaders(const std::string vertex, const std::string fragment);

	Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
	{
        ShaderProgramId = CreateShader(vertexShaderCode, fragmentShaderCode);
        UniformDatas = GetUniformDatasFromVertexAndFragmentShaders(vertexShaderCode, fragmentShaderCode);
	}

    Shader::Shader(const std::string& shaderCode)
    {
        ShaderCodeData data = ParseShader(shaderCode);
        ReplaceEmptyShaders(data);
        ShaderProgramId = CreateShader(data.vertexShaderCode, data.fragmentShaderCode);
        UniformDatas = GetUniformDatasFromVertexAndFragmentShaders(data.vertexShaderCode, data.fragmentShaderCode);
    }

    Shader::Shader() : Shader(DefultVertexShader, DefultFragmentShader) {}

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

    void IterateOverStringLines(const std::string& string, void (*func)(const std::string&))
    {
        std::istringstream iss(string);
        std::string line;
        while (std::getline(iss, line))
        {
            func(line);
        }
    }

    ShaderUniformType GetUniformTypeFromTypeName(const std::string& typeName)
    {
        if (typeName == "float")
            return ShaderUniformType::Float1;

        if (typeName == "vec4")
            return ShaderUniformType::Float4;

        return ShaderUniformType::Unknown;
    }

    ShaderUniformData GetUniformDataFromShaderCodeLine(std::string& line)
    {
        std::istringstream iss(line);
        std::string symbol;

        bool isUniform = false;;
        std::string variableType = "";
        std::string variableName = "";

        while (std::getline(iss, symbol))
        {
            if (symbol == "uniform")
            {
                isUniform = true;
                continue;
            }

            if (isUniform == false)
                break;

            if (variableType == "")
            {
                variableType = symbol;
                continue;
            }

            if (variableName == "")
            {
                variableName = symbol;
                continue;
            }
        }

        if (variableName != "" && variableType != "")
        {
            variableName.erase(variableName.length() - 1); // removes semicolon
            ShaderUniformType type = GetUniformTypeFromTypeName(variableType);
            return ShaderUniformData(variableName, type);
        }

        return ShaderUniformData("", ShaderUniformType::Unknown);
    }

    std::vector<ShaderUniformData> GetUniformDatasFromShader(const std::string& shaderCode)
    {
        std::vector<ShaderUniformData> datas;
        std::istringstream iss(shaderCode);
        std::string codeLine;

        while (std::getline(iss, codeLine))
        {
            std::string lineCopy = codeLine;
            std::replace(lineCopy.begin(), lineCopy.end(), ' ', '\n'); // turns the spaces into new lines

            ShaderUniformData data = GetUniformDataFromShaderCodeLine(lineCopy);

            if(data.Name != "" && data.Type != ShaderUniformType::Unknown)
                datas.emplace_back(data);
        }

        return datas;
    }

    std::vector<ShaderUniformData> GetUniformDatasFromVertexAndFragmentShaders(const std::string vertex, const std::string fragment)
    {
        std::vector<ShaderUniformData> vertexUniformDatas = GetUniformDatasFromShader(vertex);
        std::vector<ShaderUniformData> fragmentUniformDatas = GetUniformDatasFromShader(fragment);
        std::vector<ShaderUniformData> shaderUniformDatas;

        shaderUniformDatas.reserve(vertexUniformDatas.size() + fragmentUniformDatas.size());
        shaderUniformDatas.insert(shaderUniformDatas.end(), vertexUniformDatas.begin(), vertexUniformDatas.end());
        shaderUniformDatas.insert(shaderUniformDatas.end(), fragmentUniformDatas.begin(), fragmentUniformDatas.end());

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