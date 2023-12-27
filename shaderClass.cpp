#include <shaders/shaderClass.h>

std::string get_file_contents(const char *filename)
{
  std::cout << "get_file_contents:filename:" << filename << std::endl;

  std::ifstream in(filename, std::ios::binary);
  // There is an error in "in"
  if (in.is_open())
  {
    std::cout << "File is open and ready for reading." << std::endl;
  }
  else
  {
    std::cerr << "Failed to open file: " << filename << std::endl;
    std::cerr << "Error opening file: " << strerror(errno) << std::endl;
  }
  if (in)
  {
    std::cout << "shaderClass:get_file_contents:is in:" << '\n';
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    std::cout << "shaderClass:get_file_contents:contents:" << contents << '\n';
    return (contents);
  }
  std::cout << "shaderClass:get_file_contents:errno:" << errno << '\n';
  throw(errno);
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  glLinkProgram(ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
  glUseProgram(ID);
}

void Shader::Delete()
{
  glDeleteProgram(ID);
}