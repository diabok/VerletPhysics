cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME VerletPhysics)
project(${PROJECT_NAME} VERSION 1.0)

file(GLOB_RECURSE source_files
    "src/*.cpp"
    "include/*.hpp"
   )

set(SOURCES ${source_files})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

add_executable(${PROJECT_NAME} ${WIN32_GUI} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "src" "lib")
set(SFML_LIBS sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} pthread)



