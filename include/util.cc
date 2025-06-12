#include <string>
#include <memory>

std::unique_ptr<std::string> get_empty_string() {
    return std::make_unique<std::string>(std::string(""));
}