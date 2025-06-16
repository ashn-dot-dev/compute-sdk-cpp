if(!WASI_SDK)
    set(WASI_SDK "/opt/wasi-sdk")
endif() 

set(CMAKE_C_COMPILER "${WASI_SDK}/bin/clang")
set(CMAKE_CXX_COMPILER "${WASI_SDK}/bin/clang++")

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif ()

project(cxx_example)
cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_STANDARD 17)

option(ENABLE_LTO "Enable cross language linking time optimization" ON)
if(ENABLE_LTO)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT supported OUTPUT error)
  if(supported)
      message(STATUS "IPO / LTO enabled")
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
      add_link_options(-fuse-ld=lld)
  else()
      message(STATUS "IPO / LTO not supported: <${error}>")
  endif()
endif()

add_link_options(-L${WASI_SDK}/share/wasi-sysroot/lib/wasm32-wasi)

add_subdirectory(.. fastly)

add_executable(main main.cpp)

target_link_libraries(main fastly)
