
undefined8 * dfg_analyze(long *param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *pvVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint *puVar9;
  undefined4 *puVar10;
  uint *puVar11;
  uint uVar12;
  ulong uVar13;
  uint *puVar14;
  ulong uVar15;
  int iVar16;
  ulong uVar17;
  void *__ptr;
  long lVar18;
  uint *__ptr_00;
  uint uVar19;
  long lVar20;
  uint uVar21;
  long lVar22;
  ulong uVar23;
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined8 *local_80;
  undefined8 *local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (long *)0x0) {
    local_80 = calloc(1,0x10);
    local_70 = local_80;
    if (local_80 == (undefined8 *)0x0) {
      local_80 = (undefined8 *)0x0;
      goto LAB_00149904;
    }
    uVar19 = *(uint *)(param_1 + 1);
    *(uint *)(local_80 + 1) = uVar19;
    if (uVar19 == 0) goto LAB_00149904;
    pvVar6 = calloc((ulong)uVar19,0x20);
    lVar18 = 0;
    *local_80 = pvVar6;
    if (pvVar6 != (void *)0x0) {
      do {
        puVar11 = (uint *)((long)pvVar6 + lVar18 * 0x20);
        lVar1 = *param_1 + lVar18 * 0x20;
        uVar21 = *(uint *)(lVar1 + 0x18);
        puVar11[6] = uVar21;
        uVar12 = 0;
        if (uVar21 == 0) goto LAB_0014995c;
        pvVar6 = calloc((ulong)uVar21,8);
        *(void **)(puVar11 + 4) = pvVar6;
        if (pvVar6 == (void *)0x0) {
          dfg_destroy(&local_70);
          local_80 = (undefined8 *)0x0;
          goto LAB_00149904;
        }
        lVar22 = 0;
        lVar20 = 0;
        while( true ) {
          pvVar6 = (void *)((long)pvVar6 + lVar20 * 8);
          lVar20 = lVar20 + 1;
          dfg_extract_def_use(*(long *)(lVar1 + 0x10) + lVar22,pvVar6,(long)pvVar6 + 4);
          lVar22 = lVar22 + 0xe0;
          if (*(uint *)(lVar1 + 0x18) <= (uint)lVar20) break;
          pvVar6 = *(void **)(puVar11 + 4);
        }
        uVar21 = puVar11[6];
        uVar19 = *(uint *)(param_1 + 1);
        if (uVar21 == 0) {
          uVar12 = 0;
LAB_0014995c:
          *puVar11 = uVar12;
          puVar11[1] = uVar12;
          if (uVar19 <= (int)lVar18 + 1U) goto LAB_00149abc;
        }
        else {
          uVar8 = uVar21 - 1;
          puVar10 = *(undefined4 **)(puVar11 + 4);
          if (uVar8 < 5) {
            uVar12 = 0;
            uVar8 = 0;
          }
          else {
            puVar7 = puVar10;
            auVar25 = ZEXT816(0);
            do {
              uVar2 = *puVar7;
              uVar3 = puVar7[2];
              uVar4 = puVar7[4];
              uVar5 = puVar7[6];
              puVar7 = puVar7 + 8;
              auVar24[0] = auVar25[0] | (byte)uVar2;
              auVar24[1] = auVar25[1] | (byte)((uint)uVar2 >> 8);
              auVar24[2] = auVar25[2] | (byte)((uint)uVar2 >> 0x10);
              auVar24[3] = auVar25[3] | (byte)((uint)uVar2 >> 0x18);
              auVar24[4] = auVar25[4] | (byte)uVar3;
              auVar24[5] = auVar25[5] | (byte)((uint)uVar3 >> 8);
              auVar24[6] = auVar25[6] | (byte)((uint)uVar3 >> 0x10);
              auVar24[7] = auVar25[7] | (byte)((uint)uVar3 >> 0x18);
              auVar24[8] = auVar25[8] | (byte)uVar4;
              auVar24[9] = auVar25[9] | (byte)((uint)uVar4 >> 8);
              auVar24[10] = auVar25[10] | (byte)((uint)uVar4 >> 0x10);
              auVar24[0xb] = auVar25[0xb] | (byte)((uint)uVar4 >> 0x18);
              auVar24[0xc] = auVar25[0xc] | (byte)uVar5;
              auVar24[0xd] = auVar25[0xd] | (byte)((uint)uVar5 >> 8);
              auVar24[0xe] = auVar25[0xe] | (byte)((uint)uVar5 >> 0x10);
              auVar24[0xf] = auVar25[0xf] | (byte)((uint)uVar5 >> 0x18);
              auVar25 = auVar24;
            } while (puVar10 + (ulong)(uVar8 >> 2) * 8 != puVar7);
            uVar8 = uVar8 & 0xfffffffc;
            auVar25 = NEON_ext(auVar24,ZEXT216(0),8,1);
            auVar26[0] = auVar25[0] | auVar24[0];
            auVar26[1] = auVar25[1] | auVar24[1];
            auVar26[2] = auVar25[2] | auVar24[2];
            auVar26[3] = auVar25[3] | auVar24[3];
            auVar26[4] = auVar25[4] | auVar24[4];
            auVar26[5] = auVar25[5] | auVar24[5];
            auVar26[6] = auVar25[6] | auVar24[6];
            auVar26[7] = auVar25[7] | auVar24[7];
            auVar26[8] = auVar25[8] | auVar24[8];
            auVar26[9] = auVar25[9] | auVar24[9];
            auVar26[10] = auVar25[10] | auVar24[10];
            auVar26[0xb] = auVar25[0xb] | auVar24[0xb];
            auVar26[0xc] = auVar25[0xc] | auVar24[0xc];
            auVar26[0xd] = auVar25[0xd] | auVar24[0xd];
            auVar26[0xe] = auVar25[0xe] | auVar24[0xe];
            auVar26[0xf] = auVar25[0xf] | auVar24[0xf];
            auVar25 = NEON_ext(auVar26,ZEXT216(0),4,1);
            uVar12 = CONCAT13(auVar25[3] | auVar26[3],
                              CONCAT12(auVar25[2] | auVar26[2],
                                       CONCAT11(auVar25[1] | auVar26[1],auVar25[0] | auVar26[0])));
          }
          uVar12 = uVar12 | puVar10[(ulong)uVar8 * 2];
          if (uVar21 <= uVar8 + 1) goto LAB_0014995c;
          uVar12 = uVar12 | puVar10[(ulong)(uVar8 + 1) * 2];
          if (uVar21 <= uVar8 + 2) goto LAB_0014995c;
          uVar12 = uVar12 | puVar10[(ulong)(uVar8 + 2) * 2];
          if (uVar21 <= uVar8 + 3) goto LAB_0014995c;
          uVar12 = uVar12 | puVar10[(ulong)(uVar8 + 3) * 2];
          if (uVar21 <= uVar8 + 4) goto LAB_0014995c;
          uVar21 = puVar10[(ulong)(uVar8 + 4) * 2];
          *puVar11 = uVar12 | uVar21;
          puVar11[1] = uVar12 | uVar21;
          if (uVar19 <= (int)lVar18 + 1U) goto LAB_00149abc;
        }
        lVar18 = lVar18 + 1;
        pvVar6 = (void *)*local_80;
      } while( true );
    }
    goto LAB_00149cf0;
  }
  goto LAB_00149d04;
