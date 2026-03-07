#pragma once
#include <GLFW/glfw3.h>
#include "Triangle.h"
#include "Shader.h"
#include <memory>

class Shader;
class Triangle;

class Scene
{
public:
  Scene();
  ~Scene();
  
  void Init();
  void Update(float deltaTime);
  void Render();
  void Destroy();

private:
  float clearColor[4];
  
  // Objects
  Triangle triangle;

  // Shaders
  std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};