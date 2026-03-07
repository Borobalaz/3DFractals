#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Construct a new Shader:: Shader object
 * 
 * @param vertexPath 
 * @param fragmentPath 
 */
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  std::string vertexCode = ReadFile(vertexPath);
  std::string fragmentCode = ReadFile(fragmentPath);

  unsigned int vertexShader =
    Compile(GL_VERTEX_SHADER, vertexCode);

  unsigned int fragmentShader =
    Compile(GL_FRAGMENT_SHADER, fragmentCode);

  if (vertexShader == 0 || fragmentShader == 0) {
    std::cout << "Shader compilation failed\n";
    ID = 0;
    return;
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  int success;
  char infoLog[512];

  glGetProgramiv(ID, GL_LINK_STATUS, &success);

  if (!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "Shader linking failed:\n"
              << infoLog << std::endl;
    glDeleteProgram(ID);
    ID = 0;
  } else
  {
    std::cout << "Shader linked successfully\n";
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

/**
 * @brief Destroy the Shader:: Shader object
 * 
 */
Shader::~Shader()
{
  glDeleteProgram(ID);
}

/**
 * @brief Set the shader as active
 * 
 */
void Shader::Use() const
{
  glUseProgram(ID);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    std::cout << "GL error after glUseProgram: " << error << std::endl;
  }
}

/**
 * @brief Set a boolean uniform in the shader
 * 
 * @param name 
 * @param value 
 */
void Shader::SetBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

/**
 * @brief Set an integer uniform in the shader
 * 
 * @param name 
 * @param value 
 */
void Shader::SetInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

/**
 * @brief Set a float uniform in the shader
 * 
 * @param name 
 * @param value 
 */
void Shader::SetFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

/**
 * @brief Set a vec3 uniform in the shader
 * 
 * @param name 
 * @param value 
 */
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
  glUniform3fv(
    glGetUniformLocation(ID, name.c_str()),
    1,
    glm::value_ptr(value)
  );
}

/**
 * @brief Set a mat4 uniform in the shader
 * 
 * @param name 
 * @param value 
 */
void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
  GLint location = glGetUniformLocation(ID, name.c_str());
  if (location == -1) {
    std::cout << "Uniform '" << name << "' not found in shader " << ID << std::endl;
  } else {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
  }
}

/* --------------------------------------------------------- */
/* -------------------- private methods -------------------- */
/* --------------------------------------------------------- */

std::string Shader::ReadFile(const std::string& path)
{
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Failed to open shader file: " << path << std::endl;
    return "";
  }
  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

unsigned int Shader::Compile(unsigned int type, const std::string& source)
{
  unsigned int shader = glCreateShader(type);

  const char* code = source.c_str();
  glShaderSource(shader, 1, &code, NULL);

  glCompileShader(shader);

  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "Shader compilation error:\n"
              << infoLog << std::endl;
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}
