#version 330 core
out vec4 FragColor;

// Inputs the color from the Vertex Shader
in vec3 color;
in vec2 texCoord;

// sampler is made available by the GLSL for us to be
// able to pass data belonging to the texture object
// in our case it's sampler2D  
uniform sampler2D tex0;

void main()
{
  FragColor = texture(tex0, texCoord);
}