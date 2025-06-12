# compute-sdk-cpp

Creates a static library for C++ usage.

## Building

### Requirements

* `rustc`/`cargo`, which can be installed through [`rustup`](https://rustup.sh)
* `clang`
* `lld`
* `cmake`
* `make`

### Preparing

```sh
cmake -S . -B fastly -DENABLE_LTO=ON -DCMAKE_BUILD_TYPE=Release
```

### Actually Building

```sh
make -j
```

You'll get a `fastly.a`.