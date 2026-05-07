
/* WARNING: Type propagation algorithm not settling */

void const_refs_run(long param_1,long param_2,ulong param_3,undefined8 param_4,undefined8 *param_5,
                   undefined8 *param_6)

{
  ulong *puVar1;
  byte *pbVar2;
  byte bVar3;
  ushort uVar4;
  long lVar5;
  int iVar6;
  char *pcVar7;
  ushort **ppuVar8;
  undefined8 *puVar9;
  undefined8 uVar10;
  void *pvVar11;
  size_t __size;
  ulong uVar12;
  uint uVar13;
  ulong uVar14;
  void *pvVar15;
  uint uVar16;
  ulong uVar17;
  undefined8 *puVar18;
  int iVar19;
  byte *pbVar20;
  long *plVar21;
  ulong *puVar22;
  byte *__haystack;
  long *plVar23;
  ulong local_a8;
  ulong local_90;
  ulong local_88 [4];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_5 != (undefined8 *)0x0) {
    *param_5 = 0;
    if (param_6 != (undefined8 *)0x0) {
      *param_6 = 0;
    }
    if ((((param_1 != 0) && (*(int *)(param_1 + 0x20) != 0)) && (*(long *)(param_1 + 0x18) != 0)) &&
       (param_2 != 0 && param_3 != 0)) {
      pbVar20 = (byte *)(param_2 + 0x60);
      local_a8 = 0;
      pvVar15 = (void *)0x0;
      uVar14 = 0;
      uVar17 = 0;
      do {
        if (*pbVar20 != 0) {
          iVar19 = 0;
          __haystack = pbVar20;
LAB_0016a9b0:
          do {
            while (pcVar7 = strstr((char *)__haystack,"0x"), pcVar7 != (char *)0x0) {
              pbVar2 = (byte *)(pcVar7 + 2);
              local_90 = 0;
              ppuVar8 = __ctype_b_loc();
              bVar3 = pcVar7[2];
              __haystack = pbVar2;
              if (((*ppuVar8)[bVar3] >> 0xc & 1) != 0) {
                do {
                  __haystack = __haystack + 1;
                  bVar3 = *__haystack;
                } while (((*ppuVar8)[bVar3] >> 0xc & 1) != 0);
                if (pbVar2 < __haystack) {
                  iVar6 = __isoc99_sscanf(pcVar7,"0x%lx",&local_90);
                  if ((iVar6 == 1) &&
                     ((iVar19 < 1 ||
                      ((local_88[0] != local_90 &&
                       ((iVar19 == 1 ||
                        ((local_88[1] != local_90 && ((iVar19 != 3 || (local_88[2] != local_90))))))
                       )))))) {
                    uVar13 = (uint)*__haystack;
                    local_88[iVar19] = local_90;
                    iVar19 = iVar19 + 1;
                    goto LAB_0016ac60;
                  }
                  bVar3 = *__haystack;
                }
              }
joined_r0x0016ac90:
              if (bVar3 == 0) {
LAB_0016aa04:
                if (iVar19 < 1) goto LAB_0016aa70;
                goto LAB_0016aa0c;
              }
            }
            pcVar7 = strchr((char *)__haystack,0x23);
            if (pcVar7 == (char *)0x0) goto LAB_0016aa04;
            bVar3 = pcVar7[1];
            __haystack = (byte *)(pcVar7 + 1);
            if (bVar3 == 0x30) {
              if ((pcVar7[2] & 0xdfU) == 0x58) goto LAB_0016a9b0;
              ppuVar8 = __ctype_b_loc();
              uVar4 = (*ppuVar8)[0x30];
            }
            else {
              ppuVar8 = __ctype_b_loc();
              uVar4 = (*ppuVar8)[bVar3];
            }
            if ((uVar4 >> 0xb & 1) == 0) goto joined_r0x0016ac90;
            local_90 = 0;
            iVar6 = __isoc99_sscanf(__haystack,&DAT_001fa500,&local_90);
            if ((iVar6 == 1) &&
               ((iVar19 < 1 ||
                ((local_88[0] != local_90 &&
                 ((iVar19 == 1 ||
                  ((local_88[1] != local_90 && ((iVar19 != 3 || (local_88[2] != local_90))))))))))))
            {
              local_88[iVar19] = local_90;
              iVar19 = iVar19 + 1;
            }
            uVar12 = (ulong)(byte)pcVar7[1];
            uVar4 = (*ppuVar8)[uVar12];
            while (uVar13 = (uint)uVar12, (uVar4 >> 0xb & 1) != 0) {
              __haystack = __haystack + 1;
              uVar12 = (ulong)*__haystack;
              uVar4 = (*ppuVar8)[uVar12];
            }
LAB_0016ac60:
            if (uVar13 == 0) goto LAB_0016aa04;
          } while (iVar19 != 4);
LAB_0016aa0c:
          plVar21 = *(long **)(param_1 + 0x18);
          puVar22 = local_88;
          puVar1 = puVar22 + iVar19;
LAB_0016aa18:
          uVar12 = *puVar22;
          if ((plVar21 == (long *)0x0) || (*(uint *)(param_1 + 0x20) == 0)) goto joined_r0x0016ab5c;
          plVar23 = plVar21;
LAB_0016aa38:
          if (((plVar23[3] == 0) || (uVar12 < (ulong)plVar23[1])) ||
             ((ulong)(plVar23[3] + plVar23[1]) <= uVar12)) goto LAB_0016aa58;
          pcVar7 = (char *)*plVar23;
          if (pcVar7 == (char *)0x0) goto joined_r0x0016ab5c;
          uVar13 = (uint)uVar14;
          uVar16 = (uint)uVar17;
          pvVar11 = pvVar15;
          if (uVar16 <= uVar13) {
            if (uVar16 == 0) {
              __size = 0x800;
              uVar17 = 0x40;
            }
            else {
              uVar17 = (ulong)(uVar16 << 1);
              __size = uVar17 << 5;
            }
            pvVar11 = realloc(pvVar15,__size);
            if (pvVar11 != (void *)0x0) {
              pcVar7 = (char *)*plVar23;
              goto LAB_0016ab14;
            }
            if (uVar13 != 0) {
              puVar9 = (undefined8 *)((long)pvVar15 + 0x18);
              do {
                puVar18 = puVar9 + 4;
                free((void *)*puVar9);
                puVar9 = puVar18;
              } while ((undefined8 *)((long)pvVar15 + 0x18) + uVar14 * 4 != puVar18);
            }
            free(pvVar15);
            if (param_6 != (undefined8 *)0x0) {
              pcVar7 = strdup("const_refs: allocation failed");
              *param_6 = pcVar7;
              uVar10 = 2;
              goto LAB_0016aadc;
            }
            goto LAB_0016adc8;
          }
LAB_0016ab14:
          uVar16 = *(uint *)(plVar23 + 6);
          lVar5 = uVar14 * 0x20;
          iVar19 = 2 - (uVar16 & 1);
          *(undefined8 *)((long)pvVar11 + lVar5) = *(undefined8 *)(pbVar20 + -0x60);
          if ((uVar16 & 4) != 0) {
            iVar19 = 0;
          }
          *(ulong *)((long)pvVar11 + lVar5 + 8) = uVar12;
          *(int *)((long)pvVar11 + lVar5 + 0x10) = iVar19;
          pcVar7 = strdup(pcVar7);
          *(char **)((long)pvVar11 + lVar5 + 0x18) = pcVar7;
          if (pcVar7 != (char *)0x0) {
            uVar14 = (ulong)(uVar13 + 1);
            pvVar15 = pvVar11;
            goto joined_r0x0016ab5c;
          }
          puVar9 = (undefined8 *)((long)pvVar11 + 0x18);
          if (uVar13 != 0) {
            do {
              puVar18 = puVar9 + 4;
              free((void *)*puVar9);
              puVar9 = puVar18;
            } while (puVar18 != (undefined8 *)((long)pvVar11 + lVar5 + 0x18));
          }
          free(pvVar11);
          if (param_6 != (undefined8 *)0x0) {
            pcVar7 = strdup("const_refs: strdup failed");
            *param_6 = pcVar7;
            uVar10 = 2;
            goto LAB_0016aadc;
          }
          goto LAB_0016adc8;
        }
LAB_0016aa70:
        pbVar20 = pbVar20 + 0xe0;
        local_a8 = local_a8 + 1;
      } while (local_a8 < param_3);
      uVar13 = (uint)uVar14;
      if (uVar13 == 0) {
        free(pvVar15);
        puVar9 = malloc(0x10);
        if (puVar9 != (undefined8 *)0x0) {
          *puVar9 = 0;
          *(undefined4 *)(puVar9 + 1) = 0;
          goto LAB_0016aab0;
        }
      }
      else {
        if (((uint)uVar17 <= uVar13) ||
           (pvVar11 = realloc(pvVar15,uVar14 << 5), pvVar11 == (void *)0x0)) {
          pvVar11 = pvVar15;
        }
        puVar9 = malloc(0x10);
        if (puVar9 != (undefined8 *)0x0) {
          *puVar9 = pvVar11;
          *(uint *)(puVar9 + 1) = uVar13;
LAB_0016aab0:
          uVar10 = 0;
          *param_5 = puVar9;
          goto LAB_0016aadc;
        }
        pvVar15 = pvVar11;
        do {
          puVar9 = (undefined8 *)((long)pvVar15 + 0x18);
          pvVar15 = (void *)((long)pvVar15 + 0x20);
          free((void *)*puVar9);
        } while (pvVar15 != (void *)((long)pvVar11 + uVar14 * 0x20));
        free(pvVar11);
      }
      if (param_6 != (undefined8 *)0x0) {
        pcVar7 = strdup("const_refs: allocation failed for result");
        *param_6 = pcVar7;
      }
LAB_0016adc8:
      uVar10 = 2;
      goto LAB_0016aadc;
    }
  }
  uVar10 = 1;
LAB_0016aadc:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar10,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_0016aa58:
  plVar23 = plVar23 + 7;
  if (plVar23 == plVar21 + (ulong)*(uint *)(param_1 + 0x20) * 7) goto joined_r0x0016ab5c;
  goto LAB_0016aa38;
joined_r0x0016ab5c:
  puVar22 = puVar22 + 1;
  if (puVar22 == puVar1) goto LAB_0016aa70;
  goto LAB_0016aa18;
}

