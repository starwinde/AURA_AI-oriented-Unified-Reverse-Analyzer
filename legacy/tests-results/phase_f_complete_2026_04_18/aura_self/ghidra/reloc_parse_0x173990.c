
void reloc_parse(long *param_1)

{
  char *pcVar1;
  ulong uVar2;
  char cVar3;
  char cVar4;
  ushort uVar5;
  ushort uVar6;
  long lVar7;
  bool bVar8;
  ushort uVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  void *__ptr;
  ulong uVar13;
  ulong uVar14;
  char *pcVar15;
  undefined8 *puVar16;
  void *pvVar17;
  undefined8 uVar18;
  char *pcVar19;
  undefined8 uVar20;
  ulong uVar21;
  long lVar22;
  uint *puVar23;
  ulong uVar24;
  ulong uVar25;
  undefined8 uVar26;
  undefined8 extraout_x8;
  long extraout_x9;
  int extraout_w10;
  int extraout_w10_00;
  ulong extraout_x10;
  ulong uVar27;
  ulong extraout_x10_00;
  ulong extraout_x10_01;
  ulong extraout_x10_02;
  ulong extraout_x10_03;
  uint extraout_w11;
  uint extraout_w11_00;
  uint uVar28;
  undefined8 uVar29;
  ulong extraout_x11;
  undefined8 extraout_x11_00;
  ulong extraout_x11_01;
  ulong uVar30;
  ulong extraout_x11_02;
  ulong uVar31;
  ulong extraout_x12;
  ulong extraout_x12_00;
  ulong extraout_x12_01;
  ulong extraout_x12_02;
  ulong extraout_x12_03;
  ulong uVar32;
  ulong extraout_x13;
  ulong extraout_x13_00;
  ulong extraout_x13_01;
  code *pcVar33;
  undefined1 *extraout_x18;
  undefined1 *puVar34;
  undefined1 *extraout_x18_00;
  undefined1 *extraout_x18_01;
  uint uVar35;
  uint uVar36;
  uint uVar37;
  uint uVar38;
  ulong uVar39;
  uint uVar40;
  ushort *puVar41;
  ulong *puVar42;
  ulong uVar43;
  char *pcVar44;
  uint local_108;
  undefined1 auStack_f8 [4];
  int local_f4;
  ulong local_f0;
  ulong uStack_e8;
  uint local_e0;
  long local_c0;
  uint local_b0;
  undefined8 local_90;
  undefined8 uStack_88;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (__ptr = calloc(0x100,0x20), __ptr != (void *)0x0)) {
    if ((int)param_1[1] == 1) {
      pcVar1 = *(char **)(*param_1 + 8);
      uVar2 = *(ulong *)(*param_1 + 0x10);
      if ((((uVar2 < 0x40) || (*pcVar1 != '\x7f')) || (pcVar1[1] != 'E')) ||
         ((pcVar1[2] != 'L' || (pcVar1[3] != 'F')))) {
        free(__ptr);
      }
      else {
        cVar3 = pcVar1[4];
        cVar4 = pcVar1[5];
        uVar9 = *(ushort *)(pcVar1 + 0x12);
        if (cVar3 == '\x02') {
          uVar32 = *(ulong *)(pcVar1 + 0x28);
          uVar5 = *(ushort *)(pcVar1 + 0x3c);
          uVar39 = (ulong)uVar5;
          uVar6 = *(ushort *)(pcVar1 + 0x3a);
          uVar21 = (ulong)uVar6;
          if (cVar4 != '\x01') {
            uVar9 = uVar9 >> 8 | uVar9 << 8;
            uVar21 = (ulong)((uint)(uVar6 >> 8) | (uVar6 & 0xff00ff) << 8);
            uVar39 = (ulong)((uint)(uVar5 >> 8) | (uVar5 & 0xff00ff) << 8);
            uVar32 = (uVar32 & 0xff00ff00ff00ff00) >> 8 | (uVar32 & 0xff00ff00ff00ff) << 8;
            uVar32 = (uVar32 & 0xffff0000ffff0000) >> 0x10 | (uVar32 & 0xffff0000ffff) << 0x10;
            uVar32 = uVar32 >> 0x20 | uVar32 << 0x20;
          }
          if (uVar9 != 0x28) {
            if (uVar9 == 0xb7) goto LAB_001740e8;
            if (uVar9 == 3) goto LAB_00173d8c;
            goto LAB_00174058;
          }
LAB_00174064:
          pcVar33 = arm32_reloc_type;
        }
        else {
          uVar36 = *(uint *)(pcVar1 + 0x20);
          uVar5 = *(ushort *)(pcVar1 + 0x2e);
          uVar21 = (ulong)uVar5;
          uVar6 = *(ushort *)(pcVar1 + 0x30);
          uVar39 = (ulong)uVar6;
          if (cVar4 != '\x01') {
            uVar9 = uVar9 >> 8 | uVar9 << 8;
            uVar21 = (ulong)((uint)(uVar5 >> 8) | (uVar5 & 0xff00ff) << 8);
            uVar39 = (ulong)((uint)(uVar6 >> 8) | (uVar6 & 0xff00ff) << 8);
            uVar36 = (uVar36 & 0xff00ff00) >> 8 | (uVar36 & 0xff00ff) << 8;
            uVar36 = uVar36 >> 0x10 | uVar36 << 0x10;
          }
          uVar32 = (ulong)uVar36;
          if (uVar9 == 0x3e) {
LAB_00174058:
            pcVar33 = elf64_reloc_type;
          }
          else if (uVar9 == 0xb7) {
LAB_001740e8:
            pcVar33 = aarch64_reloc_type;
          }
          else {
            if (uVar9 == 0x28) goto LAB_00174064;
LAB_00173d8c:
            pcVar33 = elf32_reloc_type;
          }
        }
        uVar36 = (uint)uVar39;
        if ((uVar32 == 0 || uVar36 == 0) || (int)uVar21 == 0) {
LAB_00173dac:
          free(__ptr);
          if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
            __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                             local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
          }
          calloc(1,0x10);
          return;
        }
        if ((uVar32 < uVar2) && (uVar21 * uVar39 <= uVar2 - uVar32)) {
          puVar34 = auStack_f8;
          uVar40 = 0;
          uVar39 = 0;
          local_108 = 0x100;
LAB_00173e38:
          iVar10 = parse_elf_shdr(pcVar1,uVar2,uVar32,uVar40,uVar21 & 0xffffffff,cVar3,
                                  cVar4 != '\x01',puVar34);
          uVar21 = extraout_x12;
          uVar32 = extraout_x13;
          puVar34 = extraout_x18;
          if ((iVar10 != 0) && (local_f4 == 4 || local_f4 == 9)) {
            iVar10 = local_f4;
            if ((local_e0 == 0) ||
               ((uVar36 <= local_e0 ||
                (iVar12 = parse_elf_shdr(pcVar1,uVar2,extraout_x13,local_e0,
                                         extraout_x12 & 0xffffffff,cVar3), uVar21 = extraout_x12_00,
                uVar32 = extraout_x13_00, puVar34 = extraout_x18_00, iVar10 = extraout_w10,
                iVar12 == 0)))) {
              uVar26 = 0;
              lVar22 = 0;
              uVar29 = 0;
            }
            else {
              uVar26 = 0;
              lVar22 = local_c0;
              uVar29 = 0;
              if ((local_b0 != 0 && local_b0 < uVar36) &&
                 (iVar12 = parse_elf_shdr(pcVar1,uVar2,extraout_x13_00,local_b0,
                                          extraout_x12_00 & 0xffffffff,cVar3), uVar26 = extraout_x8,
                 lVar22 = extraout_x9, uVar29 = extraout_x11_00, uVar21 = extraout_x12_01,
                 uVar32 = extraout_x13_01, puVar34 = extraout_x18_01, iVar10 = extraout_w10_00,
                 iVar12 != 0)) {
                uVar26 = local_90;
                uVar29 = uStack_88;
              }
            }
            uVar43 = local_f0;
            if ((local_f0 < uVar2) && (uVar13 = uVar2 - local_f0, uStack_e8 <= uVar13)) {
              if (cVar3 == '\x02') {
                if (iVar10 == 4) {
                  if ((0x17 < uStack_e8) && (0x17 < uVar13)) {
                    uVar13 = uStack_e8 / 0x18;
                    if (cVar4 == '\x01') {
                      pcVar44 = pcVar1 + local_f0;
                      uVar24 = 0;
                      uVar25 = local_f0;
                      do {
                        uVar20 = *(undefined8 *)pcVar44;
                        uVar27 = *(ulong *)(pcVar44 + 8);
                        uVar18 = *(undefined8 *)(pcVar44 + 0x10);
                        pcVar15 = (char *)0x0;
                        if ((int)(uVar27 >> 0x20) != 0 && lVar22 != 0) {
                          pcVar15 = (char *)elf_sym_name_at_isra_0
                                                      (pcVar1,uVar2,lVar22,uVar26,uVar29,
                                                       uVar27 >> 0x20,2,0);
                          uVar27 = extraout_x10_03;
                        }
                        uVar11 = (*pcVar33)(uVar27 & 0xffffffff);
                        uVar38 = (uint)uVar39;
                        uVar28 = uVar38;
                        if (uVar38 < 1000000) {
                          pvVar17 = __ptr;
                          uVar37 = local_108;
                          if (local_108 <= uVar38) {
                            pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                            uVar37 = local_108 << 1;
                            if (pvVar17 == (void *)0x0) goto LAB_00174cb0;
                          }
                          local_108 = uVar37;
                          lVar7 = uVar39 * 0x20;
                          *(undefined8 *)((long)pvVar17 + lVar7) = uVar20;
                          pcVar19 = (char *)0x0;
                          if (pcVar15 != (char *)0x0) {
                            pcVar19 = strdup(pcVar15);
                          }
                          *(char **)((long)pvVar17 + lVar7 + 8) = pcVar19;
                          *(undefined8 *)((long)pvVar17 + lVar7 + 0x10) = uVar18;
                          *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                          __ptr = pvVar17;
                          uVar28 = uVar38 + 1;
                        }
LAB_00174cb0:
                        uVar39 = (ulong)uVar28;
                        uVar24 = uVar24 + 1;
                        if (((uVar13 <= uVar24) || (uVar25 = uVar25 + 0x18, uVar2 <= uVar25)) ||
                           (uVar2 - uVar25 < 0x18)) goto LAB_001749c8;
                        pcVar44 = pcVar44 + 0x18;
                      } while (uVar38 < 1000000);
                      uVar43 = uVar43 + uVar24 * 0x18;
                      do {
                        uVar24 = uVar24 + 1;
                        (*pcVar33)(*(undefined4 *)(pcVar1 + uVar25 + 8));
                        if ((uVar13 <= uVar24) || (uVar25 = uVar43 + 0x18, uVar2 <= uVar25)) break;
                        uVar43 = uVar25;
                      } while (0x17 < uVar2 - uVar25);
                    }
                    else {
                      puVar42 = (ulong *)(pcVar1 + local_f0);
                      uVar24 = 0;
                      uVar25 = local_f0;
                      do {
                        pcVar44 = (char *)0x0;
                        uVar27 = (puVar42[2] & 0xff00ff00ff00ff00) >> 8 |
                                 (puVar42[2] & 0xff00ff00ff00ff) << 8;
                        uVar27 = (uVar27 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar27 & 0xffff0000ffff) << 0x10;
                        uVar14 = (puVar42[1] & 0xff00ff00ff00ff00) >> 8 |
                                 (puVar42[1] & 0xff00ff00ff00ff) << 8;
                        uVar14 = (uVar14 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar14 & 0xffff0000ffff) << 0x10;
                        uVar31 = uVar14 >> 0x20;
                        uVar30 = (*puVar42 & 0xff00ff00ff00ff00) >> 8 |
                                 (*puVar42 & 0xff00ff00ff00ff) << 8;
                        uVar30 = (uVar30 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar30 & 0xffff0000ffff) << 0x10;
                        if ((int)uVar14 != 0 && lVar22 != 0) {
                          pcVar44 = (char *)elf_sym_name_at_isra_0
                                                      (pcVar1,uVar2,lVar22,uVar26,uVar29,
                                                       uVar14 & 0xffffffff,2,1);
                          uVar31 = extraout_x11_02;
                        }
                        uVar11 = (*pcVar33)(uVar31 & 0xffffffff);
                        uVar38 = (uint)uVar39;
                        uVar28 = uVar38;
                        if (uVar38 < 1000000) {
                          pvVar17 = __ptr;
                          uVar37 = local_108;
                          if (local_108 <= uVar38) {
                            pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                            uVar37 = local_108 << 1;
                            if (pvVar17 == (void *)0x0) goto LAB_00174604;
                          }
                          local_108 = uVar37;
                          lVar7 = uVar39 * 0x20;
                          *(ulong *)((long)pvVar17 + lVar7) = uVar30 >> 0x20 | uVar30 << 0x20;
                          pcVar15 = (char *)0x0;
                          if (pcVar44 != (char *)0x0) {
                            pcVar15 = strdup(pcVar44);
                          }
                          *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                          *(ulong *)((long)pvVar17 + lVar7 + 0x10) = uVar27 >> 0x20 | uVar27 << 0x20
                          ;
                          *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                          __ptr = pvVar17;
                          uVar28 = uVar38 + 1;
                        }
LAB_00174604:
                        uVar39 = (ulong)uVar28;
                        uVar24 = uVar24 + 1;
                        if (((uVar13 <= uVar24) || (uVar25 = uVar25 + 0x18, uVar2 <= uVar25)) ||
                           (uVar2 - uVar25 < 0x18)) goto LAB_001749c8;
                        puVar42 = puVar42 + 3;
                      } while (uVar38 < 1000000);
                      uVar43 = uVar43 + uVar24 * 0x18;
                      do {
                        uVar24 = uVar24 + 1;
                        uVar25 = (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff00) >> 8 |
                                 (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff) << 8;
                        uVar25 = (uVar25 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar25 & 0xffff0000ffff) << 0x10;
                        (*pcVar33)(uVar25 >> 0x20 | uVar25 << 0x20);
                        if ((uVar13 <= uVar24) || (uVar25 = uVar43 + 0x18, uVar2 <= uVar25)) break;
                        uVar43 = uVar25;
                      } while (0x17 < uVar2 - uVar25);
                    }
                    goto LAB_00174078;
                  }
                }
                else {
                  uVar24 = uStack_e8 >> 4;
                  if ((uVar24 != 0) && (0xf < uVar13)) {
                    if (cVar4 == '\x01') {
                      uVar13 = 0;
                      uVar25 = local_f0;
                      do {
                        uVar20 = *(undefined8 *)(pcVar1 + uVar25);
                        uVar27 = *(ulong *)(pcVar1 + uVar25 + 8);
                        pcVar44 = (char *)0x0;
                        if ((int)(uVar27 >> 0x20) != 0 && lVar22 != 0) {
                          pcVar44 = (char *)elf_sym_name_at_isra_0
                                                      (pcVar1,uVar2,lVar22,uVar26,uVar29,
                                                       uVar27 >> 0x20,2,0);
                          uVar27 = extraout_x10_02;
                        }
                        uVar11 = (*pcVar33)(uVar27 & 0xffffffff);
                        uVar38 = (uint)uVar39;
                        uVar28 = uVar38;
                        if (uVar38 < 1000000) {
                          pvVar17 = __ptr;
                          uVar37 = local_108;
                          if (local_108 <= uVar38) {
                            pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                            uVar37 = local_108 << 1;
                            if (pvVar17 == (void *)0x0) goto LAB_00174ae8;
                          }
                          local_108 = uVar37;
                          lVar7 = uVar39 * 0x20;
                          *(undefined8 *)((long)pvVar17 + lVar7) = uVar20;
                          pcVar15 = (char *)0x0;
                          if (pcVar44 != (char *)0x0) {
                            pcVar15 = strdup(pcVar44);
                          }
                          *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                          *(undefined8 *)((long)pvVar17 + lVar7 + 0x10) = 0;
                          *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                          __ptr = pvVar17;
                          uVar28 = uVar38 + 1;
                        }
LAB_00174ae8:
                        uVar39 = (ulong)uVar28;
                        uVar13 = uVar13 + 1;
                        if (((uVar24 == uVar13) || (uVar25 = uVar25 + 0x10, uVar2 <= uVar25)) ||
                           (uVar2 - uVar25 < 0x10)) goto LAB_001747c0;
                      } while (uVar38 < 1000000);
                      uVar43 = uVar43 + uVar13 * 0x10;
                      do {
                        uVar13 = uVar13 + 1;
                        (*pcVar33)(*(undefined4 *)(pcVar1 + uVar25 + 8));
                        if ((uVar24 <= uVar13) || (uVar25 = uVar43 + 0x10, uVar2 <= uVar25)) break;
                        uVar43 = uVar25;
                      } while (0xf < uVar2 - uVar25);
                    }
                    else {
                      uVar13 = 0;
                      uVar25 = local_f0;
                      do {
                        pcVar44 = (char *)0x0;
                        uVar27 = (*(ulong *)(pcVar1 + uVar25) & 0xff00ff00ff00ff00) >> 8 |
                                 (*(ulong *)(pcVar1 + uVar25) & 0xff00ff00ff00ff) << 8;
                        uVar27 = (uVar27 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar27 & 0xffff0000ffff) << 0x10;
                        uVar14 = (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff00) >> 8 |
                                 (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff) << 8;
                        uVar14 = (uVar14 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar14 & 0xffff0000ffff) << 0x10;
                        uVar30 = uVar14 >> 0x20;
                        if ((int)uVar14 != 0 && lVar22 != 0) {
                          pcVar44 = (char *)elf_sym_name_at_isra_0
                                                      (pcVar1,uVar2,lVar22,uVar26,uVar29,
                                                       uVar14 & 0xffffffff,2,1);
                          uVar30 = extraout_x11_01;
                        }
                        uVar11 = (*pcVar33)(uVar30 & 0xffffffff);
                        uVar38 = (uint)uVar39;
                        uVar28 = uVar38;
                        if (uVar38 < 1000000) {
                          pvVar17 = __ptr;
                          uVar37 = local_108;
                          if (local_108 <= uVar38) {
                            pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                            uVar37 = local_108 << 1;
                            if (pvVar17 == (void *)0x0) goto LAB_00174280;
                          }
                          local_108 = uVar37;
                          lVar7 = uVar39 * 0x20;
                          *(ulong *)((long)pvVar17 + lVar7) = uVar27 >> 0x20 | uVar27 << 0x20;
                          pcVar15 = (char *)0x0;
                          if (pcVar44 != (char *)0x0) {
                            pcVar15 = strdup(pcVar44);
                          }
                          *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                          *(undefined8 *)((long)pvVar17 + lVar7 + 0x10) = 0;
                          *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                          __ptr = pvVar17;
                          uVar28 = uVar38 + 1;
                        }
LAB_00174280:
                        uVar39 = (ulong)uVar28;
                        uVar13 = uVar13 + 1;
                        if (((uVar24 == uVar13) || (uVar25 = uVar25 + 0x10, uVar2 <= uVar25)) ||
                           (uVar2 - uVar25 < 0x10)) goto LAB_001747c0;
                      } while (uVar38 < 1000000);
                      uVar43 = uVar43 + uVar13 * 0x10;
                      do {
                        uVar13 = uVar13 + 1;
                        uVar25 = (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff00) >> 8 |
                                 (*(ulong *)(pcVar1 + uVar25 + 8) & 0xff00ff00ff00ff) << 8;
                        uVar25 = (uVar25 & 0xffff0000ffff0000) >> 0x10 |
                                 (uVar25 & 0xffff0000ffff) << 0x10;
                        (*pcVar33)(uVar25 >> 0x20 | uVar25 << 0x20);
                        if ((uVar24 <= uVar13) || (uVar25 = uVar43 + 0x10, uVar2 <= uVar25)) break;
                        uVar43 = uVar25;
                      } while (0xf < uVar2 - uVar25);
                    }
LAB_00174078:
                    uVar21 = uVar21 & 0xffffffff;
                  }
                }
              }
              else if (iVar10 == 4) {
                if ((0xb < uStack_e8) && (0xb < uVar13)) {
                  uVar13 = uStack_e8 / 0xc;
                  if (cVar4 == '\x01') {
                    puVar23 = (uint *)(pcVar1 + local_f0);
                    uVar24 = 0;
                    uVar25 = local_f0;
                    do {
                      uVar27 = (ulong)*puVar23;
                      pcVar44 = (char *)0x0;
                      uVar28 = puVar23[2];
                      uVar14 = (ulong)(puVar23[1] & 0xff);
                      uVar38 = puVar23[1] >> 8;
                      if (uVar38 != 0 && lVar22 != 0) {
                        pcVar44 = (char *)elf_sym_name_at_isra_0
                                                    (pcVar1,uVar2,lVar22,uVar26,uVar29,uVar38,cVar3,
                                                     0);
                        uVar14 = extraout_x10_01;
                        uVar27 = extraout_x12_03;
                        uVar28 = extraout_w11_00;
                      }
                      uVar11 = (*pcVar33)(uVar14 & 0xffffffff);
                      uVar37 = (uint)uVar39;
                      uVar38 = uVar37;
                      if (uVar37 < 1000000) {
                        pvVar17 = __ptr;
                        uVar35 = local_108;
                        if (local_108 <= uVar37) {
                          pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                          uVar35 = local_108 << 1;
                          if (pvVar17 == (void *)0x0) goto LAB_00174984;
                        }
                        local_108 = uVar35;
                        lVar7 = uVar39 * 0x20;
                        *(ulong *)((long)pvVar17 + lVar7) = uVar27 & 0xffffffff;
                        pcVar15 = (char *)0x0;
                        if (pcVar44 != (char *)0x0) {
                          pcVar15 = strdup(pcVar44);
                        }
                        *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                        *(long *)((long)pvVar17 + lVar7 + 0x10) = (long)(int)uVar28;
                        *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                        __ptr = pvVar17;
                        uVar38 = uVar37 + 1;
                      }
LAB_00174984:
                      uVar39 = (ulong)uVar38;
                      uVar24 = uVar24 + 1;
                      if (((uVar13 <= uVar24) || (uVar25 = uVar25 + 0xc, uVar2 <= uVar25)) ||
                         (uVar2 - uVar25 < 0xc)) goto LAB_001747e8;
                      puVar23 = puVar23 + 3;
                    } while (uVar37 < 1000000);
                    uVar43 = uVar43 + uVar24 * 0xc;
                    do {
                      uVar24 = uVar24 + 1;
                      (*pcVar33)(pcVar1[uVar25 + 4]);
                      if ((uVar13 <= uVar24) || (uVar25 = uVar43 + 0xc, uVar2 <= uVar25)) break;
                      uVar43 = uVar25;
                    } while (0xb < uVar2 - uVar25);
                  }
                  else {
                    puVar23 = (uint *)(pcVar1 + local_f0);
                    uVar24 = 0;
                    uVar25 = local_f0;
                    do {
                      uVar28 = puVar23[1];
                      uVar38 = (puVar23[2] & 0xff00ff00) >> 8 | (puVar23[2] & 0xff00ff) << 8;
                      uVar38 = uVar38 >> 0x10 | uVar38 << 0x10;
                      pcVar44 = (char *)0x0;
                      uVar37 = (uVar28 & 0xff00ff00) >> 8 | (uVar28 & 0xff00ff) << 8;
                      uVar35 = (*puVar23 & 0xff00ff00) >> 8 | (*puVar23 & 0xff00ff) << 8;
                      uVar14 = (ulong)(uVar35 >> 0x10 | uVar35 << 0x10);
                      uVar27 = (ulong)(uVar28 >> 0x18);
                      uVar28 = (uVar37 >> 0x10 | uVar37 << 0x10) >> 8;
                      if (uVar28 != 0 && lVar22 != 0) {
                        pcVar44 = (char *)elf_sym_name_at_isra_0
                                                    (pcVar1,uVar2,lVar22,uVar26,uVar29,uVar28,cVar3,
                                                     1);
                        uVar27 = extraout_x10;
                        uVar14 = extraout_x12_02;
                        uVar38 = extraout_w11;
                      }
                      uVar11 = (*pcVar33)(uVar27 & 0xffffffff);
                      uVar37 = (uint)uVar39;
                      uVar28 = uVar37;
                      if (uVar37 < 1000000) {
                        pvVar17 = __ptr;
                        uVar35 = local_108;
                        if (local_108 <= uVar37) {
                          pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                          uVar35 = local_108 << 1;
                          if (pvVar17 == (void *)0x0) goto LAB_00174478;
                        }
                        local_108 = uVar35;
                        lVar7 = uVar39 * 0x20;
                        *(ulong *)((long)pvVar17 + lVar7) = uVar14 & 0xffffffff;
                        pcVar15 = (char *)0x0;
                        if (pcVar44 != (char *)0x0) {
                          pcVar15 = strdup(pcVar44);
                        }
                        *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                        *(long *)((long)pvVar17 + lVar7 + 0x10) = (long)(int)uVar38;
                        *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                        __ptr = pvVar17;
                        uVar28 = uVar37 + 1;
                      }
LAB_00174478:
                      uVar39 = (ulong)uVar28;
                      uVar24 = uVar24 + 1;
                      if (((uVar13 <= uVar24) || (uVar25 = uVar25 + 0xc, uVar2 <= uVar25)) ||
                         (uVar2 - uVar25 < 0xc)) goto LAB_001747e8;
                      puVar23 = puVar23 + 3;
                    } while (uVar37 < 1000000);
                    uVar43 = uVar43 + uVar24 * 0xc;
                    do {
                      uVar24 = uVar24 + 1;
                      (*pcVar33)(pcVar1[uVar25 + 7]);
                      if ((uVar13 <= uVar24) || (uVar25 = uVar43 + 0xc, uVar2 <= uVar25)) break;
                      uVar43 = uVar25;
                    } while (0xb < uVar2 - uVar25);
                  }
                  goto LAB_00174078;
                }
              }
              else {
                uVar24 = uStack_e8 >> 3;
                if ((uVar24 != 0) && (7 < uVar13)) {
                  bVar8 = lVar22 != 0;
                  if (cVar4 == '\x01') {
                    uVar14 = *(ulong *)(pcVar1 + local_f0);
                    pcVar44 = (char *)0x0;
                    uVar13 = 0;
                    uVar27 = uVar14 >> 0x20 & 0xff;
                    uVar25 = local_f0;
                    if ((uint)(uVar14 >> 0x28) == 0 || !bVar8) goto LAB_001746f8;
                    do {
                      pcVar44 = (char *)elf_sym_name_at_isra_0
                                                  (pcVar1,uVar2,lVar22,uVar26,uVar29,uVar14 >> 0x28,
                                                   cVar3,0);
                      uVar27 = extraout_x10_00;
LAB_001746f8:
                      do {
                        uVar11 = (*pcVar33)(uVar27 & 0xffffffff);
                        uVar38 = (uint)uVar39;
                        uVar28 = uVar38;
                        if (uVar38 < 1000000) {
                          pvVar17 = __ptr;
                          uVar37 = local_108;
                          if (local_108 <= uVar38) {
                            pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                            uVar37 = local_108 << 1;
                            if (pvVar17 == (void *)0x0) goto LAB_00174764;
                          }
                          local_108 = uVar37;
                          lVar7 = uVar39 * 0x20;
                          *(ulong *)((long)pvVar17 + lVar7) = uVar14 & 0xffffffff;
                          pcVar15 = (char *)0x0;
                          if (pcVar44 != (char *)0x0) {
                            pcVar15 = strdup(pcVar44);
                          }
                          *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                          *(undefined8 *)((long)pvVar17 + lVar7 + 0x10) = 0;
                          *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                          __ptr = pvVar17;
                          uVar28 = uVar38 + 1;
                        }
LAB_00174764:
                        uVar39 = (ulong)uVar28;
                        uVar13 = uVar13 + 1;
                        if (((uVar24 == uVar13) || (uVar25 = uVar25 + 8, uVar2 <= uVar25)) ||
                           (uVar2 - uVar25 < 8)) {
                          uVar21 = uVar21 & 0xffffffff;
                          goto LAB_00174080;
                        }
                        if (999999 < uVar38) {
                          uVar21 = uVar21 & 0xffffffff;
                          uVar39 = uVar43 + uVar13 * 8;
                          goto LAB_001751ac;
                        }
                        uVar14 = *(ulong *)(pcVar1 + uVar25);
                        pcVar44 = (char *)0x0;
                        uVar27 = uVar14 >> 0x20 & 0xff;
                      } while ((uint)(uVar14 >> 0x28) == 0 || !bVar8);
                    } while( true );
                  }
                  uVar25 = local_f0;
                  uVar13 = 0;
                  do {
                    uVar27 = uVar13;
                    uVar14 = *(ulong *)(pcVar1 + uVar25);
                    pcVar44 = (char *)0x0;
                    uVar13 = (uVar14 & 0xff00ff00ff00ff00) >> 8 | (uVar14 & 0xff00ff00ff00ff) << 8;
                    uVar13 = (uVar13 & 0xffff0000ffff0000) >> 0x10 |
                             (uVar13 & 0xffff0000ffff) << 0x10;
                    uVar28 = ((uint)uVar14 & 0xff00ff00) >> 8 | ((uint)uVar14 & 0xff00ff) << 8;
                    uVar14 = uVar14 >> 0x38;
                    if ((uint)(uVar13 >> 0x28) != 0 && bVar8) {
                      pcVar44 = (char *)elf_sym_name_at_isra_0
                                                  (pcVar1,uVar2,lVar22,uVar26,uVar29,uVar13 >> 0x28,
                                                   cVar3,1);
                      uVar14 = extraout_x11;
                    }
                    uVar11 = (*pcVar33)(uVar14 & 0xffffffff);
                    uVar37 = (uint)uVar39;
                    uVar38 = uVar37;
                    if (uVar37 < 1000000) {
                      pvVar17 = __ptr;
                      uVar35 = local_108;
                      if (local_108 <= uVar37) {
                        pvVar17 = realloc(__ptr,(ulong)(local_108 << 1) << 5);
                        uVar35 = local_108 << 1;
                        if (pvVar17 == (void *)0x0) goto LAB_00173fbc;
                      }
                      local_108 = uVar35;
                      lVar7 = uVar39 * 0x20;
                      *(ulong *)((long)pvVar17 + lVar7) = (ulong)(uVar28 >> 0x10 | uVar28 << 0x10);
                      pcVar15 = (char *)0x0;
                      if (pcVar44 != (char *)0x0) {
                        pcVar15 = strdup(pcVar44);
                      }
                      *(char **)((long)pvVar17 + lVar7 + 8) = pcVar15;
                      *(undefined8 *)((long)pvVar17 + lVar7 + 0x10) = 0;
                      *(undefined4 *)((long)pvVar17 + lVar7 + 0x18) = uVar11;
                      __ptr = pvVar17;
                      uVar38 = uVar37 + 1;
                    }
LAB_00173fbc:
                    uVar39 = (ulong)uVar38;
                    uVar13 = uVar27 + 1;
                    if (((uVar24 == uVar13) || (uVar25 = uVar25 + 8, uVar2 <= uVar25)) ||
                       (uVar2 - uVar25 < 8)) {
                      uVar21 = uVar21 & 0xffffffff;
                      goto LAB_00174080;
                    }
                  } while (uVar37 < 1000000);
                  uVar43 = uVar43 + uVar13 * 8;
                  uVar27 = uVar27 + 2;
                  (*pcVar33)(*(ulong *)(pcVar1 + uVar25) >> 0x38);
                  while (((uVar27 < uVar24 && (uVar43 = uVar43 + 8, uVar43 < uVar2)) &&
                         (7 < uVar2 - uVar43))) {
                    uVar27 = uVar27 + 1;
                    (*pcVar33)(*(ulong *)(pcVar1 + uVar43) >> 0x38);
                  }
                  uVar39 = (ulong)uVar38;
                  uVar21 = uVar21 & 0xffffffff;
                }
              }
            }
          }
          goto LAB_00174080;
        }
        free(__ptr);
      }
    }
    else {
      if ((int)param_1[1] == 2) {
        pcVar1 = *(char **)(*param_1 + 8);
        uVar2 = *(ulong *)(*param_1 + 0x10);
        if (((0x3f < uVar2) && (*pcVar1 == 'M')) && (pcVar1[1] == 'Z')) {
          uVar36 = *(uint *)(pcVar1 + 0x3c);
          if ((uVar36 < uVar2) && (3 < uVar2 - uVar36)) {
            if ((*(int *)(pcVar1 + uVar36) == 0x4550) &&
               ((uVar21 = (ulong)(uVar36 + 4), uVar21 < uVar2 && (0x13 < uVar2 - uVar21)))) {
              uVar32 = uVar21 + 0x14;
              uVar9 = *(ushort *)(pcVar1 + uVar21 + 2);
              if ((uVar32 < uVar2) &&
                 ((uVar2 - uVar32 != 1 && ((*(short *)(pcVar1 + uVar32) - 0x10bU & 0xfeff) == 0))))
              {
                if (*(short *)(pcVar1 + uVar32) == 0x20b) {
                  uVar39 = uVar21 + 0x2c;
                  if ((uVar39 < uVar2) && (7 < uVar2 - uVar39)) {
                    uVar43 = *(ulong *)(pcVar1 + uVar39);
                    lVar22 = 0x70;
                    goto LAB_00173ab4;
                  }
                }
                else {
                  uVar39 = uVar21 + 0x30;
                  if ((uVar39 < uVar2) && (3 < uVar2 - uVar39)) {
                    uVar43 = (ulong)*(uint *)(pcVar1 + uVar39);
                    lVar22 = 0x60;
LAB_00173ab4:
                    uVar39 = uVar32 + lVar22 + 0x28;
                    if ((uVar2 <= uVar39) || (uVar2 - uVar39 < 8)) goto LAB_00173dac;
                    uVar40 = *(uint *)(pcVar1 + uVar39);
                    uVar36 = *(uint *)(pcVar1 + uVar32 + lVar22 + 0x2c);
                    if (uVar40 == 0 || uVar36 == 0) goto LAB_00173dac;
                    uVar32 = uVar32 + *(ushort *)(pcVar1 + uVar21 + 0x10);
                    if ((uVar32 < uVar2) &&
                       ((ulong)uVar9 * 0x28 < uVar2 - uVar32 ||
                        (ulong)uVar9 * 0x28 - (uVar2 - uVar32) == 0)) {
                      if (uVar9 != 0) {
                        puVar23 = (uint *)(pcVar1 + uVar32 + 8);
                        do {
                          uVar28 = puVar23[2];
                          if (*puVar23 != 0) {
                            uVar28 = *puVar23;
                          }
                          if ((puVar23[1] <= uVar40) &&
                             (uVar38 = uVar40 - puVar23[1], uVar38 < uVar28)) {
                            uVar21 = (ulong)uVar38 + (ulong)puVar23[3];
                            if ((uVar21 != 0) &&
                               (((uVar21 < uVar2 && ((ulong)uVar36 <= uVar2 - uVar21)) &&
                                (uVar2 = uVar21 + uVar36, uVar21 + 8 <= uVar2)))) {
                              uVar36 = 0x100;
                              uVar39 = 0;
                              goto LAB_00173bb4;
                            }
                            break;
                          }
                          puVar23 = puVar23 + 10;
                        } while (puVar23 !=
                                 (uint *)(pcVar1 + uVar32 + (ulong)(uVar9 - 1) * 0x28 + 0x30));
                      }
                      goto LAB_00173dac;
                    }
                    free(__ptr);
                    goto LAB_00173ca0;
                  }
                }
              }
            }
            free(__ptr);
            goto LAB_00173ca0;
          }
        }
      }
      free(__ptr);
    }
  }
  goto LAB_00173ca0;
