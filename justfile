default: build

[working-directory: "fastly"]
build: cmake
    cmake --build

cmake:
    cmake -S . -B fastly -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk-25.0/share/cmake/wasi-sdk-p1.cmake

[working-directory: "fastly/example"]
example: cmake-example
    cmake --build

cmake-example:
    cmake -S ./example -B fastly/example -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk-25.0/share/cmake/wasi-sdk-p1.cmake

clean:
    rm -rf fastly