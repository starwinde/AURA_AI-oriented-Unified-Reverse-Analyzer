
void elf_scalar_refs_run(long *param_1,long param_2,ulong param_3,undefined8 param_4,
                        undefined8 *param_5,undefined8 *param_6)

{
  byte bVar1;
  uint uVar2;
  byte *__nptr;
  uint uVar3;
  undefined8 *__ptr;
  void *pvVar4;
  ushort **ppuVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined8 *puVar9;
  char *pcVar10;
  undefined8 *puVar11;
  int __base;
  undefined8 uVar12;
  byte *pbVar13;
  ulong uVar14;
  byte *pbVar15;
  char *pcVar16;
  long local_78;
  byte *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 != (long *)0x0) && ((int)param_1[1] == 1)) && (param_2 != 0 && param_3 != 0)) {
    local_78 = 0;
    if (*param_1 != 0) {
      local_78 = reloc_parse();
    }
    __ptr = calloc(1,0x10);
    if (__ptr == (undefined8 *)0x0) {
      reloc_table_destroy(&local_78);
      if (param_6 != (undefined8 *)0x0) {
        pcVar16 = strdup("OOM: result alloc failed");
        *param_6 = pcVar16;
      }
    }
    else {
      *(undefined4 *)((long)__ptr + 0xc) = 0x80;
      pvVar4 = calloc(0x80,0x28);
      *__ptr = pvVar4;
      if (pvVar4 != (void *)0x0) {
        pbVar13 = (byte *)(param_2 + 0x60);
        uVar14 = 0;
LAB_0016c068:
        bVar1 = *pbVar13;
        __nptr = pbVar13;
        while (bVar1 != 0) {
          if ((bVar1 == 0x30) && (__base = 0x10, (__nptr[1] & 0xdf) == 0x58)) {
LAB_0016c0a8:
            local_70 = (byte *)0x0;
            uVar6 = strtoull((char *)__nptr,(char **)&local_70,__base);
            pbVar15 = __nptr;
            if (local_70 != __nptr) {
              if (uVar6 != 0) {
                if ((local_78 == 0) || (lVar8 = reloc_lookup(local_78,uVar6), lVar8 == 0)) {
                  uVar3 = *(uint *)(param_1 + 4);
                }
                else {
                  pcVar16 = *(char **)(lVar8 + 8);
                  uVar3 = *(uint *)(param_1 + 4);
                  if ((pcVar16 != (char *)0x0) && (*pcVar16 != '\0')) {
                    if (uVar3 == 0) goto LAB_0016c228;
                    puVar11 = (undefined8 *)param_1[3];
                    puVar9 = puVar11 + (ulong)uVar3 * 7;
                    goto LAB_0016c200;
                  }
                }
                if (uVar3 != 0) {
                  puVar11 = (undefined8 *)param_1[3];
                  puVar9 = puVar11 + (ulong)uVar3 * 7;
                  goto LAB_0016c1b0;
                }
                break;
              }
              pbVar15 = local_70;
              if (local_70 == (byte *)0x0) {
                pbVar15 = __nptr + 1;
              }
            }
          }
          else {
            ppuVar5 = __ctype_b_loc();
            if ((((*ppuVar5)[bVar1] >> 0xb & 1) != 0) &&
               ((__nptr <= pbVar13 || (((*ppuVar5)[__nptr[-1]] >> 10 & 1) == 0)))) {
              __base = 0;
              goto LAB_0016c0a8;
            }
            pbVar15 = __nptr + 1;
          }
          __nptr = pbVar15;
          bVar1 = *pbVar15;
        }
        goto joined_r0x0016c2dc;
      }
      free(__ptr);
      reloc_table_destroy(&local_78);
      if (param_6 != (undefined8 *)0x0) {
        pcVar16 = strdup("OOM: entries alloc failed");
        *param_6 = pcVar16;
      }
    }
    uVar7 = 2;
    goto LAB_0016c12c;
  }
LAB_0016c128:
  uVar7 = 1;
