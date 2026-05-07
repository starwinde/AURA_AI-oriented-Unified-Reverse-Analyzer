
void extern_entry_refs_run
               (long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 *param_5,undefined8 *param_6)

{
  ulong uVar1;
  uint uVar2;
  long *__ptr;
  undefined8 uVar3;
  char *pcVar4;
  undefined8 *puVar5;
  long *plVar6;
  long lVar7;
  long *plVar8;
  long lVar10;
  uint uVar11;
  char *pcVar12;
  uint local_78;
  uint local_74;
  long *local_70;
  long local_68;
  long *plVar9;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != 0 && param_5 != (undefined8 *)0x0) {
    *param_5 = 0;
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0;
    }
    lVar10 = *(long *)(param_1 + 0x28);
    if ((lVar10 != 0) && (uVar11 = *(uint *)(param_1 + 0x30), uVar11 != 0)) {
      local_78 = 0;
      local_74 = 0x20;
      local_70 = calloc(0x20,0x18);
      lVar7 = 0;
      if (local_70 == (long *)0x0) {
        if (param_6 != (undefined8 *)0x0) {
          pcVar12 = strdup("extern_entry_refs: allocation failed");
          *param_6 = pcVar12;
        }
      }
      else {
LAB_00169ef8:
        uVar2 = local_78;
        puVar5 = (undefined8 *)(lVar10 + lVar7 * 0x28);
        if (((*(int *)((long)puVar5 + 0x24) - 1U < 2) &&
            (*(int *)(puVar5 + 4) == 1 || *(int *)(puVar5 + 4) == 4)) &&
           (lVar10 = puVar5[2], lVar10 != 0)) {
          pcVar12 = (char *)puVar5[1];
          if (pcVar12 == (char *)0x0) {
            pcVar12 = (char *)*puVar5;
          }
          if (local_78 != 0) {
            plVar6 = local_70;
            do {
              if (lVar10 == *plVar6) goto LAB_00169f60;
              plVar6 = plVar6 + 3;
            } while (plVar6 != local_70 + (ulong)local_78 * 3);
          }
          uVar11 = local_74;
          plVar6 = local_70;
          if (local_74 <= local_78) {
            uVar11 = local_74 << 1;
            if (uVar11 < 0x20) {
              uVar11 = 0x20;
            }
            plVar6 = realloc(local_70,(ulong)uVar11 * 0x18);
            __ptr = local_70;
            if (plVar6 != (long *)0x0) goto LAB_00169f80;
            if (local_78 != 0) {
              plVar6 = local_70 + 1;
              uVar1 = (ulong)local_78;
              plVar8 = plVar6;
              do {
                plVar9 = plVar8 + 3;
                free((void *)*plVar8);
                plVar8 = plVar9;
              } while (plVar9 != plVar6 + uVar1 * 3);
            }
            free(__ptr);
            if (param_6 != (undefined8 *)0x0) {
              pcVar12 = strdup("extern_entry_refs: OOM in exported symbols");
              *param_6 = pcVar12;
            }
            goto LAB_0016a0b4;
          }
LAB_00169f80:
          local_70 = plVar6;
          local_74 = uVar11;
          plVar6 = local_70;
          uVar1 = (ulong)uVar2;
          local_70[uVar1 * 3] = lVar10;
          pcVar4 = (char *)0x0;
          if (pcVar12 != (char *)0x0) {
            pcVar4 = strdup(pcVar12);
          }
          uVar11 = *(uint *)(param_1 + 0x30);
          local_78 = uVar2 + 1;
          plVar6[uVar1 * 3 + 1] = (long)pcVar4;
          *(undefined4 *)(plVar6 + uVar1 * 3 + 2) = 0;
          if ((int)lVar7 + 1U < uVar11) goto LAB_00169f6c;
        }
        else {
LAB_00169f60:
          if ((int)lVar7 + 1U < uVar11) goto LAB_00169f6c;
        }
        collect_callback_entries_isra_0(param_1,param_2,param_3,&local_70,&local_78,&local_74);
        uVar11 = local_78;
        if (local_78 == 0) {
          free(local_70);
          goto LAB_00169ea4;
        }
        puVar5 = malloc(0x10);
        plVar6 = local_70;
        if (puVar5 != (undefined8 *)0x0) {
          uVar3 = 0;
          *puVar5 = local_70;
          *(uint *)(puVar5 + 1) = uVar11;
          *param_5 = puVar5;
          goto LAB_00169ea8;
        }
        lVar10 = 0;
        do {
          lVar7 = lVar10 + 1;
          free((void *)plVar6[lVar10 * 3 + 1]);
          lVar10 = lVar7;
        } while ((uint)lVar7 < uVar11);
        free(plVar6);
        if (param_6 != (undefined8 *)0x0) {
          pcVar12 = strdup("extern_entry_refs: allocation failed for result");
          *param_6 = pcVar12;
        }
      }
LAB_0016a0b4:
      uVar3 = 2;
      goto LAB_00169ea8;
    }
  }
LAB_00169ea4:
  uVar3 = 1;
LAB_00169ea8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar3,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_00169f6c:
  lVar7 = lVar7 + 1;
  lVar10 = *(long *)(param_1 + 0x28);
  goto LAB_00169ef8;
}

