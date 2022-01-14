cmake_minimum_required(VERSION 3.2.0)
project(Raymarcher)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(DCMAKE_BUILD_TYPE, Debug)
set(CMAKE_CXX_FLAGS_DEBUG, "-O3")

include_directories(${SDL2_INCLUDE_DIRS})

add_library(MathVectors_LIBRARY STATIC
  MathVectors.hpp
  MathVectors.cpp
)

add_library(RayMarch3D_LIBRARY STATIC
  RayMarch3D.cpp
  RayMarch3D.hpp
)

add_executable(${PROJECT_NAME} main.cpp)

if(MACOS_INFO_PLIST_NEEDED) #Info.plist include option

set_target_properties(${PROJECT_NAME} PROPERTIES
MACOSX_BUNDLE ON
MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
)

endif()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} MathVectors_LIBRARY)
target_link_libraries(${PROJECT_NAME} RayMarch3D_LIBRARY)