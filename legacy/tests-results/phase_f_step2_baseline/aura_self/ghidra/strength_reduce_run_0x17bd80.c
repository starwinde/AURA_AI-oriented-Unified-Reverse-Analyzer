
bool strength_reduce_run(long *param_1,undefined4 *param_2)

{
  long lVar1;
  undefined4 *puVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  bool bVar7;
  int *piVar8;
  void *__ptr;
  long lVar9;
  undefined8 *puVar10;
  int *piVar11;
  undefined8 *puVar12;
  uint uVar13;
  int *piVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  long lVar18;
  int iVar19;
  uint uVar20;
  ulong uVar21;
  long lVar22;
  int local_18;
  
  if (param_1 == (long *)0x0) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = 0xfffffffc;
    }
    return false;
  }
  uVar16 = *(uint *)(param_1 + 1);
  lVar18 = 0;
  uVar17 = 0;
  bVar7 = false;
  local_18 = 0;
  if (uVar16 != 0) {
    do {
      lVar1 = *param_1 + lVar18;
      uVar13 = *(uint *)(lVar1 + 0x10);
      if (uVar13 != 0) {
        uVar21 = 0;
        do {
          uVar20 = (uint)uVar21;
          lVar22 = uVar21 * 0x88;
          puVar2 = (undefined4 *)(*(long *)(lVar1 + 8) + lVar22);
          if ((*(int *)(*(long *)(lVar1 + 8) + lVar22) == 4) && (1 < (uint)puVar2[0x12])) {
            piVar14 = puVar2 + 6;
            uVar15 = 0;
            while( true ) {
              iVar4 = *piVar14;
              if (uVar16 == 0) break;
              puVar10 = (undefined8 *)(*param_1 + 8);
              puVar12 = puVar10 + (ulong)uVar16 * 9;
              do {
                if (*(uint *)(puVar10 + 1) != 0) {
                  piVar8 = (int *)*puVar10;
                  piVar11 = piVar8 + (ulong)*(uint *)(puVar10 + 1) * 0x22;
LAB_0017be40:
                  if ((*piVar8 != 1) || (iVar4 != piVar8[2])) goto LAB_0017be34;
                  uVar21 = *(ulong *)(piVar8 + 4);
                  if ((0 < (long)uVar21) && ((uVar21 - 1 & uVar21) == 0)) {
                    iVar19 = 0;
                    for (; uVar21 != 1; uVar21 = (long)uVar21 >> 1) {
                      iVar19 = iVar19 + 1;
                    }
                    iVar5 = (int)param_1[2];
                    uVar16 = *(uint *)(lVar1 + 0x14);
                    uVar6 = puVar2[(ulong)(uVar15 ^ 1) * 4 + 6];
                    *puVar2 = 9;
                    __ptr = *(void **)(lVar1 + 8);
                    puVar2[6] = uVar6;
                    puVar2[10] = iVar4;
                    *(int *)(param_1 + 2) = iVar5 + 1;
                    if (uVar16 <= uVar13) {
                      uVar16 = uVar16 << 1;
                      __ptr = realloc(__ptr,(ulong)uVar16 * 0x88);
                      if (__ptr != (void *)0x0) {
                        uVar13 = *(uint *)(lVar1 + 0x10);
                        *(void **)(lVar1 + 8) = __ptr;
                        *(uint *)(lVar1 + 0x14) = uVar16;
                        goto LAB_0017bf08;
                      }
                      uVar16 = *(uint *)(param_1 + 1);
                      uVar13 = *(uint *)(lVar1 + 0x10);
                      break;
                    }
LAB_0017bf08:
                    uVar13 = uVar13 - uVar20;
                    uVar20 = uVar20 + 1;
                    memmove((void *)((long)__ptr + (ulong)uVar20 * 0x88),
                            (void *)((long)__ptr + lVar22),(ulong)uVar13 * 0x88);
                    puVar10 = (undefined8 *)(*(long *)(lVar1 + 8) + lVar22);
                    *(int *)(lVar1 + 0x10) = *(int *)(lVar1 + 0x10) + 1;
                    puVar10[0x10] = 0;
                    puVar10[1] = 0;
                    *puVar10 = 0;
                    puVar10[3] = 0;
                    puVar10[2] = 0;
                    local_18 = local_18 + 1;
                    puVar10[5] = 0;
                    puVar10[4] = 0;
                    puVar10[7] = 0;
                    puVar10[6] = 0;
                    puVar10[9] = 0;
                    puVar10[8] = 0;
                    puVar10[0xb] = 0;
                    puVar10[10] = 0;
                    puVar10[0xd] = 0;
                    puVar10[0xc] = 0;
                    puVar10[0xf] = 0;
                    puVar10[0xe] = 0;
                    uVar16 = *(uint *)(param_1 + 1);
                    lVar9 = *(long *)(lVar1 + 8);
                    uVar13 = *(uint *)(lVar1 + 0x10);
                    lVar3 = lVar9 + (ulong)uVar20 * 0x88;
                    *(undefined4 *)(lVar9 + lVar22) = 1;
                    *(int *)(lVar9 + lVar22 + 8) = iVar5;
                    *(long *)(lVar9 + lVar22 + 0x10) = (long)iVar19;
                    *(undefined4 *)(lVar3 + 0x18) = uVar6;
                    *(int *)(lVar3 + 0x28) = iVar5;
                    goto LAB_0017bf98;
                  }
                  break;
                }
LAB_0017bfe8:
                puVar10 = puVar10 + 9;
              } while (puVar10 != puVar12);
              if (uVar15 != 0) break;
              piVar14 = piVar14 + 4;
              uVar15 = 1;
            }
          }
LAB_0017bf98:
          uVar21 = (ulong)(uVar20 + 1);
        } while (uVar20 + 1 < uVar13);
      }
      uVar17 = uVar17 + 1;
      lVar18 = lVar18 + 0x48;
    } while (uVar17 < uVar16);
    bVar7 = local_18 != 0;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
    return bVar7;
  }
  return bVar7;
LAB_0017be34:
  piVar8 = piVar8 + 0x22;
  if (piVar11 == piVar8) goto LAB_0017bfe8;
  goto LAB_0017be40;
}

