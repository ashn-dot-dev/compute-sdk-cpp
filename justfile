default: build

alias b := build

[working-directory: "fastly"]
build: cmake
    make -j

cmake:
    cmake -S . -B fastly -DENABLE_LTO=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk-25.0/share/cmake/wasi-sdk-p2.cmake

[working-directory: "fastly/example"]
example: cmake-example
    make -j

cmake-example:
    cmake -S ./example -B fastly/example -DENABLE_LTO=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk-25.0/share/cmake/wasi-sdk-p2.cmake

clean:
    rm -rf fastly