cmake_minimum_required(VERSION 3.10)

project(3DEngine)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_NAME engine)

option(USE_MOLD "Use mold instead of standard gnu ld(installation required)" ON)
option(DEBUG "Build in debug output mode" ON)

set(SRC 
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/render.cpp 
	${PROJECT_SOURCE_DIR}/src/input.c 
	${PROJECT_SOURCE_DIR}/src/init.c 
	${PROJECT_SOURCE_DIR}/src/glad.c 
	)

add_link_options(-lm -lSDL2)

if(USE_MOLD) 
	add_link_options(-fuse-ld=mold)
endif()

add_executable(${EXECUTABLE_NAME} ${SRC})

if(DEBUG) 
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE "DEBUG")
endif()

target_include_directories(${EXECUTABLE_NAME} PUBLIC 
	${PROJECT_SOURCE_DIR}/include 
	/usr/local/include/SDL2/
)
