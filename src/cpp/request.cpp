#include "request.h"

namespace fastly {

Request::Request(Method method, std::string url)
    : req(std::move(fastly::sys::create_request(method, url))) {}

Request Request::from_client() {
  Request req{fastly::sys::get_client_request()};
  return req;
}

HeaderIter Request::get_header_all(std::string name) {
  return this->req->get_header_all(name);
}

} // namespace fastly
