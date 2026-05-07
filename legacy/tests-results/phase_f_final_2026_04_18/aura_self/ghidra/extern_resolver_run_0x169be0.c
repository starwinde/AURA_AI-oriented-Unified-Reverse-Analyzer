
void extern_resolver_run(long *param_1)

{
  size_t sVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int *piVar6;
  undefined8 *__ptr;
  char *pcVar8;
  ulong uVar9;
  long lVar10;
  void *pvVar11;
  size_t sVar12;
  size_t __n;
  long *plVar13;
  undefined8 uVar14;
  undefined8 *in_x4;
  ulong uVar15;
  undefined8 *in_x5;
  ulong uVar16;
  uint uVar17;
  undefined8 *puVar18;
  long lVar19;
  uint uVar20;
  undefined8 *puVar21;
  ulong uVar22;
  long *plVar23;
  uint uVar24;
  undefined8 *puVar25;
  ulong uVar26;
  ulong uVar27;
  void *local_98;
  undefined8 *local_70;
  long local_68;
  int *piVar7;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (long *)0x0 || in_x4 == (undefined8 *)0x0) {
LAB_00169d9c:
    uVar14 = 1;
    goto LAB_00169da0;
  }
  *in_x4 = 0;
  if (in_x5 != (undefined8 *)0x0) {
    *in_x5 = 0;
  }
  if ((((int)param_1[1] != 1) || (*param_1 == 0)) ||
     (local_70 = (undefined8 *)reloc_parse(param_1), local_70 == (undefined8 *)0x0))
  goto LAB_00169d9c;
  uVar17 = *(uint *)(local_70 + 1);
  if (uVar17 == 0) {
LAB_00169f50:
    reloc_table_destroy(&local_70);
    goto LAB_00169d9c;
  }
  puVar18 = (undefined8 *)*local_70;
  uVar20 = 0;
  piVar6 = (int *)(puVar18 + 3);
  do {
    piVar7 = piVar6 + 8;
    if (*piVar6 == 4) {
      uVar20 = uVar20 + 1;
    }
    piVar6 = piVar7;
  } while (piVar7 != (int *)((long)(puVar18 + 3) + (ulong)uVar17 * 8 * 4));
  if (uVar20 == 0) goto LAB_00169f50;
  __ptr = calloc((ulong)uVar20,0x20);
  if (__ptr != (undefined8 *)0x0) {
    uVar24 = 0;
    uVar27 = 0;
    do {
      uVar22 = uVar27;
      if (*(int *)(puVar18 + 3) == 4) {
        pcVar8 = (char *)0x0;
        if ((char *)puVar18[1] != (char *)0x0) {
          pcVar8 = strdup((char *)puVar18[1]);
        }
        uVar14 = *puVar18;
        uVar22 = (ulong)((int)uVar27 + 1);
        __ptr[uVar27 * 4] = pcVar8;
        __ptr[uVar27 * 4 + 1] = uVar14;
        __ptr[uVar27 * 4 + 2] = uVar14;
        __ptr[uVar27 * 4 + 3] = 0;
      }
      uVar24 = uVar24 + 1;
      puVar18 = puVar18 + 4;
      uVar27 = uVar22;
    } while (uVar24 < uVar17 && (uint)uVar22 < uVar20);
    reloc_table_destroy(&local_70);
    puVar18 = (undefined8 *)param_1[3];
    if (*(uint *)(param_1 + 4) != 0) {
      puVar25 = puVar18 + (ulong)*(uint *)(param_1 + 4) * 7;
      puVar21 = puVar18;
      do {
        if (((char *)*puVar21 != (char *)0x0) &&
           (iVar5 = strcmp((char *)*puVar21,".dynamic"), iVar5 == 0)) {
          plVar23 = (long *)puVar21[5];
          if ((plVar23 != (long *)0x0) && (uVar27 = puVar21[3], uVar27 != 0)) goto LAB_00169de8;
          break;
        }
        puVar21 = puVar21 + 7;
      } while (puVar25 != puVar21);
    }
    goto LAB_00169d48;
  }
  reloc_table_destroy(&local_70);
  if (in_x5 != (undefined8 *)0x0) {
    pcVar8 = strdup("extern_resolver: allocation failed for entries");
    *in_x5 = pcVar8;
  }
  goto LAB_0016a12c;
  while (puVar18 = puVar18 + 7, puVar25 != puVar18) {
LAB_00169de8:
    if (((char *)*puVar18 != (char *)0x0) &&
       (iVar5 = strcmp((char *)*puVar18,".dynstr"), iVar5 == 0)) {
      if ((puVar18[5] != 0) && ((puVar18[3] != 0 && (4 < *(ulong *)(*param_1 + 0x10))))) {
        cVar2 = *(char *)(*(long *)(*param_1 + 8) + 4);
        if (cVar2 == '\x02') {
          if (0xf < uVar27) {
            uVar17 = 0;
            uVar9 = 0;
            plVar13 = plVar23;
            goto LAB_0016a020;
          }
        }
        else if (7 < uVar27) {
          uVar17 = 0;
          uVar9 = 0;
          plVar13 = plVar23;
          goto LAB_00169e6c;
        }
      }
      break;
    }
  }
  goto LAB_00169d48;
  while( true ) {
    uVar9 = uVar9 + 1;
    if (*plVar13 == 1) {
      uVar17 = uVar17 + 1;
    }
    plVar13 = plVar13 + 2;
    if (uVar9 == uVar27 >> 4) break;
LAB_0016a020:
    if (*plVar13 == 0) {
      uVar16 = 0x10;
      uVar9 = uVar27 >> 4;
      goto LAB_00169e78;
    }
  }
  uVar16 = 0x10;
  goto LAB_00169e78;
