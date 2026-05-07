
/* WARNING: Type propagation algorithm not settling */

undefined8 * loop_detect(long *param_1)

{
  size_t __nmemb;
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  void *pvVar5;
  uint *__ptr;
  byte *__ptr_00;
  undefined8 *puVar6;
  uint *puVar7;
  void *pvVar8;
  uint uVar9;
  uint *puVar10;
  long lVar11;
  int *piVar12;
  uint *puVar13;
  byte *pbVar14;
  ulong uVar16;
  int *piVar17;
  undefined8 *puVar18;
  size_t sVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  int *piVar23;
  int *piVar24;
  undefined1 uVar25;
  int *piVar26;
  long lVar27;
  uint uVar28;
  long lVar29;
  undefined8 *puVar30;
  uint uVar31;
  uint uVar32;
  ulong uVar33;
  ulong uVar34;
  size_t sVar35;
  uint uVar36;
  uint uVar37;
  uint *puVar38;
  uint local_f0 [2];
  void *local_e8;
  undefined8 local_e0;
  ulong uStack_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  uint *local_b8;
  ulong uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 local_98;
  undefined8 local_90;
  uint uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  int local_78;
  uint local_74;
  int iStack_70;
  undefined4 local_6c;
  long local_68;
  byte *pbVar15;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 != (long *)0x0) && (*(uint *)(param_1 + 1) != 0)) &&
     (pvVar5 = calloc((ulong)*(uint *)(param_1 + 1),4), pvVar5 != (void *)0x0)) {
    local_f0[0] = 0;
    local_f0[1] = 0;
    local_e8 = (void *)0x0;
    dfs_find_back_edges(param_1,0,pvVar5,&local_e8,local_f0,local_f0 + 1);
    free(pvVar5);
    uVar37 = local_f0[0];
    if (local_f0[0] != 0) {
      __ptr = calloc((ulong)local_f0[0],0x60);
      if (__ptr == (uint *)0x0) {
        puVar6 = (undefined8 *)0x0;
        free(local_e8);
        goto LAB_0017bb84;
      }
      lVar29 = 0;
      uVar36 = 0;
      pvVar5 = local_e8;
      do {
        uVar32 = *(uint *)((long)pvVar5 + lVar29 * 8);
        uVar9 = *(uint *)((long)pvVar5 + lVar29 * 8 + 4);
        if (uVar36 != 0) {
          puVar7 = __ptr;
LAB_0017b294:
          if (*puVar7 != uVar9) goto LAB_0017b288;
          local_b8 = (uint *)((ulong)local_b8 & 0xffffffff00000000);
          local_90 = (uint *)0x0;
          uVar31 = *(uint *)(param_1 + 1);
          uVar33 = (ulong)uVar31;
          compute_loop_body_isra_0(*param_1,uVar33,uVar9,uVar32,&local_90,&local_b8);
          puVar38 = local_90;
          if (local_90 != (uint *)0x0) {
            __ptr_00 = calloc(uVar33,1);
            if (__ptr_00 != (byte *)0x0) {
              if (puVar7[4] != 0) {
                puVar10 = *(uint **)(puVar7 + 2);
                puVar13 = puVar10 + puVar7[4];
                do {
                  if (*puVar10 < uVar31) {
                    __ptr_00[*puVar10] = 1;
                  }
                  puVar10 = puVar10 + 1;
                } while (puVar10 != puVar13);
              }
              puVar13 = puVar38;
              if ((int)local_b8 != 0) {
                do {
                  if (*puVar13 < uVar31) {
                    __ptr_00[*puVar13] = 1;
                  }
                  puVar13 = puVar13 + 1;
                } while (puVar13 != puVar38 + ((ulong)local_b8 & 0xffffffff));
              }
              if (uVar31 == 0) {
                pvVar5 = malloc(0);
                uVar37 = 0;
                if (pvVar5 != (void *)0x0) goto LAB_0017b3ac;
              }
              else {
                uVar34 = 0;
                pbVar15 = __ptr_00;
                do {
                  pbVar14 = pbVar15 + 1;
                  uVar37 = (int)uVar34 + (*pbVar15 & 1);
                  uVar34 = (ulong)uVar37;
                  pbVar15 = pbVar14;
                } while (__ptr_00 + uVar33 != pbVar14);
                pvVar5 = malloc(uVar34 << 2);
                if (pvVar5 != (void *)0x0) {
                  uVar34 = 0;
                  uVar16 = 0;
                  do {
                    if ((__ptr_00[uVar34] & 1) != 0) {
                      *(int *)((long)pvVar5 + uVar16 * 4) = (int)uVar34;
                      uVar16 = (ulong)((int)uVar16 + 1);
                    }
                    uVar34 = uVar34 + 1;
                  } while (uVar33 != uVar34);
LAB_0017b3ac:
                  free(*(void **)(puVar7 + 2));
                  *(void **)(puVar7 + 2) = pvVar5;
                  puVar7[4] = uVar37;
                }
              }
              free(__ptr_00);
            }
            free(puVar38);
            pvVar5 = local_e8;
            uVar37 = local_f0[0];
          }
          goto LAB_0017b3d4;
        }
LAB_0017b4f4:
        uVar33 = (ulong)uVar36;
        lVar11 = param_1[1];
        lVar27 = *param_1;
        uVar36 = uVar36 + 1;
        __ptr[uVar33 * 0x18] = uVar9;
        __ptr[uVar33 * 0x18 + 1] = uVar32;
        compute_loop_body_isra_0
                  (lVar27,(int)lVar11,uVar9,uVar32,__ptr + uVar33 * 0x18 + 2,
                   __ptr + uVar33 * 0x18 + 4);
LAB_0017b3d4:
        lVar29 = lVar29 + 1;
      } while ((uint)lVar29 < uVar37);
      free(pvVar5);
      if (uVar36 != 0) {
        uVar37 = *(uint *)(param_1 + 1);
        uVar33 = (ulong)uVar36;
        lVar29 = *param_1;
        uVar34 = (ulong)uVar37;
        puVar7 = __ptr;
        do {
          uVar9 = puVar7[4];
          puVar38 = *(uint **)(puVar7 + 2);
          pvVar5 = calloc(uVar34,1);
          if (pvVar5 == (void *)0x0) {
            uVar32 = 0xffffffff;
          }
          else {
            if (uVar9 == 0) {
              uVar31 = 0xffffffff;
            }
            else {
              puVar13 = puVar38;
              do {
                if (*puVar13 < uVar37) {
                  *(undefined1 *)((long)pvVar5 + (ulong)*puVar13) = 1;
                }
                puVar13 = puVar13 + 1;
              } while (puVar38 + uVar9 != puVar13);
              uVar16 = 0;
              uVar31 = 0xffffffff;
              do {
                uVar21 = puVar38[uVar16];
                if (uVar21 < uVar37) {
                  lVar11 = lVar29 + (ulong)uVar21 * 0x50;
                  uVar32 = *(uint *)(lVar11 + 0x30);
                  if (uVar32 != 0) {
                    puVar10 = *(uint **)(lVar11 + 0x28);
                    puVar13 = puVar10 + uVar32;
                    do {
                      uVar32 = *puVar10;
                      if ((uVar32 < uVar37) && ((*(byte *)((long)pvVar5 + (ulong)uVar32) & 1) == 0))
                      {
                        if (uVar31 == 0xffffffff) {
                          uVar31 = uVar32;
                        }
                        if (uVar21 == *puVar38) {
                          free(pvVar5);
                          goto LAB_0017b528;
                        }
                      }
                      puVar10 = puVar10 + 1;
                    } while (puVar13 != puVar10);
                  }
                }
                uVar16 = uVar16 + 1;
              } while (uVar9 != uVar16);
            }
            free(pvVar5);
            uVar32 = uVar31;
          }
LAB_0017b528:
          puVar7[5] = uVar32;
          lVar11 = lVar29 + (ulong)*puVar7 * 0x50;
          lVar27 = lVar29 + (ulong)puVar7[1] * 0x50;
          uVar32 = *(uint *)(lVar11 + 0x10);
          iVar4 = *(int *)(lVar27 + 0x10);
          uVar31 = uVar32 - 1;
          iVar20 = iVar4 + -1;
          if ((int)uVar31 < 0) {
            if (0 < iVar4) {
              piVar26 = (int *)0x0;
              goto LAB_0017b5a4;
            }
LAB_0017b5f4:
            uVar25 = 0;
            iVar4 = 0;
            uVar31 = 0;
            iVar20 = 0;
            local_d0 = 0;
            uVar21 = 0;
            iVar22 = 0;
            uVar32 = 0;
            uVar9 = 0;
          }
          else {
            piVar23 = *(int **)(lVar11 + 8);
            piVar26 = piVar23 + (long)(int)uVar31 * 0x22;
            do {
              iVar4 = *piVar26;
              if (iVar4 - 0x17U < 2 || iVar4 == 0x1a) {
                if (-1 < iVar20) goto LAB_0017b5a4;
                piVar12 = (int *)0x0;
                if (iVar4 == 0x17) goto LAB_0017b728;
                goto LAB_0017b5e8;
              }
              piVar26 = piVar26 + -0x22;
            } while (piVar26 != piVar23 + ((ulong)uVar32 - (ulong)uVar31) * 0x22 + -0x44);
            piVar26 = (int *)0x0;
            if (iVar20 < 0) goto LAB_0017b5f4;
LAB_0017b5a4:
            piVar12 = (int *)(*(long *)(lVar27 + 8) + (long)iVar20 * 0x88);
            do {
              if (*piVar12 - 0x17U < 2 || *piVar12 == 0x1a) goto LAB_0017b5d8;
              iVar20 = iVar20 + -1;
              piVar12 = piVar12 + -0x22;
            } while (iVar20 != -1);
            piVar12 = (int *)0x0;
LAB_0017b5d8:
            if (piVar26 == (int *)0x0) goto LAB_0017b5f4;
            iVar4 = *piVar26;
            if (iVar4 == 0x17) {
              if (-1 < (int)uVar31) {
                piVar23 = *(int **)(lVar11 + 8);
LAB_0017b728:
                uStack_84 = 0;
                piVar26 = piVar23 + (long)(int)uVar31 * 0x22;
                do {
                  iVar4 = *piVar26;
                  if (iVar4 - 0x17U < 2 || iVar4 == 0x1a) {
                    if (((iVar4 == 0x17) && (piVar26[0x12] != 0)) && (uVar37 != 0)) {
                      puVar6 = (undefined8 *)(lVar29 + 8);
                      puVar18 = puVar6;
                      do {
                        if (*(uint *)(puVar18 + 1) != 0) {
                          piVar12 = (int *)*puVar18;
                          piVar17 = piVar12 + (ulong)*(uint *)(puVar18 + 1) * 0x22;
                          do {
                            if (piVar26[6] == piVar12[2]) {
                              iVar4 = *piVar12;
                              if (((1 < iVar4 - 0xdU && iVar4 != 0x11) && (9 < iVar4 - 0xbU)) ||
                                 ((uint)piVar12[0x12] < 2)) goto LAB_0017b998;
                              uVar31 = piVar12[6];
                              piVar26 = piVar23 + (ulong)uVar32 * 0x22;
                              goto LAB_0017b810;
                            }
                            piVar12 = piVar12 + 0x22;
                          } while (piVar12 != piVar17);
                        }
                        puVar18 = puVar18 + 10;
                      } while (puVar6 + (ulong)uVar37 * 10 != puVar18);
                    }
                    break;
                  }
                  piVar26 = piVar26 + -0x22;
                } while (piVar26 != piVar23 + ((ulong)uVar32 - (ulong)uVar31) * 0x22 + -0x44);
              }
LAB_0017b998:
              iStack_70 = 0;
              local_74 = 0;
              local_78 = 0;
              uStack_7c = 0;
              uStack_80 = 0;
              uStack_84 = 0;
              local_6c = 0;
              uVar25 = 0;
              iVar4 = 0;
              uVar31 = 0;
              iVar20 = 0;
              local_d0 = 0;
              uVar21 = 0;
              iVar22 = 0;
              uVar32 = 0;
              uVar9 = 1;
            }
            else {
LAB_0017b5e8:
              if (piVar12 == (int *)0x0 || iVar4 != 0x18) goto LAB_0017b5f4;
              uVar25 = 0;
              iVar4 = 0;
              uVar31 = 0;
              iVar20 = 0;
              local_d0 = 0;
              uVar21 = 0;
              iVar22 = 0;
              uVar9 = (uint)(*piVar12 == 0x17) << 1;
              uVar32 = 0;
            }
          }
LAB_0017b618:
          local_e0 = CONCAT44(iVar22,uVar32);
          uStack_d8 = (ulong)uVar21;
          puVar38 = puVar7 + 0x18;
          local_c8 = CONCAT44(uVar31,iVar20);
          puVar7[6] = uVar9;
          local_c0 = (ulong)CONCAT14(uVar25,iVar4);
          *(ulong *)(puVar7 + 10) = uStack_d8;
          *(undefined8 *)(puVar7 + 8) = local_e0;
          *(undefined8 *)(puVar7 + 0xe) = local_c8;
          *(undefined8 *)(puVar7 + 0xc) = local_d0;
          *(ulong *)(puVar7 + 0x10) = local_c0;
          puVar7 = puVar38;
        } while (__ptr + uVar33 * 0x18 != puVar38);
        if ((uVar36 != 1) && (puVar6 = malloc((ulong)uVar36 << 3), puVar6 != (undefined8 *)0x0)) {
          puVar7 = __ptr + 2;
          __nmemb = 0;
          puVar38 = puVar7;
          do {
            sVar35 = __nmemb;
            pvVar5 = calloc(uVar34,1);
            puVar6[sVar35] = pvVar5;
            if (pvVar5 == (void *)0x0) {
              puVar18 = puVar6;
              if ((int)sVar35 != 0) {
                do {
                  puVar30 = puVar18 + 1;
                  free((void *)*puVar18);
                  puVar18 = puVar30;
                } while (puVar30 != puVar6 + sVar35);
              }
              goto LAB_0017bab4;
            }
            if (puVar38[2] != 0) {
              puVar10 = *(uint **)puVar38;
              puVar13 = puVar10 + puVar38[2];
              do {
                if (*puVar10 < uVar37) {
                  *(undefined1 *)((long)pvVar5 + (ulong)*puVar10) = 1;
                }
                puVar10 = puVar10 + 1;
              } while (puVar10 != puVar13);
            }
            __nmemb = sVar35 + 1;
            puVar38 = puVar38 + 0x18;
          } while (uVar36 != __nmemb);
          uVar9 = 0;
LAB_0017bbc4:
          uVar31 = 0xffffffff;
          uVar32 = 0xffffffff;
          sVar19 = 0;
          puVar38 = __ptr + 4;
          do {
            uVar21 = uVar32;
            uVar28 = uVar31;
            if ((uint)sVar19 != uVar9) {
              uVar1 = *puVar38;
              uVar2 = puVar7[2];
              if (uVar2 < uVar1) {
                if (uVar2 != 0) {
                  puVar10 = *(uint **)puVar7;
                  puVar13 = puVar10 + uVar2;
                  do {
                    if ((*puVar10 < uVar37) &&
                       ((*(byte *)(puVar6[sVar19] + (ulong)*puVar10) & 1) == 0))
                    goto joined_r0x0017bbe4;
                    puVar10 = puVar10 + 1;
                  } while (puVar10 != puVar13);
                }
                uVar21 = uVar1;
                uVar28 = (uint)sVar19;
                if (uVar32 <= uVar1) {
                  uVar21 = uVar32;
                  uVar28 = uVar31;
                }
              }
            }
joined_r0x0017bbe4:
            uVar31 = uVar28;
            uVar32 = uVar21;
            if (sVar19 == sVar35) goto LAB_0017bc58;
            puVar38 = puVar38 + 0x18;
            sVar19 = sVar19 + 1;
          } while( true );
        }
        goto LAB_0017babc;
      }
      goto LAB_0017bda8;
    }
    free(local_e8);
  }
  puVar6 = (undefined8 *)0x0;
  goto LAB_0017bb84;
