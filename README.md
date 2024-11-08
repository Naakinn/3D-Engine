![](images/preview2.png)
# Why? 
For educational purpose.
## Dependencies 
### Install system-wide 
- [GLM](https://github.com/g-truc/glm?tab=readme-ov-file#build-and-install)
### Locally
Just clone git repository of [glm](https://github.com/g-truc/glm?tab=readme-ov-file#build-and-install) and put `glm` directory in engine's `include` directory

## Build
```
$ cmake -B build
$ cmake --build build 
```
## Build in debug mode
```
$ cmake -B build -DDEBUG=ON
$ cmake --build build 
```
## Run 
```
$ ./engine
```

