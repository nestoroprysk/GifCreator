#general configurations

cmake_minimum_required(VERSION 3.1.0)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are prohibited. Sorry :(")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

#project configurations

project(GifCreator)

add_executable(GifCreator main.cpp)

target_include_directories(GifCreator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GifCreator Core Registrar)

#qt configurations

set(Qt5_DIR "/Users/nestoroprysk/Qt/5.11.1/clang_64/lib/cmake/Qt5"
   CACHE PATH "Enter the path to the Qt5 please")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

set(CMAKE_AUTOUIC ON)

#core configurations

file(GLOB CoreSources
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/ConcreteObjects/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/ConcreteObjects/*.hpp)

add_library(Core SHARED ${CoreSources})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Registrar configurations

file(GLOB RegistrarSources
        ${CMAKE_CURRENT_SOURCE_DIR}/Registrar/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Registrar/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Registrar/*.hpp)

add_library(Registrar SHARED ${RegistrarSources})

target_link_libraries(Registrar Core Qt5::Widgets)

target_include_directories(Registrar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
