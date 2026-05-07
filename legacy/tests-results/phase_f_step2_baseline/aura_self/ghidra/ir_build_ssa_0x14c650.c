
int ir_build_ssa(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined8 uVar4;
  int *__s;
  undefined4 *puVar5;
  undefined1 *__ptr;
  long lVar6;
  uint *puVar7;
  int *piVar8;
  void *pvVar9;
  void *__ptr_00;
  void *__ptr_01;
  void *pvVar10;
  void *pvVar11;
  int *piVar12;
  int iVar13;
  ulong uVar14;
  ulong uVar15;
  int iVar16;
  long lVar17;
  undefined8 *puVar18;
  ulong uVar19;
  long lVar20;
  long lVar21;
  uint uVar22;
  size_t sVar23;
  uint uVar24;
  long lVar25;
  undefined4 *puVar26;
  ulong uVar27;
  long local_28;
  int local_20;
  int local_1c;
  int local_10;
  
  if (param_1 == (long *)0x0) {
    local_1c = -4;
  }
  else {
    uVar2 = *(uint *)(param_1 + 1);
    if (uVar2 != 0) {
      if (uVar2 != 1) {
        uVar27 = (ulong)uVar2;
        lVar21 = *param_1;
        __s = calloc(uVar27,4);
        if (__s != (int *)0x0) {
          sVar23 = uVar27 * 4;
          memset(__s,0xff,sVar23);
          puVar5 = malloc(sVar23);
          __ptr = calloc(uVar27,1);
          if (puVar5 == (undefined4 *)0x0 || __ptr == (undefined1 *)0x0) {
            free(__s);
            free(puVar5);
            free(__ptr);
          }
          else {
            __memset_chk(__ptr,0,uVar27,uVar27);
            iVar13 = 1;
            lVar17 = 0;
            *__ptr = 1;
            *puVar5 = 0;
            do {
              lVar6 = lVar21 + (ulong)(uint)puVar5[lVar17] * 0x48;
              iVar16 = (int)lVar17;
              __s[(uint)puVar5[lVar17]] = iVar16;
              uVar24 = *(uint *)(lVar6 + 0x30);
              if (uVar24 != 0) {
                puVar7 = *(uint **)(lVar6 + 0x28);
                puVar1 = puVar7 + uVar24;
                do {
                  uVar24 = *puVar7;
                  puVar7 = puVar7 + 1;
                  if ((uVar24 < uVar2) && (__ptr[uVar24] == '\0')) {
                    puVar5[iVar13] = uVar24;
                    iVar13 = iVar13 + 1;
                    __ptr[uVar24] = 1;
                  }
                } while (puVar1 != puVar7);
              }
              lVar17 = lVar17 + 1;
            } while ((int)lVar17 < iVar13);
            iVar16 = iVar16 + 1;
            piVar8 = __s;
            do {
              if (*piVar8 < 0) {
                *piVar8 = iVar16;
                iVar16 = iVar16 + 1;
              }
              piVar8 = piVar8 + 1;
            } while (__s + uVar27 != piVar8);
            free(puVar5);
            free(__ptr);
            puVar5 = malloc(sVar23);
            if (puVar5 != (undefined4 *)0x0) {
              memset(puVar5,0xff,sVar23);
              *puVar5 = 0;
              do {
                lVar17 = 1;
                local_1c = 0;
                puVar18 = (undefined8 *)(lVar21 + 0x60);
                do {
                  while (*(uint *)(puVar18 + 1) == 0) {
LAB_0014c7f4:
                    lVar17 = lVar17 + 1;
                    puVar18 = puVar18 + 9;
                    if (uVar2 <= (uint)lVar17) goto LAB_0014c8ec;
                  }
                  puVar7 = (uint *)*puVar18;
                  uVar27 = 0xffffffff;
                  puVar1 = puVar7 + *(uint *)(puVar18 + 1);
                  do {
                    while( true ) {
                      uVar14 = (ulong)*puVar7;
                      uVar15 = uVar27;
                      if (((puVar5[uVar14] != -1) && (uVar15 = uVar14, (uint)uVar27 != 0xffffffff))
                         && (uVar15 = uVar27, *puVar7 != (uint)uVar27)) break;
                      uVar27 = uVar15;
                      iVar16 = (int)uVar27;
                      puVar7 = puVar7 + 1;
                      if (puVar1 == puVar7) goto LAB_0014c8bc;
                    }
                    iVar13 = __s[uVar27];
                    uVar15 = uVar14;
                    uVar19 = uVar27;
                    do {
                      iVar16 = __s[uVar14];
                      while (iVar13 < iVar16) {
                        uVar14 = (ulong)(uint)puVar5[uVar14];
                        uVar15 = uVar14;
                        iVar16 = __s[uVar14];
                      }
                      while (iVar16 < iVar13) {
                        uVar27 = (ulong)(uint)puVar5[uVar19];
                        uVar19 = uVar27;
                        iVar13 = __s[uVar27];
                      }
                      iVar16 = (int)uVar27;
                    } while ((int)uVar15 != iVar16);
                    puVar7 = puVar7 + 1;
                  } while (puVar1 != puVar7);
LAB_0014c8bc:
                  if (iVar16 == -1) {
                    iVar16 = 0;
                  }
                  if (puVar5[lVar17] == iVar16) goto LAB_0014c7f4;
                  puVar5[lVar17] = iVar16;
                  lVar17 = lVar17 + 1;
                  local_1c = 1;
                  puVar18 = puVar18 + 9;
                } while ((uint)lVar17 < uVar2);
LAB_0014c8ec:
              } while (local_1c != 0);
              lVar17 = 1;
              do {
                if (puVar5[lVar17] == -1) {
                  puVar5[lVar17] = 0;
                }
                lVar17 = lVar17 + 1;
              } while ((uint)lVar17 < uVar2);
              lVar17 = 0;
              piVar8 = (int *)(lVar21 + 0x34);
              do {
                while (piVar12 = puVar5 + lVar17, *piVar12 == -1) {
                  *piVar8 = (int)lVar17;
                  lVar17 = lVar17 + 1;
                  piVar8 = piVar8 + 0x12;
                  if (uVar2 <= (uint)lVar17) goto LAB_0014c938;
                }
                lVar17 = lVar17 + 1;
                *piVar8 = *piVar12;
                piVar8 = piVar8 + 0x12;
              } while ((uint)lVar17 < uVar2);
LAB_0014c938:
              lVar17 = 0;
              uVar24 = 0;
              do {
                uVar24 = uVar24 + 1;
                free(*(void **)(lVar21 + lVar17 + 0x38));
                lVar21 = *param_1;
                lVar6 = lVar21 + lVar17;
                lVar17 = lVar17 + 0x48;
                *(undefined8 *)(lVar6 + 0x38) = 0;
                *(undefined4 *)(lVar6 + 0x40) = 0;
              } while (uVar24 < uVar2);
              lVar17 = 0;
              do {
                lVar21 = lVar21 + lVar17 * 0x48;
                uVar24 = *(uint *)(lVar21 + 0x20);
                if ((1 < uVar24) && (uVar3 = puVar5[lVar17], uVar3 < uVar2)) {
                  lVar6 = 0;
                  do {
                    uVar22 = *(uint *)(*(long *)(lVar21 + 0x18) + lVar6 * 4);
                    if (uVar22 < uVar2) {
                      if (uVar3 != uVar22 && uVar22 < uVar2) {
                        do {
                          lVar25 = *param_1 + (ulong)uVar22 * 0x48;
                          uVar24 = *(uint *)(lVar25 + 0x40);
                          piVar8 = *(int **)(lVar25 + 0x38);
                          if (uVar24 == 0) {
                            sVar23 = 4;
                          }
                          else {
                            piVar12 = piVar8;
                            do {
                              iVar13 = *piVar12;
                              piVar12 = piVar12 + 1;
                              if (iVar13 == (int)lVar17) goto LAB_0014ca18;
                            } while (piVar8 + uVar24 != piVar12);
                            sVar23 = (ulong)(uVar24 + 1) << 2;
                          }
                          pvVar9 = realloc(piVar8,sVar23);
                          if (pvVar9 != (void *)0x0) {
                            uVar24 = *(uint *)(lVar25 + 0x40);
                            *(void **)(lVar25 + 0x38) = pvVar9;
                            *(uint *)(lVar25 + 0x40) = uVar24 + 1;
                            *(int *)((long)pvVar9 + (ulong)uVar24 * 4) = (int)lVar17;
                          }
LAB_0014ca18:
                          uVar24 = puVar5[uVar22];
                        } while ((uVar22 != uVar24) &&
                                (uVar22 = uVar24,
                                (uVar3 != uVar24 && uVar24 <= uVar2) &&
                                (uVar3 == uVar24 || uVar2 != uVar24)));
                      }
                      uVar24 = *(uint *)(lVar21 + 0x20);
                    }
                    lVar6 = lVar6 + 1;
                  } while ((uint)lVar6 < uVar24);
                }
                uVar4 = DAT_0020a3e0;
                lVar17 = lVar17 + 1;
                if (uVar2 <= (uint)lVar17) goto LAB_0014ca88;
                lVar21 = *param_1;
              } while( true );
            }
            free(__s);
          }
        }
        return -2;
      }
      *(undefined4 *)(*param_1 + 0x34) = 0;
    }
    local_1c = 0;
  }
  return local_1c;
LAB_0014ca88:
  uVar2 = *(uint *)(param_1 + 1);
  uVar27 = (ulong)uVar2;
  if (uVar2 != 0) {
    local_10 = 0x10;
    do {
      pvVar9 = malloc(uVar27 << 2);
      __ptr_00 = calloc(uVar27,1);
      if (pvVar9 == (void *)0x0 || __ptr_00 == (void *)0x0) {
LAB_0014ce4c:
        free(pvVar9);
        free(__ptr_00);
LAB_0014cdfc:
        local_1c = -2;
        break;
      }
      lVar21 = *param_1;
      if (uVar2 == 1) {
        free(pvVar9);
        free(__ptr_00);
      }
      else {
        __memset_chk(__ptr_00,0,uVar27,uVar27);
        local_20 = 0;
        puVar18 = (undefined8 *)(lVar21 + 8);
        uVar14 = 0;
        do {
          if (*(uint *)(puVar18 + 1) != 0) {
            piVar8 = (int *)*puVar18;
            piVar12 = piVar8 + (ulong)*(uint *)(puVar18 + 1) * 0x22;
            do {
              if ((*piVar8 != 0x1b) && (piVar8[2] != -1)) {
                if (*(char *)((long)__ptr_00 + uVar14) == '\0') {
                  *(int *)((long)pvVar9 + (long)local_20 * 4) = (int)uVar14;
                  local_20 = local_20 + 1;
                  *(undefined1 *)((long)__ptr_00 + uVar14) = 1;
                }
                break;
              }
              piVar8 = piVar8 + 0x22;
            } while (piVar8 != piVar12);
          }
          uVar14 = uVar14 + 1;
          puVar18 = puVar18 + 9;
        } while (uVar27 != uVar14);
        __ptr_01 = calloc(uVar27,1);
        if (__ptr_01 == (void *)0x0) goto LAB_0014ce4c;
        local_28 = 0;
        if (0 < local_20) {
          do {
            lVar21 = lVar21 + (ulong)*(uint *)((long)pvVar9 + local_28 * 4) * 0x48;
            uVar24 = *(uint *)(lVar21 + 0x40);
            if (uVar24 != 0) {
              lVar17 = 0;
              do {
                while (uVar3 = *(uint *)(*(long *)(lVar21 + 0x38) + lVar17 * 4),
                      *(char *)((long)__ptr_01 + (ulong)uVar3) != '\0') {
LAB_0014cb98:
                  lVar17 = lVar17 + 1;
                  if (uVar24 <= (uint)lVar17) goto LAB_0014cd1c;
                }
                lVar6 = *param_1;
                *(undefined1 *)((long)__ptr_01 + (ulong)uVar3) = 1;
                lVar6 = lVar6 + (ulong)uVar3 * 0x48;
                uVar14 = (ulong)(*(int *)(lVar6 + 0x10) + 1) * 0x88;
                pvVar10 = realloc(*(void **)(lVar6 + 8),uVar14);
                if (pvVar10 == (void *)0x0) {
LAB_0014cde4:
                  free(pvVar9);
                  free(__ptr_00);
                  free(__ptr_01);
                  goto LAB_0014cdfc;
                }
                if (uVar14 < 0x88) {
                  uVar14 = 0x88;
                }
                *(uint *)(lVar6 + 0x14) = *(uint *)(lVar6 + 0x10) + 1;
                *(void **)(lVar6 + 8) = pvVar10;
                __memmove_chk((long)pvVar10 + 0x88,pvVar10,(ulong)*(uint *)(lVar6 + 0x10) * 0x88,
                              uVar14 - 0x88);
                puVar26 = *(undefined4 **)(lVar6 + 8);
                *(int *)(lVar6 + 0x10) = *(int *)(lVar6 + 0x10) + 1;
                puVar26[0x21] = 0;
                *(undefined8 *)(puVar26 + 3) = 0;
                *(undefined8 *)(puVar26 + 1) = 0;
                *(undefined8 *)(puVar26 + 7) = 0;
                *(undefined8 *)(puVar26 + 5) = 0;
                *(undefined8 *)(puVar26 + 0xb) = 0;
                *(undefined8 *)(puVar26 + 9) = 0;
                *(undefined8 *)(puVar26 + 0xf) = 0;
                *(undefined8 *)(puVar26 + 0xd) = 0;
                *(undefined8 *)(puVar26 + 0x13) = 0;
                *(undefined8 *)(puVar26 + 0x11) = 0;
                *(undefined8 *)(puVar26 + 0x17) = 0;
                *(undefined8 *)(puVar26 + 0x15) = 0;
                *(undefined8 *)(puVar26 + 0x1b) = 0;
                *(undefined8 *)(puVar26 + 0x19) = 0;
                *(undefined8 *)(puVar26 + 0x1f) = 0;
                *(undefined8 *)(puVar26 + 0x1d) = 0;
                lVar25 = param_1[2];
                uVar24 = *(uint *)(lVar6 + 0x20);
                *puVar26 = 0x1b;
                *(int *)(param_1 + 2) = (int)lVar25 + 1;
                puVar26[2] = (int)lVar25;
                puVar26[3] = 4;
                puVar26[0x18] = uVar24;
                pvVar10 = calloc((ulong)uVar24,0x10);
                *(void **)(puVar26 + 0x14) = pvVar10;
                pvVar11 = calloc((ulong)uVar24,4);
                *(void **)(puVar26 + 0x16) = pvVar11;
                if (pvVar11 == (void *)0x0 || pvVar10 == (void *)0x0) goto LAB_0014cde4;
                if (uVar24 != 0) {
                  lVar20 = *(long *)(lVar6 + 0x18);
                  lVar25 = 0;
                  do {
                    *(undefined8 *)((long)pvVar10 + lVar25 * 0x10) = uVar4;
                    *(undefined4 *)((long)pvVar11 + lVar25 * 4) =
                         *(undefined4 *)(lVar20 + lVar25 * 4);
                    lVar25 = lVar25 + 1;
                  } while ((uint)lVar25 < *(uint *)(lVar6 + 0x20));
                }
                if (*(char *)((long)__ptr_00 + (ulong)uVar3) != '\0') {
                  uVar24 = *(uint *)(lVar21 + 0x40);
                  goto LAB_0014cb98;
                }
                lVar17 = lVar17 + 1;
                uVar24 = *(uint *)(lVar21 + 0x40);
                *(uint *)((long)pvVar9 + (long)local_20 * 4) = uVar3;
                local_20 = local_20 + 1;
                *(undefined1 *)((long)__ptr_00 + (ulong)uVar3) = 1;
              } while ((uint)lVar17 < uVar24);
            }
LAB_0014cd1c:
            local_28 = local_28 + 1;
            if (local_20 <= (int)local_28) break;
            lVar21 = *param_1;
          } while( true );
        }
        free(pvVar9);
        free(__ptr_00);
        free(__ptr_01);
      }
      local_10 = local_10 + -1;
    } while (local_10 != 0);
  }
  free(__s);
  free(puVar5);
  return local_1c;
}

