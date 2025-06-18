#ifndef FASTLY_REQUEST_H
#define FASTLY_REQUEST_H

#include "../sdk-sys.h"
#include "header.h"
#include <string>

namespace fastly::http {

class Request {
public:
  Request(Method method, std::string url);
  static Request from_client();
  // static Request get(std::string url);
  HeaderIter get_header_all(std::string name);

private:
  Request(rust::Box<fastly::sys::http::Request> r) : req(std::move(r)) {};
  rust::Box<fastly::sys::http::Request> req;
};

} // namespace fastly

namespace fastly {
    using fastly::http::Request;
}

#endif
