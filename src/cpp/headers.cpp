#include <memory>
#include <vector>

#include "headers.h"

namespace fastly {

std::string HeaderIter::next() {
    std::unique_ptr<std::vector<uint8_t>> vec = this->iter->next();
    return std::string(vec->begin(), vec->end());
}

}