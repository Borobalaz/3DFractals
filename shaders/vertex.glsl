#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
out vec4 posColor;
out vec3 fragNormal;

void main()
{
  gl_Position = model * vec4(aPos, 1.0);
  posColor = vec4(aPos, 1.0);
  fragNormal = normal;
}