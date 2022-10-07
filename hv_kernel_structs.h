#pragma once

#include "hv_kernel_structs_xnu_20_4.h"
#include "hv_kernel_structs_xnu_20_6.h"
#include "hv_kernel_structs_xnu_21_6.h"

typedef union {
  arm_guest_rw_context_20_4_t v204;
  arm_guest_rw_context_20_6_t v206;
  arm_guest_rw_context_21_t v216;
} arm_guest_rw_context_t;

typedef union {
  arm_guest_ro_context_20_4_t v204;
  arm_guest_ro_context_20_6_t v206;
  arm_guest_ro_context_21_t v216;
  uint64_t ver;
} arm_guest_ro_context_t;

typedef union {
  arm_guest_context_20_4_t v204;
  arm_guest_context_20_6_t v206;
  arm_guest_context_21_t v216;
} arm_guest_context_t;

typedef union {
  hv_capabilities_20_t v204;
  hv_capabilities_20_t v206;
  hv_capabilities_21_t v216;
} hv_capabilities_t;

static int _get_xnu_version(void) {
  if (__builtin_available(iOS 16, macOS 13, watchOS 9, tvOS 16, bridgeOS 7, *)) {
    return 0; // not yet supported
  } else if (__builtin_available(iOS 15, macOS 12, watchOS 8, tvOS 15, bridgeOS 6, *)) {
    return HV_VERSION_XNU_21_6;
  } else if (__builtin_available(iOS 14.7, macOS 11.5, watchOS 7.6, tvOS 14.7, bridgeOS 5.5, *)) {
    return HV_VERSION_XNU_20_6;
  } else if (__builtin_available(iOS 14, macOS 11, watchOS 7, tvOS 14, bridgeOS 5, *)) {
    return HV_VERSION_XNU_20_4;
  } else {
    return 0; // not yet supported
  }
}

static inline int get_xnu_version(void) {
  static int version = -1;
  if (__builtin_expect(version < 0, 0)) {
    version = _get_xnu_version();
  }
  return version;
}

static inline uint64_t get_expected_magic(void) {
  switch (get_xnu_version()) {
    case HV_VERSION_XNU_20_4: return HV_XNU_20_4_MAGIC;
    case HV_VERSION_XNU_20_6: return HV_XNU_20_6_MAGIC;
    case HV_VERSION_XNU_21_6: return HV_XNU_21_6_MAGIC;
    default: return 0;
  }
}

#define ACCESS(s, f) (*(get_xnu_version() == HV_VERSION_XNU_21_6 ? &(s)->v216.f : (get_xnu_version() == HV_VERSION_XNU_20_6 ? &(s)->v206.f : (get_xnu_version() == HV_VERSION_XNU_20_4 ? &(s)->v204.f : NULL)))) 
