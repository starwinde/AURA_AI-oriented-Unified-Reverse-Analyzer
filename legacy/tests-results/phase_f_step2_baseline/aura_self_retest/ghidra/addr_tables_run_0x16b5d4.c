
void addr_tables_run(long param_1,long param_2,long param_3,undefined8 param_4,undefined8 *param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  undefined1 (*pauVar6) [16];
  undefined8 uVar7;
  undefined8 uVar8;
  undefined1 (*pauVar9) [16];
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined1 auVar13 [16];
  undefined8 *local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_2 != 0 && param_3 != 0) && param_1 != 0) {
    if (*(uint *)(param_1 + 0x20) == 0) {
      uVar7 = 0;
      uVar4 = 0;
      uVar8 = 0;
    }
    else {
      puVar10 = *(undefined8 **)(param_1 + 0x18);
      puVar11 = puVar10 + (ulong)*(uint *)(param_1 + 0x20) * 7;
      puVar5 = puVar10;
      do {
        if (((char *)*puVar5 != (char *)0x0) &&
           (iVar3 = strcmp((char *)*puVar5,".text"), iVar3 == 0)) goto LAB_0016b6d0;
        puVar5 = puVar5 + 7;
      } while (puVar5 != puVar11);
      puVar12 = (undefined8 *)0x0;
      do {
        puVar5 = puVar12;
        if (((((*(uint *)(puVar10 + 6) >> 2 & 1) != 0) && (puVar10[5] != 0)) && (puVar10[3] != 0))
           && ((puVar5 = puVar10, puVar12 != (undefined8 *)0x0 &&
               (puVar5 = puVar12, (ulong)puVar12[3] < (ulong)puVar10[3])))) {
          puVar5 = puVar10;
        }
        puVar10 = puVar10 + 7;
        puVar12 = puVar5;
      } while (puVar10 != puVar11);
      if (puVar5 == (undefined8 *)0x0) {
        uVar4 = 0;
        uVar7 = 0;
        uVar8 = 0;
      }
      else {
LAB_0016b6d0:
        uVar8 = puVar5[1];
        uVar7 = puVar5[3];
        uVar4 = puVar5[5];
      }
    }
    puVar5 = (undefined8 *)indirect_resolve(param_2,param_3,uVar4,uVar7,uVar8);
    local_60 = puVar5;
    if ((puVar5 != (undefined8 *)0x0) && (uVar1 = *(uint *)(puVar5 + 1), uVar1 != 0)) {
      puVar10 = calloc((ulong)uVar1,0x18);
      if (puVar10 == (undefined8 *)0x0) {
        indirect_destroy(&local_60);
      }
      else {
        pauVar6 = (undefined1 (*) [16])*puVar5;
        pauVar9 = (undefined1 (*) [16])((long)pauVar6 + (ulong)uVar1 * 0x18);
        puVar5 = puVar10;
        do {
          iVar3 = *(int *)pauVar6[1];
          auVar13 = NEON_ext(*pauVar6,*pauVar6,8,1);
          puVar5[1] = auVar13._8_8_;
          *puVar5 = auVar13._0_8_;
          iVar2 = 1;
          if (iVar3 != 1) {
            iVar2 = (uint)(iVar3 != 2) << 1;
          }
          pauVar6 = (undefined1 (*) [16])(pauVar6[1] + 8);
          *(int *)(puVar5 + 2) = iVar2;
          puVar5 = puVar5 + 3;
        } while (pauVar9 != pauVar6);
        indirect_destroy(&local_60);
        puVar5 = malloc(0x10);
        if (puVar5 != (undefined8 *)0x0) {
          uVar4 = 0;
          *puVar5 = puVar10;
          *(uint *)(puVar5 + 1) = uVar1;
          *param_5 = puVar5;
          goto LAB_0016b610;
        }
        free(puVar10);
      }
      uVar4 = 2;
      goto LAB_0016b610;
    }
    indirect_destroy(&local_60);
  }
  uVar4 = 1;
LAB_0016b610:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar4,PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

