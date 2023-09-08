#ifndef MY_BREAK_SHADER_H
#define MY_BREAK_SHADER_H


#include "../GL/glew.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <string>

class Shader
{
private:
    /* data */
    void    checkCompileErrors(GLuint object, std::string type); 
public:
    GLuint ID;
    Shader(/* args */);
    ~Shader();

    Shader &Use();
    void Compile(const GLchar *vertexSource, 
                const GLchar * fragmentSource,
                const GLchar *geometrySource);

    void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
};


#endif