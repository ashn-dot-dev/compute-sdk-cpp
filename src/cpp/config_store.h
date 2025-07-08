#ifndef FASTLY_CONFIG_STORE_H
#define FASTLY_CONFIG_STORE_H

#include "sdk-sys.h"
#include <optional>
#include <string>

namespace fastly::config_store {

/// A Compute Config Store.
class ConfigStore {
public:
  /// Open a config store, given its name.
  ///
  /// # Examples
  ///
  /// ```no_run
  /// auto merriam{fastly::ConfigStore::open("merriam webster")};
  /// auto oed{fastly::ConfigStore::open("oxford english config store")};
  /// ```
  static ConfigStore open(std::string name);

  /// Lookup a value in this config store.
  ///
  /// If successful, this function returns `std::optional<std::string>>` if an
  /// entry was found, or `std::nullopt` if no entry with the given key was
  /// found.
  ///
  /// # Examples
  ///
  /// ```no_run
  /// auto store{fastly::ConfigStore::open("test config store"s)};
  /// assert(store.get("bread"s).value() ==
  ///        "a usually baked and leavened food"s);
  ///
  /// assert(
  ///     store.get("freedom"s).value() ==
  ///     "the absence of necessity, coercion, or constraint"s,
  /// );
  ///
  /// // Otherwise, `get` will return nullopt.
  /// assert(store.get("zzzzz"s) == std::nullopt);
  /// ```
  std::optional<std::string> get(std::string key);

  /// Return true if the config_store contains an entry with the given key.
  ///
  /// # Examples
  ///
  /// ```no_run
  /// auto store{fastly::ConfigStore::open("test config store"s)};
  /// assert(store.contains("key"s));
  /// ```
  bool contains(std::string key);

private:
  rust::Box<fastly::sys::config_store::ConfigStore> cs;
  ConfigStore(rust::Box<fastly::sys::config_store::ConfigStore> c)
      : cs(std::move(c)) {};
};

} // namespace fastly::config_store

namespace fastly {
using fastly::config_store::ConfigStore;
}

#endif
