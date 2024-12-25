#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>

#include "Shader.h"
#include "events/EventDispatcher.h"
#include "Texture.h"
#include "VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>

const int WIDTH = 1280;
const int HEIGHT = 960;
int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    EventDispatcher dispatcher(window);
    dispatcher.RegisterHandler(EventType::EventKeyPressed, [&](Event& event) {
        EventKeyPressed keyEvent = dynamic_cast<EventKeyPressed&>(event);
        if (keyEvent.GetKey() == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, 1);
        }
        });

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	float vertices[] = {
	     0.5f, -0.5f, -0.5f,  
	     0.5f,  0.5f, -0.5f,  
	    -0.5f,  0.5f, -0.5f,  
	    -0.5f, -0.5f, -0.5f,  

	    -0.5f, -0.5f,  0.5f,  
	    -0.5f,  0.5f,  0.5f,  
	     0.5f,  0.5f,  0.5f,  
	     0.5f, -0.5f,  0.5f,  

	    -0.5f, -0.5f, -0.5f,  
	    -0.5f,  0.5f, -0.5f,  
	    -0.5f,  0.5f,  0.5f,  
	    -0.5f, -0.5f,  0.5f,  

	     0.5f, -0.5f,  0.5f,  
	     0.5f,  0.5f,  0.5f,  
	     0.5f,  0.5f, -0.5f,  
	     0.5f, -0.5f, -0.5f,  

	     0.5f, -0.5f,  0.5f,  
	     0.5f, -0.5f, -0.5f,  
	    -0.5f, -0.5f, -0.5f,  
	    -0.5f, -0.5f,  0.5f,  

	    -0.5f,  0.5f,  0.5f,  
	    -0.5f,  0.5f, -0.5f,  
	     0.5f,  0.5f, -0.5f,  
	     0.5f,  0.5f,  0.5f,  
	};

    float textureCoord[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9,10,
        10,11,8,

        12,13,14,
        14,15,12,

        16,17,18,
        18,19,16,

        20,21,22,
        22,23,20,
    };

    VertexBuffer vertexBuffer(vertices, sizeof(vertices));
    VertexLayout layout;
    layout.AddAttrib<float>(3, false);
    vertexBuffer.SetLayout(layout);

    VertexBuffer textureBuffer(textureCoord, sizeof(textureCoord));
    VertexLayout textureLayout;
    textureLayout.AddAttrib<float>(2, false);
    textureBuffer.SetLayout(textureLayout);

    IndexBuffer indexBuffer(indices, sizeof(indices));

    VertexArray vertexArray;
    vertexArray.AddVertexBuffer(vertexBuffer);
    vertexArray.AddVertexBuffer(textureBuffer);
    vertexArray.SetIndexBuffer(indexBuffer);

    Shader shader("source/shader/hello_square.shader");
    shader.UnUse();

	float borderColor[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    Texture2D texture("source/picture/awesomeface.png", 
        GL_LINEAR, GL_LINEAR,
        GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE,
        borderColor);

    Texture2D matrix("source/picture/matrix.jpg", 
        GL_LINEAR, GL_LINEAR,
        GL_CLAMP_TO_BORDER, GL_REPEAT,
        borderColor);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        texture.ActiveTexture(GL_TEXTURE1);
        matrix.ActiveTexture(GL_TEXTURE2);

		shader.Use();
		shader.SetUniform1i("ourTexture", 1);
		shader.SetUniform1i("ourMatrix", 2);
        float offset = glfwGetTime();
        shader.SetUniform1f("yOffset", offset);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.25f));
        model = glm::rotate(model, float(glfwGetTime()), glm::vec3(1.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        shader.SetUniformMat4f("model", model);

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.SetUniformMat4f("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
        shader.SetUniformMat4f("projection", projection);

        vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		shader.UnUse();

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}