use std::pin::Pin;

use cxx::CxxString;

pub struct Secret(pub(crate) fastly::secret_store::Secret);

pub fn m_static_secret_store_secret_from_bytes(bytes: &CxxString) -> Box<Secret> {
    Box::new(Secret(
        fastly::secret_store::Secret::from_bytes(bytes.as_bytes().to_owned())
            .expect("secret failed"),
    ))
}

impl Secret {
    pub fn plaintext(&self, out: Pin<&mut CxxString>) {
        out.push_bytes(self.0.plaintext().as_ref());
    }
}

pub struct SecretStore(pub(crate) fastly::SecretStore);

pub fn m_static_secret_store_secret_store_open(name: &CxxString) -> Box<SecretStore> {
    Box::new(SecretStore(
        fastly::SecretStore::open(name.to_string_lossy().as_ref())
            .expect("Opening secret store failed"),
    ))
}

impl SecretStore {
    pub fn get(&self, key: &CxxString) -> *mut Secret {
        self.0
            .get(key.to_string_lossy().as_ref())
            .map(Secret)
            .map(Box::new)
            .map(Box::into_raw)
            .unwrap_or_else(std::ptr::null_mut)
    }

    pub fn contains(&self, key: &CxxString) -> bool {
        self.0.contains(key.to_string_lossy().as_ref()).expect("Failed to look up the secret")
    }
}
