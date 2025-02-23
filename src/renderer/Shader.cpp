#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

static ShaderSource loadShaderSource(const std::string& path)
{
	std::ifstream file = std::ifstream(path);
	if (!file)
	{
		std::cout << "File: " << path << " not found" << std::endl;
		throw new std::runtime_error("FILE OPEN FAILED");
	}
	enum ShaderType 
	{
		None = -1, Vertex, Fragment
	};
	std::string line;
	std::stringstream sources[2];
	ShaderType curType = None;
	while (std::getline(file, line)) 
	{
		if (line.size() == 0)
		{
			continue;
		}
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				curType = Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				curType = Fragment;
			}
			else
			{
				curType = None;
			}
			continue;
		}
		if (curType == None)
		{
			continue;
		}	
		sources[int(curType)] << line << std::endl;
	}
	return ShaderSource{
		sources[int(Vertex)].str(),
		sources[int(Fragment)].str(),
	};
}

static unsigned int compileShader(GLenum type, const std::string& source)
{
	const char* sourceStr = source.c_str();
	unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &sourceStr, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = (char*)new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, nullptr, infoLog);
        glDeleteShader(shader);
        std::cout << "Compile " << (type == GL_VERTEX_SHADER ? "VertexShader": "FragmentShader") <<
			" ERROR: " << infoLog << std::endl;
        delete[] infoLog;
		throw new std::runtime_error("COMPILE SHADER FAILED");
    }
	return shader;
}

static unsigned int linkProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
	int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        int maxLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = (char*)new char[maxLength];
        glGetProgramInfoLog(shaderProgram, maxLength, nullptr, infoLog);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        std::cout << "Link Program ERROR: " << infoLog << std::endl;
        return 0;
    }
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	return shaderProgram;
}

Shader::Shader(const std::string& path) 
{
	ShaderSource source = loadShaderSource(path);
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, source.VertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, source.FragmentShaderSource);
	mProgramID = linkProgram(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	std::cout << "Delete shader: " << mProgramID << std::endl;
	glDeleteProgram(mProgramID);
}

Shader::Shader(Shader&& right)
	: mProgramID(right.mProgramID)
{
	right.mProgramID = 0;
}

Shader& Shader::operator=(Shader&& right)
{
	if (this != &right)
	{
		glDeleteProgram(mProgramID);
		mProgramID = 0;
		std::swap(mProgramID, right.mProgramID);
	}
	return *this;
}

int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(mProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "GetUniformLocation of: " << mProgramID << ", name: " << name << " not found\n";
	}
	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

int Shader::GetUniform1i(const std::string& name)
{
	int value;
	glGetUniformiv(mProgramID, GetUniformLocation(name), &value);
	return value;
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Use() const
{
	if (mProgramID == 0)
	{
		std::cout << "Shader not init or destroyed" << std::endl;
		throw new std::runtime_error("SHADER NOT INIT OR DESTROYED");
	}
	glUseProgram(mProgramID);
}

void Shader::UnUse() const
{
	glUseProgram(0);
}
