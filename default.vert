#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aText;

out vec3 colour;
out vec2 textCoord;

uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0);
   colour = aColor;
   textCoord = aText;
}