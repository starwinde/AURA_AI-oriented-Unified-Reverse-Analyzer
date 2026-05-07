
int fd_datascan_add_candidates
              (long param_1,long param_2,ulong param_3,ulong param_4,uint param_5,long param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  long lVar4;
  ulong uVar5;
  ulong uVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  ulong uVar9;
  char *pcVar10;
  long lVar11;
  long lVar12;
  undefined **ppuVar13;
  int iVar14;
  ulong local_1a0;
  int local_184;
  undefined1 auStack_148 [224];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar14 = 0;
  if (((param_2 != 0 && param_3 <= param_4) && (param_2 == 0 || param_4 != param_3)) && param_1 != 0
     ) {
    uVar1 = *(uint *)(param_1 + 0xc);
    if (*(uint *)(param_1 + 0xc) == 0) {
      uVar1 = param_5;
    }
    local_1a0 = 8;
    if ((uVar1 < 7) && (local_1a0 = 8, (0x6aUL >> ((ulong)uVar1 & 0x3f) & 1) != 0)) {
      local_1a0 = 4;
    }
    lVar12 = 0;
    iVar14 = 0;
    do {
      pcVar10 = (&G2_NAMES_1)[lVar12];
      if (pcVar10 != (char *)0x0) {
        puVar7 = *(undefined8 **)(param_1 + 0x18);
        if (*(uint *)(param_1 + 0x20) != 0) {
          puVar8 = puVar7 + (ulong)*(uint *)(param_1 + 0x20) * 7;
          do {
            if (((char *)*puVar7 != (char *)0x0) &&
               (iVar2 = strcmp((char *)*puVar7,pcVar10), iVar2 == 0)) {
              lVar4 = puVar7[5];
              if ((lVar4 != 0) && (uVar9 = puVar7[4], local_1a0 <= uVar9)) {
                lVar11 = 0;
                iVar2 = 0;
                if (local_1a0 == 8) {
                  while( true ) {
                    uVar6 = *(ulong *)(lVar4 + lVar11);
                    if ((param_3 <= uVar6 && uVar6 < param_4) &&
                       (iVar3 = candidateset_add(param_2,uVar6,5,0x28,0), iVar3 != 0)) {
                      iVar2 = iVar2 + 1;
                    }
                    uVar6 = lVar11 + 0x10;
                    lVar11 = lVar11 + 8;
                    if (uVar9 < uVar6) break;
                    lVar4 = puVar7[5];
                  }
                  iVar14 = iVar14 + iVar2;
                }
                else {
                  while( true ) {
                    uVar6 = (ulong)*(uint *)(lVar4 + lVar11);
                    if ((uVar6 < param_4 && param_3 <= uVar6) &&
                       (iVar3 = candidateset_add(param_2,uVar6,5,0x28,0), iVar3 != 0)) {
                      iVar2 = iVar2 + 1;
                    }
                    uVar6 = lVar11 + 8;
                    lVar11 = lVar11 + 4;
                    if (uVar9 < uVar6) break;
                    lVar4 = puVar7[5];
                  }
                  iVar14 = iVar14 + iVar2;
                }
              }
              break;
            }
            puVar7 = puVar7 + 7;
          } while (puVar7 != puVar8);
        }
      }
      lVar12 = lVar12 + 1;
    } while (lVar12 != 3);
    if ((param_6 != 0 && param_5 != 0) && (lVar12 = disasm_init(), lVar12 != 0)) {
      ppuVar13 = &G3_NAMES_0;
      do {
        pcVar10 = *ppuVar13;
        if (pcVar10 != (char *)0x0) {
          puVar7 = *(undefined8 **)(param_1 + 0x18);
          if (*(uint *)(param_1 + 0x20) != 0) {
            puVar8 = puVar7 + (ulong)*(uint *)(param_1 + 0x20) * 7;
            do {
              if (((char *)*puVar7 != (char *)0x0) &&
                 (iVar2 = strcmp((char *)*puVar7,pcVar10), iVar2 == 0)) {
                lVar4 = puVar7[5];
                if ((lVar4 != 0) && (uVar9 = puVar7[4], local_1a0 <= uVar9)) {
                  if (local_1a0 == 8) {
                    lVar11 = 0;
                    local_184 = 0;
                    while( true ) {
                      uVar6 = *(ulong *)(lVar4 + lVar11);
                      if ((param_3 <= uVar6 && uVar6 < param_4) &&
                         (uVar6 - param_3 < param_4 - param_3)) {
                        uVar5 = param_4 - uVar6;
                        if (0x10 < uVar5) {
                          uVar5 = 0x10;
                        }
                        iVar2 = disasm_run(lVar12,param_6 + (uVar6 - param_3),uVar5,uVar6,
                                           auStack_148,1);
                        if ((0 < iVar2) &&
                           (iVar2 = candidateset_add(param_2,uVar6,5,0x28,0), iVar2 != 0)) {
                          local_184 = local_184 + 1;
                        }
                      }
                      uVar6 = lVar11 + 0x10;
                      lVar11 = lVar11 + 8;
                      if (uVar9 < uVar6) break;
                      lVar4 = puVar7[5];
                    }
                  }
                  else {
                    lVar11 = 0;
                    local_184 = 0;
                    while( true ) {
                      uVar6 = (ulong)*(uint *)(lVar4 + lVar11);
                      if ((uVar6 < param_4 && param_3 <= uVar6) &&
                         (uVar6 - param_3 < param_4 - param_3)) {
                        uVar5 = param_4 - uVar6;
                        if (0x10 < uVar5) {
                          uVar5 = 0x10;
                        }
                        iVar2 = disasm_run(lVar12,param_6 + (uVar6 - param_3),uVar5,uVar6,
                                           auStack_148,1);
                        if ((0 < iVar2) &&
                           (iVar2 = candidateset_add(param_2,uVar6,5,0x28,0), iVar2 != 0)) {
                          local_184 = local_184 + 1;
                        }
                      }
                      uVar6 = lVar11 + 8;
                      lVar11 = lVar11 + 4;
                      if (uVar9 < uVar6) break;
                      lVar4 = puVar7[5];
                    }
                  }
                  iVar14 = iVar14 + local_184;
                }
                break;
              }
              puVar7 = puVar7 + 7;
            } while (puVar7 != puVar8);
          }
        }
        ppuVar13 = ppuVar13 + 1;
      } while (ppuVar13 != &REG_TABLE);
      disasm_destroy(lVar12);
    }
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar14;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

