use std::pin::Pin;

use cxx::CxxString;

pub struct ConfigStore(pub(crate) fastly::ConfigStore);

pub fn m_static_config_store_config_store_open(name: &CxxString) -> Box<ConfigStore> {
    Box::new(ConfigStore(fastly::ConfigStore::open(
        name.to_string_lossy().as_ref(),
    )))
}

impl ConfigStore {
    pub fn get(&self, key: &CxxString, out: Pin<&mut CxxString>) -> bool {
        self.0
            .get(key.to_string_lossy().as_ref())
            .map(|val| out.push_str(val.as_ref()))
            .is_some()
    }

    pub fn contains(&self, key: &CxxString) -> bool {
        self.0.contains(key.to_string_lossy().as_ref())
    }
}
