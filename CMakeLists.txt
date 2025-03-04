
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Neutrons)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(neutrons main.cc ${sources} ${headers})
target_link_libraries(neutrons ${Geant4_LIBRARIES})

set(SCRIPTS
  init_vis.mac
  run.mac
  run.png
  vis.mac
  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(Neutrons DEPENDS neutrons)

install(TARGETS neutrons DESTINATION bin)


