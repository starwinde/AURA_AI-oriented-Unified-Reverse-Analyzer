
/* WARNING: Removing unreachable block (ram,0x001e8144) */

undefined1 ZydisGetCompDispScaleMvex(long *param_1)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  long lVar5;
  ulong uVar6;
  byte local_a;
  
  lVar5 = param_1[2];
  local_a = -(char)((short)*(undefined2 *)(lVar5 + 0xc) >> 0xf);
  if ((local_a != 0) && ((*(byte *)(lVar5 + 0xe) & 7) != 0)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("!index || !mvex_def->broadcast",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x4b1,
                  "ZydisGetCompDispScaleMvex");
  }
  if ((local_a == 0) && ((*(byte *)(lVar5 + 0xe) & 7) != 0)) {
    uVar1 = *(byte *)(lVar5 + 0xe) & 7;
    if (uVar1 < 3) {
      if ((*(byte *)(lVar5 + 0xe) & 7) == 0) {
LAB_001e8064:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x4bf,
                      "ZydisGetCompDispScaleMvex");
      }
      local_a = 1;
    }
    else {
      if (1 < uVar1 - 3) goto LAB_001e8064;
      local_a = 2;
    }
  }
  bVar2 = ZydisEncodeMvexBroadcastMode(*(undefined4 *)(*param_1 + 0x17c));
  bVar3 = ZydisEncodeMvexConversionMode(*(undefined4 *)(*param_1 + 0x180));
  bVar2 = bVar2 | bVar3;
  uVar1 = *(ushort *)(lVar5 + 0xc) >> 8 & 0x1f;
  if (uVar1 == 0x19) {
LAB_001e836c:
    if (1 < local_a) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("index < 2","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                    0x50b,"ZydisGetCompDispScaleMvex");
    }
    if (local_a == 0) {
      uVar4 = 6;
    }
    else {
      uVar4 = 3;
    }
  }
  else {
    if (0x19 < uVar1) goto LAB_001e83b4;
    if (uVar1 != 0x18) {
      if (0x18 < uVar1) goto LAB_001e83b4;
      if (uVar1 == 0x17) goto LAB_001e836c;
      if (0x17 < uVar1) {
LAB_001e83b4:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x50e,
                      "ZydisGetCompDispScaleMvex");
      }
      if (uVar1 != 0x16) {
        if (uVar1 < 0x17) {
          if (uVar1 == 0x15) {
LAB_001e8288:
            if (bVar2 < 3) {
              return lookup_34[(long)(int)(uint)bVar2 + (long)(int)(uint)local_a * 3];
            }
                    /* WARNING: Subroutine does not return */
            __assert_fail("sss < (sizeof(lookup[index]) / sizeof((lookup[index])[0]))",
                          "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x4fa,
                          "ZydisGetCompDispScaleMvex");
          }
          if ((uVar1 < 0x16) && (uVar1 < 0x15)) {
            if (uVar1 < 10) {
              if (uVar1 < 10) {
                if ((7 < uVar1) || (uVar1 < 4)) {
                  return 0;
                }
                if (uVar1 - 4 < 4) {
                  return 6;
                }
              }
            }
            else {
              uVar6 = 1L << ((ulong)(uVar1 - 10) & 0x3f);
              if ((uVar6 & 0x470) != 0) {
                if (bVar2 < 8) {
                  return lookup_35[(long)(int)(uint)bVar2 + (long)(int)(uint)local_a * 8];
                }
                    /* WARNING: Subroutine does not return */
                __assert_fail("sss < (sizeof(lookup[index]) / sizeof((lookup[index])[0]))",
                              "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                              0x4ec,"ZydisGetCompDispScaleMvex");
              }
              if ((uVar6 & 0x107) != 0) {
                if (bVar2 < 8) {
                  return lookup_36[(long)(int)(uint)bVar2 + (long)(int)(uint)local_a * 8];
                }
                    /* WARNING: Subroutine does not return */
                __assert_fail("sss < (sizeof(lookup[index]) / sizeof((lookup[index])[0]))",
                              "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                              0x4de,"ZydisGetCompDispScaleMvex");
              }
              if ((uVar6 & 0x288) != 0) goto LAB_001e8288;
            }
          }
        }
        goto LAB_001e83b4;
      }
    }
    if (1 < local_a) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("index < 2","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                    0x505,"ZydisGetCompDispScaleMvex");
    }
    if (7 < bVar2) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("sss < (sizeof(lookup[index]) / sizeof((lookup[index])[0]))",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x506,
                    "ZydisGetCompDispScaleMvex");
    }
    uVar4 = lookup_33[(long)(int)(uint)bVar2 + (long)(int)(uint)local_a * 8];
  }
  return uVar4;
}

