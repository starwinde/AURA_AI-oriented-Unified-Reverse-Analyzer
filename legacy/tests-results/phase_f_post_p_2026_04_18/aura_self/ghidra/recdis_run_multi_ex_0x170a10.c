
long * recdis_run_multi_ex(long param_1,long param_2,ulong param_3,ulong param_4,long param_5,
                          ulong param_6)

{
  size_t __nmemb;
  uint uVar1;
  byte bVar2;
  uint uVar3;
  ulonglong uVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  long *__ptr;
  void *pvVar10;
  undefined8 *__ptr_00;
  void *pvVar11;
  long *__ptr_01;
  void *pvVar12;
  ulong uVar13;
  char *pcVar14;
  ulong *__ptr_02;
  ulong uVar15;
  ulonglong *puVar16;
  ulonglong *puVar17;
  ulonglong uVar18;
  long lVar19;
  byte *pbVar20;
  ulong uVar21;
  int iVar22;
  ulonglong *puVar23;
  ulong *puVar24;
  byte bVar25;
  ulong uVar26;
  char *__s;
  uint uVar27;
  char *pcVar28;
  uint uVar29;
  ulonglong *__ptr_03;
  char *__nptr;
  ulong uVar30;
  char *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == 0 || param_2 == 0) || ((param_3 == 0 || param_5 == 0) || param_6 == 0)) ||
     (__ptr = calloc(1,0x10), __ptr == (long *)0x0)) goto LAB_00170fac;
  pvVar10 = calloc(0x1000,0x18);
  *__ptr = (long)pvVar10;
  if (pvVar10 == (void *)0x0) {
    free(__ptr);
    goto LAB_00170fac;
  }
  __ptr_00 = calloc(1,0x10);
  if (__ptr_00 == (undefined8 *)0x0) {
LAB_0017148c:
    pvVar11 = calloc(1,0x18);
    if (pvVar11 != (void *)0x0) {
      pvVar12 = calloc(0x100,8);
      if (pvVar12 == (void *)0x0) {
        free(pvVar11);
      }
      else {
        free(pvVar12);
        free(pvVar11);
      }
    }
  }
  else {
    *(undefined4 *)((long)__ptr_00 + 0xc) = 0x100;
    pvVar11 = calloc(0x100,8);
    *__ptr_00 = pvVar11;
    if (pvVar11 == (void *)0x0) {
      free(__ptr_00);
      goto LAB_0017148c;
    }
    __ptr_01 = calloc(1,0x18);
    if (__ptr_01 != (long *)0x0) {
      *(undefined4 *)(__ptr_01 + 2) = 0x100;
      pvVar12 = calloc(0x100,8);
      *__ptr_01 = (long)pvVar12;
      if (pvVar12 != (void *)0x0) {
        uVar26 = 0;
        do {
          lVar19 = uVar26 * 0x10;
          uVar26 = uVar26 + 1;
          queue_push_isra_0(__ptr_01,*(undefined8 *)(param_5 + lVar19));
        } while (uVar26 < param_6);
LAB_00170b4c:
        uVar29 = *(uint *)(__ptr_01 + 1);
        uVar27 = *(uint *)((long)__ptr_01 + 0xc);
        __ptr_03 = (ulonglong *)*__ptr_00;
LAB_00170b68:
        if ((uVar29 == uVar27) || (0xfff < *(uint *)(__ptr + 1))) {
          free(__ptr_03);
          free(__ptr_00);
          free((void *)*__ptr_01);
          free(__ptr_01);
          goto LAB_00170fb0;
        }
        uVar7 = *(uint *)(__ptr_01 + 2);
        uVar1 = *(uint *)(__ptr_00 + 1);
        uVar3 = 0;
        if (uVar7 != 0) {
          uVar3 = (uVar29 + 1) / uVar7;
        }
        uVar26 = *(ulong *)(*__ptr_01 + (ulong)uVar29 * 8);
        uVar29 = (uVar29 + 1) - uVar3 * uVar7;
        *(uint *)(__ptr_01 + 1) = uVar29;
        if (uVar1 != 0) {
          uVar13 = 0;
          do {
            if (uVar26 == __ptr_03[uVar13]) goto LAB_00170b68;
            uVar13 = uVar13 + 1;
          } while (uVar13 != uVar1);
        }
        uVar7 = *(uint *)((long)__ptr_00 + 0xc);
        puVar17 = __ptr_03;
        if (uVar7 <= uVar1) {
          puVar17 = realloc(__ptr_03,((ulong)uVar7 & 0x7fffffff) << 4);
          if (puVar17 == (ulonglong *)0x0) goto LAB_00170b68;
          *__ptr_00 = puVar17;
          *(uint *)((long)__ptr_00 + 0xc) = uVar7 << 1;
        }
        iVar22 = uVar1 + 1;
        *(int *)(__ptr_00 + 1) = iVar22;
        puVar17[uVar1] = uVar26;
        __ptr_03 = puVar17;
        if ((param_4 <= uVar26) && (uVar13 = param_3 + param_4, uVar26 < uVar13)) {
          uVar30 = uVar13 - uVar26;
          __nmemb = uVar30;
          if (0x2000 < uVar30) {
            __nmemb = 0x2000;
          }
          pvVar10 = calloc(__nmemb,0xe0);
          if (pvVar10 != (void *)0x0) {
            uVar7 = disasm_run(param_1,param_2 + (uVar26 - param_4),uVar30,uVar26,pvVar10,__nmemb);
            if (0 < (int)uVar7) {
              __s = (char *)((long)pvVar10 + 0x60);
              uVar29 = 0;
              do {
                pcVar28 = __s + -0x40;
                uVar27 = uVar29 + 1;
                iVar8 = strcmp(pcVar28,"call");
                if (((iVar8 == 0) && (*__s != '\0')) &&
                   (pcVar14 = strchr(__s,0x5b), pcVar14 == (char *)0x0)) {
                  local_70 = (char *)0x0;
                  uVar18 = strtoull(__s,&local_70,0);
                  if (((local_70 != __s) && (param_4 <= uVar18)) && (uVar18 < uVar13)) {
                    if (iVar22 != 0) {
                      puVar16 = puVar17;
                      do {
                        if (*puVar16 == uVar18) goto LAB_00170d44;
                        puVar16 = puVar16 + 1;
                      } while (puVar17 + (ulong)uVar1 + 1 != puVar16);
                    }
                    queue_push_isra_0(__ptr_01,uVar18);
                  }
                }
LAB_00170d44:
                if (((__s[-0x40] == 'j') && (iVar8 = strcmp(pcVar28,"jmp"), iVar8 != 0)) &&
                   ((*__s != '\0' && (pcVar14 = strchr(__s,0x5b), pcVar14 == (char *)0x0)))) {
                  local_70 = (char *)0x0;
                  uVar18 = strtoull(__s,&local_70,0);
                  if ((local_70 != __s) && (param_4 <= uVar18 && uVar18 < uVar13)) {
                    if (*(uint *)(__ptr_00 + 1) != 0) {
                      puVar23 = (ulonglong *)*__ptr_00;
                      puVar16 = puVar23 + *(uint *)(__ptr_00 + 1);
                      do {
                        if (*puVar23 == uVar18) goto LAB_00170d78;
                        puVar23 = puVar23 + 1;
                      } while (puVar23 != puVar16);
                    }
                    queue_push_isra_0(__ptr_01,uVar18);
                  }
                }
LAB_00170d78:
                iVar8 = strcmp(pcVar28,"ret");
                iVar9 = strcmp(pcVar28,"jmp");
                if (((((iVar8 == 0) || (iVar8 = strcmp(pcVar28,"retn"), iVar8 == 0)) ||
                     (iVar8 = strcmp(pcVar28,"retf"), iVar8 == 0)) ||
                    ((iVar8 = strcmp(pcVar28,"hlt"), iVar8 == 0 ||
                     (iVar8 = strcmp(pcVar28,"ud2"), iVar8 == 0)))) ||
                   (iVar8 = strcmp(pcVar28,"int3"), iVar8 == 0)) {
                  if (iVar9 != 0) goto LAB_00170da4;
LAB_00170fe0:
                  if ((*__s == '\0') || (pcVar14 = strchr(__s,0x5b), pcVar14 != (char *)0x0))
                  goto LAB_00170da4;
                  local_70 = (char *)0x0;
                  uVar18 = strtoull(__s,&local_70,0);
                  if ((__s == local_70) || (uVar13 <= uVar18 || uVar18 < param_4))
                  goto LAB_00170da4;
                  if (iVar22 == 0) goto LAB_0017146c;
                  puVar16 = puVar17;
                  goto LAB_0017105c;
                }
                if (iVar9 == 0) goto LAB_00170fe0;
                __s = __s + 0xe0;
                uVar29 = uVar27;
              } while (uVar7 != uVar27);
              goto LAB_00170ea0;
            }
            free(pvVar10);
          }
        }
        goto LAB_00170b68;
      }
      free(__ptr_01);
    }
    free(pvVar11);
    free(__ptr_00);
  }
  free(pvVar10);
  free(__ptr);
