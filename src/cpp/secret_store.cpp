#include "secret_store.h"

namespace fastly::secret_store {

std::string Secret::plaintext() {
  std::string out;
  this->s->plaintext(out);
  return out;
}

SecretStore SecretStore::open(std::string name) {
  return SecretStore(
      fastly::sys::secret_store::m_static_secret_store_secret_store_open(name));
}

std::optional<Secret> SecretStore::get(std::string key) {
  auto ptr{this->ss->get(key)};
  if (ptr == nullptr) {
    return std::nullopt;
  } else {
    return std::optional<Secret>(Secret(std::move(
        rust::Box<fastly::sys::secret_store::Secret>::from_raw(ptr))));
  }
}

bool SecretStore::contains(std::string key) { return this->ss->contains(key); }

} // namespace fastly::secret_store
