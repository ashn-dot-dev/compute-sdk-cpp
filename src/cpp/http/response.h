#ifndef FASTLY_HTTP_RESPONSE_H
#define FASTLY_HTTP_RESPONSE_H

#include "../sdk-sys.h"
#include <string>
#include <vector>

namespace fastly::http {

class Response {
public:
  Response();
  Response(rust::Box<fastly::sys::http::Response> response) : res(std::move(response)) {};
  static Response from_body(std::vector<uint8_t> body);
  static Response from_body(std::string body);
  void set_body(std::vector<uint8_t> body);
  Response* with_body(std::vector<uint8_t> body);
  void set_body(std::string body);
  Response* with_body(std::string body);
  void send_to_client();

private:
  rust::Box<fastly::sys::http::Response> res;
};

} // namespace fastly

namespace fastly {
    using fastly::http::Response;
}

#endif
