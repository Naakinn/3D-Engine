![](images/preview2.png)
# Hvat?
This is a basic 3D engine implemented in C and C++. It works with [OpenGL Graphics API](https://learnopengl.com/Getting-started/OpenGL) and uses [Glad](https://glad.dav1d.de/) loader. 

System API(creating windows, etc.) comes with [SDL2 library](https://www.libsdl.org/). 

# Why? 
For educational purpose. Also I found myself fond of 3D graphics and think I will be working in this subject later. 

# Dependencies
- [GLM](https://github.com/g-truc/glm)
  - System wide [here](https://github.com/g-truc/glm?tab=readme-ov-file#build-and-install)
  
  Or
  - Locally
  
    Just clone git repository of [glm](https://github.com/g-truc/glm) and put `glm` directory inside engine's `include` directory
    ```
    cd path/to/glm
    mv glm path/to/project/include
    ```
- [SDL2](https://wiki.libsdl.org/SDL2/Installation#supported_platforms)
# Build
```
$ cmake -B build
$ cmake --build build 
```
### Build in debug mode
```
$ cmake -B build -DDEBUG=ON
$ cmake --build build 
```
# Run 
```
$ ./engine
```

