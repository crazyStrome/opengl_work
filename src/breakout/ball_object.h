#ifndef MY_BREAK_BALL_OBJECT_H
#define MY_BREAK_BALL_OBJECT_H

#include "game_object.h"

class BallObject: public GameObject
{
private:
    /* data */
public:
    GLfloat Radius;
    GLboolean Stuck;

    BallObject(/* args */);
    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, const Texture2D &sprite);

    glm::vec2 Move(GLfloat dt, GLuint window_width);
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif