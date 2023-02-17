cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Simulation)

set(Geant4_DIR "/home/pane/modeling-auroral-nuke/GEANT4/geant4-v11.1.0-install/lib/cmake/Geant4")

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(testsim testsim.cc ${sources} ${headers})
target_link_libraries(testsim ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS testsim)