LAB_00149abc:
  pvVar6 = malloc(0x40);
  if (pvVar6 != (void *)0x0) {
    if (uVar19 != 0) {
      uVar23 = 0x10;
      __ptr_00 = (uint *)*local_80;
      uVar17 = 0;
      puVar11 = __ptr_00;
      __ptr = pvVar6;
      do {
        while( true ) {
          uVar13 = uVar17;
          uVar21 = *puVar11;
          uVar15 = uVar13 & 0xffffffff;
          puVar11[2] = 0;
          puVar11[3] = uVar21;
          uVar12 = (uint)uVar13;
          if (uVar12 < (uint)uVar23) break;
          uVar23 = (ulong)((uint)uVar23 << 1);
          pvVar6 = realloc(__ptr,uVar23 << 2);
          if (pvVar6 == (void *)0x0) goto LAB_00149ca0;
          puVar11 = puVar11 + 8;
          *(uint *)((long)pvVar6 + uVar13 * 4) = uVar12;
          uVar17 = uVar13 + 1;
          __ptr = pvVar6;
          if ((ulong)uVar19 == uVar13 + 1) goto LAB_00149b48;
        }
        *(uint *)((long)__ptr + uVar13 * 4) = uVar12;
        puVar11 = puVar11 + 8;
        uVar17 = uVar13 + 1;
        pvVar6 = __ptr;
      } while ((ulong)uVar19 != uVar13 + 1);
LAB_00149b48:
      uVar19 = *(uint *)(param_1 + 3);
      uVar17 = uVar13 & 0xffffffff;
      uVar12 = 0;
      puVar11 = __ptr_00 + (uVar13 & 0xffffffff) * 8;
      if (uVar19 == 0) goto LAB_00149c00;
LAB_00149b78:
      puVar14 = (uint *)param_1[2];
      uVar8 = 0;
      puVar9 = puVar14;
      do {
        if (puVar9[1] == (uint)uVar15) {
          uVar8 = uVar8 | __ptr_00[(ulong)*puVar9 * 8 + 3];
        }
        puVar9 = puVar9 + 3;
      } while (puVar14 + (ulong)uVar19 * 3 != puVar9);
      uVar21 = uVar8 & (puVar11[1] ^ 0xffffffff) | uVar21;
      if ((uVar8 != uVar12) || (puVar11[3] != uVar21)) {
        puVar9 = puVar14 + (ulong)uVar19 * 3;
        puVar11[2] = uVar8;
        puVar11[3] = uVar21;
        __ptr = pvVar6;
        do {
          pvVar6 = __ptr;
          if ((*puVar14 == (uint)uVar15) && (uVar21 = puVar14[1], uVar21 != 0xffffffff)) {
            if ((uint)uVar23 <= (uint)uVar17) {
              uVar23 = (ulong)((uint)uVar23 << 1);
              pvVar6 = realloc(__ptr,uVar23 << 2);
              if (pvVar6 == (void *)0x0) goto LAB_00149ca0;
            }
            *(uint *)((long)pvVar6 + uVar17 * 4) = uVar21;
            uVar17 = (ulong)((uint)uVar17 + 1);
          }
          puVar14 = puVar14 + 3;
          __ptr = pvVar6;
        } while (puVar9 != puVar14);
      }
      while ((int)uVar17 != 0) {
        while( true ) {
          iVar16 = (int)uVar17;
          uVar17 = (ulong)(iVar16 - 1);
          uVar15 = (ulong)*(uint *)((long)pvVar6 + (ulong)(iVar16 - 1) * 4);
          puVar11 = __ptr_00 + uVar15 * 8;
          uVar21 = __ptr_00[uVar15 * 8];
          uVar12 = __ptr_00[uVar15 * 8 + 2];
          if (uVar19 != 0) goto LAB_00149b78;
LAB_00149c00:
          if ((uVar12 == 0) && (puVar11[3] == uVar21)) break;
          puVar11[2] = 0;
          puVar11[3] = uVar21;
          if ((int)uVar17 == 0) goto LAB_00149c1c;
        }
      }
    }
LAB_00149c1c:
    free(pvVar6);
    goto LAB_00149904;
  }
  __ptr_00 = (uint *)*local_80;
  goto LAB_00149cac;
LAB_00149ca0:
  free(__ptr);
LAB_00149cac:
  if (__ptr_00 != (uint *)0x0) {
    if (*(int *)(local_80 + 1) != 0) {
      lVar18 = 0;
      do {
        lVar1 = lVar18 + 1;
        free(*(void **)(__ptr_00 + lVar18 * 8 + 4));
        __ptr_00 = (uint *)*local_80;
        lVar18 = lVar1;
      } while ((uint)lVar1 < *(uint *)(local_80 + 1));
    }
    free(__ptr_00);
  }
LAB_00149cf0:
  free(local_80);
LAB_00149d04:
  local_80 = (undefined8 *)0x0;
LAB_00149904:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return local_80;
}

