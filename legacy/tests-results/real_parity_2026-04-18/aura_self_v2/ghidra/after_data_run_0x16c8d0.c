
void after_data_run(long param_1,ulong *param_2,long param_3,undefined8 param_4,undefined8 *param_5,
                   undefined8 *param_6)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined8 *puVar4;
  int iVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  char *pcVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  ulong uVar12;
  ulong uVar13;
  undefined8 uVar14;
  undefined8 *local_68;
  uint local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0) && (param_2 != (ulong *)0x0 && param_3 != 0)) {
    uVar12 = *param_2;
    uVar13 = param_2[param_3 * 0x1c + -0x1c];
    uVar6 = param_2[param_3 * 0x1c + -0x19];
    if (uVar12 < uVar13 + uVar6) {
      if (*(uint *)(param_1 + 0x20) != 0) {
        puVar11 = *(undefined8 **)(param_1 + 0x18);
        puVar7 = puVar11 + (ulong)*(uint *)(param_1 + 0x20) * 7;
        do {
          if (((char *)*puVar11 != (char *)0x0) &&
             (iVar5 = strcmp((char *)*puVar11,".text"), iVar5 == 0)) {
            uVar14 = puVar11[5];
            goto LAB_0016c98c;
          }
          puVar11 = puVar11 + 7;
        } while (puVar11 != puVar7);
      }
      uVar14 = 0;
LAB_0016c98c:
      uVar1 = *(undefined4 *)(param_1 + 0xc);
      candidateset_init(&local_68);
      fd_datascan_add_candidates(param_1,&local_68,uVar12,uVar13 + uVar6,uVar1,uVar14);
      if (local_60 != 0) {
        puVar11 = malloc(0x10);
        if (puVar11 != (undefined8 *)0x0) {
          puVar7 = malloc((ulong)local_60 * 8);
          *puVar11 = puVar7;
          if (puVar7 != (undefined8 *)0x0) {
            uVar3 = local_60 - 1;
            *(uint *)(puVar11 + 1) = local_60;
            if (uVar3 < 0xd) {
              uVar6 = 0;
LAB_0016ca20:
              do {
                puVar7[uVar6] = local_68[uVar6 * 2];
                uVar6 = uVar6 + 1;
              } while (local_60 != uVar6);
            }
            else {
              uVar6 = 0;
              if (puVar7 < local_68 + (ulong)local_60 * 2 + -1 && local_68 < puVar7 + local_60)
              goto LAB_0016ca20;
              puVar8 = local_68;
              puVar10 = puVar7;
              do {
                uVar14 = *puVar8;
                puVar4 = puVar8 + 2;
                puVar8 = puVar8 + 4;
                puVar10[1] = *puVar4;
                *puVar10 = uVar14;
                puVar10 = puVar10 + 2;
              } while (local_68 + (ulong)(uVar3 >> 1) * 4 != puVar8);
              uVar2 = uVar3 | 1;
              puVar7[(ulong)uVar3 & 0xfffffffe] = local_68[((ulong)uVar3 & 0xfffffffe) * 2];
              if (uVar2 < local_60) {
                puVar7[uVar2] = local_68[(ulong)uVar2 * 2];
              }
            }
            candidateset_free(&local_68);
            uVar14 = 0;
            *param_5 = puVar11;
            goto LAB_0016ca6c;
          }
          free(puVar11);
        }
        candidateset_free(&local_68);
        if (param_6 != (undefined8 *)0x0) {
          pcVar9 = strdup("OOM: result allocation failed");
          *param_6 = pcVar9;
        }
        uVar14 = 2;
        goto LAB_0016ca6c;
      }
      candidateset_free(&local_68);
    }
  }
  uVar14 = 1;
LAB_0016ca6c:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar14,PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

