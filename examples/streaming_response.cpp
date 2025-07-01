#include "fastly/sdk.h"
#include <iostream>

using namespace std::string_literals;

int main() {
  auto backend_resp{
      Request::get("https://example.com/").send("example_backend")};

  // Take the body so we can iterate through its lines later
  auto backend_resp_body{backend_resp.take_body()};

  // Start sending the backend response to the client with a now-empty body
  auto client_body{backend_resp.stream_to_client()};

  size_t num_lines{0};
  std::string line;
  while (getline(backend_resp_body, line)) {
    num_lines++;
    client_body << line;
  }
  // Finish the streaming body to close the client connection.
  client_body.finish();

  std::cout << "backend response body contained " << num_lines << " lines"
            << std::endl;
}
