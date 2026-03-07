#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject()
{
  position = glm::vec3(0.0f);
  rotation = glm::vec3(0.0f);
  scale = glm::vec3(1.0f);
}

GameObject::~GameObject()
{
}

void GameObject::SetGeometry(std::shared_ptr<Geometry> geometry)
{
  this->geometry = geometry;
}

void GameObject::SetMaterial(std::shared_ptr<Material> material)
{
  this->material = material;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw() const
{
  if (!geometry || !material)
  {
    return;
  }

  material->Bind();

  Shader& shader = material->GetShader();

  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(model, position);

  model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
  model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
  model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));

  model = glm::scale(model, scale);

  shader.SetMat4("model", model);

  geometry->Draw(shader);
}