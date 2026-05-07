
void elf_parse(long *param_1)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  ushort uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  void *pvVar9;
  char *pcVar10;
  long lVar11;
  ulong uVar12;
  ulong uVar13;
  size_t sVar14;
  uint uVar15;
  size_t sVar16;
  size_t sVar17;
  uint uVar18;
  char *pcVar19;
  long lVar20;
  int extraout_w8;
  size_t sVar21;
  ulong extraout_x8;
  size_t extraout_x8_00;
  int extraout_w9;
  ulong uVar22;
  ulong extraout_x9;
  undefined1 *extraout_x10;
  undefined1 *puVar23;
  undefined1 *extraout_x10_00;
  int extraout_w11;
  int extraout_w11_00;
  ulong extraout_x12;
  ulong uVar24;
  ulong extraout_x12_00;
  ushort uVar25;
  ulong uVar26;
  ulong *puVar27;
  uint uVar28;
  long lVar29;
  uint uVar30;
  ulong uVar31;
  long *plVar32;
  undefined1 auVar33 [16];
  ulong local_130;
  ulong uStack_128;
  char *local_100;
  ulong local_f8;
  undefined1 auStack_c8 [4];
  int local_c4;
  ulong local_b0;
  ulong uStack_a8;
  uint local_a0;
  uint local_98;
  int local_94;
  ulong local_90;
  undefined8 local_88;
  ulong local_80;
  ulong local_78;
  long local_68;
  
  pcVar10 = *(char **)(*param_1 + 8);
  uVar31 = *(ulong *)(*param_1 + 0x10);
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((((0x3f < uVar31) && (*pcVar10 == '\x7f')) && (pcVar10[1] == 'E')) &&
     ((pcVar10[2] == 'L' && (pcVar10[3] == 'F')))) {
    cVar2 = pcVar10[4];
    cVar3 = pcVar10[5];
    if ((byte)(cVar2 - 1U) < 2) {
      *(undefined4 *)(param_1 + 1) = 1;
      if (cVar2 == '\x02') {
        local_130 = *(ulong *)(pcVar10 + 0x28);
        uVar13 = *(ulong *)(pcVar10 + 0x18);
        uVar25 = *(ushort *)(pcVar10 + 0x12);
        uVar30 = (uint)*(ushort *)(pcVar10 + 0x3a);
        uVar28 = (uint)*(ushort *)(pcVar10 + 0x3c);
        uVar4 = *(ushort *)(pcVar10 + 0x3e);
        uVar15 = (uint)uVar4;
        if (cVar3 != '\x01') {
          uVar25 = uVar25 >> 8 | uVar25 << 8;
          uVar28 = (uint)(*(ushort *)(pcVar10 + 0x3c) >> 8) | (uVar28 & 0xff00ff) << 8;
          uVar15 = (uint)(uVar4 >> 8) | (uVar4 & 0xff00ff) << 8;
          uVar30 = (uint)(*(ushort *)(pcVar10 + 0x3a) >> 8) | (uVar30 & 0xff00ff) << 8;
          uVar26 = (local_130 & 0xff00ff00ff00ff00) >> 8 | (local_130 & 0xff00ff00ff00ff) << 8;
          uVar26 = (uVar26 & 0xffff0000ffff0000) >> 0x10 | (uVar26 & 0xffff0000ffff) << 0x10;
          local_130 = uVar26 >> 0x20 | uVar26 << 0x20;
          uVar13 = (uVar13 & 0xff00ff00ff00ff00) >> 8 | (uVar13 & 0xff00ff00ff00ff) << 8;
          uVar13 = (uVar13 & 0xffff0000ffff0000) >> 0x10 | (uVar13 & 0xffff0000ffff) << 0x10;
          uVar13 = uVar13 >> 0x20 | uVar13 << 0x20;
        }
LAB_001452c4:
        bVar5 = uVar25 == 0x3e;
        if (!bVar5) goto LAB_001452cc;
LAB_00145374:
        *(undefined4 *)((long)param_1 + 0xc) = 2;
        param_1[2] = uVar13;
        if ((local_130 != 0 && uVar28 != 0) && uVar30 != 0) goto LAB_00145398;
      }
      else {
        uVar25 = *(ushort *)(pcVar10 + 0x12);
        uVar30 = (uint)*(ushort *)(pcVar10 + 0x2e);
        uVar28 = (uint)*(ushort *)(pcVar10 + 0x30);
        uVar4 = *(ushort *)(pcVar10 + 0x32);
        uVar15 = (uint)uVar4;
        uVar18 = *(uint *)(pcVar10 + 0x18);
        uVar1 = *(uint *)(pcVar10 + 0x20);
        if (cVar3 == '\x01') {
          uVar13 = (ulong)uVar18;
          local_130 = (ulong)uVar1;
          goto LAB_001452c4;
        }
        uVar25 = uVar25 >> 8 | uVar25 << 8;
        uVar28 = (uint)(*(ushort *)(pcVar10 + 0x30) >> 8) | (uVar28 & 0xff00ff) << 8;
        uVar15 = (uint)(uVar4 >> 8) | (uVar4 & 0xff00ff) << 8;
        uVar30 = (uint)(*(ushort *)(pcVar10 + 0x2e) >> 8) | (uVar30 & 0xff00ff) << 8;
        uVar1 = (uVar1 & 0xff00ff00) >> 8 | (uVar1 & 0xff00ff) << 8;
        local_130 = (ulong)(uVar1 >> 0x10 | uVar1 << 0x10);
        uVar18 = (uVar18 & 0xff00ff00) >> 8 | (uVar18 & 0xff00ff) << 8;
        uVar13 = (ulong)(uVar18 >> 0x10 | uVar18 << 0x10);
        bVar5 = false;
        if (uVar25 == 0x3e) goto LAB_00145374;
LAB_001452cc:
        if (uVar25 < 0x3e || bVar5) {
          iVar6 = 1;
          if ((uVar25 != 3) && (iVar6 = 3, uVar25 != 0x28)) {
            iVar6 = 0;
          }
        }
        else {
          iVar6 = (uint)(uVar25 == 0xb7) << 2;
        }
        *(int *)((long)param_1 + 0xc) = iVar6;
        param_1[2] = uVar13;
        if ((local_130 != 0 && uVar28 != 0) && uVar30 != 0) {
LAB_00145398:
          if ((uVar31 <= local_130) ||
             (sVar21 = (size_t)uVar28,
             uVar31 - local_130 <= (ulong)uVar28 * (ulong)uVar30 &&
             (ulong)uVar28 * (ulong)uVar30 - (uVar31 - local_130) != 0)) goto LAB_00145560;
          local_100 = (char *)0x0;
          local_f8 = 0;
          bVar5 = cVar3 != '\x01';
          if (((uVar15 != 0 && uVar15 <= uVar28) && (uVar15 == 0 || uVar28 != uVar15)) &&
             ((iVar6 = parse_shdr(pcVar10,uVar31,local_130,uVar15,uVar30,cVar2,bVar5,&local_98),
              sVar21 = extraout_x8_00, iVar6 != 0 && (local_80 < uVar31)))) {
            local_f8 = local_78;
            if (uVar31 - local_80 < local_78) {
              local_f8 = 0;
            }
            else {
              local_100 = pcVar10 + local_80;
            }
          }
          pvVar9 = calloc(sVar21,0x38);
          param_1[3] = (long)pvVar9;
          if (pvVar9 == (void *)0x0) {
LAB_00145938:
            uVar8 = 0xfffffffe;
            goto LAB_00145310;
          }
          uVar25 = 0;
          do {
            iVar6 = parse_shdr(pcVar10,uVar31,local_130,uVar25,uVar30,cVar2,bVar5,&local_98);
            if (iVar6 != 0) {
              uVar15 = *(uint *)(param_1 + 4);
              lVar20 = param_1[3];
              lVar29 = (ulong)uVar15 * 0x38;
              lVar11 = lVar20 + lVar29;
              if ((local_100 == (char *)0x0) || ((uint)local_f8 <= local_98)) {
                pcVar19 = strdup("");
                *(char **)(lVar20 + lVar29) = pcVar19;
                if (pcVar19 == (char *)0x0) goto LAB_00145938;
              }
              else {
                uVar13 = (ulong)local_98;
                sVar21 = 0;
                if (local_f8 == uVar13) {
                  sVar16 = 1;
                  sVar17 = 0;
                }
                else {
                  do {
                    sVar17 = sVar21;
                    sVar21 = sVar17 + 1;
                    sVar16 = sVar21;
                    if ((local_100 + uVar13)[sVar17] == '\0') goto LAB_0014551c;
                  } while (local_f8 - uVar13 != sVar21);
                  sVar16 = sVar17 + 2;
                  sVar17 = sVar21;
                }
LAB_0014551c:
                pvVar9 = malloc(sVar16);
                *(void **)(lVar20 + lVar29) = pvVar9;
                if (pvVar9 == (void *)0x0) goto LAB_00145938;
                __memcpy_chk(pvVar9,local_100 + uVar13,sVar17,sVar16);
                *(undefined1 *)(*(long *)(lVar20 + lVar29) + sVar17) = 0;
                uVar15 = *(uint *)(param_1 + 4);
              }
              pcVar19 = (char *)0x0;
              *(ulong *)(lVar11 + 0x18) = local_78;
              *(ulong *)(lVar11 + 0x20) = local_78;
              uVar1 = -((uint)local_90 & 1) & 2 | (uint)local_90 >> 1 & 1;
              uVar18 = uVar1 | 4;
              if ((local_90 & 4) == 0) {
                uVar18 = uVar1;
              }
              *(undefined8 *)(lVar11 + 8) = local_88;
              *(ulong *)(lVar11 + 0x10) = local_80;
              *(uint *)(lVar11 + 0x30) = uVar18;
              if ((local_80 < uVar31 && (local_78 != 0 && local_94 != 8)) &&
                 (pcVar19 = pcVar10 + local_80, uVar31 - local_80 < local_78)) {
                pcVar19 = (char *)0x0;
              }
              *(char **)(lVar11 + 0x28) = pcVar19;
              *(uint *)(param_1 + 4) = uVar15 + 1;
            }
            uVar25 = uVar25 + 1;
          } while (uVar25 < uVar28);
          puVar23 = auStack_c8;
          uVar13 = 0x10;
          if (cVar2 == '\x02') {
            uVar13 = 0x18;
          }
          uVar26 = 0;
          do {
            uVar15 = 0;
            do {
              iVar7 = parse_shdr(pcVar10,uVar31,local_130,uVar15,uVar30,cVar2,bVar5,puVar23);
              puVar23 = extraout_x10;
              iVar6 = extraout_w11;
              if ((iVar7 != 0) && (local_c4 == extraout_w9)) {
                uVar12 = local_b0;
                uVar22 = uStack_a8;
                uVar24 = extraout_x12;
                if ((local_a0 < uVar28) &&
                   (iVar7 = parse_shdr(pcVar10,uVar31,local_130,local_a0,uVar30,cVar2),
                   uVar12 = extraout_x8, uVar22 = extraout_x9, puVar23 = extraout_x10_00,
                   uVar24 = extraout_x12_00, iVar6 = extraout_w11_00, iVar7 != 0)) {
                  uVar24 = local_80;
                  uVar26 = local_78;
                }
                if (uVar12 != 0) {
                  if ((uVar31 <= uVar12) || (uVar31 - uVar12 < uVar22)) goto LAB_00145304;
                  pcVar19 = (char *)0x0;
                  sVar21 = 0;
                  if (uVar13 != 0) {
                    sVar21 = uVar22 / uVar13;
                  }
                  if ((uVar24 != 0 && uVar24 < uVar31) &&
                     (pcVar19 = pcVar10 + uVar24, uVar31 - uVar24 < uVar26)) {
                    pcVar19 = (char *)0x0;
                  }
                  pvVar9 = calloc(sVar21,0x28);
                  param_1[5] = (long)pvVar9;
                  if (pvVar9 == (void *)0x0) goto LAB_00145938;
                  if (uVar22 < uVar13) goto LAB_00145304;
                  uVar28 = *(uint *)(param_1 + 6);
                  puVar27 = (ulong *)(pcVar10 + uVar12);
                  uVar31 = 0;
                  goto LAB_0014585c;
                }
                break;
              }
              uVar15 = extraout_w8 + 1U & 0xffff;
            } while ((extraout_w8 + 1U & 0xffff) < uVar28);
          } while (iVar6 == 0);
        }
      }
LAB_00145304:
      uVar8 = 0;
      goto LAB_00145310;
    }
  }
