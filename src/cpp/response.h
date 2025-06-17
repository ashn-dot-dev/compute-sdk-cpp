#ifndef FASTLY_RESPONSE_H
#define FASTLY_RESPONSE_H

#include "sdk-sys.h"
#include <string>

namespace fastly {

class Response {
public:
  Response();
  void send_to_client();

private:
  rust::Box<fastly::sys::Response> res;
};

} // namespace fastly

#endif
