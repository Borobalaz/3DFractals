#pragma once

class Shader;

class UniformProvider
{
public:
  virtual ~UniformProvider() = default;

  virtual void Apply(Shader& shader) const = 0;
};