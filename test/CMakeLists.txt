if(EXISTS "${CMAKE_SOURCE_DIR}/../googletest")
    set(GTEST_ROOT "${CMAKE_SOURCE_DIR}/../googletest")
    find_package(GTEST REQUIRED)
else()
    message(FATAL_ERROR "googletest is not installed")
endif()

add_executable(demoapp-test)
add_test(NAME demoapp-test COMMAND demoapp-test)

target_compile_options(demoapp-test PUBLIC -DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
target_compile_options(demoapp-test PUBLIC -O0)
target_compile_options(demoapp-test PUBLIC -g)
if(APPLE)
    target_compile_options(demoapp-test PUBLIC -fcoverage-mapping)
    target_compile_options(demoapp-test PUBLIC -fprofile-instr-generate)
    target_link_options(demoapp-test PUBLIC -fprofile-arcs)
    target_link_options(demoapp-test PUBLIC -ftest-coverage)
endif()

target_sources(demoapp-test PRIVATE main.cpp)
target_sources(demoapp-test PRIVATE demoapp_test.cpp)
target_sources(demoapp-test PRIVATE ${CMAKE_SOURCE_DIR}/app/demoapp.h)

target_include_directories(demoapp-test PRIVATE ${CMAKE_SOURCE_DIR}/app)
target_include_directories(demoapp-test PRIVATE ${GTEST_INCLUDE_DIRS})
target_include_directories(demoapp-test PRIVATE ${OPENSSL_INCLUDE_DIR})
target_include_directories(demoapp-test PRIVATE /usr/local/include)

if(NOT BUILD_EXTERNAL)
#    target_link_libraries(demoapp-test ${BOOST_ROOT}/lib/libboost_iostreams.a)
endif()

target_link_libraries(demoapp-test ${GTEST_LIBRARIES} pthread)
