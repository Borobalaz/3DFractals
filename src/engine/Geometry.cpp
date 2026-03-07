#include "Geometry.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief Construct a new Geometry:: Geometry object
 * 
 */
Geometry::Geometry()
{
  position = glm::vec3(0.0f);
  rotation = glm::vec3(0.0f);
  scale = glm::vec3(1.0f);

  VAO = 0;
  VBO = 0;
  EBO = 0;
}

/**
 * @brief Destroy the Geometry:: Geometry object
 * 
 */
Geometry::~Geometry()
{
}

/**
 * @brief Generate vertex arrays and bind buffers to the GPU
 * 
 */
void Geometry::Upload()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(Vertex),
    vertices.data(),
    GL_STATIC_DRAW
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(unsigned int),
    indices.data(),
    GL_STATIC_DRAW
  );

  // POSITION
  glVertexAttribPointer(
    0,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, position)
  );
  glEnableVertexAttribArray(0);

  // NORMAL
  glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, normal)
  );
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}

/**
 * @brief Uniformprovider implementation - apply uniforms
 * 
 * @param shader 
 */
void Geometry::Apply(Shader& shader) const
{
  glm::mat4 model = GetModelMatrix();
  shader.SetMat4("model", model);
}

/**
 * @brief Draw the geometry using the provided shader
 * 
 * @param shader 
 */
void Geometry::Draw(Shader& shader) const
{
  shader.Use();
  this->Apply(shader);

  glBindVertexArray(VAO);
  glDrawElements(
    GL_TRIANGLES,
    indices.size(),
    GL_UNSIGNED_INT,
    0
  );
  glBindVertexArray(0);
}

/**
 * @brief Delete VAO, VBO and EBO buffers
 * 
 */
void Geometry::Destroy()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

/**
 * @brief Translate the object
 * 
 * @param offset 
 */
void Geometry::Translate(const glm::vec3& offset)
{
  position += offset;
}

/**
 * @brief 
 * 
 * @param angle 
 * @param axis 
 */
void Geometry::Rotate(float angle, const glm::vec3& axis)
{
  rotation += axis * angle;
}

void Geometry::Scale(const glm::vec3& s)
{
  scale *= s;
}

glm::mat4 Geometry::GetModelMatrix() const
{
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(model, position);

  model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));

  model = glm::scale(model, scale);

  return model;
}

void Geometry::ComputeNormals()
{
  // reset normals
  for (auto& v : vertices)
  {
    v.normal = glm::vec3(0.0f);
  }

  // compute face normals
  for (size_t i = 0; i < indices.size(); i += 3)
  {
    unsigned int i0 = indices[i];
    unsigned int i1 = indices[i + 1];
    unsigned int i2 = indices[i + 2];

    const glm::vec3& v0 = vertices[i0].position;
    const glm::vec3& v1 = vertices[i1].position;
    const glm::vec3& v2 = vertices[i2].position;

    glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

    vertices[i0].normal += normal;
    vertices[i1].normal += normal;
    vertices[i2].normal += normal;
  }

  // normalize vertex normals
  for (auto& v : vertices)
  {
    v.normal = glm::normalize(v.normal);
  }
}