LAB_00170fac:
  __ptr = (long *)0x0;
LAB_00170fb0:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return __ptr;
  while (puVar16 = puVar16 + 1, puVar16 != puVar17 + (ulong)uVar1 + 1) {
LAB_0017105c:
    if (*puVar16 == uVar18) goto LAB_00170da4;
  }
LAB_0017146c:
  queue_push_isra_0(__ptr_01);
LAB_00170da4:
  iVar8 = strcmp(pcVar28,"jmp");
  if (((iVar8 != 0) || (pcVar28 = strchr(__s,0x5b), pcVar28 == (char *)0x0)) || (uVar29 == 0))
  goto LAB_00170ea0;
  lVar19 = (long)(int)(uVar29 - 1) * 0xe0;
  pvVar11 = (void *)((long)pvVar10 + lVar19);
  iVar8 = strcmp((char *)((long)pvVar11 + 0x20),"cmp");
  if (iVar8 != 0) {
    if (uVar29 == 1) goto LAB_00170ea0;
    pvVar11 = (void *)((long)pvVar10 + lVar19 + -0xe0);
    iVar8 = strcmp((char *)((long)pvVar11 + 0x20),"cmp");
    if (iVar8 != 0) {
      if (uVar29 == 2) goto LAB_00170ea0;
      pvVar11 = (void *)((long)pvVar10 + lVar19 + -0x1c0);
      iVar8 = strcmp((char *)((long)pvVar11 + 0x20),"cmp");
      if (iVar8 != 0) {
        if (uVar29 == 3) goto LAB_00170ea0;
        pvVar11 = (void *)((long)pvVar10 + lVar19 + -0x2a0);
        iVar8 = strcmp((char *)((long)pvVar11 + 0x20),"cmp");
        if (iVar8 != 0) {
          if (uVar29 == 4) goto LAB_00170ea0;
          pvVar11 = (void *)((long)pvVar10 + lVar19 + -0x380);
          iVar8 = strcmp((char *)((long)pvVar11 + 0x20),"cmp");
          if (iVar8 != 0) goto LAB_00170ea0;
        }
      }
    }
  }
  pcVar28 = strrchr((char *)((long)pvVar11 + 0x60),0x2c);
  if (pcVar28 != (char *)0x0) {
    pcVar14 = pcVar28 + 1;
    cVar6 = pcVar28[1];
    while (cVar6 == ' ') {
      pcVar14 = pcVar14 + 1;
      cVar6 = *pcVar14;
    }
    local_70 = (char *)0x0;
    lVar19 = strtol(pcVar14,&local_70,0);
    if (((local_70 != pcVar14) && (lVar19 - 1U < 0x100)) &&
       (pcVar28 = strchr(__s,0x5b), pcVar28 != (char *)0x0)) {
      cVar6 = pcVar28[1];
      iVar8 = (int)lVar19;
      pcVar14 = pcVar28;
      if (cVar6 != ']' && cVar6 != '\0') {
        do {
          __nptr = pcVar14 + 1;
          if (cVar6 == '0') {
            cVar6 = pcVar14[2];
            if (cVar6 == 'x') goto LAB_001712b0;
          }
          else {
            if ((byte)(cVar6 - 0x31U) < 9) {
LAB_001712b0:
              local_70 = (char *)0x0;
              uVar30 = strtoull(__nptr,&local_70,0);
              if ((uVar30 < uVar13 && param_4 <= uVar30) && local_70 != __nptr) {
                bVar5 = uVar30 == 0;
                pcVar28 = strstr(pcVar28,"rip");
                if (pcVar28 == (char *)0x0 || !bVar5) goto LAB_001713a8;
                goto LAB_00171310;
              }
            }
            cVar6 = pcVar14[2];
          }
          pcVar14 = __nptr;
        } while (cVar6 != ']' && cVar6 != '\0');
      }
      pcVar28 = strstr(pcVar28,"rip");
      if (pcVar28 != (char *)0x0) {
LAB_00171310:
        pcVar14 = pcVar28 + 3;
        cVar6 = pcVar28[3];
        while (cVar6 == ' ') {
          pcVar14 = pcVar14 + 1;
          cVar6 = *pcVar14;
        }
        if (cVar6 == '+') {
          iVar9 = 1;
        }
        else {
          if (cVar6 != '-') goto LAB_00170ea0;
          iVar9 = -1;
        }
        pcVar14 = pcVar14 + 1;
        cVar6 = *pcVar14;
        while (cVar6 == ' ') {
          pcVar14 = pcVar14 + 1;
          cVar6 = *pcVar14;
        }
        local_70 = (char *)0x0;
        uVar18 = strtoull(pcVar14,&local_70,0);
        if (pcVar14 != local_70) {
          uVar4 = -uVar18;
          if (iVar9 == 1) {
            uVar4 = uVar18;
          }
          uVar30 = *(long *)(__s + -0x60) + *(long *)(__s + -0x48) + uVar4;
          bVar5 = uVar30 == 0;
LAB_001713a8:
          if ((param_4 <= uVar30 && uVar30 < uVar13) && !bVar5) {
            if (0xff < iVar8) {
              iVar8 = 0xff;
            }
            uVar15 = (uVar30 - param_4) + 8;
            if (uVar15 <= param_3) {
              do {
                uVar21 = *(ulong *)(param_2 + -8 + uVar15);
                if (uVar21 < uVar13 && param_4 <= uVar21) {
                  puVar16 = puVar17;
                  if (iVar22 != 0) {
                    do {
                      if (uVar21 == *puVar16) goto LAB_00171400;
                      puVar16 = puVar16 + 1;
                    } while (puVar17 + (ulong)uVar1 + 1 != puVar16);
                  }
                  queue_push_isra_0(__ptr_01);
                }
LAB_00171400:
              } while (((uVar30 - param_4) + (long)(iVar8 + 1) * 8 != uVar15) &&
                      (uVar15 = uVar15 + 8, uVar15 <= param_3));
            }
          }
        }
      }
    }
  }
