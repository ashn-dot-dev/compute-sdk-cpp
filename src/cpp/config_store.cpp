#include "config_store.h"

namespace fastly::config_store {

ConfigStore ConfigStore::open(std::string name) {
  return ConfigStore(
      fastly::sys::config_store::m_static_config_store_config_store_open(name));
}

std::optional<std::string> ConfigStore::get(std::string key) {
  std::string out;
  auto some{this->cs->get(key, out)};
  if (!some) {
    return std::nullopt;
  } else {
    return std::optional<std::string>{out};
  }
}

bool ConfigStore::contains(std::string key) { return this->cs->contains(key); }

} // namespace fastly::config_store
