#include "fastly/sdk.h"
#include <iostream>
#include <optional>
#include <string>

using namespace std::string_literals;

int main() {
  auto req{fastly::Request::from_client()};
  fastly::Body body;
  auto ua{req.get_header("User-Agent"s)};
  if (ua == std::nullopt) {
    body << "No user agent. Can't detect device."s << std::endl;
  } else {
    body << "Trying to detect device using UA `"s << ua.value() << "`..."s
         << std::endl;
    auto maybe_dev{fastly::device_detection::lookup(ua.value())};
    if (maybe_dev == std::nullopt) {
      body << "Failed to detect device based on User Agent string."s
           << std::endl;
    } else {
      auto dev{std::move(maybe_dev.value())};
      body << "Device name: "s << dev.device_name().value_or("UNKNOWN"s)
           << std::endl
           << "Brand: "s << dev.brand().value_or("UNKNOWN"s) << std::endl
           << "Model: "s << dev.model().value_or("UNKNOWN"s) << std::endl
           << "Hardware Type: "s << dev.hwtype().value_or("UNKNOWN"s)
           << std::endl
           << "eReader?: "s << dev.is_ereader().value_or(false) << std::endl
           << "Game console?: "s << dev.is_gameconsole().value_or(false)
           << std::endl
           << "Media player?: "s << dev.is_mediaplayer().value_or(false)
           << std::endl
           << "Mobile?: "s << dev.is_mobile().value_or(false) << std::endl
           << "SmartTV?: "s << dev.is_smarttv().value_or(false) << std::endl
           << "Tablet?: "s << dev.is_tablet().value_or(false) << std::endl
           << "TV Player?: "s << dev.is_tvplayer().value_or(false) << std::endl
           << "Desktop?: "s << dev.is_desktop().value_or(false) << std::endl
           << "Has Touchsreen?: "s << dev.is_touchscreen().value_or(false)
           << std::endl;
    }
  }
  fastly::Response::from_body(std::move(body)).send_to_client();
}
