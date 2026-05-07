
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void print_value(long param_1,long *param_2)

{
  undefined8 uVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined1 uVar4;
  bool bVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined *puVar9;
  ulong *puVar10;
  void *__dest;
  char *pcVar11;
  undefined1 *puVar12;
  size_t sVar13;
  undefined2 *puVar14;
  long lVar15;
  undefined2 *puVar16;
  long lVar17;
  ulong uVar18;
  long *plVar19;
  ulong uVar20;
  double dVar21;
  double dVar22;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined2 local_78;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0 || param_2 == (long *)0x0) goto LAB_001f202c;
  bVar2 = *(byte *)(param_1 + 0x18);
  if (bVar2 == 0x10) {
    lVar17 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
    puVar9 = PTR___stack_chk_guard_005ffe88;
    if (lVar17 == 0) {
      print_string_ptr(*(undefined8 *)(param_1 + 0x20),param_2,0,0);
      return;
    }
    goto LAB_001f2714;
  }
  if (bVar2 < 0x11) {
    if (bVar2 == 4) {
      puVar8 = (undefined4 *)ensure(param_2,5);
      uVar4 = DAT_0020af9c;
      if (puVar8 != (undefined4 *)0x0) {
        *puVar8 = DAT_0020af98;
        *(undefined1 *)(puVar8 + 1) = uVar4;
        goto LAB_001f1ff4;
      }
      goto LAB_001f202c;
    }
    if (bVar2 < 5) {
      if (bVar2 == 1) {
        pcVar11 = (char *)ensure(param_2,6);
        uVar3 = s_false_00202520._4_2_;
        if (pcVar11 == (char *)0x0) goto LAB_001f202c;
        *(undefined4 *)pcVar11 = s_false_00202520._0_4_;
        *(undefined2 *)(pcVar11 + 4) = uVar3;
      }
      else {
        if ((bVar2 != 2) ||
           (puVar8 = (undefined4 *)ensure(param_2,5), uVar4 = DAT_00202534,
           puVar8 == (undefined4 *)0x0)) goto LAB_001f202c;
        *puVar8 = DAT_00202530;
        *(undefined1 *)(puVar8 + 1) = uVar4;
      }
LAB_001f1ff4:
      puVar9 = (undefined *)0x1;
    }
    else {
      if (bVar2 != 8) goto LAB_001f202c;
      dVar21 = *(double *)(param_1 + 0x30);
      local_98 = 0.0;
      local_90 = 0;
      uStack_88 = 0;
      local_80 = 0;
      local_78 = 0;
      if ((NAN(dVar21)) || (dVar22 = ABS(dVar21), 1.79769313486232e+308 < dVar22)) {
        uVar6 = 4;
        local_90 = (ulong)CONCAT14(DAT_0020af9c,DAT_0020af98);
LAB_001f20bc:
        uVar20 = (ulong)(int)uVar6;
        puVar10 = (ulong *)ensure(param_2,uVar20 + 1);
        if (puVar10 != (ulong *)0x0) {
          if (uVar6 != 0) {
            if ((uVar20 - 1 < 7) || ((ulong)((long)puVar10 - ((long)&local_90 + 1)) < 0xf)) {
              uVar18 = 1;
              do {
                bVar5 = uVar20 != uVar18;
                *(undefined1 *)((long)puVar10 + (uVar18 - 1)) =
                     *(undefined1 *)((long)&local_98 + uVar18 + 7);
                uVar18 = uVar18 + 1;
              } while (bVar5);
            }
            else if (uVar20 - 1 < 0xf) {
              lVar17 = 0;
              uVar18 = uVar20;
LAB_001f24a8:
              lVar15 = lVar17 + 8;
              *(undefined8 *)((long)puVar10 + lVar17) = *(undefined8 *)((long)&local_90 + lVar17);
              if (uVar18 != 8) {
LAB_001f24bc:
                *(undefined1 *)((long)puVar10 + lVar15) = *(undefined1 *)((long)&local_90 + lVar15);
                if (lVar15 + 1U < uVar20) {
                  *(undefined1 *)((long)puVar10 + lVar15 + 1U) =
                       *(undefined1 *)((long)&local_90 + lVar15 + 1);
                  if (lVar15 + 2U < uVar20) {
                    *(undefined1 *)((long)puVar10 + lVar15 + 2U) =
                         *(undefined1 *)((long)&local_90 + lVar15 + 2);
                    if (lVar15 + 3U < uVar20) {
                      *(undefined1 *)((long)puVar10 + lVar15 + 3U) =
                           *(undefined1 *)((long)&local_90 + lVar15 + 3);
                      if (lVar15 + 4U < uVar20) {
                        *(undefined1 *)((long)puVar10 + lVar15 + 4U) =
                             *(undefined1 *)((long)&local_90 + lVar15 + 4);
                        if (lVar15 + 5U < uVar20) {
                          *(undefined1 *)((long)puVar10 + lVar15 + 5U) =
                               *(undefined1 *)((long)&local_90 + lVar15 + 5);
                          if (lVar15 + 6U < uVar20) {
                            *(undefined1 *)((long)puVar10 + lVar15 + 6U) =
                                 *(undefined1 *)((long)&local_90 + lVar15 + 6);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            else {
              puVar10[1] = uStack_88;
              *puVar10 = local_90;
              if (uVar6 != 0x10) {
                if (6 < uVar20 - 0x11) {
                  lVar17 = 0x10;
                  uVar18 = uVar20 - 0x10;
                  goto LAB_001f24a8;
                }
                lVar15 = 0x10;
                goto LAB_001f24bc;
              }
            }
            puVar10 = (ulong *)((long)puVar10 + uVar20);
          }
          *(undefined1 *)puVar10 = 0;
          puVar9 = (undefined *)0x1;
          param_2[2] = param_2[2] + uVar20;
          goto LAB_001f2030;
        }
      }
      else {
        if (dVar21 == (double)*(int *)(param_1 + 0x28)) {
          uVar6 = __sprintf_chk(&local_90,2,0x1a,"%d");
          goto LAB_001f20bc;
        }
        uVar6 = __sprintf_chk(dVar21,&local_90,2,0x1a,"%1.15g");
        iVar7 = __isoc99_sscanf(&local_90,&DAT_0020afa8,&local_98);
        if (iVar7 == 1) {
          if (dVar22 < ABS(local_98)) {
            dVar22 = ABS(local_98);
          }
          if (dVar22 * 2.220446049250313e-16 < ABS(local_98 - dVar21)) goto LAB_001f2634;
        }
        else {
LAB_001f2634:
          uVar6 = __sprintf_chk(dVar21,&local_90,2,0x1a,"%1.17g");
        }
        if (uVar6 < 0x1a) goto LAB_001f20bc;
      }
      puVar9 = (undefined *)0x0;
    }
  }
  else {
    if (bVar2 == 0x40) {
      plVar19 = *(long **)(param_1 + 0x10);
      if ((ulong)param_2[3] < 1000) {
        bVar5 = *(int *)((long)param_2 + 0x24) == 0;
        lVar17 = 2;
        if (bVar5) {
          lVar17 = 1;
        }
        uVar1 = 2;
        if (!bVar5) {
          uVar1 = 3;
        }
        puVar12 = (undefined1 *)ensure(param_2,uVar1);
        if (puVar12 != (undefined1 *)0x0) {
          *puVar12 = 0x7b;
          param_2[3] = param_2[3] + 1;
          iVar7 = 0;
          if (*(int *)((long)param_2 + 0x24) != 0) {
            puVar12[1] = 10;
            iVar7 = *(int *)((long)param_2 + 0x24);
          }
          param_2[2] = param_2[2] + lVar17;
          if (plVar19 != (long *)0x0) {
            while( true ) {
              if (iVar7 != 0) {
                lVar17 = ensure(param_2,param_2[3]);
                if (lVar17 == 0) goto LAB_001f202c;
                uVar20 = 0;
                if (param_2[3] != 0) {
                  uVar18 = 0;
                  do {
                    *(undefined1 *)(lVar17 + uVar18) = 9;
                    uVar18 = uVar18 + 1;
                    uVar20 = param_2[3];
                  } while (uVar18 < uVar20);
                }
                param_2[2] = param_2[2] + uVar20;
              }
              iVar7 = print_string_ptr(plVar19[7],param_2);
              if (iVar7 == 0) goto LAB_001f202c;
              if (*param_2 != 0) {
                lVar17 = param_2[2];
                sVar13 = strlen((char *)(*param_2 + lVar17));
                param_2[2] = lVar17 + sVar13;
              }
              lVar17 = (ulong)(*(int *)((long)param_2 + 0x24) != 0) + 1;
              puVar12 = (undefined1 *)ensure(param_2,lVar17);
              if (puVar12 == (undefined1 *)0x0) goto LAB_001f202c;
              *puVar12 = 0x3a;
              if (*(int *)((long)param_2 + 0x24) != 0) {
                puVar12[1] = 9;
              }
              param_2[2] = param_2[2] + lVar17;
              iVar7 = print_value(plVar19,param_2);
              if (iVar7 == 0) goto LAB_001f202c;
              if (*param_2 != 0) {
                lVar17 = param_2[2];
                sVar13 = strlen((char *)(*param_2 + lVar17));
                param_2[2] = lVar17 + sVar13;
              }
              uVar20 = (ulong)(*(int *)((long)param_2 + 0x24) != 0);
              if (*plVar19 != 0) {
                uVar20 = uVar20 + 1;
              }
              puVar14 = (undefined2 *)ensure(param_2,uVar20 + 1);
              if (puVar14 == (undefined2 *)0x0) goto LAB_001f202c;
              puVar16 = puVar14;
              if (*plVar19 != 0) {
                puVar16 = (undefined2 *)((long)puVar14 + 1);
                *(undefined1 *)puVar14 = 0x2c;
              }
              if (*(int *)((long)param_2 + 0x24) == 0) {
                *(undefined1 *)puVar16 = 0;
              }
              else {
                *puVar16 = 10;
              }
              plVar19 = (long *)*plVar19;
              param_2[2] = param_2[2] + uVar20;
              if (plVar19 == (long *)0x0) break;
              iVar7 = *(int *)((long)param_2 + 0x24);
            }
            iVar7 = *(int *)((long)param_2 + 0x24);
          }
          lVar17 = 2;
          if (iVar7 != 0) {
            lVar17 = param_2[3] + 1;
          }
          puVar14 = (undefined2 *)ensure(param_2,lVar17);
          if (puVar14 != (undefined2 *)0x0) {
            if ((*(int *)((long)param_2 + 0x24) != 0) && (param_2[3] != 1)) {
              uVar20 = 0;
              do {
                uVar18 = uVar20;
                *(undefined1 *)((long)puVar14 + uVar18) = 9;
                uVar20 = uVar18 + 1;
              } while (uVar18 + 1 < param_2[3] - 1U);
              puVar14 = (undefined2 *)((long)puVar14 + uVar18 + 1);
            }
            *puVar14 = 0x7d;
            param_2[3] = param_2[3] + -1;
            goto LAB_001f1ff4;
          }
        }
      }
    }
    else if (bVar2 == 0x80) {
      if (*(char **)(param_1 + 0x20) != (char *)0x0) {
        sVar13 = strlen(*(char **)(param_1 + 0x20));
        __dest = (void *)ensure(param_2,sVar13 + 1);
        if (__dest != (void *)0x0) {
          memcpy(__dest,*(void **)(param_1 + 0x20),sVar13 + 1);
          goto LAB_001f1ff4;
        }
      }
    }
    else if (((bVar2 == 0x20) && (plVar19 = *(long **)(param_1 + 0x10), (ulong)param_2[3] < 1000))
            && (puVar12 = (undefined1 *)ensure(param_2,1), puVar12 != (undefined1 *)0x0)) {
      *puVar12 = 0x5b;
      lVar17 = _DAT_0020b170;
      lVar15 = param_2[2] + _DAT_0020b170;
      param_2[3] = param_2[3] + _UNK_0020b178;
      param_2[2] = lVar15;
      while (plVar19 != (long *)0x0) {
        iVar7 = print_value(plVar19,param_2);
        if (iVar7 == 0) goto LAB_001f202c;
        if (*param_2 != 0) {
          lVar15 = param_2[2];
          sVar13 = strlen((char *)(*param_2 + lVar15));
          param_2[2] = lVar15 + sVar13;
        }
        if (*plVar19 == 0) break;
        bVar5 = *(int *)((long)param_2 + 0x24) != 0;
        lVar15 = lVar17;
        if (bVar5) {
          lVar15 = 2;
        }
        uVar1 = 2;
        if (bVar5) {
          uVar1 = 3;
        }
        puVar12 = (undefined1 *)ensure(param_2,uVar1);
        if (puVar12 == (undefined1 *)0x0) goto LAB_001f202c;
        *puVar12 = 0x2c;
        if (*(int *)((long)param_2 + 0x24) == 0) {
          puVar12[1] = 0;
        }
        else {
          *(undefined2 *)(puVar12 + 1) = 0x20;
        }
        plVar19 = (long *)*plVar19;
        param_2[2] = param_2[2] + lVar15;
      }
      puVar14 = (undefined2 *)ensure(param_2,2);
      if (puVar14 != (undefined2 *)0x0) {
        *puVar14 = 0x5d;
        param_2[3] = param_2[3] + -1;
        goto LAB_001f1ff4;
      }
    }
LAB_001f202c:
    puVar9 = (undefined *)0x0;
  }
LAB_001f2030:
  lVar17 = local_68 - *(long *)PTR___stack_chk_guard_005ffe88;
  param_2 = (long *)PTR___stack_chk_guard_005ffe88;
  if (lVar17 == 0) {
    return;
  }
LAB_001f2714:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar9,param_2,0,lVar17);
}

