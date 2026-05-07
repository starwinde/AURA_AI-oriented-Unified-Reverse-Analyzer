
int FUN_0014cd8c(long *param_1)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  int *__s;
  undefined4 *puVar6;
  undefined1 *__ptr;
  long lVar7;
  uint *puVar8;
  int *piVar9;
  ulong *puVar10;
  void *pvVar12;
  void *__ptr_00;
  void *__ptr_01;
  ulong uVar13;
  int *piVar14;
  ulong uVar15;
  int iVar16;
  long lVar17;
  undefined8 *puVar18;
  ulong uVar19;
  long lVar20;
  uint uVar21;
  size_t sVar22;
  ulong uVar23;
  uint uVar24;
  long lVar25;
  ulong uVar26;
  ulong uVar27;
  ulong *puVar11;
  
  if (param_1 == (long *)0x0) {
    iVar5 = -4;
  }
  else {
    uVar2 = *(uint *)(param_1 + 1);
    if (uVar2 != 0) {
      if (uVar2 != 1) {
        uVar26 = (ulong)uVar2;
        lVar20 = *param_1;
        __s = calloc(uVar26,4);
        if (__s != (int *)0x0) {
          sVar22 = uVar26 * 4;
          memset(__s,0xff,sVar22);
          puVar6 = malloc(sVar22);
          __ptr = calloc(uVar26,1);
          if (puVar6 == (undefined4 *)0x0 || __ptr == (undefined1 *)0x0) {
            free(__s);
            free(puVar6);
            free(__ptr);
          }
          else {
            __memset_chk(__ptr,0,uVar26,uVar26);
            iVar5 = 1;
            lVar17 = 0;
            *__ptr = 1;
            *puVar6 = 0;
            do {
              lVar7 = lVar20 + (ulong)(uint)puVar6[lVar17] * 0x50;
              iVar16 = (int)lVar17;
              __s[(uint)puVar6[lVar17]] = iVar16;
              uVar24 = *(uint *)(lVar7 + 0x30);
              if (uVar24 != 0) {
                puVar8 = *(uint **)(lVar7 + 0x28);
                puVar1 = puVar8 + uVar24;
                do {
                  uVar24 = *puVar8;
                  puVar8 = puVar8 + 1;
                  if ((uVar24 < uVar2) && (__ptr[uVar24] == '\0')) {
                    puVar6[iVar5] = uVar24;
                    iVar5 = iVar5 + 1;
                    __ptr[uVar24] = 1;
                  }
                } while (puVar8 != puVar1);
              }
              lVar17 = lVar17 + 1;
            } while ((int)lVar17 < iVar5);
            iVar16 = iVar16 + 1;
            piVar9 = __s;
            do {
              if (*piVar9 < 0) {
                *piVar9 = iVar16;
                iVar16 = iVar16 + 1;
              }
              piVar9 = piVar9 + 1;
            } while (piVar9 != __s + uVar26);
            free(puVar6);
            free(__ptr);
            puVar6 = malloc(sVar22);
            if (puVar6 != (undefined4 *)0x0) {
              memset(puVar6,0xff,sVar22);
              *puVar6 = 0;
              do {
                lVar17 = 1;
                bVar4 = false;
                puVar18 = (undefined8 *)(lVar20 + 0x68);
                do {
                  while (*(uint *)(puVar18 + 1) == 0) {
LAB_0014cf34:
                    lVar17 = lVar17 + 1;
                    puVar18 = puVar18 + 10;
                    if (uVar2 <= (uint)lVar17) goto LAB_0014d028;
                  }
                  puVar8 = (uint *)*puVar18;
                  uVar26 = 0xffffffff;
                  puVar1 = puVar8 + *(uint *)(puVar18 + 1);
                  do {
                    while( true ) {
                      uVar15 = (ulong)*puVar8;
                      uVar27 = uVar26;
                      if (((puVar6[uVar15] != -1) && (uVar27 = uVar15, (uint)uVar26 != 0xffffffff))
                         && (uVar27 = uVar26, *puVar8 != (uint)uVar26)) break;
                      uVar26 = uVar27;
                      iVar16 = (int)uVar26;
                      puVar8 = puVar8 + 1;
                      if (puVar8 == puVar1) goto LAB_0014cffc;
                    }
                    iVar5 = __s[uVar26];
                    uVar27 = uVar15;
                    uVar23 = uVar26;
                    do {
                      iVar16 = __s[uVar15];
                      while (iVar5 < iVar16) {
                        uVar15 = (ulong)(uint)puVar6[uVar15];
                        uVar27 = uVar15;
                        iVar16 = __s[uVar15];
                      }
                      while (iVar16 < iVar5) {
                        uVar26 = (ulong)(uint)puVar6[uVar23];
                        uVar23 = uVar26;
                        iVar5 = __s[uVar26];
                      }
                      iVar16 = (int)uVar26;
                    } while ((int)uVar27 != iVar16);
                    puVar8 = puVar8 + 1;
                  } while (puVar8 != puVar1);
LAB_0014cffc:
                  if (iVar16 == -1) {
                    iVar16 = 0;
                  }
                  if (puVar6[lVar17] == iVar16) goto LAB_0014cf34;
                  puVar6[lVar17] = iVar16;
                  lVar17 = lVar17 + 1;
                  puVar18 = puVar18 + 10;
                  bVar4 = true;
                } while ((uint)lVar17 < uVar2);
LAB_0014d028:
              } while (bVar4);
              lVar17 = 1;
              do {
                if (puVar6[lVar17] == -1) {
                  puVar6[lVar17] = 0;
                }
                lVar17 = lVar17 + 1;
              } while ((uint)lVar17 < uVar2);
              lVar17 = 0;
              piVar9 = (int *)(lVar20 + 0x34);
              do {
                while (piVar14 = puVar6 + lVar17, *piVar14 == -1) {
                  *piVar9 = (int)lVar17;
                  lVar17 = lVar17 + 1;
                  piVar9 = piVar9 + 0x14;
                  if (uVar2 <= (uint)lVar17) goto LAB_0014d070;
                }
                lVar17 = lVar17 + 1;
                *piVar9 = *piVar14;
                piVar9 = piVar9 + 0x14;
              } while ((uint)lVar17 < uVar2);
LAB_0014d070:
              lVar17 = 0;
              uVar24 = 0;
              do {
                uVar24 = uVar24 + 1;
                free(*(void **)(lVar20 + lVar17 + 0x38));
                lVar20 = *param_1;
                lVar7 = lVar20 + lVar17;
                lVar17 = lVar17 + 0x50;
                *(undefined8 *)(lVar7 + 0x38) = 0;
                *(undefined4 *)(lVar7 + 0x40) = 0;
              } while (uVar24 < uVar2);
              lVar17 = 0;
              do {
                lVar20 = lVar20 + lVar17 * 0x50;
                uVar24 = *(uint *)(lVar20 + 0x20);
                if ((1 < uVar24) && (uVar3 = puVar6[lVar17], uVar3 < uVar2)) {
                  lVar7 = 0;
                  do {
                    uVar21 = *(uint *)(*(long *)(lVar20 + 0x18) + lVar7 * 4);
                    if (uVar21 < uVar2) {
                      if (uVar3 != uVar21 && uVar21 < uVar2) {
                        do {
                          lVar25 = *param_1 + (ulong)uVar21 * 0x50;
                          uVar24 = *(uint *)(lVar25 + 0x40);
                          piVar9 = *(int **)(lVar25 + 0x38);
                          if (uVar24 == 0) {
                            sVar22 = 4;
                          }
                          else {
                            piVar14 = piVar9;
                            do {
                              iVar5 = *piVar14;
                              piVar14 = piVar14 + 1;
                              if (iVar5 == (int)lVar17) goto LAB_0014d150;
                            } while (piVar14 != piVar9 + uVar24);
                            sVar22 = (ulong)(uVar24 + 1) << 2;
                          }
                          pvVar12 = realloc(piVar9,sVar22);
                          if (pvVar12 != (void *)0x0) {
                            uVar24 = *(uint *)(lVar25 + 0x40);
                            *(void **)(lVar25 + 0x38) = pvVar12;
                            *(uint *)(lVar25 + 0x40) = uVar24 + 1;
                            *(int *)((long)pvVar12 + (ulong)uVar24 * 4) = (int)lVar17;
                          }
LAB_0014d150:
                          uVar24 = puVar6[uVar21];
                        } while ((uVar21 != uVar24) &&
                                (uVar21 = uVar24,
                                (uVar3 != uVar24 && uVar24 <= uVar2) &&
                                (uVar3 == uVar24 || uVar2 != uVar24)));
                      }
                      uVar24 = *(uint *)(lVar20 + 0x20);
                    }
                    lVar7 = lVar7 + 1;
                  } while ((uint)lVar7 < uVar24);
                }
                lVar17 = lVar17 + 1;
                if (uVar2 <= (uint)lVar17) goto LAB_0014d1c0;
                lVar20 = *param_1;
              } while( true );
            }
            free(__s);
          }
        }
        return -2;
      }
      *(undefined4 *)(*param_1 + 0x34) = 0;
    }
    iVar5 = 0;
  }
  return iVar5;
