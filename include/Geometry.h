#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "UniformProvider.h"
#include "Shader.h"

struct Vertex
{
  glm::vec3 position;
  glm::vec3 normal;
};

class Geometry : public UniformProvider
{
public:
  Geometry();
  virtual ~Geometry();

  // Core lifecycle
  virtual void Generate() = 0;
  virtual void Upload();
  virtual void Draw(Shader& shader) const;
  virtual void Destroy();

  // Transform operations
  void Translate(const glm::vec3& offset);
  void Rotate(float angle, const glm::vec3& axis);
  void Scale(const glm::vec3& scale);

  glm::mat4 GetModelMatrix() const;

  // Geometry processing
  void ComputeNormals();

  void Apply(Shader& shader) const override;
protected:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
};