#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Geometry.h"
#include "Material.h"

class GameObject
{
public:
  GameObject();
  ~GameObject();

  void SetGeometry(std::shared_ptr<Geometry> geometry);
  void SetMaterial(std::shared_ptr<Material> material);

  void Update(float deltaTime);
  void Draw() const;

  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

private:
  std::shared_ptr<Geometry> geometry;
  std::shared_ptr<Material> material;
};