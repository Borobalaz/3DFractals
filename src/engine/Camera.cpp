#include "Camera.h"

Camera::Camera()
  : position(0.0f, 0.0f, 3.0f)
{
}

Camera::~Camera()
{
}

void Camera::SetPosition(const glm::vec3& pos)
{
  position = pos;
}

glm::vec3 Camera::GetPosition() const
{
  return position;
}