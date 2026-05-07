
undefined8 * func_detect(ulong *param_1,ulong param_2,long param_3,byte *param_4)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined8 *__ptr;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulong *__s1;
  ulong *puVar10;
  char *pcVar11;
  byte *pbVar12;
  long *plVar14;
  void *pvVar15;
  char *pcVar16;
  ulong uVar17;
  ulong *puVar18;
  ulong uVar19;
  ulong uVar20;
  long lVar21;
  char *pcVar22;
  uint uVar23;
  long *plVar24;
  void *__ptr_00;
  long lVar25;
  uint uVar26;
  uint uVar27;
  ulong *puVar28;
  uint uVar29;
  ulong uVar30;
  long lVar31;
  byte bVar32;
  long *local_d0;
  ulong local_c8;
  ulong local_b0;
  long *local_88;
  ulong local_80;
  long local_78;
  uint local_70;
  long local_68;
  byte *pbVar13;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  __ptr = malloc(0x10);
  if (__ptr != (undefined8 *)0x0) {
    bVar3 = param_2 != 0;
    *__ptr = 0;
    __ptr[1] = 0;
    bVar4 = param_1 != (ulong *)0x0;
    if (param_4 == (byte *)0x0) {
      if (param_3 == 0) {
        if (!bVar3 || !bVar4) goto LAB_00149dd0;
        local_88 = (long *)xref_build(param_1,param_2);
        bVar32 = 0;
        candidateset_init(&local_78);
LAB_0014a188:
        bVar3 = false;
        goto LAB_00149ec0;
      }
      if (*(int *)(param_3 + 0x30) == 0) {
        if (!bVar3 || !bVar4) goto LAB_00149dd0;
        local_88 = (long *)xref_build(param_1,param_2);
        bVar32 = 0;
        candidateset_init(&local_78);
LAB_00149e7c:
        if (*(uint *)(param_3 + 0x30) != 0) {
          plVar14 = (long *)(*(long *)(param_3 + 0x28) + 0x10);
          plVar24 = plVar14 + (ulong)*(uint *)(param_3 + 0x30) * 5;
          do {
            if (((int)plVar14[2] == 1) && (*plVar14 != 0)) {
              bVar3 = true;
              goto LAB_00149ec0;
            }
            plVar14 = plVar14 + 5;
          } while (plVar24 != plVar14);
        }
        goto LAB_0014a188;
      }
      if (bVar3 && bVar4) {
        local_88 = (long *)xref_build(param_1,param_2);
        bVar32 = 100;
        candidateset_init(&local_78);
        goto LAB_00149e7c;
      }
LAB_00149dd0:
      puVar8 = malloc(0x10);
      if (puVar8 == (undefined8 *)0x0) {
        puVar8 = (undefined8 *)0x0;
        free(__ptr);
        goto LAB_00149e0c;
      }
      *puVar8 = 0;
      *__ptr = puVar8;
      *(undefined4 *)(puVar8 + 1) = 0;
      puVar9 = malloc(0x10);
      if (puVar9 == (undefined8 *)0x0) {
        free(puVar8);
        puVar8 = (undefined8 *)0x0;
        free(__ptr);
        goto LAB_00149e0c;
      }
      *puVar9 = 0;
      *(undefined4 *)(puVar9 + 1) = 0;
LAB_00149e04:
      __ptr[1] = puVar9;
      puVar8 = __ptr;
      goto LAB_00149e0c;
    }
    if (!bVar3 || !bVar4) goto LAB_00149dd0;
    bVar32 = *param_4;
    local_88 = (long *)xref_build(param_1,param_2);
    candidateset_init();
    bVar3 = false;
    if (param_3 != 0) goto LAB_00149e7c;
LAB_00149ec0:
    plVar14 = local_88;
    local_d0 = &local_78;
    puVar28 = param_1 + 0xc;
    local_c8 = 0;
    do {
      puVar18 = puVar28 + 0x10;
      puVar10 = puVar28 + -8;
      uVar30 = local_c8 + 1;
      if (param_2 <= uVar30) {
        puVar18 = (ulong *)0x0;
      }
      iVar5 = strcmp((char *)puVar10,"push");
      if (iVar5 == 0) {
        __s1 = puVar28;
        if ((char)*puVar28 == ' ' || (char)*puVar28 == '\t') {
          do {
            __s1 = (ulong *)((long)__s1 + 1);
          } while (*(char *)__s1 == ' ' || *(char *)__s1 == '\t');
        }
        iVar6 = strcmp((char *)__s1,"rbp");
        if (iVar6 != 0) goto LAB_0014a064;
        if ((puVar18 == (ulong *)0x0) || (iVar5 = strcmp((char *)(puVar18 + 4),"mov"), iVar5 != 0))
        {
LAB_0014a018:
          iVar5 = candidateset_add(local_d0,puVar28[-0xc],0,0x3c,0);
        }
        else {
          puVar10 = puVar18 + 0xc;
          if ((char)puVar18[0xc] == ' ' || (char)puVar18[0xc] == '\t') {
            do {
              puVar10 = (ulong *)((long)puVar10 + 1);
            } while (*(char *)puVar10 == ' ' || *(char *)puVar10 == '\t');
          }
          if ((((char)*puVar10 != 'r') || (*(char *)((long)puVar10 + 1) != 'b')) ||
             ((*(char *)((long)puVar10 + 2) != 'p' ||
              ((*(char *)((long)puVar10 + 3) != ',' ||
               (pcVar11 = strstr((char *)puVar10,"rsp"), pcVar11 == (char *)0x0))))))
          goto LAB_0014a018;
          uVar17 = puVar28[-0xc];
LAB_0014a124:
          iVar5 = candidateset_add(local_d0,uVar17,0,0x50,0);
        }
        if (iVar5 == 0) goto LAB_0014a034;
      }
      else {
LAB_0014a064:
        if ((!bVar3) && (iVar6 = strcmp((char *)puVar10,"sub"), iVar6 == 0)) {
          puVar18 = puVar28;
          if ((char)*puVar28 == ' ' || (char)*puVar28 == '\t') {
            do {
              puVar18 = (ulong *)((long)puVar18 + 1);
            } while (*(char *)puVar18 == ' ' || *(char *)puVar18 == '\t');
          }
          if (((((char)*puVar18 == 'r') && (*(char *)((long)puVar18 + 1) == 's')) &&
              (*(char *)((long)puVar18 + 2) == 'p')) && (*(char *)((long)puVar18 + 3) == ','))
          goto LAB_0014a018;
        }
        iVar6 = strcmp((char *)puVar10,"stp");
        if (iVar6 == 0) {
          puVar18 = puVar28;
          if ((char)*puVar28 == ' ' || (char)*puVar28 == '\t') {
            do {
              puVar18 = (ulong *)((long)puVar18 + 1);
            } while (*(char *)puVar18 == ' ' || *(char *)puVar18 == '\t');
          }
          iVar6 = strncmp((char *)puVar18,"x29, x30, [sp",0xd);
          if (iVar6 == 0) {
            uVar17 = puVar28[-0xc];
            pcVar11 = strchr((char *)puVar28,0x21);
            if ((pcVar11 == (char *)0x0) && (local_c8 != 0)) {
              puVar18 = puVar28 + -0x1c;
              do {
                iVar5 = strcmp((char *)(puVar18 + -8),"sub");
                if (iVar5 == 0) {
                  puVar10 = puVar18;
                  if ((char)*puVar18 == ' ' || (char)*puVar18 == '\t') {
                    do {
                      puVar10 = (ulong *)((long)puVar10 + 1);
                    } while (*(char *)puVar10 == ' ' || *(char *)puVar10 == '\t');
                  }
                  iVar5 = strncmp((char *)puVar10,"sp, sp, #",9);
                  if (iVar5 == 0) {
                    uVar17 = puVar18[-0xc];
                    break;
                  }
                }
                if ((puVar28 + -0x70 == puVar18) ||
                   (puVar18 = puVar18 + -0x1c, param_1 + -0x10 == puVar18)) break;
              } while( true );
            }
            goto LAB_0014a124;
          }
        }
        iVar6 = strcmp((char *)puVar10,"str");
        if (iVar6 == 0) {
          puVar18 = puVar28;
          if ((char)*puVar28 == ' ' || (char)*puVar28 == '\t') {
            do {
              puVar18 = (ulong *)((long)puVar18 + 1);
            } while (*(char *)puVar18 == ' ' || *(char *)puVar18 == '\t');
          }
          iVar6 = strncmp((char *)puVar18,"x30, [sp",8);
          if ((iVar6 == 0) && (pcVar11 = strchr((char *)puVar18,0x21), pcVar11 != (char *)0x0))
          goto LAB_0014a018;
        }
        if (iVar5 == 0) {
          cVar1 = (char)*puVar28;
          puVar18 = puVar28;
          if (cVar1 == ' ' || cVar1 == '\t') {
            do {
              puVar18 = (ulong *)((long)puVar18 + 1);
              cVar1 = *(char *)puVar18;
            } while (cVar1 == ' ' || cVar1 == '\t');
          }
          if ((cVar1 == '{') && (pcVar11 = strstr((char *)puVar18,"lr"), pcVar11 != (char *)0x0)) {
            uVar17 = puVar28[-0xc];
            goto LAB_0014a124;
          }
        }
        iVar5 = strcmp((char *)puVar10,"stmdb");
        if (iVar5 == 0) {
          puVar18 = puVar28;
          if ((char)*puVar28 == ' ' || (char)*puVar28 == '\t') {
            do {
              puVar18 = (ulong *)((long)puVar18 + 1);
            } while (*(char *)puVar18 == ' ' || *(char *)puVar18 == '\t');
          }
          if (((((char)*puVar18 == 's') && (*(char *)((long)puVar18 + 1) == 'p')) &&
              (*(char *)((long)puVar18 + 2) == '!')) &&
             (pcVar11 = strstr((char *)puVar18,"lr"), pcVar11 != (char *)0x0)) {
            uVar17 = puVar28[-0xc];
            goto LAB_0014a124;
          }
        }
      }
      puVar28 = puVar28 + 0x1c;
      local_c8 = uVar30;
    } while (uVar30 < param_2);
    uVar19 = *param_1;
    uVar20 = param_1[param_2 * 0x1c + -0x1c];
    puVar28 = param_1 + 4;
    uVar17 = param_1[param_2 * 0x1c + -0x19];
    uVar30 = 0;
    puVar18 = puVar28;
    do {
      iVar5 = strncmp((char *)puVar18,"call",4);
      if (((((iVar5 == 0) ||
            ((((char)*puVar18 == 'b' && (*(char *)((long)puVar18 + 1) == 'l')) &&
             (*(char *)((long)puVar18 + 2) == '\0')))) ||
           (iVar5 = strcmp((char *)puVar18,"jal"), iVar5 == 0)) &&
          ((iVar5 = parse_direct_addr(puVar18 + 8,&local_80), iVar5 != 0 &&
           (local_80 < uVar20 + uVar17 && uVar19 <= local_80)))) &&
         (iVar5 = candidateset_add(local_d0,local_80,1,0xffffffb4,0), iVar5 == 0))
      goto LAB_0014a034;
      uVar30 = uVar30 + 1;
      puVar18 = puVar18 + 0x1c;
    } while (uVar30 < param_2);
    if ((plVar14 != (long *)0x0) && (uVar23 = *(uint *)(plVar14 + 1), uVar23 != 0)) {
      lVar31 = 0;
      uVar19 = *param_1;
      uVar17 = param_1[param_2 * 0x1c + -0x1c];
      uVar30 = param_1[param_2 * 0x1c + -0x19];
      do {
        lVar25 = *plVar14 + lVar31 * 0x18;
        if ((*(int *)(lVar25 + 0x10) == 0) &&
           (uVar20 = *(ulong *)(lVar25 + 8), uVar19 <= uVar20 && uVar20 < uVar17 + uVar30)) {
          iVar5 = candidateset_add(local_d0,uVar20,2,0xffffffaa,0);
          if (iVar5 == 0) goto LAB_0014a034;
          uVar23 = *(uint *)(plVar14 + 1);
        }
        lVar31 = lVar31 + 1;
      } while ((uint)lVar31 < uVar23);
    }
    if (param_3 == 0) {
      iVar5 = candidateset_add(local_d0,*param_1,0,0x3c,0);
      if (iVar5 != 0) goto LAB_0014a5b8;
LAB_0014a034:
      candidateset_free(local_d0);
      if (local_88 != (long *)0x0) {
        xref_table_destroy(&local_88);
      }
    }
    else {
      uVar23 = *(uint *)(param_3 + 0x30);
      if (uVar23 != 0) {
        lVar31 = 0;
        uVar29 = 0;
        do {
          lVar25 = *(long *)(param_3 + 0x28) + lVar31;
          if ((*(int *)(lVar25 + 0x20) == 1) && (lVar21 = *(long *)(lVar25 + 0x10), lVar21 != 0)) {
            if (*(long *)(lVar25 + 0x18) == 0) {
              iVar5 = candidateset_add(local_d0,lVar21,3,0xffffffa0,0);
              if (iVar5 == 0) goto LAB_0014a034;
              uVar23 = *(uint *)(param_3 + 0x30);
            }
            else {
              iVar5 = candidateset_add(local_d0,lVar21,3,0xffffffc8);
              if (iVar5 == 0) goto LAB_0014a034;
              uVar23 = *(uint *)(param_3 + 0x30);
            }
          }
          uVar29 = uVar29 + 1;
          lVar31 = lVar31 + 0x28;
        } while (uVar29 < uVar23);
      }
      iVar5 = candidateset_add(local_d0,*param_1,0,0x3c,0);
      if (iVar5 == 0) goto LAB_0014a034;
      uVar30 = param_1[param_2 * 0x1c + -0x19];
      uVar19 = *param_1;
      uVar17 = param_1[param_2 * 0x1c + -0x1c];
      fd_ehframe_add_candidates(param_3,local_d0,uVar19,uVar17 + uVar30);
      fd_plt_add_candidates(param_3,local_d0);
      fd_datascan_add_candidates
                (param_3,local_d0,uVar19,uVar17 + uVar30,*(undefined4 *)(param_3 + 0xc),0);
      candidateset_dedup(local_d0);
LAB_0014a5b8:
      candidateset_dedup(local_d0);
      if (local_88 != (long *)0x0) {
        xref_table_destroy(&local_88);
      }
      uVar23 = local_70;
      if (local_70 == 0) {
        plVar14 = malloc(0x10);
        if (plVar14 == (long *)0x0) goto LAB_0014aaf8;
        *plVar14 = 0;
        *(undefined4 *)(plVar14 + 1) = 0;
      }
      else {
        uVar29 = 0;
        pbVar13 = (byte *)(local_78 + 9);
        do {
          pbVar12 = pbVar13 + 0x10;
          if (bVar32 <= *pbVar13) {
            uVar29 = uVar29 + 1;
          }
          pbVar13 = pbVar12;
        } while ((byte *)(local_78 + 9) + (ulong)local_70 * 0x10 != pbVar12);
        plVar14 = malloc(0x10);
        if (plVar14 == (long *)0x0) {
LAB_0014aaf8:
          plVar14 = (long *)0x0;
        }
        else {
          *(uint *)(plVar14 + 1) = uVar29;
          if (uVar29 == 0) {
            *plVar14 = 0;
            local_b0 = param_1[param_2 * 0x1c + -0x1c] + param_1[param_2 * 0x1c + -0x19];
          }
          else {
            pvVar15 = calloc((ulong)uVar29,0x98);
            *plVar14 = (long)pvVar15;
            if (pvVar15 == (void *)0x0) {
              free(plVar14);
              goto LAB_0014aaf8;
            }
            local_b0 = param_1[param_2 * 0x1c + -0x1c] + param_1[param_2 * 0x1c + -0x19];
          }
          lVar31 = 0;
          uVar30 = 0;
          uVar29 = 0;
          do {
            while( true ) {
              uVar7 = uVar29 + 1;
              bVar2 = *(byte *)(local_78 + lVar31 * 0x10 + 9);
              if (bVar2 < bVar32) break;
              uVar17 = *(ulong *)(local_78 + lVar31 * 0x10);
              lVar25 = *plVar14 + uVar30 * 0x98;
              *(ulong *)(*plVar14 + uVar30 * 0x98) = uVar17;
              *(byte *)(lVar25 + 0x94) = bVar2;
              if (uVar7 < uVar23) {
                puVar18 = (ulong *)(local_78 + (ulong)uVar7 * 0x10);
                do {
                  if (bVar32 <= *(byte *)((long)puVar18 + 9)) {
                    uVar19 = *puVar18;
                    *(ulong *)(lVar25 + 8) = uVar19;
                    iVar5 = (int)uVar19 - (int)uVar17;
                    if (uVar19 <= uVar17) {
                      iVar5 = 0;
                    }
                    *(int *)(lVar25 + 0x10) = iVar5;
                    goto joined_r0x0014a700;
                  }
                  puVar18 = puVar18 + 2;
                } while ((ulong *)(local_78 + 0x20 +
                                  ((ulong)((uVar23 - 2) - uVar29) + lVar31) * 0x10) != puVar18);
              }
              *(ulong *)(lVar25 + 8) = local_b0;
              iVar5 = (int)local_b0 - (int)uVar17;
              if (local_b0 <= uVar17) {
                iVar5 = 0;
              }
              *(int *)(lVar25 + 0x10) = iVar5;
joined_r0x0014a700:
              if ((param_3 == 0) || (*(uint *)(param_3 + 0x30) == 0)) {
LAB_0014a998:
                __snprintf_chk(lVar25 + 0x14,0x80,2,0x80,"sub_%lx");
                uVar23 = local_70;
              }
              else {
                puVar8 = *(undefined8 **)(param_3 + 0x28);
                pcVar11 = (char *)0x0;
                uVar29 = 0;
                puVar9 = puVar8 + (ulong)*(uint *)(param_3 + 0x30) * 5;
                do {
                  if ((((uVar17 == puVar8[2]) && (pcVar16 = (char *)*puVar8, pcVar16 != (char *)0x0)
                       ) && (*pcVar16 != '\0')) &&
                     (((*pcVar16 != '$' || (uVar27 = (byte)pcVar16[1] - 100 & 0xff, 0x14 < uVar27))
                      || (((0x110001UL >> ((ulong)uVar27 & 0x3f) & 1) == 0 ||
                          (pcVar16[2] != '.' && pcVar16[2] != '\0')))))) {
                    uVar27 = 4;
                    if (puVar8[3] == 0) {
                      uVar27 = 3;
                    }
                    uVar26 = 2;
                    if (puVar8[3] == 0) {
                      uVar26 = 1;
                    }
                    if (*(int *)((long)puVar8 + 0x24) != 1) {
                      uVar27 = uVar26;
                    }
                    if (((uVar29 < uVar27) &&
                        (pcVar22 = (char *)puVar8[1], pcVar11 = pcVar16, uVar29 = uVar27,
                        pcVar22 != (char *)0x0)) && (pcVar11 = pcVar22, *pcVar22 == '\0')) {
                      pcVar11 = pcVar16;
                    }
                  }
                  puVar8 = puVar8 + 5;
                } while (puVar8 != puVar9);
                if (pcVar11 == (char *)0x0) goto LAB_0014a998;
                strncpy((char *)(lVar25 + 0x14),pcVar11,0x7f);
                *(undefined1 *)(lVar25 + 0x93) = 0;
              }
              uVar30 = (ulong)((int)uVar30 + 1);
              lVar31 = lVar31 + 1;
              uVar29 = uVar7;
              if (uVar23 <= uVar7) goto LAB_0014a7d0;
            }
            lVar31 = lVar31 + 1;
            uVar29 = uVar7;
          } while (uVar7 < uVar23);
        }
      }
LAB_0014a7d0:
      *__ptr = plVar14;
      candidateset_free(local_d0);
      plVar14 = (long *)*__ptr;
      if (plVar14 != (long *)0x0) {
        puVar9 = malloc(0x10);
        if (puVar9 != (undefined8 *)0x0) {
          *(undefined4 *)(puVar9 + 1) = 0;
          pvVar15 = malloc(0x300);
          *puVar9 = pvVar15;
          if (pvVar15 != (void *)0x0) {
            uVar23 = 0x20;
            uVar30 = 0;
            do {
              iVar5 = strncmp((char *)puVar28,"call",4);
              if (((iVar5 == 0) ||
                  (((((char)*puVar28 == 'b' && (*(char *)((long)puVar28 + 1) == 'l')) &&
                    (*(char *)((long)puVar28 + 2) == '\0')) ||
                   (iVar5 = strcmp((char *)puVar28,"jal"), iVar5 == 0)))) &&
                 (iVar5 = parse_direct_addr(puVar28 + 8,&local_80), uVar17 = local_80, iVar5 != 0))
              {
                uVar29 = *(uint *)(plVar14 + 1);
                uVar19 = puVar28[-4];
                if (uVar29 != 0) {
                  uVar7 = 0;
                  uVar27 = uVar29;
                  while (uVar26 = uVar27, uVar7 < uVar26) {
                    uVar27 = uVar7 + (uVar26 - uVar7 >> 1);
                    if (*(ulong *)(*plVar14 + (ulong)uVar27 * 0x98) <= uVar19) {
                      uVar7 = uVar27 + 1;
                      uVar27 = uVar26;
                    }
                  }
                  if (uVar7 != 0) {
                    lVar25 = *plVar14;
                    lVar31 = (ulong)(uVar7 - 1) * 0x98;
                    if ((*(ulong *)(lVar25 + lVar31) <= uVar19) &&
                       (uVar19 < *(ulong *)(lVar25 + lVar31 + 8))) {
                      uVar27 = 0;
                      while (uVar26 = uVar29, uVar27 < uVar26) {
                        uVar29 = uVar27 + (uVar26 - uVar27 >> 1);
                        if (*(ulong *)(lVar25 + (ulong)uVar29 * 0x98) <= local_80) {
                          uVar27 = uVar29 + 1;
                          uVar29 = uVar26;
                        }
                      }
                      uVar29 = 0xffffffff;
                      if (uVar27 != 0) {
                        uVar29 = uVar27 - 1;
                        if (local_80 < *(ulong *)(lVar25 + (ulong)uVar29 * 0x98)) {
                          uVar29 = 0xffffffff;
                        }
                        else if (*(ulong *)(lVar25 + (ulong)uVar29 * 0x98 + 8) <= local_80) {
                          uVar29 = 0xffffffff;
                        }
                      }
                      uVar27 = *(uint *)(puVar9 + 1);
                      __ptr_00 = (void *)*puVar9;
                      pvVar15 = __ptr_00;
                      if (uVar23 <= uVar27) {
                        uVar23 = uVar23 << 1;
                        pvVar15 = realloc(__ptr_00,(ulong)uVar23 * 0x18);
                        if (pvVar15 == (void *)0x0) {
                          free(__ptr_00);
                          free(puVar9);
                          plVar14 = (long *)*__ptr;
                          __ptr[1] = 0;
                          if (plVar14 == (long *)0x0) goto LAB_0014a04c;
                          goto LAB_0014aac8;
                        }
                        uVar19 = puVar28[-4];
                        *puVar9 = pvVar15;
                      }
                      *(uint *)(puVar9 + 1) = uVar27 + 1;
                      lVar31 = (ulong)uVar27 * 0x18;
                      *(uint *)((long)pvVar15 + lVar31) = uVar7 - 1;
                      *(uint *)((long)pvVar15 + lVar31 + 4) = uVar29;
                      *(ulong *)((long)pvVar15 + lVar31 + 8) = uVar17;
                      *(ulong *)((long)pvVar15 + lVar31 + 0x10) = uVar19;
                    }
                  }
                }
              }
              uVar30 = uVar30 + 1;
              puVar28 = puVar28 + 0x1c;
            } while (uVar30 < param_2);
            goto LAB_00149e04;
          }
          free(puVar9);
        }
LAB_0014aac8:
        free((void *)*plVar14);
        free(plVar14);
      }
    }
LAB_0014a04c:
    free(__ptr);
  }
  puVar8 = (undefined8 *)0x0;
LAB_00149e0c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return puVar8;
}

