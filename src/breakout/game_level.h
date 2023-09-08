#ifndef MY_GAME_LEVEL_H
#define MY_GAME_LEVEL_H

#include <vector>
#include "game_object.h"

class GameLevel
{
private:
    void init(const std::vector<std::vector<GLuint>> &tileData, GLuint levelWidth, GLuint levelHeight);
public:
    std::vector<GameObject> Bricks;
    void Load(const GLchar *file, GLuint levelWitdh, GLuint levelHeight);
    void Draw(SpriteRenderer &renderer);

    GLboolean IsCompleted();
};

#endif