code_r0x00169f34:
  plVar23 = (long *)puVar21[5];
  plVar13 = (long *)((long)plVar23 + lVar19);
  goto joined_r0x00169ecc;
  while( true ) {
    uVar9 = uVar9 + 1;
    if ((int)*plVar13 == 1) {
      uVar17 = uVar17 + 1;
    }
    plVar13 = plVar13 + 1;
    if (uVar27 >> 3 == uVar9) break;
LAB_00169e6c:
    if ((int)*plVar13 == 0) {
      uVar16 = 8;
      uVar9 = uVar27 >> 3;
      goto LAB_00169e78;
    }
  }
  uVar16 = 8;
LAB_00169e78:
  if ((uVar17 == 0) || (local_98 = calloc((ulong)uVar17,8), local_98 == (void *)0x0)) {
LAB_00169d48:
    uVar26 = 0;
    local_98 = (void *)0x0;
  }
  else if (uVar27 < uVar16) {
    uVar26 = 0;
    local_98 = realloc(local_98,0);
  }
  else {
    lVar19 = 0;
    uVar26 = 0;
    uVar27 = 0;
    plVar13 = plVar23;
joined_r0x00169ecc:
    if (cVar2 == '\x02') {
      lVar10 = *(long *)((long)plVar23 + lVar19);
      uVar15 = plVar13[1];
    }
    else {
      lVar10 = (long)*(int *)((long)plVar23 + lVar19);
      uVar15 = (ulong)*(uint *)((long)plVar13 + 4);
    }
    if (lVar10 != 0) {
      if (lVar10 == 1) {
        if ((ulong)puVar18[3] <= uVar15) {
          aura_log(2,0,0,"DT_NEEDED offset %lu out of .dynstr range (%lu)");
          goto LAB_00169f20;
        }
        sVar12 = puVar18[3] - uVar15;
        sVar1 = 0;
        do {
          __n = sVar1;
          if (((char *)(puVar18[5] + uVar15))[__n] == '\0') {
            if (__n == 0) goto LAB_00169f20;
            break;
          }
          sVar1 = __n + 1;
          __n = sVar12;
        } while (sVar12 != sVar1);
        pcVar8 = strndup((char *)(puVar18[5] + uVar15),__n);
        *(char **)((long)local_98 + uVar26 * 8) = pcVar8;
        if (pcVar8 != (char *)0x0) {
          uVar26 = (ulong)((uint)uVar26 + 1);
          goto LAB_00169f20;
        }
        for (lVar19 = 0; (uint)lVar19 < (uint)uVar26; lVar19 = lVar19 + 1) {
          free(*(void **)((long)local_98 + lVar19 * 8));
        }
        free(local_98);
        goto LAB_00169d48;
      }
LAB_00169f20:
      uVar27 = uVar27 + 1;
      lVar19 = lVar19 + uVar16;
      bVar3 = false;
      bVar4 = false;
      if (uVar27 < uVar9) {
        bVar4 = (uint)uVar26 <= uVar17;
        bVar3 = uVar17 == (uint)uVar26;
      }
      if (bVar4 && !bVar3) goto code_r0x00169f34;
    }
    if (((uint)uVar26 < uVar17) &&
       (pvVar11 = realloc(local_98,uVar26 << 3), pvVar11 != (void *)0x0 || (uint)uVar26 == 0)) {
      local_98 = pvVar11;
    }
  }
  puVar18 = malloc(0x20);
  if (puVar18 == (undefined8 *)0x0) {
    for (puVar18 = __ptr; __ptr + uVar22 * 4 != puVar18; puVar18 = puVar18 + 4) {
      free((void *)*puVar18);
      free((void *)puVar18[3]);
    }
    free(__ptr);
    for (lVar19 = 0; (uint)lVar19 < (uint)uVar26; lVar19 = lVar19 + 1) {
      free(*(void **)((long)local_98 + lVar19 * 8));
    }
    free(local_98);
    if (in_x5 != (undefined8 *)0x0) {
      pcVar8 = strdup("extern_resolver: allocation failed for result");
      *in_x5 = pcVar8;
    }
LAB_0016a12c:
    uVar14 = 2;
  }
  else {
    uVar14 = 0;
    *puVar18 = __ptr;
    *(uint *)(puVar18 + 1) = (uint)uVar22;
    *(uint *)(puVar18 + 3) = (uint)uVar26;
    *in_x4 = puVar18;
    puVar18[2] = local_98;
  }
LAB_00169da0:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar14,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

