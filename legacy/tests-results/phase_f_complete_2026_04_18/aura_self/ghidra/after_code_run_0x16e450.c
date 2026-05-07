
void after_code_run(long param_1,ulong *param_2,long param_3,undefined8 param_4,undefined8 *param_5,
                   undefined8 *param_6)

{
  uint uVar1;
  uint uVar2;
  undefined8 *puVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  char *pcVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  ulong uVar12;
  ulong uVar13;
  undefined8 *local_78;
  uint local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_2 != (ulong *)0x0 && param_3 != 0) && param_1 != 0) {
    uVar12 = *param_2;
    uVar13 = param_2[param_3 * 0x1c + -0x1c];
    uVar6 = param_2[param_3 * 0x1c + -0x19];
    if (uVar12 < uVar13 + uVar6) {
      if (*(uint *)(param_1 + 0x20) != 0) {
        puVar11 = *(undefined8 **)(param_1 + 0x18);
        puVar7 = puVar11 + (ulong)*(uint *)(param_1 + 0x20) * 7;
        do {
          if (((char *)*puVar11 != (char *)0x0) &&
             (iVar4 = strcmp((char *)*puVar11,".text"), iVar4 == 0)) {
            uVar5 = puVar11[5];
            goto LAB_0016e55c;
          }
          puVar11 = puVar11 + 7;
        } while (puVar11 != puVar7);
      }
      uVar5 = 0;
LAB_0016e55c:
      iVar4 = *(int *)(param_1 + 0xc);
      if (iVar4 != 0) {
        candidateset_init(&local_78);
        fd_gap_add_candidates(param_2,param_3,&local_78,uVar12,uVar13 + uVar6,iVar4,uVar5);
        if (local_70 != 0) {
          puVar11 = malloc(0x10);
          if (puVar11 != (undefined8 *)0x0) {
            puVar7 = malloc((ulong)local_70 * 8);
            *puVar11 = puVar7;
            if (puVar7 != (undefined8 *)0x0) {
              uVar2 = local_70 - 1;
              *(uint *)(puVar11 + 1) = local_70;
              if (uVar2 < 0xd) {
                uVar6 = 0;
LAB_0016e5f8:
                do {
                  puVar7[uVar6] = local_78[uVar6 * 2];
                  uVar6 = uVar6 + 1;
                } while (local_70 != uVar6);
              }
              else {
                uVar6 = 0;
                if (puVar7 < local_78 + (ulong)local_70 * 2 + -1 && local_78 < puVar7 + local_70)
                goto LAB_0016e5f8;
                puVar8 = local_78;
                puVar10 = puVar7;
                do {
                  uVar5 = *puVar8;
                  puVar3 = puVar8 + 2;
                  puVar8 = puVar8 + 4;
                  puVar10[1] = *puVar3;
                  *puVar10 = uVar5;
                  puVar10 = puVar10 + 2;
                } while (local_78 + (ulong)(uVar2 >> 1) * 4 != puVar8);
                uVar1 = uVar2 | 1;
                puVar7[(ulong)uVar2 & 0xfffffffe] = local_78[((ulong)uVar2 & 0xfffffffe) * 2];
                if (uVar1 < local_70) {
                  puVar7[uVar1] = local_78[(ulong)uVar1 * 2];
                }
              }
              candidateset_free(&local_78);
              uVar5 = 0;
              *param_5 = puVar11;
              goto LAB_0016e48c;
            }
            free(puVar11);
          }
          candidateset_free(&local_78);
          if (param_6 != (undefined8 *)0x0) {
            pcVar9 = strdup("OOM: result allocation failed");
            *param_6 = pcVar9;
          }
          uVar5 = 2;
          goto LAB_0016e48c;
        }
        candidateset_free(&local_78);
      }
    }
  }
  uVar5 = 1;
LAB_0016e48c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar5,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

