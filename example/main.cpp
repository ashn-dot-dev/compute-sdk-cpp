#include <string>

#include "fastly.h"

using namespace std::string_literals;

int main() {
    auto req{fastly::create_request(fastly::Method::GET, "https://fastly.com"s)};
    auto header{req->get_header_all("Host"s)};
}
