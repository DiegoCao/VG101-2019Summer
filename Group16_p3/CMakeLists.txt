#cmake_minimum_required(VERSION 2.7)
#project(p3)
#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-Werror -pedantic -Wall -Wextra")

#set(SOURCE_FILES p3.cpp test.cpp car.cpp Curve.cpp spacecraft.cpp Group.cpp UFO.cpp Setting.cpp Park.cpp)
#add_executable(p3 ${SOURCE_FILES})

#target_link_libraries(p3 freeglut opengl32 glu32)
#add_executable(part1 part1main.cpp generic_parkinglot)

#the cmake for mingw 32 is below...

cmake_minimum_required(VERSION 2.7)
project(p3)

# Set the C++ Standard (you can use 98, 11, but 14 is recommended now)
set(CMAKE_CXX_STANDARD 14)

# Set the compiling flags (don't modify)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic -Wno-unused-result -Wno-deprecated-declarations")

# Find the OpenGL library (don't modify)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Find the GLUT library (don't modify)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# Build Part 1 of the project (add all of related files)
add_executable(p3_part2 p3.cpp Group.cpp UFO.cpp Park.cpp car.cpp Curve.cpp Setting.cpp spacecraft.cpp test.cpp)

# Build Part 2 of the project (add all of related files)
add_executable(p3_part1 part1main.cpp generic_parkinglot.cpp )

# Link the OpenGL, GLUT and Maths library to your project (don't modify)
target_link_libraries(p3_part2 ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)