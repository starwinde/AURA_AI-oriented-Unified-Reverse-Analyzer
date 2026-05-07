
int eliminate_dead_stores_in_block(long param_1,long param_2)

{
  long lVar1;
  undefined8 *puVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  void *__ptr;
  uint uVar6;
  undefined8 *puVar7;
  ulong uVar8;
  int *piVar9;
  ulong uVar10;
  long lVar11;
  uint uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int aiStack_464 [257];
  undefined8 local_60;
  long local_58;
  
  local_60 = 0;
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != 0) && (uVar3 = *(uint *)(param_1 + 0x10), param_2 != 0 && uVar3 != 0)) {
    uVar10 = (ulong)uVar3;
    __ptr = malloc(uVar10);
    if (__ptr != (void *)0x0) {
      __memset_chk(__ptr,1,uVar10,uVar10);
      iVar5 = uVar3 - 1;
      if (-1 < iVar5) {
        lVar13 = (long)iVar5;
        uVar12 = 0;
        lVar11 = (long)iVar5 * 0x90;
        do {
          lVar1 = *(long *)(param_1 + 8) + lVar11;
          iVar5 = *(int *)(*(long *)(param_1 + 8) + lVar11);
          if (iVar5 == 0x16) {
            if (((*(int *)(lVar1 + 0x48) != 0) && (*(int *)(lVar1 + 0x18) != -1)) &&
               (iVar5 = alias_get_partition(param_2), iVar5 != -1)) {
              uVar10 = 0;
              if (uVar12 != 0) {
                uVar10 = (ulong)uVar12;
                uVar8 = 1;
                do {
                  if (iVar5 == aiStack_464[uVar8]) {
                    *(undefined1 *)((long)__ptr + lVar13) = 0;
                    goto LAB_00156bb4;
                  }
                  bVar4 = uVar10 != uVar8;
                  uVar8 = uVar8 + 1;
                } while (bVar4);
                uVar8 = 1;
                do {
                  if (iVar5 == aiStack_464[uVar8]) goto LAB_00156bb4;
                  bVar4 = uVar10 != uVar8;
                  uVar8 = uVar8 + 1;
                } while (bVar4);
                if (0xff < uVar12) goto LAB_00156bb4;
              }
              uVar12 = uVar12 + 1;
              aiStack_464[uVar10 + 1] = iVar5;
            }
          }
          else if (iVar5 == 0x19) {
LAB_00156bb0:
            uVar12 = 0;
          }
          else if (iVar5 == 0x15) {
            if (((*(int *)(lVar1 + 0x48) == 0) || (*(int *)(lVar1 + 0x18) == -1)) ||
               ((iVar5 = alias_get_partition(param_2), iVar5 == -1 || (uVar12 == 0))))
            goto LAB_00156bb0;
            uVar6 = 0;
            piVar9 = aiStack_464 + 1;
            do {
              if (iVar5 == *piVar9) {
                uVar12 = uVar12 - 1;
                aiStack_464[(ulong)uVar6 + 1] = aiStack_464[(ulong)uVar12 + 1];
                break;
              }
              uVar6 = uVar6 + 1;
              piVar9 = piVar9 + 1;
            } while (uVar6 != uVar12);
          }
LAB_00156bb4:
          lVar13 = lVar13 + -1;
          lVar11 = lVar11 + -0x90;
        } while (-1 < (int)lVar13);
      }
      lVar11 = 0;
      uVar12 = 0;
      iVar5 = 0;
      do {
        if (*(char *)((long)__ptr + lVar11) == '\0') {
          iVar5 = iVar5 + 1;
          free(*(void **)(*(long *)(param_1 + 8) + lVar11 * 0x90 + 0x50));
          free(*(void **)(*(long *)(param_1 + 8) + lVar11 * 0x90 + 0x58));
        }
        else {
          if (uVar12 != (uint)lVar11) {
            puVar2 = (undefined8 *)(*(long *)(param_1 + 8) + lVar11 * 0x90);
            puVar7 = (undefined8 *)(*(long *)(param_1 + 8) + (ulong)uVar12 * 0x90);
            uVar14 = *puVar2;
            uVar16 = puVar2[3];
            uVar15 = puVar2[2];
            puVar7[1] = puVar2[1];
            *puVar7 = uVar14;
            puVar7[3] = uVar16;
            puVar7[2] = uVar15;
            uVar14 = puVar2[4];
            uVar16 = puVar2[7];
            uVar15 = puVar2[6];
            puVar7[5] = puVar2[5];
            puVar7[4] = uVar14;
            puVar7[7] = uVar16;
            puVar7[6] = uVar15;
            uVar14 = puVar2[8];
            uVar16 = puVar2[0xb];
            uVar15 = puVar2[10];
            puVar7[9] = puVar2[9];
            puVar7[8] = uVar14;
            puVar7[0xb] = uVar16;
            puVar7[10] = uVar15;
            uVar14 = puVar2[0xc];
            uVar16 = puVar2[0xf];
            uVar15 = puVar2[0xe];
            puVar7[0xd] = puVar2[0xd];
            puVar7[0xc] = uVar14;
            puVar7[0xf] = uVar16;
            puVar7[0xe] = uVar15;
            uVar14 = puVar2[0x10];
            puVar7[0x11] = puVar2[0x11];
            puVar7[0x10] = uVar14;
          }
          uVar12 = uVar12 + 1;
        }
        lVar11 = lVar11 + 1;
      } while ((uint)lVar11 < uVar3);
      *(uint *)(param_1 + 0x10) = uVar12;
      free(__ptr);
      goto LAB_00156afc;
    }
  }
  iVar5 = 0;
LAB_00156afc:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar5;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

