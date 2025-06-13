# From https://github.com/XiangpengHao/cxx-cmake-example/blob/master/fastly/CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(compute-sdk-cpp)

set (CMAKE_CXX_STANDARD 11)

set(TARGET_TRIPLE wasm32-wasip1)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build --target=${TARGET_TRIPLE} --verbose)
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD cargo build --target=${TARGET_TRIPLE} --release --verbose)
    set(TARGET_DIR "release")
endif ()

# If the user is cross compiling to a different target, update the location of the target directory
# *Note*: Make sure to install the target with rustup, as well as setting the proper environment variables, such as CC, HOST_CC, CARGO_TARGET_<triple>_LINKER, ...
# See https://doc.rust-lang.org/cargo/reference/environment-variables.html#configuration-environment-variables
if (DEFINED ENV{CARGO_BUILD_TARGET})
    set(TARGET_DIR "$ENV{CARGO_BUILD_TARGET}/${TARGET_DIR}")
endif()

set(CC "/opt/wasi-sdk-25.0/bin/clang")
set(CXX "/opt/wasi-sdk-25.0/bin/clang++")

if(ENABLE_LTO)
    set(CFLAGS "-flto=thin -Oz")
    set(CXXFLAGS "-flto=thin -Oz --sysroot=/opt/wasi-sdk-25.0/share/wasi-sysroot -DRUST_CXX_NO_EXCEPTIONS")
    set(RUST_FLAGS "-Clinker-plugin-lto" "-Clinker=${CMAKE_CURRENT_SOURCE_DIR}/build-workaround.sh" "-Clink-arg=-fuse-ld=lld" "-L/opt/wasi-sdk-25.0/share/wasi-sysroot/lib/wasm32-wasi" "-lstatic=c++" "-lstatic=c++abi")
else()
    set(CXXFLAGS "--sysroot=/opt/wasi-sdk-25.0/share/wasi-sysroot -DRUST_CXX_NO_EXCEPTIONS")
    set(RUST_FLAGS "-L/opt/wasi-sdk-25.0/share/wasi-sysroot/lib/wasm32-wasi" "-lstatic=c++" "-lstatic=c++abi")
endif()

set(FASTLY_LIB "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_TRIPLE}/${TARGET_DIR}/libfastly.a")

set(FASTLY_CXX "${CMAKE_CURRENT_BINARY_DIR}/fastly.cpp")
add_library(fastly STATIC ${FASTLY_CXX})
add_custom_command(
    OUTPUT ${FASTLY_CXX} ${FASTLY_LIB} ${CMAKE_CURRENT_BINARY_DIR}/fastly.h ${CMAKE_CURRENT_BINARY_DIR}/util.h
    COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} CC=${CC} CXX=${CXX} CFLAGS=${CFLAGS} CXXFLAGS=${CXXFLAGS} RUSTFLAGS="${RUST_FLAGS}" ${CARGO_CMD}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/fastly/src/lib.rs.cc ${FASTLY_CXX}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/fastly/src/lib.rs.h ${CMAKE_CURRENT_BINARY_DIR}/fastly.h
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/include/util.h ${CMAKE_CURRENT_BINARY_DIR}/util.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fastly ${FASTLY_LIB})
target_include_directories(fastly INTERFACE ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME fastly_test 
    COMMAND cargo test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})