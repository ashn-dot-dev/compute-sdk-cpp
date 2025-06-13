# compute-sdk-cpp

Creates a static library for C++ usage.

See `example/` on usage.

### Requirements

* `rustc`/`cargo`, which can be installed through [`rustup`](https://rustup.sh)
* `clang`
* `lld`
* `cmake`
* `make`
* `wasi-sdk-25.0` installed as `/opt/wasi-sdk-25.0` (yes, I'll fix this)
* `just`

### Building Static library

```sh
just
```

### Building example

```sh
just example
```