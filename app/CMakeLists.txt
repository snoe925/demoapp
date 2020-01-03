add_executable(demoapp)

set(OPENSSL_INCLUDE_PATH "/usr/local/opt/openssl/include")

target_include_directories(demoapp PRIVATE "${CMAKE_SOURCE_DIR}/app")
target_include_directories(demoapp PRIVATE "${CMAKE_SOURCE_DIR}/../../../boost")
target_include_directories(demoapp PRIVATE "${CMAKE_SOURCE_DIR}/../../../json/single_include")

target_sources(demoapp PUBLIC "demoapp.h")
target_sources(demoapp PUBLIC "main.cpp")

target_compile_options(demoapp PUBLIC "-DDEBUG")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(popeye-shard-writer-test PUBLIC -fcoverage-mapping)
    target_compile_options(popeye-shard-writer-test PUBLIC -fprofile-instr-generate)
    target_link_options(popeye-shard-writer-test PUBLIC -fprofile-arcs)
    target_link_options(popeye-shard-writer-test PUBLIC -ftest-coverage)
endif()

find_package(CURL REQUIRED)

target_include_directories(demoapp PRIVATE ${OPENSSL_INCLUDE_PATH})

if(NOT BUILD_EXTERNAL)
    target_link_libraries(demoapp z)
endif()

target_link_libraries(demoapp ${CURL_LIBRARIES})
