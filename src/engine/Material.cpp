#include "Material.h"

Material::Material()
{
}

Material::Material(std::shared_ptr<Shader> shader)
  : shader(shader)
{
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
  this->shader = shader;
}

void Material::SetTexture(std::shared_ptr<Texture> texture)
{
  this->texture = texture;
}

Shader& Material::GetShader() const
{
  return *shader;
}

void Material::Bind() const
{
  if (shader)
  {
    shader->Use();
  }

  if (texture)
  {
    texture->Bind();
  }
}