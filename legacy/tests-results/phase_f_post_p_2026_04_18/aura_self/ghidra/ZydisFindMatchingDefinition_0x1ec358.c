
undefined4 ZydisFindMatchingDefinition(int *param_1,undefined8 *param_2)

{
  bool bVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  char cVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined1 uVar11;
  byte local_3b;
  undefined8 *local_28;
  long local_20;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  memset(param_2,0,0x38);
  *param_2 = param_1;
  param_2[4] = *(undefined8 *)(param_1 + 4);
  local_28 = (undefined8 *)0x0;
  bVar2 = ZydisGetEncodableInstructions(param_1[2],&local_28);
  if ((local_28 == (undefined8 *)0x0) || (bVar2 == 0)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("definition && definition_count",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xc5f,
                  "ZydisFindMatchingDefinition");
  }
  uVar7 = ZydisGetMachineModeWidth(*param_1);
  uVar7 = (uVar7 & 0xff) >> 4;
  if ((*param_1 == 2) || (*param_1 == 1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = ZydisGetAszFromHint(param_1[8]);
  uVar4 = ZydisGetOszFromHint(param_1[9]);
  sVar6 = ZydisGetOperandMask(param_1);
  uVar8 = ZydisGetViableEncodings(param_1);
  if (uVar8 == 0) {
    uVar10 = 0x8020000d;
  }
  else {
    for (local_3b = 0; local_3b < bVar2; local_3b = local_3b + 1) {
      if (sVar6 == *(short *)((long)local_28 + 2)) {
        local_20 = 0;
        ZydisGetInstructionDefinition
                  (*(byte *)((long)local_28 + 6) & 7,*(undefined2 *)local_28,&local_20);
        if ((((uint)((ulong)*local_28 >> 0x37) & 7 & uVar7) != 0) &&
           (uVar9 = ZydisGetEncodableEncoding(*(byte *)((long)local_28 + 6) & 7),
           (uVar9 & uVar8) != 0)) {
          if (*param_1 == 5) {
            if (((*(byte *)(local_20 + 5) & 0x20) == 0) &&
               (3 < (*(byte *)((long)local_28 + 6) & 7) - 2)) {
LAB_001ec5a8:
              if ((((!bVar1) || ((*(byte *)(local_20 + 5) & 0x40) == 0)) &&
                  ((param_1[6] == 0 || (param_1[6] == (uint)(*(byte *)(local_20 + 8) >> 5))))) &&
                 ((((*(byte *)(local_20 + 8) & 0xe0) != 0 &&
                   ((*(byte *)(local_20 + 8) & 0xe0) != 0x80)) || (param_1[7] == 0)))) {
                param_2[1] = local_28;
                param_2[2] = local_20;
                param_2[3] = 0;
                uVar11 = uVar3;
                if ((*(byte *)((long)local_28 + 9) & 0xc) != 4) {
                  uVar11 = 0;
                }
                *(undefined1 *)((long)param_2 + 0x29) = uVar11;
                uVar11 = uVar4;
                if ((*(byte *)((long)local_28 + 9) & 0xc) != 8) {
                  uVar11 = 0;
                }
                *(undefined1 *)(param_2 + 5) = uVar11;
                *(undefined1 *)((long)param_2 + 0x2c) = 0;
                *(undefined1 *)((long)param_2 + 0x2b) = *(undefined1 *)((long)param_2 + 0x2c);
                *(undefined1 *)((long)param_2 + 0x2a) = *(undefined1 *)((long)param_2 + 0x2b);
                *(undefined4 *)(param_2 + 6) = 0;
                *(undefined1 *)((long)param_2 + 0x34) = 0;
                *(undefined1 *)((long)param_2 + 0x35) = 0;
                if ((((*(byte *)(local_20 + 4) & 0xe) == 2) || (*(char *)(param_2 + 5) != '\b')) &&
                   ((cVar5 = ZydisArePrefixesCompatible(param_2), cVar5 != '\0' &&
                    (cVar5 = ZydisIsDefinitionCompatible(param_2,param_1), cVar5 != '\0')))) {
                  cVar5 = ZydisHandleSwappableDefinition(param_2);
                  if (cVar5 != '\0') {
                    if ((undefined8 *)param_2[1] == local_28) goto LAB_001ecb60;
                    local_3b = local_3b + 1;
                    local_28 = (undefined8 *)param_2[1];
                    local_20 = param_2[2];
                  }
                  if (*(char *)((long)param_2 + 0x29) == '\0') {
                    if (((uint)((ulong)*local_28 >> 0x3a) & 7 & uVar7) == 0) {
                      if (uVar7 == 1) {
                        *(undefined1 *)((long)param_2 + 0x29) = 0x20;
                      }
                      else if (uVar7 == 2) {
                        *(undefined1 *)((long)param_2 + 0x29) = 0x10;
                      }
                      else {
                        *(undefined1 *)((long)param_2 + 0x29) = 0x20;
                      }
                    }
                    else {
                      *(char *)((long)param_2 + 0x29) = (char)(uVar7 << 4);
                    }
                    if (((uint)((ulong)*local_28 >> 0x3a) & 7 &
                        (uint)(*(byte *)((long)param_2 + 0x29) >> 4)) == 0) {
                    /* WARNING: Subroutine does not return */
                      __assert_fail("definition->address_sizes & (match->easz >> 4)",
                                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c"
                                    ,0xcd7,"ZydisFindMatchingDefinition");
                    }
                  }
                  else if (((uint)((ulong)*local_28 >> 0x3a) & 7 &
                           (uint)(*(byte *)((long)param_2 + 0x29) >> 4)) == 0) goto LAB_001ecb60;
                  if (uVar7 == 4) {
                    if ((*(byte *)(local_20 + 4) & 0xe) == 8) {
                      if (*(char *)(param_2 + 5) == '\0') {
                        if ((*(byte *)((long)local_28 + 7) >> 5 & 5) == 0) {
                    /* WARNING: Subroutine does not return */
                          __assert_fail("definition->operand_sizes & (ZYDIS_WIDTH_16 | ZYDIS_WIDTH_64)"
                                        ,
                                        "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c"
                                        ,0xce4,"ZydisFindMatchingDefinition");
                        }
                        if ((*(byte *)((long)local_28 + 7) >> 5 & 4) == 0) {
                          *(undefined1 *)(param_2 + 5) = 0x10;
                        }
                        else {
                          *(undefined1 *)(param_2 + 5) = 0x40;
                        }
                      }
                      else if (*(char *)(param_2 + 5) == ' ') goto LAB_001ecb60;
                    }
                    else if ((*(byte *)(local_20 + 4) & 0xe) == 10) {
                      if (*(char *)(param_2 + 5) == '\0') {
                        *(undefined1 *)(param_2 + 5) = 0x40;
                      }
                      else if (*(char *)(param_2 + 5) != '@') goto LAB_001ecb60;
                    }
                  }
                  if (*(char *)(param_2 + 5) == '\0') {
                    if (uVar7 == 4) {
                      uVar7 = 2;
                    }
                    if ((*(byte *)((long)local_28 + 7) >> 5 & uVar7) == 0) {
                      if ((*(byte *)((long)local_28 + 7) >> 5 & 1) == 0) {
                        if ((*(byte *)((long)local_28 + 7) >> 5 & 2) == 0) {
                          *(undefined1 *)(param_2 + 5) = 0x40;
                        }
                        else {
                          *(undefined1 *)(param_2 + 5) = 0x20;
                        }
                      }
                      else {
                        *(undefined1 *)(param_2 + 5) = 0x10;
                      }
                    }
                    else {
                      *(char *)(param_2 + 5) = (char)(uVar7 << 4);
                    }
                  }
                  else if (((*(char *)((long)param_2 + 0x34) != '\0') &&
                           (*(char *)(param_2 + 5) == '@')) ||
                          ((byte)(*(byte *)((long)local_28 + 7) >> 5 & *(byte *)(param_2 + 5) >> 4)
                           == 0)) goto LAB_001ecb60;
                  uVar10 = 0x100000;
                  goto LAB_001ecb90;
                }
              }
            }
          }
          else if ((*param_1 == 0) || ((*(byte *)((long)local_28 + 6) & 7) != 5)) goto LAB_001ec5a8;
        }
      }
LAB_001ecb60:
      local_28 = (undefined8 *)((long)local_28 + 10);
    }
    uVar10 = 0x8020000d;
  }
LAB_001ecb90:
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar10;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,uVar10,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

