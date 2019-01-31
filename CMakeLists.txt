cmake_minimum_required(VERSION 3.0)

MESSAGE("This template works on linux")

project(chess)



SET(CMAKE_MODULE_PATH "/home/michaelz/Desktop/projects/courses/22L/chess")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()



SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

find_package (PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK2 REQUIRED gtk+-2.0)

FIND_PACKAGE(GTK2 REQUIRED)



INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include" 
${GTK2_INCLUDE_DIRS}
)

LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib" 
${GTK2_LINK_FLAGS})

LINK_LIBRARIES(${SDL_LIBRARY} ${GTK2_LIBRARIES}${GTK2_LINK_FLAGS})



AUX_SOURCE_DIRECTORY(src DIR_SRCS )
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# set(SOURCE src/SDL_Sample.c)
# add_executable(${PROJECT_NAME} ${SOURCE})



