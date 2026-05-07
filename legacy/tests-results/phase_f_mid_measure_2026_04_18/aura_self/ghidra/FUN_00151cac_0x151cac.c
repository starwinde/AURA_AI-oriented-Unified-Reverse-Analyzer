
void FUN_00151cac(long *param_1,undefined8 param_2,char *param_3,long param_4)

{
  char *__s;
  undefined8 *puVar1;
  uint uVar2;
  byte bVar3;
  bool bVar4;
  bool bVar5;
  undefined8 uVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  void *pvVar12;
  undefined8 uVar13;
  long *plVar14;
  char *pcVar15;
  undefined8 *puVar16;
  undefined4 *puVar17;
  ulong uVar18;
  char *pcVar19;
  undefined4 *puVar20;
  ulonglong uVar21;
  uint uVar22;
  size_t sVar23;
  int *piVar24;
  undefined8 uVar25;
  uint uVar26;
  undefined8 uVar27;
  int *__ptr;
  uint uVar28;
  long lVar29;
  char *pcVar30;
  char *pcVar31;
  long lVar32;
  long lVar33;
  undefined8 uVar34;
  long lVar35;
  long lVar36;
  undefined4 uVar37;
  ulong uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  int iVar41;
  undefined4 uVar42;
  undefined8 uVar43;
  undefined8 uVar44;
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined8 uStack_310;
  long lStack_2f0;
  undefined8 uStack_2e0;
  int iStack_2d4;
  uint uStack_2b0;
  uint uStack_2ac;
  uint uStack_2a8;
  undefined4 uStack_2a4;
  undefined4 uStack_2a0;
  undefined4 uStack_29c;
  long *plStack_298;
  uint uStack_290;
  undefined4 uStack_28c;
  undefined8 uStack_288;
  undefined8 uStack_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 uStack_1e0;
  undefined8 uStack_1d8;
  undefined8 uStack_1d0;
  undefined8 uStack_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 uStack_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 uStack_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  char acStack_168 [127];
  char acStack_e9 [65];
  long lStack_a8;
  
  lStack_a8 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (plStack_298 = calloc(1,0xa0), plStack_298 != (long *)0x0)) {
    *(undefined4 *)(plStack_298 + 2) = 0;
    plStack_298[3] = param_4;
    if ((param_3 == (char *)0x0) || (*param_3 == '\0')) {
      __snprintf_chk(plStack_298 + 4,0x80,2,0x80,"sub_%lx",param_4);
    }
    else {
      snprintf((char *)(plStack_298 + 4),0x80,"%s",param_3);
    }
    uVar6 = DAT_0020bf20;
    lStack_2f0 = 0;
    if ((int)param_1[1] != 0) {
      do {
        plVar14 = plStack_298;
        uVar22 = *(uint *)(plStack_298 + 1);
        uVar28 = *(uint *)((long)plStack_298 + 0xc);
        pvVar12 = (void *)*plStack_298;
        lVar29 = *param_1 + lStack_2f0 * 0x20;
        if (uVar28 <= uVar22) {
          if (uVar28 == 0) {
            sVar23 = 0x280;
            uVar28 = 8;
          }
          else {
            uVar28 = uVar28 << 1;
            sVar23 = (ulong)uVar28 * 0x50;
          }
          pvVar12 = realloc(pvVar12,sVar23);
          if (pvVar12 == (void *)0x0) goto LAB_001529c4;
          uVar22 = *(uint *)(plVar14 + 1);
          *plVar14 = (long)pvVar12;
          *(uint *)((long)plVar14 + 0xc) = uVar28;
        }
        puVar1 = (undefined8 *)((long)pvVar12 + (ulong)uVar22 * 0x50);
        uStack_1f0 = 0xffffffffffffffff;
        uStack_1f8 = 0xffffffffffffffff;
        uStack_1e0 = 0xffffffffffffffff;
        uStack_1e8 = 0xffffffffffffffff;
        puVar1[1] = 0;
        *puVar1 = 0;
        puVar1[3] = 0;
        puVar1[2] = 0;
        puVar1[5] = 0;
        puVar1[4] = 0;
        puVar1[7] = 0;
        puVar1[6] = 0;
        puVar1[9] = 0;
        puVar1[8] = 0;
        iVar8 = (int)plVar14[1];
        uStack_1d0 = 0xffffffffffffffff;
        uStack_1d8 = 0xffffffffffffffff;
        uStack_1c0 = 0xffffffffffffffff;
        uStack_1c8 = 0xffffffffffffffff;
        *(int *)(plVar14 + 1) = iVar8 + 1;
        *(int *)((long)pvVar12 + (ulong)uVar22 * 0x50) = iVar8;
        *(int *)((long)puVar1 + 0x34) = iVar8;
        uStack_1b0 = 0xffffffffffffffff;
        uStack_1b8 = 0xffffffffffffffff;
        uStack_1a0 = 0xffffffffffffffff;
        uStack_1a8 = 0xffffffffffffffff;
        uStack_190 = 0xffffffffffffffff;
        uStack_198 = 0xffffffffffffffff;
        uStack_180 = 0xffffffffffffffff;
        uStack_188 = 0xffffffffffffffff;
        uStack_278 = 0x400000004;
        uStack_280 = 0x400000004;
        uStack_268 = 0x400000004;
        uStack_270 = 0x400000004;
        uStack_258 = 0x400000004;
        uStack_260 = 0x400000004;
        uStack_248 = 0x400000004;
        uStack_250 = 0x400000004;
        uStack_238 = 0x400000004;
        uStack_240 = 0x400000004;
        uStack_228 = 0x400000004;
        uStack_230 = 0x400000004;
        uStack_218 = 0x400000004;
        uStack_220 = 0x400000004;
        uStack_208 = 0x400000004;
        uStack_210 = 0x400000004;
        if ((int)lStack_2f0 == 0) {
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 8;
          uStack_1f8 = CONCAT44(iVar8 + 1,iVar8);
          uStack_1f0 = CONCAT44(iVar8 + 3,iVar8 + 2);
          uStack_1e8 = CONCAT44(iVar8 + 5,iVar8 + 4);
          uStack_1e0 = CONCAT44(iVar8 + 7,iVar8 + 6);
        }
        iVar8 = arm_emit_const(puVar1,plStack_298,0,param_4);
        if (iVar8 != -1) {
          uStack_208 = CONCAT44(5,(undefined4)uStack_208);
          uStack_180 = CONCAT44(iVar8,(undefined4)uStack_180);
        }
        if (*(int *)(lVar29 + 0x18) != 0) {
          iVar41 = -1;
          lVar32 = 0;
          uStack_2e0 = 0;
          iStack_2d4 = -1;
          uVar43 = uVar6;
          uVar44 = uVar6;
          iVar8 = iVar41;
LAB_00151ea8:
          lVar35 = *(long *)(lVar29 + 0x10) + lVar32 * 0xe0;
          pcVar19 = (char *)(lVar35 + 0x20);
          uVar13 = *(undefined8 *)(*(long *)(lVar29 + 0x10) + lVar32 * 0xe0);
          cVar7 = *(char *)(lVar35 + 0x60);
          acStack_168[0] = '\0';
          acStack_168[0x40] = '\0';
          acStack_e9[1] = '\0';
          if (cVar7 != '\0') {
            pcVar31 = (char *)(lVar35 + 0x60);
            iVar10 = 0;
            pcVar30 = pcVar31;
            do {
              while (cVar7 == '[') {
                pcVar30 = pcVar30 + 1;
                cVar7 = *pcVar30;
                iVar10 = iVar10 + 1;
                if (cVar7 == '\0') goto LAB_0015232c;
              }
              if (cVar7 == ']') {
                iVar10 = iVar10 + -1;
              }
              else if (cVar7 == ',' && iVar10 == 0) {
                sVar23 = (long)pcVar30 - (long)pcVar31;
                if (0x3f < sVar23) {
                  sVar23 = 0x3f;
                }
                memcpy(acStack_168,pcVar31,sVar23);
                acStack_168[sVar23] = '\0';
                cVar7 = acStack_168[0];
                if (acStack_168[0] == '\0') goto LAB_00152488;
                sVar23 = strlen(acStack_168);
                pcVar31 = acStack_168 + (sVar23 - 1);
                if (pcVar31 <= acStack_168) goto LAB_00152448;
                goto LAB_00152438;
              }
              pcVar30 = pcVar30 + 1;
              cVar7 = *pcVar30;
            } while (cVar7 != '\0');
LAB_0015232c:
            snprintf(acStack_168,0x40,"%s",pcVar31);
            cVar7 = acStack_168[0];
            if (acStack_168[0] != '\0') {
              sVar23 = strlen(acStack_168);
              pcVar31 = acStack_168 + (sVar23 - 1);
              if (acStack_168 < pcVar31) {
                do {
                  cVar7 = acStack_168[0];
                  if (*pcVar31 != ' ') break;
                  pcVar30 = pcVar31 + -1;
                  *pcVar31 = '\0';
                  pcVar31 = pcVar30;
                  cVar7 = acStack_168[0];
                } while (pcVar30 != acStack_168);
              }
              pcVar31 = acStack_168;
              if (cVar7 == ' ') {
                do {
                  pcVar31 = pcVar31 + 1;
                } while (*pcVar31 == ' ');
                if (pcVar31 != acStack_168) {
                  sVar23 = strlen(pcVar31);
                  __memmove_chk(acStack_168,pcVar31,sVar23 + 1,0x40);
                }
              }
            }
            uStack_2b0 = 0xfffffffe;
            uStack_2ac = 0xfffffffe;
            uStack_2a8 = 0xfffffffe;
            uStack_2a4 = 4;
            uStack_2a0 = 4;
            uStack_29c = 4;
            iVar10 = arm64_reg_lookup(acStack_168,&uStack_2b0,&uStack_2a4);
            if (iVar10 == 0) {
              iVar10 = 1;
              goto LAB_00151ef4;
            }
            uVar38 = 0;
            iVar10 = 1;
            bVar4 = false;
            bVar5 = false;
            uStack_310 = 0;
            goto LAB_00152754;
          }
          iVar10 = 0;
          uStack_2ac = 0xfffffffe;
          uStack_2a8 = 0xfffffffe;
          uStack_2a4 = 4;
          uStack_2a0 = 4;
          uStack_29c = 4;
LAB_00151ef4:
          uStack_2b0 = 0xfffffffe;
          iVar9 = strcmp(pcVar19,"adrp");
          if (iVar9 != 0) {
            uVar38 = 0;
            bVar4 = false;
            bVar5 = false;
            uStack_310 = 0;
            goto LAB_00151f14;
          }
          goto LAB_00152170;
        }
LAB_001521a0:
        lStack_2f0 = lStack_2f0 + 1;
      } while ((uint)lStack_2f0 < *(uint *)(param_1 + 1));
    }
    lVar29 = 0;
    uVar22 = *(uint *)(param_1 + 3);
    plVar14 = plStack_298;
    if (uVar22 != 0) {
      do {
        uVar28 = *(uint *)(param_1[2] + lVar29 * 0xc + 4);
        if (uVar28 != 0xffffffff) {
          uVar2 = *(uint *)(param_1[2] + lVar29 * 0xc);
          uVar26 = uVar28;
          if (uVar28 < uVar2) {
            uVar26 = uVar2;
          }
          if (uVar26 < *(uint *)(plVar14 + 1)) {
            lVar36 = *plVar14;
            lVar33 = (ulong)uVar28 * 0x50;
            lVar32 = lVar36 + (ulong)uVar2 * 0x50;
            lVar35 = lVar36 + lVar33;
            uVar28 = *(uint *)(lVar32 + 0x30);
            __ptr = *(int **)(lVar32 + 0x28);
            if (uVar28 == 0) {
              sVar23 = 4;
            }
            else {
              piVar24 = __ptr;
              do {
                if (*piVar24 == *(int *)(lVar36 + lVar33)) goto LAB_001521fc;
                piVar24 = piVar24 + 1;
              } while (__ptr + uVar28 != piVar24);
              sVar23 = (ulong)(uVar28 + 1) << 2;
            }
            pvVar12 = realloc(__ptr,sVar23);
            if (pvVar12 == (void *)0x0) goto LAB_001529c4;
            uVar22 = *(uint *)(lVar32 + 0x30);
            uVar11 = *(undefined4 *)(lVar36 + lVar33);
            *(void **)(lVar32 + 0x28) = pvVar12;
            *(uint *)(lVar32 + 0x30) = uVar22 + 1;
            *(undefined4 *)((long)pvVar12 + (ulong)uVar22 * 4) = uVar11;
            pvVar12 = realloc(*(void **)(lVar35 + 0x18),(ulong)(*(int *)(lVar35 + 0x20) + 1) << 2);
            if (pvVar12 == (void *)0x0) goto LAB_001529c4;
            uVar22 = *(uint *)(lVar35 + 0x20);
            uVar11 = *(undefined4 *)(lVar36 + (ulong)uVar2 * 0x50);
            *(void **)(lVar35 + 0x18) = pvVar12;
            *(uint *)(lVar35 + 0x20) = uVar22 + 1;
            *(undefined4 *)((long)pvVar12 + (ulong)uVar22 * 4) = uVar11;
            uVar22 = *(uint *)(param_1 + 3);
            plVar14 = plStack_298;
          }
        }
LAB_001521fc:
        lVar29 = lVar29 + 1;
      } while ((uint)lVar29 < uVar22);
    }
    goto LAB_001529f0;
  }
