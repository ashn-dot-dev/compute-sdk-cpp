#include "config_store.h"

namespace fastly::config_store {

ConfigStore ConfigStore::open(std::string_view name) {
  return ConfigStore(
      fastly::sys::config_store::m_static_config_store_config_store_open(
          static_cast<std::string>(name)));
}

std::optional<std::string> ConfigStore::get(std::string_view key) {
  std::string out;
  auto some{this->cs->get(static_cast<std::string>(key), out)};
  if (!some) {
    return std::nullopt;
  } else {
    return std::optional<std::string>{std::move(out)};
  }
}

bool ConfigStore::contains(std::string_view key) {
  return this->cs->contains(static_cast<std::string>(key));
}

} // namespace fastly::config_store
