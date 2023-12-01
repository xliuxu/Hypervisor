#pragma once

#include "hv_kernel_structs_xnu_20.h"
#include "hv_kernel_structs_xnu_21.h"
#include "hv_kernel_structs_xnu_22.h"

typedef union {
  arm_guest_rw_context_20_t v20;
  arm_guest_rw_context_21_t v21;
  arm_guest_rw_context_22_t v22;
} arm_guest_rw_context_t;

typedef union {
  arm_guest_ro_context_20_t v20;
  arm_guest_ro_context_21_t v21;
  arm_guest_ro_context_22_t v22;
  uint64_t ver;
} arm_guest_ro_context_t;

typedef union {
  arm_guest_context_20_t v20;
  arm_guest_context_21_t v21;
  arm_guest_context_22_t v22;
} arm_guest_context_t;

typedef union {
  hv_capabilities_20_t v20;
  hv_capabilities_21_t v21;
  hv_capabilities_22_t v22;
} hv_capabilities_t;

static int _get_xnu_version(void) {
  if (__builtin_available(iOS 16, macOS 13, watchOS 9, tvOS 16, bridgeOS 7, *)) {
    return HV_VERSION_XNU_22;
  } else if (__builtin_available(iOS 15, macOS 12, watchOS 8, tvOS 15, bridgeOS 6, *)) {
    return HV_VERSION_XNU_21;
  } else if (__builtin_available(iOS 14, macOS 11, watchOS 7, tvOS 14, bridgeOS 5, *)) {
    return HV_VERSION_XNU_20;
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
    case HV_VERSION_XNU_20: return HV_XNU_20_MAGIC;
    case HV_VERSION_XNU_21: return HV_XNU_21_MAGIC;
    case HV_VERSION_XNU_22: return HV_XNU_22_MAGIC;
    default: return 0;
  }
}

#define ACCESS(s, f) (*(get_xnu_version() == HV_VERSION_XNU_21 ? &(s)->v21.f : (get_xnu_version() == HV_VERSION_XNU_20 ? &(s)->v20.f : (get_xnu_version() == HV_VERSION_XNU_22 ? &(s)->v22.f : NULL))))
