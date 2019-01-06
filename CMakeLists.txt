cmake_minimum_required(VERSION 3.6)
project(glfw-occt-demo)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_TARGET TKmyDrawPlugin)

include_directories(${PROJECT_SOURCE_DIR})

# opencasacde 
# make sure that your "CASROOT" environment variable contains a directory, where "lib/libTKernel.so|lib/libTKernel.dylib|lib/TKernel.lib" is located.
INCLUDE_DIRECTORIES($ENV{CASROOT}/include/opencascade/)
LINK_DIRECTORIES($ENV{CASROOT}/lib/)
SET(OpenCASCADE_LIBS 
  TKernel
  TKService 
  TKV3d 
  TKOpenGl
  TKBRep
  TKGeomBase
  TKGeomAlgo
  TKG3d
  TKG2d
  TKTopAlgo
  TKPrim
)

add_library(${APP_TARGET} SHARED main.cxx)
target_link_libraries(
  ${APP_TARGET}
  ${OpenCASCADE_LIBS}
)