LAB_0014d1c0:
  uVar2 = *(uint *)(param_1 + 1);
  if (1 < uVar2) {
    lVar20 = *param_1;
    uVar26 = (ulong)uVar2;
    uVar15 = 0;
    puVar10 = (ulong *)(lVar20 + 0x48);
    do {
      puVar11 = puVar10 + 10;
      uVar15 = uVar15 | *puVar10;
      puVar10 = puVar11;
    } while (puVar11 != (ulong *)(lVar20 + 0x48) + (ulong)uVar2 * 10);
    pvVar12 = malloc(uVar26 << 2);
    __ptr_00 = calloc(uVar26,1);
    __ptr_01 = calloc(uVar26,1);
    if ((pvVar12 == (void *)0x0 || __ptr_00 == (void *)0x0) || __ptr_01 == (void *)0x0) {
      free(pvVar12);
      free(__ptr_00);
      iVar5 = -2;
      free(__ptr_01);
      goto LAB_0014d278;
    }
    if (uVar15 == 0) {
      puVar18 = (undefined8 *)(lVar20 + 8);
      uVar15 = 0;
      iVar16 = 0;
      do {
        if (*(uint *)(puVar18 + 1) != 0) {
          piVar9 = (int *)*puVar18;
          piVar14 = piVar9 + (ulong)*(uint *)(puVar18 + 1) * 0x24;
          do {
            if ((*piVar9 != 0x1b) && (piVar9[2] != -1)) {
              if (*(char *)((long)__ptr_00 + uVar15) == '\0') {
                *(int *)((long)pvVar12 + (long)iVar16 * 4) = (int)uVar15;
                iVar16 = iVar16 + 1;
                *(undefined1 *)((long)__ptr_00 + uVar15) = 1;
              }
              break;
            }
            piVar9 = piVar9 + 0x24;
          } while (piVar9 != piVar14);
        }
        uVar15 = uVar15 + 1;
        puVar18 = puVar18 + 10;
      } while (uVar15 != uVar26);
      if (0 < iVar16) {
        lVar17 = 0;
        while( true ) {
          lVar20 = lVar20 + (ulong)*(uint *)((long)pvVar12 + lVar17 * 4) * 0x50;
          uVar24 = *(uint *)(lVar20 + 0x40);
          if (uVar24 != 0) {
            lVar7 = 0;
            do {
              uVar3 = *(uint *)(*(long *)(lVar20 + 0x38) + lVar7 * 4);
              if ((uVar3 < uVar2) && (*(char *)((long)__ptr_01 + (ulong)uVar3) == '\0')) {
                *(undefined1 *)((long)__ptr_01 + (ulong)uVar3) = 1;
                iVar5 = FUN_0014c084(param_1,uVar3);
                if (iVar5 != 0) goto LAB_0014d4f4;
                uVar24 = *(uint *)(lVar20 + 0x40);
                if (*(char *)((long)__ptr_00 + (ulong)uVar3) == '\0') {
                  *(uint *)((long)pvVar12 + (long)iVar16 * 4) = uVar3;
                  iVar16 = iVar16 + 1;
                  *(undefined1 *)((long)__ptr_00 + (ulong)uVar3) = 1;
                }
              }
              lVar7 = lVar7 + 1;
            } while ((uint)lVar7 < uVar24);
          }
          lVar17 = lVar17 + 1;
          if (iVar16 <= (int)lVar17) break;
          lVar20 = *param_1;
        }
      }
    }
    else {
      uVar27 = 0;
      do {
        uVar23 = 1L << (uVar27 & 0x3f);
        if ((uVar15 & uVar23) != 0) {
          __memset_chk(__ptr_00,0,uVar26,uVar26);
          __memset_chk(__ptr_01,0,uVar26,uVar26);
          lVar20 = *param_1;
          iVar16 = 0;
          uVar13 = 0;
          puVar10 = (ulong *)(lVar20 + 0x48);
          do {
            uVar19 = *puVar10;
            puVar10 = puVar10 + 10;
            if ((uVar23 & uVar19) != 0) {
              *(int *)((long)pvVar12 + (long)iVar16 * 4) = (int)uVar13;
              iVar16 = iVar16 + 1;
              *(undefined1 *)((long)__ptr_00 + uVar13) = 1;
            }
            uVar13 = uVar13 + 1;
          } while (uVar13 != uVar26);
          if (0 < iVar16) {
            lVar17 = 0;
            while( true ) {
              lVar20 = lVar20 + (ulong)*(uint *)((long)pvVar12 + lVar17 * 4) * 0x50;
              uVar24 = *(uint *)(lVar20 + 0x40);
              if (uVar24 != 0) {
                lVar7 = 0;
                do {
                  uVar3 = *(uint *)(*(long *)(lVar20 + 0x38) + lVar7 * 4);
                  if ((uVar3 < uVar2) && (*(char *)((long)__ptr_01 + (ulong)uVar3) == '\0')) {
                    *(undefined1 *)((long)__ptr_01 + (ulong)uVar3) = 1;
                    iVar5 = FUN_0014c084(param_1,uVar3);
                    if (iVar5 != 0) goto LAB_0014d4f4;
                    uVar24 = *(uint *)(lVar20 + 0x40);
                    if (*(char *)((long)__ptr_00 + (ulong)uVar3) == '\0') {
                      *(uint *)((long)pvVar12 + (long)iVar16 * 4) = uVar3;
                      iVar16 = iVar16 + 1;
                      *(undefined1 *)((long)__ptr_00 + (ulong)uVar3) = 1;
                    }
                  }
                  lVar7 = lVar7 + 1;
                } while ((uint)lVar7 < uVar24);
              }
              lVar17 = lVar17 + 1;
              if (iVar16 <= (int)lVar17) break;
              lVar20 = *param_1;
            }
          }
        }
        uVar24 = (int)uVar27 + 1;
        uVar27 = (ulong)uVar24;
      } while (uVar24 != 0x10);
    }
    free(pvVar12);
    free(__ptr_00);
    free(__ptr_01);
  }
  iVar5 = 0;
  goto LAB_0014d278;
LAB_0014d4f4:
  free(pvVar12);
  free(__ptr_00);
  free(__ptr_01);
LAB_0014d278:
  free(__s);
  free(puVar6);
  return iVar5;
}

