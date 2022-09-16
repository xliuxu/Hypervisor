#pragma once
#include <Hypervisor/Hypervisor.h>

// Headers extracted from
// Kernel_Debug_Kit_11.6.5_build_20G527.dmg

// type lookup hv_vcpu_t
// type lookup arm_guest_context_t

#import "hv_kernel_structs_xnu_20_4.h"

typedef struct {
  uint64_t hcr_el2;
  uint64_t hacr_el2;
  uint64_t cptr_el2;
  uint64_t mdcr_el2;
  uint64_t vmpidr_el2;
  uint64_t vpidr_el2;
  uint64_t virtual_timer_offset;
  uint64_t ich_hcr_el2;
  uint64_t hfgrtr_el2;
  uint64_t hfgwtr_el2;
  uint64_t hfgitr_el2;
  uint64_t hdfgrtr_el2;
  uint64_t hdfgwtr_el2;
  uint64_t timer;
  uint64_t vmkeyhi_el2;
  uint64_t vmkeylo_el2;
  uint64_t apsts_el1;
  uint64_t host_debug;
} arm_guest_controls_20_6_t;

typedef union {
  struct {
    union {
      // arm_context_t guest_context;
      struct {
        uint64_t res1[1];
        struct {
          uint64_t x[29];
          uint64_t fp;
          uint64_t lr;
          uint64_t sp;
          uint64_t pc;
          uint32_t cpsr;
          uint32_t pad;
        } regs;
        uint64_t res2[4];
        struct {
          __uint128_t q[32];
          uint32_t fpsr;
          uint32_t fpcr;
        } neon;
      };
    };
    arm_guest_shared_sysregs_20_t shared_sysregs;
    arm_guest_banked_sysregs_20_t banked_sysregs;
    arm_guest_dbgregs_20_t dbgregs;
    volatile arm_guest_controls_20_6_t controls;
    volatile uint64_t state_dirty;
    uint64_t guest_tick_count;
    arm_guest_extregs_20_t extregs;
    arm_vncr_context_20_t vncr;
    apple_vncr_context_20_t avncr;
  };
  uint8_t page[16384];
} arm_guest_rw_context_20_6_t;

typedef union {
  struct {
    uint64_t ver;
    arm_guest_vmexit_20_t exit;
    arm_guest_controls_20_6_t controls;
    uint64_t state_valid;
    uint64_t state_dirty;
  };
  uint8_t page[16384];
} arm_guest_ro_context_20_6_t;

typedef struct {
  arm_guest_rw_context_20_6_t rw;
  arm_guest_ro_context_20_6_t ro;
  arm_host_context_20_t priv;
} arm_guest_context_20_6_t;

#define HV_XNU_20_6_MAGIC (HV_XNU_20_4_MAGIC)
#define HV_VERSION_XNU_20_6 (206)
