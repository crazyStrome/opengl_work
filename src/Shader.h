#pragma once

#include <string>

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

	void Use() const;
	void UnUse() const;
};
