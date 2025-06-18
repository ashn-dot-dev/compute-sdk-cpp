#include "method.h"
#include "request.h"

namespace fastly::http {

Request::Request(Method method, std::string url)
    : req(std::move(fastly::sys::http::m_static_http_request_new(method, url))) {}

Request Request::from_client() {
  Request req{fastly::sys::http::m_static_http_request_from_client()};
  return req;
}

// Request Request::get(std::string url) {
//     Request req{fastly::sys::request_get(url)};
//     return req;
// }

HeaderIter Request::get_header_all(std::string name) {
  return this->req->get_header_all(name);
}

} // namespace fastly
