#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaders/shaderClass.h>
#include <VAO/VAO.h>
#include <VBO/VBO.h>
#include <EBO/EBO.h>

GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};

GLuint indices[] = {
    0,
    3,
    5, // Lower left triangle
    3,
    2,
    4, // Upper triangle
    5,
    4,
    1 // Lower right triangle
};

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(800, 800, "IlkerTests", NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, 800, 800);

  // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // glCompileShader(vertexShader);

  // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  // glCompileShader(fragmentShader);

  // GLuint shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);

  // glLinkProgram(shaderProgram);

  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);

  // GLuint VAO, VBO, EBO;

  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);
  // glGenBuffers(1, &EBO);

  // glBindVertexArray(VAO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  // glEnableVertexAttribArray(0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Shader shaderProgram("default.vert", "default.frag");
  std::filesystem::path parentPath = std::filesystem::current_path().parent_path();

  std::filesystem::path vertFilePath = parentPath / "default.vert";
  std::filesystem::path fragFilePath = parentPath / "default.frag";

  const char *vertFilePathStr = vertFilePath.c_str();
  const char *fragFilePathStr = fragFilePath.c_str();

  Shader shaderProgram(vertFilePathStr, fragFilePathStr);

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkVBO(VBO1, 0);
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // glUseProgram(shaderProgram);
    shaderProgram.Activate();
    // glBindVertexArray(VAO);
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &EBO);
  // glDeleteProgram(shaderProgram);
  // glfwDestroyWindow(window);
  // glfwTerminate();
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}