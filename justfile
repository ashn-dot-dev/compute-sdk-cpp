default: build

wasi-sdk := "/opt/wasi-sdk"

clean:
    rm -rf fastly
    
example: build-example
    fastly compute serve -C example --file ../fastly/example/main

strip-example: build-example
    {{wasi-sdk}}/bin/strip ./fastly/example/main
    
build-example: cmake-example
    cmake --build fastly/example
    
cmake-example:
    cmake -S ./example -B fastly/example -DWASI_SDK={{wasi-sdk}} -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE={{wasi-sdk}}/share/cmake/wasi-sdk-p1.cmake
    
build: cmake
    cmake --build fastly

cmake:
    cmake -S . -B fastly -DWASI_SDK={{wasi-sdk}} -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE={{wasi-sdk}}/share/cmake/wasi-sdk-p1.cmake
