cmake_minimum_required(VERSION 3.16)

find_package(Qt6 REQUIRED COMPONENTS Core Location Positioning)

qt_add_library(FlightMap STATIC
    
)

qt_standard_project_setup()

target_link_libraries(FlightMap PUBLIC
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
)

set_target_properties(FlightMap PROPERTIES
    AUTOMOC ON
)

target_include_directories(FlightMap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
