
uint ZydisRegisterGetLargestEnclosing(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  byte local_a;
  byte local_9;
  
  if (0x14a < param_2) {
    return 0;
  }
  if (5 < param_1) {
    return 0;
  }
  uVar1 = *(uint *)(REG_LOOKUP + (ulong)param_2 * 0xc);
  if ((uVar1 == 0) || ((uVar1 == 4 && (param_1 != 0)))) {
    return 0;
  }
  if (0x13 < uVar1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)reg_class < (sizeof(STATIC_MAPPING) / sizeof((STATIC_MAPPING)[0]))",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Register.c",0xb2,
                  "ZydisRegisterGetLargestEnclosing");
  }
  if (5 < param_1) goto LAB_001f296c;
  if (param_1 < 4) {
    if (param_1 == 3) {
LAB_001f2958:
      local_a = 1;
    }
    else {
      if (3 < param_1) {
LAB_001f296c:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Register.c",0xc4,
                      "ZydisRegisterGetLargestEnclosing");
      }
      if (param_1 == 2) goto LAB_001f2964;
      if (2 < param_1) goto LAB_001f296c;
      if (param_1 != 0) {
        if (param_1 != 1) goto LAB_001f296c;
        goto LAB_001f2958;
      }
      local_a = 2;
    }
  }
  else {
LAB_001f2964:
    local_a = 0;
  }
  uVar2 = *(uint *)(STATIC_MAPPING_1 + ((ulong)uVar1 * 3 + (long)(int)(uint)local_a) * 4);
  if ((uVar2 == 0) && (local_9 = REG_LOOKUP[(ulong)param_2 * 0xc + 4], uVar2 = param_2, uVar1 < 10))
  {
    if (uVar1 < 7) {
      if (uVar1 == 1) {
        if (0x23 < local_9) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("reg_id < (sizeof(GPR8_MAPPING) / sizeof((GPR8_MAPPING)[0]))",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Register.c",0xfa,
                        "ZydisRegisterGetLargestEnclosing");
        }
        local_9 = GPR8_MAPPING_0[(int)(uint)local_9];
      }
      else {
        if (uVar1 == 0) {
          return param_2;
        }
        if (2 < uVar1 - 2) {
          return param_2;
        }
      }
      if (local_a == 2) {
        uVar2 = local_9 + 0x65;
      }
      else {
        if (2 < local_a) {
LAB_001f2ad4:
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Register.c",
                        0x109,"ZydisRegisterGetLargestEnclosing");
        }
        if (local_a == 0) {
          uVar2 = local_9 + 0x25;
        }
        else {
          if (local_a != 1) goto LAB_001f2ad4;
          uVar2 = local_9 + 0x45;
        }
      }
    }
    else {
      uVar2 = local_9 + 0xd8;
    }
  }
  return uVar2;
}

