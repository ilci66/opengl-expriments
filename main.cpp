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

// float vertices[] = {
//     // positions          // colors           // texture coords
//     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
//     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
//     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
// };

// unsigned int indices[] = {
//     0, 1, 3, // first triangle
//     1, 2, 3  // second triangle
// };

// void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// void processInput(GLFWwindow *window);

// const unsigned int windowWidth = 800;
// const unsigned int windowHeight = 600;

// int main()
// {
//   glfwInit();

//   if (!glfwInit())
//   {
//     std::cout << "Failed to initialize GLFW" << std::endl;
//     return -1;
//   }

//   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//   GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "IlkerTests", NULL, NULL);

//   if (window == NULL)
//   {
//     std::cout << "Failed to create GLFW window" << std::endl;
//     glfwTerminate();
//     return -1;
//   }
//   glfwMakeContextCurrent(window);
//   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//   gladLoadGL();
//   glViewport(0, 0, windowWidth, windowHeight);

//   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//   {
//     std::cout << "Failed to initialize GLAD" << std::endl;
//     return -1;
//   }

//   std::filesystem::path parentPath = std::filesystem::current_path().parent_path();

//   std::filesystem::path vertFilePath = parentPath / "default.vert";
//   std::filesystem::path fragFilePath = parentPath / "default.frag";

//   const char *vertFilePathStr = vertFilePath.c_str();
//   const char *fragFilePathStr = fragFilePath.c_str();

//   Shader shaderProgram(vertFilePathStr, fragFilePathStr);

//   VAO VAO1;
//   VAO1.Bind();

//   VBO VBO1(vertices, sizeof(vertices));
//   EBO EBO1(indices, sizeof(indices));

//   // VAO1.LinkVBO(VBO1, 0);

//   // Links VBO attributes such as coordinates and colors to VAO

//   // Pass in the layout number/ID, number of components,
//   // types (float in our case),
//   // stride ((3 (for position) +3 (for colors - RGB)) * sizeof(float))
//   //  -- 4 bytes for each pos or color input float --  //
//   //  -- Which makes the color offset 12 (color starts after 12) --  //
//   // and offset and we don't currently have an offset for positions
//   VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
//   VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
//   VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
//   // Unbind all to prevent accidentally modifying them
//   VAO1.Unbind();
//   VBO1.Unbind();
//   EBO1.Unbind();

//   // Gets ID of uniform called "scale"
//   GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

//   // -------------- Texture ----------------

//   std::string parentPathStr = parentPath.string();
//   std::string texturePath = "/textures/";

//   Texture sadCat((parentPathStr + texturePath + "sad_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

//   sadCat.texUnit(shaderProgram, "tex0", 0);

//   int imgWidth, imgHeight, numColCh;
//   // Pass in the file loacation isnstead of the name
//   unsigned char *bytes = stbi_load((parentPathStr + texturePath + "sad_cat.png").c_str(), &imgWidth, &imgHeight, &numColCh, 0);
//   // unsigned char *bytes = stbi_load("sad_cat.png", &imgWidth, &imgHeight, &numColCh, 0);

//   // there might be an issue in the image
//   std::cout << "imgWidth: " << imgWidth << std::endl;
//   std::cout << "imgHeight: " << imgHeight << std::endl;
//   std::cout << "numColCh: " << numColCh << std::endl;

//   GLuint texture;
//   glGenTextures(1, &texture);
//   std::cout << "texture: " << texture << std::endl;
//   glActiveTexture(GL_TEXTURE0);
//   glBindTexture(GL_TEXTURE_2D, texture);

//   // GL linear almost returns a blurry looking interpolated pixel using neihbouring pixels
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//   // S and T are equivalent of X and Y axes
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//   if (bytes)
//   {
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
//     glGenerateMipmap(GL_TEXTURE_2D);
//   }
//   else
//   {
//     std::cout << "Failed to load texture" << std::endl;
//   }

//   stbi_image_free(bytes);

//   GLuint tex0uni = glGetUniformLocation(shaderProgram.ID, "tex0");
//   shaderProgram.Activate();
//   glUniform1i(tex0uni, 0);

//   while (!glfwWindowShouldClose(window))
//   {
//     glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);

//     // // /////////////
//     // glEnable(GL_DEPTH_TEST);
//     // glDepthFunc(GL_LESS);
//     // // /////////////

//     shaderProgram.Activate();
//     glUniform1f(uniID, 0.5f);
//     glBindTexture(GL_TEXTURE_2D, 0);

//     sadCat.Bind();
//     VAO1.Bind();
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//     glfwSwapBuffers(window);
//     glfwPollEvents();
//   };

//   VAO1.Delete();
//   VBO1.Delete();
//   EBO1.Delete();
//   sadCat.Delete();
//   shaderProgram.Delete();
//   glfwDestroyWindow(window);
//   glfwTerminate();
//   return 0;
// }

