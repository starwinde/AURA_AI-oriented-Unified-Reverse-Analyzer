
void FUN_0016dca0(long param_1,ulong param_2,undefined8 *param_3)

{
  uint uVar1;
  ulong *puVar2;
  ulong uVar3;
  int iVar4;
  ulong *__ptr;
  ulong *puVar5;
  ulong *puVar6;
  ulong uVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  ulong *puVar10;
  ulonglong uVar11;
  ulong uVar12;
  ulong uVar13;
  char *pcVar14;
  ulong uVar15;
  ulong __size;
  uint uVar16;
  ulong uVar17;
  ulong uVar18;
  ulong uVar19;
  ulong uVar20;
  ulong uVar21;
  char *pcVar22;
  char *pcVar23;
  ulong uVar24;
  ulong uVar25;
  ulong *puVar26;
  ulong uVar27;
  ulong local_2b8;
  char *local_270;
  ulong local_268 [64];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0 || param_2 == 0) {
LAB_0016dfb0:
    uVar9 = 1;
  }
  else {
    __ptr = malloc(0x200);
    if (__ptr != (ulong *)0x0) {
      pcVar23 = (char *)(param_1 + 0x60);
      uVar24 = 0;
      uVar20 = 0;
      pcVar14 = pcVar23;
      uVar27 = 0x40;
      do {
        while( true ) {
          pcVar22 = pcVar14 + -0x40;
          iVar4 = strcmp(pcVar22,"ret");
          if (((iVar4 == 0) || (iVar4 = strcmp(pcVar22,"retf"), iVar4 == 0)) ||
             (iVar4 = strcmp(pcVar22,"retn"), iVar4 == 0)) break;
          if (((pcVar14[-0x40] == 'b') && (pcVar14[-0x3f] == 'x')) && (pcVar14[-0x3e] == '\0')) {
            pcVar22 = pcVar14;
            if (*pcVar14 == ' ' || *pcVar14 == '\t') {
              do {
                pcVar22 = pcVar22 + 1;
              } while (*pcVar22 == ' ' || *pcVar22 == '\t');
            }
            if (((*pcVar22 == 'l') && (pcVar22[1] == 'r')) && (pcVar22[2] == '\0')) break;
          }
          uVar20 = uVar20 + 1;
          pcVar14 = pcVar14 + 0xe0;
          if (param_2 <= uVar20) goto LAB_0016dde0;
        }
        puVar5 = __ptr;
        uVar17 = uVar27;
        if (uVar27 <= uVar24) {
          uVar17 = uVar27 << 1;
          puVar5 = realloc(__ptr,uVar27 << 4);
          if (puVar5 == (ulong *)0x0) goto LAB_0016e2a0;
        }
        puVar5[uVar24] = uVar20;
        uVar20 = uVar20 + 1;
        uVar24 = uVar24 + 1;
        pcVar14 = pcVar14 + 0xe0;
        __ptr = puVar5;
        uVar27 = uVar17;
      } while (uVar20 < param_2);
LAB_0016dde0:
      if (uVar24 == 0) {
LAB_0016df8c:
        free(__ptr);
        goto LAB_0016dfb0;
      }
      puVar5 = malloc(0x800);
      if (puVar5 != (ulong *)0x0) {
        uVar27 = 0;
        uVar20 = 0;
        local_2b8 = 0x80;
        do {
          iVar4 = strcmp(pcVar23 + -0x40,"jmp");
          if (((iVar4 == 0) || ((pcVar23[-0x40] == 'b' && (pcVar23[-0x3f] == '\0')))) ||
             ((pcVar23[-0x40] == 'b' && ((pcVar23[-0x3f] == 'x' && (pcVar23[-0x3e] == '\0')))))) {
            pcVar14 = pcVar23;
            if (*pcVar23 == ' ' || *pcVar23 == '\t') {
              do {
                pcVar14 = pcVar14 + 1;
              } while (*pcVar14 == ' ' || *pcVar14 == '\t');
            }
            if (((*pcVar14 != 'l') || (pcVar14[1] != 'r')) || (pcVar14[2] != '\0')) {
              local_270 = (char *)0x0;
              uVar11 = strtoull(pcVar14,&local_270,0);
              if ((local_270 != pcVar14) && (uVar11 != 0)) {
                puVar6 = puVar5;
                if (local_2b8 <= uVar27) {
                  puVar6 = realloc(puVar5,local_2b8 << 5);
                  local_2b8 = local_2b8 << 1;
                  if (puVar6 == (ulong *)0x0) goto LAB_0016e2cc;
                }
                puVar6[uVar27 * 2] = *(ulong *)(pcVar23 + -0x60);
                puVar6[uVar27 * 2 + 1] = uVar11;
                puVar5 = puVar6;
                uVar27 = uVar27 + 1;
              }
            }
          }
          uVar20 = uVar20 + 1;
          pcVar23 = pcVar23 + 0xe0;
        } while (uVar20 < param_2);
        puVar6 = malloc(0x2180);
        if (puVar6 == (ulong *)0x0) {
LAB_0016e2cc:
          free(__ptr);
          __ptr = puVar5;
        }
        else {
          uVar17 = 0x10;
          __size = 0x2180;
          iVar4 = 0;
          uVar16 = 0;
          uVar20 = 0;
          do {
            uVar7 = __ptr[uVar20];
            uVar25 = 1;
            puVar2 = (ulong *)(param_1 + uVar7 * 0xe0);
            puVar26 = puVar2;
            do {
              if (uVar25 <= uVar7 + 1) {
                uVar15 = *puVar26;
                iVar4 = iVar4 + 1;
                if (uVar27 != 0) {
                  uVar21 = 0;
                  uVar12 = 0;
                  puVar10 = puVar5;
                  do {
                    while ((uVar15 == puVar10[1] &&
                           ((uVar13 = *puVar10, uVar13 < uVar15 || (*puVar2 < uVar13))))) {
                      local_268[uVar21] = uVar13;
                      uVar1 = (uint)uVar21 + 1;
                      uVar21 = (ulong)uVar1;
                      uVar12 = uVar12 + 1;
                      puVar10 = puVar10 + 2;
                      if (0x3f < uVar1 || uVar27 <= uVar12) goto LAB_0016e050;
                    }
                    uVar12 = uVar12 + 1;
                    puVar10 = puVar10 + 2;
                  } while ((uint)uVar21 < 0x40 && uVar12 < uVar27);
LAB_0016e050:
                  if (1 < (uint)uVar21) {
                    if (uVar16 != 0) {
                      puVar10 = puVar6;
                      do {
                        if (uVar15 == *puVar10) goto LAB_0016dee4;
                        puVar10 = puVar10 + 0x43;
                      } while (puVar6 + (ulong)uVar16 * 0x43 != puVar10);
                    }
                    puVar10 = puVar6;
                    if (uVar17 <= uVar16) {
                      __size = uVar17 * 0x430;
                      puVar10 = realloc(puVar6,__size);
                      uVar17 = uVar17 << 1;
                      if (puVar10 == (ulong *)0x0) {
                        free(__ptr);
                        free(puVar5);
                        __ptr = puVar6;
                        goto LAB_0016e2a0;
                      }
                    }
                    puVar6 = puVar10;
                    uVar13 = (ulong)uVar16;
                    uVar18 = uVar13 * 0x218;
                    uVar12 = __size;
                    if (__size < uVar18) {
                      uVar12 = uVar18;
                    }
                    uVar19 = uVar12 + uVar13 * -0x218;
                    puVar6[uVar13 * 0x43] = uVar15;
                    uVar15 = __size;
                    if (__size < uVar19) {
                      uVar15 = uVar19;
                    }
                    *(int *)(puVar6 + uVar13 * 0x43 + 1) = (int)uVar25;
                    uVar3 = (uVar18 - uVar12) + uVar15;
                    if (CARRY8(uVar18 - uVar12,uVar15)) {
                      uVar3 = uVar15;
                    }
                    *(uint *)(puVar6 + uVar13 * 0x43 + 0x42) = (uint)uVar21;
                    uVar3 = uVar3 + (uVar19 - uVar15);
                    if (uVar3 < 0x10) {
                      uVar3 = 0x10;
                    }
                    __memcpy_chk(puVar6 + uVar13 * 0x43 + 2,local_268,uVar21 << 3,uVar3 - 0x10);
                    uVar16 = uVar16 + 1;
                  }
                }
              }
LAB_0016dee4:
              uVar25 = uVar25 + 1;
              puVar26 = puVar26 + -0x1c;
            } while (uVar25 != 5);
            uVar20 = uVar20 + 1;
          } while (uVar20 != uVar24);
          free(__ptr);
          free(puVar5);
          __ptr = puVar6;
          if (uVar16 == 0) goto LAB_0016df8c;
          puVar8 = malloc(0x18);
          if (puVar8 != (undefined8 *)0x0) {
            uVar9 = 0;
            *puVar8 = puVar6;
            *(uint *)(puVar8 + 1) = uVar16;
            *(int *)((long)puVar8 + 0xc) = (int)uVar20;
            *(int *)(puVar8 + 2) = iVar4;
            *param_3 = puVar8;
            goto LAB_0016dfb4;
          }
        }
      }
LAB_0016e2a0:
      free(__ptr);
    }
    uVar9 = 2;
  }
LAB_0016dfb4:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar9,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

