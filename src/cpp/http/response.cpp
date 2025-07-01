#include "response.h"

namespace fastly::http {

Response::Response()
    : res(std::move(fastly::sys::http::m_static_http_response_new())) {}

bool Response::is_from_backend() { return this->res->is_from_backend(); }

Response Response::clone_without_body() {
  Response res{this->res->clone_without_body()};
  return res;
}

Response Response::clone_with_body() {
  Response res{this->res->clone_with_body()};
  return res;
}

Response Response::from_body(Body body) {
  Response res(std::move(fastly::sys::http::m_static_http_response_from_body(
      std::move(body.bod))));
  return res;
}

Response Response::from_status(StatusCode status) {
  Response res(std::move(
      fastly::sys::http::m_static_http_response_from_status(status.as_code())));
  return res;
}

Response Response::with_body(Body body) {
  this->set_body(std::move(body));
  return std::move(*this);
}

void Response::set_body(Body body) {
  body << std::flush;
  this->res->set_body(std::move(body.bod));
}

Body Response::take_body() {
  Body body{this->res->take_body()};
  return body;
}

void Response::append_body(Body other) {
    this->res->append_body(std::move(other.bod));
}


std::vector<uint8_t> Response::into_body_bytes() {
  auto str{this->into_body_string()};
  return std::vector<uint8_t>(str.begin(), str.end());
}

std::string Response::into_body_string() {
  Body body{this->into_body()};
  return std::string(std::istreambuf_iterator<char>(body),
                     std::istreambuf_iterator<char>());
}

Body Response::into_body() {
  return Body(
      fastly::sys::http::m_http_response_into_body(std::move(this->res)));
}

void Response::set_body_text_plain(std::string body) {
  return this->res->set_body_text_plain(body);
}

Response Response::with_body_text_html(std::string body) {
  this->set_body_text_html(body);
  return std::move(*this);
}

void Response::set_body_text_html(std::string body) {
  return this->res->set_body_text_html(body);
}

Response Response::with_body_text_plain(std::string body) {
  this->set_body_text_plain(body);
  return std::move(*this);
}

std::string Response::take_body_string() {
  Body bod{this->take_body()};
  return std::string(std::istreambuf_iterator<char>(bod),
                     std::istreambuf_iterator<char>());
}

Response Response::with_body_octet_stream(std::vector<uint8_t> body) {
  this->set_body_octet_stream(body);
  return std::move(*this);
}

void Response::set_body_octet_stream(std::vector<uint8_t> body) {
  this->res->set_body_octet_stream(body);
}

std::vector<uint8_t> Response::take_body_bytes() {
  auto body_str{this->take_body_string()};
  return std::vector<uint8_t>(body_str.begin(), body_str.end());
}

// ChunksIter Response::read_body_chunks(size_t chunk_size);

std::optional<std::string> Response::get_content_type() {
  auto ptr{this->res->get_content_type()};
  if (ptr == nullptr) {
    return std::nullopt;
  } else {
    std::string str(ptr->begin(), ptr->end());
    return std::optional<std::string>{str};
  }
}

Response Response::with_content_type(std::string mime) {
  this->set_content_type(mime);
  return std::move(*this);
}

void Response::set_content_type(std::string mime) {
  this->res->set_content_type(mime);
}

std::optional<size_t> Response::get_content_length() {
  auto ptr{this->res->get_content_length()};
  if (ptr == nullptr) {
    return std::nullopt;
  } else {
    return std::optional<size_t>(*ptr);
  }
}

bool Response::contains_header(std::string name) {
  return this->res->contains_header(name);
}

Response Response::with_header(std::string name, std::string value) {
  this->append_header(name, value);
  return std::move(*this);
}

Response Response::with_set_header(std::string name, std::string value) {
  this->set_header(name, value);
  return std::move(*this);
}

// TODO(@zkat): do a proper HeaderValue situation here?
std::optional<std::string> Response::get_header(std::string name) {
  auto ptr{this->res->get_header(name)};
  if (ptr == nullptr) {
    return std::nullopt;
  } else {
    std::string str{ptr->begin(), ptr->end()};
    return {str};
  }
}

HeaderValuesIter Response::get_header_all(std::string name) {
  return this->res->get_header_all(name);
}

// TODO(@zkat): sigh. IDK
// ??? get_headers();
// HeaderNamesIter get_header_names();

void Response::set_header(std::string name, std::string value) {
  this->res->set_header(name, value);
}

void Response::append_header(std::string name, std::string value) {
  this->res->append_header(name, value);
}

std::optional<std::string> Response::remove_header(std::string name) {
  auto ptr{this->res->remove_header(name)};
  if (ptr == nullptr) {
    return std::nullopt;
  } else {
    std::string str{ptr->begin(), ptr->end()};
    return {str};
  }
}

void Response::set_status(StatusCode status) {
  this->res->set_status(status.as_code());
}

Response Response::with_status(StatusCode status) {
  this->set_status(status);
  return std::move(*this);
}

void Response::send_to_client() {
  fastly::sys::http::m_http_response_send_to_client(std::move(this->res));
}

} // namespace fastly::http