LAB_001529ec:
  plVar14 = (long *)0x0;
LAB_001529f0:
  if (lStack_a8 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(plVar14,PTR___stack_chk_guard_005ffe88,0,
                   lStack_a8 - *(long *)PTR___stack_chk_guard_005ffe88);
  while( true ) {
    pcVar15 = pcVar31 + -1;
    *pcVar31 = '\0';
    pcVar31 = pcVar15;
    cVar7 = acStack_168[0];
    if (pcVar15 == acStack_168) break;
LAB_00152438:
    cVar7 = acStack_168[0];
    if (*pcVar31 != ' ') break;
  }
LAB_00152448:
  pcVar31 = acStack_168;
  if (cVar7 == ' ') {
    do {
      pcVar31 = pcVar31 + 1;
    } while (*pcVar31 == ' ');
    if (pcVar31 != acStack_168) {
      sVar23 = strlen(pcVar31);
      __memmove_chk(acStack_168,pcVar31,sVar23 + 1,0x40);
    }
  }
LAB_00152488:
  cVar7 = pcVar30[1];
  pcVar30 = pcVar30 + 1;
  if (cVar7 != '\0') {
    iVar10 = 0;
    pcVar31 = pcVar30;
    do {
      while (cVar7 == '[') {
        pcVar31 = pcVar31 + 1;
        cVar7 = *pcVar31;
        iVar10 = iVar10 + 1;
        if (cVar7 == '\0') goto LAB_001524d0;
      }
      if (cVar7 == ']') {
        iVar10 = iVar10 + -1;
      }
      else if (cVar7 == ',' && iVar10 == 0) {
        sVar23 = (long)pcVar31 - (long)pcVar30;
        pcVar15 = acStack_168 + 0x40;
        if (0x3f < sVar23) {
          sVar23 = 0x3f;
        }
        __s = acStack_e9 + 1;
        memcpy(pcVar15,pcVar30,sVar23);
        pcVar15[sVar23] = '\0';
        snprintf(__s,0x40,"%s",pcVar31 + 1);
        cVar7 = acStack_168[0x40];
        if (acStack_168[0x40] == '\0') goto LAB_00152658;
        sVar23 = strlen(pcVar15);
        pcVar31 = pcVar15 + (sVar23 - 1);
        if (pcVar15 + (sVar23 - 1) <= pcVar15) goto LAB_0015261c;
        goto LAB_0015260c;
      }
      pcVar31 = pcVar31 + 1;
      cVar7 = *pcVar31;
    } while (cVar7 != '\0');
  }
LAB_001524d0:
  pcVar31 = acStack_168 + 0x40;
  snprintf(pcVar31,0x40,"%s",pcVar30);
  cVar7 = acStack_168[0x40];
  if (acStack_168[0x40] != '\0') {
    sVar23 = strlen(pcVar31);
    pcVar30 = pcVar31 + (sVar23 - 1);
    if (pcVar31 < pcVar31 + (sVar23 - 1)) {
      do {
        cVar7 = acStack_168[0x40];
        if (*pcVar30 != ' ') break;
        pcVar15 = pcVar30 + -1;
        *pcVar30 = '\0';
        pcVar30 = pcVar15;
        cVar7 = acStack_168[0x40];
      } while (pcVar15 != pcVar31);
    }
    pcVar30 = pcVar31;
    if (cVar7 == ' ') {
      do {
        pcVar30 = pcVar30 + 1;
      } while (*pcVar30 == ' ');
      if (pcVar30 != pcVar31) {
        sVar23 = strlen(pcVar30);
        __memmove_chk(pcVar31,pcVar30,sVar23 + 1,0x40);
      }
    }
  }
  uStack_2b0 = 0xfffffffe;
  uStack_2ac = 0xfffffffe;
  uStack_2a8 = 0xfffffffe;
  uStack_2a4 = 4;
  uStack_2a0 = 4;
  uStack_29c = 4;
  iVar10 = arm64_reg_lookup(acStack_168,&uStack_2b0,&uStack_2a4);
  if (iVar10 == 0) {
    uStack_2b0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar31,&uStack_2ac,&uStack_2a0);
  }
  else {
    iVar10 = arm64_reg_lookup(pcVar31,&uStack_2ac,&uStack_2a0);
  }
  if (iVar10 == 0) {
    iVar10 = 2;
    goto LAB_00152880;
  }
  uVar38 = 0;
  iVar10 = 2;
  bVar4 = false;
  bVar5 = false;
  uStack_310 = 0;
