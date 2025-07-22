cmake_minimum_required(VERSION 3.15)

# Set this wherever you have the `libfastly.a` + `fastly/*.h`
set(FASTLY_RELEASE_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/..)

if(!WASI_SDK)
    set(WASI_SDK "/opt/wasi-sdk")
endif()
set(CMAKE_C_COMPILER "${WASI_SDK}/bin/clang")
set(CMAKE_CXX_COMPILER "${WASI_SDK}/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif ()

project(quickstart)

set (CMAKE_CXX_STANDARD 17)

add_link_options(-L${WASI_SDK}/share/wasi-sysroot/lib/wasm32-wasi)

add_executable(main main.cpp)

if(MSVC)
    target_compile_options(main PRIVATE /W3 /WX)
else()
    target_compile_options(main PRIVATE -Wall -Wextra -Werror)
endif()

set_target_properties(main PROPERTIES SUFFIX .wasm)
target_include_directories(main PUBLIC ${FASTLY_RELEASE_LOCATION})
target_link_libraries(main ${FASTLY_RELEASE_LOCATION}/libfastly.a)
