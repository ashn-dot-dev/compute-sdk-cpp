#include <iostream>
#include <string>

#include "fastly/headers.h"
#include "fastly/request.h"
#include "fastly/response.h"
// or just pull everything in with:
// #include "fastly/fastly.h"

using namespace std::string_literals;

int main() {
  fastly::Request req{fastly::Request::from_client()};
  fastly::HeaderIter iter{req.get_header_all("Host"s)};
  std::string header = iter.next();
  while (header.size()) {
    std::cerr << "Host: " << header << std::endl;
    header = iter.next();
  }
  fastly::Response res;
  res.send_to_client();
}
