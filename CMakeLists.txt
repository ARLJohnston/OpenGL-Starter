cmake_minimum_required(VERSION 3.6)
project(OpenGL C)

#Libraries
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG master)

FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)

#Executable
add_executable(${PROJECT_NAME} "src/main.c")
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw assimp)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
