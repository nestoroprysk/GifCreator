#general configurations

cmake_minimum_required(VERSION 3.1.0)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds are prohibited. Sorry :(")
endif()

if (NOT APPLE)
    message(FATAL_ERROR
    "The project may be built only in macOS for now. Sorry :(")
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

#project configurations

project(GifCreator)

add_executable(GifCreator main.cpp)

target_include_directories(GifCreator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GifCreator Core Gui EncoderDecoder)

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

add_library(Core STATIC ${CoreSources})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#gui configurations

file(GLOB GuiSources
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/*.hpp)

add_library(Gui STATIC ${GuiSources})

target_link_libraries(Gui Qt5::Widgets)

target_include_directories(Gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#encoderDecoder configurations

file(GLOB EncoderDecoderSources
        ${CMAKE_CURRENT_SOURCE_DIR}/EncoderDecoder/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/EncoderDecoder/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EncoderDecoder/*.hpp)

add_library(EncoderDecoder STATIC ${EncoderDecoderSources})

target_link_libraries(EncoderDecoder Qt5::Widgets)

target_include_directories(EncoderDecoder PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
