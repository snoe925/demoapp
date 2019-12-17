cmake_minimum_required(VERSION 3.14)
project(demoapp)
set(PROJ demoapp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(APPLE)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/../boost_1_72_0/boost")
endif()

option(BUILD_TESTING "Build test programs" OFF)
option(BUILD_EXTERNAL "Download and build external projects" OFF)

if (BUILD_EXTERNAL)
    add_subdirectory("external")
endif()

if(NOT BUILD_TESTING)
    add_subdirectory(app)
else()
    add_subdirectory(test)
endif()
