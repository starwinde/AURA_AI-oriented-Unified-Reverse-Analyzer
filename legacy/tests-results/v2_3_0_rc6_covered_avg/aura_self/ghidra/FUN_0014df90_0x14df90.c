
long * FUN_0014df90(long *param_1,undefined8 param_2,char *param_3,long param_4)

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
  int iVar15;
  int iVar12;
  int iVar13;
  int iVar14;
  long *plVar16;
  void *pvVar17;
  undefined8 uVar18;
  char *pcVar19;
  char *pcVar20;
  int *piVar21;
  undefined4 *puVar22;
  ulonglong uVar23;
  undefined4 *puVar24;
  size_t sVar25;
  ulong uVar26;
  int *piVar27;
  int *extraout_x1;
  char *pcVar28;
  undefined4 uVar29;
  uint uVar30;
  long lVar31;
  long lVar32;
  int iVar33;
  char *pcVar34;
  char cVar35;
  uint uVar36;
  undefined4 uVar37;
  ulong uVar38;
  uint uVar39;
  long lVar40;
  ulong uVar41;
  undefined8 uVar42;
  long lVar43;
  undefined8 *puVar44;
  undefined **ppuVar45;
  undefined **ppuVar46;
  undefined4 uVar47;
  undefined4 uVar48;
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
  undefined8 local_308;
  undefined8 local_300;
  undefined8 uStack_2f8;
  undefined8 local_2f0;
  undefined8 local_2e8;
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
    uVar9 = DAT_0020c568;
    uVar8 = DAT_0020c560;
    lVar40 = 0;
    if ((int)param_1[1] != 0) {
LAB_0014e074:
      uVar36 = *(uint *)(plVar16 + 1);
      uVar30 = *(uint *)((long)plVar16 + 0xc);
      pvVar17 = (void *)*plVar16;
      lVar1 = *param_1 + lVar40 * 0x20;
      if (uVar30 <= uVar36) {
        if (uVar30 == 0) {
          sVar25 = 0x280;
          uVar30 = 8;
        }
        else {
          uVar30 = uVar30 << 1;
          sVar25 = (ulong)uVar30 * 0x50;
        }
        pvVar17 = realloc(pvVar17,sVar25);
        if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
        uVar36 = *(uint *)(plVar16 + 1);
        *plVar16 = (long)pvVar17;
        *(uint *)((long)plVar16 + 0xc) = uVar30;
      }
      puVar2 = (undefined8 *)((long)pvVar17 + (ulong)uVar36 * 0x50);
      uStack_358 = 0xffffffffffffffff;
      local_360 = 0xffffffffffffffff;
      uStack_348 = 0xffffffffffffffff;
      uStack_350 = 0xffffffffffffffff;
      puVar2[1] = 0;
      *puVar2 = 0;
      puVar2[3] = 0;
      puVar2[2] = 0;
      puVar2[5] = 0;
      puVar2[4] = 0;
      puVar2[7] = 0;
      puVar2[6] = 0;
      puVar2[9] = 0;
      puVar2[8] = 0;
      iVar11 = (int)plVar16[1];
      uStack_318 = 0xffffffffffffffff;
      local_320 = 0xffffffffffffffff;
      local_308 = 0xffffffffffffffff;
      local_310 = 0xffffffffffffffff;
      *(int *)(plVar16 + 1) = iVar11 + 1;
      *(int *)((long)pvVar17 + (ulong)uVar36 * 0x50) = iVar11;
      *(int *)((long)puVar2 + 0x34) = iVar11;
      uStack_2f8 = 0xffffffffffffffff;
      local_300 = 0xffffffffffffffff;
      local_2e8 = 0xffffffffffffffff;
      local_2f0 = 0xffffffffffffffff;
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
        lVar31 = 0;
        auVar50._8_8_ = 0;
        auVar50._0_8_ = uVar8;
        local_3d0 = -1;
        local_3cc = -1;
        uVar26 = uVar8;
LAB_0014e168:
        local_3d8 = auVar50._8_8_;
        lVar32 = *(long *)(lVar1 + 0x10) + lVar31 * 0xe0;
        pcVar34 = (char *)(lVar32 + 0x20);
        uVar18 = *(undefined8 *)(*(long *)(lVar1 + 0x10) + lVar31 * 0xe0);
        cVar10 = *(char *)(lVar32 + 0x60);
        acStack_159[1] = '\0';
        acStack_159[0x41] = '\0';
        if (cVar10 == '\0') {
          iVar11 = strcmp(pcVar34,"mov");
          if (iVar11 == 0) {
            uVar48 = 4;
            pcVar34 = acStack_159 + 1;
            iVar11 = -1;
            local_3f8 = 0;
            bVar7 = false;
LAB_0014e46c:
            pcVar28 = strstr(pcVar34,"ptr");
            if ((pcVar28 == (char *)0x0) && (pcVar34 = strchr(pcVar34,0x5b), pcVar34 == (char *)0x0)
               ) goto LAB_0014e30c;
            goto LAB_0014e480;
          }
          uVar48 = 4;
          uVar41 = 0xffffffff;
          uVar38 = 0xffffffff;
          bVar7 = false;
          local_3f8 = 0;
          iVar11 = 0;
          uVar47 = 4;
LAB_0014e1cc:
          iVar12 = strcmp(pcVar34,"movzx");
          uVar36 = (uint)uVar38;
          plVar6 = local_378;
          if ((((iVar12 == 0) || (iVar12 = strcmp(pcVar34,"movsx"), plVar6 = local_378, iVar12 == 0)
               ) || (iVar12 = strcmp(pcVar34,"movsxd"), plVar6 = local_378, iVar12 == 0)) ||
             (iVar12 = strcmp(pcVar34,"lea"), plVar6 = local_378, iVar12 == 0))
          goto joined_r0x0014e7b8;
          iVar12 = strcmp(pcVar34,"add");
          plVar6 = local_378;
          uVar30 = (uint)uVar41;
          uVar37 = uVar47;
          if (iVar12 == 0) {
            if (-1 < (int)uVar36) {
              lVar32 = (long)(int)uVar36;
              iVar11 = *(int *)((long)&local_320 + lVar32 * 4);
              if (iVar11 == -1) {
                iVar11 = (int)local_378[2];
                *(int *)(local_378 + 2) = iVar11 + 1;
              }
              else {
                uVar37 = *(undefined4 *)((long)&local_2e0 + lVar32 * 4);
              }
              if ((int)uVar30 < 0) {
                if (bVar7) {
                  auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                  uVar42 = auVar49._8_8_;
                  iVar12 = auVar49._0_4_;
                  uVar48 = auVar49._4_4_;
                  if (iVar12 == -1) goto LAB_0014ebf8;
                  iVar13 = (int)plVar6[2];
                }
                else {
                  iVar12 = (int)local_378[2];
                  uVar48 = 4;
                  uVar42 = 0;
                  iVar13 = iVar12 + 1;
                }
              }
              else {
                iVar12 = (int)local_378[2];
                iVar15 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4);
                if (iVar15 == -1) {
                  uVar42 = 0;
                  iVar13 = iVar12 + 1;
                }
                else {
                  uVar42 = 0;
                  uVar48 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar30 * 4);
                  iVar13 = iVar12;
                  iVar12 = iVar15;
                }
              }
              uVar36 = *(uint *)(puVar2 + 2);
              uVar30 = *(uint *)((long)puVar2 + 0x14);
              *(int *)(plVar6 + 2) = iVar13 + 1;
              pvVar17 = (void *)puVar2[1];
              if (uVar30 <= uVar36) {
                if (uVar30 == 0) {
                  sVar25 = 0x900;
                  uVar30 = 0x10;
                }
                else {
                  uVar30 = uVar30 << 1;
                  sVar25 = (ulong)uVar30 * 0x90;
                }
                pvVar17 = realloc(pvVar17,sVar25);
                if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                puVar2[1] = pvVar17;
                uVar36 = *(uint *)(puVar2 + 2);
                *(uint *)((long)puVar2 + 0x14) = uVar30;
              }
              *(int *)((long)&local_320 + lVar32 * 4) = iVar13;
              *(uint *)(puVar2 + 2) = uVar36 + 1;
              puVar44 = (undefined8 *)((long)pvVar17 + (ulong)uVar36 * 0x90);
              *(undefined4 *)((long)&local_2e0 + lVar32 * 4) = uVar47;
              puVar44[1] = 0;
              *puVar44 = 0;
              puVar44[3] = 0;
              puVar44[2] = 0;
              puVar44[5] = 0;
              puVar44[4] = 0;
              puVar44[7] = 0;
              puVar44[6] = 0;
              puVar44[9] = 0;
              puVar44[8] = 0;
              puVar44[0xb] = 0;
              puVar44[10] = 0;
              puVar44[0xd] = 0;
              puVar44[0xc] = 0;
              puVar44[0xf] = 0;
              puVar44[0xe] = 0;
              puVar44[0x11] = 0;
              puVar44[0x10] = 0;
              *(undefined4 *)((long)pvVar17 + (ulong)uVar36 * 0x90) = 2;
LAB_0014eb18:
              *(int *)(puVar44 + 3) = iVar11;
              *(undefined4 *)((long)puVar44 + 0x1c) = uVar37;
              *(int *)(puVar44 + 1) = iVar13;
              *(undefined4 *)((long)puVar44 + 0xc) = uVar47;
              *(int *)(puVar44 + 5) = iVar12;
              *(undefined4 *)((long)puVar44 + 0x2c) = uVar48;
              puVar44[6] = uVar42;
              *(undefined4 *)(puVar44 + 9) = 2;
              puVar44[0xe] = uVar18;
            }
          }
          else {
            iVar12 = strcmp(pcVar34,"sub");
            plVar6 = local_378;
            if (iVar12 == 0) {
              if (-1 < (int)uVar36) {
                lVar32 = (long)(int)uVar36;
                iVar11 = *(int *)((long)&local_320 + lVar32 * 4);
                if (iVar11 == -1) {
                  iVar11 = (int)local_378[2];
                  *(int *)(local_378 + 2) = iVar11 + 1;
                }
                else {
                  uVar37 = *(undefined4 *)((long)&local_2e0 + lVar32 * 4);
                }
                if ((int)uVar30 < 0) {
                  if (bVar7) {
                    auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                    uVar42 = auVar49._8_8_;
                    iVar12 = auVar49._0_4_;
                    uVar48 = auVar49._4_4_;
                    if (iVar12 == -1) goto LAB_0014ebf8;
                    iVar13 = (int)plVar6[2];
                  }
                  else {
                    iVar12 = (int)local_378[2];
                    uVar48 = 4;
                    uVar42 = 0;
                    iVar13 = iVar12 + 1;
                  }
                }
                else {
                  iVar12 = (int)local_378[2];
                  iVar15 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4);
                  if (iVar15 == -1) {
                    uVar42 = 0;
                    iVar13 = iVar12 + 1;
                  }
                  else {
                    uVar42 = 0;
                    uVar48 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar30 * 4);
                    iVar13 = iVar12;
                    iVar12 = iVar15;
                  }
                }
                uVar30 = *(uint *)(puVar2 + 2);
                uVar39 = *(uint *)((long)puVar2 + 0x14);
                *(int *)(plVar6 + 2) = iVar13 + 1;
                pvVar17 = (void *)puVar2[1];
                if (uVar39 <= uVar30) {
                  if (uVar39 == 0) {
                    sVar25 = 0x900;
                    uVar39 = 0x10;
                  }
                  else {
                    uVar39 = uVar39 << 1;
                    sVar25 = (ulong)uVar39 * 0x90;
                  }
                  pvVar17 = realloc(pvVar17,sVar25);
                  if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                  puVar2[1] = pvVar17;
                  uVar30 = *(uint *)(puVar2 + 2);
                  *(uint *)((long)puVar2 + 0x14) = uVar39;
                }
                uVar29 = 3;
                *(int *)((long)&local_320 + lVar32 * 4) = iVar13;
                lVar32 = (ulong)uVar30 * 0x90;
                *(uint *)(puVar2 + 2) = uVar30 + 1;
LAB_0014ee20:
                puVar44 = (undefined8 *)((long)pvVar17 + lVar32);
                *(undefined4 *)((long)&local_2e0 + (long)(int)uVar36 * 4) = uVar47;
                puVar44[1] = 0;
                *puVar44 = 0;
                puVar44[3] = 0;
                puVar44[2] = 0;
                puVar44[5] = 0;
                puVar44[4] = 0;
                puVar44[7] = 0;
                puVar44[6] = 0;
                puVar44[9] = 0;
                puVar44[8] = 0;
                puVar44[0xb] = 0;
                puVar44[10] = 0;
                puVar44[0xd] = 0;
                puVar44[0xc] = 0;
                puVar44[0xf] = 0;
                puVar44[0xe] = 0;
                puVar44[0x11] = 0;
                puVar44[0x10] = 0;
                *(undefined4 *)((long)pvVar17 + lVar32) = uVar29;
                goto LAB_0014eb18;
              }
            }
            else {
              iVar12 = strcmp(pcVar34,"imul");
              if ((iVar12 == 0) || (iVar12 = strcmp(pcVar34,"mul"), iVar12 == 0)) {
                plVar6 = local_378;
                if (-1 < (int)uVar36) {
                  lVar32 = (long)(int)uVar36;
                  iVar11 = *(int *)((long)&local_320 + lVar32 * 4);
                  if (iVar11 == -1) {
                    iVar11 = (int)local_378[2];
                    *(int *)(local_378 + 2) = iVar11 + 1;
                  }
                  else {
                    uVar37 = *(undefined4 *)((long)&local_2e0 + lVar32 * 4);
                  }
                  if ((int)uVar30 < 0) {
                    if (bVar7) {
                      auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                      uVar42 = auVar49._8_8_;
                      iVar12 = auVar49._0_4_;
                      uVar48 = auVar49._4_4_;
                      if (iVar12 == -1) goto LAB_0014ebf8;
                      iVar13 = (int)plVar6[2];
                    }
                    else {
                      iVar12 = (int)local_378[2];
                      uVar48 = 4;
                      uVar42 = 0;
                      iVar13 = iVar12 + 1;
                    }
                  }
                  else {
                    iVar12 = (int)local_378[2];
                    iVar15 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4);
                    if (iVar15 == -1) {
                      uVar42 = 0;
                      iVar13 = iVar12 + 1;
                    }
                    else {
                      uVar42 = 0;
                      uVar48 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar30 * 4);
                      iVar13 = iVar12;
                      iVar12 = iVar15;
                    }
                  }
                  uVar30 = *(uint *)(puVar2 + 2);
                  uVar39 = *(uint *)((long)puVar2 + 0x14);
                  *(int *)(plVar6 + 2) = iVar13 + 1;
                  pvVar17 = (void *)puVar2[1];
                  if (uVar39 <= uVar30) {
                    if (uVar39 == 0) {
                      sVar25 = 0x900;
                      uVar39 = 0x10;
                    }
                    else {
                      uVar39 = uVar39 << 1;
                      sVar25 = (ulong)uVar39 * 0x90;
                    }
                    pvVar17 = realloc(pvVar17,sVar25);
                    if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                    puVar2[1] = pvVar17;
                    uVar30 = *(uint *)(puVar2 + 2);
                    *(uint *)((long)puVar2 + 0x14) = uVar39;
                  }
                  uVar29 = 4;
                  *(int *)((long)&local_320 + lVar32 * 4) = iVar13;
                  lVar32 = (ulong)uVar30 * 0x90;
                  *(uint *)(puVar2 + 2) = uVar30 + 1;
                  goto LAB_0014ee20;
                }
              }
              else {
                iVar12 = strcmp(pcVar34,"and");
                plVar6 = local_378;
                if (iVar12 == 0) {
                  if (-1 < (int)uVar36) {
                    lVar32 = (long)(int)uVar36;
                    iVar11 = *(int *)((long)&local_320 + lVar32 * 4);
                    if (iVar11 == -1) {
                      iVar11 = (int)local_378[2];
                      *(int *)(local_378 + 2) = iVar11 + 1;
                    }
                    else {
                      uVar37 = *(undefined4 *)((long)&local_2e0 + lVar32 * 4);
                    }
                    if ((int)uVar30 < 0) {
                      if (bVar7) {
                        auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                        uVar42 = auVar49._8_8_;
                        iVar12 = auVar49._0_4_;
                        uVar48 = auVar49._4_4_;
                        if (iVar12 == -1) goto LAB_0014ebf8;
                        iVar13 = (int)plVar6[2];
                      }
                      else {
                        iVar12 = (int)local_378[2];
                        uVar48 = 4;
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                        *(int *)(local_378 + 2) = iVar13;
                      }
                    }
                    else {
                      iVar12 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4);
                      if (iVar12 == -1) {
                        iVar12 = (int)local_378[2];
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                        *(int *)(local_378 + 2) = iVar13;
                      }
                      else {
                        iVar13 = (int)local_378[2];
                        uVar42 = 0;
                        uVar48 = *(undefined4 *)((long)&local_2e0 + (long)(int)uVar30 * 4);
                      }
                    }
                    uVar30 = *(uint *)(puVar2 + 2);
                    uVar39 = *(uint *)((long)puVar2 + 0x14);
                    *(int *)(plVar6 + 2) = iVar13 + 1;
                    pvVar17 = (void *)puVar2[1];
                    if (uVar39 <= uVar30) {
                      if (uVar39 == 0) {
                        sVar25 = 0x900;
                        uVar39 = 0x10;
                      }
                      else {
                        uVar39 = uVar39 << 1;
                        sVar25 = (ulong)uVar39 * 0x90;
                      }
                      pvVar17 = realloc(pvVar17,sVar25);
                      if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                      puVar2[1] = pvVar17;
                      uVar30 = *(uint *)(puVar2 + 2);
                      *(uint *)((long)puVar2 + 0x14) = uVar39;
                    }
                    uVar29 = 6;
                    *(int *)((long)&local_320 + lVar32 * 4) = iVar13;
                    lVar32 = (ulong)uVar30 * 0x90;
                    *(uint *)(puVar2 + 2) = uVar30 + 1;
                    goto LAB_0014ee20;
                  }
                }
                else if (((*(char *)(lVar32 + 0x20) == 'o') && (*(char *)(lVar32 + 0x21) == 'r')) &&
                        (*(char *)(lVar32 + 0x22) == '\0')) {
                  if (-1 < (int)uVar36) {
                    lVar32 = (long)(int)uVar36;
                    iVar11 = *(int *)((long)&local_320 + lVar32 * 4);
                    if (iVar11 == -1) {
                      iVar11 = (int)local_378[2];
                      *(int *)(local_378 + 2) = iVar11 + 1;
                    }
                    else {
                      uVar37 = *(undefined4 *)((long)&local_2e0 + lVar32 * 4);
                    }
                    if ((int)uVar30 < 0) {
                      if (bVar7) {
                        auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                        uVar42 = auVar49._8_8_;
                        iVar12 = auVar49._0_4_;
                        uVar48 = auVar49._4_4_;
                        if (iVar12 == -1) goto LAB_0014ebf8;
                        iVar13 = (int)plVar6[2];
                      }
                      else {
                        iVar12 = (int)local_378[2];
                        uVar48 = 4;
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                        *(int *)(local_378 + 2) = iVar13;
                      }
                    }
                    else {
                      uVar38 = -(uVar41 >> 0x1f) & 0xfffffffc00000000 | uVar41 << 2;
                      iVar12 = *(int *)((long)&local_320 + uVar38);
                      if (iVar12 == -1) {
                        iVar12 = (int)local_378[2];
                        uVar42 = 0;
                        iVar13 = iVar12 + 1;
                        *(int *)(local_378 + 2) = iVar13;
                      }
                      else {
                        iVar13 = (int)local_378[2];
                        uVar42 = 0;
                        uVar48 = *(undefined4 *)((long)&local_2e0 + uVar38);
                      }
                    }
                    uVar30 = *(uint *)(puVar2 + 2);
                    uVar39 = *(uint *)((long)puVar2 + 0x14);
                    *(int *)(plVar6 + 2) = iVar13 + 1;
                    pvVar17 = (void *)puVar2[1];
                    if (uVar39 <= uVar30) {
                      uVar5 = uVar39 << 1;
                      if (uVar39 == 0) {
                        uVar5 = 0x10;
                      }
                      pvVar17 = realloc(pvVar17,(ulong)uVar5 * 0x90);
                      if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                      puVar2[1] = pvVar17;
                      uVar30 = *(uint *)(puVar2 + 2);
                      *(uint *)((long)puVar2 + 0x14) = uVar5;
                    }
                    *(int *)((long)&local_320 + lVar32 * 4) = iVar13;
                    lVar32 = (ulong)uVar30 * 0x90;
                    uVar29 = 7;
                    *(uint *)(puVar2 + 2) = uVar30 + 1;
                    goto LAB_0014ee20;
                  }
                }
                else {
                  iVar12 = strcmp(pcVar34,"xor");
                  plVar6 = local_378;
                  if (iVar12 == 0) {
                    if (-1 < (int)uVar36) {
                      uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                      iVar11 = *(int *)((long)&local_320 + uVar38);
                      if (iVar11 == -1) {
                        iVar11 = (int)local_378[2];
                        *(int *)(local_378 + 2) = iVar11 + 1;
                      }
                      else {
                        uVar37 = *(undefined4 *)((long)&local_2e0 + uVar38);
                      }
                      if ((int)uVar30 < 0) {
                        if (bVar7) {
                          auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                          uVar42 = auVar49._8_8_;
                          iVar12 = auVar49._0_4_;
                          uVar48 = auVar49._4_4_;
                          if (iVar12 == -1) goto LAB_0014ebf8;
                          iVar13 = (int)plVar6[2];
                        }
                        else {
                          iVar12 = (int)local_378[2];
                          uVar48 = 4;
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                      }
                      else {
                        uVar38 = -(uVar41 >> 0x1f) & 0xfffffffc00000000 | uVar41 << 2;
                        iVar12 = *(int *)((long)&local_320 + uVar38);
                        if (iVar12 == -1) {
                          iVar12 = (int)local_378[2];
                          uVar42 = 0;
                          iVar13 = iVar12 + 1;
                          *(int *)(local_378 + 2) = iVar13;
                        }
                        else {
                          iVar13 = (int)local_378[2];
                          uVar42 = 0;
                          uVar48 = *(undefined4 *)((long)&local_2e0 + uVar38);
                        }
                      }
                      *(int *)(plVar6 + 2) = iVar13 + 1;
                      puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                      if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                      lVar32 = (long)(int)uVar36 * 4;
                      uVar29 = 8;
                      puVar22[2] = iVar13;
                      *(int *)((long)&local_320 + lVar32) = iVar13;
                      puVar22[3] = uVar47;
LAB_0014f3ac:
                      *(undefined4 *)((long)&local_2e0 + lVar32) = uVar47;
                      puVar22[6] = iVar11;
                      puVar22[7] = uVar37;
                      *puVar22 = uVar29;
                      *(undefined8 *)(puVar22 + 4) = 0;
                      *(undefined8 *)(puVar22 + 8) = 0;
                      puVar22[10] = iVar12;
                      puVar22[0xb] = uVar48;
                      *(undefined8 *)(puVar22 + 0xc) = uVar42;
                      puVar22[0x12] = 2;
                      *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                    }
                  }
                  else {
                    iVar12 = strcmp(pcVar34,"shl");
                    plVar6 = local_378;
                    if (iVar12 == 0) {
                      if (-1 < (int)uVar36) {
                        uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                        iVar11 = *(int *)((long)&local_320 + uVar38);
                        if (iVar11 == -1) {
                          iVar11 = (int)local_378[2];
                          *(int *)(local_378 + 2) = iVar11 + 1;
                        }
                        else {
                          uVar37 = *(undefined4 *)((long)&local_2e0 + uVar38);
                        }
                        if ((int)uVar30 < 0) {
                          if (bVar7) {
                            auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                            uVar42 = auVar49._8_8_;
                            iVar12 = auVar49._0_4_;
                            uVar48 = auVar49._4_4_;
                            if (iVar12 == -1) goto LAB_0014ebf8;
                            iVar13 = (int)plVar6[2];
                          }
                          else {
                            iVar12 = (int)local_378[2];
                            uVar48 = 4;
                            uVar42 = 0;
                            iVar13 = iVar12 + 1;
                            *(int *)(local_378 + 2) = iVar13;
                          }
                        }
                        else {
                          uVar38 = -(uVar41 >> 0x1f) & 0xfffffffc00000000 | uVar41 << 2;
                          iVar12 = *(int *)((long)&local_320 + uVar38);
                          if (iVar12 == -1) {
                            iVar12 = (int)local_378[2];
                            uVar42 = 0;
                            iVar13 = iVar12 + 1;
                            *(int *)(local_378 + 2) = iVar13;
                          }
                          else {
                            iVar13 = (int)local_378[2];
                            uVar42 = 0;
                            uVar48 = *(undefined4 *)((long)&local_2e0 + uVar38);
                          }
                        }
                        *(int *)(plVar6 + 2) = iVar13 + 1;
                        puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                        if (puVar22 != (undefined4 *)0x0) {
                          lVar32 = (long)(int)uVar36 * 4;
                          uVar29 = 9;
                          puVar22[2] = iVar13;
                          *(int *)((long)&local_320 + lVar32) = iVar13;
                          puVar22[3] = uVar47;
                          goto LAB_0014f3ac;
                        }
                        goto LAB_0014ebf8;
                      }
                    }
                    else {
                      iVar12 = strcmp(pcVar34,"shr");
                      if ((iVar12 == 0) || (iVar12 = strcmp(pcVar34,"sar"), iVar12 == 0)) {
                        plVar6 = local_378;
                        if (-1 < (int)uVar36) {
                          uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                          iVar11 = *(int *)((long)&local_320 + uVar38);
                          if (iVar11 == -1) {
                            iVar11 = (int)local_378[2];
                            *(int *)(local_378 + 2) = iVar11 + 1;
                          }
                          else {
                            uVar37 = *(undefined4 *)((long)&local_2e0 + uVar38);
                          }
                          if ((int)uVar30 < 0) {
                            if (bVar7) {
                              auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
                              uVar42 = auVar49._8_8_;
                              iVar12 = auVar49._0_4_;
                              uVar48 = auVar49._4_4_;
                              if (iVar12 == -1) goto LAB_0014ebf8;
                              iVar13 = (int)plVar6[2];
                            }
                            else {
                              iVar12 = (int)local_378[2];
                              uVar48 = 4;
                              uVar42 = 0;
                              iVar13 = iVar12 + 1;
                              *(int *)(local_378 + 2) = iVar13;
                            }
                          }
                          else {
                            uVar38 = -(uVar41 >> 0x1f) & 0xfffffffc00000000 | uVar41 << 2;
                            iVar12 = *(int *)((long)&local_320 + uVar38);
                            if (iVar12 == -1) {
                              iVar12 = (int)local_378[2];
                              uVar42 = 0;
                              iVar13 = iVar12 + 1;
                              *(int *)(local_378 + 2) = iVar13;
                            }
                            else {
                              iVar13 = (int)local_378[2];
                              uVar42 = 0;
                              uVar48 = *(undefined4 *)((long)&local_2e0 + uVar38);
                            }
                          }
                          *(int *)(plVar6 + 2) = iVar13 + 1;
                          puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                          if (puVar22 != (undefined4 *)0x0) {
                            lVar32 = (long)(int)uVar36 * 4;
                            puVar22[2] = iVar13;
                            puVar22[3] = uVar47;
                            uVar29 = 10;
                            *(int *)((long)&local_320 + lVar32) = iVar13;
                            goto LAB_0014f3ac;
                          }
                          goto LAB_0014ebf8;
                        }
                      }
                      else {
                        iVar12 = strcmp(pcVar34,"neg");
                        plVar6 = local_378;
                        if (iVar12 == 0) {
                          if (-1 < (int)uVar36) {
                            auVar49 = FUN_0014ccb0(puVar2,local_378,0,uVar18);
                            if (auVar49._0_4_ == -1) goto LAB_0014ebf8;
                            uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                            iVar11 = *(int *)((long)&local_320 + uVar38);
                            if (iVar11 == -1) {
                              iVar11 = (int)plVar6[2];
                              iVar12 = iVar11 + 1;
                              *(int *)(plVar6 + 2) = iVar12;
                              uVar48 = uVar47;
                            }
                            else {
                              iVar12 = (int)plVar6[2];
                              uVar48 = *(undefined4 *)((long)&local_2e0 + uVar38);
                            }
                            *(int *)(plVar6 + 2) = iVar12 + 1;
                            puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                            if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                            *(long *)(puVar22 + 8) = auVar49._8_8_;
                            *(undefined4 *)((long)&local_2e0 + (long)(int)uVar36 * 4) = uVar47;
                            *(int *)((long)&local_320 + (long)(int)uVar36 * 4) = iVar12;
                            *puVar22 = 3;
                            puVar22[2] = iVar12;
                            puVar22[3] = uVar47;
                            *(undefined8 *)(puVar22 + 4) = 0;
                            *(long *)(puVar22 + 6) = auVar49._0_8_;
                            puVar22[10] = iVar11;
                            puVar22[0xb] = uVar48;
                            *(undefined8 *)(puVar22 + 0xc) = 0;
                            puVar22[0x12] = 2;
                            *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                          }
                        }
                        else {
                          iVar12 = strcmp(pcVar34,"not");
                          plVar6 = local_378;
                          if (iVar12 == 0) {
                            if (-1 < (int)uVar36) {
                              uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                              iVar11 = *(int *)((long)&local_320 + uVar38);
                              if (iVar11 == -1) {
                                iVar11 = (int)local_378[2];
                                *(int *)(local_378 + 2) = iVar11 + 1;
                              }
                              else {
                                uVar37 = *(undefined4 *)((long)&local_2e0 + uVar38);
                              }
                              auVar49 = FUN_0014ccb0(puVar2,local_378,0xffffffffffffffff,uVar18);
                              if (auVar49._0_4_ == -1) goto LAB_0014ebf8;
                              iVar12 = (int)plVar6[2];
                              *(int *)(plVar6 + 2) = iVar12 + 1;
                              puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                              if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                              puVar22[2] = iVar12;
                              *(int *)((long)&local_320 + (long)(int)uVar36 * 4) = iVar12;
                              *(undefined4 *)((long)&local_2e0 + (long)(int)uVar36 * 4) = uVar47;
                              *puVar22 = 8;
                              puVar22[3] = uVar47;
LAB_0014f748:
                              *(undefined8 *)(puVar22 + 4) = 0;
                              puVar22[6] = iVar11;
                              puVar22[7] = uVar37;
                              *(undefined8 *)(puVar22 + 8) = 0;
                              *(undefined1 (*) [16])(puVar22 + 10) = auVar49;
                              puVar22[0x12] = 2;
                              *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                            }
                          }
                          else {
                            iVar12 = strcmp(pcVar34,"inc");
                            plVar6 = local_378;
                            if (iVar12 == 0) {
                              if (-1 < (int)uVar36) {
                                uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                                iVar11 = *(int *)((long)&local_320 + uVar38);
                                if (iVar11 == -1) {
                                  iVar11 = (int)local_378[2];
                                  *(int *)(local_378 + 2) = iVar11 + 1;
                                }
                                else {
                                  uVar37 = *(undefined4 *)((long)&local_2e0 + uVar38);
                                }
                                auVar49 = FUN_0014ccb0(puVar2,local_378,1,uVar18);
                                if (auVar49._0_4_ != -1) {
                                  iVar12 = (int)plVar6[2];
                                  *(int *)(plVar6 + 2) = iVar12 + 1;
                                  puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                  if (puVar22 != (undefined4 *)0x0) {
                                    puVar22[2] = iVar12;
                                    *(int *)((long)&local_320 + (long)(int)uVar36 * 4) = iVar12;
                                    *(undefined4 *)((long)&local_2e0 + (long)(int)uVar36 * 4) =
                                         uVar47;
                                    *puVar22 = 2;
                                    puVar22[3] = uVar47;
                                    goto LAB_0014f748;
                                  }
                                }
                                goto LAB_0014ebf8;
                              }
                            }
                            else {
                              iVar12 = strcmp(pcVar34,"dec");
                              plVar6 = local_378;
                              if (iVar12 == 0) {
                                if (-1 < (int)uVar36) {
                                  iVar11 = *(int *)((long)&local_320 + (long)(int)uVar36 * 4);
                                  if (iVar11 == -1) {
                                    iVar11 = (int)local_378[2];
                                    *(int *)(local_378 + 2) = iVar11 + 1;
                                  }
                                  else {
                                    uVar37 = *(undefined4 *)
                                              ((long)&local_2e0 + (long)(int)uVar36 * 4);
                                  }
                                  auVar49 = FUN_0014ccb0(puVar2,local_378,1,uVar18);
                                  if (auVar49._0_4_ != -1) {
                                    iVar12 = (int)plVar6[2];
                                    *(int *)(plVar6 + 2) = iVar12 + 1;
                                    puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                    if (puVar22 != (undefined4 *)0x0) {
                                      lVar32 = (long)(int)uVar36 * 4;
                                      puVar22[2] = iVar12;
                                      *(int *)((long)&local_320 + lVar32) = iVar12;
                                      *(undefined4 *)((long)&local_2e0 + lVar32) = uVar47;
                                      *puVar22 = 3;
                                      puVar22[3] = uVar47;
                                      goto LAB_0014f748;
                                    }
                                  }
                                  goto LAB_0014ebf8;
                                }
                              }
                              else {
                                iVar12 = strncmp(pcVar34,"set",3);
                                if (iVar12 == 0) {
                                  if (-1 < (int)uVar36) {
                                    iVar12 = FUN_0014c510(lVar32 + 0x23);
                                    iVar11 = (int)local_378[2];
                                    *(int *)(local_378 + 2) = iVar11 + 1;
                                    piVar21 = (int *)FUN_0014c000(puVar2);
                                    if (piVar21 == (int *)0x0) goto LAB_0014ebf8;
                                    if (iVar12 == 0x1d || local_3d0 == -1) {
                                      if (local_3cc == -1) {
                                        iVar13 = 0;
                                        *piVar21 = 0x1d;
                                        piVar21[2] = iVar11;
                                        piVar21[3] = 1;
                                        piVar21[4] = 0;
                                        piVar21[5] = 0;
                                      }
                                      else {
                                        iVar13 = 1;
                                        *piVar21 = 0;
                                        piVar21[2] = iVar11;
                                        piVar21[3] = 1;
                                        piVar21[4] = 0;
                                        piVar21[5] = 0;
                                        piVar21[6] = local_3cc;
                                        piVar21[7] = 6;
                                        piVar21[8] = 0;
                                        piVar21[9] = 0;
                                      }
                                    }
                                    else {
                                      piVar21[2] = iVar11;
                                      piVar21[3] = 1;
                                      iVar13 = 2;
                                      *piVar21 = iVar12;
                                      piVar21[4] = 0;
                                      piVar21[5] = 0;
                                      *(ulong *)(piVar21 + 6) = uVar26;
                                      piVar21[8] = 0;
                                      piVar21[9] = 0;
                                      *(undefined1 (*) [16])(piVar21 + 10) = auVar50;
                                    }
                                    uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 | uVar38 << 2;
                                    piVar21[0x12] = iVar13;
                                    *(int *)((long)&local_320 + uVar38) = iVar11;
                                    *(undefined4 *)((long)&local_2e0 + uVar38) = 1;
                                    *(undefined8 *)(piVar21 + 0x1c) = uVar18;
                                  }
                                }
                                else {
                                  iVar12 = strcmp(pcVar34,"bswap");
                                  plVar6 = local_378;
                                  if (iVar12 == 0) {
                                    if (-1 < (int)uVar36) {
                                      iVar11 = (int)local_378[2];
                                      *(int *)(local_378 + 2) = iVar11 + 1;
                                      puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                      if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                      *puVar22 = 0;
                                      puVar22[2] = iVar11;
                                      puVar22[3] = uVar47;
                                      iVar12 = *(int *)((long)&local_320 + (long)(int)uVar36 * 4);
                                      *(undefined8 *)(puVar22 + 4) = 0;
                                      if (iVar12 == -1) {
                                        iVar12 = (int)plVar6[2];
                                        *(int *)(plVar6 + 2) = iVar12 + 1;
                                      }
                                      *(int *)((long)&local_320 + (long)(int)uVar36 * 4) = iVar11;
                                      puVar22[6] = iVar12;
                                      puVar22[7] = uVar47;
                                      *(undefined8 *)(puVar22 + 8) = 0;
                                      puVar22[0x12] = 1;
                                      *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                    }
                                  }
                                  else {
                                    iVar12 = strcmp(pcVar34,"bsf");
                                    if (((iVar12 == 0) ||
                                        (iVar12 = strcmp(pcVar34,"bsr"), iVar12 == 0)) ||
                                       ((iVar12 = strcmp(pcVar34,"popcnt"), iVar12 == 0 ||
                                        ((iVar12 = strcmp(pcVar34,"lzcnt"), iVar12 == 0 ||
                                         (iVar12 = strcmp(pcVar34,"tzcnt"), iVar12 == 0)))))) {
                                      if (-1 < (int)uVar36) {
                                        iVar12 = (int)local_378[2];
                                        iVar11 = iVar12 + 1;
                                        if ((int)uVar30 < 0) {
                                          *(int *)(local_378 + 2) = iVar11;
                                          iVar15 = iVar11;
                                          iVar13 = iVar12;
                                          uVar48 = uVar47;
                                        }
                                        else {
                                          iVar13 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4
                                                           );
                                          iVar15 = iVar12;
                                          if (iVar13 == -1) {
                                            *(int *)(local_378 + 2) = iVar11;
                                            iVar15 = iVar11;
                                            iVar13 = iVar12;
                                          }
                                        }
                                        *(int *)(local_378 + 2) = iVar15 + 1;
                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                        if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                        uVar38 = -(uVar38 >> 0x1f) & 0xfffffffc00000000 |
                                                 uVar38 << 2;
                                        *puVar22 = 0;
                                        *(int *)((long)&local_320 + uVar38) = iVar15;
                                        *(undefined4 *)((long)&local_2e0 + uVar38) = uVar47;
                                        puVar22[0x12] = 1;
                                        puVar22[2] = iVar15;
                                        puVar22[3] = uVar47;
                                        *(undefined8 *)(puVar22 + 4) = 0;
                                        puVar22[6] = iVar13;
                                        puVar22[7] = uVar48;
                                        *(undefined8 *)(puVar22 + 8) = 0;
                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                      }
                                    }
                                    else {
                                      iVar12 = strncmp(pcVar34,"cmov",4);
                                      if (iVar12 == 0) {
                                        if (-1 < (int)(uVar36 | uVar30)) {
                                          iVar13 = FUN_0014c510(lVar32 + 0x24);
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
                                            piVar21 = (int *)FUN_0014c000(puVar2);
                                            if (piVar21 == (int *)0x0) goto LAB_0014ebf8;
                                            piVar21[2] = iVar12;
                                            piVar21[3] = 6;
                                            *(ulong *)(piVar21 + 6) = uVar26;
                                            *(long *)(piVar21 + 10) = auVar50._0_8_;
                                            lVar32 = plVar6[2];
                                            piVar21[0x12] = 2;
                                            *piVar21 = iVar13;
                                            piVar21[4] = 0;
                                            piVar21[5] = 0;
                                            piVar21[8] = 0;
                                            piVar21[9] = 0;
                                            *(undefined8 *)(piVar21 + 0xc) = local_3d8;
                                            *(undefined8 *)(piVar21 + 0x1c) = uVar18;
                                            iVar13 = (int)lVar32;
                                            iVar15 = iVar12;
                                          }
                                          iVar12 = *(int *)((long)&local_320 + (long)(int)uVar30 * 4
                                                           );
                                          iVar11 = iVar13;
                                          if (iVar12 == -1) {
                                            iVar11 = iVar13 + 1;
                                            *(int *)(plVar6 + 2) = iVar11;
                                            iVar12 = iVar13;
                                          }
                                          iVar14 = *(int *)((long)&local_320 + (long)(int)uVar36 * 4
                                                           );
                                          iVar13 = iVar11;
                                          if (iVar14 == -1) {
                                            iVar13 = iVar11 + 1;
                                            *(int *)(plVar6 + 2) = iVar13;
                                            iVar14 = iVar11;
                                          }
                                          *(int *)(plVar6 + 2) = iVar13 + 1;
                                          puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                          if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                          *puVar22 = 0x1c;
                                          *(undefined4 *)((long)&local_2e0 + (long)(int)uVar36 * 4)
                                               = uVar47;
                                          *(int *)((long)&local_320 + (long)(int)uVar36 * 4) =
                                               iVar13;
                                          puVar22[2] = iVar13;
                                          puVar22[3] = uVar47;
                                          *(undefined8 *)(puVar22 + 4) = 0;
                                          puVar22[6] = iVar15;
                                          puVar22[7] = 6;
                                          *(undefined8 *)(puVar22 + 8) = 0;
                                          puVar22[10] = iVar12;
                                          puVar22[0xb] = uVar48;
                                          *(undefined8 *)(puVar22 + 0xc) = 0;
                                          puVar22[0xe] = iVar14;
                                          puVar22[0xf] = uVar47;
                                          *(undefined8 *)(puVar22 + 0x10) = 0;
                                          puVar22[0x12] = 3;
                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                        }
                                      }
                                      else {
                                        iVar12 = strcmp(pcVar34,"cmp");
                                        if ((iVar12 == 0) ||
                                           (iVar12 = strcmp(pcVar34,"test"), iVar12 == 0)) {
                                          plVar6 = local_378;
                                          if ((int)uVar36 < 0) goto LAB_0014e30c;
                                          local_3d0 = *(int *)((long)&local_320 +
                                                              (long)(int)uVar36 * 4);
                                          if (local_3d0 == -1) {
                                            local_3d0 = (int)local_378[2];
                                            *(int *)(local_378 + 2) = local_3d0 + 1;
                                          }
                                          uVar26 = CONCAT44(uVar47,local_3d0);
                                          if ((int)uVar30 < 0) {
                                            if (!bVar7) {
                                              iVar11 = (int)local_378[2];
                                              uVar48 = 4;
                                              local_3cc = iVar11 + 1;
                                              *(int *)(local_378 + 2) = local_3cc;
                                              goto LAB_001506c4;
                                            }
                                            auVar50 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18
                                                                  );
LAB_0015078c:
                                            if ((bool)(bVar7 & auVar50._0_4_ == -1))
                                            goto LAB_0014ebf8;
                                            local_3cc = (int)plVar6[2];
                                          }
                                          else {
                                            local_3cc = (int)local_378[2];
                                            iVar11 = *(int *)((long)&local_320 +
                                                             (long)(int)uVar30 * 4);
                                            auVar50._4_4_ = uVar48;
                                            auVar50._0_4_ = local_3cc;
                                            if (iVar11 == -1) {
                                              *(int *)(local_378 + 2) = local_3cc + 1;
                                              auVar50._8_8_ = 0;
                                              goto LAB_0015078c;
                                            }
LAB_001506c4:
                                            auVar50._4_4_ = uVar48;
                                            auVar50._0_4_ = iVar11;
                                            auVar50._8_8_ = 0;
                                          }
                                          *(int *)(plVar6 + 2) = local_3cc + 1;
                                          puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                          if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                          puVar22[2] = local_3cc;
                                          puVar22[3] = 6;
                                          puVar22[6] = local_3d0;
                                          puVar22[0x12] = 2;
                                          *puVar22 = 0xb;
                                          *(undefined8 *)(puVar22 + 4) = 0;
                                          puVar22[7] = uVar47;
                                          *(undefined8 *)(puVar22 + 8) = 0;
                                          *(undefined1 (*) [16])(puVar22 + 10) = auVar50;
                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                        }
                                        else {
                                          iVar12 = strcmp(pcVar34,"jmp");
                                          cVar10 = *(char *)(lVar32 + 0x20);
                                          if (cVar10 == 'j') {
                                            if (iVar12 != 0) {
                                              iVar12 = FUN_0014c510(lVar32 + 0x21);
                                              iVar11 = local_3cc;
                                              if (iVar12 != 0x1d && local_3d0 != -1) {
                                                iVar11 = (int)local_378[2];
                                                *(int *)(local_378 + 2) = iVar11 + 1;
                                                piVar21 = (int *)FUN_0014c000(puVar2);
                                                if (piVar21 == (int *)0x0) goto LAB_0014ebf8;
                                                piVar21[2] = iVar11;
                                                piVar21[3] = 6;
                                                piVar21[0x12] = 2;
                                                *piVar21 = iVar12;
                                                piVar21[4] = 0;
                                                piVar21[5] = 0;
                                                *(ulong *)(piVar21 + 6) = uVar26;
                                                piVar21[8] = 0;
                                                piVar21[9] = 0;
                                                *(undefined1 (*) [16])(piVar21 + 10) = auVar50;
                                                *(undefined8 *)(piVar21 + 0x1c) = uVar18;
                                              }
                                              puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                              if (puVar22 != (undefined4 *)0x0) {
                                                puVar22[0x12] = 1;
                                                *puVar22 = 0x17;
                                                *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                puVar22[6] = iVar11;
                                                puVar22[7] = 6;
                                                *(undefined8 *)(puVar22 + 8) = 0;
                                                *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                goto LAB_0014e30c;
                                              }
                                              goto LAB_0014ebf8;
                                            }
                                          }
                                          else if (iVar12 != 0) {
                                            iVar12 = strcmp(pcVar34,"call");
                                            if (iVar12 == 0) {
                                              iVar11 = (int)local_378[2];
                                              *(int *)(local_378 + 2) = iVar11 + 1;
                                              puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                              if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
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
                                              uVar42 = DAT_0020c568;
                                              *(ulonglong *)(puVar22 + 8) = uVar23;
                                              puVar22[0x12] = 1;
                                              uVar38 = 0;
                                              *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                              *(undefined8 *)(puVar22 + 6) = uVar42;
                                              do {
                                                if (*(int *)((long)&local_320 +
                                                            (long)(int)(&DAT_0020c610)[uVar38] * 4)
                                                    == -1) {
                                                  if ((int)uVar38 == 0) goto LAB_00150c90;
                                                  break;
                                                }
                                                uVar38 = uVar38 + 1;
                                              } while (uVar38 != 6);
                                              puVar24 = malloc(-((uVar38 & 0xffffffff) >> 0x1f) &
                                                               0xfffffff000000000 |
                                                               (uVar38 & 0xffffffff) << 4);
                                              *(undefined4 **)(puVar22 + 0x14) = puVar24;
                                              if (puVar24 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                              lVar32 = 0;
                                              *(undefined8 *)(puVar22 + 0x16) = 0;
                                              puVar22[0x18] = (int)uVar38;
                                              do {
                                                iVar12 = (&DAT_0020c610)[lVar32];
                                                lVar32 = lVar32 + 1;
                                                *(undefined8 *)(puVar24 + 2) = 0;
                                                uVar47 = *(undefined4 *)
                                                          ((long)&local_2e0 + (long)iVar12 * 4);
                                                *puVar24 = *(undefined4 *)
                                                            ((long)&local_320 + (long)iVar12 * 4);
                                                puVar24[1] = uVar47;
                                                puVar24 = puVar24 + 4;
                                              } while ((int)lVar32 < (int)uVar38);
LAB_00150c90:
                                              local_320 = CONCAT44(local_320._4_4_,iVar11);
                                              local_2e0 = CONCAT44(local_2e0._4_4_,4);
                                            }
                                            else {
                                              iVar12 = strcmp(pcVar34,"ret");
                                              if (iVar12 == 0) {
                                                puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
                                                *puVar22 = 0x1a;
                                                *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                if (((int)local_2a0 == -1) ||
                                                   (iVar11 = (int)local_2a0, iVar12 = (int)local_260
                                                   , 1 < (int)local_260 - 7U)) {
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
                                                sVar25 = strlen(pcVar34);
                                                if (((sVar25 < 2) || (pcVar34[sVar25 - 2] != 's'))
                                                   || (uVar39 = (uint)(pcVar34[sVar25 - 1] == 's'),
                                                      pcVar34[sVar25 - 1] != 'd' && uVar39 == 0)) {
LAB_0014ff5c:
                                                  if (cVar10 == 'v') {
                                                    local_394 = 0xffffffff;
                                                    local_390 = 0xffffffff;
                                                    local_38c = 0xffffffff;
                                                    local_388 = 0xffffffff;
                                                    pcVar28 = acStack_159 + 0x41;
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
                                                      pcVar19 = pcVar28;
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
                                                              FUN_0014c7d4(pcVar28);
                                                            }
                                                            if ((char)local_d8 != '\0') {
                                                              FUN_0014c7d4(&local_d8);
                                                            }
                                                            FUN_0014c954(acStack_159 + 1,&local_388)
                                                            ;
                                                            FUN_0014c954(pcVar28,&local_384);
                                                            FUN_0014c954(&local_d8,&local_380);
                                                            iVar11 = 3;
                                                            goto LAB_001502e4;
                                                          }
                                                          pcVar19 = pcVar19 + 1;
                                                        }
                                                      }
                                                    }
                                                    FUN_0014c954(acStack_159 + 1,&local_388);
                                                    FUN_0014c954(pcVar28,&local_384);
LAB_001502e4:
                                                    uVar36 = local_388;
                                                    pcVar19 = acStack_159 + 1;
                                                    if ((int)local_388 < 0) {
                                                      FUN_0014c9e0(pcVar19,&local_394);
                                                    }
                                                    uVar30 = local_384;
                                                    if ((int)local_384 < 0) {
                                                      FUN_0014c9e0(pcVar28,&local_390);
                                                    }
                                                    uVar39 = local_380;
                                                    if ((iVar11 == 3) && ((int)local_380 < 0)) {
                                                      FUN_0014c9e0(&local_d8,&local_38c);
                                                    }
                                                    uVar5 = local_394;
                                                    local_3f8 = (ulong)local_394;
                                                    if ((int)(uVar36 & local_394) < 0) {
                                                      FUN_0014ca70(pcVar19,&local_37c);
                                                    }
                                                    uVar4 = local_390;
                                                    if ((int)(uVar30 & local_390) < 0) {
                                                      FUN_0014ca70(pcVar28,&local_370);
                                                    }
                                                    if ((iVar11 == 3) &&
                                                       ((int)(uVar39 & local_38c) < 0)) {
                                                      FUN_0014ca70(&local_d8,&local_368);
                                                    }
                                                    if ((int)uVar36 < 0) {
                                                      if (-1 < (int)uVar30) {
                                                        if ((int)uVar5 < 0) {
                                                          local_3f8 = (ulong)local_37c;
                                                          if ((int)local_37c < 0) {
                                                            iVar12 = 0xc;
LAB_0015137c:
                                                            puVar44 = (undefined8 *)0x0;
                                                            local_3f8 = 0xffffffff;
                                                            goto LAB_001503b8;
                                                          }
                                                          puVar44 = &local_2a0;
                                                          iVar12 = 0xc;
                                                        }
                                                        else {
                                                          puVar44 = &local_220;
                                                          iVar12 = 0xc;
                                                        }
                                                        goto LAB_001503bc;
                                                      }
                                                      if ((int)uVar39 < 0) {
                                                        if ((int)uVar5 < 0) {
                                                          iVar12 = 10 - ((int)~(uVar4 & local_38c)
                                                                        >> 0x1f);
                                                          goto LAB_001513a0;
                                                        }
                                                        puVar44 = &local_220;
                                                        iVar12 = 0xb;
                                                      }
                                                      else {
                                                        iVar12 = 0xc;
                                                        if ((int)uVar5 < 0) {
LAB_001513a0:
                                                          local_3f8 = (ulong)local_37c;
                                                          if ((int)local_37c < 0) goto LAB_0015137c;
                                                          puVar44 = &local_2a0;
                                                        }
                                                        else {
                                                          puVar44 = &local_220;
                                                        }
                                                      }
LAB_00151350:
                                                      if (((int)uVar4 < 0) ||
                                                         (iVar13 = *(int *)((long)&local_220 +
                                                                           (long)(int)uVar4 * 4),
                                                         iVar13 == -1)) {
                                                        if ((int)local_370 < 0) {
                                                          iVar13 = -1;
                                                        }
                                                        else {
                                                          iVar13 = *(int *)((long)&local_2a0 +
                                                                           (long)(int)local_370 * 4)
                                                          ;
                                                        }
                                                      }
                                                    }
                                                    else {
                                                      local_3f8 = (ulong)uVar36;
                                                      iVar12 = 0xc;
                                                      puVar44 = local_1d8;
LAB_001503b8:
                                                      if ((int)uVar30 < 0) goto LAB_00151350;
LAB_001503bc:
                                                      iVar13 = *(int *)((long)local_1d8 +
                                                                       (long)(int)uVar30 * 4);
                                                      if (iVar13 == -1) goto LAB_00151350;
                                                    }
                                                    if ((((int)uVar39 < 0) ||
                                                        (iVar15 = *(int *)((long)local_1d8 +
                                                                          (long)(int)uVar39 * 4),
                                                        iVar15 == -1)) &&
                                                       (((int)local_38c < 0 ||
                                                        (iVar15 = *(int *)((long)&local_220 +
                                                                          (long)(int)local_38c * 4),
                                                        iVar15 == -1)))) {
                                                      if (local_368 < 0) {
                                                        iVar15 = -1;
                                                      }
                                                      else {
                                                        iVar15 = *(int *)((long)&local_2a0 +
                                                                         (long)local_368 * 4);
                                                      }
                                                    }
                                                    iVar14 = strncmp(pcVar34,"vmov",4);
                                                    if (iVar14 == 0) {
                                                      if ((uint)local_3f8 == 0xffffffff) {
                                                        iVar11 = FUN_0014c870(pcVar19);
                                                        if (iVar11 != 0 && iVar13 != -1) {
                                                          puVar22 = (undefined4 *)
                                                                    FUN_0014c000(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014ebf8;
                                                          *puVar22 = 0x16;
                                                          uVar42 = DAT_0020c568;
                                                          puVar22[0x12] = 2;
                                                          *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                          *(undefined8 *)(puVar22 + 6) = uVar42;
                                                          *(undefined8 *)(puVar22 + 8) = 0;
                                                          puVar22[10] = iVar13;
                                                          puVar22[0xb] = iVar12;
                                                          *(undefined8 *)(puVar22 + 0xc) = 0;
                                                          *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                        }
                                                      }
                                                      else {
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2)
                                                        ;
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014ebf8;
                                                        if (iVar13 == -1) {
                                                          FUN_0014c870(pcVar28);
                                                          uVar47 = 0x15;
                                                          iVar15 = 5;
                                                        }
                                                        else {
                                                          uVar47 = 0;
                                                          iVar15 = iVar12;
                                                        }
                                                        puVar22[6] = iVar13;
                                                        puVar22[7] = iVar15;
                                                        uVar38 = -(local_3f8 >> 0x1f) &
                                                                 0xfffffffc00000000 | local_3f8 << 2
                                                        ;
                                                        *puVar22 = uVar47;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = iVar12;
                                                        *(int *)((long)puVar44 + uVar38) = iVar11;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                        if (iVar12 == 10) {
                                                          *(undefined4 *)((long)&local_260 + uVar38)
                                                               = 10;
                                                        }
                                                      }
                                                    }
                                                    else {
                                                      pcVar34 = (char *)(lVar32 + 0x21);
                                                      iVar14 = strncmp(pcVar34,"add",3);
                                                      if (iVar14 == 0) {
                                                        uVar47 = 2;
                                                      }
                                                      else {
                                                        iVar14 = strncmp(pcVar34,"sub",3);
                                                        if (iVar14 == 0) {
                                                          uVar47 = 3;
                                                        }
                                                        else {
                                                          iVar14 = strncmp(pcVar34,"mul",3);
                                                          if (iVar14 == 0) {
                                                            uVar47 = 4;
                                                          }
                                                          else {
                                                            iVar14 = strncmp(pcVar34,"div",3);
                                                            if (iVar14 == 0) {
                                                              uVar47 = 5;
                                                            }
                                                            else {
                                                              iVar14 = strncmp(pcVar34,"and",3);
                                                              if (iVar14 == 0) {
                                                                uVar47 = 6;
                                                              }
                                                              else {
                                                                iVar14 = strncmp(pcVar34,"or",2);
                                                                if (iVar14 == 0) {
                                                                  uVar47 = 7;
                                                                }
                                                                else {
                                                                  iVar14 = strncmp(pcVar34,"xor",3);
                                                                  if (iVar14 != 0)
                                                                  goto LAB_0014e30c;
                                                                  uVar47 = 8;
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                      }
                                                      if ((uint)local_3f8 != 0xffffffff) {
                                                        iVar3 = (int)local_378[2];
                                                        iVar14 = iVar3 + 1;
                                                        iVar33 = iVar3;
                                                        if (iVar11 == 3) {
                                                          iVar11 = iVar13;
                                                          if (iVar13 == -1) {
                                                            *(int *)(local_378 + 2) = iVar14;
                                                            iVar33 = iVar14;
                                                            iVar11 = iVar3;
                                                          }
                                                          iVar13 = iVar15;
                                                          if (iVar15 == -1) {
                                                            *(int *)(local_378 + 2) = iVar33 + 1;
                                                            iVar13 = iVar33;
                                                            iVar33 = iVar33 + 1;
                                                          }
                                                        }
                                                        else {
                                                          iVar11 = *(int *)((long)puVar44 +
                                                                           (long)(int)(uint)
                                                  local_3f8 * 4);
                                                  if (iVar11 == -1) {
                                                    *(int *)(local_378 + 2) = iVar14;
                                                    iVar33 = iVar14;
                                                    iVar11 = iVar3;
                                                  }
                                                  if (iVar13 == -1) {
                                                    *(int *)(local_378 + 2) = iVar33 + 1;
                                                    iVar13 = iVar33;
                                                    iVar33 = iVar33 + 1;
                                                  }
                                                  }
                                                  *(int *)(local_378 + 2) = iVar33 + 1;
                                                  puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014ebf8;
                                                  *puVar22 = uVar47;
                                                  puVar22[2] = iVar33;
                                                  puVar22[3] = iVar12;
                                                  uVar38 = -(ulong)((uint)local_3f8 >> 0x1f) &
                                                           0xfffffffc00000000 | local_3f8 << 2;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = iVar12;
                                                  *(int *)((long)puVar44 + uVar38) = iVar33;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  puVar22[10] = iVar13;
                                                  puVar22[0xb] = iVar12;
                                                  *(undefined8 *)(puVar22 + 0xc) = 0;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  if (iVar12 == 10) {
                                                    *(undefined4 *)((long)&local_260 + uVar38) = 10;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    local_370 = 0xffffffff;
                                                    local_368 = -1;
                                                    if (iVar11 == 0) {
LAB_0014ff78:
                                                      if (cVar10 == 'f') {
                                                        iVar12 = strcmp(pcVar34,"fld");
                                                        if (iVar12 == 0) {
                                                          local_368 = -1;
                                                          iVar11 = (int)local_378[2];
                                                          *(int *)(local_378 + 2) = iVar11 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    FUN_0014c000(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014ebf8;
                                                          iVar12 = FUN_0014c4a0(acStack_159 + 1,
                                                                                &local_368);
                                                          if ((iVar12 == 0) || (7 < local_368)) {
                                                            iVar12 = -1;
                                                            uVar48 = 0x15;
                                                            uVar47 = 5;
                                                          }
                                                          else {
                                                            iVar12 = *(int *)((long)&local_360 +
                                                                             (long)local_368 * 4);
                                                            uVar47 = 5;
                                                            if (iVar12 != -1) {
                                                              uVar47 = 9;
                                                            }
                                                            uVar48 = 0x15;
                                                            if (iVar12 != -1) {
                                                              uVar48 = 0;
                                                            }
                                                          }
                                                          puVar22[6] = iVar12;
                                                          puVar22[7] = uVar47;
                                                          *puVar22 = uVar48;
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
                                                          iVar12 = strcmp(pcVar34,"fstp");
                                                          if ((iVar12 == 0) ||
                                                             (iVar12 = strcmp(pcVar34,"fst"),
                                                             iVar12 == 0)) {
                                                            local_368 = -1;
                                                            iVar12 = FUN_0014c4a0(acStack_159 + 1,
                                                                                  &local_368);
                                                            iVar11 = local_368;
                                                            plVar6 = local_378;
                                                            if ((iVar12 == 0) || (7 < local_368)) {
                                                              puVar22 = (undefined4 *)
                                                                        FUN_0014c000(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014ebf8;
                                                              *puVar22 = 0x16;
                                                              uVar42 = DAT_0020c568;
                                                              *(undefined8 *)(puVar22 + 2) =
                                                                   0xffffffff;
                                                              *(undefined8 *)(puVar22 + 6) = uVar42;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              iVar11 = (int)local_360;
                                                              if ((int)local_360 == -1) {
                                                                iVar11 = (int)local_378[2];
                                                                *(int *)(local_378 + 2) = iVar11 + 1
                                                                ;
                                                              }
                                                              uVar47 = 9;
LAB_00150264:
                                                              puVar22[10] = iVar11;
                                                              puVar22[0xb] = uVar47;
                                                              *(undefined8 *)(puVar22 + 0xc) = 0;
                                                              puVar22[0x12] = 2;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                            }
                                                            else {
                                                              iVar12 = (int)local_378[2];
                                                              *(int *)(local_378 + 2) = iVar12 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        FUN_0014c000(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014ebf8;
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
                                                            iVar12 = strncmp(pcVar34,"fadd",4);
                                                            if (iVar12 == 0) {
                                                              uVar48 = 2;
                                                            }
                                                            else {
                                                              iVar12 = strncmp(pcVar34,"fsub",4);
                                                              if (iVar12 == 0) {
                                                                uVar48 = 3;
                                                              }
                                                              else {
                                                                iVar12 = strncmp(pcVar34,"fmul",4);
                                                                if (iVar12 == 0) {
                                                                  uVar48 = 4;
                                                                }
                                                                else {
                                                                  iVar12 = strncmp(pcVar34,"fdiv",4)
                                                                  ;
                                                                  if (iVar12 != 0)
                                                                  goto LAB_0014e30c;
                                                                  uVar48 = 5;
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
                                                              iVar11 = FUN_0014c4a0(acStack_159 +
                                                                                    0x41,&local_368)
                                                              ;
                                                              piVar21 = extraout_x1;
                                                              if (((iVar11 == 0) || (7 < local_368))
                                                                 || (iVar11 = *(int *)((long)&
                                                  local_360 + (long)local_368 * 4), iVar11 == -1))
                                                  goto LAB_00150e6c;
                                                  }
                                                  else {
                                                    if (iVar11 == 1) {
                                                      piVar21 = &local_368;
LAB_00150e6c:
                                                      iVar11 = FUN_0014c4a0(acStack_159 + 1,piVar21)
                                                      ;
                                                      if (((iVar11 != 0) && (local_368 < 8)) &&
                                                         (iVar11 = *(int *)((long)&local_360 +
                                                                           (long)local_368 * 4),
                                                         iVar11 != -1)) goto LAB_00150e04;
                                                    }
                                                    iVar11 = (int)local_378[2];
                                                    *(int *)(local_378 + 2) = iVar11 + 1;
                                                  }
LAB_00150e04:
                                                  iVar13 = (int)local_378[2];
                                                  *(int *)(local_378 + 2) = iVar13 + 1;
                                                  puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014ebf8;
                                                  uVar47 = 9;
                                                  *puVar22 = uVar48;
                                                  puVar22[2] = iVar13;
                                                  puVar22[3] = 9;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar12;
                                                  puVar22[7] = 9;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  puVar22[10] = iVar11;
                                                  local_360 = CONCAT44(local_360._4_4_,iVar13);
LAB_00150e40:
                                                  puVar22[0xb] = uVar47;
                                                  *(undefined8 *)(puVar22 + 0xc) = 0;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    iVar11 = strcmp(pcVar34,"nop");
                                                    if (iVar11 != 0) {
                                                      iVar11 = strcmp(pcVar34,"push");
                                                      if (iVar11 == 0) {
                                                        iVar11 = (int)local_310;
                                                        if ((int)local_310 == -1) {
                                                          iVar11 = (int)plVar16[2];
                                                          *(int *)(plVar16 + 2) = iVar11 + 1;
                                                        }
                                                        auVar49 = FUN_0014ccb0(puVar2,plVar16,8,
                                                                               uVar18);
                                                        if (auVar49._0_4_ == -1) goto LAB_0014ebf8;
                                                        iVar12 = (int)plVar16[2];
                                                        *(int *)(plVar16 + 2) = iVar12 + 1;
                                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2)
                                                        ;
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014ebf8;
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
                                                        if ((int)uVar36 < 0) {
                                                          if (bVar7) {
                                                            auVar49 = FUN_0014ccb0(puVar2,plVar16,
                                                                                   local_3f8,uVar18)
                                                            ;
                                                            uVar42 = auVar49._8_8_;
                                                            iVar11 = auVar49._0_4_;
                                                            uVar47 = auVar49._4_4_;
                                                            if (iVar11 == -1) goto LAB_0014ebf8;
                                                          }
                                                          else {
                                                            uVar47 = 4;
                                                            uVar42 = 0;
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                        }
                                                        else {
                                                          uVar38 = -(uVar38 >> 0x1f) &
                                                                   0xfffffffc00000000 | uVar38 << 2;
                                                          iVar11 = *(int *)((long)&local_320 +
                                                                           uVar38);
                                                          if (iVar11 == -1) {
                                                            uVar42 = 0;
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                          else {
                                                            uVar42 = 0;
                                                            uVar47 = *(undefined4 *)
                                                                      ((long)&local_2e0 + uVar38);
                                                          }
                                                        }
                                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2)
                                                        ;
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014ebf8;
                                                        *puVar22 = 0x16;
                                                        puVar22[0x12] = 2;
                                                        *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                        puVar22[6] = iVar12;
                                                        puVar22[7] = 5;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[10] = iVar11;
                                                        puVar22[0xb] = uVar47;
                                                        *(undefined8 *)(puVar22 + 0xc) = uVar42;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                      else {
                                                        iVar11 = strcmp(pcVar34,"pop");
                                                        if (iVar11 == 0) {
                                                          iVar11 = (int)local_310;
                                                          if ((int)local_310 == -1) {
                                                            iVar11 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar11 + 1;
                                                          }
                                                          if (-1 < (int)uVar36) {
                                                            iVar12 = (int)plVar16[2];
                                                            *(int *)(plVar16 + 2) = iVar12 + 1;
                                                            puVar22 = (undefined4 *)
                                                                      FUN_0014c000(puVar2);
                                                            if (puVar22 == (undefined4 *)0x0)
                                                            goto LAB_0014ebf8;
                                                            uVar38 = -(uVar38 >> 0x1f) &
                                                                     0xfffffffc00000000 |
                                                                     uVar38 << 2;
                                                            puVar22[0x12] = 1;
                                                            *(int *)((long)&local_320 + uVar38) =
                                                                 iVar12;
                                                            *(undefined4 *)
                                                             ((long)&local_2e0 + uVar38) = uVar47;
                                                            *puVar22 = 0x15;
                                                            puVar22[2] = iVar12;
                                                            puVar22[3] = uVar47;
                                                            *(undefined8 *)(puVar22 + 4) = 0;
                                                            puVar22[6] = iVar11;
                                                            puVar22[7] = 5;
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            *(undefined8 *)(puVar22 + 0x1c) = uVar18
                                                            ;
                                                          }
                                                          auVar49 = FUN_0014ccb0(puVar2,plVar16,8,
                                                                                 uVar18);
                                                          if (auVar49._0_4_ == -1)
                                                          goto LAB_0014ebf8;
                                                          iVar12 = (int)plVar16[2];
                                                          *(int *)(plVar16 + 2) = iVar12 + 1;
                                                          puVar22 = (undefined4 *)
                                                                    FUN_0014c000(puVar2);
                                                          if (puVar22 == (undefined4 *)0x0)
                                                          goto LAB_0014ebf8;
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
                                                          iVar11 = strcmp(pcVar34,"xchg");
                                                          if (iVar11 == 0) {
                                                            if (-1 < (int)(uVar36 | uVar30)) {
                                                              uVar38 = -(uVar38 >> 0x1f) &
                                                                       0xfffffffc00000000 |
                                                                       uVar38 << 2;
                                                              iVar12 = (int)plVar16[2];
                                                              iVar13 = *(int *)((long)&local_320 +
                                                                               uVar38);
                                                              iVar11 = iVar12 + 1;
                                                              if (iVar13 == -1) {
                                                                *(int *)(plVar16 + 2) = iVar11;
                                                              }
                                                              else {
                                                                iVar11 = iVar12;
                                                                iVar12 = iVar13;
                                                                uVar37 = *(undefined4 *)
                                                                          ((long)&local_2e0 + uVar38
                                                                          );
                                                              }
                                                              *(int *)(plVar16 + 2) = iVar11 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        FUN_0014c000(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014ebf8;
                                                              uVar38 = -(uVar41 >> 0x1f) &
                                                                       0xfffffffc00000000 |
                                                                       uVar41 << 2;
                                                              puVar22[2] = iVar11;
                                                              iVar15 = (int)plVar16[2];
                                                              *puVar22 = 0;
                                                              puVar22[3] = uVar47;
                                                              iVar13 = iVar15 + 1;
                                                              iVar14 = *(int *)((long)&local_320 +
                                                                               uVar38);
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar12;
                                                              puVar22[7] = uVar37;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                              if (iVar14 == -1) {
                                                                *(int *)(plVar16 + 2) = iVar13;
                                                                uVar37 = uVar48;
                                                              }
                                                              else {
                                                                iVar13 = iVar15;
                                                                iVar15 = iVar14;
                                                                uVar37 = *(undefined4 *)
                                                                          ((long)&local_2e0 + uVar38
                                                                          );
                                                              }
                                                              *(int *)(plVar16 + 2) = iVar13 + 1;
                                                              puVar22 = (undefined4 *)
                                                                        FUN_0014c000(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014ebf8;
                                                              iVar12 = (int)plVar16[2];
                                                              *puVar22 = 0;
                                                              puVar22[2] = iVar13;
                                                              puVar22[3] = uVar47;
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar15;
                                                              puVar22[7] = uVar37;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                              *(int *)(plVar16 + 2) = iVar12 + 1;
                                                              *(int *)((long)&local_320 +
                                                                      (long)(int)uVar36 * 4) =
                                                                   iVar13;
                                                              *(undefined4 *)
                                                               ((long)&local_2e0 +
                                                               (long)(int)uVar36 * 4) = uVar47;
                                                              puVar22 = (undefined4 *)
                                                                        FUN_0014c000(puVar2);
                                                              if (puVar22 == (undefined4 *)0x0)
                                                              goto LAB_0014ebf8;
                                                              *puVar22 = 0;
                                                              puVar22[2] = iVar12;
                                                              *(undefined4 *)
                                                               ((long)&local_2e0 +
                                                               (long)(int)uVar30 * 4) = uVar48;
                                                              puVar22[3] = uVar48;
                                                              *(int *)((long)&local_320 +
                                                                      (long)(int)uVar30 * 4) =
                                                                   iVar12;
                                                              *(undefined8 *)(puVar22 + 4) = 0;
                                                              puVar22[6] = iVar11;
                                                              puVar22[7] = uVar47;
                                                              *(undefined8 *)(puVar22 + 8) = 0;
                                                              puVar22[0x12] = 1;
                                                              *(undefined8 *)(puVar22 + 0x1c) =
                                                                   uVar18;
                                                            }
                                                          }
                                                          else {
                                                            iVar11 = strcmp(pcVar34,"cdq");
                                                            iVar12 = strcmp(pcVar34,"cqo");
                                                            if (iVar11 == 0) {
                                                              uVar42 = 0x3f;
                                                              if (iVar12 != 0) {
                                                                uVar42 = 0x1f;
                                                              }
                                                              uVar47 = 4;
                                                              if (iVar12 != 0) {
                                                                uVar47 = 3;
                                                              }
                                                            }
                                                            else if (iVar12 == 0) {
                                                              uVar42 = 0x3f;
                                                              uVar47 = 4;
                                                            }
                                                            else {
                                                              iVar11 = strcmp(pcVar34,"cwd");
                                                              if (iVar11 != 0) {
                                                                if (((cVar10 != '\0') &&
                                                                    (iVar11 = strcmp(pcVar34,"hint")
                                                                    , iVar11 != 0)) &&
                                                                   ((iVar11 = strcmp(pcVar34,"pause"
                                                                                    ), iVar11 != 0
                                                                    && (((iVar11 = strcmp(pcVar34,
                                                  "endbr64"), iVar11 != 0 &&
                                                  (iVar11 = strcmp(pcVar34,"endbr32"), iVar11 != 0))
                                                  && (puVar22 = (undefined4 *)FUN_0014c000(puVar2),
                                                     puVar22 != (undefined4 *)0x0)))))) {
                                                    *puVar22 = 0x1d;
                                                    puVar22[0x12] = 0;
                                                    *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                    *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                    strncpy((char *)(puVar22 + 0x1e),pcVar34,0xf);
                                                    *(undefined1 *)((long)puVar22 + 0x87) = 0;
                                                  }
                                                  goto LAB_0014e30c;
                                                  }
                                                  uVar42 = 0xf;
                                                  uVar47 = 2;
                                                  }
                                                  iVar11 = (int)local_320;
                                                  if ((int)local_320 == -1) {
                                                    iVar11 = (int)plVar16[2];
                                                    *(int *)(plVar16 + 2) = iVar11 + 1;
                                                  }
                                                  auVar49 = FUN_0014ccb0(puVar2,plVar16,uVar42,
                                                                         uVar18);
                                                  if (auVar49._0_4_ == -1) goto LAB_0014ebf8;
                                                  iVar12 = (int)plVar16[2];
                                                  *(int *)(plVar16 + 2) = iVar12 + 1;
                                                  puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                  if (puVar22 == (undefined4 *)0x0)
                                                  goto LAB_0014ebf8;
                                                  *puVar22 = 10;
                                                  puVar22[2] = iVar12;
                                                  puVar22[3] = uVar47;
                                                  *(undefined8 *)(puVar22 + 4) = 0;
                                                  puVar22[6] = iVar11;
                                                  puVar22[7] = uVar47;
                                                  *(undefined8 *)(puVar22 + 8) = 0;
                                                  *(undefined1 (*) [16])(puVar22 + 10) = auVar49;
                                                  puVar22[0x12] = 2;
                                                  *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                  uStack_318 = CONCAT44(uStack_318._4_4_,iVar12);
                                                  uStack_2d8 = CONCAT44(uStack_2d8._4_4_,uVar47);
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    iVar12 = iVar11;
                                                    FUN_0014c8f0(acStack_159 + 1,&local_370);
                                                    if (iVar12 == 2) {
                                                      FUN_0014c8f0(acStack_159 + 0x41,&local_368);
                                                      iVar12 = local_368;
                                                      uVar39 = local_370;
                                                      if (-1 < (int)local_370) goto LAB_00150cd4;
                                                      if (local_368 < 0) goto LAB_0014ff78;
                                                      iVar11 = strcmp(pcVar34,"movq");
                                                      if ((iVar11 != 0) &&
                                                         (iVar11 = strcmp(pcVar34,"movd"),
                                                         iVar11 != 0)) goto LAB_00150f1c;
                                                      plVar6 = local_378;
                                                      if ((int)uVar36 < 0) {
                                                        iVar11 = FUN_0014c870(acStack_159 + 1);
                                                        if (iVar11 != 0) {
                                                          puVar22 = (undefined4 *)
                                                                    FUN_0014c000(puVar2);
                                                          if (puVar22 != (undefined4 *)0x0) {
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            uVar42 = DAT_0020c568;
                                                            *puVar22 = 0x16;
                                                            *(undefined8 *)(puVar22 + 2) =
                                                                 0xffffffff;
                                                            *(undefined8 *)(puVar22 + 6) = uVar42;
                                                            iVar11 = *(int *)((long)&local_340 +
                                                                             (long)iVar12 * 4);
                                                            if (iVar11 == -1) {
                                                              iVar11 = (int)local_378[2];
                                                              *(int *)(local_378 + 2) = iVar11 + 1;
                                                              uVar47 = 0xd;
                                                            }
                                                            else {
                                                              uVar47 = 0xd;
                                                            }
                                                            goto LAB_00150264;
                                                          }
                                                          goto LAB_0014ebf8;
                                                        }
                                                      }
                                                      else {
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2)
                                                        ;
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014ebf8;
                                                        *puVar22 = 0;
                                                        iVar12 = *(int *)((long)&local_340 +
                                                                         (long)iVar12 * 4);
                                                        if (iVar12 == -1) {
                                                          iVar12 = (int)plVar6[2];
                                                          *(int *)(plVar6 + 2) = iVar12 + 1;
                                                        }
                                                        uVar38 = -(uVar38 >> 0x1f) &
                                                                 0xfffffffc00000000 | uVar38 << 2;
                                                        puVar22[6] = iVar12;
                                                        puVar22[7] = 0xd;
                                                        *(int *)((long)&local_320 + uVar38) = iVar11
                                                        ;
                                                        *(undefined4 *)((long)&local_2e0 + uVar38) =
                                                             uVar47;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = uVar47;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                    }
                                                    else {
                                                      if ((int)local_370 < 0) goto LAB_0014ff78;
LAB_00150cd4:
                                                      uVar39 = local_370;
                                                      iVar11 = strcmp(pcVar34,"movq");
                                                      if ((iVar11 == 0) ||
                                                         (iVar11 = strcmp(pcVar34,"movd"),
                                                         iVar11 == 0)) {
                                                        plVar6 = local_378;
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                        puVar22 = (undefined4 *)FUN_0014c000(puVar2)
                                                        ;
                                                        if (puVar22 == (undefined4 *)0x0)
                                                        goto LAB_0014ebf8;
                                                        if (local_368 < 0) {
                                                          if ((int)uVar30 < 0) {
                                                            uVar48 = 5;
                                                            iVar12 = -1;
                                                            *puVar22 = 0x15;
                                                          }
                                                          else {
                                                            *puVar22 = 0;
                                                            iVar12 = *(int *)((long)&local_320 +
                                                                             (long)(int)uVar30 * 4);
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
                                                          uVar48 = 0xd;
                                                        }
                                                        *(int *)((long)&local_340 +
                                                                (long)(int)uVar39 * 4) = iVar11;
                                                        puVar22[6] = iVar12;
                                                        puVar22[2] = iVar11;
                                                        puVar22[3] = 0xd;
                                                        *(undefined8 *)(puVar22 + 4) = 0;
                                                        puVar22[7] = uVar48;
                                                        *(undefined8 *)(puVar22 + 8) = 0;
                                                        puVar22[0x12] = 1;
                                                        *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                      }
                                                      else {
LAB_00150f1c:
                                                        iVar11 = strncmp(pcVar34,"padd",4);
                                                        if (iVar11 == 0) {
                                                          uVar47 = 2;
                                                        }
                                                        else {
                                                          iVar11 = strncmp(pcVar34,"psub",4);
                                                          if (iVar11 == 0) {
                                                            uVar47 = 3;
                                                          }
                                                          else {
                                                            iVar11 = strcmp(pcVar34,"pand");
                                                            if (iVar11 == 0) {
                                                              uVar47 = 6;
                                                            }
                                                            else {
                                                              iVar11 = strcmp(pcVar34,"por");
                                                              if (iVar11 == 0) {
                                                                uVar47 = 7;
                                                              }
                                                              else {
                                                                iVar11 = strcmp(pcVar34,"pxor");
                                                                if (iVar11 == 0) {
                                                                  uVar47 = 8;
                                                                }
                                                                else {
                                                                  iVar11 = strncmp(pcVar34,"pmul",4)
                                                                  ;
                                                                  if (iVar11 != 0)
                                                                  goto LAB_0014e30c;
                                                                  uVar47 = 4;
                                                                }
                                                              }
                                                            }
                                                          }
                                                        }
                                                        if (-1 < (int)uVar39) {
                                                          iVar11 = (int)local_378[2];
                                                          iVar12 = *(int *)((long)&local_340 +
                                                                           (long)(int)uVar39 * 4);
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
                                                                    FUN_0014c000(puVar2);
                                                          if (puVar22 != (undefined4 *)0x0) {
                                                            *(int *)((long)&local_340 +
                                                                    (long)(int)uVar39 * 4) = iVar15;
                                                            *puVar22 = uVar47;
                                                            uVar47 = 0xd;
                                                            puVar22[2] = iVar15;
                                                            puVar22[3] = 0xd;
                                                            *(undefined8 *)(puVar22 + 4) = 0;
                                                            puVar22[6] = iVar12;
                                                            puVar22[7] = 0xd;
                                                            *(undefined8 *)(puVar22 + 8) = 0;
                                                            puVar22[10] = iVar11;
                                                            goto LAB_00150e40;
                                                          }
                                                          goto LAB_0014ebf8;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                }
                                                else {
                                                  iVar12 = 8 - uVar39;
                                                  local_370 = 0xffffffff;
                                                  local_368 = -1;
                                                  FUN_0014ca70(acStack_159 + 1,&local_370);
                                                  if (iVar11 == 2) {
                                                    FUN_0014ca70(acStack_159 + 0x41,&local_368);
                                                  }
                                                  iVar15 = strncmp(pcVar34,"mov",3);
                                                  iVar13 = local_368;
                                                  uVar39 = local_370;
                                                  plVar6 = local_378;
                                                  if (iVar15 == 0) {
                                                    uVar38 = (ulong)local_370;
                                                    if ((int)local_370 < 0) {
                                                      if (local_368 < 0) goto LAB_0014e30c;
                                                      puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                      if (puVar22 == (undefined4 *)0x0)
                                                      goto LAB_0014ebf8;
                                                      *(undefined8 *)(puVar22 + 8) = 0;
                                                      uVar42 = DAT_0020c568;
                                                      *puVar22 = 0x16;
                                                      iVar11 = *(int *)((long)&local_2a0 +
                                                                       (long)iVar13 * 4);
                                                      *(undefined8 *)(puVar22 + 2) = 0xffffffff;
                                                      *(undefined8 *)(puVar22 + 6) = uVar42;
                                                      if (iVar11 == -1) {
                                                        iVar11 = (int)local_378[2];
                                                        *(int *)(local_378 + 2) = iVar11 + 1;
                                                      }
                                                      puVar22[10] = iVar11;
                                                      puVar22[0xb] = iVar12;
                                                      *(undefined8 *)(puVar22 + 0xc) = 0;
                                                      puVar22[0x12] = 2;
                                                      *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                    }
                                                    else {
                                                      iVar11 = (int)local_378[2];
                                                      *(int *)(local_378 + 2) = iVar11 + 1;
                                                      puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                      if (puVar22 == (undefined4 *)0x0)
                                                      goto LAB_0014ebf8;
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
                                                      uVar38 = -(ulong)(uVar39 >> 0x1f) &
                                                               0xfffffffc00000000 | uVar38 << 2;
                                                      puVar22[2] = iVar11;
                                                      puVar22[3] = iVar12;
                                                      *(undefined8 *)(puVar22 + 4) = 0;
                                                      *(int *)((long)&local_2a0 + uVar38) = iVar11;
                                                      *(int *)((long)&local_260 + uVar38) = iVar12;
                                                      puVar22[6] = iVar13;
                                                      puVar22[7] = iVar15;
                                                      *(undefined8 *)(puVar22 + 8) = 0;
                                                      puVar22[0x12] = 1;
                                                      *(undefined8 *)(puVar22 + 0x1c) = uVar18;
                                                    }
                                                  }
                                                  else {
                                                    iVar13 = strncmp(pcVar34,"add",3);
                                                    if (iVar13 == 0) {
                                                      uVar47 = 2;
                                                    }
                                                    else {
                                                      iVar13 = strncmp(pcVar34,"sub",3);
                                                      if (iVar13 == 0) {
                                                        uVar47 = 3;
                                                      }
                                                      else {
                                                        iVar13 = strncmp(pcVar34,"mul",3);
                                                        if (iVar13 == 0) {
                                                          uVar47 = 4;
                                                        }
                                                        else {
                                                          iVar13 = strncmp(pcVar34,"div",3);
                                                          if (iVar13 != 0) {
                                                            cVar10 = *(char *)(lVar32 + 0x20);
                                                            goto LAB_0014ff5c;
                                                          }
                                                          uVar47 = 5;
                                                        }
                                                      }
                                                    }
                                                    if (-1 < (int)local_370) {
                                                      lVar32 = (long)(int)local_370;
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
                                                      puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                                      if (puVar22 == (undefined4 *)0x0)
                                                      goto LAB_0014ebf8;
                                                      *puVar22 = uVar47;
                                                      *(int *)((long)&local_2a0 + lVar32 * 4) =
                                                           iVar14;
                                                      *(int *)((long)&local_260 + lVar32 * 4) =
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
                                            goto LAB_0014e30c;
                                          }
                                          puVar22 = (undefined4 *)FUN_0014c000(puVar2);
                                          if (puVar22 == (undefined4 *)0x0) goto LAB_0014ebf8;
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
          pcVar28 = (char *)(lVar32 + 0x60);
          iVar11 = 0;
          pcVar19 = pcVar28;
          do {
            while (cVar10 != '[') {
              if (cVar10 == ']') {
                iVar11 = iVar11 + -1;
              }
              else if (cVar10 == ',' && iVar11 == 0) {
                sVar25 = (long)pcVar19 - (long)pcVar28;
                if (0x3f < sVar25) {
                  sVar25 = 0x3f;
                }
                memcpy(acStack_159 + 1,pcVar28,sVar25);
                (acStack_159 + 1)[sVar25] = '\0';
                snprintf(acStack_159 + 0x41,0x40,"%s",pcVar19 + 1);
                iVar11 = 2;
                cVar10 = acStack_159[1];
                cVar35 = acStack_159[0x41];
                goto joined_r0x0014e884;
              }
              pcVar19 = pcVar19 + 1;
              cVar10 = *pcVar19;
              if (cVar10 == '\0') goto LAB_0014e5f4;
            }
            pcVar19 = pcVar19 + 1;
            cVar10 = *pcVar19;
            iVar11 = iVar11 + 1;
          } while (cVar10 != '\0');
LAB_0014e5f4:
          snprintf(acStack_159 + 1,0x40,"%s",pcVar28);
          iVar11 = 1;
          cVar10 = acStack_159[1];
          cVar35 = acStack_159[0x41];
joined_r0x0014e884:
          acStack_159[1] = cVar10;
          acStack_159[0x41] = cVar35;
          if (cVar10 == '\0') {
LAB_0014e628:
            if (cVar35 == '\0') goto LAB_0014eb80;
LAB_0014e62c:
            pcVar28 = acStack_159 + 0x41;
            sVar25 = strlen(pcVar28);
            pcVar19 = pcVar28 + (sVar25 - 1);
            if (pcVar28 < pcVar28 + (sVar25 - 1)) {
              do {
                cVar35 = acStack_159[0x41];
                if (*pcVar19 != ' ') break;
                pcVar20 = pcVar19 + -1;
                *pcVar19 = '\0';
                pcVar19 = pcVar20;
              } while (pcVar20 != pcVar28);
            }
            pcVar19 = pcVar28;
            if (cVar35 == ' ') {
              do {
                pcVar19 = pcVar19 + 1;
              } while (*pcVar19 == ' ');
              if (pcVar19 != pcVar28) {
                sVar25 = strlen(pcVar19);
                __memmove_chk(pcVar28,pcVar19,sVar25 + 1,0x40);
              }
            }
            if (cVar10 != ' ') goto LAB_0014eb80;
LAB_0014e6c0:
            pcVar28 = acStack_159 + 1;
            do {
              pcVar28 = pcVar28 + 1;
            } while (*pcVar28 == ' ');
          }
          else {
            pcVar19 = acStack_159 + 1;
            sVar25 = strlen(pcVar19);
            pcVar28 = pcVar19 + (sVar25 - 1);
            if (pcVar19 < pcVar19 + (sVar25 - 1)) {
              do {
                cVar10 = acStack_159[1];
                if (*pcVar28 != ' ') break;
                pcVar20 = pcVar28 + -1;
                *pcVar28 = '\0';
                pcVar28 = pcVar20;
                cVar10 = acStack_159[1];
              } while (pcVar20 != pcVar19);
            }
            pcVar28 = pcVar19;
            if (cVar10 != ' ') goto LAB_0014e628;
            do {
              pcVar28 = pcVar28 + 1;
            } while (*pcVar28 == ' ');
            if (pcVar28 == pcVar19) {
              if (cVar35 != '\0') goto LAB_0014e62c;
              goto LAB_0014e6c0;
            }
            sVar25 = strlen(pcVar28);
            __memmove_chk(pcVar19,pcVar28,sVar25 + 1,0x40);
            cVar10 = acStack_159[1];
            if (cVar35 != '\0') goto LAB_0014e62c;
            if (acStack_159[1] == ' ') goto LAB_0014e6c0;
LAB_0014eb80:
            pcVar28 = acStack_159 + 1;
          }
          ppuVar46 = &PTR_DAT_005df888;
          iVar12 = 0;
          ppuVar45 = ppuVar46;
          do {
            iVar13 = strcmp(*ppuVar45,pcVar28);
            cVar10 = acStack_159[0x41];
            if (iVar13 == 0) {
              uVar38 = (ulong)(uint)(&DAT_005df890)[(long)iVar12 * 4];
              uVar47 = (&DAT_005df894)[(long)iVar12 * 4];
              goto LAB_0014e71c;
            }
            iVar12 = iVar12 + 1;
            ppuVar45 = ppuVar45 + 2;
          } while (iVar12 != 0x30);
          uVar47 = 4;
          uVar38 = 0xffffffff;
LAB_0014e71c:
          if (iVar11 == 2) {
            pcVar19 = acStack_159 + 0x41;
            pcVar28 = pcVar19;
            cVar35 = acStack_159[0x41];
            while (cVar35 == ' ') {
              pcVar28 = pcVar28 + 1;
              cVar35 = *pcVar28;
            }
            iVar12 = 0;
            do {
              iVar13 = strcmp(*ppuVar46,pcVar28);
              iVar11 = 2;
              if (iVar13 == 0) {
                local_3f8 = 0;
                uVar41 = (ulong)(uint)(&DAT_005df890)[(long)iVar12 * 4];
                uVar48 = (&DAT_005df894)[(long)iVar12 * 4];
                bVar7 = false;
                goto LAB_0014e7a4;
              }
              iVar12 = iVar12 + 1;
              ppuVar46 = ppuVar46 + 2;
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
              iVar12 = __isoc99_sscanf(pcVar19,&DAT_001fa658,&local_368);
              if (iVar12 == 1) {
                local_3f8 = CONCAT44(uStack_364,local_368);
                bVar7 = true;
              }
              else {
                bVar7 = false;
                local_3f8 = 0;
              }
            }
            uVar48 = 4;
            uVar41 = 0xffffffff;
          }
          else {
            uVar48 = 4;
            uVar41 = 0xffffffff;
            bVar7 = false;
            local_3f8 = 0;
            iVar11 = 1;
          }
LAB_0014e7a4:
          iVar12 = strcmp(pcVar34,"mov");
          if (iVar12 != 0) goto LAB_0014e1cc;
          uVar36 = (uint)uVar38;
          plVar6 = local_378;
joined_r0x0014e7b8:
          iVar11 = (int)uVar41;
          local_378 = plVar6;
          if (-1 < (int)uVar36) {
            uVar36 = *(uint *)(puVar2 + 2);
            uVar30 = *(uint *)((long)puVar2 + 0x14);
            iVar12 = (int)plVar6[2];
            pvVar17 = (void *)puVar2[1];
            *(int *)(plVar6 + 2) = iVar12 + 1;
            if (uVar30 <= uVar36) {
              if (uVar30 == 0) {
                sVar25 = 0x900;
                uVar30 = 0x10;
              }
              else {
                uVar30 = uVar30 << 1;
                sVar25 = (ulong)uVar30 * 0x90;
              }
              pvVar17 = realloc(pvVar17,sVar25);
              if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
              uVar36 = *(uint *)(puVar2 + 2);
              puVar2[1] = pvVar17;
              *(uint *)((long)puVar2 + 0x14) = uVar30;
            }
            *(uint *)(puVar2 + 2) = uVar36 + 1;
            puVar44 = (undefined8 *)((long)pvVar17 + (ulong)uVar36 * 0x90);
            pcVar28 = acStack_159 + 0x41;
            puVar44[1] = 0;
            *puVar44 = 0;
            puVar44[3] = 0;
            puVar44[2] = 0;
            *(int *)(puVar44 + 1) = iVar12;
            *(undefined4 *)((long)puVar44 + 0xc) = uVar47;
            puVar44[5] = 0;
            puVar44[4] = 0;
            puVar44[7] = 0;
            puVar44[6] = 0;
            puVar44[9] = 0;
            puVar44[8] = 0;
            puVar44[0xb] = 0;
            puVar44[10] = 0;
            puVar44[0xd] = 0;
            puVar44[0xc] = 0;
            puVar44[0xf] = 0;
            puVar44[0xe] = 0;
            puVar44[0x11] = 0;
            puVar44[0x10] = 0;
            cVar10 = acStack_159[0x41];
            while (cVar10 == ' ') {
              pcVar28 = pcVar28 + 1;
              cVar10 = *pcVar28;
            }
            if ((((cVar10 == '[') || (pcVar19 = strstr(pcVar28,"ptr"), pcVar19 != (char *)0x0)) ||
                (pcVar28 = strchr(pcVar28,0x5b), pcVar28 != (char *)0x0)) &&
               (iVar13 = strcmp(pcVar34,"lea"), iVar13 != 0)) {
              *(undefined4 *)puVar44 = 0x15;
              uVar42 = DAT_0020c568;
              *(undefined4 *)(puVar44 + 9) = 1;
              puVar44[3] = uVar42;
            }
            else if (iVar11 < 0) {
              if (bVar7) {
                *(undefined4 *)puVar44 = 1;
                puVar44[2] = local_3f8;
              }
              else {
                *(undefined4 *)puVar44 = 1;
              }
            }
            else {
              iVar11 = *(int *)((long)&local_320 + (long)iVar11 * 4);
              if (iVar11 == -1) {
                iVar11 = (int)plVar6[2];
                *(int *)(plVar6 + 2) = iVar11 + 1;
              }
              *(int *)(puVar44 + 3) = iVar11;
              *(undefined4 *)((long)puVar44 + 0x1c) = uVar48;
              puVar44[4] = 0;
              *(undefined4 *)(puVar44 + 9) = 1;
            }
            puVar44[0xe] = uVar18;
            *(int *)((long)&local_320 + (long)(int)uVar38 * 4) = iVar12;
            *(undefined4 *)((long)&local_2e0 + (long)(int)uVar38 * 4) = uVar47;
            goto LAB_0014e30c;
          }
          pcVar34 = acStack_159 + 1;
          cVar10 = acStack_159[1];
          while (cVar10 == ' ') {
            pcVar34 = pcVar34 + 1;
            cVar10 = *pcVar34;
          }
          if (cVar10 != '[') goto LAB_0014e46c;
LAB_0014e480:
          uVar36 = *(uint *)(puVar2 + 2);
          uVar30 = *(uint *)((long)puVar2 + 0x14);
          pvVar17 = (void *)puVar2[1];
          if (uVar30 <= uVar36) {
            if (uVar30 == 0) {
              sVar25 = 0x900;
              uVar30 = 0x10;
            }
            else {
              uVar30 = uVar30 << 1;
              sVar25 = (ulong)uVar30 * 0x90;
            }
            pvVar17 = realloc(pvVar17,sVar25);
            if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
            uVar36 = *(uint *)(puVar2 + 2);
            puVar2[1] = pvVar17;
            *(uint *)((long)puVar2 + 0x14) = uVar30;
          }
          *(uint *)(puVar2 + 2) = uVar36 + 1;
          puVar44 = (undefined8 *)((long)pvVar17 + (ulong)uVar36 * 0x90);
          *(undefined8 *)((long)puVar44 + 0x6c) = 0;
          *(undefined8 *)((long)puVar44 + 100) = 0;
          *(undefined8 *)((long)puVar44 + 0x7c) = 0;
          *(undefined8 *)((long)puVar44 + 0x74) = 0;
          *(undefined8 *)((long)puVar44 + 0xc) = 0;
          *(undefined8 *)((long)puVar44 + 4) = 0;
          *(undefined8 *)((long)puVar44 + 0x1c) = 0;
          *(undefined8 *)((long)puVar44 + 0x14) = 0;
          *(undefined8 *)((long)puVar44 + 0x2c) = 0;
          *(undefined8 *)((long)puVar44 + 0x24) = 0;
          *(undefined8 *)((long)puVar44 + 0x3c) = 0;
          *(undefined8 *)((long)puVar44 + 0x34) = 0;
          *(undefined8 *)((long)puVar44 + 0x4c) = 0;
          *(undefined8 *)((long)puVar44 + 0x44) = 0;
          *(undefined8 *)((long)puVar44 + 0x5c) = 0;
          *(undefined8 *)((long)puVar44 + 0x54) = 0;
          puVar44[0x11] = 0;
          puVar44[0x10] = 0;
          *(undefined4 *)((long)pvVar17 + (ulong)uVar36 * 0x90) = 0x16;
          *(undefined4 *)(puVar44 + 1) = 0xffffffff;
          puVar44[3] = uVar9;
          if ((iVar11 < 0) || (iVar11 = *(int *)((long)&local_320 + (long)iVar11 * 4), iVar11 == -1)
             ) {
            if (bVar7) {
              auVar49 = FUN_0014ccb0(puVar2,local_378,local_3f8,uVar18);
              if (auVar49._0_4_ == -1) goto LAB_0014ebf8;
              uVar36 = *(uint *)(puVar2 + 2);
              uVar30 = *(uint *)((long)puVar2 + 0x14);
              pvVar17 = (void *)puVar2[1];
              if (uVar30 <= uVar36) {
                if (uVar30 == 0) {
                  sVar25 = 0x900;
                  uVar30 = 0x10;
                }
                else {
                  uVar30 = uVar30 << 1;
                  sVar25 = (ulong)uVar30 * 0x90;
                }
                pvVar17 = realloc(pvVar17,sVar25);
                if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
                uVar36 = *(uint *)(puVar2 + 2);
                puVar2[1] = pvVar17;
                *(uint *)((long)puVar2 + 0x14) = uVar30;
              }
              *(uint *)(puVar2 + 2) = uVar36 + 1;
              uVar42 = DAT_0020c568;
              puVar44 = (undefined8 *)((long)pvVar17 + (ulong)uVar36 * 0x90);
              puVar44[1] = 0;
              *puVar44 = 0;
              puVar44[3] = 0;
              puVar44[2] = 0;
              puVar44[5] = 0;
              puVar44[4] = 0;
              puVar44[7] = 0;
              puVar44[6] = 0;
              puVar44[9] = 0;
              puVar44[8] = 0;
              puVar44[0xb] = 0;
              puVar44[10] = 0;
              puVar44[0xd] = 0;
              puVar44[0xc] = 0;
              puVar44[0xf] = 0;
              puVar44[0xe] = 0;
              puVar44[0x11] = 0;
              puVar44[0x10] = 0;
              *(undefined4 *)((long)pvVar17 + (ulong)uVar36 * 0x90) = 0x16;
              *(undefined4 *)(puVar44 + 1) = 0xffffffff;
              puVar44[3] = uVar42;
              *(undefined1 (*) [16])(puVar44 + 5) = auVar49;
              *(undefined4 *)(puVar44 + 9) = 2;
            }
            else {
              *(undefined4 *)(puVar44 + 9) = 1;
            }
          }
          else {
            *(int *)(puVar44 + 5) = iVar11;
            *(undefined4 *)((long)puVar44 + 0x2c) = uVar48;
          }
          puVar44[0xe] = uVar18;
        }
LAB_0014e30c:
        lVar31 = lVar31 + 1;
        if (*(uint *)(lVar1 + 0x18) <= (uint)lVar31) goto code_r0x0014e31c;
        goto LAB_0014e168;
      }
      uStack_318._0_4_ = -1;
      uStack_2f8._0_4_ = -1;
      local_300._4_4_ = -1;
      local_308._4_4_ = -1;
      local_310._0_4_ = -1;
      uStack_318._4_4_ = -1;
      local_310._4_4_ = -1;
      local_308._0_4_ = -1;
      local_300._0_4_ = -1;
      uStack_2f8._4_4_ = -1;
      local_2f0._0_4_ = -1;
      local_2f0._4_4_ = -1;
      local_2e8._0_4_ = -1;
      local_2e8._4_4_ = -1;
      uVar26 = 0;
      goto LAB_0014e364;
    }
LAB_0014ee90:
    uVar30 = *(uint *)(param_1 + 3);
    lVar40 = 0;
    uVar36 = 0;
    if (uVar30 != 0) {
      do {
        uVar39 = *(uint *)(param_1[2] + lVar40 + 4);
        if (uVar39 != 0xffffffff) {
          uVar4 = *(uint *)(param_1[2] + lVar40);
          uVar5 = uVar39;
          if (uVar39 < uVar4) {
            uVar5 = uVar4;
          }
          if (uVar5 < *(uint *)(plVar16 + 1)) {
            lVar43 = *plVar16;
            lVar32 = (ulong)uVar39 * 0x50;
            lVar1 = lVar43 + (ulong)uVar4 * 0x50;
            lVar31 = lVar43 + lVar32;
            uVar39 = *(uint *)(lVar1 + 0x30);
            piVar21 = *(int **)(lVar1 + 0x28);
            if (uVar39 == 0) {
              sVar25 = 4;
            }
            else {
              piVar27 = piVar21;
              do {
                if (*piVar27 == *(int *)(lVar43 + lVar32)) goto LAB_0014eeb4;
                piVar27 = piVar27 + 1;
              } while (piVar21 + uVar39 != piVar27);
              sVar25 = (ulong)(uVar39 + 1) << 2;
            }
            pvVar17 = realloc(piVar21,sVar25);
            if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
            uVar30 = *(uint *)(lVar1 + 0x30);
            uVar47 = *(undefined4 *)(lVar43 + lVar32);
            *(void **)(lVar1 + 0x28) = pvVar17;
            *(uint *)(lVar1 + 0x30) = uVar30 + 1;
            *(undefined4 *)((long)pvVar17 + (ulong)uVar30 * 4) = uVar47;
            pvVar17 = realloc(*(void **)(lVar31 + 0x18),(ulong)(*(int *)(lVar31 + 0x20) + 1) << 2);
            if (pvVar17 == (void *)0x0) goto LAB_0014ebf8;
            uVar30 = *(uint *)(lVar31 + 0x20);
            uVar47 = *(undefined4 *)(lVar43 + (ulong)uVar4 * 0x50);
            *(void **)(lVar31 + 0x18) = pvVar17;
            *(uint *)(lVar31 + 0x20) = uVar30 + 1;
            *(undefined4 *)((long)pvVar17 + (ulong)uVar30 * 4) = uVar47;
            uVar30 = *(uint *)(param_1 + 3);
          }
        }
LAB_0014eeb4:
        uVar36 = uVar36 + 1;
        lVar40 = lVar40 + 0xc;
      } while (uVar36 < uVar30);
    }
    goto LAB_0014ec2c;
  }
LAB_0014ec28:
  plVar16 = (long *)0x0;
LAB_0014ec2c:
  if (local_98 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_98 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return plVar16;
code_r0x0014e31c:
  uVar26 = (ulong)((int)local_320 != -1);
  if (local_320._4_4_ != -1) {
    uVar26 = uVar26 | 2;
  }
LAB_0014e364:
  puVar2[9] = uVar26;
  if ((int)uStack_318 != -1) {
    uVar26 = uVar26 | 4;
    puVar2[9] = uVar26;
  }
  if (uStack_318._4_4_ != -1) {
    uVar26 = uVar26 | 8;
    puVar2[9] = uVar26;
  }
  if ((int)local_310 != -1) {
    uVar26 = uVar26 | 0x10;
    puVar2[9] = uVar26;
  }
  if (local_310._4_4_ != -1) {
    uVar26 = uVar26 | 0x20;
    puVar2[9] = uVar26;
  }
  if ((int)local_308 != -1) {
    uVar26 = uVar26 | 0x40;
    puVar2[9] = uVar26;
  }
  if (local_308._4_4_ != -1) {
    uVar26 = uVar26 | 0x80;
    puVar2[9] = uVar26;
  }
  if ((int)local_300 != -1) {
    uVar26 = uVar26 | 0x100;
    puVar2[9] = uVar26;
  }
  if (local_300._4_4_ != -1) {
    uVar26 = uVar26 | 0x200;
    puVar2[9] = uVar26;
  }
  if ((int)uStack_2f8 != -1) {
    uVar26 = uVar26 | 0x400;
    puVar2[9] = uVar26;
  }
  if (uStack_2f8._4_4_ != -1) {
    uVar26 = uVar26 | 0x800;
    puVar2[9] = uVar26;
  }
  if ((int)local_2f0 != -1) {
    uVar26 = uVar26 | 0x1000;
    puVar2[9] = uVar26;
  }
  if (local_2f0._4_4_ != -1) {
    uVar26 = uVar26 | 0x2000;
    puVar2[9] = uVar26;
  }
  if ((int)local_2e8 != -1) {
    uVar26 = uVar26 | 0x4000;
    puVar2[9] = uVar26;
  }
  uVar36 = *(uint *)(param_1 + 1);
  if (local_2e8._4_4_ != -1) {
    puVar2[9] = uVar26 | 0x8000;
  }
  iVar11 = (int)lVar40;
  lVar40 = lVar40 + 1;
  if (uVar36 <= iVar11 + 1U) goto LAB_0014ee90;
  goto LAB_0014e074;
LAB_0014ebf8:
  FUN_0014deb0(&local_378);
  goto LAB_0014ec28;
}

