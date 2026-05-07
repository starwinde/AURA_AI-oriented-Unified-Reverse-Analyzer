
long * indirect_resolve(long param_1,ulong param_2,long param_3,ulong param_4,ulong param_5)

{
  long lVar1;
  uint uVar2;
  uint uVar3;
  ulonglong uVar4;
  char cVar5;
  int iVar6;
  long *__ptr;
  void *pvVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  long lVar11;
  char *pcVar12;
  ulonglong uVar13;
  ulong uVar14;
  undefined4 uVar15;
  undefined8 uVar16;
  char *__s1;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  ulong local_c8;
  char *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  __ptr = calloc(1,0x10);
  if (__ptr != (long *)0x0) {
    *(undefined4 *)((long)__ptr + 0xc) = 0x40;
    pvVar7 = calloc(0x40,0x18);
    *__ptr = (long)pvVar7;
    if (pvVar7 != (void *)0x0) {
      if (param_1 != 0 && param_2 != 0) {
        __s1 = (char *)(param_1 + 0x20);
        uVar17 = 0;
        do {
          iVar6 = strcmp(__s1,"call");
          if ((iVar6 == 0) || (iVar6 = strcmp(__s1,"jmp"), iVar6 == 0)) {
            pcVar12 = __s1 + 0x40;
            pcVar8 = strchr(pcVar12,0x5b);
            if (pcVar8 != (char *)0x0) {
              pcVar8 = strstr(pcVar8,"rip");
              if (pcVar8 == (char *)0x0) {
LAB_00188354:
                iVar6 = strcmp(__s1,"jmp");
              }
              else {
                pcVar9 = pcVar8 + 3;
                cVar5 = pcVar8[3];
                while (cVar5 == ' ') {
                  pcVar9 = pcVar9 + 1;
                  cVar5 = *pcVar9;
                }
                iVar6 = 1;
                if (cVar5 != '+') {
                  if (cVar5 != '-') goto LAB_00188354;
                  iVar6 = -1;
                }
                pcVar9 = pcVar9 + 1;
                cVar5 = *pcVar9;
                while (cVar5 == ' ') {
                  pcVar9 = pcVar9 + 1;
                  cVar5 = *pcVar9;
                }
                local_70 = (char *)0x0;
                uVar13 = strtoull(pcVar9,&local_70,0);
                if (local_70 == pcVar9) goto LAB_00188354;
                lVar11 = *(long *)(__s1 + -0x20);
                uVar4 = -uVar13;
                if (iVar6 == 1) {
                  uVar4 = uVar13;
                }
                uVar14 = lVar11 + *(long *)(__s1 + -8) + uVar4;
                if ((((uVar14 < param_5) || (param_4 + param_5 < uVar14 + 8)) ||
                    (uVar14 = *(ulong *)(param_3 + (uVar14 - param_5)), uVar14 < param_5)) ||
                   (param_4 + param_5 <= uVar14)) goto LAB_00188354;
                iVar6 = strcmp(__s1,"call");
                uVar15 = 0;
                if ((iVar6 == 0) && (uVar17 != 0)) {
                  pcVar8 = strchr(pcVar12,0x5b);
                  uVar15 = 0;
                  if (pcVar8 != (char *)0x0) {
                    uVar18 = uVar17;
                    if (uVar17 < 5) {
                      uVar18 = 5;
                    }
                    if (uVar18 - 5 < uVar17) {
                      pcVar8 = (char *)(param_1 + uVar18 * 0xe0 + -0x440);
                      do {
                        iVar6 = strcmp(pcVar8,"mov");
                        if (iVar6 == 0) {
                          pcVar9 = pcVar8 + 0x40;
                          pcVar10 = strstr(pcVar9,"[rdi]");
                          if (((pcVar10 != (char *)0x0) ||
                              (pcVar10 = strstr(pcVar9,"[rcx]"), pcVar10 != (char *)0x0)) ||
                             ((pcVar10 = strstr(pcVar9,"[edi]"), pcVar10 != (char *)0x0 ||
                              (pcVar9 = strstr(pcVar9,"[ecx]"), pcVar9 != (char *)0x0)))) {
                            uVar15 = 1;
                            goto LAB_00188558;
                          }
                        }
                        pcVar8 = pcVar8 + 0xe0;
                      } while (pcVar8 != __s1);
                      uVar15 = 0;
                    }
                  }
                }
LAB_00188558:
                uVar2 = *(uint *)(__ptr + 1);
                if (*(uint *)((long)__ptr + 0xc) <= uVar2) {
                  uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
                  if (uVar3 < 0x40) {
                    uVar3 = 0x40;
                  }
                  pvVar7 = realloc((void *)*__ptr,(ulong)uVar3 * 0x18);
                  if (pvVar7 == (void *)0x0) goto LAB_00188354;
                  *__ptr = (long)pvVar7;
                  *(uint *)((long)__ptr + 0xc) = uVar3;
                }
                if (0x3ff < uVar2) goto LAB_00188354;
                *(uint *)(__ptr + 1) = uVar2 + 1;
                lVar1 = *__ptr + (ulong)uVar2 * 0x18;
                *(long *)(*__ptr + (ulong)uVar2 * 0x18) = lVar11;
                *(ulong *)(lVar1 + 8) = uVar14;
                *(undefined4 *)(lVar1 + 0x10) = uVar15;
                iVar6 = strcmp(__s1,"jmp");
              }
              if ((iVar6 == 0) && (pcVar8 = strchr(pcVar12,0x5b), pcVar8 != (char *)0x0)) {
                uVar14 = uVar17;
                if (uVar17 < 5) {
                  uVar14 = 5;
                }
                if (uVar14 - 5 < uVar17) {
                  pcVar8 = (char *)(param_1 + uVar14 * 0xe0 + -0x460);
LAB_00188604:
                  iVar6 = strcmp(pcVar8 + 0x20,"cmp");
                  if (iVar6 != 0) goto LAB_001885f8;
                  pcVar8 = strrchr(pcVar8 + 0x60,0x2c);
                  if (pcVar8 != (char *)0x0) {
                    pcVar9 = pcVar8 + 1;
                    cVar5 = pcVar8[1];
                    while (cVar5 == ' ') {
                      pcVar9 = pcVar9 + 1;
                      cVar5 = *pcVar9;
                    }
                    local_70 = (char *)0x0;
                    lVar11 = strtol(pcVar9,&local_70,0);
                    if (((pcVar9 != local_70) && (lVar11 - 1U < 0x100)) &&
                       (pcVar12 = strchr(pcVar12,0x5b), pcVar12 != (char *)0x0)) {
                      pcVar8 = strstr(pcVar12,"rip");
                      if (pcVar8 == (char *)0x0) {
                        cVar5 = pcVar12[1];
                        if (cVar5 != ']' && cVar5 != '\0') {
                          do {
                            local_c8 = param_4 + param_5;
                            pcVar8 = pcVar12 + 1;
                            if (cVar5 == '0') {
                              cVar5 = pcVar12[2];
                              if (cVar5 == 'x') goto LAB_00188878;
                            }
                            else {
                              if ((byte)(cVar5 - 0x31U) < 9) {
LAB_00188878:
                                local_70 = (char *)0x0;
                                uVar14 = strtoull(pcVar8,&local_70,0);
                                if ((local_70 != pcVar8 && param_5 <= uVar14) && (uVar14 < local_c8)
                                   ) {
                                  if (uVar14 != 0) goto LAB_00188760;
                                  break;
                                }
                              }
                              cVar5 = pcVar12[2];
                            }
                            pcVar12 = pcVar8;
                          } while (cVar5 != ']' && cVar5 != '\0');
                        }
                      }
                      else {
                        pcVar12 = pcVar8 + 3;
                        cVar5 = pcVar8[3];
                        while (cVar5 == ' ') {
                          pcVar12 = pcVar12 + 1;
                          cVar5 = *pcVar12;
                        }
                        iVar6 = 1;
                        if (cVar5 != '+') {
                          if (cVar5 != '-') goto LAB_00188368;
                          iVar6 = -1;
                        }
                        pcVar12 = pcVar12 + 1;
                        cVar5 = *pcVar12;
                        while (cVar5 == ' ') {
                          pcVar12 = pcVar12 + 1;
                          cVar5 = *pcVar12;
                        }
                        local_70 = (char *)0x0;
                        uVar13 = strtoull(pcVar12,&local_70,0);
                        if (pcVar12 != local_70) {
                          uVar4 = -uVar13;
                          if (iVar6 == 1) {
                            uVar4 = uVar13;
                          }
                          uVar14 = *(long *)(__s1 + -0x20) + *(long *)(__s1 + -8) + uVar4;
                          if ((uVar14 != 0 && param_5 <= uVar14) && (uVar14 < param_4 + param_5)) {
LAB_00188760:
                            iVar6 = (int)lVar11;
                            if (0xff < iVar6) {
                              iVar6 = 0xff;
                            }
                            uVar18 = (uVar14 - param_5) + 8;
                            if (uVar18 <= param_4) {
                              do {
                                uVar19 = *(ulong *)(param_3 + -8 + uVar18);
                                if (param_5 <= uVar19 && uVar19 < param_4 + param_5) {
                                  uVar2 = *(uint *)(__ptr + 1);
                                  uVar16 = *(undefined8 *)(__s1 + -0x20);
                                  if (*(uint *)((long)__ptr + 0xc) <= uVar2) {
                                    uVar3 = *(uint *)((long)__ptr + 0xc) << 1;
                                    if (uVar3 < 0x40) {
                                      uVar3 = 0x40;
                                    }
                                    pvVar7 = realloc((void *)*__ptr,(ulong)uVar3 * 0x18);
                                    if (pvVar7 == (void *)0x0) goto LAB_0018879c;
                                    *__ptr = (long)pvVar7;
                                    *(uint *)((long)__ptr + 0xc) = uVar3;
                                  }
                                  if (uVar2 < 0x400) {
                                    *(uint *)(__ptr + 1) = uVar2 + 1;
                                    lVar11 = *__ptr + (ulong)uVar2 * 0x18;
                                    *(undefined8 *)(*__ptr + (ulong)uVar2 * 0x18) = uVar16;
                                    *(ulong *)(lVar11 + 8) = uVar19;
                                    *(undefined4 *)(lVar11 + 0x10) = 2;
                                  }
                                }
LAB_0018879c:
                              } while ((uVar18 != (uVar14 - param_5) + (long)(iVar6 + 1) * 8) &&
                                      (uVar18 = uVar18 + 8, uVar18 <= param_4));
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
LAB_00188368:
          uVar17 = uVar17 + 1;
          __s1 = __s1 + 0xe0;
        } while (uVar17 < param_2);
      }
      goto LAB_00188380;
    }
    free(__ptr);
  }
  __ptr = (long *)0x0;
LAB_00188380:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return __ptr;
LAB_001885f8:
  pcVar8 = pcVar8 + 0xe0;
  if (pcVar8 == __s1 + -0x20) goto LAB_00188368;
  goto LAB_00188604;
}

