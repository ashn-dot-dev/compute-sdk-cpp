use std::pin::Pin;

use cxx::CxxString;
use fastly::http::StatusCode;

pub fn f_http_status_code_canonical_reason(code: u16, string: Pin<&mut CxxString>) -> bool {
    let status = StatusCode::from_u16(code).expect("invalid code");
    if let Some(reason) = status.canonical_reason() {
        string.push_str(reason);
        true
    } else {
        false
    }
}
