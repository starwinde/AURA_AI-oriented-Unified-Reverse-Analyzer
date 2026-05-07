
/* WARNING: Removing unreachable block (ram,0x001f01a0) */

undefined8 ZydisBuildInstruction(long *param_1,ulong *param_2)

{
  uint *puVar1;
  uint uVar2;
  ushort uVar3;
  byte bVar4;
  char cVar5;
  byte *pbVar6;
  byte local_22;
  
  memset(param_2,0,0x40);
  *param_2 = param_1[4];
  *(uint *)(param_2 + 1) = *(byte *)(param_1[1] + 6) & 7;
  *(uint *)((long)param_2 + 0xc) = *(byte *)(param_1[1] + 6) >> 3 & 0xf;
  *(undefined1 *)(param_2 + 2) = *(undefined1 *)(param_1[1] + 4);
  *(byte *)((long)param_2 + 0x1d) = *(byte *)(param_1[1] + 8) >> 2 & 1;
  *(byte *)((long)param_2 + 0x15) = *(byte *)(param_1[1] + 5) >> 6;
  *(byte *)((long)param_2 + 0x16) = *(byte *)(param_1[1] + 5) >> 3 & 7;
  *(byte *)((long)param_2 + 0x17) = *(byte *)(param_1[1] + 5) & 7;
  if (*(char *)(param_1[1] + 5) != '\0') {
    *param_2 = *param_2 | 1;
  }
  if ((*(byte *)(param_1[1] + 8) & 0x18) == 0x10) {
    *param_2 = *param_2 | 0x400000000000;
  }
  ZydisGetCcInfo(*(undefined4 *)(*param_1 + 8),param_2 + 7);
  if ((int)param_2[7] != 0) {
    *(undefined1 *)((long)param_2 + 0x11) = *(undefined1 *)(*param_1 + 0x17b);
  }
  uVar3 = *(ushort *)(param_1[1] + 8) >> 8 & 3;
  if (uVar3 == 3) {
    *(undefined1 *)((long)param_2 + 0x14) = 2;
  }
  else {
    if (3 < uVar3) {
LAB_001f01dc:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x104e,
                    "ZydisBuildInstruction");
    }
    if (uVar3 < 2) {
      *(undefined1 *)((long)param_2 + 0x14) = 0;
    }
    else {
      if (uVar3 != 2) goto LAB_001f01dc;
      *(undefined1 *)((long)param_2 + 0x14) = 1;
    }
  }
  if ((*(byte *)(param_1[1] + 6) & 7) == 4) {
    if (((uint)((ulong)*(undefined8 *)(param_1[2] + 8) >> 0x37) & 3) != 1) {
      *(undefined1 *)((long)param_2 + 0x1f) = *(undefined1 *)(*param_1 + 0x179);
    }
    if ((*(char *)(*param_1 + 0x178) != '\0') || (*(int *)(*param_1 + 0x170) != 0)) {
      *param_2 = *param_2 | 0x200000000000;
    }
    if (*(int *)(*param_1 + 0x174) != 0) {
      *param_2 = *param_2 | 0x200000000000;
      uVar2 = *(uint *)(*param_1 + 0x174);
      if (uVar2 == 4) {
        *(undefined1 *)((long)param_2 + 0x14) = 3;
      }
      else {
        if (4 < uVar2) {
LAB_001f0330:
                    /* WARNING: Subroutine does not return */
          __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                        0x1070,"ZydisBuildInstruction");
        }
        if (uVar2 == 3) {
          *(undefined1 *)((long)param_2 + 0x14) = 2;
        }
        else {
          if (3 < uVar2) goto LAB_001f0330;
          if (uVar2 == 1) {
            *(undefined1 *)((long)param_2 + 0x14) = 0;
          }
          else {
            if (uVar2 != 2) goto LAB_001f0330;
            *(undefined1 *)((long)param_2 + 0x14) = 1;
          }
        }
      }
    }
    *(byte *)((long)param_2 + 0x1e) = *(byte *)(param_1[1] + 8) >> 6 & 1;
    if ((*(byte *)(param_1[1] + 8) & 0x20) != 0) {
      *param_2 = *param_2 | 0x200000000000;
    }
    if (((*(byte *)(param_1[1] + 8) & 0x80) != 0) && ((char)param_1[5] == '\x10')) {
      *param_2 = *param_2 | 0x80000000000;
    }
  }
  else if ((*(byte *)(param_1[1] + 6) & 7) == 5) {
    bVar4 = ZydisEncodeMvexBroadcastMode(*(undefined4 *)(*param_1 + 0x17c));
    *(byte *)((long)param_2 + 0x12) = bVar4 | *(byte *)((long)param_2 + 0x12);
    bVar4 = ZydisEncodeMvexConversionMode(*(undefined4 *)(*param_1 + 0x180));
    *(byte *)((long)param_2 + 0x12) = bVar4 | *(byte *)((long)param_2 + 0x12);
    if (*(int *)(*param_1 + 0x184) != 0) {
      if (3 < *(int *)(*param_1 + 0x184) - 1U) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x108d,
                      "ZydisBuildInstruction");
      }
      *(byte *)((long)param_2 + 0x12) =
           *(byte *)((long)param_2 + 0x12) | (char)*(undefined4 *)(*param_1 + 0x184) - 1U;
    }
    if (*(int *)(*param_1 + 0x188) != 0) {
      if (7 < *(int *)(*param_1 + 0x188) - 1U) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x109f,
                      "ZydisBuildInstruction");
      }
      *(byte *)((long)param_2 + 0x12) =
           *(byte *)((long)param_2 + 0x12) | (char)*(undefined4 *)(*param_1 + 0x188) - 1U;
    }
    if (((*(char *)(*param_1 + 0x18c) != '\0') || (*(char *)(*param_1 + 0x18d) != '\0')) ||
       (*(int *)(*param_1 + 0x184) != 0)) {
      *(undefined1 *)(param_2 + 4) = 1;
    }
    if (*(char *)(*param_1 + 0x18c) != '\0') {
      *(byte *)((long)param_2 + 0x12) = *(byte *)((long)param_2 + 0x12) | 4;
    }
    uVar2 = *(uint *)(*param_1 + 8);
    if (uVar2 < 0x52c) {
      if (0x529 < uVar2) {
        *(undefined1 *)(param_2 + 4) = 0;
      }
    }
    else if (uVar2 - 0x52c < 2) {
      *(undefined1 *)(param_2 + 4) = 1;
    }
  }
  bVar4 = *(byte *)(param_1[1] + 8) & 3;
  if (bVar4 == 3) {
    *param_2 = *param_2 | 0x10000000;
  }
  else {
    if (3 < bVar4) {
LAB_001f0698:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x10ce,
                    "ZydisBuildInstruction");
    }
    if (bVar4 == 2) {
      *param_2 = *param_2 | 0x40000000;
    }
    else {
      if (2 < bVar4) goto LAB_001f0698;
      if ((*(byte *)(param_1[1] + 8) & 3) != 0) {
        if (bVar4 != 1) goto LAB_001f0698;
        *param_2 = *param_2 | 0x80000000000;
      }
    }
  }
  cVar5 = ZydisGetMachineModeWidth(*(undefined4 *)*param_1);
  if (cVar5 != *(char *)((long)param_1 + 0x29)) {
    *param_2 = *param_2 | 0x100000000000;
  }
  if ((*(int *)*param_1 == 0) && ((*(byte *)(param_1[2] + 4) & 0xe) != 10)) {
    bVar4 = *(byte *)(param_1 + 5);
    if (bVar4 == 0x40) {
      *(bool *)((long)param_2 + 0x1d) = (*(byte *)(param_1[2] + 4) & 0xe) != 8;
    }
    else {
      if (0x40 < bVar4) {
LAB_001f079c:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x10e5,
                      "ZydisBuildInstruction");
      }
      if (bVar4 == 0x10) {
        *param_2 = *param_2 | 0x80000000000;
      }
      else if (bVar4 != 0x20) goto LAB_001f079c;
    }
  }
  else if (cVar5 != (char)param_1[5]) {
    *param_2 = *param_2 | 0x80000000000;
  }
  local_22 = 0;
  do {
    if (*(byte *)(*param_1 + 0x28) <= local_22) {
      return 0x100000;
    }
    puVar1 = (uint *)(*param_1 + (long)(int)(uint)local_22 * 0x40 + 0x30);
    pbVar6 = (byte *)(param_1[3] + (ulong)local_22 * 5);
    uVar2 = *puVar1;
    if (uVar2 == 4) {
      if ((*pbVar6 & 0x3f) != 3) {
        pbVar6 = (byte *)ZydisGetOperandDetails(pbVar6);
        if ((*pbVar6 & 0x3f) == 5) {
          if (*(char *)((long)param_2 + 0x22) != '\b') {
                    /* WARNING: Subroutine does not return */
            __assert_fail("instruction->imm_size == 8",
                          "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x112d,
                          "ZydisBuildInstruction");
          }
          param_2[6] = param_2[6] | *(ulong *)(puVar1 + 0xe);
        }
        else {
          if (*(char *)((long)param_2 + 0x22) != '\0') {
            if (*(char *)((long)param_2 + 0x21) != '\0') {
                    /* WARNING: Subroutine does not return */
              __assert_fail("instruction->disp_size == 0",
                            "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                            0x1124,"ZydisBuildInstruction");
            }
            *(undefined1 *)((long)param_2 + 0x21) = *(undefined1 *)((long)param_1 + 0x2a);
            param_2[5] = param_2[6];
          }
          *(undefined1 *)((long)param_2 + 0x22) = *(undefined1 *)((long)param_1 + 0x2b);
          param_2[6] = *(ulong *)(puVar1 + 0xe);
        }
      }
    }
    else {
      if (4 < uVar2) {
LAB_001f0aa0:
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x1133,
                      "ZydisBuildInstruction");
      }
      if (uVar2 == 3) {
        *(undefined1 *)((long)param_2 + 0x21) = *(undefined1 *)((long)param_1 + 0x2a);
        param_2[5] = (ulong)puVar1[0xd];
        *(undefined1 *)((long)param_2 + 0x22) = *(undefined1 *)((long)param_1 + 0x2b);
        param_2[6] = (ulong)(ushort)puVar1[0xc];
      }
      else {
        if (3 < uVar2) goto LAB_001f0aa0;
        if (uVar2 == 1) {
          ZydisBuildRegisterOperand(puVar1,pbVar6,param_2);
        }
        else {
          if (uVar2 != 2) goto LAB_001f0aa0;
          if ((*pbVar6 & 0x3f) == 0x20) {
            *(undefined1 *)((long)param_2 + 0x21) = *(undefined1 *)((long)param_1 + 0x2a);
            param_2[5] = *(ulong *)(puVar1 + 8);
          }
          else {
            ZydisBuildMemoryOperand(param_1,puVar1,param_2);
            if ((*(char *)((long)param_1 + 0x2c) != '\0') &&
               (*(char *)((long)param_2 + 0x21) == '\b')) {
              param_2[5] = param_2[5] >> ((ulong)*(byte *)((long)param_1 + 0x2c) & 0x3f);
            }
            if ((*pbVar6 & 0x3f) - 0x18 < 3) {
              *(undefined1 *)((long)param_2 + 0x1b) = 1;
            }
          }
        }
      }
    }
    local_22 = local_22 + 1;
  } while( true );
}

