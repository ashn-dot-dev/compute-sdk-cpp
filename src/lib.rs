use cxx::{CxxString, CxxVector, UniquePtr};

pub struct HeaderIter(Box<dyn Iterator<Item = UniquePtr<CxxVector<u8>>>>);

impl HeaderIter {
    pub fn next(&mut self) -> UniquePtr<CxxVector<u8>> {
        self.0.next().unwrap_or_else(|| CxxVector::new())
    }
}

pub struct Request(fastly::Request);

pub fn create_request(method: ffi::Method, url: &CxxString) -> Box<Request> {
    let method: fastly::http::Method = method.into();
    Box::new(Request(fastly::Request::new(method, url.to_string_lossy().as_ref()))) 
}

pub fn get_client_request() -> Box<Request> {
    Box::new(Request(fastly::Request::from_client()))
}

impl Request {
    pub fn get_header_all(&self, name: &CxxString) -> Box<HeaderIter> {
        // Yeah. Sorry. Lifetimes :/
        let iter = self.0.get_header_all(name.as_bytes()).map(|v| {
            let mut vector = CxxVector::new();
            for byte in v.as_bytes() {
                vector.pin_mut().push(*byte);
            }
            vector
        }).collect::<Vec<UniquePtr<CxxVector<u8>>>>();
        Box::new(HeaderIter(Box::new(iter.into_iter())))
    }
}

pub struct Response(fastly::Response);

pub fn create_response() -> Box<Response> {
    Box::new(Response(fastly::Response::new()))
}

pub fn send_response(response: Box<Response>) {
    response.0.send_to_client();
}

impl From<ffi::Method> for fastly::http::Method {
    fn from(val: ffi::Method) -> Self {
        match val {
           ffi::Method::GET => fastly::http::Method::GET,
           ffi::Method::POST => fastly::http::Method::POST,
           ffi::Method::PUT => fastly::http::Method::PUT,
           ffi::Method::DELETE => fastly::http::Method::DELETE,
           ffi::Method::HEAD => fastly::http::Method::HEAD,
           ffi::Method::OPTIONS => fastly::http::Method::OPTIONS,
           ffi::Method::CONNECT => fastly::http::Method::CONNECT,
           ffi::Method::PATCH => fastly::http::Method::PATCH,
           ffi::Method::TRACE => fastly::http::Method::TRACE,
           _ => panic!("Unsupported method.")
        }
    }
}

impl From<fastly::http::Method> for ffi::Method {
    fn from(val: fastly::http::Method) -> Self {
        match val {
           fastly::http::Method::GET => ffi::Method::GET,
           fastly::http::Method::POST => ffi::Method::POST,
           fastly::http::Method::PUT => ffi::Method::PUT,
           fastly::http::Method::DELETE => ffi::Method::DELETE,
           fastly::http::Method::HEAD => ffi::Method::HEAD,
           fastly::http::Method::OPTIONS => ffi::Method::OPTIONS,
           fastly::http::Method::CONNECT => ffi::Method::CONNECT,
           fastly::http::Method::PATCH => ffi::Method::PATCH,
           fastly::http::Method::TRACE => ffi::Method::TRACE,
           _ => panic!("Unsupported method.")
        }
    }
}

#[cxx::bridge(namespace = "fastly::sys")]
mod ffi {
    #[namespace = "fastly"]
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
    
    extern "Rust" {
        type HeaderIter;
        fn next(self: &mut HeaderIter) -> UniquePtr<CxxVector<u8>>;
        type Request;
        fn create_request(method: Method, url: &CxxString) -> Box<Request>;
        fn get_client_request() -> Box<Request>;
        fn get_header_all(self: &Request, name: &CxxString) -> Box<HeaderIter>;
        type Response;
        fn create_response() -> Box<Response>;
        fn send_response(response: Box<Response>);
    }
    
    // unsafe extern "C++" {
    //     include!("include/util.h");
        
    //     fn get_empty_string() -> UniquePtr<CxxString>;
    // }
}