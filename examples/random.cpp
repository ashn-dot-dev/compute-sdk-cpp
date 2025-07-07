#include "fastly/sdk.h"
#include <iostream>
#include <random>

using namespace std::string_literals;

// You can use the standard library's RNG features directly in wasm.
int random_get() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, 42);
  return dist(rng);
}

int main() {
  fastly::Body body{"Have a random number: "};
  body << random_get() << std::endl;
  fastly::Response::from_body(std::move(body)).send_to_client();
}
