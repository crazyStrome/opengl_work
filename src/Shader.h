#pragma once

#include <string>
#include <glm/glm.hpp>

struct ShaderSource {
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class Shader {
private:
	unsigned int mProgramID;
public:
	Shader(const std::string&);
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&&);
	Shader& operator=(Shader&&);

	unsigned int GetProgramID() const { return mProgramID; }

	int GetUniformLocation(const std::string&);
	void SetUniform1i(const std::string&, int);
	int GetUniform1i(const std::string&);

	void SetUniform1f(const std::string&, float);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);

	void Use() const;
	void UnUse() const;
};
