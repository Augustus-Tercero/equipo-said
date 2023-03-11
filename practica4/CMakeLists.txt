cmake_minimum_required(VERSION 3.24)
project(actividad_practica_4_Augustus_Tercero)

set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS system graphics window)

add_executable(actividad_practica_4_Augustus_Tercero
        main.cpp)
target_link_libraries(actividad_practica_4_Augustus_Tercero sfml-system sfml-graphics sfml-window)
