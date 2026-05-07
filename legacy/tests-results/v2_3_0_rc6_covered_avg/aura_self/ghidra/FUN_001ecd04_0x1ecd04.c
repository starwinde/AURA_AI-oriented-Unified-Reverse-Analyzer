
undefined8 FUN_001ecd04(undefined8 *param_1,long param_2)

{
  uint *puVar1;
  byte *pbVar2;
  uint uVar3;
  char cVar4;
  undefined8 uVar5;
  byte local_13;
  char local_12;
  char local_11;
  
  if (*(byte *)(param_2 + 0x28) !=
      (byte)((*(byte *)(param_1[2] + 2) & 3) << 1 | *(byte *)(param_1[2] + 1) >> 7)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("request->operand_count == match->base_definition->operand_count_visible",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xb05,
                  "ZydisIsDefinitionCompatible");
  }
  uVar5 = FUN_001f2e04(param_1[2]);
  param_1[3] = uVar5;
  cVar4 = FUN_001ebd6c(param_1,param_2);
  if (cVar4 == '\0') {
    uVar5 = 0;
  }
  else {
    cVar4 = FUN_001ec048(param_1,param_2);
    if (cVar4 == '\0') {
      uVar5 = 0;
    }
    else {
      for (local_13 = 0; local_13 < *(byte *)(param_2 + 0x28); local_13 = local_13 + 1) {
        puVar1 = (uint *)(param_2 + (long)(int)(uint)local_13 * 0x40 + 0x30);
        pbVar2 = (byte *)(param_1[3] + (ulong)local_13 * 5);
        if ((*pbVar2 & 0xc0) == 0xc0) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("def_op->visibility != ZYDIS_OPERAND_VISIBILITY_HIDDEN",
                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xb15,
                        "ZydisIsDefinitionCompatible");
        }
        uVar3 = *puVar1;
        if (uVar3 == 4) {
          local_12 = FUN_001eb8f4(param_1,puVar1,pbVar2);
        }
        else {
          if (4 < uVar3) {
LAB_001ecedc:
                    /* WARNING: Subroutine does not return */
            __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                          0xb26,"ZydisIsDefinitionCompatible");
          }
          if (uVar3 == 3) {
            local_12 = FUN_001eb790(param_1,puVar1);
          }
          else {
            if (3 < uVar3) goto LAB_001ecedc;
            if (uVar3 == 1) {
              local_12 = FUN_001e99f0(param_1,puVar1,pbVar2);
            }
            else {
              if (uVar3 != 2) goto LAB_001ecedc;
              local_12 = FUN_001eaac4(param_1,puVar1,pbVar2);
            }
          }
        }
        if (local_12 == '\0') {
          return 0;
        }
      }
      local_11 = '\0';
      if (((*(byte *)(param_1[2] + 8) & 0xe0) != 0) && ((*(byte *)(param_1[2] + 8) & 0xe0) != 0x80))
      {
        uVar3 = *(uint *)(param_2 + 0x1c);
        if (uVar3 == 4) {
          if (*(char *)((long)param_1 + 0x35) != '\0') {
            return 0;
          }
          local_11 = '@';
        }
        else {
          if (4 < uVar3) {
LAB_001ed06c:
                    /* WARNING: Subroutine does not return */
            __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                          0xb50,"ZydisIsDefinitionCompatible");
          }
          if (uVar3 == 3) {
            if (((*(char *)((long)param_1 + 0x35) == '\0') || (*(int *)*param_1 != 0)) ||
               ((*(byte *)(param_1[2] + 4) & 0xe) != 10)) {
              local_11 = ' ';
            }
            else {
              local_11 = '@';
            }
          }
          else {
            if (3 < uVar3) goto LAB_001ed06c;
            if (uVar3 == 2) {
              local_11 = '\x10';
            }
            else {
              if (2 < uVar3) goto LAB_001ed06c;
              if (uVar3 != 0) {
                if (uVar3 != 1) goto LAB_001ed06c;
                if ((*(char *)((long)param_1 + 0x35) == '\0') ||
                   ((*(byte *)(param_1[2] + 8) & 0xe0) != 0x20)) {
                  return 0;
                }
              }
            }
          }
        }
      }
      if (local_11 != '\0') {
        if (*(char *)(param_1 + 5) == '\0') {
          *(char *)(param_1 + 5) = local_11;
        }
        else if (local_11 != *(char *)(param_1 + 5)) {
          return 0;
        }
      }
      cVar4 = FUN_001ec77c(param_1);
      if (cVar4 == '\0') {
        uVar5 = 0;
      }
      else {
        uVar5 = 1;
      }
    }
  }
  return uVar5;
}

