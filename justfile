default: build

wasi-sdk := "/opt/wasi-sdk"
default-example := "basic"

clean:
    rm -rf fastly
    
example name=default-example: (build-example name)
    fastly compute serve -C examples --file ../fastly/examples/main

strip-example name=default-example: (build-example name)
    {{wasi-sdk}}/bin/strip ./fastly/examples/main
    
build-example name=default-example: (cmake-example name)
    cmake --build fastly/examples
    
cmake-example name=default-example:
    cmake -S ./examples -B fastly/examples -DWASI_SDK={{wasi-sdk}} -DEXAMPLE_NAME={{name}} -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE={{wasi-sdk}}/share/cmake/wasi-sdk-p1.cmake
    
build: cmake
    cmake --build fastly

cmake:
    cmake -S . -B fastly -DWASI_SDK={{wasi-sdk}} -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE={{wasi-sdk}}/share/cmake/wasi-sdk-p1.cmake
