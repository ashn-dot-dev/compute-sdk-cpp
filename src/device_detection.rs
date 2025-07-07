use std::pin::Pin;

use cxx::CxxString;

pub struct Device(pub(crate) fastly::device_detection::Device);

// Just used to force generation of symbols, since we're otherwise doing raw pointers.
pub fn f_device_detection_noop(dev: Box<Device>) -> Box<Device> {
    dev
}

pub fn f_device_detection_lookup(user_agent: &CxxString) -> *mut Device {
    if let Some(dev) = fastly::device_detection::lookup(user_agent.to_string_lossy().as_ref()) {
        Box::into_raw(Box::new(Device(dev)))
    } else {
        std::ptr::null_mut()
    }
}

impl Device {
    pub fn device_name(&self, out: Pin<&mut CxxString>) -> bool {
        if let Some(b) = self.0.device_name() {
            out.push_str(b);
            true
        } else {
            false
        }
    }
    pub fn brand(&self, out: Pin<&mut CxxString>) -> bool {
        if let Some(b) = self.0.brand() {
            out.push_str(b);
            true
        } else {
            false
        }
    }
    pub fn model(&self, out: Pin<&mut CxxString>) -> bool {
        if let Some(b) = self.0.model() {
            out.push_str(b);
            true
        } else {
            false
        }
    }
    pub fn hwtype(&self, out: Pin<&mut CxxString>) -> bool {
        if let Some(b) = self.0.model() {
            out.push_str(b);
            true
        } else {
            false
        }
    }
    pub fn is_ereader(&self) -> *const bool {
        if let Some(b) = self.0.is_ereader() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_gameconsole(&self) -> *const bool {
        if let Some(b) = self.0.is_gameconsole() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_mediaplayer(&self) -> *const bool {
        if let Some(b) = self.0.is_mediaplayer() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_mobile(&self) -> *const bool {
        if let Some(b) = self.0.is_mobile() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_smarttv(&self) -> *const bool {
        if let Some(b) = self.0.is_smarttv() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_tablet(&self) -> *const bool {
        if let Some(b) = self.0.is_tablet() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_tvplayer(&self) -> *const bool {
        if let Some(b) = self.0.is_tvplayer() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_desktop(&self) -> *const bool {
        if let Some(b) = self.0.is_desktop() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
    pub fn is_touchscreen(&self) -> *const bool {
        if let Some(b) = self.0.is_touchscreen() {
            Box::into_raw(Box::new(b))
        } else {
            std::ptr::null()
        }
    }
}
