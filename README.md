# OpenGL-Starter
A base for OpenGL using C and CMake and working batch renderer that automatically polls number of texture slots to minimize draw calls. 

Example in main.c draws 32 unique textures from assets/textures and 6400 coloured quads.
To Use without a batch renderer, delete renderer.c, renderer.h and all includes of it.

# To run
First clone the repository (This must be recursive to clone GLAD)
```git clone --recurse-submodules https://github.com/ARLJay/OpenGL-Starter.git```

Then run a cmake command e.g.  
```cmake -S . -B ./build && cd build```

Note: the example program expects 32 textures (names tex(number).png) to be in assets/textures. If run without these textures they will all appear as black quads.

# CMake:
- Gets GLFW3 from computer, if it isn't found it is downloaded from the git repository and notifies the user
- GLAD is compiled from source (this is downloaded upon cloning the project)
- stb_image is copied from source (dated 12/04/2022)

# Note on including glad
 - Glad can also be included (using a specific version) as reccommended in https://github.com/Dav1dde/glad/issues/186 (see [Previous Commit](https://github.com/ARLJay/OpenGL-Starter/tree/daae626bf5d8b17ada7a22e919aa9e723c829f9c) for an implementation of this approach)

# Include Diagram
(Arrow goes from included to file which includes)
[![](https://mermaid.ink/img/pako:eNptkTFPwzAQhf9KdHOL4qRN2wwslJEJNpvBsg9iQeLKdUpR1f_OOXHigti-9-75dL67gLIaoYZ3Jw9N9rIXXZbl3Drf2MEy6kG26ORd8xpKjHs8-95h1AU_NlKji7LkDjuSZKjBWP3Xaiyt-QmVt1Oy4ieDX0_SO3OO3TZTYpRb3t5WdyRNF1-z_PZ59NKw0SjSePE75TR_SAQn2y6X9_lArCAsB8yJVgNtiNZzsErB3RwcqfpFLLYMyOZGrJg7RcwTVgmLhOyPW8ICaKm0Ck1XvISCAN9giwJqQi3dhwDRXSnXH7T0-KgN7RRq73pcgOy9ff7u1KTHzN5IOlkL9Zv8POL1B3EZpc8)](https://mermaid.live/edit#pako:eNptkTFPwzAQhf9KdHOL4qRN2wwslJEJNpvBsg9iQeLKdUpR1f_OOXHigti-9-75dL67gLIaoYZ3Jw9N9rIXXZbl3Drf2MEy6kG26ORd8xpKjHs8-95h1AU_NlKji7LkDjuSZKjBWP3Xaiyt-QmVt1Oy4ieDX0_SO3OO3TZTYpRb3t5WdyRNF1-z_PZ59NKw0SjSePE75TR_SAQn2y6X9_lArCAsB8yJVgNtiNZzsErB3RwcqfpFLLYMyOZGrJg7RcwTVgmLhOyPW8ICaKm0Ck1XvISCAN9giwJqQi3dhwDRXSnXH7T0-KgN7RRq73pcgOy9ff7u1KTHzN5IOlkL9Zv8POL1B3EZpc8)
