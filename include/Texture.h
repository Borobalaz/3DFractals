#pragma once

#include <glad/glad.h>

class Texture
{
public:
  Texture();
  ~Texture();

  void Bind() const;

private:
  unsigned int id;
};