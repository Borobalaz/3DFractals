#include "Scene.h"

/**
 * @brief Construct a new Scene:: Scene object
 * 
 */
Scene::Scene()
  : clearColor{0.8f, 0.3f, 0.3f, 1.0f}
{
  // Init objects
  triangle.Generate();

  // Init shaders
  shaders["basic"] = std::make_unique<Shader>(
    "shaders/vertex.glsl",
    "shaders/fragment.glsl"
  );
}

/**
 * @brief Destroy the Scene:: Scene object
 * 
 */
Scene::~Scene()
{
}

/**
 * @brief 
 * 
 */
void Scene::Init()
{
  glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

  triangle.Upload();
}

/**
 * @brief Game loop update function
 * 
 * @param deltaTime 
 */
void Scene::Update(float deltaTime)
{
  triangle.Rotate(deltaTime, glm::vec3(1, 1, 1));
}

/**
 * @brief Scene renderer function
 * 
 */
void Scene::Render()
{
  glClear(GL_COLOR_BUFFER_BIT);

  triangle.Draw(*shaders["basic"]);
}

/**
 * @brief 
 * 
 */
void Scene::Destroy()
{
  triangle.Destroy();
}