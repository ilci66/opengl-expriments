#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <texture/texture.h>
#include <shaders/shaderClass.h>
#include <VAO/VAO.h>
#include <VBO/VBO.h>
#include <EBO/EBO.h>

// // Vertices coordinates
// GLfloat vertices[] =
//     {
//         //     COORDINATES     /        COLORS      /   TexCoord  //
//         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
//         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
//         0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // Upper right corner
//         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f   // Lower right corner
// };

// // Indices for vertices order
// GLuint indices[] =
//     {
//         0, 2, 1, // Upper triangle
//         0, 3, 2  // Lower triangle
// };

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;

int main()
{
  glfwInit();

  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "IlkerTests", NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, windowWidth, windowHeight);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

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
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  // Unbind all to prevent accidentally modifying them
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  // Gets ID of uniform called "scale"
  GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  // -------------- Texture ----------------

  std::string parentPathStr = parentPath.string();
  std::string texturePath = "/textures/";

  Texture sadCat((parentPathStr + texturePath + "sad_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

  sadCat.texUnit(shaderProgram, "tex0", 0);

  int imgWidth, imgHeight, numColCh;
  // Pass in the file loacation isnstead of the name
  unsigned char *bytes = stbi_load((parentPathStr + texturePath + "sad_cat.png").c_str(), &imgWidth, &imgHeight, &numColCh, 0);
  // unsigned char *bytes = stbi_load("sad_cat.png", &imgWidth, &imgHeight, &numColCh, 0);

  // there might be an issue in the image
  std::cout << "imgWidth: " << imgWidth << std::endl;
  std::cout << "imgHeight: " << imgHeight << std::endl;
  std::cout << "numColCh: " << numColCh << std::endl;

  GLuint texture;
  glGenTextures(1, &texture);
  std::cout << "texture: " << texture << std::endl;
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  // GL linear almost returns a blurry looking interpolated pixel using neihbouring pixels
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // S and T are equivalent of X and Y axes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  if (bytes)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(bytes);

  GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");
  shaderProgram.Activate();
  glUniform1i(tex0uni, 0);

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // // /////////////
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LESS);
    // // /////////////

    shaderProgram.Activate();
    glUniform1f(uniID, 0.5f);
    glBindTexture(GL_TEXTURE_2D, 0);

    sadCat.Bind();
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  };

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  sadCat.Delete();
  shaderProgram.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}