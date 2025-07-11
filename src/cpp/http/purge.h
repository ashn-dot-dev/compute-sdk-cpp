#ifndef FASTLY_HTTP_PURGE_H
#define FASTLY_HTTP_PURGE_H

#include "../sdk-sys.h"
#include <string>
#include <string_view>

namespace fastly::http::purge {

void purge_surrogate_key(std::string_view surrogate_key);

void soft_purge_surrogate_key(std::string_view surrogate_key);

} // namespace fastly::http::purge

#endif
