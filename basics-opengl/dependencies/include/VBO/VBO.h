#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
  // Reference ID of the Vertex Buffer Object
  GLuint ID;

  VBO(GLfloat *vertices, GLsizeiptr size);
  void Bind();
  // Unbinds the VBO
  void Unbind();
  // Deletes the VBO
  void Delete();
};

#endif