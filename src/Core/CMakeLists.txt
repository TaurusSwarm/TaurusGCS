cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(HEADERS 
    SwarmManager.h
    Drone.h
    Telemetry.h
)

set(SOURCES
    SwarmManager.cpp
    Drone.cpp 
    Telemetry.cpp
    Swarm.cpp
)

qt_add_library(Core STATIC
    ${HEADERS}
    ${SOURCES}
)

qt_standard_project_setup()

target_link_libraries(Core PUBLIC
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    MAVSDK::mavsdk
)

set_target_properties(Core PROPERTIES
    AUTOMOC ON
)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
