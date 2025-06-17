#ifndef FASTLY_REQUEST_H
#define FASTLY_REQUEST_H

#include "sdk-sys.h"
#include "headers.h"
#include <string>

namespace fastly {

class Request {
public:
  Request(Method method, std::string url);
  static Request from_client();
  HeaderIter get_header_all(std::string name);

private:
  Request(rust::Box<fastly::sys::Request> r) : req(std::move(r)) {};
  rust::Box<fastly::sys::Request> req;
};

} // namespace fastly

#endif
