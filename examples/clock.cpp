#include "fastly/sdk.h"
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std::string_literals;

int main() {
  fastly::Body body{"It is currently: "};
  // You can use `chrono` directly to get and format datetime/clock data.
  std::time_t now{
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};
  body << std::ctime(&now) << std::endl;
  fastly::Response::from_body(std::move(body)).send_to_client();
}
