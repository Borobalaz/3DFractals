#include "Texture.h"

Texture::Texture()
{
  glGenTextures(1, &id);
}

Texture::~Texture()
{
  glDeleteTextures(1, &id);
}

void Texture::Bind() const
{
  glBindTexture(GL_TEXTURE_2D, id);
}