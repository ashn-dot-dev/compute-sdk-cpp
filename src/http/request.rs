use cxx::{CxxString, CxxVector, UniquePtr};

use crate::http::header::HeaderIter;
use crate::ffi::Method;

pub struct Request(fastly::Request);

pub fn m_static_http_request_new(method: Method, url: &CxxString) -> Box<Request> {
    let method: fastly::http::Method = method.into();
    // TODO(@zkat): not liking this .to_string_lossy()
    Box::new(Request(fastly::Request::new(method, url.to_string_lossy().as_ref()))) 
}

pub fn m_static_http_request_get(url: &CxxString) -> Box<Request> {
    // TODO(@zkat): not liking this .to_string_lossy()
    Box::new(Request(fastly::Request::get(url.to_string_lossy().as_ref())))
}

pub fn m_static_http_request_from_client() -> Box<Request> {
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
    
    // TODO(@zkat): cxx doesn't support function pointers
    // pub fn set_after_send(&mut self, _f: unsafe extern "C" fn(*mut Request)) {
    //     unimplemented!()
    // }
    
    pub fn set_auto_decompress_gzip(&mut self, gzip: bool) {
        self.0.set_auto_decompress_gzip(gzip);
    }
    
    // TODO(@zkat): cxx doesn't support function pointers
    // pub fn set_before_send(&mut self, _f: unsafe extern "C" fn(*mut Request)) -> Box<Request> {
    //     unimplemented!()
    // }
    
    pub fn set_body(&mut self, body: &CxxVector<u8>) {
        self.0.set_body(body.as_slice());
    }
}
