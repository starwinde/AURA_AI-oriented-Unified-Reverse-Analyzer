
bool ZydisCheckVectorMemorySize(long *param_1,long param_2,short *param_3)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  long lVar4;
  ulong uVar5;
  byte local_16;
  ushort local_14;
  ushort local_12;
  
  uVar3 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
  local_16 = (byte)((uVar3 & 0xff) >> 5);
  if ((*(char *)((long)param_1 + 0x34) != '\0') && (local_16 == 2)) {
    local_16 = 1;
  }
  if ((param_3[local_16] != 0) || ((*(byte *)(param_1[1] + 6) & 7) == 3)) {
    if (param_3[local_16] == *(short *)(param_2 + 0x28)) {
      return true;
    }
    if ((*(char *)((long)param_1 + 0x34) == '\0') && (local_16 == 2)) {
      if (*param_3 == param_3[1]) {
        return *(short *)(param_2 + 0x28) == param_3[1];
      }
                    /* WARNING: Subroutine does not return */
      __assert_fail("size_table[0] == size_table[1]",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x696,
                    "ZydisCheckVectorMemorySize");
    }
    return false;
  }
  if (((*(byte *)(param_1[1] + 6) & 7) != 4) && ((*(byte *)(param_1[1] + 6) & 7) != 5)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(match->definition->encoding == ZYDIS_INSTRUCTION_ENCODING_EVEX) || (match->definition->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX)"
                  ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x69b,
                  "ZydisCheckVectorMemorySize");
  }
  uVar1 = *(ushort *)(param_1[1] + 8) >> 8;
  uVar2 = uVar1 & 3;
  if (uVar2 == 3) {
LAB_001ea638:
    local_14 = 0x40;
  }
  else {
    if (3 < uVar2) {
LAB_001ea644:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x6ac,
                    "ZydisCheckVectorMemorySize");
    }
    if (uVar2 == 2) {
      local_14 = 0x20;
    }
    else {
      if (2 < uVar2) goto LAB_001ea644;
      if ((uVar1 & 3) == 0) {
        if ((*(byte *)(param_1[1] + 6) & 7) != 5) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("match->definition->encoding == ZYDIS_INSTRUCTION_ENCODING_MVEX",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x6a6,
                        "ZydisCheckVectorMemorySize");
        }
        goto LAB_001ea638;
      }
      if (uVar2 != 1) goto LAB_001ea644;
      local_14 = 0x10;
    }
  }
  if ((*(byte *)(param_1[1] + 6) & 7) == 4) {
    lVar4 = param_1[2];
    if (5 < (byte)((*(byte *)(lVar4 + 0xe) & 3) << 1 | *(byte *)(lVar4 + 0xd) >> 7)) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("evex_def->element_size < (sizeof(element_sizes) / sizeof((element_sizes)[0]))",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x6b6,
                    "ZydisCheckVectorMemorySize");
    }
    if ((*(int *)(*param_1 + 0x170) == 0) && ((*(byte *)(lVar4 + 0xf) & 0x1e) == 0)) {
      uVar1 = *(ushort *)(lVar4 + 0xc) >> 10 & 0x1f;
      if (uVar1 == 0x11) {
        local_14 = local_14 >> 2;
      }
      else {
        if (0x11 < uVar1) {
LAB_001ea7b8:
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x6cc
                        ,"ZydisCheckVectorMemorySize");
        }
        if (uVar1 == 3) {
          local_14 = local_14 >> 1;
        }
        else {
          if (3 < uVar1) goto LAB_001ea7b8;
          if (uVar1 == 1) {
            local_14 = 0;
          }
          else if (uVar1 != 2) goto LAB_001ea7b8;
        }
      }
    }
    else {
      local_14 = (ushort)*(byte *)((long)&element_sizes_28 +
                                  (long)(int)((*(byte *)(lVar4 + 0xe) & 3) << 1 |
                                             (uint)(*(byte *)(lVar4 + 0xd) >> 7)));
    }
    goto LAB_001eaaa4;
  }
  lVar4 = param_1[2];
  uVar3 = *(uint *)(*param_1 + 0x180);
  if (5 < uVar3) {
LAB_001ea944:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x703,
                  "ZydisCheckVectorMemorySize");
  }
  if (uVar3 < 4) {
    if (3 < uVar3) goto LAB_001ea944;
    if (uVar3 < 2) {
      if (uVar3 != 0) {
        if (uVar3 != 1) goto LAB_001ea944;
        goto LAB_001ea91c;
      }
      uVar3 = (*(ushort *)(lVar4 + 0xc) >> 8 & 0x1f) - 10;
      if (0xf < uVar3) {
LAB_001ea8f8:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x6f4,
                      "ZydisCheckVectorMemorySize");
      }
      uVar5 = 1L << ((ulong)uVar3 & 0x3f);
      if ((uVar5 & 0x5555) == 0) {
        if ((uVar5 & 0xaa88) == 0) {
          if ((uVar5 & 0x22) == 0) goto LAB_001ea8f8;
          local_14 = 0x20;
          local_12 = 4;
        }
        else {
          local_14 = 0x40;
          local_12 = 8;
        }
      }
      else {
        local_14 = 0x40;
        local_12 = 4;
      }
    }
    else {
      local_14 = 0x10;
      local_12 = 1;
    }
  }
  else {
LAB_001ea91c:
    local_14 = 0x20;
    local_12 = 2;
  }
  if (((*(byte *)(lVar4 + 0xe) & 7) != 0) && (*(int *)(*param_1 + 0x17c) != 0)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("!mvex_def->broadcast || !match->request->mvex.broadcast",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x705,
                  "ZydisCheckVectorMemorySize");
  }
  uVar3 = *(byte *)(lVar4 + 0xe) & 7;
  if (4 < uVar3) {
LAB_001eaa08:
                    /* WARNING: Subroutine does not return */
    __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x713,
                  "ZydisCheckVectorMemorySize");
  }
  if (uVar3 < 3) {
    if ((*(byte *)(lVar4 + 0xe) & 7) != 0) {
      if (1 < uVar3 - 1) goto LAB_001eaa08;
      local_14 = local_12;
    }
  }
  else {
    local_14 = local_12 << 2;
  }
  uVar3 = *(uint *)(*param_1 + 0x17c);
  if (uVar3 < 0xc) {
    if (uVar3 < 10) {
      if (uVar3 != 0) {
        if (1 < uVar3 - 3) goto LAB_001eaa78;
        local_14 = local_12;
      }
    }
    else {
      local_14 = local_12 << 2;
    }
LAB_001eaaa4:
    return local_14 == *(ushort *)(param_2 + 0x28);
  }
LAB_001eaa78:
                    /* WARNING: Subroutine does not return */
  __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x722,
                "ZydisCheckVectorMemorySize");
}

