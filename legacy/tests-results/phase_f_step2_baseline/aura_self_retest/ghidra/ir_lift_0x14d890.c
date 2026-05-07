
long * ir_lift(long *param_1,undefined8 param_2,char *param_3,long param_4)

{
  long lVar1;
  undefined8 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  long *plVar6;
  bool bVar7;
  ulong uVar8;
  undefined8 uVar9;
  char cVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  long *plVar16;
  void *pvVar17;
  undefined8 uVar18;
  char *pcVar19;
  int *piVar20;
  char *pcVar21;
  undefined4 *puVar22;
  ulonglong uVar23;
  undefined4 *puVar24;
  size_t sVar25;
  int *piVar26;
  int *extraout_x1;
  char *pcVar27;
  undefined4 uVar28;
  uint uVar29;
  long lVar30;
  long lVar31;
  char cVar32;
  uint uVar33;
  undefined4 uVar34;
  ulong uVar35;
  char *pcVar36;
  int iVar37;
  uint uVar38;
  long lVar39;
  ulong uVar40;
  long lVar41;
  undefined8 uVar42;
  undefined8 *puVar43;
  undefined **ppuVar44;
  undefined **ppuVar45;
  undefined4 uVar46;
  undefined4 uVar47;
  ulong uVar48;
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  ulong local_3f8;
  undefined8 local_3d8;
  int local_3d0;
  int local_3cc;
  uint local_394;
  uint local_390;
  uint local_38c;
  uint local_388;
  uint local_384;
  uint local_380;
  uint local_37c;
  long *local_378;
  uint local_370;
  undefined4 uStack_36c;
  int local_368;
  undefined4 uStack_364;
  undefined8 local_360;
  undefined8 uStack_358;
  undefined8 uStack_350;
  undefined8 uStack_348;
  undefined8 local_340;
  undefined8 uStack_338;
  undefined8 uStack_330;
  undefined8 uStack_328;
  undefined8 local_320;
  undefined8 uStack_318;
  undefined8 local_310;
  undefined8 uStack_308;
  undefined8 local_300;
  undefined8 uStack_2f8;
  undefined8 uStack_2f0;
  undefined8 uStack_2e8;
  undefined8 local_2e0;
  undefined8 uStack_2d8;
  undefined8 local_2d0;
  undefined8 uStack_2c8;
  undefined8 local_2c0;
  undefined8 uStack_2b8;
  undefined8 uStack_2b0;
  undefined8 uStack_2a8;
  undefined8 local_2a0;
  undefined8 uStack_298;
  undefined8 uStack_290;
  undefined8 uStack_288;
  undefined8 local_280;
  undefined8 uStack_278;
  undefined8 uStack_270;
  undefined8 uStack_268;
  undefined8 local_260;
  undefined8 uStack_258;
  undefined8 uStack_250;
  undefined8 uStack_248;
  undefined8 local_240;
  undefined8 uStack_238;
  undefined8 uStack_230;
  undefined8 uStack_228;
  undefined8 local_220;
  undefined8 uStack_218;
  undefined8 uStack_210;
  undefined8 uStack_208;
  undefined8 local_200;
  undefined8 uStack_1f8;
  undefined8 uStack_1f0;
  undefined8 uStack_1e8;
  undefined8 local_1d8 [15];
  char cStack_160;
  char cStack_15f;
  char cStack_15e;
  char cStack_15d;
  char cStack_15c;
  char cStack_15b;
  char cStack_15a;
  char acStack_159 [129];
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  long local_98;
  
  local_98 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) &&
     (plVar16 = calloc(1,0xa0), local_378 = plVar16, plVar16 != (long *)0x0)) {
    *(undefined4 *)(plVar16 + 2) = 0;
    plVar16[3] = param_4;
    if ((param_3 == (char *)0x0) || (*param_3 == '\0')) {
      __snprintf_chk(plVar16 + 4,0x80,2,0x80,"sub_%lx",param_4);
    }
    else {
      snprintf((char *)(plVar16 + 4),0x80,"%s",param_3);
    }
    uVar9 = DAT_0020a3e8;
    uVar8 = DAT_0020a3e0;
    lVar39 = 0;
    if ((int)param_1[1] != 0) {
      do {
        uVar33 = *(uint *)(plVar16 + 1);
        uVar29 = *(uint *)((long)plVar16 + 0xc);
        pvVar17 = (void *)*plVar16;
        lVar1 = *param_1 + lVar39 * 0x20;
        if (uVar29 <= uVar33) {
          if (uVar29 == 0) {
            sVar25 = 0x240;
            uVar29 = 8;
          }
          else {
            uVar29 = uVar29 << 1;
            sVar25 = (ulong)uVar29 * 0x48;
          }
          pvVar17 = realloc(pvVar17,sVar25);
          if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
          uVar33 = *(uint *)(plVar16 + 1);
          *plVar16 = (long)pvVar17;
          *(uint *)((long)plVar16 + 0xc) = uVar29;
        }
        puVar2 = (undefined8 *)((long)pvVar17 + (ulong)uVar33 * 0x48);
        uStack_358 = 0xffffffffffffffff;
        local_360 = 0xffffffffffffffff;
        uStack_348 = 0xffffffffffffffff;
        uStack_350 = 0xffffffffffffffff;
        puVar2[8] = 0;
        puVar2[1] = 0;
        *puVar2 = 0;
        puVar2[3] = 0;
        puVar2[2] = 0;
        puVar2[5] = 0;
        puVar2[4] = 0;
        puVar2[7] = 0;
        puVar2[6] = 0;
        iVar11 = (int)plVar16[1];
        uStack_318 = 0xffffffffffffffff;
        local_320 = 0xffffffffffffffff;
        uStack_308 = 0xffffffffffffffff;
        local_310 = 0xffffffffffffffff;
        *(int *)(plVar16 + 1) = iVar11 + 1;
        *(int *)((long)pvVar17 + (ulong)uVar33 * 0x48) = iVar11;
        *(int *)((long)puVar2 + 0x34) = iVar11;
        uStack_2f8 = 0xffffffffffffffff;
        local_300 = 0xffffffffffffffff;
        uStack_2e8 = 0xffffffffffffffff;
        uStack_2f0 = 0xffffffffffffffff;
        uStack_2d8 = 0x400000004;
        local_2e0 = 0x400000004;
        uStack_2c8 = 0x400000004;
        local_2d0 = 0x400000004;
        uStack_2b8 = 0x400000004;
        local_2c0 = 0x400000004;
        uStack_2a8 = 0x400000004;
        uStack_2b0 = 0x400000004;
        uStack_298 = 0xffffffffffffffff;
        local_2a0 = 0xffffffffffffffff;
        uStack_288 = 0xffffffffffffffff;
        uStack_290 = 0xffffffffffffffff;
        uStack_278 = 0xffffffffffffffff;
        local_280 = 0xffffffffffffffff;
        uStack_268 = 0xffffffffffffffff;
        uStack_270 = 0xffffffffffffffff;
        uStack_258 = 0x800000008;
        local_260 = 0x800000008;
        uStack_248 = 0x800000008;
        uStack_250 = 0x800000008;
        uStack_238 = 0x800000008;
        local_240 = 0x800000008;
        uStack_228 = 0x800000008;
        uStack_230 = 0x800000008;
        uStack_218 = 0xffffffffffffffff;
        local_220 = 0xffffffffffffffff;
        uStack_208 = 0xffffffffffffffff;
        uStack_210 = 0xffffffffffffffff;
        uStack_1f8 = 0xffffffffffffffff;
        local_200 = 0xffffffffffffffff;
        uStack_1e8 = 0xffffffffffffffff;
        uStack_1f0 = 0xffffffffffffffff;
        local_1d8[1] = 0xffffffffffffffff;
        local_1d8[0] = 0xffffffffffffffff;
        local_1d8[3] = 0xffffffffffffffff;
        local_1d8[2] = 0xffffffffffffffff;
        local_1d8[5] = 0xffffffffffffffff;
        local_1d8[4] = 0xffffffffffffffff;
        local_1d8[7] = 0xffffffffffffffff;
        local_1d8[6] = 0xffffffffffffffff;
        local_1d8[9] = 0xffffffffffffffff;
        local_1d8[8] = 0xffffffffffffffff;
        local_1d8[0xb] = 0xffffffffffffffff;
        local_1d8[10] = 0xffffffffffffffff;
        local_1d8[0xd] = 0xffffffffffffffff;
        local_1d8[0xc] = 0xffffffffffffffff;
        cStack_160 = -1;
        cStack_15f = -1;
        cStack_15e = -1;
        cStack_15d = -1;
        cStack_15c = -1;
        cStack_15b = -1;
        cStack_15a = -1;
        acStack_159[0] = -1;
        local_1d8[0xe] = 0xffffffffffffffff;
        uStack_338 = 0xffffffffffffffff;
        local_340 = 0xffffffffffffffff;
        uStack_328 = 0xffffffffffffffff;
        uStack_330 = 0xffffffffffffffff;
        if (*(int *)(lVar1 + 0x18) != 0) {
          lVar30 = 0;
          auVar50._8_8_ = 0;
          auVar50._0_8_ = uVar8;
          local_3d0 = -1;
          local_3cc = -1;
          uVar48 = uVar8;
LAB_0014da60:
          local_3d8 = auVar50._8_8_;
          lVar31 = *(long *)(lVar1 + 0x10) + lVar30 * 0xe0;
          pcVar36 = (char *)(lVar31 + 0x20);
          uVar18 = *(undefined8 *)(*(long *)(lVar1 + 0x10) + lVar30 * 0xe0);
          cVar10 = *(char *)(lVar31 + 0x60);
          acStack_159[1] = '\0';
          acStack_159[0x41] = '\0';
          if (cVar10 == '\0') {
            iVar11 = strcmp(pcVar36,"mov");
            if (iVar11 == 0) {
              uVar47 = 4;
              pcVar36 = acStack_159 + 1;
              iVar11 = -1;
              local_3f8 = 0;
              bVar7 = false;
LAB_0014dd60:
              pcVar27 = strstr(pcVar36,"ptr");
              if ((pcVar27 == (char *)0x0) &&
                 (pcVar36 = strchr(pcVar36,0x5b), pcVar36 == (char *)0x0)) goto LAB_0014dc04;
              goto LAB_0014dd74;
            }
            uVar47 = 4;
            uVar35 = 0xffffffff;
            uVar40 = 0xffffffff;
            bVar7 = false;
            local_3f8 = 0;
            iVar11 = 0;
            uVar46 = 4;
LAB_0014dac4:
            iVar12 = strcmp(pcVar36,"movzx");
            uVar33 = (uint)uVar35;
            plVar6 = local_378;
            if ((((iVar12 == 0) ||
                 (iVar12 = strcmp(pcVar36,"movsx"), plVar6 = local_378, iVar12 == 0)) ||
                (iVar12 = strcmp(pcVar36,"movsxd"), plVar6 = local_378, iVar12 == 0)) ||
               (iVar12 = strcmp(pcVar36,"lea"), plVar6 = local_378, iVar12 == 0))
            goto joined_r0x0014e0a8;
            iVar12 = strcmp(pcVar36,"add");
            plVar6 = local_378;
            uVar29 = (uint)uVar40;
            uVar34 = uVar46;
            if (iVar12 == 0) {
              if (-1 < (int)uVar33) {
                lVar31 = (long)(int)uVar33;
                iVar11 = *(int *)((long)&local_320 + lVar31 * 4);
                if (iVar11 == -1) {
                  iVar11 = (int)local_378[2];
                  *(int *)(local_378 + 2) = iVar11 + 1;
                }
                else {
                  uVar34 = *(undefined4 *)((long)&local_2e0 + lVar31 * 4);
                }
                if ((int)uVar29 < 0) {
                  if (bVar7) {
                    auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                    uVar42 = auVar49._8_8_;
                    iVar12 = auVar49._0_4_;
                    uVar47 = auVar49._4_4_;
                    if (iVar12 == -1) goto LAB_0014e4e8;
                    iVar13 = (int)plVar6[2];
                  }
                  else {
                    iVar12 = (int)local_378[2];
                    uVar47 = 4;
                    uVar42 = 0;
                    iVar13 = iVar12 + 1;
                  }
                }
                else {
                  iVar12 = (int)local_378[2];
                  iVar15 = *(int *)((long)&local_320 + (long)(int)uVar29 * 4);
                  if (iVar15 == -1) {
                    uVar42 = 0;
                    iVar13 = iVar12 + 1;
                  }
                  else {
                    uVar42 = 0;
                    uVar47 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar29 * 4);
                    iVar13 = iVar12;
                    iVar12 = iVar15;
                  }
                }
                uVar33 = *(uint *)(puVar2 + 2);
                uVar29 = *(uint *)((long)puVar2 + 0x14);
                *(int *)(plVar6 + 2) = iVar13 + 1;
                pvVar17 = (void *)puVar2[1];
                if (uVar29 <= uVar33) {
                  if (uVar29 == 0) {
                    sVar25 = 0x880;
                    uVar29 = 0x10;
                  }
                  else {
                    uVar29 = uVar29 << 1;
                    sVar25 = (ulong)uVar29 * 0x88;
                  }
                  pvVar17 = realloc(pvVar17,sVar25);
                  if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                  puVar2[1] = pvVar17;
                  uVar33 = *(uint *)(puVar2 + 2);
                  *(uint *)((long)puVar2 + 0x14) = uVar29;
                }
                *(int *)((long)&local_320 + lVar31 * 4) = iVar13;
                *(uint *)(puVar2 + 2) = uVar33 + 1;
                puVar43 = (undefined8 *)((long)pvVar17 + (ulong)uVar33 * 0x88);
                *(undefined4 *)((long)&local_2e0 + lVar31 * 4) = uVar46;
                puVar43[1] = 0;
                *puVar43 = 0;
                puVar43[3] = 0;
                puVar43[2] = 0;
                puVar43[5] = 0;
                puVar43[4] = 0;
                puVar43[7] = 0;
                puVar43[6] = 0;
                puVar43[9] = 0;
                puVar43[8] = 0;
                puVar43[0xb] = 0;
                puVar43[10] = 0;
                puVar43[0xd] = 0;
                puVar43[0xc] = 0;
                puVar43[0xf] = 0;
                puVar43[0xe] = 0;
                puVar43[0x10] = 0;
                *(undefined4 *)((long)pvVar17 + (ulong)uVar33 * 0x88) = 2;
LAB_0014e408:
                *(int *)(puVar43 + 3) = iVar11;
                *(undefined4 *)((long)puVar43 + 0x1c) = uVar34;
                *(int *)(puVar43 + 1) = iVar13;
                *(undefined4 *)((long)puVar43 + 0xc) = uVar46;
                *(int *)(puVar43 + 5) = iVar12;
                *(undefined4 *)((long)puVar43 + 0x2c) = uVar47;
                puVar43[6] = uVar42;
                *(undefined4 *)(puVar43 + 9) = 2;
                puVar43[0xe] = uVar18;
              }
            }
            else {
              iVar12 = strcmp(pcVar36,"sub");
              plVar6 = local_378;
              if (iVar12 == 0) {
                if (-1 < (int)uVar33) {
                  lVar31 = (long)(int)uVar33;
                  iVar11 = *(int *)((long)&local_320 + lVar31 * 4);
                  if (iVar11 == -1) {
                    iVar11 = (int)local_378[2];
                    *(int *)(local_378 + 2) = iVar11 + 1;
                  }
                  else {
                    uVar34 = *(undefined4 *)((long)&local_2e0 + lVar31 * 4);
                  }
                  if ((int)uVar29 < 0) {
                    if (bVar7) {
                      auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                      uVar42 = auVar49._8_8_;
                      iVar12 = auVar49._0_4_;
                      uVar47 = auVar49._4_4_;
                      if (iVar12 == -1) goto LAB_0014e4e8;
                      iVar13 = (int)plVar6[2];
                    }
                    else {
                      iVar12 = (int)local_378[2];
                      uVar47 = 4;
                      uVar42 = 0;
                      iVar13 = iVar12 + 1;
                    }
                  }
                  else {
                    iVar12 = (int)local_378[2];
                    iVar15 = *(int *)((long)&local_320 + (long)(int)uVar29 * 4);
                    if (iVar15 == -1) {
                      uVar42 = 0;
                      iVar13 = iVar12 + 1;
                    }
                    else {
                      uVar42 = 0;
                      uVar47 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar29 * 4);
                      iVar13 = iVar12;
                      iVar12 = iVar15;
                    }
                  }
                  uVar29 = *(uint *)(puVar2 + 2);
                  uVar38 = *(uint *)((long)puVar2 + 0x14);
                  *(int *)(plVar6 + 2) = iVar13 + 1;
                  pvVar17 = (void *)puVar2[1];
                  if (uVar38 <= uVar29) {
                    if (uVar38 == 0) {
                      sVar25 = 0x880;
                      uVar38 = 0x10;
                    }
                    else {
                      uVar38 = uVar38 << 1;
                      sVar25 = (ulong)uVar38 * 0x88;
                    }
                    pvVar17 = realloc(pvVar17,sVar25);
                    if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                    puVar2[1] = pvVar17;
                    uVar29 = *(uint *)(puVar2 + 2);
                    *(uint *)((long)puVar2 + 0x14) = uVar38;
                  }
                  uVar28 = 3;
                  *(int *)((long)&local_320 + lVar31 * 4) = iVar13;
                  lVar31 = (ulong)uVar29 * 0x88;
                  *(uint *)(puVar2 + 2) = uVar29 + 1;
LAB_0014e710:
                  puVar43 = (undefined8 *)((long)pvVar17 + lVar31);
                  *(undefined4 *)((long)&local_2e0 + (long)(int)uVar33 * 4) = uVar46;
                  puVar43[0x10] = 0;
                  puVar43[1] = 0;
                  *puVar43 = 0;
                  puVar43[3] = 0;
                  puVar43[2] = 0;
                  puVar43[5] = 0;
                  puVar43[4] = 0;
                  puVar43[7] = 0;
                  puVar43[6] = 0;
                  puVar43[9] = 0;
                  puVar43[8] = 0;
                  puVar43[0xb] = 0;
                  puVar43[10] = 0;
                  puVar43[0xd] = 0;
                  puVar43[0xc] = 0;
                  puVar43[0xf] = 0;
                  puVar43[0xe] = 0;
                  *(undefined4 *)((long)pvVar17 + lVar31) = uVar28;
                  goto LAB_0014e408;
                }
              }
              else {
                iVar12 = strcmp(pcVar36,"imul");
                if ((iVar12 == 0) || (iVar12 = strcmp(pcVar36,"mul"), iVar12 == 0)) {
                  plVar6 = local_378;
                  if (-1 < (int)uVar33) {
                    lVar31 = (long)(int)uVar33;
                    iVar11 = *(int *)((long)&local_320 + lVar31 * 4);
                    if (iVar11 == -1) {
                      iVar11 = (int)local_378[2];
                      *(int *)(local_378 + 2) = iVar11 + 1;
                    }
                    else {
                      uVar34 = *(undefined4 *)((long)&local_2e0 + lVar31 * 4);
                    }
                    if ((int)uVar29 < 0) {
                      if (bVar7) {
                        auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                        uVar42 = auVar49._8_8_;
                        iVar12 = auVar49._0_4_;
                        uVar47 = auVar49._4_4_;
                        if (iVar12 == -1) goto LAB_0014e4e8;
                        iVar13 = (int)plVar6[2];
                      }
                      else {
                        iVar12 = (int)local_378[2];
                        uVar47 = 4;
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                      }
                    }
                    else {
                      iVar12 = (int)local_378[2];
                      iVar15 = *(int *)((long)&local_320 + (long)(int)uVar29 * 4);
                      if (iVar15 == -1) {
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                      }
                      else {
                        uVar42 = 0;
                        uVar47 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar29 * 4);
                        iVar13 = iVar12;
                        iVar12 = iVar15;
                      }
                    }
                    uVar29 = *(uint *)(puVar2 + 2);
                    uVar38 = *(uint *)((long)puVar2 + 0x14);
                    *(int *)(plVar6 + 2) = iVar13 + 1;
                    pvVar17 = (void *)puVar2[1];
                    if (uVar38 <= uVar29) {
                      if (uVar38 == 0) {
                        sVar25 = 0x880;
                        uVar38 = 0x10;
                      }
                      else {
                        uVar38 = uVar38 << 1;
                        sVar25 = (ulong)uVar38 * 0x88;
                      }
                      pvVar17 = realloc(pvVar17,sVar25);
                      if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                      puVar2[1] = pvVar17;
                      uVar29 = *(uint *)(puVar2 + 2);
                      *(uint *)((long)puVar2 + 0x14) = uVar38;
                    }
                    uVar28 = 4;
                    *(int *)((long)&local_320 + lVar31 * 4) = iVar13;
                    lVar31 = (ulong)uVar29 * 0x88;
                    *(uint *)(puVar2 + 2) = uVar29 + 1;
                    goto LAB_0014e710;
                  }
                }
                else {
                  iVar12 = strcmp(pcVar36,"and");
                  plVar6 = local_378;
                  if (iVar12 == 0) {
                    if (-1 < (int)uVar33) {
                      lVar31 = (long)(int)uVar33;
                      iVar11 = *(int *)((long)&local_320 + lVar31 * 4);
                      if (iVar11 == -1) {
                        iVar11 = (int)local_378[2];
                        *(int *)(local_378 + 2) = iVar11 + 1;
                      }
                      else {
                        uVar34 = *(undefined4 *)((long)&local_2e0 + lVar31 * 4);
                      }
                      if ((int)uVar29 < 0) {
                        if (bVar7) {
                          auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                          uVar42 = auVar49._8_8_;
                          iVar12 = auVar49._0_4_;
                          uVar47 = auVar49._4_4_;
                          if (iVar12 == -1) goto LAB_0014e4e8;
                          iVar13 = (int)plVar6[2];
                        }
                        else {
                          iVar12 = (int)local_378[2];
                          uVar47 = 4;
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                      }
                      else {
                        iVar12 = *(int *)((long)&local_320 + (long)(int)uVar29 * 4);
                        if (iVar12 == -1) {
                          iVar12 = (int)local_378[2];
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                        else {
                          iVar13 = (int)local_378[2];
                          uVar42 = 0;
                          uVar47 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar29 * 4);
                        }
                      }
                      uVar29 = *(uint *)(puVar2 + 2);
                      uVar38 = *(uint *)((long)puVar2 + 0x14);
                      *(int *)(plVar6 + 2) = iVar13 + 1;
                      pvVar17 = (void *)puVar2[1];
                      if (uVar38 <= uVar29) {
                        if (uVar38 == 0) {
                          sVar25 = 0x880;
                          uVar38 = 0x10;
                        }
                        else {
                          uVar38 = uVar38 << 1;
                          sVar25 = (ulong)uVar38 * 0x88;
                        }
                        pvVar17 = realloc(pvVar17,sVar25);
                        if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                        puVar2[1] = pvVar17;
                        uVar29 = *(uint *)(puVar2 + 2);
                        *(uint *)((long)puVar2 + 0x14) = uVar38;
                      }
                      uVar28 = 6;
                      *(int *)((long)&local_320 + lVar31 * 4) = iVar13;
                      lVar31 = (ulong)uVar29 * 0x88;
                      *(uint *)(puVar2 + 2) = uVar29 + 1;
                      goto LAB_0014e710;
                    }
                  }
                  else if (((*(char *)(lVar31 + 0x20) == 'o') && (*(char *)(lVar31 + 0x21) == 'r'))
                          && (*(char *)(lVar31 + 0x22) == '\0')) {
                    if (-1 < (int)uVar33) {
                      lVar31 = (long)(int)uVar33;
                      iVar11 = *(int *)((long)&local_320 + lVar31 * 4);
                      if (iVar11 == -1) {
                        iVar11 = (int)local_378[2];
                        *(int *)(local_378 + 2) = iVar11 + 1;
                      }
                      else {
                        uVar34 = *(undefined4 *)((long)&local_2e0 + lVar31 * 4);
                      }
                      if ((int)uVar29 < 0) {
                        if (bVar7) {
                          auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                          uVar42 = auVar49._8_8_;
                          iVar12 = auVar49._0_4_;
                          uVar47 = auVar49._4_4_;
                          if (iVar12 == -1) goto LAB_0014e4e8;
                          iVar13 = (int)plVar6[2];
                        }
                        else {
                          iVar12 = (int)local_378[2];
                          uVar47 = 4;
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                      }
                      else {
                        uVar35 = -(uVar40 >> 0x1f) & 0xfffffffc00000000 | uVar40 << 2;
                        iVar12 = *(int *)((long)&local_320 + uVar35);
                        if (iVar12 == -1) {
                          iVar12 = (int)local_378[2];
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                        else {
                          iVar13 = (int)local_378[2];
                          uVar42 = 0;
                          uVar47 = *(undefined4 *)((long)&local_2e0 + uVar35);
                        }
                      }
                      uVar29 = *(uint *)(puVar2 + 2);
                      uVar38 = *(uint *)((long)puVar2 + 0x14);
                      *(int *)(plVar6 + 2) = iVar13 + 1;
                      pvVar17 = (void *)puVar2[1];
                      if (uVar38 <= uVar29) {
                        uVar5 = uVar38 << 1;
                        if (uVar38 == 0) {
                          uVar5 = 0x10;
                        }
                        pvVar17 = realloc(pvVar17,(ulong)uVar5 * 0x88);
                        if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                        puVar2[1] = pvVar17;
                        uVar29 = *(uint *)(puVar2 + 2);
                        *(uint *)((long)puVar2 + 0x14) = uVar5;
                      }
                      *(int *)((long)&local_320 + lVar31 * 4) = iVar13;
                      lVar31 = (ulong)uVar29 * 0x88;
                      uVar28 = 7;
                      *(uint *)(puVar2 + 2) = uVar29 + 1;
                      goto LAB_0014e710;
                    }
                  }
                  else {
                    iVar12 = strcmp(pcVar36,"xor");
                    plVar6 = local_378;
                    if (iVar12 == 0) {
                      if (-1 < (int)uVar33) {
                        uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                        iVar11 = *(int *)((long)&local_320 + uVar35);
                        if (iVar11 == -1) {
                          iVar11 = (int)local_378[2];
                          *(int *)(local_378 + 2) = iVar11 + 1;
                        }
                        else {
                          uVar34 = *(undefined4 *)((long)&local_2e0 + uVar35);
                        }
                        if ((int)uVar29 < 0) {
                          if (bVar7) {
                            auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                            uVar42 = auVar49._8_8_;
                            iVar12 = auVar49._0_4_;
                            uVar47 = auVar49._4_4_;
                            if (iVar12 == -1) goto LAB_0014e4e8;
                            iVar13 = (int)plVar6[2];
                          }
                          else {
                            iVar12 = (int)local_378[2];
                            uVar47 = 4;
                            uVar42 = 0;
                            iVar13 = iVar12 + 1;
                            *(int *)(local_378 + 2) = iVar13;
                          }
                        }
                        else {
                          uVar35 = -(uVar40 >> 0x1f) & 0xfffffffc00000000 | uVar40 << 2;
                          iVar12 = *(int *)((long)&local_320 + uVar35);
                          if (iVar12 == -1) {
                            iVar12 = (int)local_378[2];
                            uVar42 = 0;
                            iVar13 = iVar12 + 1;
                            *(int *)(local_378 + 2) = iVar13;
                          }
                          else {
                            iVar13 = (int)local_378[2];
                            uVar42 = 0;
                            uVar47 = *(undefined4 *)((long)&local_2e0 + uVar35);
                          }
                        }
                        *(int *)(plVar6 + 2) = iVar13 + 1;
                        puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                        if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                        lVar31 = (long)(int)uVar33 * 4;
                        uVar28 = 8;
                        puVar22[2] = iVar13;
                        *(int *)((long)&local_320 + lVar31) = iVar13;
                        puVar22[3] = uVar46;
LAB_0014ea9c:
                        *(undefined4 *)((long)&local_2e0 + lVar31) = uVar46;
                        puVar22[6] = iVar11;
                        puVar22[7] = uVar34;
                        *puVar22 = uVar28;
                        *(undefined8 *)(puVar22 + 4) = 0;
                        *(undefined8 *)(puVar22 + 8) = 0;
                        puVar22[10] = iVar12;
                        puVar22[0xb] = uVar47;
                        *(undefined8 *)(puVar22 + 0xc) = uVar42;
                        puVar22[0x12] = 2;
                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                      }
                    }
                    else {
                      iVar12 = strcmp(pcVar36,"shl");
                      plVar6 = local_378;
                      if (iVar12 == 0) {
                        if (-1 < (int)uVar33) {
                          uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                          iVar11 = *(int *)((long)&local_320 + uVar35);
                          if (iVar11 == -1) {
                            iVar11 = (int)local_378[2];
                            *(int *)(local_378 + 2) = iVar11 + 1;
                          }
                          else {
                            uVar34 = *(undefined4 *)((long)&local_2e0 + uVar35);
                          }
                          if ((int)uVar29 < 0) {
                            if (bVar7) {
                              auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                              uVar42 = auVar49._8_8_;
                              iVar12 = auVar49._0_4_;
                              uVar47 = auVar49._4_4_;
                              if (iVar12 == -1) goto LAB_0014e4e8;
                              iVar13 = (int)plVar6[2];
                            }
                            else {
                              iVar12 = (int)local_378[2];
                              uVar47 = 4;
                              uVar42 = 0;
                              iVar13 = iVar12 + 1;
                              *(int *)(local_378 + 2) = iVar13;
                            }
                          }
                          else {
                            uVar35 = -(uVar40 >> 0x1f) & 0xfffffffc00000000 | uVar40 << 2;
                            iVar12 = *(int *)((long)&local_320 + uVar35);
                            if (iVar12 == -1) {
                              iVar12 = (int)local_378[2];
                              uVar42 = 0;
                              iVar13 = iVar12 + 1;
                              *(int *)(local_378 + 2) = iVar13;
                            }
                            else {
                              iVar13 = (int)local_378[2];
                              uVar42 = 0;
                              uVar47 = *(undefined4 *)((long)&local_2e0 + uVar35);
                            }
                          }
                          *(int *)(plVar6 + 2) = iVar13 + 1;
                          puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                          if (puVar22 != (undefined4 *)0x0) {
                            lVar31 = (long)(int)uVar33 * 4;
                            uVar28 = 9;
                            puVar22[2] = iVar13;
                            *(int *)((long)&local_320 + lVar31) = iVar13;
                            puVar22[3] = uVar46;
                            goto LAB_0014ea9c;
                          }
                          goto LAB_0014e4e8;
                        }
                      }
                      else {
                        iVar12 = strcmp(pcVar36,"shr");
                        if ((iVar12 == 0) || (iVar12 = strcmp(pcVar36,"sar"), iVar12 == 0)) {
                          plVar6 = local_378;
                          if (-1 < (int)uVar33) {
                            uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                            iVar11 = *(int *)((long)&local_320 + uVar35);
                            if (iVar11 == -1) {
                              iVar11 = (int)local_378[2];
                              *(int *)(local_378 + 2) = iVar11 + 1;
                            }
                            else {
                              uVar34 = *(undefined4 *)((long)&local_2e0 + uVar35);
                            }
                            if ((int)uVar29 < 0) {
                              if (bVar7) {
                                auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                                uVar42 = auVar49._8_8_;
                                iVar12 = auVar49._0_4_;
                                uVar47 = auVar49._4_4_;
                                if (iVar12 == -1) goto LAB_0014e4e8;
                                iVar13 = (int)plVar6[2];
                              }
                              else {
                                iVar12 = (int)local_378[2];
                                uVar47 = 4;
                                uVar42 = 0;
                                iVar13 = iVar12 + 1;
                                *(int *)(local_378 + 2) = iVar13;
                              }
                            }
                            else {
                              uVar35 = -(uVar40 >> 0x1f) & 0xfffffffc00000000 | uVar40 << 2;
                              iVar12 = *(int *)((long)&local_320 + uVar35);
                              if (iVar12 == -1) {
                                iVar12 = (int)local_378[2];
                                uVar42 = 0;
                                iVar13 = iVar12 + 1;
                                *(int *)(local_378 + 2) = iVar13;
                              }
                              else {
                                iVar13 = (int)local_378[2];
                                uVar42 = 0;
                                uVar47 = *(undefined4 *)((long)&local_2e0 + uVar35);
                              }
                            }
                            *(int *)(plVar6 + 2) = iVar13 + 1;
                            puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                            if (puVar22 != (undefined4 *)0x0) {
                              lVar31 = (long)(int)uVar33 * 4;
                              puVar22[2] = iVar13;
                              puVar22[3] = uVar46;
                              uVar28 = 10;
                              *(int *)((long)&local_320 + lVar31) = iVar13;
                              goto LAB_0014ea9c;
                            }
                            goto LAB_0014e4e8;
                          }
                        }
                        else {
                          iVar12 = strcmp(pcVar36,"neg");
                          plVar6 = local_378;
                          if (iVar12 == 0) {
                            if (-1 < (int)uVar33) {
                              auVar49 = emit_const(puVar2,local_378,0,uVar18);
                              if (auVar49._0_4_ == -1) goto LAB_0014e4e8;
                              uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                              iVar11 = *(int *)((long)&local_320 + uVar35);
                              if (iVar11 == -1) {
                                iVar11 = (int)plVar6[2];
                                iVar12 = iVar11 + 1;
                                *(int *)(plVar6 + 2) = iVar12;
                                uVar47 = uVar46;
                              }
                              else {
                                iVar12 = (int)plVar6[2];
                                uVar47 = *(undefined4 *)((long)&local_2e0 + uVar35);
                              }
                              *(int *)(plVar6 + 2) = iVar12 + 1;
                              puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                              if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                              *(long *)(puVar22 + 8) = auVar49._8_8_;
                              *(undefined4 *)((long)&local_2e0 + (long)(int)uVar33 * 4) = uVar46;
                              *(int *)((long)&local_320 + (long)(int)uVar33 * 4) = iVar12;
                              *puVar22 = 3;
                              puVar22[2] = iVar12;
                              puVar22[3] = uVar46;
                              *(undefined8 *)(puVar22 + 4) = 0;
                              *(long *)(puVar22 + 6) = auVar49._0_8_;
                              puVar22[10] = iVar11;
                              puVar22[0xb] = uVar47;
                              *(undefined8 *)(puVar22 + 0xc) = 0;
                              puVar22[0x12] = 2;
                              *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                            }
                          }
                          else {
                            iVar12 = strcmp(pcVar36,"not");
                            plVar6 = local_378;
                            if (iVar12 == 0) {
                              if (-1 < (int)uVar33) {
                                uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                                iVar11 = *(int *)((long)&local_320 + uVar35);
                                if (iVar11 == -1) {
                                  iVar11 = (int)local_378[2];
                                  *(int *)(local_378 + 2) = iVar11 + 1;
                                }
                                else {
                                  uVar34 = *(undefined4 *)((long)&local_2e0 + uVar35);
                                }
                                auVar49 = emit_const(puVar2,local_378,0xffffffffffffffff,uVar18);
                                if (auVar49._0_4_ == -1) goto LAB_0014e4e8;
                                iVar12 = (int)plVar6[2];
                                *(int *)(plVar6 + 2) = iVar12 + 1;
                                puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                puVar22[2] = iVar12;
                                *(int *)((long)&local_320 + (long)(int)uVar33 * 4) = iVar12;
                                *(undefined4 *)((long)&local_2e0 + (long)(int)uVar33 * 4) = uVar46;
                                *puVar22 = 8;
                                puVar22[3] = uVar46;
LAB_0014ef94:
                                *(undefined8 *)(puVar22 + 4) = 0;
                                puVar22[6] = iVar11;
                                puVar22[7] = uVar34;
                                *(undefined8 *)(puVar22 + 8) = 0;
                                *(undefined1 (*) [16])(puVar22 + 10) = auVar49;
                                puVar22[0x12] = 2;
                                *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                              }
                            }
                            else {
                              iVar12 = strcmp(pcVar36,"inc");
                              plVar6 = local_378;
                              if (iVar12 == 0) {
                                if (-1 < (int)uVar33) {
                                  uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                                  iVar11 = *(int *)((long)&local_320 + uVar35);
                                  if (iVar11 == -1) {
                                    iVar11 = (int)local_378[2];
                                    *(int *)(local_378 + 2) = iVar11 + 1;
                                  }
                                  else {
                                    uVar34 = *(undefined4 *)((long)&local_2e0 + uVar35);
                                  }
                                  auVar49 = emit_const(puVar2,local_378,1,uVar18);
                                  if (auVar49._0_4_ != -1) {
                                    iVar12 = (int)plVar6[2];
                                    *(int *)(plVar6 + 2) = iVar12 + 1;
                                    puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                    if (puVar22 != (undefined4 *)0x0) {
                                      puVar22[2] = iVar12;
                                      *(int *)((long)&local_320 + (long)(int)uVar33 * 4) = iVar12;
                                      *(undefined4 *)((long)&local_2e0 + (long)(int)uVar33 * 4) =
                                           uVar46;
                                      *puVar22 = 2;
                                      puVar22[3] = uVar46;
                                      goto LAB_0014ef94;
                                    }
                                  }
                                  goto LAB_0014e4e8;
                                }
                              }
                              else {
                                iVar12 = strcmp(pcVar36,"dec");
                                plVar6 = local_378;
                                if (iVar12 == 0) {
                                  if (-1 < (int)uVar33) {
                                    iVar11 = *(int *)((long)&local_320 + (long)(int)uVar33 * 4);
                                    if (iVar11 == -1) {
                                      iVar11 = (int)local_378[2];
                                      *(int *)(local_378 + 2) = iVar11 + 1;
                                    }
                                    else {
                                      uVar34 = *(undefined4 *)
                                                ((long)&local_2e0 + (long)(int)uVar33 * 4);
                                    }
                                    auVar49 = emit_const(puVar2,local_378,1,uVar18);
                                    if (auVar49._0_4_ != -1) {
                                      iVar12 = (int)plVar6[2];
                                      *(int *)(plVar6 + 2) = iVar12 + 1;
                                      puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                      if (puVar22 != (undefined4 *)0x0) {
                                        lVar31 = (long)(int)uVar33 * 4;
                                        puVar22[2] = iVar12;
                                        *(int *)((long)&local_320 + lVar31) = iVar12;
                                        *(undefined4 *)((long)&local_2e0 + lVar31) = uVar46;
                                        *puVar22 = 3;
                                        puVar22[3] = uVar46;
                                        goto LAB_0014ef94;
                                      }
                                    }
                                    goto LAB_0014e4e8;
                                  }
                                }
                                else {
                                  iVar12 = strncmp(pcVar36,"set",3);
                                  if (iVar12 == 0) {
                                    if (-1 < (int)uVar33) {
                                      iVar12 = x86_cond_suffix_to_cmp(lVar31 + 0x23);
                                      iVar11 = (int)local_378[2];
                                      *(int *)(local_378 + 2) = iVar11 + 1;
                                      piVar20 = (int *)irblock_alloc_instr(puVar2);
                                      if (piVar20 == (int *)0x0) goto LAB_0014e4e8;
                                      if (iVar12 == 0x1d || local_3d0 == -1) {
                                        if (local_3cc == -1) {
                                          iVar13 = 0;
                                          *piVar20 = 0x1d;
                                          piVar20[2] = iVar11;
                                          piVar20[3] = 1;
                                          piVar20[4] = 0;
                                          piVar20[5] = 0;
                                        }
                                        else {
                                          iVar13 = 1;
                                          *piVar20 = 0;
                                          piVar20[2] = iVar11;
                                          piVar20[3] = 1;
                                          piVar20[4] = 0;
                                          piVar20[5] = 0;
                                          piVar20[6] = local_3cc;
                                          piVar20[7] = 6;
                                          piVar20[8] = 0;
                                          piVar20[9] = 0;
                                        }
                                      }
                                      else {
                                        piVar20[2] = iVar11;
                                        piVar20[3] = 1;
                                        iVar13 = 2;
                                        *piVar20 = iVar12;
                                        piVar20[4] = 0;
                                        piVar20[5] = 0;
                                        *(ulong *)(piVar20 + 6) = uVar48;
                                        piVar20[8] = 0;
                                        piVar20[9] = 0;
                                        *(undefined1 (*) [16])(piVar20 + 10) = auVar50;
                                      }
                                      uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                                      piVar20[0x12] = iVar13;
                                      *(int *)((long)&local_320 + uVar35) = iVar11;
                                      *(undefined4 *)((long)&local_2e0 + uVar35) = 1;
                                      *(undefined8 *)(piVar20 + 0x1c) = uVar18;
                                    }
                                  }
                                  else {
                                    iVar12 = strcmp(pcVar36,"bswap");
                                    plVar6 = local_378;
                                    if (iVar12 == 0) {
                                      if (-1 < (int)uVar33) {
                                        iVar11 = (int)local_378[2];
                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                        puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                        if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                        *puVar22 = 0;
                                        puVar22[2] = iVar11;
                                        puVar22[3] = uVar46;
                                        iVar12 = *(int *)((long)&local_320 + (long)(int)uVar33 * 4);
                                        *(undefined8 *)(puVar22 + 4) = 0;
                                        if (iVar12 == -1) {
                                          iVar12 = (int)plVar6[2];
                                          *(int *)(plVar6 + 2) = iVar12 + 1;
                                        }
                                        *(int *)((long)&local_320 + (long)(int)uVar33 * 4) = iVar11;
                                        puVar22[6] = iVar12;
                                        puVar22[7] = uVar46;
                                        *(undefined8 *)(puVar22 + 8) = 0;
                                        puVar22[0x12] = 1;
                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                      }
                                    }
                                    else {
                                      iVar12 = strcmp(pcVar36,"bsf");
                                      if (((iVar12 == 0) ||
                                          (iVar12 = strcmp(pcVar36,"bsr"), iVar12 == 0)) ||
                                         ((iVar12 = strcmp(pcVar36,"popcnt"), iVar12 == 0 ||
                                          ((iVar12 = strcmp(pcVar36,"lzcnt"), iVar12 == 0 ||
                                           (iVar12 = strcmp(pcVar36,"tzcnt"), iVar12 == 0)))))) {
                                        if (-1 < (int)uVar33) {
                                          iVar12 = (int)local_378[2];
                                          iVar11 = iVar12 + 1;
                                          if ((int)uVar29 < 0) {
                                            *(int *)(local_378 + 2) = iVar11;
                                            iVar15 = iVar11;
                                            iVar13 = iVar12;
                                            uVar47 = uVar46;
                                          }
                                          else {
                                            iVar13 = *(int *)((long)&local_320 +
                                                             (long)(int)uVar29 * 4);
                                            iVar15 = iVar12;
                                            if (iVar13 == -1) {
                                              *(int *)(local_378 + 2) = iVar11;
                                              iVar15 = iVar11;
                                              iVar13 = iVar12;
                                            }
                                          }
                                          *(int *)(local_378 + 2) = iVar15 + 1;
                                          puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                          if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                          uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 |
                                                   uVar35 << 2;
                                          *puVar22 = 0;
                                          *(int *)((long)&local_320 + uVar35) = iVar15;
                                          *(undefined4 *)((long)&local_2e0 + uVar35) = uVar46;
                                          puVar22[0x12] = 1;
                                          puVar22[2] = iVar15;
                                          puVar22[3] = uVar46;
                                          *(undefined8 *)(puVar22 + 4) = 0;
                                          puVar22[6] = iVar13;
                                          puVar22[7] = uVar47;
                                          *(undefined8 *)(puVar22 + 8) = 0;
                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                        }
                                      }
                                      else {
                                        iVar12 = strncmp(pcVar36,"cmov",4);
                                        if (iVar12 == 0) {
                                          if (-1 < (int)(uVar29 | uVar33)) {
                                            iVar13 = x86_cond_suffix_to_cmp(lVar31 + 0x24);
                                            plVar6 = local_378;
                                            iVar12 = (int)local_378[2];
                                            iVar11 = iVar12 + 1;
                                            if (iVar13 == 0x1d || local_3d0 == -1) {
                                              iVar13 = iVar12;
                                              iVar15 = local_3cc;
                                              if (local_3cc == -1) {
                                                *(int *)(local_378 + 2) = iVar11;
                                                iVar13 = iVar11;
                                                iVar15 = iVar12;
                                              }
                                            }
                                            else {
                                              *(int *)(local_378 + 2) = iVar11;
                                              piVar20 = (int *)irblock_alloc_instr(puVar2);
                                              if (piVar20 == (int *)0x0) goto LAB_0014e4e8;
                                              piVar20[2] = iVar12;
                                              piVar20[3] = 6;
                                              *(ulong *)(piVar20 + 6) = uVar48;
                                              *(long *)(piVar20 + 10) = auVar50._0_8_;
                                              lVar31 = plVar6[2];
                                              piVar20[0x12] = 2;
                                              *piVar20 = iVar13;
                                              piVar20[4] = 0;
                                              piVar20[5] = 0;
                                              piVar20[8] = 0;
                                              piVar20[9] = 0;
                                              *(undefined8 *)(piVar20 + 0xc) = local_3d8;
                                              *(undefined8 *)(piVar20 + 0x1c) = uVar18;
                                              iVar13 = (int)lVar31;
                                              iVar15 = iVar12;
                                            }
                                            iVar12 = *(int *)((long)&local_320 +
                                                             (long)(int)uVar29 * 4);
                                            iVar11 = iVar13;
                                            if (iVar12 == -1) {
                                              iVar11 = iVar13 + 1;
                                              *(int *)(plVar6 + 2) = iVar11;
                                              iVar12 = iVar13;
                                            }
                                            iVar14 = *(int *)((long)&local_320 +
                                                             (long)(int)uVar33 * 4);
                                            iVar13 = iVar11;
                                            if (iVar14 == -1) {
                                              iVar13 = iVar11 + 1;
                                              *(int *)(plVar6 + 2) = iVar13;
                                              iVar14 = iVar11;
                                            }
                                            *(int *)(plVar6 + 2) = iVar13 + 1;
                                            puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                            if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                            *puVar22 = 0x1c;
                                            *(undefined4 *)
                                             ((long)&local_2e0 + (long)(int)uVar33 * 4) = uVar46;
                                            *(int *)((long)&local_320 + (long)(int)uVar33 * 4) =
                                                 iVar13;
                                            puVar22[2] = iVar13;
                                            puVar22[3] = uVar46;
                                            *(undefined8 *)(puVar22 + 4) = 0;
                                            puVar22[6] = iVar15;
                                            puVar22[7] = 6;
                                            *(undefined8 *)(puVar22 + 8) = 0;
                                            puVar22[10] = iVar12;
                                            puVar22[0xb] = uVar47;
                                            *(undefined8 *)(puVar22 + 0xc) = 0;
                                            puVar22[0xe] = iVar14;
                                            puVar22[0xf] = uVar46;
                                            *(undefined8 *)(puVar22 + 0x10) = 0;
                                            puVar22[0x12] = 3;
                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                          }
                                        }
                                        else {
                                          iVar12 = strcmp(pcVar36,"cmp");
                                          if ((iVar12 == 0) ||
                                             (iVar12 = strcmp(pcVar36,"test"), iVar12 == 0)) {
                                            plVar6 = local_378;
                                            if ((int)uVar33 < 0) goto LAB_0014dc04;
                                            local_3d0 = *(int *)((long)&local_320 +
                                                                (long)(int)uVar33 * 4);
                                            if (local_3d0 == -1) {
                                              local_3d0 = (int)local_378[2];
                                              *(int *)(local_378 + 2) = local_3d0 + 1;
                                            }
                                            uVar48 = CONCAT44(uVar46,local_3d0);
                                            if ((int)uVar29 < 0) {
                                              if (bVar7) {
                                                auVar50 = emit_const(puVar2,local_378,local_3f8,
                                                                     uVar18);
                                                goto LAB_00150894;
                                              }
                                              iVar11 = (int)local_378[2];
                                              uVar47 = 4;
                                              local_3cc = iVar11 + 1;
                                              *(int *)(local_378 + 2) = local_3cc;
LAB_00150518:
                                              auVar50._4_4_ = uVar47;
                                              auVar50._0_4_ = iVar11;
                                              auVar50._8_8_ = 0;
                                            }
                                            else {
                                              local_3cc = (int)local_378[2];
                                              iVar11 = *(int *)((long)&local_320 +
                                                               (long)(int)uVar29 * 4);
                                              auVar50._4_4_ = uVar47;
                                              auVar50._0_4_ = local_3cc;
                                              if (iVar11 != -1) goto LAB_00150518;
                                              *(int *)(local_378 + 2) = local_3cc + 1;
                                              auVar50._8_8_ = 0;
LAB_00150894:
                                              if ((bool)(bVar7 & auVar50._0_4_ == -1))
                                              goto LAB_0014e4e8;
                                              local_3cc = (int)plVar6[2];
                                            }
                                            *(int *)(plVar6 + 2) = local_3cc + 1;
                                            puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                            if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                            puVar22[2] = local_3cc;
                                            puVar22[3] = 6;
                                            puVar22[6] = local_3d0;
                                            puVar22[0x12] = 2;
                                            *puVar22 = 0xb;
                                            *(undefined8 *)(puVar22 + 4) = 0;
                                            puVar22[7] = uVar46;
                                            *(undefined8 *)(puVar22 + 8) = 0;
                                            *(undefined1 (*) [16])(puVar22 + 10) = auVar50;
                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                          }
                                          else {
                                            iVar12 = strcmp(pcVar36,"jmp");
                                            cVar10 = *(char *)(lVar31 + 0x20);
                                            if (cVar10 == 'j') {
                                              if (iVar12 != 0) {
                                                iVar12 = x86_cond_suffix_to_cmp(lVar31 + 0x21);
                                                iVar11 = local_3cc;
                                                if (iVar12 != 0x1d && local_3d0 != -1) {
                                                  iVar11 = (int)local_378[2];
                                                  *(int *)(local_378 + 2) = iVar11 + 1;
                                                  piVar20 = (int *)irblock_alloc_instr(puVar2);
                                                  if (piVar20 == (int *)0x0) goto LAB_0014e4e8;
                                                  piVar20[2] = iVar11;
                                                  piVar20[3] = 6;
                                                  piVar20[0x12] = 2;
                                                  *piVar20 = iVar12;
                                                  piVar20[4] = 0;
                                                  piVar20[5] = 0;
                                                  *(ulong *)(piVar20 + 6) = uVar48;
                                                  piVar20[8] = 0;
                                                  piVar20[9] = 0;
                                                  *(undefined1 (*) [16])(piVar20 + 10) = auVar50;
                                                  *(undefined8 *)(piVar20 + 0x1c) = uVar18;
                                                }
                                                puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                                if (puVar22 != (undefined4 *)0x0) {
                                                  puVar22[0x12] = 1;
                                                  *puVar22 = 0x17;
                                                  *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = 6;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  goto LAB_0014dc04;
                                                }
                                                goto LAB_0014e4e8;
                                              }
                                            }
                                            else if (iVar12 != 0) {
                                              iVar12 = strcmp(pcVar36,"call");
                                              if (iVar12 == 0) {
                                                iVar11 = (int)local_378[2];
                                                *(int *)(local_378 + 2) = iVar11 + 1;
                                                puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                                if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                                *puVar22 = 0x19;
                                                puVar22[2] = iVar11;
                                                puVar22[3] = 4;
                                                *(undefined8 *)(puVar22 + 4) = 0;
                                                if ((acStack_159[1] == '0') &&
                                                   ((acStack_159[2] & 0xdfU) == 0x58)) {
                                                  uVar23 = strtoull(acStack_159 + 1,(char **)0x0,0);
                                                }
                                                else {
                                                  uVar23 = 0;
                                                }
                                                uVar42 = DAT_0020a3e8;
                                                *(ulonglong *)(puVar22 + 8) = uVar23;
                                                puVar22[0x12] = 1;
                                                uVar35 = 0;
                                                *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                *(undefined8 *)(puVar22 + 6) = uVar42;
                                                do {
                                                  if (*(int *)((long)&local_320 +
                                                              (long)(int)(&sysv_arg_regs_0)[uVar35]
                                                              * 4) == -1) {
                                                    if ((int)uVar35 == 0) goto LAB_00150a9c;
                                                    break;
                                                  }
                                                  uVar35 = uVar35 + 1;
                                                } while (uVar35 != 6);
                                                puVar24 = malloc(-((uVar35 & 0xffffffff) >> 0x1f) &
                                                                 0xfffffff000000000 |
                                                                 (uVar35 & 0xffffffff) << 4);
                                                *(undefined4 **)(puVar22 + 0x14) = puVar24;
                                                if (puVar24 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                                lVar31 = 0;
                                                *(undefined8 *)(puVar22 + 0x16) = 0;
                                                puVar22[0x18] = (int)uVar35;
                                                do {
                                                  iVar12 = (&sysv_arg_regs_0)[lVar31];
                                                  lVar31 = lVar31 + 1;
                                                  *(undefined8 *)(puVar24 + 2) = 0;
                                                  uVar46 = *(undefined4 *)
                                                            ((long)&local_2e0 + (long)iVar12 * 4);
                                                  *puVar24 = *(undefined4 *)
                                                              ((long)&local_320 + (long)iVar12 * 4);
                                                  puVar24[1] = uVar46;
                                                  puVar24 = puVar24 + 4;
                                                } while ((int)lVar31 < (int)uVar35);
LAB_00150a9c:
                                                local_320 = CONCAT44(local_320._4_4_,iVar11);
                                                local_2e0 = CONCAT44(local_2e0._4_4_,4);
                                              }
                                              else {
                                                iVar12 = strcmp(pcVar36,"ret");
                                                if (iVar12 == 0) {
                                                  puVar22 = (undefined4 *)
                                                            irblock_alloc_instr(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014e4e8;
                                                  *puVar22 = 0x1a;
                                                  *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                  if (((int)local_2a0 == -1) ||
                                                     (iVar11 = (int)local_2a0,
                                                     iVar12 = (int)local_260,
                                                     1 < (int)local_260 - 7U)) {
                                                    iVar11 = (int)local_320;
                                                    if ((int)local_320 == -1) {
                                                      iVar12 = 4;
                                                    }
                                                    else {
                                                      iVar12 = (int)local_2e0;
                                                    }
                                                  }
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = iVar12;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  puVar22[0x12] = 1;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                }
                                                else {
                                                  sVar25 = strlen(pcVar36);
                                                  if (((sVar25 < 2) || (pcVar36[sVar25 - 2] != 's'))
                                                     || (uVar38 = (uint)(pcVar36[sVar25 - 1] == 's')
                                                        , pcVar36[sVar25 - 1] != 'd' && uVar38 == 0)
                                                     ) {
LAB_0014f774:
                                                    if (cVar10 == 'v') {
                                                      local_394 = 0xffffffff;
                                                      local_390 = 0xffffffff;
                                                      local_38c = 0xffffffff;
                                                      local_388 = 0xffffffff;
                                                      pcVar27 = acStack_159 + 0x41;
                                                      local_384 = 0xffffffff;
                                                      local_380 = 0xffffffff;
                                                      local_37c = 0xffffffff;
                                                      local_370 = 0xffffffff;
                                                      local_368 = -1;
                                                      uStack_d0 = 0;
                                                      local_d8 = 0;
                                                      uStack_c0 = 0;
                                                      uStack_c8 = 0;
                                                      uStack_b0 = 0;
                                                      local_b8 = 0;
                                                      uStack_a0 = 0;
                                                      uStack_a8 = 0;
                                                      if (iVar11 == 2) {
                                                        iVar12 = 0;
                                                        pcVar19 = pcVar27;
                                                        while (cVar10 = *pcVar19, cVar10 != '\0') {
                                                          if (cVar10 == '[') {
                                                            iVar12 = iVar12 + 1;
                                                            pcVar19 = pcVar19 + 1;
                                                          }
                                                          else if (cVar10 == ']') {
                                                            iVar12 = iVar12 + -1;
                                                            pcVar19 = pcVar19 + 1;
                                                          }
                                                          else {
                                                            if (cVar10 == ',' && iVar12 == 0) {
                                                              snprintf((char *)&local_d8,0x40,"%s",
                                                                       pcVar19 + 1);
                                                              *pcVar19 = '\0';
                                                              if (acStack_159[0x41] != '\0') {
                                                                trim_inplace_part_0(pcVar27);
                                                              }
                                                              if ((char)local_d8 != '\0') {
                                                                trim_inplace_part_0(&local_d8);
                                                              }
                                                              zmm_lookup_isra_0(acStack_159 + 1,
                                                                                &local_388);
                                                              zmm_lookup_isra_0(pcVar27,&local_384);
                                                              zmm_lookup_isra_0(&local_d8,&local_380
                                                                               );
                                                              iVar11 = 3;
                                                              goto LAB_0014fb6c;
                                                            }
                                                            pcVar19 = pcVar19 + 1;
                                                          }
                                                        }
                                                      }
                                                      zmm_lookup_isra_0(acStack_159 + 1,&local_388);
                                                      zmm_lookup_isra_0(pcVar27,&local_384);
LAB_0014fb6c:
                                                      uVar33 = local_388;
                                                      pcVar19 = acStack_159 + 1;
                                                      if ((int)local_388 < 0) {
                                                        ymm_lookup_isra_0(pcVar19,&local_394);
                                                      }
                                                      uVar29 = local_384;
                                                      if ((int)local_384 < 0) {
                                                        ymm_lookup_isra_0(pcVar27,&local_390);
                                                      }
                                                      uVar38 = local_380;
                                                      if ((iVar11 == 3) && ((int)local_380 < 0)) {
                                                        ymm_lookup_isra_0(&local_d8,&local_38c);
                                                      }
                                                      uVar5 = local_394;
                                                      local_3f8 = (ulong)local_394;
                                                      if ((int)(uVar33 & local_394) < 0) {
                                                        xmm_lookup_isra_0(pcVar19,&local_37c);
                                                      }
                                                      uVar4 = local_390;
                                                      if ((int)(uVar29 & local_390) < 0) {
                                                        xmm_lookup_isra_0(pcVar27,&local_370);
                                                      }
                                                      if ((iVar11 == 3) &&
                                                         ((int)(uVar38 & local_38c) < 0)) {
                                                        xmm_lookup_isra_0(&local_d8,&local_368);
                                                      }
                                                      if ((int)uVar33 < 0) {
                                                        if (-1 < (int)uVar29) {
                                                          if ((int)uVar5 < 0) {
                                                            local_3f8 = (ulong)local_37c;
                                                            if ((int)local_37c < 0) {
                                                              iVar12 = 0xc;
LAB_00150428:
                                                              puVar43 = (undefined8 *)0x0;
                                                              local_3f8._0_4_ = 0xffffffff;
                                                              goto LAB_0014fc40;
                                                            }
                                                            puVar43 = &local_2a0;
                                                            iVar12 = 0xc;
                                                          }
                                                          else {
                                                            puVar43 = &local_220;
                                                            iVar12 = 0xc;
                                                          }
                                                          goto LAB_0014fc44;
                                                        }
                                                        if ((int)uVar38 < 0) {
                                                          if ((int)uVar5 < 0) {
                                                            iVar12 = 10 - ((int)~(uVar4 & local_38c)
                                                                          >> 0x1f);
                                                            goto LAB_001500ec;
                                                          }
                                                          puVar43 = &local_220;
                                                          iVar12 = 0xb;
                                                        }
                                                        else if ((int)uVar5 < 0) {
                                                          iVar12 = 0xc;
LAB_001500ec:
                                                          local_3f8 = (ulong)local_37c;
                                                          if ((int)local_37c < 0) goto LAB_00150428;
                                                          puVar43 = &local_2a0;
                                                        }
                                                        else {
                                                          puVar43 = &local_220;
                                                          iVar12 = 0xc;
                                                        }
LAB_001500fc:
                                                        if (((int)uVar4 < 0) ||
                                                           (iVar13 = *(int *)((long)&local_220 +
                                                                             (long)(int)uVar4 * 4),
                                                           iVar13 == -1)) {
                                                          if ((int)local_370 < 0) {
                                                            iVar13 = -1;
                                                          }
                                                          else {
                                                            iVar13 = *(int *)((long)&local_2a0 +
                                                                             (long)(int)local_370 *
                                                                             4);
                                                          }
                                                        }
                                                      }
                                                      else {
                                                        iVar12 = 0xc;
                                                        puVar43 = local_1d8;
                                                        local_3f8._0_4_ = uVar33;
LAB_0014fc40:
                                                        local_3f8 = (ulong)(uint)local_3f8;
                                                        if ((int)uVar29 < 0) goto LAB_001500fc;
LAB_0014fc44:
                                                        iVar13 = *(int *)((long)local_1d8 +
                                                                         (long)(int)uVar29 * 4);
                                                        if (iVar13 == -1) goto LAB_001500fc;
                                                      }
                                                      if ((((int)uVar38 < 0) ||
                                                          (iVar15 = *(int *)((long)local_1d8 +
                                                                            (long)(int)uVar38 * 4),
                                                          iVar15 == -1)) &&
                                                         (((int)local_38c < 0 ||
                                                          (iVar15 = *(int *)((long)&local_220 +
                                                                            (long)(int)local_38c * 4
                                                                            ), iVar15 == -1)))) {
                                                        if (local_368 < 0) {
                                                          iVar15 = -1;
                                                        }
                                                        else {
                                                          iVar15 = *(int *)((long)&local_2a0 +
                                                                           (long)local_368 * 4);
                                                        }
                                                      }
                                                      iVar14 = strncmp(pcVar36,"vmov",4);
                                                      if (iVar14 == 0) {
                                                        if ((uint)local_3f8 == 0xffffffff) {
                                                          iVar11 = is_mem_op_part_0(pcVar19);
                                                          if (iVar11 != 0 && iVar13 != -1) {
                                                            puVar22 = (undefined4 *)
                                                                      irblock_alloc_instr(puVar2);
                                                            if (puVar22 == (undefined4 *)0x0)
                                                            goto LAB_0014e4e8;
                                                            *puVar22 = 0x16;
                                                            uVar42 = DAT_0020a3e8;
                                                            puVar22[0x12] = 2;
                                                            *(undefined8 *)(puVar22 + 2) =
                                                                 0xffffffff;
                                                            *(undefined8 *)(puVar22 + 6) = uVar42;
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            puVar22[10] = iVar13;
                                                            puVar22[0xb] = iVar12;
                                                            *(undefined8 *)(puVar22 + 0xc) = 0;
                                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18
                                                            ;
                                                          }
                                                        }
                                                        else {
                                                          iVar11 = (int)local_378[2];
                                                          *(int *)(local_378 + 2) = iVar11 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014e4e8;
                                                          if (iVar13 == -1) {
                                                            is_mem_op_part_0(pcVar27);
                                                            uVar46 = 0x15;
                                                            iVar15 = 5;
                                                          }
                                                          else {
                                                            uVar46 = 0;
                                                            iVar15 = iVar12;
                                                          }
                                                          puVar22[6] = iVar13;
                                                          puVar22[7] = iVar15;
                                                          uVar35 = -(local_3f8 >> 0x1f) &
                                                                   0xfffffffc00000000 |
                                                                   local_3f8 << 2;
                                                          *puVar22 = uVar46;
                                                          puVar22[2] = iVar11;
                                                          puVar22[3] = iVar12;
                                                          *(int *)((long)puVar43 + uVar35) = iVar11;
                                                          *(undefined8 *)(puVar22 + 4) = 0;
                                                          *(undefined8 *)(puVar22 + 8) = 0;
                                                          puVar22[0x12] = 1;
                                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                          if (iVar12 == 10) {
                                                            *(undefined4 *)
                                                             ((long)&local_260 + uVar35) = 10;
                                                          }
                                                        }
                                                      }
                                                      else {
                                                        pcVar36 = (char *)(lVar31 + 0x21);
                                                        iVar14 = strncmp(pcVar36,"add",3);
                                                        if (iVar14 == 0) {
                                                          uVar46 = 2;
                                                        }
                                                        else {
                                                          iVar14 = strncmp(pcVar36,"sub",3);
                                                          if (iVar14 == 0) {
                                                            uVar46 = 3;
                                                          }
                                                          else {
                                                            iVar14 = strncmp(pcVar36,"mul",3);
                                                            if (iVar14 == 0) {
                                                              uVar46 = 4;
                                                            }
                                                            else {
                                                              iVar14 = strncmp(pcVar36,"div",3);
                                                              if (iVar14 == 0) {
                                                                uVar46 = 5;
                                                              }
                                                              else {
                                                                iVar14 = strncmp(pcVar36,"and",3);
                                                                if (iVar14 == 0) {
                                                                  uVar46 = 6;
                                                                }
                                                                else {
                                                                  iVar14 = strncmp(pcVar36,"or",2);
                                                                  if (iVar14 == 0) {
                                                                    uVar46 = 7;
                                                                  }
                                                                  else {
                                                                    iVar14 = strncmp(pcVar36,"xor",3
                                                                                    );
                                                                    if (iVar14 != 0)
                                                                    goto LAB_0014dc04;
                                                                    uVar46 = 8;
                                                                  }
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                        if ((uint)local_3f8 != 0xffffffff) {
                                                          iVar3 = (int)local_378[2];
                                                          iVar14 = iVar3 + 1;
                                                          iVar37 = iVar3;
                                                          if (iVar11 == 3) {
                                                            iVar11 = iVar13;
                                                            if (iVar13 == -1) {
                                                              *(int *)(local_378 + 2) = iVar14;
                                                              iVar37 = iVar14;
                                                              iVar11 = iVar3;
                                                            }
                                                            iVar13 = iVar15;
                                                            if (iVar15 == -1) {
                                                              *(int *)(local_378 + 2) = iVar37 + 1;
                                                              iVar13 = iVar37;
                                                              iVar37 = iVar37 + 1;
                                                            }
                                                          }
                                                          else {
                                                            iVar11 = *(int *)((long)puVar43 +
                                                                             (long)(int)(uint)
                                                  local_3f8 * 4);
                                                  if (iVar11 == -1) {
                                                    *(int *)(local_378 + 2) = iVar14;
                                                    iVar37 = iVar14;
                                                    iVar11 = iVar3;
                                                  }
                                                  if (iVar13 == -1) {
                                                    *(int *)(local_378 + 2) = iVar37 + 1;
                                                    iVar13 = iVar37;
                                                    iVar37 = iVar37 + 1;
                                                  }
                                                  }
                                                  *(int *)(local_378 + 2) = iVar37 + 1;
                                                  puVar22 = (undefined4 *)
                                                            irblock_alloc_instr(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014e4e8;
                                                  *puVar22 = uVar46;
                                                  puVar22[2] = iVar37;
                                                  puVar22[3] = iVar12;
                                                  uVar35 = -(ulong)((uint)local_3f8 >> 0x1f) &
                                                           0xfffffffc00000000 | local_3f8 << 2;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = iVar12;
                                                  *(int *)((long)puVar43 + uVar35) = iVar37;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  puVar22[10] = iVar13;
                                                  puVar22[0xb] = iVar12;
                                                  *(undefined8 *)(puVar22 + 0xc) = 0;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  if (iVar12 == 10) {
                                                    *(undefined4 *)((long)&local_260 + uVar35) = 10;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    local_370 = 0xffffffff;
                                                    local_368 = -1;
                                                    if (iVar11 == 0) {
LAB_0014f790:
                                                      if (cVar10 == 'f') {
                                                        iVar12 = strcmp(pcVar36,"fld");
                                                        if (iVar12 == 0) {
                                                          local_368 = -1;
                                                          iVar11 = (int)local_378[2];
                                                          *(int *)(local_378 + 2) = iVar11 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014e4e8;
                                                          iVar12 = st_lookup_part_0(acStack_159 + 1,
                                                                                    &local_368);
                                                          if ((iVar12 == 0) || (7 < local_368)) {
                                                            iVar12 = -1;
                                                            uVar47 = 0x15;
                                                            uVar46 = 5;
                                                          }
                                                          else {
                                                            iVar12 = *(int *)((long)&local_360 +
                                                                             (long)local_368 * 4);
                                                            uVar46 = 5;
                                                            if (iVar12 != -1) {
                                                              uVar46 = 9;
                                                            }
                                                            uVar47 = 0x15;
                                                            if (iVar12 != -1) {
                                                              uVar47 = 0;
                                                            }
                                                          }
                                                          puVar22[6] = iVar12;
                                                          puVar22[7] = uVar46;
                                                          *puVar22 = uVar47;
                                                          puVar22[2] = iVar11;
                                                          puVar22[3] = 9;
                                                          *(undefined8 *)(puVar22 + 4) = 0;
                                                          *(undefined8 *)(puVar22 + 8) = 0;
                                                          puVar22[0x12] = 1;
                                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                          local_360 = CONCAT44(local_360._4_4_,
                                                                               iVar11);
                                                        }
                                                        else {
                                                          iVar12 = strcmp(pcVar36,"fstp");
                                                          if ((iVar12 == 0) ||
                                                             (iVar12 = strcmp(pcVar36,"fst"),
                                                             iVar12 == 0)) {
                                                            local_368 = -1;
                                                            iVar12 = st_lookup_part_0(acStack_159 +
                                                                                      1,&local_368);
                                                            iVar11 = local_368;
                                                            plVar6 = local_378;
                                                            if ((iVar12 == 0) || (7 < local_368)) {
                                                              puVar22 = (undefined4 *)
                                                                        irblock_alloc_instr(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014e4e8;
                                                              *puVar22 = 0x16;
                                                              uVar42 = DAT_0020a3e8;
                                                              *(undefined8 *)(puVar22 + 2) =
                                                                   0xffffffff;
                                                              *(undefined8 *)(puVar22 + 6) = uVar42;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              if ((int)local_360 == -1) {
                                                                iVar11 = (int)local_378[2];
                                                                *(int *)(local_378 + 2) = iVar11 + 1
                                                                ;
                                                                uVar46 = 9;
                                                              }
                                                              else {
                                                                uVar46 = 9;
                                                                iVar11 = (int)local_360;
                                                              }
LAB_001500a4:
                                                              puVar22[10] = iVar11;
                                                              puVar22[0xb] = uVar46;
                                                              *(undefined8 *)(puVar22 + 0xc) = 0;
                                                              puVar22[0x12] = 2;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                            }
                                                            else {
                                                              iVar12 = (int)local_378[2];
                                                              *(int *)(local_378 + 2) = iVar12 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        irblock_alloc_instr(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014e4e8;
                                                              *puVar22 = 0;
                                                              iVar13 = (int)local_360;
                                                              if ((int)local_360 == -1) {
                                                                iVar13 = (int)plVar6[2];
                                                                *(int *)(plVar6 + 2) = iVar13 + 1;
                                                              }
                                                              puVar22[6] = iVar13;
                                                              puVar22[7] = 9;
                                                              *(int *)((long)&local_360 +
                                                                      (long)iVar11 * 4) = iVar12;
                                                              puVar22[2] = iVar12;
                                                              puVar22[3] = 9;
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                            }
                                                          }
                                                          else {
                                                            iVar12 = strncmp(pcVar36,"fadd",4);
                                                            if (iVar12 == 0) {
                                                              uVar46 = 2;
                                                            }
                                                            else {
                                                              iVar12 = strncmp(pcVar36,"fsub",4);
                                                              if (iVar12 == 0) {
                                                                uVar46 = 3;
                                                              }
                                                              else {
                                                                iVar12 = strncmp(pcVar36,"fmul",4);
                                                                if (iVar12 == 0) {
                                                                  uVar46 = 4;
                                                                }
                                                                else {
                                                                  iVar12 = strncmp(pcVar36,"fdiv",4)
                                                                  ;
                                                                  if (iVar12 != 0)
                                                                  goto LAB_0014dc04;
                                                                  uVar46 = 5;
                                                                }
                                                              }
                                                            }
                                                            iVar12 = (int)local_360;
                                                            if ((int)local_360 == -1) {
                                                              iVar12 = (int)plVar16[2];
                                                              *(int *)(plVar16 + 2) = iVar12 + 1;
                                                            }
                                                            local_368 = -1;
                                                            if (iVar11 == 2) {
                                                              iVar11 = st_lookup_part_0(acStack_159
                                                                                        + 0x41,&
                                                  local_368);
                                                  piVar20 = extraout_x1;
                                                  if (((iVar11 == 0) || (7 < local_368)) ||
                                                     (iVar11 = *(int *)((long)&local_360 +
                                                                       (long)local_368 * 4),
                                                     iVar11 == -1)) goto LAB_00150bbc;
                                                  }
                                                  else {
                                                    if (iVar11 == 1) {
                                                      piVar20 = &local_368;
LAB_00150bbc:
                                                      iVar11 = st_lookup_part_0(acStack_159 + 1,
                                                                                piVar20);
                                                      if (((iVar11 != 0) && (local_368 < 8)) &&
                                                         (iVar11 = *(int *)((long)&local_360 +
                                                                           (long)local_368 * 4),
                                                         iVar11 != -1)) goto LAB_00150b70;
                                                    }
                                                    iVar11 = (int)local_378[2];
                                                    *(int *)(local_378 + 2) = iVar11 + 1;
                                                  }
LAB_00150b70:
                                                  iVar13 = (int)local_378[2];
                                                  *(int *)(local_378 + 2) = iVar13 + 1;
                                                  puVar22 = (undefined4 *)
                                                            irblock_alloc_instr(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014e4e8;
                                                  *puVar22 = uVar46;
                                                  uVar47 = 9;
                                                  puVar22[2] = iVar13;
                                                  puVar22[3] = 9;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar12;
                                                  puVar22[7] = 9;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  puVar22[10] = iVar11;
                                                  local_360 = CONCAT44(local_360._4_4_,iVar13);
LAB_0014ff54:
                                                  puVar22[0xb] = uVar47;
                                                  *(undefined8 *)(puVar22 + 0xc) = 0;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    iVar11 = strcmp(pcVar36,"nop");
                                                    if (iVar11 != 0) {
                                                      iVar11 = strcmp(pcVar36,"push");
                                                      if (iVar11 == 0) {
                                                        iVar11 = (int)local_310;
                                                        if ((int)local_310 == -1) {
                                                          iVar11 = (int)plVar16[2];
                                                          *(int *)(plVar16 + 2) = iVar11 + 1;
                                                        }
                                                        auVar49 = emit_const(puVar2,plVar16,8,uVar18
                                                                            );
                                                        if (auVar49._0_4_ == -1) goto LAB_0014e4e8;
                                                        iVar12 = (int)plVar16[2];
                                                        *(int *)(plVar16 + 2) = iVar12 + 1;
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        *puVar22 = 3;
                                                        puVar22[2] = iVar12;
                                                        puVar22[3] = 4;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        puVar22[6] = iVar11;
                                                        puVar22[7] = 4;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        *(undefined1 (*) [16])(puVar22 + 10) =
                                                             auVar49;
                                                        puVar22[0x12] = 2;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                        local_310 = CONCAT44(local_310._4_4_,iVar12)
                                                        ;
                                                        local_2d0 = CONCAT44(local_2d0._4_4_,4);
                                                        if ((int)uVar33 < 0) {
                                                          if (bVar7) {
                                                            auVar49 = emit_const(puVar2,plVar16,
                                                                                 local_3f8,uVar18);
                                                            uVar42 = auVar49._8_8_;
                                                            iVar11 = auVar49._0_4_;
                                                            uVar46 = auVar49._4_4_;
                                                            if (iVar11 == -1) goto LAB_0014e4e8;
                                                          }
                                                          else {
                                                            uVar46 = 4;
                                                            uVar42 = 0;
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                        }
                                                        else {
                                                          uVar35 = -(uVar35 >> 0x1f) &
                                                                   0xfffffffc00000000 | uVar35 << 2;
                                                          iVar11 = *(int *)((long)&local_320 +
                                                                           uVar35);
                                                          if (iVar11 == -1) {
                                                            uVar42 = 0;
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                          else {
                                                            uVar42 = 0;
                                                            uVar46 = *(undefined4 *)
                                                                      ((long)&local_2e0 + uVar35);
                                                          }
                                                        }
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        *puVar22 = 0x16;
                                                        puVar22[0x12] = 2;
                                                        *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                        puVar22[6] = iVar12;
                                                        puVar22[7] = 5;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[10] = iVar11;
                                                        puVar22[0xb] = uVar46;
                                                        *(undefined8 *)(puVar22 + 0xc) = uVar42;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                      else {
                                                        iVar11 = strcmp(pcVar36,"pop");
                                                        if (iVar11 == 0) {
                                                          iVar11 = (int)local_310;
                                                          if ((int)local_310 == -1) {
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                          if (-1 < (int)uVar33) {
                                                            iVar12 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar12 + 1;
                                                            puVar22 = (undefined4 *)
                                                                      irblock_alloc_instr(puVar2);
                                                            if (puVar22 == (undefined4 *)0x0)
                                                            goto LAB_0014e4e8;
                                                            uVar35 = -(uVar35 >> 0x1f) &
                                                                     0xfffffffc00000000 |
                                                                     uVar35 << 2;
                                                            puVar22[0x12] = 1;
                                                            *(int *)((long)&local_320 + uVar35) =
                                                                 iVar12;
                                                            *(undefined4 *)
                                                             ((long)&local_2e0 + uVar35) = uVar46;
                                                            *puVar22 = 0x15;
                                                            puVar22[2] = iVar12;
                                                            puVar22[3] = uVar46;
                                                            *(undefined8 *)(puVar22 + 4) = 0;
                                                            puVar22[6] = iVar11;
                                                            puVar22[7] = 5;
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18
                                                            ;
                                                          }
                                                          auVar49 = emit_const(puVar2,plVar16,8,
                                                                               uVar18);
                                                          if (auVar49._0_4_ == -1)
                                                          goto LAB_0014e4e8;
                                                          iVar12 = (int)plVar16[2];
                                                          *(int *)(plVar16 + 2) = iVar12 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014e4e8;
                                                          *puVar22 = 2;
                                                          puVar22[2] = iVar12;
                                                          puVar22[3] = 4;
                                                          *(undefined8 *)(puVar22 + 4) = 0;
                                                          puVar22[6] = iVar11;
                                                          puVar22[7] = 4;
                                                          *(undefined8 *)(puVar22 + 8) = 0;
                                                          *(undefined1 (*) [16])(puVar22 + 10) =
                                                               auVar49;
                                                          puVar22[0x12] = 2;
                                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                          local_310 = CONCAT44(local_310._4_4_,
                                                                               iVar12);
                                                          local_2d0 = CONCAT44(local_2d0._4_4_,4);
                                                        }
                                                        else {
                                                          iVar11 = strcmp(pcVar36,"xchg");
                                                          if (iVar11 == 0) {
                                                            if (-1 < (int)(uVar29 | uVar33)) {
                                                              uVar35 = -(uVar35 >> 0x1f) &
                                                                       0xfffffffc00000000 |
                                                                       uVar35 << 2;
                                                              iVar12 = (int)plVar16[2];
                                                              iVar13 = *(int *)((long)&local_320 +
                                                                               uVar35);
                                                              iVar11 = iVar12 + 1;
                                                              if (iVar13 == -1) {
                                                                *(int *)(plVar16 + 2) = iVar11;
                                                              }
                                                              else {
                                                                iVar11 = iVar12;
                                                                iVar12 = iVar13;
                                                                uVar34 = *(undefined4 *)
                                                                          ((long)&local_2e0 + uVar35
                                                                          );
                                                              }
                                                              *(int *)(plVar16 + 2) = iVar11 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        irblock_alloc_instr(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014e4e8;
                                                              uVar35 = -(uVar40 >> 0x1f) &
                                                                       0xfffffffc00000000 |
                                                                       uVar40 << 2;
                                                              puVar22[2] = iVar11;
                                                              iVar15 = (int)plVar16[2];
                                                              *puVar22 = 0;
                                                              puVar22[3] = uVar46;
                                                              iVar13 = iVar15 + 1;
                                                              iVar14 = *(int *)((long)&local_320 +
                                                                               uVar35);
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar12;
                                                              puVar22[7] = uVar34;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                              if (iVar14 == -1) {
                                                                *(int *)(plVar16 + 2) = iVar13;
                                                                uVar34 = uVar47;
                                                              }
                                                              else {
                                                                iVar13 = iVar15;
                                                                iVar15 = iVar14;
                                                                uVar34 = *(undefined4 *)
                                                                          ((long)&local_2e0 + uVar35
                                                                          );
                                                              }
                                                              *(int *)(plVar16 + 2) = iVar13 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        irblock_alloc_instr(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014e4e8;
                                                              iVar12 = (int)plVar16[2];
                                                              *puVar22 = 0;
                                                              puVar22[2] = iVar13;
                                                              puVar22[3] = uVar46;
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar15;
                                                              puVar22[7] = uVar34;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                              *(int *)(plVar16 + 2) = iVar12 + 1;
                                                              *(int *)((long)&local_320 +
                                                                      (long)(int)uVar33 * 4) =
                                                                   iVar13;
                                                              *(undefined4 *)
                                                               ((long)&local_2e0 +
                                                               (long)(int)uVar33 * 4) = uVar46;
                                                              puVar22 = (undefined4 *)
                                                                        irblock_alloc_instr(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014e4e8;
                                                              *puVar22 = 0;
                                                              puVar22[2] = iVar12;
                                                              *(undefined4 *)
                                                               ((long)&local_2e0 +
                                                               (long)(int)uVar29 * 4) = uVar47;
                                                              puVar22[3] = uVar47;
                                                              *(int *)((long)&local_320 +
                                                                      (long)(int)uVar29 * 4) =
                                                                   iVar12;
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar11;
                                                              puVar22[7] = uVar46;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                            }
                                                          }
                                                          else {
                                                            iVar11 = strcmp(pcVar36,"cdq");
                                                            iVar12 = strcmp(pcVar36,"cqo");
                                                            if (iVar11 == 0) {
                                                              uVar42 = 0x3f;
                                                              if (iVar12 != 0) {
                                                                uVar42 = 0x1f;
                                                              }
                                                              uVar46 = 4;
                                                              if (iVar12 != 0) {
                                                                uVar46 = 3;
                                                              }
                                                            }
                                                            else if (iVar12 == 0) {
                                                              uVar42 = 0x3f;
                                                              uVar46 = 4;
                                                            }
                                                            else {
                                                              iVar11 = strcmp(pcVar36,"cwd");
                                                              if (iVar11 != 0) {
                                                                if (((cVar10 != '\0') &&
                                                                    (iVar11 = strcmp(pcVar36,"hint")
                                                                    , iVar11 != 0)) &&
                                                                   ((iVar11 = strcmp(pcVar36,"pause"
                                                                                    ), iVar11 != 0
                                                                    && (((iVar11 = strcmp(pcVar36,
                                                  "endbr64"), iVar11 != 0 &&
                                                  (iVar11 = strcmp(pcVar36,"endbr32"), iVar11 != 0))
                                                  && (puVar22 = (undefined4 *)
                                                                irblock_alloc_instr(puVar2),
                                                     puVar22 != (undefined4 *)0x0)))))) {
                                                    *puVar22 = 0x1d;
                                                    puVar22[0x12] = 0;
                                                    *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                    *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                    strncpy((char *)(puVar22 + 0x1e),pcVar36,0xf);
                                                    *(undefined1 *)((long)puVar22 + 0x87) = 0;
                                                  }
                                                  goto LAB_0014dc04;
                                                  }
                                                  uVar42 = 0xf;
                                                  uVar46 = 2;
                                                  }
                                                  iVar11 = (int)local_320;
                                                  if ((int)local_320 == -1) {
                                                    iVar11 = (int)plVar16[2];
                                                    *(int *)(plVar16 + 2) = iVar11 + 1;
                                                  }
                                                  auVar49 = emit_const(puVar2,plVar16,uVar42,uVar18)
                                                  ;
                                                  if (auVar49._0_4_ == -1) goto LAB_0014e4e8;
                                                  iVar12 = (int)plVar16[2];
                                                  *(int *)(plVar16 + 2) = iVar12 + 1;
                                                  puVar22 = (undefined4 *)
                                                            irblock_alloc_instr(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014e4e8;
                                                  *puVar22 = 10;
                                                  puVar22[2] = iVar12;
                                                  puVar22[3] = uVar46;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = uVar46;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  *(undefined1 (*) [16])(puVar22 + 10) = auVar49;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  uStack_318 = CONCAT44(uStack_318._4_4_,iVar12);
                                                  uStack_2d8 = CONCAT44(uStack_2d8._4_4_,uVar46);
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    iVar12 = iVar11;
                                                    mm_lookup_part_0_isra_0
                                                              (acStack_159 + 1,&local_370);
                                                    if (iVar12 == 2) {
                                                      mm_lookup_part_0_isra_0
                                                                (acStack_159 + 0x41,&local_368);
                                                      iVar12 = local_368;
                                                      uVar38 = local_370;
                                                      if (-1 < (int)local_370) goto LAB_0014fa88;
                                                      if (local_368 < 0) goto LAB_0014f790;
                                                      iVar11 = strcmp(pcVar36,"movq");
                                                      if ((iVar11 != 0) &&
                                                         (iVar11 = strcmp(pcVar36,"movd"),
                                                         iVar11 != 0)) goto LAB_0014fe4c;
                                                      plVar6 = local_378;
                                                      if ((int)uVar33 < 0) {
                                                        iVar11 = is_mem_op_part_0(acStack_159 + 1);
                                                        if (iVar11 != 0) {
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 != (undefined4 *)0x0) {
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            uVar42 = DAT_0020a3e8;
                                                            *puVar22 = 0x16;
                                                            *(undefined8 *)(puVar22 + 2) =
                                                                 0xffffffff;
                                                            *(undefined8 *)(puVar22 + 6) = uVar42;
                                                            iVar11 = *(int *)((long)&local_340 +
                                                                             (long)iVar12 * 4);
                                                            if (iVar11 == -1) {
                                                              iVar11 = (int)local_378[2];
                                                              *(int *)(local_378 + 2) = iVar11 + 1;
                                                            }
                                                            uVar46 = 0xd;
                                                            goto LAB_001500a4;
                                                          }
                                                          goto LAB_0014e4e8;
                                                        }
                                                      }
                                                      else {
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        *puVar22 = 0;
                                                        iVar12 = *(int *)((long)&local_340 +
                                                                         (long)iVar12 * 4);
                                                        if (iVar12 == -1) {
                                                          iVar12 = (int)plVar6[2];
                                                          *(int *)(plVar6 + 2) = iVar12 + 1;
                                                        }
                                                        uVar35 = -(uVar35 >> 0x1f) &
                                                                 0xfffffffc00000000 | uVar35 << 2;
                                                        puVar22[6] = iVar12;
                                                        puVar22[7] = 0xd;
                                                        *(int *)((long)&local_320 + uVar35) = iVar11
                                                        ;
                                                        *(undefined4 *)((long)&local_2e0 + uVar35) =
                                                             uVar46;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = uVar46;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                    }
                                                    else {
                                                      if ((int)local_370 < 0) goto LAB_0014f790;
LAB_0014fa88:
                                                      uVar38 = local_370;
                                                      iVar11 = strcmp(pcVar36,"movq");
                                                      if ((iVar11 == 0) ||
                                                         (iVar11 = strcmp(pcVar36,"movd"),
                                                         iVar11 == 0)) {
                                                        plVar6 = local_378;
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        if (local_368 < 0) {
                                                          if ((int)uVar29 < 0) {
                                                            uVar47 = 5;
                                                            iVar12 = -1;
                                                            *puVar22 = 0x15;
                                                          }
                                                          else {
                                                            *puVar22 = 0;
                                                            iVar12 = *(int *)((long)&local_320 +
                                                                             (long)(int)uVar29 * 4);
                                                            if (iVar12 == -1) {
                                                              iVar12 = (int)plVar6[2];
                                                              *(int *)(plVar6 + 2) = iVar12 + 1;
                                                            }
                                                          }
                                                        }
                                                        else {
                                                          *puVar22 = 0;
                                                          iVar12 = *(int *)((long)&local_340 +
                                                                           (long)local_368 * 4);
                                                          if (iVar12 == -1) {
                                                            iVar12 = (int)plVar6[2];
                                                            *(int *)(plVar6 + 2) = iVar12 + 1;
                                                          }
                                                          uVar47 = 0xd;
                                                        }
                                                        *(int *)((long)&local_340 +
                                                                (long)(int)uVar38 * 4) = iVar11;
                                                        puVar22[6] = iVar12;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = 0xd;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        puVar22[7] = uVar47;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                      else {
LAB_0014fe4c:
                                                        iVar11 = strncmp(pcVar36,"padd",4);
                                                        if (iVar11 == 0) {
                                                          uVar46 = 2;
                                                        }
                                                        else {
                                                          iVar11 = strncmp(pcVar36,"psub",4);
                                                          if (iVar11 == 0) {
                                                            uVar46 = 3;
                                                          }
                                                          else {
                                                            iVar11 = strcmp(pcVar36,"pand");
                                                            if (iVar11 == 0) {
                                                              uVar46 = 6;
                                                            }
                                                            else {
                                                              iVar11 = strcmp(pcVar36,"por");
                                                              if (iVar11 == 0) {
                                                                uVar46 = 7;
                                                              }
                                                              else {
                                                                iVar11 = strcmp(pcVar36,"pxor");
                                                                if (iVar11 == 0) {
                                                                  uVar46 = 8;
                                                                }
                                                                else {
                                                                  iVar11 = strncmp(pcVar36,"pmul",4)
                                                                  ;
                                                                  if (iVar11 != 0)
                                                                  goto LAB_0014dc04;
                                                                  uVar46 = 4;
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                        if (-1 < (int)uVar38) {
                                                          iVar11 = (int)local_378[2];
                                                          iVar12 = *(int *)((long)&local_340 +
                                                                           (long)(int)uVar38 * 4);
                                                          iVar13 = iVar11;
                                                          if (iVar12 == -1) {
                                                            *(int *)(local_378 + 2) = iVar11 + 1;
                                                            iVar13 = iVar11 + 1;
                                                            iVar12 = iVar11;
                                                          }
                                                          if ((local_368 < 0) ||
                                                             (iVar11 = *(int *)((long)&local_340 +
                                                                               (long)local_368 * 4),
                                                             iVar15 = iVar13, iVar11 == -1)) {
                                                            *(int *)(local_378 + 2) = iVar13 + 1;
                                                            iVar15 = iVar13 + 1;
                                                            iVar11 = iVar13;
                                                          }
                                                          *(int *)(local_378 + 2) = iVar15 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 != (undefined4 *)0x0) {
                                                            uVar47 = 0xd;
                                                            *(int *)((long)&local_340 +
                                                                    (long)(int)uVar38 * 4) = iVar15;
                                                            *puVar22 = uVar46;
                                                            puVar22[2] = iVar15;
                                                            puVar22[3] = 0xd;
                                                            *(undefined8 *)(puVar22 + 4) = 0;
                                                            puVar22[6] = iVar12;
                                                            puVar22[7] = 0xd;
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            puVar22[10] = iVar11;
                                                            goto LAB_0014ff54;
                                                          }
                                                          goto LAB_0014e4e8;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    iVar12 = 8 - uVar38;
                                                    local_370 = 0xffffffff;
                                                    local_368 = -1;
                                                    xmm_lookup_isra_0(acStack_159 + 1,&local_370);
                                                    if (iVar11 == 2) {
                                                      xmm_lookup_isra_0(acStack_159 + 0x41,
                                                                        &local_368);
                                                    }
                                                    iVar15 = strncmp(pcVar36,"mov",3);
                                                    iVar13 = local_368;
                                                    uVar38 = local_370;
                                                    plVar6 = local_378;
                                                    if (iVar15 == 0) {
                                                      uVar35 = (ulong)local_370;
                                                      if ((int)local_370 < 0) {
                                                        if (-1 < local_368) {
                                                          puVar22 = (undefined4 *)
                                                                    irblock_alloc_instr(puVar2);
                                                          if (puVar22 != (undefined4 *)0x0) {
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            uVar42 = DAT_0020a3e8;
                                                            *puVar22 = 0x16;
                                                            iVar11 = *(int *)((long)&local_2a0 +
                                                                             (long)iVar13 * 4);
                                                            *(undefined8 *)(puVar22 + 2) =
                                                                 0xffffffff;
                                                            *(undefined8 *)(puVar22 + 6) = uVar42;
                                                            if (iVar11 == -1) {
                                                              iVar11 = (int)local_378[2];
                                                              *(int *)(local_378 + 2) = iVar11 + 1;
                                                            }
                                                            puVar22[10] = iVar11;
                                                            puVar22[0xb] = iVar12;
                                                            *(undefined8 *)(puVar22 + 0xc) = 0;
                                                            puVar22[0x12] = 2;
                                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18
                                                            ;
                                                            goto LAB_0014dc04;
                                                          }
                                                          goto LAB_0014e4e8;
                                                        }
                                                      }
                                                      else {
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        if (local_368 < 0) {
                                                          iVar13 = -1;
                                                          *puVar22 = 0x15;
                                                          iVar15 = 5;
                                                        }
                                                        else {
                                                          iVar13 = *(int *)((long)&local_2a0 +
                                                                           (long)local_368 * 4);
                                                          *puVar22 = 0;
                                                          iVar15 = iVar12;
                                                          if (iVar13 == -1) {
                                                            iVar13 = (int)plVar6[2];
                                                            *(int *)(plVar6 + 2) = iVar13 + 1;
                                                          }
                                                        }
                                                        uVar35 = -(ulong)(uVar38 >> 0x1f) &
                                                                 0xfffffffc00000000 | uVar35 << 2;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = iVar12;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        *(int *)((long)&local_2a0 + uVar35) = iVar11
                                                        ;
                                                        *(int *)((long)&local_260 + uVar35) = iVar12
                                                        ;
                                                        puVar22[6] = iVar13;
                                                        puVar22[7] = iVar15;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                    }
                                                    else {
                                                      iVar13 = strncmp(pcVar36,"add",3);
                                                      if (iVar13 == 0) {
                                                        uVar46 = 2;
                                                      }
                                                      else {
                                                        iVar13 = strncmp(pcVar36,"sub",3);
                                                        if (iVar13 == 0) {
                                                          uVar46 = 3;
                                                        }
                                                        else {
                                                          iVar13 = strncmp(pcVar36,"mul",3);
                                                          if (iVar13 == 0) {
                                                            uVar46 = 4;
                                                          }
                                                          else {
                                                            iVar13 = strncmp(pcVar36,"div",3);
                                                            if (iVar13 != 0) {
                                                              cVar10 = *(char *)(lVar31 + 0x20);
                                                              goto LAB_0014f774;
                                                            }
                                                            uVar46 = 5;
                                                          }
                                                        }
                                                      }
                                                      if (-1 < (int)local_370) {
                                                        lVar31 = (long)(int)local_370;
                                                        iVar13 = *(int *)((long)&local_2a0 +
                                                                         (long)(int)local_370 * 4);
                                                        iVar11 = (int)local_378[2];
                                                        if (iVar13 == -1) {
                                                          *(int *)(local_378 + 2) = iVar11 + 1;
                                                          iVar13 = iVar11;
                                                          iVar11 = iVar11 + 1;
                                                        }
                                                        if ((local_368 < 0) ||
                                                           (iVar15 = *(int *)((long)&local_2a0 +
                                                                             (long)local_368 * 4),
                                                           iVar14 = iVar11, iVar15 == -1)) {
                                                          *(int *)(local_378 + 2) = iVar11 + 1;
                                                          iVar14 = iVar11 + 1;
                                                          iVar15 = iVar11;
                                                        }
                                                        *(int *)(local_378 + 2) = iVar14 + 1;
                                                        puVar22 = (undefined4 *)
                                                                  irblock_alloc_instr(puVar2);
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014e4e8;
                                                        *puVar22 = uVar46;
                                                        *(int *)((long)&local_2a0 + lVar31 * 4) =
                                                             iVar14;
                                                        *(int *)((long)&local_260 + lVar31 * 4) =
                                                             iVar12;
                                                        puVar22[2] = iVar14;
                                                        puVar22[3] = iVar12;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        puVar22[6] = iVar13;
                                                        puVar22[7] = iVar12;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[10] = iVar15;
                                                        puVar22[0xb] = iVar12;
                                                        *(undefined8 *)(puVar22 + 0xc) = 0;
                                                        puVar22[0x12] = 2;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                              goto LAB_0014dc04;
                                            }
                                            puVar22 = (undefined4 *)irblock_alloc_instr(puVar2);
                                            if (puVar22 == (undefined4 *)0x0) goto LAB_0014e4e8;
                                            *puVar22 = 0x18;
                                            puVar22[0x12] = 0;
                                            *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          else {
            pcVar27 = (char *)(lVar31 + 0x60);
            iVar11 = 0;
            pcVar19 = pcVar27;
            do {
              while (cVar10 == '[') {
                pcVar19 = pcVar19 + 1;
                cVar10 = *pcVar19;
                iVar11 = iVar11 + 1;
                if (cVar10 == '\0') goto LAB_0014dee8;
              }
              if (cVar10 == ']') {
                iVar11 = iVar11 + -1;
              }
              else if (cVar10 == ',' && iVar11 == 0) {
                sVar25 = (long)pcVar19 - (long)pcVar27;
                if (0x3f < sVar25) {
                  sVar25 = 0x3f;
                }
                memcpy(acStack_159 + 1,pcVar27,sVar25);
                (acStack_159 + 1)[sVar25] = '\0';
                snprintf(acStack_159 + 0x41,0x40,"%s",pcVar19 + 1);
                iVar11 = 2;
                cVar10 = acStack_159[1];
                cVar32 = acStack_159[0x41];
                goto joined_r0x0014e174;
              }
              pcVar19 = pcVar19 + 1;
              cVar10 = *pcVar19;
            } while (cVar10 != '\0');
LAB_0014dee8:
            snprintf(acStack_159 + 1,0x40,"%s",pcVar27);
            iVar11 = 1;
            cVar10 = acStack_159[1];
            cVar32 = acStack_159[0x41];
joined_r0x0014e174:
            acStack_159[1] = cVar10;
            acStack_159[0x41] = cVar32;
            if (cVar10 == '\0') {
LAB_0014df18:
              if (cVar32 == '\0') goto LAB_0014e470;
LAB_0014df1c:
              pcVar27 = acStack_159 + 0x41;
              sVar25 = strlen(pcVar27);
              pcVar19 = pcVar27 + (sVar25 - 1);
              if (pcVar27 < pcVar27 + (sVar25 - 1)) {
                do {
                  cVar32 = acStack_159[0x41];
                  if (*pcVar19 != ' ') break;
                  pcVar21 = pcVar19 + -1;
                  *pcVar19 = '\0';
                  pcVar19 = pcVar21;
                } while (pcVar21 != pcVar27);
              }
              pcVar19 = pcVar27;
              if (cVar32 == ' ') {
                do {
                  pcVar19 = pcVar19 + 1;
                } while (*pcVar19 == ' ');
                if (pcVar19 != pcVar27) {
                  sVar25 = strlen(pcVar19);
                  __memmove_chk(pcVar27,pcVar19,sVar25 + 1,0x40);
                }
              }
              if (cVar10 != ' ') goto LAB_0014e470;
LAB_0014dfb0:
              pcVar27 = acStack_159 + 1;
              do {
                pcVar27 = pcVar27 + 1;
              } while (*pcVar27 == ' ');
            }
            else {
              pcVar19 = acStack_159 + 1;
              sVar25 = strlen(pcVar19);
              pcVar27 = pcVar19 + (sVar25 - 1);
              if (pcVar19 < pcVar19 + (sVar25 - 1)) {
                do {
                  cVar10 = acStack_159[1];
                  if (*pcVar27 != ' ') break;
                  pcVar21 = pcVar27 + -1;
                  *pcVar27 = '\0';
                  pcVar27 = pcVar21;
                  cVar10 = acStack_159[1];
                } while (pcVar21 != pcVar19);
              }
              pcVar27 = pcVar19;
              if (cVar10 != ' ') goto LAB_0014df18;
              do {
                pcVar27 = pcVar27 + 1;
              } while (*pcVar27 == ' ');
              if (pcVar27 == pcVar19) {
                if (cVar32 != '\0') goto LAB_0014df1c;
                goto LAB_0014dfb0;
              }
              sVar25 = strlen(pcVar27);
              __memmove_chk(pcVar19,pcVar27,sVar25 + 1,0x40);
              cVar10 = acStack_159[1];
              if (cVar32 != '\0') goto LAB_0014df1c;
              if (acStack_159[1] == ' ') goto LAB_0014dfb0;
LAB_0014e470:
              pcVar27 = acStack_159 + 1;
            }
            ppuVar45 = &REG_TABLE;
            iVar12 = 0;
            ppuVar44 = ppuVar45;
            do {
              iVar13 = strcmp(*ppuVar44,pcVar27);
              cVar10 = acStack_159[0x41];
              if (iVar13 == 0) {
                uVar35 = (ulong)(uint)(&DAT_005df910)[(long)iVar12 * 4];
                uVar46 = (&DAT_005df914)[(long)iVar12 * 4];
                goto LAB_0014e00c;
              }
              iVar12 = iVar12 + 1;
              ppuVar44 = ppuVar44 + 2;
            } while (iVar12 != 0x30);
            uVar46 = 4;
            uVar35 = 0xffffffff;
LAB_0014e00c:
            if (iVar11 == 2) {
              pcVar19 = acStack_159 + 0x41;
              pcVar27 = pcVar19;
              cVar32 = acStack_159[0x41];
              while (cVar32 == ' ') {
                pcVar27 = pcVar27 + 1;
                cVar32 = *pcVar27;
              }
              iVar12 = 0;
              do {
                iVar13 = strcmp(*ppuVar45,pcVar27);
                iVar11 = 2;
                if (iVar13 == 0) {
                  local_3f8 = 0;
                  uVar40 = (ulong)(uint)(&DAT_005df910)[(long)iVar12 * 4];
                  uVar47 = (&DAT_005df914)[(long)iVar12 * 4];
                  bVar7 = false;
                  goto LAB_0014e094;
                }
                iVar12 = iVar12 + 1;
                ppuVar45 = ppuVar45 + 2;
              } while (iVar12 != 0x30);
              while (cVar10 == ' ') {
                pcVar19 = pcVar19 + 1;
                cVar10 = *pcVar19;
              }
              iVar12 = __isoc99_sscanf(pcVar19,"0x%lx",&local_370);
              if (iVar12 == 1) {
                local_3f8 = CONCAT44(uStack_36c,local_370);
                bVar7 = true;
              }
              else {
                iVar12 = __isoc99_sscanf(pcVar19,&DAT_001f84c8,&local_368);
                if (iVar12 == 1) {
                  local_3f8 = CONCAT44(uStack_364,local_368);
                  bVar7 = true;
                }
                else {
                  bVar7 = false;
                  local_3f8 = 0;
                }
              }
              uVar47 = 4;
              uVar40 = 0xffffffff;
            }
            else {
              uVar47 = 4;
              uVar40 = 0xffffffff;
              bVar7 = false;
              local_3f8 = 0;
              iVar11 = 1;
            }
LAB_0014e094:
            iVar12 = strcmp(pcVar36,"mov");
            if (iVar12 != 0) goto LAB_0014dac4;
            uVar33 = (uint)uVar35;
            plVar6 = local_378;
joined_r0x0014e0a8:
            iVar11 = (int)uVar40;
            local_378 = plVar6;
            if (-1 < (int)uVar33) {
              uVar33 = *(uint *)(puVar2 + 2);
              uVar29 = *(uint *)((long)puVar2 + 0x14);
              iVar12 = (int)plVar6[2];
              pvVar17 = (void *)puVar2[1];
              *(int *)(plVar6 + 2) = iVar12 + 1;
              if (uVar29 <= uVar33) {
                if (uVar29 == 0) {
                  sVar25 = 0x880;
                  uVar29 = 0x10;
                }
                else {
                  uVar29 = uVar29 << 1;
                  sVar25 = (ulong)uVar29 * 0x88;
                }
                pvVar17 = realloc(pvVar17,sVar25);
                if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                uVar33 = *(uint *)(puVar2 + 2);
                puVar2[1] = pvVar17;
                *(uint *)((long)puVar2 + 0x14) = uVar29;
              }
              *(uint *)(puVar2 + 2) = uVar33 + 1;
              puVar43 = (undefined8 *)((long)pvVar17 + (ulong)uVar33 * 0x88);
              pcVar27 = acStack_159 + 0x41;
              puVar43[1] = 0;
              *puVar43 = 0;
              puVar43[3] = 0;
              puVar43[2] = 0;
              *(int *)(puVar43 + 1) = iVar12;
              *(undefined4 *)((long)puVar43 + 0xc) = uVar46;
              puVar43[5] = 0;
              puVar43[4] = 0;
              puVar43[7] = 0;
              puVar43[6] = 0;
              puVar43[9] = 0;
              puVar43[8] = 0;
              puVar43[0xb] = 0;
              puVar43[10] = 0;
              puVar43[0xd] = 0;
              puVar43[0xc] = 0;
              puVar43[0xf] = 0;
              puVar43[0xe] = 0;
              puVar43[0x10] = 0;
              cVar10 = acStack_159[0x41];
              while (cVar10 == ' ') {
                pcVar27 = pcVar27 + 1;
                cVar10 = *pcVar27;
              }
              if ((((cVar10 == '[') || (pcVar19 = strstr(pcVar27,"ptr"), pcVar19 != (char *)0x0)) ||
                  (pcVar27 = strchr(pcVar27,0x5b), pcVar27 != (char *)0x0)) &&
                 (iVar13 = strcmp(pcVar36,"lea"), iVar13 != 0)) {
                *(undefined4 *)puVar43 = 0x15;
                uVar42 = DAT_0020a3e8;
                *(undefined4 *)(puVar43 + 9) = 1;
                puVar43[3] = uVar42;
              }
              else if (iVar11 < 0) {
                if (bVar7) {
                  *(undefined4 *)puVar43 = 1;
                  puVar43[2] = local_3f8;
                }
                else {
                  *(undefined4 *)puVar43 = 1;
                }
              }
              else {
                iVar11 = *(int *)((long)&local_320 + (long)iVar11 * 4);
                if (iVar11 == -1) {
                  iVar11 = (int)plVar6[2];
                  *(int *)(plVar6 + 2) = iVar11 + 1;
                }
                *(int *)(puVar43 + 3) = iVar11;
                *(undefined4 *)((long)puVar43 + 0x1c) = uVar47;
                puVar43[4] = 0;
                *(undefined4 *)(puVar43 + 9) = 1;
              }
              puVar43[0xe] = uVar18;
              *(int *)((long)&local_320 + (long)(int)uVar35 * 4) = iVar12;
              *(undefined4 *)((long)&local_2e0 + (long)(int)uVar35 * 4) = uVar46;
              goto LAB_0014dc04;
            }
            pcVar36 = acStack_159 + 1;
            cVar10 = acStack_159[1];
            while (cVar10 == ' ') {
              pcVar36 = pcVar36 + 1;
              cVar10 = *pcVar36;
            }
            if (cVar10 != '[') goto LAB_0014dd60;
LAB_0014dd74:
            uVar33 = *(uint *)(puVar2 + 2);
            uVar29 = *(uint *)((long)puVar2 + 0x14);
            pvVar17 = (void *)puVar2[1];
            if (uVar29 <= uVar33) {
              if (uVar29 == 0) {
                sVar25 = 0x880;
                uVar29 = 0x10;
              }
              else {
                uVar29 = uVar29 << 1;
                sVar25 = (ulong)uVar29 * 0x88;
              }
              pvVar17 = realloc(pvVar17,sVar25);
              if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
              uVar33 = *(uint *)(puVar2 + 2);
              puVar2[1] = pvVar17;
              *(uint *)((long)puVar2 + 0x14) = uVar29;
            }
            *(uint *)(puVar2 + 2) = uVar33 + 1;
            puVar43 = (undefined8 *)((long)pvVar17 + (ulong)uVar33 * 0x88);
            *(undefined4 *)((long)puVar43 + 0x84) = 0;
            *(undefined8 *)((long)puVar43 + 0xc) = 0;
            *(undefined8 *)((long)puVar43 + 4) = 0;
            *(undefined8 *)((long)puVar43 + 0x1c) = 0;
            *(undefined8 *)((long)puVar43 + 0x14) = 0;
            *(undefined8 *)((long)puVar43 + 0x2c) = 0;
            *(undefined8 *)((long)puVar43 + 0x24) = 0;
            *(undefined8 *)((long)puVar43 + 0x3c) = 0;
            *(undefined8 *)((long)puVar43 + 0x34) = 0;
            *(undefined8 *)((long)puVar43 + 0x4c) = 0;
            *(undefined8 *)((long)puVar43 + 0x44) = 0;
            *(undefined8 *)((long)puVar43 + 0x5c) = 0;
            *(undefined8 *)((long)puVar43 + 0x54) = 0;
            *(undefined8 *)((long)puVar43 + 0x6c) = 0;
            *(undefined8 *)((long)puVar43 + 100) = 0;
            *(undefined8 *)((long)puVar43 + 0x7c) = 0;
            *(undefined8 *)((long)puVar43 + 0x74) = 0;
            *(undefined4 *)((long)pvVar17 + (ulong)uVar33 * 0x88) = 0x16;
            *(undefined4 *)(puVar43 + 1) = 0xffffffff;
            puVar43[3] = uVar9;
            if ((iVar11 < 0) ||
               (iVar11 = *(int *)((long)&local_320 + (long)iVar11 * 4), iVar11 == -1)) {
              if (bVar7) {
                auVar49 = emit_const(puVar2,local_378,local_3f8,uVar18);
                if (auVar49._0_4_ == -1) goto LAB_0014e4e8;
                uVar33 = *(uint *)(puVar2 + 2);
                uVar29 = *(uint *)((long)puVar2 + 0x14);
                pvVar17 = (void *)puVar2[1];
                if (uVar29 <= uVar33) {
                  if (uVar29 == 0) {
                    sVar25 = 0x880;
                    uVar29 = 0x10;
                  }
                  else {
                    uVar29 = uVar29 << 1;
                    sVar25 = (ulong)uVar29 * 0x88;
                  }
                  pvVar17 = realloc(pvVar17,sVar25);
                  if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
                  uVar33 = *(uint *)(puVar2 + 2);
                  puVar2[1] = pvVar17;
                  *(uint *)((long)puVar2 + 0x14) = uVar29;
                }
                *(uint *)(puVar2 + 2) = uVar33 + 1;
                uVar42 = DAT_0020a3e8;
                puVar43 = (undefined8 *)((long)pvVar17 + (ulong)uVar33 * 0x88);
                puVar43[1] = 0;
                *puVar43 = 0;
                puVar43[3] = 0;
                puVar43[2] = 0;
                puVar43[5] = 0;
                puVar43[4] = 0;
                puVar43[7] = 0;
                puVar43[6] = 0;
                puVar43[9] = 0;
                puVar43[8] = 0;
                puVar43[0xb] = 0;
                puVar43[10] = 0;
                puVar43[0xd] = 0;
                puVar43[0xc] = 0;
                puVar43[0xf] = 0;
                puVar43[0xe] = 0;
                puVar43[0x10] = 0;
                *(undefined4 *)((long)pvVar17 + (ulong)uVar33 * 0x88) = 0x16;
                *(undefined4 *)(puVar43 + 1) = 0xffffffff;
                puVar43[3] = uVar42;
                *(undefined1 (*) [16])(puVar43 + 5) = auVar49;
                *(undefined4 *)(puVar43 + 9) = 2;
              }
              else {
                *(undefined4 *)(puVar43 + 9) = 1;
              }
            }
            else {
              *(int *)(puVar43 + 5) = iVar11;
              *(undefined4 *)((long)puVar43 + 0x2c) = uVar47;
            }
            puVar43[0xe] = uVar18;
          }
LAB_0014dc04:
          lVar30 = lVar30 + 1;
          if (*(uint *)(lVar1 + 0x18) <= (uint)lVar30) goto LAB_0014dc1c;
          goto LAB_0014da60;
        }
LAB_0014dc1c:
        lVar39 = lVar39 + 1;
      } while ((uint)lVar39 < *(uint *)(param_1 + 1));
    }
    uVar29 = *(uint *)(param_1 + 3);
    lVar39 = 0;
    uVar33 = 0;
    if (uVar29 != 0) {
      do {
        uVar38 = *(uint *)(param_1[2] + lVar39 + 4);
        if (uVar38 != 0xffffffff) {
          uVar4 = *(uint *)(param_1[2] + lVar39);
          uVar5 = uVar38;
          if (uVar38 < uVar4) {
            uVar5 = uVar4;
          }
          if (uVar5 < *(uint *)(plVar16 + 1)) {
            lVar41 = *plVar16;
            lVar31 = (ulong)uVar38 * 0x48;
            lVar1 = lVar41 + (ulong)uVar4 * 0x48;
            lVar30 = lVar41 + lVar31;
            uVar38 = *(uint *)(lVar1 + 0x30);
            piVar20 = *(int **)(lVar1 + 0x28);
            if (uVar38 == 0) {
              sVar25 = 4;
            }
            else {
              piVar26 = piVar20;
              do {
                if (*piVar26 == *(int *)(lVar41 + lVar31)) goto LAB_0014dc70;
                piVar26 = piVar26 + 1;
              } while (piVar20 + uVar38 != piVar26);
              sVar25 = (ulong)(uVar38 + 1) << 2;
            }
            pvVar17 = realloc(piVar20,sVar25);
            if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
            uVar29 = *(uint *)(lVar1 + 0x30);
            uVar46 = *(undefined4 *)(lVar41 + lVar31);
            *(void **)(lVar1 + 0x28) = pvVar17;
            *(uint *)(lVar1 + 0x30) = uVar29 + 1;
            *(undefined4 *)((long)pvVar17 + (ulong)uVar29 * 4) = uVar46;
            pvVar17 = realloc(*(void **)(lVar30 + 0x18),(ulong)(*(int *)(lVar30 + 0x20) + 1) << 2);
            if (pvVar17 == (void *)0x0) goto LAB_0014e4e8;
            uVar29 = *(uint *)(lVar30 + 0x20);
            uVar46 = *(undefined4 *)(lVar41 + (ulong)uVar4 * 0x48);
            *(void **)(lVar30 + 0x18) = pvVar17;
            *(uint *)(lVar30 + 0x20) = uVar29 + 1;
            *(undefined4 *)((long)pvVar17 + (ulong)uVar29 * 4) = uVar46;
            uVar29 = *(uint *)(param_1 + 3);
          }
        }
LAB_0014dc70:
        uVar33 = uVar33 + 1;
        lVar39 = lVar39 + 0xc;
      } while (uVar33 < uVar29);
    }
    goto LAB_0014e51c;
  }
LAB_0014e518:
  plVar16 = (long *)0x0;
LAB_0014e51c:
  if (local_98 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return plVar16;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_98 - *(long *)PTR___stack_chk_guard_005ffe88);
LAB_0014e4e8:
  ir_func_destroy(&local_378);
  goto LAB_0014e518;
}

