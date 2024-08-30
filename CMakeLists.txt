cmake_minimum_required(VERSION 3.10)

# set(CMAKE_C_COMPILER "gcc")

project(engine)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SRC 
	${PROJECT_SOURCE_DIR}/main.c 
	${PROJECT_SOURCE_DIR}/render.c 
	${PROJECT_SOURCE_DIR}/input.c 
	${PROJECT_SOURCE_DIR}/sdl.c 
	)

add_compile_options(-ggdb -D_REENTRANT)

add_link_options(-lm -L/usr/local/lib, -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR}/include 
	/usr/local/include/SDL2/
)