LAB_00152754:
  iVar9 = strcmp(pcVar19,"adrp");
  uVar22 = uStack_2b0;
  if (iVar9 == 0) {
    if ((int)uStack_2b0 < 0) goto LAB_00152170;
    if (bVar4) {
LAB_00152800:
      if (uVar38 != 0) {
        iVar8 = arm_emit_const(puVar1,plStack_298,uVar38,uVar13);
        if (iVar8 == -1) goto LAB_001529c4;
        *(int *)((long)&uStack_1f8 + (long)(int)uVar22 * 4) = iVar8;
        *(undefined4 *)((long)&uStack_280 + (long)(int)uVar22 * 4) = 5;
        goto LAB_00152170;
      }
    }
    else if (iVar10 != 1) {
      pcVar19 = acStack_168 + 0x40;
      cVar7 = acStack_168[0x40];
      while (cVar7 == ' ') {
        pcVar19 = pcVar19 + 1;
        cVar7 = *pcVar19;
      }
      if (cVar7 == '#') {
        pcVar31 = pcVar19 + 1;
        pcVar19 = pcVar19 + 1;
        cVar7 = *pcVar31;
        while (cVar7 == ' ') {
          pcVar19 = pcVar19 + 1;
          cVar7 = *pcVar19;
        }
      }
      iVar8 = __isoc99_sscanf(pcVar19,"0x%lx",&uStack_290);
      if (iVar8 == 1) {
        uVar38 = CONCAT44(uStack_28c,uStack_290);
      }
      else {
        iVar8 = __isoc99_sscanf(pcVar19,&DAT_001fa008,&uStack_288);
        if (iVar8 != 1) goto LAB_0015277c;
        uVar38 = CONCAT44(uStack_288._4_4_,(int)uStack_288);
      }
      goto LAB_00152800;
    }
LAB_0015277c:
    lVar35 = plStack_298[2];
    *(int *)((long)&uStack_1f8 + (long)(int)uVar22 * 4) = (int)lVar35;
    *(undefined4 *)((long)&uStack_280 + (long)(int)uVar22 * 4) = 5;
    *(int *)(plStack_298 + 2) = (int)lVar35 + 1;
LAB_00152170:
    uVar11 = (undefined4)((ulong)uVar44 >> 0x20);
    uVar42 = (undefined4)((ulong)uVar43 >> 0x20);
    iVar8 = (int)uVar44;
    iVar41 = (int)uVar43;
  }
  else {
LAB_00151f14:
    iVar9 = strcmp(pcVar19,"mov");
    if (((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"movz"), iVar9 == 0)) ||
       (iVar9 = strcmp(pcVar19,"movk"), iVar9 == 0)) {
      uVar22 = uStack_2b0;
      if (-1 < (int)uStack_2b0) {
        uVar28 = *(uint *)(puVar1 + 2);
        uVar26 = *(uint *)((long)puVar1 + 0x14);
        iVar8 = (int)plStack_298[2];
        pvVar12 = (void *)puVar1[1];
        *(int *)(plStack_298 + 2) = iVar8 + 1;
        if (uVar26 <= uVar28) {
          if (uVar26 == 0) {
            sVar23 = 0x880;
            uVar26 = 0x10;
          }
          else {
            uVar26 = uVar26 << 1;
            sVar23 = (ulong)uVar26 * 0x88;
          }
          pvVar12 = realloc(pvVar12,sVar23);
          if (pvVar12 == (void *)0x0) goto LAB_001529c4;
          uVar28 = *(uint *)(puVar1 + 2);
          puVar1[1] = pvVar12;
          *(uint *)((long)puVar1 + 0x14) = uVar26;
        }
        *(uint *)(puVar1 + 2) = uVar28 + 1;
        puVar16 = (undefined8 *)((long)pvVar12 + (ulong)uVar28 * 0x88);
        puVar16[1] = 0;
        *puVar16 = 0;
        puVar16[3] = 0;
        puVar16[2] = 0;
        puVar16[5] = 0;
        puVar16[4] = 0;
        puVar16[7] = 0;
        puVar16[6] = 0;
        puVar16[9] = 0;
        puVar16[8] = 0;
        puVar16[0xb] = 0;
        puVar16[10] = 0;
        puVar16[0xd] = 0;
        puVar16[0xc] = 0;
        puVar16[0xf] = 0;
        puVar16[0xe] = 0;
        puVar16[0x10] = 0;
        if (uStack_2ac < 0x20) {
          iVar41 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2ac * 4);
          if (iVar41 == -1) {
            iVar41 = (int)plStack_298[2];
            *(int *)(plStack_298 + 2) = iVar41 + 1;
          }
          uVar38 = 0;
          *(int *)(puVar16 + 3) = iVar41;
          *(undefined4 *)((long)puVar16 + 0x1c) = uStack_2a0;
          puVar16[4] = 0;
          *(undefined4 *)(puVar16 + 9) = 1;
        }
        else if ((uStack_2ac == 0xffffffff) || (!bVar4)) {
          uVar38 = 0;
          *(undefined4 *)puVar16 = 1;
        }
        else {
          *(undefined4 *)puVar16 = 1;
        }
        *(int *)(puVar16 + 1) = iVar8;
        *(undefined4 *)((long)puVar16 + 0xc) = uStack_2a4;
        puVar16[2] = uVar38;
        *(undefined4 *)((long)&uStack_280 + (long)(int)uVar22 * 4) = uStack_2a4;
        *(int *)((long)&uStack_1f8 + (long)(int)uVar22 * 4) = iVar8;
        puVar16[0xe] = uVar13;
      }
      goto LAB_00152170;
    }
    iVar9 = strcmp(pcVar19,"add");
    if ((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"adds"), iVar9 == 0)) {
      uVar11 = 2;
LAB_00151f60:
      uVar42 = uStack_2a4;
      uVar22 = uStack_2b0;
      if (iVar10 == 3) {
        if ((int)uStack_2b0 < 0) {
LAB_00152f6c:
          iVar10 = strcmp(pcVar19,"ldr");
          if (iVar10 != 0) goto LAB_00152f80;
        }
        else {
          if (uStack_2ac < 0x20) {
            iVar8 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2ac * 4);
            if (iVar8 == -1) {
              iVar8 = (int)plStack_298[2];
              *(int *)(plStack_298 + 2) = iVar8 + 1;
            }
            uVar27 = 0;
            uVar42 = uStack_2a0;
          }
          else if (uStack_2ac == 0xffffffff) {
            auVar45 = arm_emit_const(puVar1,plStack_298,0,uVar13);
            uVar27 = auVar45._8_8_;
            iVar8 = auVar45._0_4_;
            uVar42 = auVar45._4_4_;
            if (iVar8 == -1) goto LAB_001529c4;
          }
          else {
            iVar8 = (int)plStack_298[2];
            uVar27 = 0;
            *(int *)(plStack_298 + 2) = iVar8 + 1;
          }
          if (uStack_2a8 < 0x20) {
            iVar41 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2a8 * 4);
            iVar9 = (int)plStack_298[2];
            iVar10 = iVar9;
            if (iVar41 == -1) {
              iVar10 = iVar9 + 1;
              *(int *)(plStack_298 + 2) = iVar10;
              iVar41 = iVar9;
            }
            uVar34 = 0;
            uVar37 = uStack_29c;
          }
          else if (uStack_2a8 == 0xffffffff) {
            auVar45 = arm_emit_const(puVar1,plStack_298,0,uVar13);
            uVar34 = auVar45._8_8_;
            iVar41 = auVar45._0_4_;
            uVar37 = auVar45._4_4_;
            if (iVar41 == -1) goto LAB_001529c4;
            iVar10 = (int)plStack_298[2];
          }
          else if (bVar5) {
            auVar45 = arm_emit_const(puVar1,plStack_298,uStack_310,uVar13);
            uVar34 = auVar45._8_8_;
            iVar41 = auVar45._0_4_;
            uVar37 = auVar45._4_4_;
            if (iVar41 == -1) goto LAB_001529c4;
            iVar10 = (int)plStack_298[2];
          }
          else {
            iVar41 = (int)plStack_298[2];
            uVar34 = 0;
            iVar10 = iVar41 + 1;
            *(int *)(plStack_298 + 2) = iVar10;
            uVar37 = uStack_2a4;
          }
          uVar28 = *(uint *)(puVar1 + 2);
          uVar26 = *(uint *)((long)puVar1 + 0x14);
          *(int *)(plStack_298 + 2) = iVar10 + 1;
          pvVar12 = (void *)puVar1[1];
          if (uVar26 <= uVar28) {
            if (uVar26 == 0) {
              sVar23 = 0x880;
              uVar26 = 0x10;
            }
            else {
              uVar26 = uVar26 << 1;
              sVar23 = (ulong)uVar26 * 0x88;
            }
            pvVar12 = realloc(pvVar12,sVar23);
            if (pvVar12 == (void *)0x0) goto LAB_001529c4;
            puVar1[1] = pvVar12;
            uVar28 = *(uint *)(puVar1 + 2);
            *(uint *)((long)puVar1 + 0x14) = uVar26;
          }
          *(uint *)(puVar1 + 2) = uVar28 + 1;
          puVar16 = (undefined8 *)((long)pvVar12 + (ulong)uVar28 * 0x88);
          *(int *)((long)&uStack_1f8 + (long)(int)uVar22 * 4) = iVar10;
          *(undefined4 *)((long)&uStack_280 + (long)(int)uVar22 * 4) = uStack_2a4;
          puVar16[1] = 0;
          *puVar16 = 0;
          puVar16[3] = 0;
          puVar16[2] = 0;
          puVar16[5] = 0;
          puVar16[4] = 0;
          puVar16[7] = 0;
          puVar16[6] = 0;
          puVar16[9] = 0;
          puVar16[8] = 0;
          puVar16[0xb] = 0;
          puVar16[10] = 0;
          puVar16[0xd] = 0;
          puVar16[0xc] = 0;
          puVar16[0xf] = 0;
          puVar16[0xe] = 0;
          puVar16[0x10] = 0;
          *(undefined4 *)((long)pvVar12 + (ulong)uVar28 * 0x88) = uVar11;
          *(int *)(puVar16 + 1) = iVar10;
          *(undefined4 *)((long)puVar16 + 0xc) = uStack_2a4;
          *(int *)(puVar16 + 3) = iVar8;
          *(undefined4 *)((long)puVar16 + 0x1c) = uVar42;
          puVar16[4] = uVar27;
          *(int *)(puVar16 + 5) = iVar41;
          *(undefined4 *)((long)puVar16 + 0x2c) = uVar37;
          puVar16[6] = uVar34;
          *(undefined4 *)(puVar16 + 9) = 2;
          puVar16[0xe] = uVar13;
        }
      }
      else {
        if (iVar10 != 2) goto LAB_00152b3c;
        if ((int)uStack_2b0 < 0) goto LAB_00152f6c;
        lVar35 = (long)(int)uStack_2b0;
        iVar8 = *(int *)((long)&uStack_1f8 + lVar35 * 4);
        if (iVar8 == -1) {
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 1;
        }
        if (uStack_2ac < 0x20) {
          iVar10 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2ac * 4);
          iVar9 = (int)plStack_298[2];
          iVar41 = iVar9;
          if (iVar10 == -1) {
            iVar41 = iVar9 + 1;
            *(int *)(plStack_298 + 2) = iVar41;
            iVar10 = iVar9;
          }
          uVar27 = 0;
          uVar37 = uStack_2a0;
        }
        else if (bVar4) {
          auVar45 = arm_emit_const(puVar1,plStack_298,uVar38,uVar13);
          uVar27 = auVar45._8_8_;
          iVar10 = auVar45._0_4_;
          uVar37 = auVar45._4_4_;
          if (iVar10 == -1) goto LAB_001529c4;
          iVar41 = (int)plStack_298[2];
        }
        else {
          iVar10 = (int)plStack_298[2];
          uVar27 = 0;
          iVar41 = iVar10 + 1;
          *(int *)(plStack_298 + 2) = iVar41;
          uVar37 = uStack_2a4;
        }
        uVar22 = *(uint *)(puVar1 + 2);
        uVar28 = *(uint *)((long)puVar1 + 0x14);
        *(int *)(plStack_298 + 2) = iVar41 + 1;
        pvVar12 = (void *)puVar1[1];
        if (uVar28 <= uVar22) {
          if (uVar28 == 0) {
            sVar23 = 0x880;
            uVar28 = 0x10;
          }
          else {
            uVar28 = uVar28 << 1;
            sVar23 = (ulong)uVar28 * 0x88;
          }
          pvVar12 = realloc(pvVar12,sVar23);
          if (pvVar12 == (void *)0x0) goto LAB_001529c4;
          uVar22 = *(uint *)(puVar1 + 2);
          puVar1[1] = pvVar12;
          *(uint *)((long)puVar1 + 0x14) = uVar28;
        }
        *(uint *)(puVar1 + 2) = uVar22 + 1;
        *(int *)((long)&uStack_1f8 + lVar35 * 4) = iVar41;
        puVar16 = (undefined8 *)((long)pvVar12 + (ulong)uVar22 * 0x88);
        *(undefined4 *)((long)&uStack_280 + lVar35 * 4) = uVar42;
        puVar16[1] = 0;
        *puVar16 = 0;
        puVar16[3] = 0;
        puVar16[2] = 0;
        puVar16[5] = 0;
        puVar16[4] = 0;
        puVar16[7] = 0;
        puVar16[6] = 0;
        puVar16[9] = 0;
        puVar16[8] = 0;
        puVar16[0xb] = 0;
        puVar16[10] = 0;
        puVar16[0xd] = 0;
        puVar16[0xc] = 0;
        puVar16[0xf] = 0;
        puVar16[0xe] = 0;
        puVar16[0x10] = 0;
        *(undefined4 *)((long)pvVar12 + (ulong)uVar22 * 0x88) = uVar11;
        *(int *)(puVar16 + 1) = iVar41;
        *(undefined4 *)((long)puVar16 + 0xc) = uVar42;
        *(int *)(puVar16 + 3) = iVar8;
        *(undefined4 *)((long)puVar16 + 0x1c) = uVar42;
        *(int *)(puVar16 + 5) = iVar10;
        *(undefined4 *)((long)puVar16 + 0x2c) = uVar37;
        puVar16[6] = uVar27;
        *(undefined4 *)(puVar16 + 9) = 2;
        puVar16[0xe] = uVar13;
      }
      goto LAB_00152170;
    }
    iVar9 = strcmp(pcVar19,"sub");
    if ((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"subs"), iVar9 == 0)) {
      uVar11 = 3;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"mul");
    if (iVar9 == 0) {
      uVar11 = 4;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"sdiv");
    if ((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"udiv"), iVar9 == 0)) {
      uVar11 = 5;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"and");
    if ((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"ands"), iVar9 == 0)) {
      uVar11 = 6;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"orr");
    if (iVar9 == 0) {
      uVar11 = 7;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"eor");
    if (iVar9 == 0) {
      uVar11 = 8;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"lsl");
    if (iVar9 == 0) {
      uVar11 = 9;
      goto LAB_00151f60;
    }
    iVar9 = strcmp(pcVar19,"lsr");
    if ((iVar9 == 0) || (iVar9 = strcmp(pcVar19,"asr"), iVar9 == 0)) {
      uVar11 = 10;
      goto LAB_00151f60;
    }
