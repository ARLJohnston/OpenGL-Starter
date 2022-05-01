cmake_minimum_required(VERSION 3.6)
project(OpenGL C)

#Libraries
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)

#find_package(glad CONFIG REQUIRED)
#if(!${glad_found})
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG master)
FetchContent_MakeAvailable(glad)
#endif()

find_package(glfw3 3.3 REQUIRED)
message(STATUS "GLFW was found")
if(!${glfw3_found})
	message(STATUS "GLFW was not found, downloading from source (Recommended to install glfw)")
	FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
	FetchContent_MakeAvailable(glfw)
endif()


#Executable
add_executable(${PROJECT_NAME} "src/main.c")
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_link_libraries(${PROJECT_NAME} 
	glad 
	glfw
	m
	)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)
