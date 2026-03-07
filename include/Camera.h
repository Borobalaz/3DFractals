#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
  Camera();
  virtual ~Camera();

  virtual glm::mat4 GetViewMatrix() const = 0;
  virtual glm::mat4 GetProjectionMatrix() const = 0;

  virtual void Update(float deltaTime) = 0;

  void SetPosition(const glm::vec3& pos);
  glm::vec3 GetPosition() const;

protected:
  glm::vec3 position;
};