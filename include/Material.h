#pragma once

#include <memory>
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
  Material();
  Material(std::shared_ptr<Shader> shader);

  void SetShader(std::shared_ptr<Shader> shader);
  void SetTexture(std::shared_ptr<Texture> texture);

  Shader& GetShader() const;

  void Bind() const;

private:
  std::shared_ptr<Shader> shader;
  std::shared_ptr<Texture> texture;
};