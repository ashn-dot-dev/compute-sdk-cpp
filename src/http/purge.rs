use cxx::CxxString;

pub fn f_http_purge_purge_surrogate_key(surrogate_key: &CxxString) {
    fastly::http::purge::purge_surrogate_key(surrogate_key.to_str().expect("invalid utf8"))
        .expect("purge failed");
}

pub fn f_http_purge_soft_purge_surrogate_key(surrogate_key: &CxxString) {
    fastly::http::purge::soft_purge_surrogate_key(surrogate_key.to_str().expect("invalid utf8"))
        .expect("purge failed");
}
