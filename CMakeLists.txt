cmake_minimum_required(VERSION 3.6)
project(OpenGL C)
set(CMAKE_BUILD_TYPE Debug)

#Top-level flags to show all errors
#if(MVSC)
#	add_compile_options(/W3 /WX)
#else()
#	add_compile_options(-W -Wall -Werror)
#endif()

#Libraries
find_package(OpenGL REQUIRED)

add_subdirectory(glad/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(glfw3 3.3 REQUIRED)
if(!${glfw3_found})
	message(STATUS "GLFW was not found, downloading from source")
	FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
	FetchContent_MakeAvailable(glfw)
endif()

#Executable
set(SOURCES 
	src/main.c
	src/shader.c
	src/texture.c
	src/vector.c
	include/stb_image.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "src" "include")
target_link_libraries(${PROJECT_NAME} 
	glad
	glfw
	m
	)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
									 COMMAND ${CMAKE_COMMAND} -E copy_directory
									 		${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
	)