LAB_0017b288:
  puVar7 = puVar7 + 0x18;
  if (puVar7 == __ptr + (ulong)uVar36 * 0x18) goto LAB_0017b4f4;
  goto LAB_0017b294;
LAB_0017b810:
  if (((*piVar23 == 0x1b) && (1 < (uint)piVar23[0x18])) &&
     (uVar32 = piVar23[2], uVar31 == uVar32 || piVar12[10] == uVar32)) {
    piVar24 = *(int **)(piVar23 + 0x14);
    puVar13 = *(uint **)(piVar23 + 0x16);
    iVar20 = -1;
    iVar22 = -1;
    piVar17 = piVar24 + (ulong)(uint)piVar23[0x18] * 4;
    do {
      puVar10 = puVar38;
      if (uVar9 != 0) {
        do {
          if (*puVar13 == *puVar10) {
            iVar20 = *piVar24;
            goto LAB_0017b874;
          }
          puVar10 = puVar10 + 1;
        } while (puVar10 != puVar38 + uVar9);
      }
      iVar22 = *piVar24;
LAB_0017b874:
      piVar24 = piVar24 + 4;
      puVar13 = puVar13 + 1;
    } while (piVar24 != piVar17);
    puVar18 = puVar6;
    if (iVar22 != -1 && iVar20 != -1) {
      do {
        if (*(uint *)(puVar18 + 1) != 0) {
          piVar17 = (int *)*puVar18;
          piVar24 = piVar17 + (ulong)*(uint *)(puVar18 + 1) * 0x22;
          do {
            if (piVar17[2] == iVar20) {
              iVar20 = *piVar17;
              if ((1 < iVar20 - 2U) || ((uint)piVar17[0x12] < 2)) goto LAB_0017b804;
              uVar21 = piVar17[6];
              if (uVar21 != uVar32 && piVar17[10] != uVar32) goto LAB_0017b804;
              if (uVar21 == uVar32) {
                uVar21 = piVar17[10];
              }
              uVar28 = 0;
              puVar18 = puVar6;
              goto LAB_0017b904;
            }
            piVar17 = piVar17 + 0x22;
          } while (piVar17 != piVar24);
        }
        puVar18 = puVar18 + 10;
      } while (puVar6 + (ulong)uVar37 * 10 != puVar18);
    }
  }
  goto LAB_0017b804;
