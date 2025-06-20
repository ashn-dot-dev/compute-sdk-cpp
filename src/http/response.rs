use cxx::CxxVector;

pub struct Response(pub(crate) fastly::Response);

pub fn m_static_http_response_new() -> Box<Response> {
    Box::new(Response(fastly::Response::new()))
}

pub fn m_http_response_send_to_client(response: Box<Response>) {
    response.0.send_to_client();
}

pub fn m_static_http_response_from_body(body: &CxxVector<u8>) -> Box<Response> {
    Box::new(Response(fastly::Response::from_body(body.as_slice())))
}

impl Response {
    pub fn set_body(&mut self, body: &CxxVector<u8>) {
        self.0.set_body(body.as_slice());
    }
}