LAB_00152b3c:
    iVar10 = strcmp(pcVar19,"ldr");
    uVar22 = uStack_2b0;
    if (iVar10 == 0) {
      if ((int)uStack_2b0 < 0) goto LAB_00152170;
      iVar8 = strcmp(pcVar19,"ldrb");
      uVar11 = 1;
      if ((iVar8 != 0) && (iVar8 = strcmp(pcVar19,"ldrh"), uVar11 = uStack_2a4, iVar8 == 0)) {
        uVar11 = 2;
      }
LAB_00152b90:
      arm64_parse_mem_op_isra_0(acStack_168 + 0x40,&uStack_290,&uStack_288);
      uVar28 = *(uint *)(puVar1 + 2);
      uVar26 = *(uint *)((long)puVar1 + 0x14);
      iVar8 = (int)plStack_298[2];
      *(int *)(plStack_298 + 2) = iVar8 + 1;
      if (uVar28 < uVar26) {
        pvVar12 = (void *)puVar1[1];
      }
      else {
        if (uVar26 == 0) {
          sVar23 = 0x880;
          uVar26 = 0x10;
        }
        else {
          uVar26 = uVar26 << 1;
          sVar23 = (ulong)uVar26 * 0x88;
        }
        pvVar12 = realloc((void *)puVar1[1],sVar23);
        if (pvVar12 == (void *)0x0) goto LAB_001529c4;
        uVar28 = *(uint *)(puVar1 + 2);
        puVar1[1] = pvVar12;
        *(uint *)((long)puVar1 + 0x14) = uVar26;
      }
      *(uint *)(puVar1 + 2) = uVar28 + 1;
      puVar16 = (undefined8 *)((long)pvVar12 + (ulong)uVar28 * 0x88);
      puVar16[0x10] = 0;
      puVar16[1] = 0;
      *puVar16 = 0;
      puVar16[3] = 0;
      puVar16[2] = 0;
      puVar16[5] = 0;
      puVar16[4] = 0;
      puVar16[7] = 0;
      puVar16[6] = 0;
      puVar16[9] = 0;
      puVar16[8] = 0;
      puVar16[0xb] = 0;
      puVar16[10] = 0;
      puVar16[0xd] = 0;
      puVar16[0xc] = 0;
      puVar16[0xf] = 0;
      puVar16[0xe] = 0;
      iVar41 = *(int *)(puVar1 + 2);
      *(undefined4 *)((long)pvVar12 + (ulong)uVar28 * 0x88) = 0x15;
      *(int *)(puVar16 + 1) = iVar8;
      *(undefined4 *)((long)puVar16 + 0xc) = uVar11;
      if (uStack_290 < 0x20) {
        lVar35 = (long)(int)uStack_290;
        iVar10 = *(int *)((long)&uStack_1f8 + lVar35 * 4);
        if (iVar10 == -1) goto LAB_0015307c;
        auVar45 = arm_emit_const(puVar1,plStack_298,CONCAT44(uStack_288._4_4_,(int)uStack_288),
                                 uVar13);
        if (auVar45._0_4_ == -1) goto LAB_001529c4;
        uVar28 = *(uint *)(puVar1 + 2);
        uVar26 = *(uint *)((long)puVar1 + 0x14);
        iVar9 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar9 + 1;
        pvVar12 = (void *)puVar1[1];
        if (uVar26 <= uVar28) {
          if (uVar26 == 0) {
            sVar23 = 0x880;
            uVar26 = 0x10;
          }
          else {
            uVar26 = uVar26 << 1;
            sVar23 = (ulong)uVar26 * 0x88;
          }
          pvVar12 = realloc(pvVar12,sVar23);
          if (pvVar12 == (void *)0x0) goto LAB_001529c4;
          puVar1[1] = pvVar12;
          uVar28 = *(uint *)(puVar1 + 2);
          *(uint *)((long)puVar1 + 0x14) = uVar26;
        }
        *(uint *)(puVar1 + 2) = uVar28 + 1;
        lVar33 = (ulong)uVar28 * 0x88;
        uVar42 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x84) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0xc) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 4) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x1c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x14) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x2c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x24) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x3c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x34) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x4c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x44) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x5c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x54) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x6c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 100) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x7c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x74) = 0;
        lVar35 = puVar1[1];
        *(undefined4 *)((long)pvVar12 + lVar33) = 2;
        *(int *)((long)pvVar12 + lVar33 + 8) = iVar9;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0xc) = 5;
        *(int *)((long)pvVar12 + lVar33 + 0x18) = iVar10;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x1c) = uVar42;
        puVar16 = (undefined8 *)(lVar35 + (ulong)(iVar41 - 1) * 0x88);
        *(undefined1 (*) [16])((long)pvVar12 + lVar33 + 0x28) = auVar45;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x48) = 2;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x70) = uVar13;
        *(int *)(puVar16 + 3) = iVar9;
        *(undefined4 *)((long)puVar16 + 0x1c) = 5;
        puVar16[4] = 0;
      }
      else {
LAB_0015307c:
        puVar16[3] = DAT_0020bf28;
      }
      *(undefined4 *)(puVar16 + 9) = 1;
      *(int *)((long)&uStack_1f8 + (long)(int)uVar22 * 4) = iVar8;
      *(undefined4 *)((long)&uStack_280 + (long)(int)uVar22 * 4) = uVar11;
      puVar16[0xe] = uVar13;
      goto LAB_00152170;
    }
LAB_00152f80:
    iVar10 = strcmp(pcVar19,"ldrb");
    if (iVar10 == 0) {
      uVar11 = 1;
joined_r0x00153124:
      uVar22 = uStack_2b0;
      if ((int)uStack_2b0 < 0) goto LAB_00152170;
      goto LAB_00152b90;
    }
    iVar10 = strcmp(pcVar19,"ldrh");
    if (iVar10 == 0) {
      uVar11 = 2;
      goto joined_r0x00153124;
    }
    iVar10 = strcmp(pcVar19,"ldrsw");
    if (iVar10 == 0) {
      uVar22 = uStack_2b0;
      uVar11 = uStack_2a4;
      if (-1 < (int)uStack_2b0) goto LAB_00152b90;
      goto LAB_00152170;
    }
    iVar10 = strcmp(pcVar19,"str");
    if (((iVar10 == 0) || (iVar10 = strcmp(pcVar19,"strb"), iVar10 == 0)) ||
       (iVar10 = strcmp(pcVar19,"strh"), iVar10 == 0)) {
      arm64_parse_mem_op_isra_0(acStack_168 + 0x40,&uStack_290,&uStack_288);
      uVar22 = *(uint *)(puVar1 + 2);
      uVar28 = *(uint *)((long)puVar1 + 0x14);
      if (uVar22 < uVar28) {
        pvVar12 = (void *)puVar1[1];
      }
      else {
        if (uVar28 == 0) {
          sVar23 = 0x880;
          uVar28 = 0x10;
        }
        else {
          uVar28 = uVar28 << 1;
          sVar23 = (ulong)uVar28 * 0x88;
        }
        pvVar12 = realloc((void *)puVar1[1],sVar23);
        if (pvVar12 == (void *)0x0) goto LAB_001529c4;
        uVar22 = *(uint *)(puVar1 + 2);
        puVar1[1] = pvVar12;
        *(uint *)((long)puVar1 + 0x14) = uVar28;
      }
      *(uint *)(puVar1 + 2) = uVar22 + 1;
      puVar16 = (undefined8 *)((long)pvVar12 + (ulong)uVar22 * 0x88);
      puVar16[0x10] = 0;
      puVar16[1] = 0;
      *puVar16 = 0;
      puVar16[3] = 0;
      puVar16[2] = 0;
      puVar16[5] = 0;
      puVar16[4] = 0;
      puVar16[7] = 0;
      puVar16[6] = 0;
      puVar16[9] = 0;
      puVar16[8] = 0;
      puVar16[0xb] = 0;
      puVar16[10] = 0;
      puVar16[0xd] = 0;
      puVar16[0xc] = 0;
      puVar16[0xf] = 0;
      puVar16[0xe] = 0;
      iVar8 = *(int *)(puVar1 + 2);
      *(undefined4 *)((long)pvVar12 + (ulong)uVar22 * 0x88) = 0x16;
      *(undefined4 *)(puVar16 + 1) = 0xffffffff;
      if (uStack_290 < 0x20) {
        lVar35 = (long)(int)uStack_290;
        iVar41 = *(int *)((long)&uStack_1f8 + lVar35 * 4);
        if (iVar41 == -1) goto LAB_001535e4;
        auVar45 = arm_emit_const(puVar1,plStack_298,CONCAT44(uStack_288._4_4_,(int)uStack_288),
                                 uVar13);
        if (auVar45._0_4_ == -1) goto LAB_001529c4;
        uVar22 = *(uint *)(puVar1 + 2);
        uVar28 = *(uint *)((long)puVar1 + 0x14);
        iVar10 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar10 + 1;
        pvVar12 = (void *)puVar1[1];
        if (uVar28 <= uVar22) {
          if (uVar28 == 0) {
            sVar23 = 0x880;
            uVar28 = 0x10;
          }
          else {
            uVar28 = uVar28 << 1;
            sVar23 = (ulong)uVar28 * 0x88;
          }
          pvVar12 = realloc(pvVar12,sVar23);
          if (pvVar12 == (void *)0x0) goto LAB_001529c4;
          puVar1[1] = pvVar12;
          uVar22 = *(uint *)(puVar1 + 2);
          *(uint *)((long)puVar1 + 0x14) = uVar28;
        }
        *(uint *)(puVar1 + 2) = uVar22 + 1;
        lVar33 = (ulong)uVar22 * 0x88;
        uVar11 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x84) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0xc) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 4) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x1c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x14) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x2c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x24) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x3c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x34) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x4c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x44) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x5c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x54) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x6c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 100) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x7c) = 0;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x74) = 0;
        lVar35 = puVar1[1];
        *(undefined4 *)((long)pvVar12 + lVar33) = 2;
        *(int *)((long)pvVar12 + lVar33 + 8) = iVar10;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0xc) = 5;
        *(int *)((long)pvVar12 + lVar33 + 0x18) = iVar41;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x1c) = uVar11;
        puVar16 = (undefined8 *)(lVar35 + (ulong)(iVar8 - 1U) * 0x88);
        *(undefined1 (*) [16])((long)pvVar12 + lVar33 + 0x28) = auVar45;
        *(undefined4 *)((long)pvVar12 + lVar33 + 0x48) = 2;
        *(undefined8 *)((long)pvVar12 + lVar33 + 0x70) = uVar13;
        *(int *)(puVar16 + 3) = iVar10;
        *(undefined4 *)((long)puVar16 + 0x1c) = 5;
        puVar16[4] = 0;
      }
      else {
LAB_001535e4:
        puVar16[3] = DAT_0020bf28;
      }
      if (uStack_2b0 == 0xffffffff) {
        auVar45 = arm_emit_const(puVar1,plStack_298,0,uVar13);
        if (auVar45._0_4_ == -1) goto LAB_001529c4;
        puVar16 = (undefined8 *)(puVar1[1] + (ulong)(iVar8 - 1U) * 0x88);
        *(undefined1 (*) [16])(puVar16 + 5) = auVar45;
      }
      else {
        if (uStack_2b0 < 0x20) {
          iVar8 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2b0 * 4);
          if (iVar8 == -1) goto LAB_0015363c;
          uVar11 = *(undefined4 *)((long)&uStack_280 + (long)(int)uStack_2b0 * 4);
        }
        else {
LAB_0015363c:
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 1;
          uVar11 = uStack_2a4;
        }
        *(int *)(puVar16 + 5) = iVar8;
        *(undefined4 *)((long)puVar16 + 0x2c) = uVar11;
        puVar16[6] = 0;
      }
      *(undefined4 *)(puVar16 + 9) = 2;
      puVar16[0xe] = uVar13;
      goto LAB_00152170;
    }
    iVar10 = strcmp(pcVar19,"ldp");
    if (iVar10 == 0) {
      arm64_parse_mem_op_isra_0(acStack_e9 + 1,&uStack_290,&uStack_288);
      uVar38 = (ulong)uStack_2b0;
      if ((int)uStack_2b0 < 0) {
        lVar35 = 1;
        goto LAB_001538f4;
      }
      lVar35 = 0;
      uVar11 = uStack_2a4;
LAB_001537e4:
      do {
        iVar8 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar8 + 1;
        puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
        if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
        iVar41 = *(int *)(puVar1 + 2);
        *puVar17 = 0x15;
        puVar17[2] = iVar8;
        puVar17[3] = uVar11;
        *(undefined8 *)(puVar17 + 4) = 0;
        if ((uStack_290 < 0x20) &&
           (iVar10 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_290 * 4), iVar10 != -1)) {
          auVar45 = arm_emit_const(puVar1,plStack_298,
                                   CONCAT44(uStack_288._4_4_,(int)uStack_288) + lVar35 * 8,uVar13);
          if (auVar45._0_4_ == -1) goto LAB_001529c4;
          iVar9 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar9 + 1;
          puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
          if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
          puVar17 = (undefined4 *)(puVar1[1] + (ulong)(iVar41 - 1) * 0x88);
          *(undefined8 *)(puVar20 + 8) = 0;
          *(long *)(puVar20 + 10) = auVar45._0_8_;
          *puVar20 = 2;
          puVar20[2] = iVar9;
          puVar20[3] = 5;
          *(undefined8 *)(puVar20 + 4) = 0;
          puVar20[6] = iVar10;
          puVar20[7] = 5;
          *(long *)(puVar20 + 0xc) = auVar45._8_8_;
          puVar20[0x12] = 2;
          *(undefined8 *)(puVar20 + 0x1c) = uVar13;
          puVar17[6] = iVar9;
          puVar17[7] = 5;
          *(undefined8 *)(puVar17 + 8) = 0;
        }
        else {
          *(undefined8 *)(puVar17 + 8) = 0;
          *(undefined8 *)(puVar17 + 6) = DAT_0020bf28;
        }
        puVar17[0x12] = 1;
        *(undefined8 *)(puVar17 + 0x1c) = uVar13;
        if ((int)uVar38 < 0x20) {
          uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
          *(int *)((long)&uStack_1f8 + uVar38) = iVar8;
          *(undefined4 *)((long)&uStack_280 + uVar38) = uVar11;
        }
        lVar35 = lVar35 + 1;
        if (lVar35 == 2) break;
LAB_001538f4:
        for (; (int)lVar35 == 0; lVar35 = lVar35 + 1) {
          uVar38 = (ulong)uStack_2b0;
          uVar11 = uStack_2a4;
          if (-1 < (int)uStack_2b0) goto LAB_001537e4;
        }
        uVar38 = (ulong)uStack_2ac;
        uVar11 = uStack_2a0;
      } while (-1 < (int)uStack_2ac);
      goto LAB_00152170;
    }
    iVar10 = strcmp(pcVar19,"stp");
    if (iVar10 == 0) {
      arm64_parse_mem_op_isra_0(acStack_e9 + 1,&uStack_290,&uStack_288);
      uVar27 = DAT_0020bf28;
      lVar35 = 0;
      uVar22 = uStack_2b0;
      uVar11 = uStack_2a4;
      do {
        puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
        uVar28 = uStack_290;
        if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
        iVar8 = *(int *)(puVar1 + 2);
        *puVar17 = 0x16;
        *(undefined8 *)(puVar17 + 2) = 0xffffffff;
        if ((uStack_290 < 0x20) &&
           (iVar41 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_290 * 4), iVar41 != -1)) {
          auVar45 = arm_emit_const(puVar1,plStack_298,
                                   CONCAT44(uStack_288._4_4_,(int)uStack_288) + lVar35 * 8,uVar13);
          iVar10 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar10 + 1;
          puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
          if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
          lVar33 = puVar1[1];
          *(undefined8 *)(puVar20 + 4) = 0;
          puVar17 = (undefined4 *)(lVar33 + (ulong)(iVar8 - 1U) * 0x88);
          puVar20[2] = iVar10;
          puVar20[6] = iVar41;
          *puVar20 = 2;
          *(undefined8 *)(puVar20 + 8) = 0;
          *(long *)(puVar20 + 10) = auVar45._0_8_;
          puVar20[3] = 5;
          puVar20[7] = 5;
          *(long *)(puVar20 + 0xc) = auVar45._8_8_;
          puVar20[0x12] = 2;
          *(undefined8 *)(puVar20 + 0x1c) = uVar13;
          puVar17[6] = iVar10;
          puVar17[7] = 5;
          *(undefined8 *)(puVar17 + 8) = 0;
        }
        else {
          *(undefined8 *)(puVar17 + 6) = uVar27;
          *(undefined8 *)(puVar17 + 8) = 0;
        }
        if (uVar22 == 0xffffffff) {
          auVar45 = arm_emit_const(puVar1,plStack_298,0,uVar13);
          if (auVar45._0_4_ == -1) goto LAB_001529c4;
          puVar17 = (undefined4 *)(puVar1[1] + (ulong)(iVar8 - 1U) * 0x88);
          *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
        }
        else {
          if (uVar22 < 0x20) {
            uVar38 = -(ulong)(uVar22 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar22 << 2;
            iVar8 = *(int *)((long)&uStack_1f8 + uVar38);
            if (iVar8 == -1) goto LAB_00154b58;
            uVar11 = *(undefined4 *)((long)&uStack_280 + uVar38);
          }
          else {
LAB_00154b58:
            iVar8 = (int)plStack_298[2];
            *(int *)(plStack_298 + 2) = iVar8 + 1;
          }
          puVar17[10] = iVar8;
          puVar17[0xb] = uVar11;
          *(undefined8 *)(puVar17 + 0xc) = 0;
        }
        puVar17[0x12] = 2;
        *(undefined8 *)(puVar17 + 0x1c) = uVar13;
        if (lVar35 != 0) goto LAB_00153b74;
        lVar35 = 1;
        uVar22 = uStack_2ac;
        uVar11 = uStack_2a0;
      } while( true );
    }
    iVar10 = strcmp(pcVar19,"cmp");
    if (iVar10 == 0) {
      if (uStack_2b0 < 0x20) {
        iVar8 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2b0 * 4);
        uVar11 = uStack_2a4;
        if (iVar8 == -1) {
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 1;
        }
      }
      else {
        iVar8 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar8 + 1;
        uVar11 = 4;
      }
      if (uStack_2ac < 0x20) {
        iVar41 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2ac * 4);
        if (iVar41 == -1) {
          iVar41 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar41 + 1;
        }
        uStack_2e0 = 0;
        uVar42 = uStack_2a0;
      }
      else {
        if (uStack_2ac == 0xffffffff) {
          uVar38 = 0;
        }
        else if (!bVar4) {
          iVar41 = (int)plStack_298[2];
          uVar42 = 4;
          uStack_2e0 = 0;
          *(int *)(plStack_298 + 2) = iVar41 + 1;
          goto LAB_001532dc;
        }
        auVar45 = arm_emit_const(puVar1,plStack_298,uVar38,uVar13);
        uStack_2e0 = auVar45._8_8_;
        iVar41 = auVar45._0_4_;
        uVar42 = auVar45._4_4_;
        if (iVar41 == -1) goto LAB_001529c4;
      }
