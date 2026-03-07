#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
  unsigned int ID;

  Shader() = default;

  Shader(const std::string& vertexPath,
         const std::string& fragmentPath);

  ~Shader();

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  void Use() const;

  // uniform helpers
  void SetBool(const std::string& name, bool value) const;
  void SetInt(const std::string& name, int value) const;
  void SetFloat(const std::string& name, float value) const;
  void SetVec3(const std::string& name, const glm::vec3& value) const;
  void SetMat4(const std::string& name,const glm::mat4& value) const;

private:
  std::string ReadFile(const std::string& path);
  unsigned int Compile(unsigned int type, const std::string& source);
};