
#ifndef MY_BREAK_GAME_H
#define MY_BREAK_GAME_H

#include "../glm/matrix.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../GL/glew.h"
#include "../GLFW/glfw3.h"
#include <vector>
#include "game_level.h"
#include "ball_object.h"
#include "game_object.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
};
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};  
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;   
class Game
{
private:
    /* data */
public:
    GameState State;
    GLboolean Keys[1024];
    GLuint Width, Height;

    std::vector<GameLevel> Levels;
    GLuint Level;

    Game(GLuint width, GLuint height);
    ~Game();

    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();

    void DoCollisions();
    void ResetLevel();
    void ResetPlayer();
};
Collision CheckCollision(BallObject &one, GameObject &two);

Direction VectorDirection(glm::vec2 target);
#endif