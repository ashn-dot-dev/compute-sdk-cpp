#include <iostream>
#include <string>

#include "fastly/sdk.h"

using namespace std::string_literals;

int main() {
  auto req{fastly::Request::from_client()};
  auto iter{req.get_header_all("Host"s)};
  std::string header = iter.next();
  while (header.size()) {
    std::cerr << "Host: " << header << std::endl;
    header = iter.next();
  }
  fastly::Response::from_body("hello, world"s).send_to_client();
}
