#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>

#include "Shader.h"
#include "events/EventDispatcher.h"
#include "Texture.h"
#include "VertexArray.h"

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

    window = glfwCreateWindow(1280, 960, "Hello Triangle", NULL, NULL);
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
        -0.5f, -0.5f, 0.0f, 
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f
    };
    float textureCoord[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f 
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        texture.ActiveTexture(GL_TEXTURE1);
        matrix.ActiveTexture(GL_TEXTURE2);

		shader.Use();
		shader.SetUniform1i("ourTexture", 1);
		shader.SetUniform1i("ourMatrix", 2);
        float offset = glfwGetTime();
        shader.SetUniform1f("yOffset", offset);
        vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        vertexArray.UnBind();
		shader.UnUse();

		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}