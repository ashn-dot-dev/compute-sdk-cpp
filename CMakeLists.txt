# From https://github.com/XiangpengHao/cxx-cmake-example/blob/master/fastly/CMakeLists.txt

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD cargo build --verbose)
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD cargo build --release --verbose)
    set(TARGET_DIR "release")
endif ()

# If the user is cross compiling to a different target, update the location of the target directory
# *Note*: Make sure to install the target with rustup, as well as setting the proper environment variables, such as CC, HOST_CC, CARGO_TARGET_<triple>_LINKER, ...
# See https://doc.rust-lang.org/cargo/reference/environment-variables.html#configuration-environment-variables
if (DEFINED ENV{CARGO_BUILD_TARGET})
    set(TARGET_DIR "$ENV{CARGO_BUILD_TARGET}/${TARGET_DIR}")
endif()

if(ENABLE_LTO)
    set(CFLAGS "-flto=thin -O0")
    set(CXXFLAGS "-flto=thin -O0")
    set(RUST_FLAGS "-Clinker-plugin-lto" "-Clinker=${CMAKE_CURRENT_SOURCE_DIR}/build-workaround.sh" "-Clink-arg=-fuse-ld=lld")
endif()

set(FASTLY_LIB "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_DIR}/libfastly.a")

set(FASTLY_CXX "${CMAKE_CURRENT_BINARY_DIR}/fastly.cpp")
add_library(fastly STATIC ${FASTLY_CXX})
add_custom_command(
    OUTPUT ${FASTLY_CXX}
    COMMAND CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} RUSTFLAGS="${RUST_FLAGS}" ${CARGO_CMD}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/fastly/src/lib.rs.cc ${FASTLY_CXX}
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/fastly/src/lib.rs.h ${CMAKE_CURRENT_BINARY_DIR}/fastly.h
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/cxxbridge/fastly/src/lib.rs.h ${CMAKE_BINARY_DIR}/libfastly.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fastly pthread dl ${FASTLY_LIB})

add_test(NAME fastly_test 
    COMMAND cargo test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})