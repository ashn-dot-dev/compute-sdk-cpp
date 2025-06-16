#include "response.h"

namespace fastly {

Response::Response() : res(std::move(fastly::sys::create_response())) {}

void Response::send_to_client() {
  fastly::sys::send_response(std::move(this->res));
}

} // namespace fastly
