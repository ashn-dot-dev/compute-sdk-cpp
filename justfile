default: build

alias b := build

[working-directory: "fastly"]
build: cmake
    make -j

cmake:
    cmake -S . -B fastly -DENABLE_LTO=OFF -DCMAKE_BUILD_TYPE=Release

clean:
    rm -rf fastly