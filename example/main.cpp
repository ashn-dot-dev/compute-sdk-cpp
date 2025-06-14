#include <string>

#include "fastly.h"

using namespace std::string_literals;

int main() {
    auto req{fastly::get_client_request()};
    auto header{req->get_header_all("Host"s)};
    auto res{fastly::create_response()};
    fastly::send_response(std::move(res));
}
