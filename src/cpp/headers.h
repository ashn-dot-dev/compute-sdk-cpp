#ifndef FASTLY_HEADERS_H
#define FASTLY_HEADERS_H

#include <memory>
#include <string>
#include <vector>

#include "sdk-sys.h"

namespace fastly {

class HeaderIter {
public:
  HeaderIter(rust::Box<fastly::sys::HeaderIter> i) : iter(std::move(i)) {};
  std::string next();

private:
  rust::Box<fastly::sys::HeaderIter> iter;
};

} // namespace fastly

#endif
