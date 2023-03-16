cmake_minimum_required(VERSION 2.8)

project(PACMAN) # tells CMAKE how the executable is to be named

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED) # tells CMAKE OpenGL is required to build the executable. Will fail if not found on the system
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

file(GLOB SRC
     "*.cpp"
)
message("FILES: " + ${SRC})


add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})# tells CMAKE to include the OpenGl libraries (dll, so. etc.)
