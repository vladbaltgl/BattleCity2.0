#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/vec2.hpp>


#include<iostream>

#include"Renderer/Texture2D.h"
#include"Renderer/ShaderProgram.h"
#include"Resources/ResourceManager.h"

using namespace std;

GLfloat point[] = {
  0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};
GLfloat colors[] = {
    1.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,0.0f,1.0f
};
GLfloat texCoord[] = {
    0.5f,1.0f,
    1.0f,0.0f,
    0.0f,0.0f
};







glm::ivec2 g_windowSize(640, 480);


void glfwWindowSizeCallback(GLFWwindow* pWindow,int width,int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, width, height);
}
void glfwKeyCallback(GLFWwindow* pWindow,int key,int scancode,int action,int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow,GL_TRUE);

    }
}


int main(int argc, char** argv)
{




    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfwint failed!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        cout << "glfwCreateWindow failed\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD !" << std::endl;
        return -1;
    }
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;


    glClearColor(2, 1, 0, 1);






    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shaders program: " << "DefaultShader" << std::endl;
            return -1;
        }



     auto tex =   resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");


    //vbo
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);


    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


    //texCoord vbo
    GLuint texCoord_vbo = 0;
    glGenBuffers(1, &texCoord_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    //vao
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    //coord Text download 
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);



    pDefaultShaderProgram->use();
    pDefaultShaderProgram->setInt("tex",0);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        pDefaultShaderProgram->use();
        glBindVertexArray(vao);
        tex->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

    glfwTerminate();
    return 0;
}