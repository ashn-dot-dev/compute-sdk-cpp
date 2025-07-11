#ifndef FASTLY_HTTP_BODY_H
#define FASTLY_HTTP_BODY_H

#include "request.h"
#include "response.h"

#include <array>
#include <iostream>
#include <memory>
#include <streambuf>
#include <string>
#include <string_view>
#include <vector>

#include "../sdk-sys.h"

namespace fastly::http {

class Body : public std::iostream, public std::streambuf {

  friend Response;
  friend Request;

protected:
  int underflow();
  int overflow(int_type val);
  int sync();

public:
  Body()
      : bod(std::move(fastly::sys::http::m_static_http_body_new())),
        std::iostream(this) {
    this->setg(this->gbuf.data(), this->gbuf.data(), this->gbuf.data());
    this->setp(this->pbuf.data(), this->pbuf.data() + this->pbuf.max_size());
  };
  Body(Body &&old)
      : bod((old.sync(), std::move(old.bod))), pbuf(std::move(old.pbuf)),
        std::iostream(this) {
    auto gcurr{old.gptr() - old.eback()};
    auto gend{old.egptr() - old.eback()};
    this->gbuf = std::move(old.gbuf);
    this->setg(this->gbuf.data(), this->gbuf.data() + gcurr,
               this->gbuf.data() + gend);
    this->setp(this->pbuf.data(), this->pbuf.data() + this->pbuf.max_size());
  }
  Body(std::vector<uint8_t> body_vec) : Body() {
    this->fill_from_vec(body_vec);
  };
  Body(std::string_view body_str) : Body() {
    std::vector<uint8_t> vec{body_str.begin(), body_str.end()};
    this->fill_from_vec(vec);
  };
  size_t read(uint8_t *buf, size_t bufsize);
  size_t write(uint8_t *buf, size_t bufsize);
  void append(Body other);
  void append_trailer(std::string_view header_name,
                      std::string_view header_value);

  // TODO(@zkat): this needs a HeaderMap wrapper.
  // HeaderMap get_trailers();

  // TODO(@zkat)
  // Prefix get_prefix(uint32_t prefix_len);
  // PrefixString get_prefix_string(uint32_t prefix_len);
  // class Prefix {
  //     private:
  //     rust::Box<fastly::sys::http::Prefix> pref;
  //     Prefix(rust::Box<fastly::sys::http::Prefix> prefix) :
  //     pref(std::move(prefix)) {};
  // };

  // class PrefixString {
  //     private:
  //     rust::Box<fastly::sys::http::PrefixString> pref;
  //     PrefixString(rust::Box<fastly::sys::http::PrefixString> prefix) :
  //     pref(std::move(prefix)) {};
  // };

  rust::Box<fastly::sys::http::Body> bod;

private:
  std::array<char, 512> pbuf;
  std::array<char, 512> gbuf;
  Body(rust::Box<fastly::sys::http::Body> body)
      : bod(std::move(body)), std::iostream(this) {
    this->setg(this->gbuf.data(), this->gbuf.data(), this->gbuf.data());
    this->setp(this->pbuf.data(), this->pbuf.data() + this->pbuf.max_size());
  };

  void fill_from_vec(std::vector<uint8_t> vec) {
    size_t pos{0};
    size_t written{0};
    while ((written = this->write(vec.data() + pos, vec.size() - pos))) {
      pos += written;
    }
  }
};

class StreamingBody : public std::ostream, public std::streambuf {
  friend Response;
  friend Request;
  friend std::pair<Response, std::vector<request::PendingRequest>>
  request::select(std::vector<request::PendingRequest> &reqs);

protected:
  int overflow(int_type val);
  int sync();

public:
  StreamingBody(StreamingBody &&other)
      : bod((other.sync(), std::move(other.bod))), pbuf(std::move(other.pbuf)),
        std::ostream(this) {
    this->setp(this->pbuf.data(), this->pbuf.data() + this->pbuf.max_size());
  };
  void finish();
  void append(Body other);
  size_t write(uint8_t *buf, size_t bufsize);
  void append_trailer(std::string_view header_name,
                      std::string_view header_value);
  // TODO(@zkat): needs the HeaderMap type.
  // void finish_with_trailers(&HeaderMap trailers);

private:
  StreamingBody(rust::Box<fastly::sys::http::StreamingBody> body)
      : bod(std::move(body)), std::ostream(this) {
    this->setp(this->pbuf.data(), this->pbuf.data() + this->pbuf.max_size());
  };
  rust::Box<fastly::sys::http::StreamingBody> bod;
  std::array<char, 512> pbuf;
};

} // namespace fastly::http

namespace fastly {
using fastly::http::Body;
}

#endif
