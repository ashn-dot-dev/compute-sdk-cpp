#include "purge.h"

namespace fastly::http::purge {

void purge_surrogate_key(std::string surrogate_key) {
  return fastly::sys::http::purge::f_http_purge_purge_surrogate_key(
      surrogate_key);
}

void soft_purge_surrogate_key(std::string surrogate_key) {
  return fastly::sys::http::purge::f_http_purge_soft_purge_surrogate_key(
      surrogate_key);
}

} // namespace fastly::http::purge