LAB_0017b904:
  do {
    if (*(uint *)(puVar18 + 1) != 0) {
      piVar17 = (int *)*puVar18;
      piVar24 = piVar17 + (ulong)*(uint *)(puVar18 + 1) * 0x22;
      do {
        if (piVar17[2] == uVar21) {
          if (*piVar17 != 1) goto LAB_0017b804;
          local_d0 = *(undefined8 *)(piVar17 + 4);
          local_90 = (uint *)CONCAT44(iVar22,uVar32);
          if (uVar31 == uVar32) {
            uVar31 = piVar12[10];
          }
          uStack_80 = (undefined4)local_d0;
          uStack_7c = (undefined4)((ulong)local_d0 >> 0x20);
          uVar9 = 3;
          uStack_b0 = (ulong)uVar21;
          local_b8 = local_90;
          uStack_a0 = CONCAT44(uVar31,iVar20);
          local_6c = 1;
          local_98 = CONCAT44(1,iVar4);
          uVar25 = 1;
          uStack_a8 = local_d0;
          uStack_88 = uVar21;
          local_78 = iVar20;
          local_74 = uVar31;
          iStack_70 = iVar4;
          goto LAB_0017b618;
        }
        piVar17 = piVar17 + 0x22;
      } while (piVar17 != piVar24);
    }
    uVar28 = uVar28 + 1;
    puVar18 = puVar18 + 10;
  } while (uVar28 < uVar37);
