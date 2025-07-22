# Fastly C++ Compute SDK Quickstart

This is a quickstart project that you're able to copy as-in in order to get
started quickly. It includes a `fastly.toml` with a basic example backend, a
`CMakeLists.txt` with some baseline configuration and a `main.cpp` file with a
scaffolded request handler.

## Requirements

This project should be ready to use as soon as you extract the tarball from the
GitHub release, as long as you have the following prerequisites installed:

- `wasi-sdk`, version `25.0` \*
- `cmake` and `make`

\* Located at `/opt/wasi-sdk`. If you place it elsewhere, you'll need to pass
`-DWASI_SDK=/path/to/wasi-sdk-dist` when you configure with `cmake`.

## Getting Started

Assuming you're in the `quickstart` directory:

```shell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake
```

Then, run the build:

```shell
cmake --build build
```

Now you should be able to use the [Fastly
CLI](https://www.fastly.com/documentation/reference/cli/) to run your Compute
app locally:

```shell
fastly compute serve -C examples --file build/main.wasm
```

And you can curl the app directly from there:

```shell
curl -d "hello, world!" http://127.0.0.1:7676/
```

✨Happy hacking!✨

## Documentation

The release tarball includes the HTML reference docs in `docs/html/index.html`,
which you can open locally. If you've configured your editor properly, you may
also be able to hover over Fastly SDK symbols to see their documentation
in-place.
