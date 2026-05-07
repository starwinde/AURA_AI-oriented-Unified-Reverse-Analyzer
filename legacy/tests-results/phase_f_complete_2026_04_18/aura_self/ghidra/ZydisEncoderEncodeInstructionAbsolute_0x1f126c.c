
int ZydisEncoderEncodeInstructionAbsolute
              (undefined4 *param_1,long param_2,ulong *param_3,ulong param_4)

{
  int *piVar1;
  char cVar2;
  char cVar3;
  bool bVar4;
  undefined2 uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  byte local_be;
  bool local_bd;
  byte local_bc;
  byte local_bb;
  byte local_ba;
  undefined4 local_a8;
  int *local_a0;
  long local_98;
  undefined2 *local_90;
  undefined1 auStack_60 [8];
  int local_58;
  byte local_3f;
  byte local_3e;
  undefined2 local_20;
  undefined1 local_1e;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == (undefined4 *)0x0) || (param_2 == 0)) || (param_3 == (ulong *)0x0)) {
    iVar7 = -0x7feffffc;
  }
  else {
    iVar7 = ZydisEncoderCheckRequestSanity(param_1,0);
    if (-1 < iVar7) {
      lVar10 = ZydisGetRelInfo(param_1[2]);
      local_a0 = (int *)0x0;
      bVar4 = false;
      local_98 = 0;
      uVar8 = ZydisGetMachineModeWidth(*param_1);
      uVar8 = (uVar8 & 0xff) >> 5;
      for (local_be = 0; local_be < *(byte *)(param_1 + 10); local_be = local_be + 1) {
        piVar1 = param_1 + (long)(int)(uint)local_be * 0x10 + 0xc;
        if ((*piVar1 == 4) && (lVar10 != 0)) {
          if (bVar4) {
            iVar7 = -0x7feffffc;
            goto LAB_001f1af8;
          }
          bVar6 = *(byte *)(lVar10 + 9);
          if (bVar6 != 2) {
            if (2 < bVar6) {
LAB_001f18d0:
                    /* WARNING: Subroutine does not return */
              __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                            0x12da,"ZydisEncoderEncodeInstructionAbsolute");
            }
            if (bVar6 != 0) {
              if (bVar6 != 1) goto LAB_001f18d0;
              cVar3 = asz_prefix_lookup_3[(ulong)(uint)param_1[8] + (long)(int)uVar8 * 4];
              if (cVar3 < '\0') {
                iVar7 = -0x7feffffc;
              }
              else {
                bVar6 = (byte)uVar8;
                if (param_1[8] != 0) {
                  uVar9 = ZydisGetAszFromHint(param_1[8]);
                  bVar6 = (byte)((uVar9 & 0xff) >> 5);
                }
                if ((((*(char *)(lVar10 + (long)(int)(uint)bVar6 * 3) == '\0') ||
                     (*(char *)(lVar10 + (long)(int)(uint)bVar6 * 3 + 1) != '\0')) ||
                    (*(char *)(lVar10 + (long)(int)(uint)bVar6 * 3 + 2) != '\0')) ||
                   (*(char *)(lVar10 + 10) != '\0')) {
                    /* WARNING: Subroutine does not return */
                  __assert_fail("(rel_info->size[asz_index][0] != 0) && (rel_info->size[asz_index][1] == 0) && (rel_info->size[asz_index][2] == 0) && !rel_info->accepts_branch_hints"
                                ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                                0x12c6,"ZydisEncoderEncodeInstructionAbsolute");
                }
                bVar6 = *(char *)(lVar10 + (long)(int)(uint)bVar6 * 3) + cVar3;
                if (-(ulong)bVar6 < param_4) {
                  iVar7 = -0x7feffffc;
                }
                else {
                  lVar11 = *(long *)(piVar1 + 0xe) - (bVar6 + param_4);
                  bVar6 = ZydisGetSignedImmSize(lVar11);
                  if (bVar6 < 9) {
                    *(long *)(piVar1 + 0xe) = lVar11;
                    bVar4 = true;
LAB_001f18fc:
                    if (bVar4) goto LAB_001f1978;
                    iVar7 = -0x7feffffc;
                  }
                  else {
                    iVar7 = -0x7feffffc;
                  }
                }
              }
              goto LAB_001f1af8;
            }
          }
          local_20 = DAT_00570f58;
          uVar5 = local_20;
          local_1e = DAT_00570f5a;
          local_bd = false;
          local_bc = 0;
          local_20._1_1_ = (undefined1)((ushort)DAT_00570f58 >> 8);
          local_20 = uVar5;
          if (*(char *)(lVar10 + 9) == '\0') {
            if ((param_1[6] == 3) || (param_1[7] == 4)) {
              iVar7 = -0x7feffffc;
              goto LAB_001f1af8;
            }
            if ((*(char *)(lVar10 + 10) != '\0') && ((*(ulong *)(param_1 + 4) & 0xc00000000) != 0))
            {
              local_bd = true;
            }
            if ((((*(char *)(lVar10 + 0xb) != '\0') && ((*(ulong *)(param_1 + 4) & 0x80000000) != 0)
                 ) && (local_bd = (bool)(local_bd + '\x01'), param_1[2] == 0x17a)) &&
               ((param_1[6] == 0 && (param_1[7] == 0)))) {
              local_bc = 1;
            }
            if (param_1[7] == 0) {
              if (param_1[6] == 2) {
                local_bc = 1;
              }
              local_90 = (undefined2 *)(asz_priority_5 + (long)(int)uVar8 * 3);
            }
            else {
              local_20 = CONCAT11(local_20._1_1_,(char)param_1[7] + -1);
              local_90 = &local_20;
            }
          }
          else if (param_1[9] == 0) {
            local_90 = (undefined2 *)(osz_priority_4 + (long)(int)uVar8 * 3);
          }
          else {
            if (param_1[9] != 4) {
              local_20 = CONCAT11(local_20._1_1_,(char)param_1[9] + -1);
            }
            else {
              local_20 = CONCAT11(local_20._1_1_,2);
            }
            local_bd = param_1[9] == 4;
            local_90 = &local_20;
          }
          local_bb = local_bc;
          do {
            if ((2 < local_bb) ||
               (cVar3 = *(char *)((long)local_90 + (ulong)local_bb), cVar3 < '\0'))
            goto LAB_001f18fc;
            cVar2 = *(char *)(lVar10 + (long)(int)uVar8 * 3 + (long)(int)cVar3);
            if ((cVar2 != '\0') && (bVar6 = cVar2 + local_bd, param_4 <= -(ulong)bVar6)) {
              lVar11 = *(long *)(piVar1 + 0xe) - (bVar6 + param_4);
              bVar6 = ZydisGetSignedImmSize(lVar11);
              if ((int)(uint)bVar6 <= 8 << (ulong)((int)cVar3 & 0x1f)) {
                *(long *)(piVar1 + 0xe) = lVar11;
                bVar4 = true;
                if (*(char *)(lVar10 + 9) == '\0') {
                  if (param_1[7] == 0) {
                    param_1[7] = cVar3 + 1;
                  }
                }
                else if (param_1[9] == 0) {
                  param_1[9] = cVar3 + 1;
                }
                goto LAB_001f18fc;
              }
            }
            local_bb = local_bb + 1;
          } while( true );
        }
        if ((*piVar1 == 2) && ((piVar1[4] == 0x104 || (piVar1[4] == 0x105)))) {
          if (local_a0 != (int *)0x0) {
            iVar7 = -0x7feffffc;
            goto LAB_001f1af8;
          }
          local_98 = *(long *)(piVar1 + 8);
          piVar1[8] = 0;
          piVar1[9] = 0;
          local_a0 = piVar1;
        }
LAB_001f1978:
      }
      iVar7 = ZydisEncoderEncodeInstructionInternal(param_1,param_2,param_3,auStack_60);
      if (-1 < iVar7) {
        if (local_a0 != (int *)0x0) {
          uVar12 = *param_3;
          if (-uVar12 < param_4) {
            iVar7 = -0x7feffffc;
            goto LAB_001f1af8;
          }
          local_98 = local_98 - (param_4 + uVar12);
          bVar6 = ZydisGetSignedImmSize(local_98);
          if (0x20 < bVar6) {
            iVar7 = -0x7feffffc;
            goto LAB_001f1af8;
          }
          if (local_3f == 0) {
                    /* WARNING: Subroutine does not return */
            __assert_fail("instruction.disp_size != 0",
                          "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x12fe,
                          "ZydisEncoderEncodeInstructionAbsolute");
          }
          local_ba = (local_3f >> 3) + (local_3e >> 3);
          if (local_58 == 1) {
            local_ba = local_ba + 1;
          }
          if (uVar12 <= local_ba) {
                    /* WARNING: Subroutine does not return */
            __assert_fail("instruction_size > disp_offset",
                          "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x1304,
                          "ZydisEncoderEncodeInstructionAbsolute");
          }
          local_a8 = (undefined4)local_98;
          *(undefined4 *)(param_2 + (uVar12 - local_ba)) = local_a8;
          *(long *)(local_a0 + 8) = local_98;
        }
        iVar7 = 0x100000;
      }
    }
  }
LAB_001f1af8:
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar7;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar7,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

