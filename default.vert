#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
// layout (location = 2) in vec3 aTex;
layout (location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
out vec3 texCoord;

// Controls the scale of the vertices
// Never declare uniforms unless you will use them
uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
  color = aColor;
  // texCoord = aTex;
  texCoord = vec2(aTex.x, aTex.y);
}