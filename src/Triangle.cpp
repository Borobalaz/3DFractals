#include "Triangle.h"

void Triangle::Generate()
{
  vertices =
  {
    { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f) },
    { glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f) },
    { glm::vec3( 0.0f,  0.5f, 0.0f), glm::vec3(0.0f) }
  };

  indices = { 0, 1, 2 };

  ComputeNormals();
}