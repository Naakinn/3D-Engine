> [!WARNING]
> Highly beta, PRs are allowed.

![](images/preview2.png)
# Hvat?
This is a basic 3D engine implemented in C and C++. It works with [OpenGL Graphics API](https://learnopengl.com/Getting-started/OpenGL) and uses [Glad](https://glad.dav1d.de/) loader. 

System API(creating windows, etc.) comes with [SDL2 library](https://www.libsdl.org/). 

# Why? 
Educational purpose. 3D graphics is pretty cool.

# Dependencies
- [SDL2](https://wiki.libsdl.org/SDL2/Installation#supported_platforms)

# Build
Firstly, clone the repository and initialize submodules(dependencies, like [cglm](https://github.com/recp/cglm)). 
```
$ git clone --recurse-submodules https://github.com/Naakinn/3D-Engine
```

Then build and run. 
```
$ make 
$./engine
```

### Build in debug mode or with some optimizations (-O2)
```
$ make DEBUG=ON
# or 
$ make OPTIMIZE=ON 
$ ./engine
```

