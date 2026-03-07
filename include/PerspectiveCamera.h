#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(
    float fov,
    float aspect,
    float nearPlane,
    float farPlane
  );

  virtual ~PerspectiveCamera();

  glm::mat4 GetViewMatrix() const override;
  glm::mat4 GetProjectionMatrix() const override;

  void Update(float deltaTime) override;

  void LookAt(const glm::vec3& target);

private:
  glm::vec3 front;
  glm::vec3 up;

  float fov;
  float aspect;
  float nearPlane;
  float farPlane;
};