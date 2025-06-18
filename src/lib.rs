use http::{
    header::*,
    request::*,
    response::*,
};

mod http;

// Unfortunately, due to some limitations with cxx, the ENTIRE bridge basically
// has to be under a single ffi module, or cross-referencing ffi types is gonna
// break.
#[cxx::bridge]
mod ffi {
    #[namespace = "fastly::sys::http"]
    pub enum Method {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        CONNECT,
        PATCH,
        TRACE,
    }
    
    #[namespace = "fastly::sys::http"]
    extern "Rust" {
        type HeaderIter;
        fn next(&mut self) -> UniquePtr<CxxVector<u8>>;
    }
    
    #[namespace = "fastly::sys::http"]
    extern "Rust" {
        type Request;
        
        // Static methods
        fn m_static_http_request_get(url: &CxxString) -> Box<Request>;
        fn m_static_http_request_new(method: Method, url: &CxxString) -> Box<Request>;
        fn m_static_http_request_from_client() -> Box<Request>;
        
        // Regular methods
        fn get_header_all(&self, name: &CxxString) -> Box<HeaderIter>;
        fn set_auto_decompress_gzip(&mut self, gzip: bool);
        fn set_body(&mut self, body: &CxxVector<u8>);
    }
    
    #[namespace = "fastly::sys::http"]
    extern "Rust" {
        type Response;
        fn m_static_http_response_new() -> Box<Response>;
        fn m_static_http_response_from_body(body: &CxxVector<u8>) -> Box<Response>;
        fn m_http_response_send_to_client(response: Box<Response>);
        fn set_body(&mut self, body: &CxxVector<u8>);
    }
}