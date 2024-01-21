#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char *filename);

class Shader
{
public:
  // Reference ID of the Shader Program
  GLuint ID;
  // Constructor that build the Shader Program from 2 different shaders
  Shader(const char *vertexFile, const char *fragmentFile);

  // Activates the Shader Program
  void use();

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  // Deletes the Shader Program
  void Delete();

private:
  // Checks if the different Shaders have compiled properly
  void compileErrors(unsigned int shader, const char *type);
};

#endif