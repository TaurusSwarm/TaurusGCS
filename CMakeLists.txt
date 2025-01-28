cmake_minimum_required(VERSION 3.16)

project(TaurusGCS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(MAVSDK REQUIRED)

qt_add_executable(TaurusGCS
    src/main.cpp
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
