cmake_minimum_required(VERSION 3.21)
project(SerpantinumNative VERSION 0.1.0 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(LayerShellQt REQUIRED CONFIG)
qt_standard_project_setup()

qt_add_executable(serpantinum
 main.cpp
SystemStatus.h
SystemStatus.cpp
)

qt_add_qml_module(serpantinum
    URI Serpantinum
    VERSION 1.0
    QML_FILES Main.qml
)

target_link_libraries(serpantinum PRIVATE Qt6::Quick LayerShellQt::Interface)
