cmake_minimum_required(VERSION 3.6)
project(glfw-occt-demo)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)
set(APP_TARGET TKmyDrawPlugin)

include_directories(${PROJECT_SOURCE_DIR})

# opencasacde 
set(OpenCASCADE_DIR "/home/user/opt/occt_77/lib/cmake/opencascade")
find_package(OpenCASCADE REQUIRED NO_DEFAULT_PATH)
if (OpenCASCADE_FOUND)
  message (STATUS "Using OpenCASCADE from \"${OpenCASCADE_DIR}\"" )
  INCLUDE_DIRECTORIES(${OpenCASCADE_INCLUDE_DIR})
  LINK_DIRECTORIES(${OpenCASCADE_LIBRARY_DIR})
else()
  message (WARNING "Could not find OpenCASCADE, please set OpenCASCADE_DIR variable." )
  set (OCCT_LIBRARY_DIR)
  set (OCCT_BIN_DIR)
endif()

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