LAB_00145560:
  uVar8 = 0xfffffff9;
LAB_00145310:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(uVar8,PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_0014585c:
  if (cVar2 == '\x02') {
    auVar33 = *(undefined1 (*) [16])(puVar27 + 1);
    uVar18 = (uint)*(byte *)((long)puVar27 + 4);
    uStack_128 = auVar33._8_8_;
    local_130 = auVar33._0_8_;
    uVar15 = (uint)*puVar27;
    if (cVar3 != '\x01') {
      auVar33 = NEON_rev64(auVar33,1);
      uVar15 = (uVar15 & 0xff00ff00) >> 8 | (uVar15 & 0xff00ff) << 8;
      uVar15 = uVar15 >> 0x10 | uVar15 << 0x10;
      uStack_128 = auVar33._8_8_;
      local_130 = auVar33._0_8_;
    }
  }
  else {
    uVar12 = *puVar27;
    uVar15 = (uint)uVar12;
    uVar30 = (uint)puVar27[1];
    local_130 = uVar12 >> 0x20;
    if (cVar3 != '\x01') {
      uVar18 = (uint)(uVar12 >> 0x20);
      uVar18 = (uVar18 & 0xff00ff00) >> 8 | (uVar18 & 0xff00ff) << 8;
      local_130 = (ulong)(uVar18 >> 0x10 | uVar18 << 0x10);
      uVar15 = (uVar15 & 0xff00ff00) >> 8 | (uVar15 & 0xff00ff) << 8;
      uVar15 = uVar15 >> 0x10 | uVar15 << 0x10;
      uVar30 = (uVar30 & 0xff00ff00) >> 8 | (uVar30 & 0xff00ff) << 8;
      uVar30 = uVar30 >> 0x10 | uVar30 << 0x10;
    }
    uVar18 = (uint)(puVar27[1] >> 0x20) & 0xff;
    uStack_128 = (ulong)uVar30;
  }
  plVar32 = (long *)((long)pvVar9 + (ulong)uVar28 * 0x28);
  if ((pcVar19 == (char *)0x0) || ((uint)uVar26 <= uVar15)) {
    pcVar10 = strdup("");
    *plVar32 = (long)pcVar10;
    if (pcVar10 == (char *)0x0) goto LAB_00145938;
  }
  else {
    uVar12 = (ulong)uVar15;
    sVar16 = 0;
    if (uVar26 == uVar12) {
      sVar14 = 0;
      sVar17 = 1;
    }
    else {
      do {
        sVar14 = sVar16;
        sVar16 = sVar14 + 1;
        sVar17 = sVar16;
        if ((pcVar19 + uVar12)[sVar14] == '\0') goto LAB_001458c0;
      } while (uVar26 - uVar12 != sVar16);
      sVar17 = sVar14 + 2;
      sVar14 = sVar16;
    }
LAB_001458c0:
    pvVar9 = malloc(sVar17);
    *plVar32 = (long)pvVar9;
    if (pvVar9 == (void *)0x0) goto LAB_00145938;
    __memcpy_chk(pvVar9,pcVar19 + uVar12,sVar14,sVar17);
    *(undefined1 *)(*plVar32 + sVar14) = 0;
    pcVar10 = (char *)*plVar32;
  }
  lVar11 = aura_demangle(pcVar10);
  plVar32[1] = lVar11;
  uVar28 = 2;
  plVar32[3] = uStack_128;
  plVar32[2] = local_130;
  if ((uVar18 & 0xf) != 1) {
    uVar28 = (uint)((uVar18 & 0xf) == 2);
  }
  *(uint *)(plVar32 + 4) = uVar28;
  iVar6 = 1;
  if (uVar18 >> 4 != 1) {
    iVar6 = (uint)(uVar18 >> 4 == 2) << 1;
  }
  lVar11 = param_1[6];
  uVar31 = uVar31 + 1;
  *(int *)((long)plVar32 + 0x24) = iVar6;
  puVar27 = (ulong *)((long)puVar27 + uVar13);
  uVar28 = (int)lVar11 + 1;
  *(uint *)(param_1 + 6) = uVar28;
  if (sVar21 <= uVar31) goto LAB_00145304;
  pvVar9 = (void *)param_1[5];
  goto LAB_0014585c;
}

