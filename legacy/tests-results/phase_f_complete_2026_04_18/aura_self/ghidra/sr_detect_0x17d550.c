
undefined8 * sr_detect(long *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  void *__ptr;
  long lVar6;
  int *piVar7;
  int *piVar8;
  size_t sVar9;
  undefined8 *puVar10;
  uint uVar11;
  long lVar12;
  long lVar13;
  int iVar14;
  ulong uVar15;
  int iVar16;
  uint uVar17;
  undefined8 *puVar18;
  uint uVar19;
  int iVar20;
  uint uVar22;
  ulong uVar23;
  long lVar24;
  uint uVar25;
  int iVar26;
  void *__ptr_00;
  undefined8 uVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  ulong local_30;
  uint local_24;
  void *local_20;
  uint local_c;
  ulong uVar21;
  
  if ((param_1 != (long *)0x0) && (uVar3 = *(uint *)(param_1 + 1), uVar3 != 0)) {
    __ptr = calloc((ulong)uVar3,1);
    if (__ptr != (void *)0x0) {
      local_30 = 0;
      local_24 = 0;
      local_20 = (void *)0x0;
      local_c = 0;
      do {
        bVar5 = *(byte *)((long)__ptr + local_30);
        if ((bVar5 & 1) == 0) {
          uVar11 = (uint)local_30;
          lVar24 = *param_1;
          if (uVar11 < uVar3) {
            __ptr_00 = (void *)0x0;
            uVar23 = 0;
            uVar21 = 0;
            uVar25 = uVar11;
            uVar17 = 0xffffffff;
            iVar14 = -1;
            while( true ) {
              uVar15 = (ulong)uVar25;
              uVar19 = (uint)uVar21;
              uVar22 = (uint)uVar23;
              if ((((bVar5 & 1) != 0) || (lVar12 = lVar24 + (ulong)uVar25 * 0x50, lVar12 == 0)) ||
                 (uVar25 = *(uint *)(lVar12 + 0x10), uVar25 == 0)) break;
              lVar6 = *(long *)(lVar12 + 8);
              lVar13 = (ulong)(uVar25 - 1) * 0x90;
              lVar12 = lVar6 + lVar13;
              iVar20 = *(int *)(lVar6 + lVar13);
              if ((iVar20 != 0x17 || 1 < iVar20 - 0x17U && iVar20 != 0x1a) ||
                 (*(int *)(lVar12 + 0x48) == 0)) break;
              iVar20 = uVar25 - 2;
              if (iVar20 < 0) break;
              piVar7 = (int *)(lVar6 + (ulong)uVar25 * 0x90 + -0x120);
              while ((*(int *)(lVar12 + 0x18) != piVar7[2] || (*piVar7 != 0xb))) {
                iVar20 = iVar20 + -1;
                piVar7 = piVar7 + -0x24;
                if (iVar20 == -1) goto joined_r0x0017d9e0;
              }
              if ((uint)piVar7[0x12] < 2) break;
              iVar16 = piVar7[6];
              if (iVar20 != 0) {
                piVar8 = (int *)(lVar6 + (long)iVar20 * 0x90 + -0x90);
                do {
                  if (*piVar8 == 1) {
                    if (piVar7[10] == piVar8[2]) {
                      lVar6 = *(long *)(piVar8 + 4);
                      goto LAB_0017d888;
                    }
                    if (iVar16 == piVar8[2]) {
                      lVar6 = *(long *)(piVar8 + 4);
                      iVar16 = piVar7[10];
                      goto LAB_0017d888;
                    }
                  }
                  piVar8 = piVar8 + -0x24;
                } while (piVar8 != (int *)((long)iVar20 * 0x90 + (ulong)(iVar20 - 1) * -0x90 +
                                          lVar6 + -0x120));
              }
              lVar6 = *(long *)(piVar7 + 0xc);
              if ((lVar6 == 0) && (piVar7[0xb] != 3)) break;
LAB_0017d888:
              if ((iVar14 != -1) && (iVar16 != iVar14)) break;
              uVar2 = *(undefined4 *)(lVar12 + 100);
              uVar25 = *(uint *)(lVar12 + 0x68);
              if (uVar22 <= uVar19) {
                if (uVar22 == 0) {
                  sVar9 = 0x80;
                  uVar23 = 8;
                }
                else {
                  uVar23 = (ulong)(uVar22 << 1);
                  sVar9 = uVar23 << 4;
                }
                __ptr_00 = realloc(__ptr_00,sVar9);
                if (__ptr_00 == (void *)0x0) goto LAB_0017d768;
              }
              lVar12 = uVar21 * 0x10;
              *(undefined1 *)((long)__ptr + uVar15) = 1;
              uVar15 = (ulong)(uVar19 + 1);
              *(long *)((long)__ptr_00 + lVar12) = lVar6;
              *(undefined4 *)((long)__ptr_00 + lVar12 + 8) = uVar2;
              *(undefined2 *)((long)__ptr_00 + lVar12 + 0xc) = 0;
              uVar21 = uVar15;
              if (uVar3 <= uVar25) {
                if (uVar19 + 1 < 2) goto LAB_0017d9e4;
                goto LAB_0017d670;
              }
              bVar5 = *(byte *)((long)__ptr + (ulong)uVar25);
              uVar17 = uVar25;
              iVar14 = iVar16;
            }
joined_r0x0017d9e0:
            uVar15 = uVar21;
            if (uVar19 < 2) {
LAB_0017d9e4:
              free(__ptr_00);
              if ((int)uVar15 != 0) {
                *(undefined1 *)((long)__ptr + local_30) = 0;
              }
            }
            else {
              uVar25 = uVar17;
              iVar16 = iVar14;
              if (uVar17 < uVar3) {
                uVar1 = uVar19 + 1;
                if (uVar19 < uVar22) {
                  lVar12 = uVar21 * 0x10;
                  *(undefined8 *)((long)__ptr_00 + lVar12) = 0;
                  *(uint *)((long)__ptr_00 + lVar12 + 8) = uVar17;
                  *(undefined2 *)((long)__ptr_00 + lVar12 + 0xc) = 1;
                  uVar15 = (ulong)uVar1;
                  goto LAB_0017d670;
                }
                __ptr_00 = realloc(__ptr_00,(ulong)uVar1 << 4);
                if (__ptr_00 == (void *)0x0) goto LAB_0017d768;
                lVar12 = uVar21 * 0x10;
                *(undefined8 *)((long)__ptr_00 + lVar12) = 0;
                *(uint *)((long)__ptr_00 + lVar12 + 8) = uVar17;
                *(undefined2 *)((long)__ptr_00 + lVar12 + 0xc) = 1;
                uVar15 = (ulong)uVar1;
                if (1 < uVar1) goto LAB_0017d670;
                iVar20 = -1;
                iVar14 = 0;
LAB_0017d968:
                lVar24 = lVar24 + (ulong)uVar25 * 0x50;
                if ((lVar24 == 0) || (*(int *)(lVar24 + 0x10) == 0)) {
                  iVar26 = -1;
                }
                else {
                  iVar26 = -1;
                  lVar12 = (ulong)(*(int *)(lVar24 + 0x10) - 1) * 0x90;
                  iVar4 = *(int *)(*(long *)(lVar24 + 8) + lVar12);
                  if ((iVar4 - 0x17U < 2 || iVar4 == 0x1a) && iVar4 == 0x18) {
                    iVar26 = *(int *)(*(long *)(lVar24 + 8) + lVar12 + 100);
                  }
                }
              }
              else {
LAB_0017d670:
                iVar20 = (int)uVar21;
                iVar14 = (int)uVar15;
                piVar7 = (int *)((long)__ptr_00 + 8);
                do {
                  if ((((*(byte *)(piVar7 + 1) & 1) == 0) && ((*(byte *)(piVar7 + 5) & 1) == 0)) &&
                     (*piVar7 == piVar7[4])) {
                    *(undefined1 *)((long)piVar7 + 5) = 1;
                  }
                  piVar7 = piVar7 + 4;
                } while (piVar7 != (int *)((long)__ptr_00 + (ulong)(iVar14 - 2) * 0x10 + 0x18));
                iVar26 = -1;
                if (uVar25 < uVar3) goto LAB_0017d968;
              }
              piVar7 = calloc(1,0x28);
              if (piVar7 == (int *)0x0) {
                free(__ptr_00);
              }
              else {
                piVar7[6] = iVar26;
                piVar7[7] = uVar11;
                *piVar7 = iVar16;
                *(void **)(piVar7 + 2) = __ptr_00;
                piVar7[4] = iVar14;
                piVar7[5] = uVar25;
                piVar7[8] = iVar20;
                if (local_c <= local_24) {
                  if (local_c == 0) {
                    sVar9 = 0xa0;
                    local_c = 4;
                  }
                  else {
                    local_c = local_c << 1;
                    sVar9 = (ulong)local_c * 0x28;
                  }
                  local_20 = realloc(local_20,sVar9);
                  if (local_20 == (void *)0x0) {
                    free(__ptr_00);
                    free(piVar7);
                    local_20 = __ptr;
                    goto LAB_0017da68;
                  }
                }
                uVar28 = *(undefined8 *)(piVar7 + 2);
                uVar27 = *(undefined8 *)piVar7;
                uVar30 = *(undefined8 *)(piVar7 + 6);
                uVar29 = *(undefined8 *)(piVar7 + 4);
                puVar10 = (undefined8 *)((long)local_20 + (ulong)local_24 * 0x28);
                puVar10[4] = *(undefined8 *)(piVar7 + 8);
                puVar10[1] = uVar28;
                *puVar10 = uVar27;
                puVar10[3] = uVar30;
                puVar10[2] = uVar29;
                free(piVar7);
                local_24 = local_24 + 1;
              }
            }
          }
        }
LAB_0017d768:
        local_30 = local_30 + 1;
      } while (uVar3 != local_30);
      free(__ptr);
      if (local_24 != 0) {
        puVar10 = calloc(1,0x10);
        if (puVar10 != (undefined8 *)0x0) {
          *puVar10 = local_20;
          *(uint *)(puVar10 + 1) = local_24;
          return puVar10;
        }
        puVar10 = (undefined8 *)((long)local_20 + 8);
        do {
          puVar18 = puVar10 + 5;
          free((void *)*puVar10);
          puVar10 = puVar18;
        } while (puVar18 != (undefined8 *)((long)local_20 + 8) + (ulong)local_24 * 5);
      }
LAB_0017da68:
      free(local_20);
    }
  }
  return (undefined8 *)0x0;
}

