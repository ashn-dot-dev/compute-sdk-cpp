// https://www.fastly.com/documentation/solutions/examples/serve-robots-txt-from-the-edge/

#include "fastly/sdk.h"

using namespace std::string_literals;

int main() {
  auto req{fastly::Request::from_client()};
  if (req.get_method() == fastly::http::Method::GET &&
      req.get_path() == "/robots.txt") {
    fastly::Response::from_body("User-agent: BadBot\nDisallow: /\n"s)
        .send_to_client();
  } else {
    fastly::Response::from_body("The page you requested could not be found"s)
        .with_status(fastly::http::StatusCode::NOT_FOUND)
        .send_to_client();
  }
}

