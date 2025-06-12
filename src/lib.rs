pub struct Request(fastly::Request);

pub struct HeaderIter(Box<dyn Iterator<Item = Vec<u8>>>);

impl HeaderIter {
    pub fn next(&mut self) -> Vec<u8> {
        self.0.next().unwrap_or_else(|| Vec::new())
    }
}

impl Request {
    pub fn get_header_all(&self, name: &str) -> Box<HeaderIter> {
        // Yeah. Sorry. Lifetimes :/
        let iter = self.0.get_header_all(name).map(|v| v.as_bytes().to_vec()).collect::<Vec<Vec<u8>>>();
        Box::new(HeaderIter(Box::new(iter.into_iter())))
    }
}

#[cxx::bridge]
mod ffi {
    #[namespace = "fastly"]
    extern "Rust" {
        type HeaderIter;
        fn next(self: &mut HeaderIter) -> Vec<u8>;
        type Request;
        fn get_header_all(self: &Request, name: &str) -> Box<HeaderIter>;
    }
    
    // unsafe extern "C++" {
    //     include!("include/util.h");
        
    //     fn get_empty_string() -> UniquePtr<CxxString>;
    // }
}