LAB_0017b804:
  piVar23 = piVar23 + 0x22;
  if (piVar23 == piVar26) goto LAB_0017b998;
  goto LAB_0017b810;
LAB_0017bc58:
  if (uVar31 != 0xffffffff) {
    uVar32 = (__ptr + (ulong)uVar31 * 0x18)[0x17];
    *(uint **)(puVar7 + 0x10) = __ptr + (ulong)uVar31 * 0x18;
    puVar7[0x15] = uVar32 + 1;
  }
  uVar9 = uVar9 + 1;
  puVar7 = puVar7 + 0x18;
  if (uVar36 == uVar9) goto code_r0x0017bc84;
  goto LAB_0017bbc4;
code_r0x0017bc84:
  pvVar5 = calloc(__nmemb,4);
  if (pvVar5 != (void *)0x0) {
    puVar7 = __ptr + 0x12;
    uVar32 = 0;
    do {
      if (*(long *)puVar7 != 0) {
        uVar16 = (ulong)(uint)((int)(*(long *)puVar7 - (long)__ptr >> 5) * -0x55555555);
        *(int *)((long)pvVar5 + uVar16 * 4) = *(int *)((long)pvVar5 + uVar16 * 4) + 1;
      }
      uVar32 = uVar32 + 1;
      puVar7 = puVar7 + 0x18;
    } while (uVar32 < uVar9);
    puVar7 = __ptr + 0x14;
    lVar29 = 0;
    do {
      uVar32 = *(uint *)((long)pvVar5 + lVar29 * 4);
      if (uVar32 != 0) {
        pvVar8 = calloc((ulong)uVar32,8);
        *(void **)puVar7 = pvVar8;
        puVar7[2] = 0;
      }
      lVar29 = lVar29 + 1;
      puVar7 = puVar7 + 0x18;
    } while ((uint)lVar29 < uVar9);
    uVar32 = 0;
    puVar7 = __ptr;
    do {
      if (*(long *)(puVar7 + 0x12) != 0) {
        iVar4 = (int)(*(long *)(puVar7 + 0x12) - (long)__ptr >> 5);
        lVar29 = *(long *)(__ptr + (ulong)(uint)(iVar4 * -0x55555555) * 0x18 + 0x14);
        if (lVar29 != 0) {
          uVar31 = __ptr[(ulong)(uint)(iVar4 * -0x55555555) * 0x18 + 0x16];
          __ptr[(ulong)(uint)(iVar4 * -0x55555555) * 0x18 + 0x16] = uVar31 + 1;
          *(uint **)(lVar29 + (ulong)uVar31 * 8) = puVar7;
        }
      }
      uVar32 = uVar32 + 1;
      puVar7 = puVar7 + 0x18;
    } while (uVar32 < uVar9);
    free(pvVar5);
  }
  do {
    bVar3 = false;
    puVar7 = __ptr + 0x17;
    do {
      if ((*(long *)(puVar7 + -5) != 0) &&
         (uVar32 = *(int *)(*(long *)(puVar7 + -5) + 0x5c) + 1, uVar32 != *puVar7)) {
        bVar3 = true;
        *puVar7 = uVar32;
      }
      puVar7 = puVar7 + 0x18;
    } while (puVar7 != __ptr + 0x17 + uVar33 * 0x18);
  } while (bVar3);
  lVar29 = 0;
  do {
    puVar18 = puVar6 + lVar29;
    lVar29 = lVar29 + 1;
    free((void *)*puVar18);
  } while ((uint)lVar29 < uVar9);
