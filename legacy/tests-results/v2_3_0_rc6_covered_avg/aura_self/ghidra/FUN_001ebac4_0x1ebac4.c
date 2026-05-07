
undefined8 FUN_001ebac4(long param_1,uint param_2,int param_3)

{
  ushort uVar1;
  byte bVar2;
  undefined8 uVar3;
  byte local_7;
  byte local_6;
  int local_4;
  
  if (param_3 == 0) {
    uVar3 = 1;
  }
  else {
    if (param_2 == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("vector_length != ZYDIS_VECTOR_LENGTH_INVALID",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x919,
                    "ZydisIsBroadcastModeCompatible");
    }
    if (param_2 == 3) {
      local_7 = 0x40;
    }
    else {
      if (3 < param_2) {
LAB_001ebb74:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x926,
                      "ZydisIsBroadcastModeCompatible");
      }
      if (param_2 == 1) {
        local_7 = 0x10;
      }
      else {
        if (param_2 != 2) goto LAB_001ebb74;
        local_7 = 0x20;
      }
    }
    uVar1 = *(ushort *)(param_1 + 0xc) >> 10 & 0x1f;
    if (uVar1 == 0x11) {
      local_7 = local_7 >> 2;
    }
    else {
      if (0x11 < uVar1) {
LAB_001ebbe4:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x933,
                      "ZydisIsBroadcastModeCompatible");
      }
      if (uVar1 != 2) {
        if (uVar1 != 3) goto LAB_001ebbe4;
        local_7 = local_7 >> 1;
      }
    }
    bVar2 = (*(byte *)(param_1 + 0xe) & 3) << 1 | *(byte *)(param_1 + 0xd) >> 7;
    if (bVar2 == 4) {
      local_6 = 8;
    }
    else {
      if (4 < bVar2) {
LAB_001ebc74:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x943,
                      "ZydisIsBroadcastModeCompatible");
      }
      if (bVar2 == 2) {
        local_6 = 2;
      }
      else {
        if (bVar2 != 3) goto LAB_001ebc74;
        local_6 = 4;
      }
    }
    bVar2 = 0;
    if (local_6 != 0) {
      bVar2 = local_7 / local_6;
    }
    if (bVar2 == 0x20) {
      local_4 = 5;
    }
    else {
      if (0x20 < bVar2) {
LAB_001ebd28:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x95a,
                      "ZydisIsBroadcastModeCompatible");
      }
      if (bVar2 == 0x10) {
        local_4 = 4;
      }
      else {
        if (0x10 < bVar2) goto LAB_001ebd28;
        if (bVar2 == 8) {
          local_4 = 3;
        }
        else {
          if (8 < bVar2) goto LAB_001ebd28;
          if (bVar2 == 2) {
            local_4 = 1;
          }
          else {
            if (bVar2 != 4) goto LAB_001ebd28;
            local_4 = 2;
          }
        }
      }
    }
    if (param_3 == local_4) {
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}