LAB_001532dc:
      iStack_2d4 = (int)plStack_298[2];
      uVar22 = *(uint *)(puVar1 + 2);
      uVar28 = *(uint *)((long)puVar1 + 0x14);
      *(int *)(plStack_298 + 2) = iStack_2d4 + 1;
      if (uVar28 <= uVar22) {
        uVar26 = uVar28 << 1;
        if (uVar28 == 0) {
          uVar26 = 0x10;
        }
        pvVar12 = realloc((void *)puVar1[1],(ulong)uVar26 * 0x88);
        if (pvVar12 == (void *)0x0) goto LAB_001529c4;
        uVar22 = *(uint *)(puVar1 + 2);
        puVar1[1] = pvVar12;
        *(uint *)((long)puVar1 + 0x14) = uVar26;
      }
      lVar35 = puVar1[1];
      *(uint *)(puVar1 + 2) = uVar22 + 1;
      puVar16 = (undefined8 *)(lVar35 + (ulong)uVar22 * 0x88);
      puVar16[1] = 0;
      *puVar16 = 0;
      puVar16[3] = 0;
      puVar16[2] = 0;
      puVar16[5] = 0;
      puVar16[4] = 0;
      puVar16[7] = 0;
      puVar16[6] = 0;
      puVar16[9] = 0;
      puVar16[8] = 0;
      puVar16[0xb] = 0;
      puVar16[10] = 0;
      puVar16[0xd] = 0;
      puVar16[0xc] = 0;
      puVar16[0xf] = 0;
      puVar16[0xe] = 0;
      puVar16[0x10] = 0;
      *(undefined4 *)(lVar35 + (ulong)uVar22 * 0x88) = 0xb;
      *(int *)(puVar16 + 1) = iStack_2d4;
      *(undefined4 *)((long)puVar16 + 0xc) = 6;
      puVar16[6] = uStack_2e0;
      *(int *)(puVar16 + 3) = iVar8;
      *(undefined4 *)((long)puVar16 + 0x1c) = uVar11;
      *(int *)(puVar16 + 5) = iVar41;
      *(undefined4 *)((long)puVar16 + 0x2c) = uVar42;
      *(undefined4 *)(puVar16 + 9) = 2;
      puVar16[0xe] = uVar13;
    }
    else {
      iVar10 = strcmp(pcVar19,"ccmp");
      if (iVar10 != 0) {
        iVar10 = strcmp(pcVar19,"cbz");
        if (iVar10 == 0) {
          uVar11 = 0xb;
        }
        else {
          iVar10 = strcmp(pcVar19,"cbnz");
          if (iVar10 != 0) {
            iVar10 = strcmp(pcVar19,"tbz");
            if (iVar10 == 0) {
              uStack_310._0_4_ = 0xb;
            }
            else {
              iVar10 = strcmp(pcVar19,"tbnz");
              if (iVar10 != 0) {
                if ((*(char *)(lVar35 + 0x20) == 'b') && (*(char *)(lVar35 + 0x21) == '.')) {
                  if (iVar41 == -1 || iVar8 == -1) {
LAB_00154a4c:
                    iVar8 = iStack_2d4;
                    if (iStack_2d4 == -1) {
                      iVar8 = (int)plStack_298[2];
                      *(int *)(plStack_298 + 2) = iVar8 + 1;
                    }
                  }
                  else {
                    uVar11 = arm64_cond_suffix_to_cmp(lVar35 + 0x22,&uStack_288);
                    iVar8 = (int)plStack_298[2];
                    *(int *)(plStack_298 + 2) = iVar8 + 1;
                    puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                    if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                    *puVar17 = uVar11;
                    puVar17[2] = iVar8;
                    puVar17[3] = 6;
                    *(undefined8 *)(puVar17 + 4) = 0;
                    if ((int)uStack_288 == 0) {
                      uVar27 = uStack_2e0;
                      uVar34 = 0;
                      uVar25 = uVar43;
                      uVar39 = uVar44;
                    }
                    else {
                      uVar27 = 0;
                      uVar34 = uStack_2e0;
                      uVar25 = uVar44;
                      uVar39 = uVar43;
                    }
                    *(undefined8 *)(puVar17 + 0xc) = uVar27;
                    *(undefined8 *)(puVar17 + 6) = uVar39;
                    *(undefined8 *)(puVar17 + 8) = uVar34;
                    *(undefined8 *)(puVar17 + 10) = uVar25;
                    puVar17[0x12] = 2;
                    *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                    if (iVar8 == -1) goto LAB_00154a4c;
                  }
                  puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                  if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                  puVar17[0x12] = 1;
                  *puVar17 = 0x17;
                  *(undefined8 *)(puVar17 + 2) = 0xffffffff;
                  puVar17[6] = iVar8;
                  puVar17[7] = 6;
                  *(undefined8 *)(puVar17 + 8) = 0;
                  *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                  goto LAB_00152170;
                }
                iVar10 = strcmp(pcVar19,"csel");
                uVar22 = uStack_2b0;
                if (iVar10 != 0) {
                  iVar10 = strcmp(pcVar19,"cset");
                  iVar9 = strcmp(pcVar19,"csetm");
                  uVar22 = uStack_2b0;
                  if (iVar10 == 0) {
                    uVar27 = 0xffffffffffffffff;
                    if (iVar9 != 0) {
                      uVar27 = 1;
                    }
                  }
                  else {
                    if (iVar9 != 0) {
                      iVar10 = strcmp(pcVar19,"bl");
                      if (iVar10 == 0) {
                        iVar8 = (int)plStack_298[2];
                        *(int *)(plStack_298 + 2) = iVar8 + 1;
                        puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                        if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                        *puVar17 = 0x19;
                        puVar17[2] = iVar8;
                        puVar17[3] = 4;
                        *(undefined8 *)(puVar17 + 4) = 0;
                        if (acStack_168[0] == '#') {
                          uVar21 = strtoull(acStack_168 + 1,(char **)0x0,0);
                        }
                        else if (acStack_168[0] == '0') {
                          uVar21 = strtoull(acStack_168,(char **)0x0,0);
                        }
                        else {
                          uVar21 = 0;
                        }
                        *(ulonglong *)(puVar17 + 8) = uVar21;
                        uVar27 = DAT_0020bf28;
                        uVar38 = 0;
                        puVar17[0x12] = 1;
                        *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                        *(undefined8 *)(puVar17 + 6) = uVar27;
                        do {
                          if (*(int *)((long)&uStack_1f8 + uVar38 * 4) == -1) {
                            if ((int)uVar38 == 0) goto LAB_00154bbc;
                            break;
                          }
                          uVar38 = uVar38 + 1;
                        } while (uVar38 != 8);
                        puVar20 = malloc(-((uVar38 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                         (uVar38 & 0xffffffff) << 4);
                        *(undefined4 **)(puVar17 + 0x14) = puVar20;
                        if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
                        lVar35 = 0;
                        *(undefined8 *)(puVar17 + 0x16) = 0;
                        puVar17[0x18] = (int)uVar38;
                        do {
                          uVar11 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
                          lVar33 = lVar35 * 4;
                          lVar35 = lVar35 + 1;
                          *puVar20 = *(undefined4 *)((long)&uStack_1f8 + lVar33);
                          puVar20[1] = uVar11;
                          *(undefined8 *)(puVar20 + 2) = 0;
                          puVar20 = puVar20 + 4;
                        } while ((int)lVar35 < (int)uVar38);
LAB_00154bbc:
                        uStack_280 = CONCAT44(uStack_280._4_4_,4);
                        uStack_1f8 = CONCAT44(uStack_1f8._4_4_,iVar8);
                        goto LAB_00152170;
                      }
                      iVar10 = strcmp(pcVar19,"blr");
                      if (iVar10 != 0) {
                        iVar10 = strcmp(pcVar19,"br");
                        if (iVar10 == 0) {
                          iVar8 = (int)plStack_298[2];
                          *(int *)(plStack_298 + 2) = iVar8 + 1;
                          puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                          if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                          *puVar17 = 0x19;
                          puVar17[2] = iVar8;
                          puVar17[3] = 4;
                          *(undefined8 *)(puVar17 + 4) = 0;
                          if (uStack_2b0 < 0x20) {
                            uVar38 = -(ulong)(uStack_2b0 >> 0x1f) & 0xfffffffc00000000 |
                                     (ulong)uStack_2b0 << 2;
                            iVar41 = *(int *)((long)&uStack_1f8 + uVar38);
                            if (iVar41 == -1) goto LAB_001549f8;
                            uVar11 = *(undefined4 *)((long)&uStack_280 + uVar38);
                          }
                          else {
LAB_001549f8:
                            uVar11 = 5;
                            iVar41 = (int)plStack_298[2];
                            *(int *)(plStack_298 + 2) = iVar41 + 1;
                          }
                          puVar17[6] = iVar41;
                          puVar17[7] = uVar11;
                          uVar38 = 0;
                          *(undefined8 *)(puVar17 + 8) = 0;
                          puVar17[0x12] = 1;
                          *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                          do {
                            if (*(int *)((long)&uStack_1f8 + uVar38 * 4) == -1) {
                              if ((int)uVar38 == 0) goto LAB_001547bc;
                              break;
                            }
                            uVar38 = uVar38 + 1;
                          } while (uVar38 != 8);
                          puVar20 = malloc(-((uVar38 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                           (uVar38 & 0xffffffff) << 4);
                          *(undefined4 **)(puVar17 + 0x14) = puVar20;
                          if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
                          lVar35 = 0;
                          *(undefined8 *)(puVar17 + 0x16) = 0;
                          puVar17[0x18] = (int)uVar38;
                          do {
                            uVar11 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
                            lVar33 = lVar35 * 4;
                            lVar35 = lVar35 + 1;
                            *puVar20 = *(undefined4 *)((long)&uStack_1f8 + lVar33);
                            puVar20[1] = uVar11;
                            *(undefined8 *)(puVar20 + 2) = 0;
                            puVar20 = puVar20 + 4;
                          } while ((int)lVar35 < (int)uVar38);
LAB_001547bc:
                          uStack_280 = CONCAT44(uStack_280._4_4_,4);
                          uStack_1f8 = CONCAT44(uStack_1f8._4_4_,iVar8);
                          puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                          if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                          puVar17[0x12] = 1;
                          *puVar17 = 0x1a;
                          *(undefined8 *)(puVar17 + 2) = 0xffffffff;
                          puVar17[6] = iVar8;
                          puVar17[7] = 4;
                          *(undefined8 *)(puVar17 + 8) = 0;
                          *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                        }
                        else {
                          iVar10 = strcmp(pcVar19,"b");
                          if (iVar10 == 0) {
                            for (pcVar19 = acStack_168; cVar7 = *pcVar19,
                                cVar7 == ' ' || cVar7 == '#'; pcVar19 = pcVar19 + 1) {
                            }
                            if ((cVar7 != '\0') &&
                               (uVar21 = strtoull(pcVar19,(char **)&uStack_288,0),
                               (char *)CONCAT44(uStack_288._4_4_,(int)uStack_288) != pcVar19)) {
                              for (lVar35 = 0; (uint)lVar35 < *(uint *)(param_1 + 1);
                                  lVar35 = lVar35 + 1) {
                                if ((*(ulong *)(*param_1 + lVar35 * 0x20) <= uVar21) &&
                                   (uVar21 < *(ulong *)(*param_1 + lVar35 * 0x20 + 8)))
                                goto LAB_001545ec;
                              }
                              iVar8 = (int)plStack_298[2];
                              *(int *)(plStack_298 + 2) = iVar8 + 1;
                              puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                              if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                              puVar17[0x12] = 1;
                              uVar27 = DAT_0020bf28;
                              uVar38 = 0;
                              *puVar17 = 0x19;
                              puVar17[2] = iVar8;
                              puVar17[3] = 4;
                              *(undefined8 *)(puVar17 + 4) = 0;
                              *(ulonglong *)(puVar17 + 8) = uVar21;
                              *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                              *(undefined8 *)(puVar17 + 6) = uVar27;
                              do {
                                if (*(int *)((long)&uStack_1f8 + uVar38 * 4) == -1) {
                                  if ((int)uVar38 == 0) goto LAB_001547bc;
                                  break;
                                }
                                uVar38 = uVar38 + 1;
                              } while (uVar38 != 8);
                              puVar20 = malloc(-((uVar38 & 0xffffffff) >> 0x1f) & 0xfffffff000000000
                                               | (uVar38 & 0xffffffff) << 4);
                              *(undefined4 **)(puVar17 + 0x14) = puVar20;
                              if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
                              lVar35 = 0;
                              *(undefined8 *)(puVar17 + 0x16) = 0;
                              puVar17[0x18] = (int)uVar38;
                              do {
                                uVar11 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
                                lVar33 = lVar35 * 4;
                                lVar35 = lVar35 + 1;
                                *puVar20 = *(undefined4 *)((long)&uStack_1f8 + lVar33);
                                puVar20[1] = uVar11;
                                *(undefined8 *)(puVar20 + 2) = 0;
                                puVar20 = puVar20 + 4;
                              } while ((int)lVar35 < (int)uVar38);
                              goto LAB_001547bc;
                            }
LAB_001545ec:
                            puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                            if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                            *puVar17 = 0x18;
                            puVar17[0x12] = 0;
                            *(undefined8 *)(puVar17 + 2) = 0xffffffff;
                            *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                          }
                          else {
                            iVar10 = strcmp(pcVar19,"ret");
                            if (iVar10 == 0) {
                              puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                              if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                              *puVar17 = 0x1a;
                              *(undefined8 *)(puVar17 + 2) = 0xffffffff;
                              if ((int)uStack_1f8 == -1) {
                                uVar11 = 4;
                              }
                              else {
                                uVar11 = (undefined4)uStack_280;
                              }
                              puVar17[6] = (int)uStack_1f8;
                              puVar17[7] = uVar11;
                              *(undefined8 *)(puVar17 + 8) = 0;
                              puVar17[0x12] = 1;
                              *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                            }
                            else {
                              iVar10 = strcmp(pcVar19,"nop");
                              if (((((iVar10 != 0) && (iVar10 = strcmp(pcVar19,"hint"), iVar10 != 0)
                                    ) && ((iVar10 = strcmp(pcVar19,"yield"), iVar10 != 0 &&
                                          (((((iVar10 = strcmp(pcVar19,"sev"), iVar10 != 0 &&
                                              (iVar10 = strcmp(pcVar19,"sevl"), iVar10 != 0)) &&
                                             (iVar10 = strcmp(pcVar19,"wfi"), iVar10 != 0)) &&
                                            ((iVar10 = strcmp(pcVar19,"wfe"), iVar10 != 0 &&
                                             (iVar10 = strcmp(pcVar19,"isb"), iVar10 != 0)))) &&
                                           (iVar10 = strcmp(pcVar19,"dsb"), iVar10 != 0)))))) &&
                                  ((iVar10 = strcmp(pcVar19,"dmb"), iVar10 != 0 &&
                                   (iVar10 = strcmp(pcVar19,"paciasp"), iVar10 != 0)))) &&
                                 ((iVar10 = strcmp(pcVar19,"autiasp"), iVar10 != 0 &&
                                  (((iVar10 = strcmp(pcVar19,"pacibsp"), iVar10 != 0 &&
                                    (iVar10 = strcmp(pcVar19,"autibsp"), iVar10 != 0)) &&
                                   (iVar10 = strcmp(pcVar19,"bti"), iVar10 != 0)))))) {
                                puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                                if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                                *puVar17 = 0x1d;
                                puVar17[0x12] = 0;
                                *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                                *(undefined8 *)(puVar17 + 2) = 0xffffffff;
                                strncpy((char *)(puVar17 + 0x1e),pcVar19,0xf);
                                *(undefined1 *)((long)puVar17 + 0x87) = 0;
                                goto LAB_00152190;
                              }
                            }
                          }
                        }
                        goto LAB_00152170;
                      }
                      iVar8 = (int)plStack_298[2];
                      *(int *)(plStack_298 + 2) = iVar8 + 1;
                      puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                      if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                      *puVar17 = 0x19;
                      puVar17[2] = iVar8;
                      puVar17[3] = 4;
                      *(undefined8 *)(puVar17 + 4) = 0;
                      if (uStack_2b0 < 0x20) {
                        uVar38 = -(ulong)(uStack_2b0 >> 0x1f) & 0xfffffffc00000000 |
                                 (ulong)uStack_2b0 << 2;
                        iVar41 = *(int *)((long)&uStack_1f8 + uVar38);
                        if (iVar41 == -1) goto LAB_00154c14;
                        uVar11 = *(undefined4 *)((long)&uStack_280 + uVar38);
                      }
                      else {
LAB_00154c14:
                        uVar11 = 5;
                        iVar41 = (int)plStack_298[2];
                        *(int *)(plStack_298 + 2) = iVar41 + 1;
                      }
                      puVar17[6] = iVar41;
                      puVar17[7] = uVar11;
                      uVar38 = 0;
                      *(undefined8 *)(puVar17 + 8) = 0;
                      puVar17[0x12] = 1;
                      *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                      do {
                        if (*(int *)((long)&uStack_1f8 + uVar38 * 4) == -1) {
                          if ((int)uVar38 == 0) goto LAB_00154c04;
                          break;
                        }
                        uVar38 = uVar38 + 1;
                      } while (uVar38 != 8);
                      puVar20 = malloc(-((uVar38 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                       (uVar38 & 0xffffffff) << 4);
                      *(undefined4 **)(puVar17 + 0x14) = puVar20;
                      if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
                      lVar35 = 0;
                      *(undefined8 *)(puVar17 + 0x16) = 0;
                      puVar17[0x18] = (int)uVar38;
                      do {
                        uVar11 = *(undefined4 *)((long)&uStack_280 + lVar35 * 4);
                        lVar33 = lVar35 * 4;
                        lVar35 = lVar35 + 1;
                        *puVar20 = *(undefined4 *)((long)&uStack_1f8 + lVar33);
                        puVar20[1] = uVar11;
                        *(undefined8 *)(puVar20 + 2) = 0;
                        puVar20 = puVar20 + 4;
                      } while ((int)lVar35 < (int)uVar38);
LAB_00154c04:
                      uStack_280 = CONCAT44(uStack_280._4_4_,4);
                      uStack_1f8 = CONCAT44(uStack_1f8._4_4_,iVar8);
                      goto LAB_00152170;
                    }
                    uVar27 = 0xffffffffffffffff;
                  }
                  uVar38 = (ulong)uStack_2b0;
                  if ((int)uStack_2b0 < 0) goto LAB_00152170;
                  if (iVar41 == -1 || iVar8 == -1) {
LAB_00154238:
                    iVar8 = iStack_2d4;
                    if (iStack_2d4 == -1) {
                      iVar8 = (int)plStack_298[2];
                      *(int *)(plStack_298 + 2) = iVar8 + 1;
                    }
                  }
                  else {
                    plVar14 = plStack_298;
                    uVar11 = arm64_cond_suffix_to_cmp(acStack_168 + 0x40,&uStack_288);
                    iVar8 = (int)plVar14[2];
                    *(int *)(plVar14 + 2) = iVar8 + 1;
                    puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                    if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                    *puVar17 = uVar11;
                    puVar17[2] = iVar8;
                    puVar17[3] = 6;
                    *(undefined8 *)(puVar17 + 4) = 0;
                    if ((int)uStack_288 == 0) {
                      uVar34 = uStack_2e0;
                      uVar25 = 0;
                      uVar39 = uVar43;
                      uVar40 = uVar44;
                    }
                    else {
                      uVar34 = 0;
                      uVar25 = uStack_2e0;
                      uVar39 = uVar44;
                      uVar40 = uVar43;
                    }
                    *(undefined8 *)(puVar17 + 0xc) = uVar34;
                    *(undefined8 *)(puVar17 + 6) = uVar40;
                    *(undefined8 *)(puVar17 + 8) = uVar25;
                    *(undefined8 *)(puVar17 + 10) = uVar39;
                    puVar17[0x12] = 2;
                    *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                    if (iVar8 == -1) goto LAB_00154238;
                  }
                  auVar45 = arm_emit_const(puVar1,plStack_298,uVar27,uVar13);
                  if (auVar45._0_4_ == -1) goto LAB_001529c4;
                  auVar46 = arm_emit_const(puVar1,plStack_298,0,uVar13);
                  if (auVar46._0_4_ == -1) goto LAB_001529c4;
                  iVar41 = (int)plStack_298[2];
                  *(int *)(plStack_298 + 2) = iVar41 + 1;
                  puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                  if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                  uVar38 = -(ulong)(uVar22 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                  puVar17[2] = iVar41;
                  *(long *)(puVar17 + 0x10) = auVar46._8_8_;
                  *(int *)((long)&uStack_1f8 + uVar38) = iVar41;
                  *puVar17 = 0x1c;
                  puVar17[7] = 6;
                  *(undefined4 *)((long)&uStack_280 + uVar38) = uStack_2a4;
                  puVar17[3] = uStack_2a4;
                  *(undefined8 *)(puVar17 + 4) = 0;
                  puVar17[6] = iVar8;
                  *(undefined8 *)(puVar17 + 8) = 0;
                  *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
                  *(long *)(puVar17 + 0xe) = auVar46._0_8_;
                  puVar17[0x12] = 3;
                  *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                  goto LAB_00152170;
                }
                uVar38 = (ulong)uStack_2b0;
                if ((int)uStack_2b0 < 0) goto LAB_00152170;
                iVar10 = (int)plStack_298[2];
                *(int *)(plStack_298 + 2) = iVar10 + 1;
                puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
                *puVar17 = 0x1c;
                if (iVar41 == -1 || iVar8 == -1) {
LAB_00154b24:
                  iVar8 = iStack_2d4;
                  if (iStack_2d4 == -1) {
                    iVar8 = (int)plStack_298[2];
                    *(int *)(plStack_298 + 2) = iVar8 + 1;
                  }
                }
                else {
                  uStack_178 = 0;
                  pcVar19 = strchr(acStack_e9 + 1,0x2c);
                  if (pcVar19 != (char *)0x0) {
                    do {
                      pcVar31 = pcVar19 + 1;
                      pcVar19 = pcVar19 + 1;
                    } while (*pcVar31 == ' ');
                    for (lVar35 = 0;
                        (bVar3 = pcVar19[lVar35], bVar3 != 0x2c && (bVar3 & 0xdf) != 0 &&
                        (lVar35 != 7)); lVar35 = lVar35 + 1) {
                      *(byte *)((long)&uStack_178 + lVar35) = bVar3;
                    }
                    *(undefined1 *)((long)&uStack_178 + (long)(int)lVar35) = 0;
                  }
                  uVar11 = arm64_cond_suffix_to_cmp(&uStack_178,&uStack_288);
                  iVar8 = (int)plStack_298[2];
                  *(int *)(plStack_298 + 2) = iVar8 + 1;
                  puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
                  if (puVar20 == (undefined4 *)0x0) goto LAB_001529c4;
                  *puVar20 = uVar11;
                  puVar20[2] = iVar8;
                  puVar20[3] = 6;
                  *(undefined8 *)(puVar20 + 4) = 0;
                  if ((int)uStack_288 == 0) {
                    uVar27 = uStack_2e0;
                    uVar34 = 0;
                    uVar25 = uVar43;
                    uVar39 = uVar44;
                  }
                  else {
                    uVar27 = 0;
                    uVar34 = uStack_2e0;
                    uVar25 = uVar44;
                    uVar39 = uVar43;
                  }
                  *(undefined8 *)(puVar20 + 0xc) = uVar27;
                  *(undefined8 *)(puVar20 + 6) = uVar39;
                  *(undefined8 *)(puVar20 + 8) = uVar34;
                  *(undefined8 *)(puVar20 + 10) = uVar25;
                  puVar20[0x12] = 2;
                  *(undefined8 *)(puVar20 + 0x1c) = uVar13;
                  if (iVar8 == -1) goto LAB_00154b24;
                }
                puVar17[6] = iVar8;
                puVar17[7] = 6;
                *(undefined8 *)(puVar17 + 8) = 0;
                if (uStack_2ac < 0x20) {
                  uVar18 = -(ulong)(uStack_2ac >> 0x1f) & 0xfffffffc00000000 |
                           (ulong)uStack_2ac << 2;
                  iVar8 = *(int *)((long)&uStack_1f8 + uVar18);
                  if (iVar8 == -1) goto LAB_00154138;
                  uVar11 = *(undefined4 *)((long)&uStack_280 + uVar18);
                }
                else {
LAB_00154138:
                  iVar8 = (int)plStack_298[2];
                  *(int *)(plStack_298 + 2) = iVar8 + 1;
                  uVar11 = uStack_2a0;
                }
                puVar17[10] = iVar8;
                puVar17[0xb] = uVar11;
                *(undefined8 *)(puVar17 + 0xc) = 0;
                uStack_178 = 0;
                uStack_170 = 0;
                pcVar19 = strchr(acStack_168 + 0x40,0x2c);
                if (pcVar19 != (char *)0x0) {
                  do {
                    pcVar31 = pcVar19 + 1;
                    pcVar19 = pcVar19 + 1;
                  } while (*pcVar31 == ' ');
                  for (lVar35 = 0;
                      (bVar3 = pcVar19[lVar35], bVar3 != 0x2c && (bVar3 & 0xdf) != 0 &&
                      (lVar35 != 0xf)); lVar35 = lVar35 + 1) {
                    *(byte *)((long)&uStack_178 + lVar35) = bVar3;
                  }
                  *(undefined1 *)((long)&uStack_178 + (long)(int)lVar35) = 0;
                }
                uStack_290 = 0xfffffffe;
                uStack_288._0_4_ = 4;
                if ((((char)uStack_178 == '\0') ||
                    (iVar8 = arm64_reg_lookup(&uStack_178,&uStack_290,&uStack_288), iVar8 == 0)) ||
                   (0x1f < uStack_290)) {
LAB_00154058:
                  iVar8 = (int)plStack_298[2];
                  *(int *)(plStack_298 + 2) = iVar8 + 1;
                  uVar11 = uStack_2a4;
                }
                else {
                  uVar18 = -(ulong)(uStack_290 >> 0x1f) & 0xfffffffc00000000 |
                           (ulong)uStack_290 << 2;
                  iVar8 = *(int *)((long)&uStack_1f8 + uVar18);
                  if (iVar8 == -1) goto LAB_00154058;
                  uVar11 = *(undefined4 *)((long)&uStack_280 + uVar18);
                }
                uVar38 = -(ulong)(uVar22 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                puVar17[0xe] = iVar8;
                puVar17[0xf] = uVar11;
                *(int *)((long)&uStack_1f8 + uVar38) = iVar10;
                *(undefined4 *)((long)&uStack_280 + uVar38) = uStack_2a4;
                puVar17[2] = iVar10;
                puVar17[3] = uStack_2a4;
                *(undefined8 *)(puVar17 + 4) = 0;
                *(undefined8 *)(puVar17 + 0x10) = 0;
                puVar17[0x12] = 3;
                *(undefined8 *)(puVar17 + 0x1c) = uVar13;
                goto LAB_00152170;
              }
              uStack_310._0_4_ = 0xc;
            }
            if (uStack_2b0 < 0x20) {
              uVar18 = -(ulong)(uStack_2b0 >> 0x1f) & 0xfffffffc00000000 | (ulong)uStack_2b0 << 2;
              iVar8 = *(int *)((long)&uStack_1f8 + uVar18);
              if (iVar8 == -1) goto LAB_00153ec4;
              uVar11 = *(undefined4 *)((long)&uStack_280 + uVar18);
            }
            else {
LAB_00153ec4:
              uVar11 = 4;
              iVar8 = (int)plStack_298[2];
              *(int *)(plStack_298 + 2) = iVar8 + 1;
            }
            if (bVar4) {
              if (-1 < (long)uVar38) goto LAB_00153d9c;
              uVar38 = 0;
            }
            else {
              uVar38 = 0;
LAB_00153d9c:
              if (0x3f < (long)uVar38) {
                uVar38 = 0x3f;
              }
            }
            auVar45 = arm_emit_const(puVar1,plStack_298,1L << (uVar38 & 0x3f),uVar13);
            if (auVar45._0_4_ == -1) goto LAB_001529c4;
            iVar41 = (int)plStack_298[2];
            *(int *)(plStack_298 + 2) = iVar41 + 1;
            puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
            if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
            *puVar17 = 6;
            puVar17[2] = iVar41;
            puVar17[3] = uVar11;
            *(undefined8 *)(puVar17 + 4) = 0;
            puVar17[6] = iVar8;
            puVar17[7] = uVar11;
            *(undefined8 *)(puVar17 + 8) = 0;
            *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
            puVar17[0x12] = 2;
            *(undefined8 *)(puVar17 + 0x1c) = uVar13;
            auVar45 = arm_emit_const(puVar1,plStack_298,0);
            if (auVar45._0_4_ == -1) goto LAB_001529c4;
            iVar8 = (int)plStack_298[2];
            *(int *)(plStack_298 + 2) = iVar8 + 1;
            puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
            if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
            puVar17[6] = iVar41;
            puVar17[7] = uVar11;
            puVar17[2] = iVar8;
            puVar17[3] = 6;
            *puVar17 = (undefined4)uStack_310;
            *(undefined8 *)(puVar17 + 4) = 0;
            *(undefined8 *)(puVar17 + 8) = 0;
            *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
            puVar17[0x12] = 2;
            *(undefined8 *)(puVar17 + 0x1c) = uVar13;
            puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
            if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
            *puVar17 = 0x17;
            puVar17[6] = iVar8;
            puVar17[7] = 6;
            *(undefined8 *)(puVar17 + 8) = 0;
            *(undefined8 *)(puVar17 + 2) = 0xffffffff;
            puVar17[0x12] = 1;
            *(undefined8 *)(puVar17 + 0x1c) = uVar13;
            goto LAB_00152170;
          }
          uVar11 = 0xc;
        }
        if (uStack_2b0 < 0x20) {
          uVar38 = -(ulong)(uStack_2b0 >> 0x1f) & 0xfffffffc00000000 | (ulong)uStack_2b0 << 2;
          iVar8 = *(int *)((long)&uStack_1f8 + uVar38);
          if (iVar8 == -1) goto LAB_00153d18;
          uVar42 = *(undefined4 *)((long)&uStack_280 + uVar38);
        }
        else {
LAB_00153d18:
          uVar42 = 4;
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 1;
        }
        auVar45 = arm_emit_const(puVar1,plStack_298,0,uVar13);
        if (auVar45._0_4_ == -1) goto LAB_001529c4;
        iVar41 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar41 + 1;
        puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
        if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
        puVar17[6] = iVar8;
        puVar17[7] = uVar42;
        *puVar17 = uVar11;
        puVar17[2] = iVar41;
        puVar17[3] = 6;
        *(undefined8 *)(puVar17 + 4) = 0;
        *(undefined8 *)(puVar17 + 8) = 0;
        *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
        puVar17[0x12] = 2;
        *(undefined8 *)(puVar17 + 0x1c) = uVar13;
        puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
        if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
        *puVar17 = 0x17;
        puVar17[6] = iVar41;
        puVar17[7] = 6;
        *(undefined8 *)(puVar17 + 8) = 0;
        *(undefined8 *)(puVar17 + 2) = 0xffffffff;
        puVar17[0x12] = 1;
        *(undefined8 *)(puVar17 + 0x1c) = uVar13;
        goto LAB_00152170;
      }
      if (uStack_2b0 < 0x20) {
        iVar8 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2b0 * 4);
        uVar11 = uStack_2a4;
        if (iVar8 == -1) {
          iVar8 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar8 + 1;
        }
      }
      else {
        iVar8 = (int)plStack_298[2];
        *(int *)(plStack_298 + 2) = iVar8 + 1;
        uVar11 = 4;
      }
      if (uStack_2ac < 0x20) {
        iVar41 = *(int *)((long)&uStack_1f8 + (long)(int)uStack_2ac * 4);
        if (iVar41 == -1) {
          iVar41 = (int)plStack_298[2];
          *(int *)(plStack_298 + 2) = iVar41 + 1;
        }
        uStack_2e0 = 0;
        uVar42 = uStack_2a0;
      }
      else if (bVar4) {
        auVar45 = arm_emit_const(puVar1,plStack_298,uVar38,uVar13);
        uStack_2e0 = auVar45._8_8_;
        iVar41 = auVar45._0_4_;
        uVar42 = auVar45._4_4_;
        if (iVar41 == -1) goto LAB_001529c4;
      }
      else {
        iVar41 = (int)plStack_298[2];
        uVar42 = 4;
        uStack_2e0 = 0;
        *(int *)(plStack_298 + 2) = iVar41 + 1;
      }
      iStack_2d4 = (int)plStack_298[2];
      *(int *)(plStack_298 + 2) = iStack_2d4 + 1;
      puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
      if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
      puVar17[2] = iStack_2d4;
      puVar17[3] = 6;
      puVar17[0x12] = 2;
      *puVar17 = 0xb;
      *(undefined8 *)(puVar17 + 4) = 0;
      puVar17[6] = iVar8;
      puVar17[7] = uVar11;
      *(undefined8 *)(puVar17 + 8) = 0;
      puVar17[10] = iVar41;
      puVar17[0xb] = uVar42;
      *(undefined8 *)(puVar17 + 0xc) = uStack_2e0;
      *(undefined8 *)(puVar17 + 0x1c) = uVar13;
    }
  }
  uVar44 = CONCAT44(uVar11,iVar8);
  uVar43 = CONCAT44(uVar42,iVar41);
LAB_00152190:
  lVar32 = lVar32 + 1;
  if (*(uint *)(lVar29 + 0x18) <= (uint)lVar32) goto LAB_001521a0;
  goto LAB_00151ea8;
  while( true ) {
    pcVar30 = pcVar31 + -1;
    *pcVar31 = '\0';
    pcVar31 = pcVar30;
    cVar7 = acStack_168[0x40];
    if (pcVar30 == pcVar15) break;
LAB_0015260c:
    cVar7 = acStack_168[0x40];
    if (*pcVar31 != ' ') break;
  }
LAB_0015261c:
  pcVar31 = pcVar15;
  if (cVar7 == ' ') {
    do {
      pcVar31 = pcVar31 + 1;
    } while (*pcVar31 == ' ');
    if (pcVar31 != pcVar15) {
      sVar23 = strlen(pcVar31);
      __memmove_chk(pcVar15,pcVar31,sVar23 + 1,0x40);
    }
  }
LAB_00152658:
  cVar7 = acStack_e9[1];
  if (acStack_e9[1] == '\0') {
LAB_0015283c:
    uStack_2b0 = 0xfffffffe;
    uStack_2ac = 0xfffffffe;
    uStack_2a8 = 0xfffffffe;
    uStack_2a4 = 4;
    uStack_2a0 = 4;
    uStack_29c = 4;
    iVar10 = arm64_reg_lookup(acStack_168,&uStack_2b0,&uStack_2a4);
    if (iVar10 == 0) goto LAB_0015270c;
LAB_00152868:
    iVar10 = arm64_reg_lookup(pcVar15,&uStack_2ac,&uStack_2a0);
  }
  else {
    sVar23 = strlen(__s);
    pcVar31 = __s + (sVar23 - 1);
    if (__s < __s + (sVar23 - 1)) {
      do {
        cVar7 = acStack_e9[1];
        if (*pcVar31 != ' ') break;
        pcVar30 = pcVar31 + -1;
        *pcVar31 = '\0';
        pcVar31 = pcVar30;
        cVar7 = acStack_e9[1];
      } while (pcVar30 != __s);
    }
    pcVar31 = __s;
    if (cVar7 != ' ') goto LAB_0015283c;
    do {
      pcVar31 = pcVar31 + 1;
    } while (*pcVar31 == ' ');
    if (pcVar31 == __s) goto LAB_0015283c;
    sVar23 = strlen(pcVar31);
    __memmove_chk(__s,pcVar31,sVar23 + 1,0x40);
    uStack_2b0 = 0xfffffffe;
    uStack_2ac = 0xfffffffe;
    uStack_2a8 = 0xfffffffe;
    uStack_2a4 = 4;
    uStack_2a0 = 4;
    uStack_29c = 4;
    iVar10 = arm64_reg_lookup(acStack_168,&uStack_2b0,&uStack_2a4);
    if (iVar10 != 0) goto LAB_00152868;
LAB_0015270c:
    uStack_2b0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar15,&uStack_2ac,&uStack_2a0);
  }
  if (iVar10 == 0) {
    iVar10 = 3;
LAB_00152880:
    pcVar31 = acStack_168 + 0x40;
    cVar7 = acStack_168[0x40];
    while (cVar7 == ' ') {
      pcVar31 = pcVar31 + 1;
      cVar7 = *pcVar31;
    }
    if (cVar7 == '#') {
      pcVar30 = pcVar31 + 1;
      pcVar31 = pcVar31 + 1;
      cVar7 = *pcVar30;
      while (cVar7 == ' ') {
        pcVar31 = pcVar31 + 1;
        cVar7 = *pcVar31;
      }
    }
    iVar9 = __isoc99_sscanf(pcVar31,"0x%lx",&uStack_290);
    if (iVar9 == 1) {
      uVar38 = CONCAT44(uStack_28c,uStack_290);
      bVar4 = true;
    }
    else {
      iVar9 = __isoc99_sscanf(pcVar31,&DAT_001fa008,&uStack_288);
      if (iVar9 == 1) {
        uVar38 = CONCAT44(uStack_288._4_4_,(int)uStack_288);
        bVar4 = true;
      }
      else {
        uVar38 = 0;
        bVar4 = false;
      }
    }
    if (iVar10 == 3) {
      iVar10 = arm64_reg_lookup(acStack_e9 + 1,&uStack_2a8,&uStack_29c);
      if (iVar10 == 0) goto LAB_00152910;
LAB_00152748:
      iVar10 = 3;
      bVar5 = false;
      uStack_310 = 0;
    }
    else {
      iVar10 = 2;
      bVar5 = false;
      uStack_310 = 0;
    }
  }
  else {
    uVar38 = 0;
    iVar10 = arm64_reg_lookup(__s,&uStack_2a8,&uStack_29c);
    bVar4 = false;
    if (iVar10 != 0) goto LAB_00152748;
LAB_00152910:
    bVar5 = false;
    pcVar31 = acStack_e9 + 1;
    cVar7 = acStack_e9[1];
    while (cVar7 == ' ') {
      pcVar31 = pcVar31 + 1;
      cVar7 = *pcVar31;
    }
    if (cVar7 == '#') {
      pcVar30 = pcVar31 + 1;
      pcVar31 = pcVar31 + 1;
      cVar7 = *pcVar30;
      while (cVar7 == ' ') {
        pcVar31 = pcVar31 + 1;
        cVar7 = *pcVar31;
      }
    }
    iVar10 = __isoc99_sscanf(pcVar31,"0x%lx",&uStack_290);
    if (iVar10 == 1) {
      uStack_310 = CONCAT44(uStack_28c,uStack_290);
      iVar10 = 3;
      bVar5 = true;
    }
    else {
      iVar10 = __isoc99_sscanf(pcVar31,&DAT_001fa008,&uStack_288);
      uStack_310 = 0;
      if (iVar10 == 1) {
        uStack_310 = CONCAT44(uStack_288._4_4_,(int)uStack_288);
        iVar10 = 3;
        bVar5 = true;
      }
      else {
        iVar10 = 3;
      }
    }
  }
  goto LAB_00152754;
LAB_00153b74:
  if (((uVar28 == 0x1f) && (lVar35 = CONCAT44(uStack_288._4_4_,(int)uStack_288), lVar35 != 0)) &&
     (pcVar19 = strchr(acStack_e9 + 1,0x21), pcVar19 != (char *)0x0)) {
    auVar45 = arm_emit_const(puVar1,plStack_298,lVar35,uVar13);
    iVar8 = (int)plStack_298[2];
    *(int *)(plStack_298 + 2) = iVar8 + 1;
    puVar17 = (undefined4 *)arm_irblock_alloc_instr(puVar1);
    if (puVar17 == (undefined4 *)0x0) goto LAB_001529c4;
    uVar11 = uStack_180._4_4_;
    uStack_180 = CONCAT44(iVar8,(undefined4)uStack_180);
    *puVar17 = 2;
    puVar17[2] = iVar8;
    puVar17[3] = 5;
    *(undefined8 *)(puVar17 + 4) = 0;
    puVar17[6] = uVar11;
    puVar17[7] = 5;
    *(undefined8 *)(puVar17 + 8) = 0;
    *(undefined1 (*) [16])(puVar17 + 10) = auVar45;
    puVar17[0x12] = 2;
    *(undefined8 *)(puVar17 + 0x1c) = uVar13;
  }
  goto LAB_00152170;
LAB_001529c4:
  ir_func_destroy(&plStack_298);
  goto LAB_001529ec;
}