// void processInput(GLFWwindow *window)
// {
//   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//     glfwSetWindowShouldClose(window, true);
// }

// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//   // make sure the viewport matches the new window dimensions; note that width and
//   // height will be significantly larger than specified on retina displays.
//   glViewport(0, 0, width, height);
// }

// TRIANGLE

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShader1Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\0";

const char *fragmentShader2Source = "#version 330 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(0.2f, 0.7f, 0.3f, 1.0f);\n"
                                    "}\0";

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

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
  unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color yellow
  unsigned int shaderProgramOrange = glCreateProgram();
  unsigned int shaderProgramGreen = glCreateProgram(); // the second shader program

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragmentShaderOrange);
  glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentShaderYellow);

  glAttachShader(shaderProgramOrange, vertexShader);
  glAttachShader(shaderProgramOrange, fragmentShaderOrange);
  glLinkProgram(shaderProgramOrange);
  // then link the second program object using a different fragment shader (but same vertex shader)
  // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
  glAttachShader(shaderProgramGreen, vertexShader);
  glAttachShader(shaderProgramGreen, fragmentShaderYellow);
  glLinkProgram(shaderProgramGreen);

  float firstTriangle[] = {
      -0.9f, -0.5f, 0.0f, // left
      -0.0f, -0.5f, 0.0f, // right
      -0.45f, 0.5f, 0.0f, // top
  };
  float secondTriangle[] = {
      0.0f, -0.5f, 0.0f, // left
      0.9f, -0.5f, 0.0f, // right
      0.45f, 0.5f, 0.0f  // top
  };

  // int success;
  // char infoLog[512];
  // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  // if (!success)
  // {
  //   glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  //   std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
  // if (!success)
  // {
  //   glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  //   std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
  //             << infoLog << std::endl;
  // }
  // glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
  // if (!success)
  // {
  //   glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
  //   std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // glGetProgramiv(fragmentShaderOrange, GL_LINK_STATUS, &success);
  // if (!success)
  // {
  //   glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  //   std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
  // if (!success)
  // {
  //   glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
  //   std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);
  // glDeleteShader(fragmentShader2);

  // float vertices[] = {
  //     0.5f, 0.5f, 0.0f,   // top right
  //     0.5f, -0.5f, 0.0f,  // bottom right
  //     -0.5f, -0.5f, 0.0f, // bottom left
  //     -0.5f, 0.5f, 0.0f   // top left
  // };

  // unsigned int indices[] = {
  //     // note that we start from 0!
  //     0, 1, 3, // first triangle
  //     1, 2, 3  // second triangle
  // };

  // // EBO is Element Buffer Object
  // unsigned int VBO, VAO, EBO, VAO2, VBO2;

  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);

  // glGenVertexArrays(1, &VAO2);
  // glGenBuffers(1, &VBO2);

  // glGenBuffers(1, &EBO);

  // // Bind VAO first, then bind & set vertex buffers, then configure vertex
  // glBindVertexArray(VAO);
  // glBindVertexArray(VAO2);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // glEnableVertexAttribArray(0);

  // // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // // unbinding the vertex array so we won't accideentally modiffy it
  // glBindVertexArray(0);

  // while (!glfwWindowShouldClose(window))
  // {
  //   processInput(window);
  //   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //   glClear(GL_COLOR_BUFFER_BIT);

  //   glUseProgram(shaderProgram);
  //   glBindVertexArray(VAO);  // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
  //   glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
  //   glDrawArrays(GL_TRIANGLES, 0, 3);
  //   glDrawArrays(GL_TRIANGLES, 3, 6);
  //   // glDrawArrays(GL_TRIANGLES, 0, 6); // for two triangles
  //   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);          // bind EBO to GL_ELEMENT_ARRAY_BUFFER
  //   // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // draw elements replaced draw arrays
  //   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);           // wireframe mode
  //   // glBindVertexArray(0); // no need to unbind it every time

  //   // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
  //   // -------------------------------------------------------------------------------
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteVertexArrays(1, &VAO2);
  // glDeleteBuffers(1, &VBO2);
  // glDeleteBuffers(1, &EBO);
  // glDeleteProgram(shaderProgram);

  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
  glGenBuffers(2, VBOs);
  // first triangle setup
  // --------------------
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // Vertex attributes stay the same
  glEnableVertexAttribArray(0);
  // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
  // second triangle setup
  // ---------------------
  glBindVertexArray(VAOs[1]);             // note that we bind to a different VAO now
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
  glEnableVertexAttribArray(0);
  // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramOrange);
    // draw first triangle using the data from the first VAO
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramGreen);
    // then we draw the second triangle using the data from the second VAO
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgramOrange);
  glDeleteProgram(shaderProgramGreen);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}