#include <VAO/VAO.h>
// Constructor that generates a VAO ID
VAO::VAO()
{
  glGenVertexArrays(1, &ID);
}

// void VAO::LinkVBO(VBO &VBO, GLuint layout)
// {
//   VBO.Bind();
//   glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
//   glEnableVertexAttribArray(layout);
//   VBO.Unbind();
// }

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
  glBindVertexArray(ID);
}

void VAO::Unbind()
{
  glBindVertexArray(0);
}

void VAO::Delete()
{
  glDeleteVertexArrays(1, &ID);
}