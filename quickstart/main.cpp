#include "fastly/sdk.h"
#include <iostream>

int main() {
  auto req{fastly::Request::from_client()};
  auto body{req.into_body()};
  body << " What's up?"; // You can append to it with `<<`.
  fastly::Response::from_body(std::move(body)).send_to_client();
}
