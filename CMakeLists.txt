cmake_minimum_required(VERSION 3.14)
project(VGL C CXX)
set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(lib/glfw)
#add_subdirectory(libs)

find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)

add_definitions(-DGL_SILENCE_DEPRECATION)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/libs)
file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
link_directories(libs)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

list(APPEND SOURCES
    Headers/sources.cpp
    Headers/VAO.cpp
    Headers/VBO.cpp
    Headers/EBO.cpp
)

add_executable(Random src/main.cpp ${SOURCES})
add_executable(tut1 src/tuts/tut1_shader.cpp ${SOURCES})

if(WIN32)
    list(APPEND EXTRA_LIBS
        "-lglfw3 -lSOIL -lglu32 -lopengl32 -lglew32"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else()
    list(APPEND EXTRA_LIBS
        "-lGL -lGLU -lSOIL -lGLEW -lglfw"
    )
endif()

# target_link_libraries(VGL glfw ${EXTRA_LIBS})
target_link_libraries(Random GLEW::GLEW ${EXTRA_LIBS})
target_link_libraries(tut1 GLEW::GLEW ${EXTRA_LIBS})
# target_link_libraries(Random ${GLEW_LIBRARY})
