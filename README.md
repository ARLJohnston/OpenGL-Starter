# OpenGL-Starter
A base for OpenGL using C and CMake and working batch renderer that automatically polls number of texture slots to minimize draw calls. 

Example in main.c draws 32 unique textures from assets/textures and 6400 coloured quads. 

# CMake:
- Gets GLFW3 from computer, if it isn't found it is downloaded from the git repository
- GLAD is included as recommended in  https://github.com/Dav1dde/glad/issues/186
- stb_image is copied from source (dated 12/04/2022)

# Include Diagram
(Arrow goes from included to file which includes)
[![](https://mermaid.ink/img/pako:eNptkTFvwjAQhf9KdDNUcQIBMnQpjEzt5nSw7Cu22sTIOJQK8d97MU6Mqm7fe_eedbavIK1CqOHgxFFnb9umy7KcW-e1DZaRL6JFJ570-zBi3OPF9w6jLvhJC4UuypI77EiSIYOx-O-o-2jJzyi9HZMVPxv83gvvzCWethoTd7nm7eN0Q9J0sc3yx3r00rLRKNJ68TrluP-QGJxsPZ8_54FYQVgGzIkWgVZEyylYpeAmYEXEYn1ANpVYMbUi5gmrhEVC9sctYQb0gHRtRT92HQYNeI0tNlATKuE-G2i6G-X6oxIed8rQ-0H9Ib5OOAPRe_v600movetxDG2NoP9pY-r2CzH-ob4)](https://mermaid.live/edit#pako:eNptkTFvwjAQhf9KdDNUcQIBMnQpjEzt5nSw7Cu22sTIOJQK8d97MU6Mqm7fe_eedbavIK1CqOHgxFFnb9umy7KcW-e1DZaRL6JFJ570-zBi3OPF9w6jLvhJC4UuypI77EiSIYOx-O-o-2jJzyi9HZMVPxv83gvvzCWethoTd7nm7eN0Q9J0sc3yx3r00rLRKNJ68TrluP-QGJxsPZ8_54FYQVgGzIkWgVZEyylYpeAmYEXEYn1ANpVYMbUi5gmrhEVC9sctYQb0gHRtRT92HQYNeI0tNlATKuE-G2i6G-X6oxIed8rQ-0H9Ib5OOAPRe_v600movetxDG2NoP9pY-r2CzH-ob4)
