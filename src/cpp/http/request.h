#ifndef FASTLY_HTTP_REQUEST_H
#define FASTLY_HTTP_REQUEST_H

#include "../sdk-sys.h"
#include "header.h"
#include "method.h"
#include "response.h"
#include <string>
#include <vector>

namespace fastly::http {

class Request {
public:
  Request(Method method, std::string url);
  static Request from_client();
  static Request get(std::string url);
  static Request head(std::string url);
  static Request post(std::string url);
  static Request put(std::string url);
  static Request delete_(std::string url);
  static Request connect(std::string url);
  static Request options(std::string url);
  static Request trace(std::string url);
  static Request patch(std::string url);
  bool is_from_client();
  Request clone_without_body();
  Request clone_with_body();
  Response send(std::string backend);
  HeaderIter get_header_all(std::string name);
  void set_auto_decompress_gzip(bool gzip);
  Request* with_auto_decompress_gzip(bool gzip);
  void set_body(std::vector<uint8_t> body);
  void set_body(std::string body);
  Request* with_body(std::vector<uint8_t> body);
  Request* with_body(std::string body);
  bool has_body();
  std::unique_ptr<std::vector<uint8_t>> into_body_bytes();
  std::string into_body_string();

private:
  Request(rust::Box<fastly::sys::http::Request> r) : req(std::move(r)) {};
  rust::Box<fastly::sys::http::Request> req;
};

} // namespace fastly

namespace fastly {
    using fastly::http::Request;
}

#endif
