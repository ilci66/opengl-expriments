#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shaders/shaderClass.h>
#include <VAO/VAO.h>
#include <VBO/VBO.h>
#include <EBO/EBO.h>

GLfloat vertices[] =
    {
        //               COORDINATES                  /     COLORS           //
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f,  // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f,   // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,    // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.9f, 0.45f, 0.17f, // Inner left
        0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f, 0.9f, 0.45f, 0.17f,  // Inner right
        0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f, 0.02f    // Inner down
};

GLuint indices[] =
    {
        // Lower left triangle
        0, 3, 5,
        // Upper triangle
        3, 2, 4,
        // Lower right triangle
        5, 4, 1};

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

  // VAO1.LinkVBO(VBO1, 0);

  // Links VBO attributes such as coordinates and colors to VAO

  // Pass in the layout number/ID, number of components,
  // types (float in our case),
  // stride ((3 (for position) +3 (for colors - RGB)) * sizeof(float))
  //  -- 4 bytes for each pos or color input float --  //
  //  -- Which makes the color offset 12 (color starts after 12) --  //
  // and offset and we don't currently have an offset for positions
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

  // Gets ID of uniform called "scale"
  GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Activate();
    glUniform1f(uniID, 0.5f);
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}