LAB_001749c8:
  uVar21 = uVar21 & 0xffffffff;
  goto LAB_00174080;
LAB_001747c0:
  uVar21 = uVar21 & 0xffffffff;
  goto LAB_00174080;
LAB_001747e8:
  uVar21 = uVar21 & 0xffffffff;
  goto LAB_00174080;
  while (uVar39 = uVar25, 7 < uVar2 - uVar25) {
LAB_001751ac:
    uVar13 = uVar13 + 1;
    (*pcVar33)(pcVar1[uVar25 + 4]);
    if ((uVar24 <= uVar13) || (uVar25 = uVar39 + 8, uVar2 <= uVar25)) break;
  }
  uVar39 = (ulong)uVar28;
LAB_00174080:
  uVar28 = uVar40 + 1;
  uVar40 = uVar28 & 0xffff;
  if (uVar36 <= (uVar28 & 0xffff)) goto LAB_00174090;
  goto LAB_00173e38;
LAB_00173bb4:
  do {
    uVar28 = *(uint *)(pcVar1 + uVar21);
    uVar40 = *(uint *)(pcVar1 + uVar21 + 4);
    if ((uVar40 < 8) || (uVar32 = uVar21 + uVar40, uVar2 < uVar32)) break;
    uVar40 = uVar40 - 8 >> 1;
    if ((uVar40 != 0) && (uVar21 + 10 <= uVar2)) {
      puVar41 = (ushort *)(pcVar1 + uVar21 + 8);
      do {
        uVar9 = *puVar41;
        uVar5 = uVar9 >> 0xc;
        if (uVar5 == 2) {
          uVar38 = 0xc;
LAB_00173c2c:
          uVar37 = (uint)uVar39;
          if (uVar37 < 1000000) {
            pvVar17 = __ptr;
            uVar35 = uVar36;
            if (uVar36 <= uVar37) {
              uVar35 = uVar36 << 1;
              pvVar17 = realloc(__ptr,(ulong)uVar35 << 5);
              if (pvVar17 == (void *)0x0) goto LAB_00173c54;
            }
            lVar22 = uVar39 * 0x20;
            uVar39 = (ulong)(uVar37 + 1);
            *(ulong *)((long)pvVar17 + lVar22) = ((ulong)uVar9 & 0xfff) + uVar43 + uVar28;
            *(undefined8 *)((long)pvVar17 + lVar22 + 8) = 0;
            *(undefined8 *)((long)pvVar17 + lVar22 + 0x10) = 0;
            *(uint *)((long)pvVar17 + lVar22 + 0x18) = uVar38;
            __ptr = pvVar17;
            uVar36 = uVar35;
          }
        }
        else {
          if (2 < uVar5) {
            uVar38 = 2;
            if (uVar5 != 3) {
              uVar38 = (uint)(uVar5 == 10);
            }
            goto LAB_00173c2c;
          }
          uVar38 = 0xb;
          if (uVar5 != 0) goto LAB_00173c2c;
        }
LAB_00173c54:
      } while ((puVar41 != (ushort *)(pcVar1 + uVar21 + (ulong)(uVar40 - 1) * 2 + 8)) &&
              (puVar41 = puVar41 + 1,
              puVar41 !=
              (ushort *)(pcVar1 + ((uVar2 - 10) - uVar21 & 0xfffffffffffffffe) + uVar21 + 10)));
    }
    uVar21 = uVar32;
  } while (uVar32 + 8 <= uVar2);
LAB_00174090:
  if ((int)uVar39 == 0) goto LAB_00173dac;
  qsort(__ptr,uVar39,0x20,reloc_entry_cmp);
  puVar16 = calloc(1,0x10);
  if (puVar16 != (undefined8 *)0x0) {
    *puVar16 = __ptr;
    *(int *)(puVar16 + 1) = (int)uVar39;
    goto LAB_00173ca8;
  }
  pvVar17 = __ptr;
  do {
    puVar16 = (undefined8 *)((long)pvVar17 + 8);
    pvVar17 = (void *)((long)pvVar17 + 0x20);
    free((void *)*puVar16);
  } while (pvVar17 != (void *)((long)__ptr + uVar39 * 0x20));
  free(__ptr);
LAB_00173ca0:
  puVar16 = (undefined8 *)0x0;
LAB_00173ca8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(puVar16,PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

