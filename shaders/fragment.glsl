#version 330 core

in vec4 posColor;
in vec3 fragNormal;
out vec4 FragColor;

void main()
{
  FragColor = vec4(fragNormal * 0.5 + 0.5, 1.0);
}