LAB_0016c12c:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar7,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  while (puVar11 = puVar11 + 7, puVar9 != puVar11) {
LAB_0016c200:
    if (((ulong)puVar11[1] <= uVar6) && (uVar6 < (ulong)(puVar11[1] + puVar11[3]))) {
      uVar7 = *puVar11;
      goto LAB_0016c22c;
    }
  }
LAB_0016c228:
  uVar7 = 0;
LAB_0016c22c:
  uVar3 = *(uint *)(__ptr + 1);
  uVar12 = *(undefined8 *)(pbVar13 + -0x60);
  pvVar4 = (void *)*__ptr;
  if (*(uint *)((long)__ptr + 0xc) <= uVar3) {
    uVar2 = *(uint *)((long)__ptr + 0xc) << 1;
    if (uVar2 < 0x40) {
      uVar2 = 0x40;
    }
    pvVar4 = realloc(pvVar4,(ulong)uVar2 * 0x28);
    if (pvVar4 == (void *)0x0) goto joined_r0x0016c2dc;
    *__ptr = pvVar4;
    uVar3 = *(uint *)(__ptr + 1);
    *(uint *)((long)__ptr + 0xc) = uVar2;
  }
  lVar8 = (ulong)uVar3 * 0x28;
  *(uint *)(__ptr + 1) = uVar3 + 1;
  *(undefined8 *)((long)pvVar4 + lVar8) = uVar12;
  *(ulonglong *)((long)pvVar4 + lVar8 + 8) = uVar6;
  pcVar16 = strdup(pcVar16);
  *(char **)((long)pvVar4 + lVar8 + 0x10) = pcVar16;
  *(undefined8 *)((long)pvVar4 + lVar8 + 0x18) = uVar7;
  *(undefined4 *)((long)pvVar4 + lVar8 + 0x20) = 1;
  goto joined_r0x0016c2dc;
  while (puVar11 = puVar11 + 7, puVar9 != puVar11) {
LAB_0016c1b0:
    if (((ulong)puVar11[1] <= uVar6) && (uVar6 < (ulong)(puVar11[1] + puVar11[3]))) {
      pcVar16 = (char *)*puVar11;
      if (pcVar16 == (char *)0x0) break;
      uVar3 = *(uint *)(__ptr + 1);
      uVar7 = *(undefined8 *)(pbVar13 + -0x60);
      pvVar4 = (void *)*__ptr;
      if (*(uint *)((long)__ptr + 0xc) <= uVar3) {
        uVar2 = *(uint *)((long)__ptr + 0xc) << 1;
        if (uVar2 < 0x40) {
          uVar2 = 0x40;
        }
        pvVar4 = realloc(pvVar4,(ulong)uVar2 * 0x28);
        if (pvVar4 == (void *)0x0) break;
        *__ptr = pvVar4;
        uVar3 = *(uint *)(__ptr + 1);
        *(uint *)((long)__ptr + 0xc) = uVar2;
      }
      lVar8 = (ulong)uVar3 * 0x28;
      *(uint *)(__ptr + 1) = uVar3 + 1;
      *(undefined8 *)((long)pvVar4 + lVar8) = uVar7;
      *(ulonglong *)((long)pvVar4 + lVar8 + 8) = uVar6;
      pcVar10 = strdup(pcVar16);
      *(char **)((long)pvVar4 + lVar8 + 0x10) = pcVar10;
      *(char **)((long)pvVar4 + lVar8 + 0x18) = pcVar16;
      *(undefined4 *)((long)pvVar4 + lVar8 + 0x20) = 2;
      break;
    }
  }
joined_r0x0016c2dc:
  pbVar13 = pbVar13 + 0xe0;
  uVar14 = uVar14 + 1;
  if (param_3 <= uVar14) goto LAB_0016c0f0;
  goto LAB_0016c068;
LAB_0016c0f0:
  reloc_table_destroy(&local_78);
  if (*(int *)(__ptr + 1) != 0) {
    uVar7 = 0;
    *param_5 = __ptr;
    goto LAB_0016c12c;
  }
  free((void *)*__ptr);
  free(__ptr);
  goto LAB_0016c128;
}