LAB_00170ea0:
  __ptr_02 = calloc(1,0x18);
  if (__ptr_02 != (ulong *)0x0) {
    *__ptr_02 = uVar26;
    *(uint *)(__ptr_02 + 2) = uVar27;
    pvVar11 = calloc((ulong)uVar27,0xe0);
    __ptr_02[1] = (ulong)pvVar11;
    if (pvVar11 != (void *)0x0) goto code_r0x00170ed4;
    free(__ptr_02);
  }
  free(pvVar10);
  uVar29 = *(uint *)(__ptr_01 + 1);
  uVar27 = *(uint *)((long)__ptr_01 + 0xc);
  goto LAB_00170b68;
code_r0x00170ed4:
  __memcpy_chk(pvVar11,pvVar10,(ulong)uVar27 * 0xe0);
  free(pvVar10);
  uVar29 = *(uint *)(__ptr + 1);
  uVar13 = 0;
  uVar30 = __ptr_02[1];
  puVar24 = (ulong *)(*__ptr + (ulong)uVar29 * 0x18);
  uVar15 = __ptr_02[2];
  iVar22 = -1;
  pbVar20 = (byte *)(param_5 + 9);
  *puVar24 = *__ptr_02;
  puVar24[1] = uVar30;
  puVar24[2] = uVar15;
  bVar25 = 0;
  do {
    while ((uVar26 != *(ulong *)(pbVar20 + -9) ||
           ((bVar2 = *pbVar20, -1 < iVar22 && (bVar2 <= bVar25))))) {
      uVar13 = uVar13 + 1;
      pbVar20 = pbVar20 + 0x10;
      if (param_6 <= uVar13) goto LAB_00170f74;
    }
    iVar22 = (int)uVar13;
    uVar13 = uVar13 + 1;
    pbVar20 = pbVar20 + 0x10;
    bVar25 = bVar2;
  } while (uVar13 < param_6);
LAB_00170f74:
  if (-1 < iVar22) {
    *(undefined2 *)((long)puVar24 + 0x14) = *(undefined2 *)(param_5 + (long)iVar22 * 0x10 + 8);
  }
  *(uint *)(__ptr + 1) = uVar29 + 1;
  *(uint *)((long)__ptr + 0xc) = *(int *)((long)__ptr + 0xc) + uVar27;
  free(__ptr_02);
  goto LAB_00170b4c;
}