LAB_0017bab4:
  free(puVar6);
LAB_0017babc:
  puVar6 = calloc(1,0x20);
  if (puVar6 != (undefined8 *)0x0) {
    *puVar6 = __ptr;
    *(uint *)(puVar6 + 1) = uVar36;
    *(uint *)(puVar6 + 3) = uVar37;
    pvVar5 = malloc(uVar34 << 2);
    puVar6[2] = pvVar5;
    if (pvVar5 != (void *)0x0) {
      if (uVar37 != 0) {
        memset(pvVar5,0xff,uVar34 << 2);
      }
      puVar7 = __ptr + 2;
      uVar9 = 0;
      do {
        if (puVar7[2] != 0) {
          puVar13 = *(uint **)puVar7;
          puVar38 = puVar13 + puVar7[2];
          do {
            uVar32 = *puVar13;
            if (uVar32 < uVar37) {
              uVar31 = *(uint *)((long)pvVar5 + (ulong)uVar32 * 4);
              if ((uVar31 == 0xffffffff) || (__ptr[(ulong)uVar31 * 0x18 + 0x17] < puVar7[0x15])) {
                *(uint *)((long)pvVar5 + (ulong)uVar32 * 4) = uVar9;
              }
            }
            puVar13 = puVar13 + 1;
          } while (puVar13 != puVar38);
        }
        uVar9 = uVar9 + 1;
        puVar7 = puVar7 + 0x18;
      } while (uVar36 != uVar9);
    }
    goto LAB_0017bb84;
  }
  puVar7 = __ptr + 2;
  do {
    puVar38 = puVar7 + 0x18;
    free(*(void **)puVar7);
    free(*(void **)(puVar7 + 0x12));
    puVar7 = puVar38;
  } while (puVar38 != __ptr + 2 + uVar33 * 0x18);
LAB_0017bda8:
  puVar6 = (undefined8 *)0x0;
  free(__ptr);
LAB_0017bb84:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return puVar6;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

