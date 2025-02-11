cmake_minimum_required(VERSION 3.16)

project(TaurusGCS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(MAVSDK REQUIRED)

qt_add_executable(TaurusGCS
    src/main.cpp
    src/TaurusGCS.h
    src/TaurusGCS.cpp
    Qml.qrc
    Resources.qrc
)

add_subdirectory("src/Core/")
add_subdirectory("src/FlightMap")

target_link_libraries(TaurusGCS PUBLIC
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    MAVSDK::mavsdk
    Core
    FlightMap
)

# Set the install prefix to /usr/local
set(CMAKE_INSTALL_PREFIX /usr/local CACHE STRING "Install prefix" FORCE)

# Include directory for Core module
target_include_directories(TaurusGCS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Core>
    $<INSTALL_INTERFACE:include>
)
