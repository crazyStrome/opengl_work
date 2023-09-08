#ifndef MY_BREAK_SPRITE_RENDERER
#define MY_BREAK_SPRITE_RENDERER
#include "shader.h"
#include "texture.h"
#include "../glm/glm.hpp"

class SpriteRenderer
{
private:
    /* data */
    Shader shader;
    GLuint quadVAO;

    void initRenderData();

public:
    SpriteRenderer(const Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(const Texture2D &texture,
                    glm::vec2 position,
                    glm::vec2 size = glm::vec2(10, 10),
                    GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
};

#endif