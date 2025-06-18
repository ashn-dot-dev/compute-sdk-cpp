#include "response.h"

namespace fastly::http {

Response::Response() : res(std::move(fastly::sys::http::m_static_http_response_new())) {}

Response Response::from_body(std::string body) {
    std::vector<uint8_t> bod(body.begin(), body.end());
    return Response::from_body(std::move(bod));
}

Response Response::from_body(std::vector<uint8_t> body) {
    Response res(std::move(fastly::sys::http::m_static_http_response_from_body(body)));
    return res;
}

void Response::set_body(std::string body) {
    std::vector<uint8_t> vec(body.begin(), body.end());
    this->set_body(std::move(vec));
}

Response* Response::with_body(std::string body) {
    this->set_body(std::move(body));
    return this;
}

void Response::set_body(std::vector<uint8_t> body) {
    this->res->set_body(std::move(body));
}

Response* Response::with_body(std::vector<uint8_t> body) {
    this->set_body(std::move(body));
    return this;
}

void Response::send_to_client() {
  fastly::sys::http::m_http_response_send_to_client(std::move(this->res));
}

} // namespace fastly
