fn main() {
    let _build = cxx_build::bridge("src/lib.rs")
        .target("wasm32-wasip2")
        .compiler("/opt/wasi-sdk-25.0/bin/clang")
        .flag("--sysroot=/opt/wasi-sdk-25.0/share/wasi-sysroot")
        .flag("-DRUST_CXX_NO_EXCEPTIONS");

    println!("cargo:rerun-if-changed=src/lib.rs");
}
