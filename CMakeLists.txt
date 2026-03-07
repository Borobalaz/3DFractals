cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(Connectomics-Imaging)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# remove any duplicate entries (e.g. same file through different paths)
list(REMOVE_DUPLICATES SOURCES)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE include)

target_link_libraries(app
    OpenGL::GL
    glfw
    glm::glm
    glad::glad
)

if (WIN32)
  add_custom_command(TARGET app POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:glfw>
          $<TARGET_FILE_DIR:app>)
endif()