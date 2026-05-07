
/* WARNING: Type propagation algorithm not settling */

void ir_lift_arm64(long *param_1,undefined8 param_2,char *param_3,long param_4)

{
  char *__s;
  long lVar1;
  undefined8 *puVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  bool bVar6;
  bool bVar7;
  undefined8 uVar8;
  char cVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  void *pvVar14;
  undefined8 uVar15;
  long *plVar16;
  char *pcVar17;
  undefined8 *puVar18;
  undefined4 *puVar19;
  ulong uVar20;
  char *pcVar21;
  undefined4 *puVar22;
  ulonglong uVar23;
  uint uVar24;
  size_t sVar25;
  int *piVar26;
  undefined4 uVar27;
  int *__ptr;
  long lVar28;
  uint uVar29;
  long lVar30;
  long lVar31;
  char *pcVar32;
  char *pcVar33;
  long lVar34;
  ulong uVar35;
  undefined8 uVar36;
  uint uVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  undefined8 uVar41;
  undefined8 uVar42;
  undefined4 uVar43;
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined8 local_2e8;
  int local_2dc;
  int local_2d8;
  int local_2d4;
  undefined4 local_2c0;
  uint local_2a0;
  uint local_29c;
  uint local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  long *local_288;
  uint local_280;
  undefined4 uStack_27c;
  undefined8 local_278;
  undefined8 local_270;
  undefined8 uStack_268;
  undefined8 uStack_260;
  undefined8 uStack_258;
  undefined8 local_250;
  undefined8 uStack_248;
  undefined8 uStack_240;
  undefined8 uStack_238;
  undefined8 local_230;
  undefined8 uStack_228;
  undefined8 uStack_220;
  undefined8 uStack_218;
  undefined8 local_210;
  undefined8 uStack_208;
  undefined8 uStack_200;
  undefined8 uStack_1f8;
  undefined8 local_1e8;
  undefined8 uStack_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 uStack_1c0;
  undefined8 uStack_1b8;
  undefined8 uStack_1b0;
  undefined8 local_1a8;
  undefined8 uStack_1a0;
  undefined8 uStack_198;
  undefined8 uStack_190;
  undefined8 local_188;
  undefined8 uStack_180;
  undefined8 uStack_178;
  undefined8 uStack_170;
  undefined8 local_168;
  undefined8 uStack_160;
  char local_158 [192];
  long local_98;
  
  local_98 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (local_288 = calloc(1,0xa0), local_288 != (long *)0x0)) {
    *(undefined4 *)(local_288 + 2) = 0;
    local_288[3] = param_4;
    if ((param_3 == (char *)0x0) || (*param_3 == '\0')) {
      __snprintf_chk(local_288 + 4,0x80,2,0x80,"sub_%lx",param_4);
    }
    else {
      snprintf((char *)(local_288 + 4),0x80,"%s",param_3);
    }
    uVar8 = DAT_0020a3e0;
    lVar31 = 0;
    if ((int)param_1[1] != 0) {
      do {
        plVar16 = local_288;
        uVar24 = *(uint *)(local_288 + 1);
        uVar29 = *(uint *)((long)local_288 + 0xc);
        pvVar14 = (void *)*local_288;
        lVar1 = *param_1 + lVar31 * 0x20;
        if (uVar29 <= uVar24) {
          if (uVar29 == 0) {
            sVar25 = 0x240;
            uVar29 = 8;
          }
          else {
            uVar29 = uVar29 << 1;
            sVar25 = (ulong)uVar29 * 0x48;
          }
          pvVar14 = realloc(pvVar14,sVar25);
          if (pvVar14 == (void *)0x0) goto LAB_001525a8;
          uVar24 = *(uint *)(plVar16 + 1);
          *plVar16 = (long)pvVar14;
          *(uint *)((long)plVar16 + 0xc) = uVar29;
        }
        puVar2 = (undefined8 *)((long)pvVar14 + (ulong)uVar24 * 0x48);
        uStack_1e0 = 0xffffffffffffffff;
        local_1e8 = 0xffffffffffffffff;
        local_1d0 = 0xffffffffffffffff;
        local_1d8 = 0xffffffffffffffff;
        puVar2[8] = 0;
        puVar2[1] = 0;
        *puVar2 = 0;
        puVar2[3] = 0;
        puVar2[2] = 0;
        puVar2[5] = 0;
        puVar2[4] = 0;
        puVar2[7] = 0;
        puVar2[6] = 0;
        iVar10 = (int)plVar16[1];
        uStack_1c0 = 0xffffffffffffffff;
        local_1c8 = 0xffffffffffffffff;
        uStack_1b0 = 0xffffffffffffffff;
        uStack_1b8 = 0xffffffffffffffff;
        *(int *)(plVar16 + 1) = iVar10 + 1;
        *(int *)((long)pvVar14 + (ulong)uVar24 * 0x48) = iVar10;
        *(int *)((long)puVar2 + 0x34) = iVar10;
        uStack_1a0 = 0xffffffffffffffff;
        local_1a8 = 0xffffffffffffffff;
        uStack_190 = 0xffffffffffffffff;
        uStack_198 = 0xffffffffffffffff;
        uStack_180 = 0xffffffffffffffff;
        local_188 = 0xffffffffffffffff;
        uStack_170 = 0xffffffffffffffff;
        uStack_178 = 0xffffffffffffffff;
        uStack_268 = 0x400000004;
        local_270 = 0x400000004;
        uStack_258 = 0x400000004;
        uStack_260 = 0x400000004;
        uStack_248 = 0x400000004;
        local_250 = 0x400000004;
        uStack_238 = 0x400000004;
        uStack_240 = 0x400000004;
        uStack_228 = 0x400000004;
        local_230 = 0x400000004;
        uStack_218 = 0x400000004;
        uStack_220 = 0x400000004;
        uStack_208 = 0x400000004;
        local_210 = 0x400000004;
        uStack_1f8 = 0x400000004;
        uStack_200 = 0x400000004;
        if ((int)lVar31 == 0) {
          iVar10 = (int)local_288[2];
          *(int *)(local_288 + 2) = iVar10 + 8;
          local_1e8 = CONCAT44(iVar10 + 1,iVar10);
          uStack_1e0 = CONCAT44(iVar10 + 3,iVar10 + 2);
          local_1d8 = CONCAT44(iVar10 + 5,iVar10 + 4);
          local_1d0 = CONCAT44(iVar10 + 7,iVar10 + 6);
        }
        iVar10 = arm_emit_const(puVar2,local_288,0,param_4);
        if (iVar10 != -1) {
          uStack_1f8 = CONCAT44(5,(undefined4)uStack_1f8);
          uStack_170 = CONCAT44(iVar10,(undefined4)uStack_170);
        }
        if (*(int *)(lVar1 + 0x18) != 0) {
          lVar28 = 0;
          local_2e8 = 0;
          local_2dc = -1;
          local_2d8 = -1;
          local_2d4 = -1;
          uVar41 = uVar8;
          uVar42 = uVar8;
LAB_00151a90:
          lVar30 = *(long *)(lVar1 + 0x10) + lVar28 * 0xe0;
          pcVar21 = (char *)(lVar30 + 0x20);
          uVar15 = *(undefined8 *)(*(long *)(lVar1 + 0x10) + lVar28 * 0xe0);
          cVar9 = *(char *)(lVar30 + 0x60);
          local_158[0] = '\0';
          local_158[0x40] = '\0';
          local_158[0x80] = '\0';
          if (cVar9 != '\0') {
            pcVar33 = (char *)(lVar30 + 0x60);
            iVar10 = 0;
            pcVar32 = pcVar33;
            do {
              while (cVar9 != '[') {
                if (cVar9 == ']') {
                  iVar10 = iVar10 + -1;
                }
                else if (cVar9 == ',' && iVar10 == 0) {
                  sVar25 = (long)pcVar32 - (long)pcVar33;
                  if (0x3f < sVar25) {
                    sVar25 = 0x3f;
                  }
                  memcpy(local_158,pcVar33,sVar25);
                  local_158[sVar25] = '\0';
                  cVar9 = local_158[0];
                  if (local_158[0] == '\0') goto LAB_00152060;
                  sVar25 = strlen(local_158);
                  pcVar33 = local_158 + (sVar25 - 1);
                  if (local_158 < pcVar33) goto LAB_00152014;
                  goto LAB_00152024;
                }
                pcVar32 = pcVar32 + 1;
                cVar9 = *pcVar32;
                if (cVar9 == '\0') goto LAB_00151f00;
              }
              pcVar32 = pcVar32 + 1;
              cVar9 = *pcVar32;
              iVar10 = iVar10 + 1;
            } while (cVar9 != '\0');
LAB_00151f00:
            snprintf(local_158,0x40,"%s",pcVar33);
            cVar9 = local_158[0];
            if (local_158[0] != '\0') {
              sVar25 = strlen(local_158);
              pcVar33 = local_158 + (sVar25 - 1);
              if (local_158 < pcVar33) {
                do {
                  cVar9 = local_158[0];
                  if (*pcVar33 != ' ') break;
                  pcVar32 = pcVar33 + -1;
                  *pcVar33 = '\0';
                  pcVar33 = pcVar32;
                  cVar9 = local_158[0];
                } while (pcVar32 != local_158);
              }
              pcVar33 = local_158;
              if (cVar9 == ' ') {
                do {
                  pcVar33 = pcVar33 + 1;
                } while (*pcVar33 == ' ');
                if (pcVar33 != local_158) {
                  sVar25 = strlen(pcVar33);
                  __memmove_chk(local_158,pcVar33,sVar25 + 1,0x40);
                }
              }
            }
            local_298 = 0xfffffffe;
            local_29c = 0xfffffffe;
            local_2a0 = 0xfffffffe;
            local_294 = 4;
            local_290 = 4;
            local_28c = 4;
            iVar10 = arm64_reg_lookup(local_158,&local_2a0,&local_294);
            if (iVar10 == 0) {
              iVar10 = 1;
              goto LAB_00151adc;
            }
            uVar35 = 0;
            iVar10 = 1;
            bVar6 = false;
            uVar38 = 0;
            bVar7 = false;
            goto LAB_0015231c;
          }
          iVar10 = 0;
          local_29c = 0xfffffffe;
          local_298 = 0xfffffffe;
          local_294 = 4;
          local_290 = 4;
          local_28c = 4;
LAB_00151adc:
          local_2a0 = 0xfffffffe;
          iVar11 = strcmp(pcVar21,"adrp");
          if (iVar11 != 0) {
            uVar35 = 0;
            bVar6 = false;
            uVar38 = 0;
            bVar7 = false;
            goto LAB_00151afc;
          }
          goto LAB_00151c88;
        }
LAB_00151c9c:
        lVar31 = lVar31 + 1;
      } while ((uint)lVar31 < *(uint *)(param_1 + 1));
    }
    lVar31 = 0;
    uVar24 = *(uint *)(param_1 + 3);
    plVar16 = local_288;
    if (uVar24 != 0) {
      do {
        uVar29 = *(uint *)(param_1[2] + lVar31 * 0xc + 4);
        if (uVar29 != 0xffffffff) {
          uVar4 = *(uint *)(param_1[2] + lVar31 * 0xc);
          uVar37 = uVar29;
          if (uVar29 < uVar4) {
            uVar37 = uVar4;
          }
          if (uVar37 < *(uint *)(plVar16 + 1)) {
            lVar34 = *plVar16;
            lVar30 = (ulong)uVar29 * 0x48;
            lVar1 = lVar34 + (ulong)uVar4 * 0x48;
            lVar28 = lVar34 + lVar30;
            uVar29 = *(uint *)(lVar1 + 0x30);
            __ptr = *(int **)(lVar1 + 0x28);
            if (uVar29 == 0) {
              sVar25 = 4;
            }
            else {
              piVar26 = __ptr;
              do {
                if (*piVar26 == *(int *)(lVar34 + lVar30)) goto LAB_00151ce8;
                piVar26 = piVar26 + 1;
              } while (__ptr + uVar29 != piVar26);
              sVar25 = (ulong)(uVar29 + 1) << 2;
            }
            pvVar14 = realloc(__ptr,sVar25);
            if (pvVar14 == (void *)0x0) goto LAB_001525a8;
            uVar24 = *(uint *)(lVar1 + 0x30);
            uVar13 = *(undefined4 *)(lVar34 + lVar30);
            *(void **)(lVar1 + 0x28) = pvVar14;
            *(uint *)(lVar1 + 0x30) = uVar24 + 1;
            *(undefined4 *)((long)pvVar14 + (ulong)uVar24 * 4) = uVar13;
            pvVar14 = realloc(*(void **)(lVar28 + 0x18),(ulong)(*(int *)(lVar28 + 0x20) + 1) << 2);
            if (pvVar14 == (void *)0x0) goto LAB_001525a8;
            uVar24 = *(uint *)(lVar28 + 0x20);
            uVar13 = *(undefined4 *)(lVar34 + (ulong)uVar4 * 0x48);
            *(void **)(lVar28 + 0x18) = pvVar14;
            *(uint *)(lVar28 + 0x20) = uVar24 + 1;
            *(undefined4 *)((long)pvVar14 + (ulong)uVar24 * 4) = uVar13;
            uVar24 = *(uint *)(param_1 + 3);
            plVar16 = local_288;
          }
        }
LAB_00151ce8:
        lVar31 = lVar31 + 1;
      } while ((uint)lVar31 < uVar24);
    }
    goto LAB_001525d4;
  }
LAB_001525d0:
  plVar16 = (long *)0x0;
LAB_001525d4:
  if (local_98 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(plVar16,PTR___stack_chk_guard_005ffe88,0,
                     local_98 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
  while( true ) {
    pcVar17 = pcVar33 + -1;
    *pcVar33 = '\0';
    pcVar33 = pcVar17;
    cVar9 = local_158[0];
    if (pcVar17 == local_158) break;
LAB_00152014:
    cVar9 = local_158[0];
    if (*pcVar33 != ' ') break;
  }
LAB_00152024:
  pcVar33 = local_158;
  if (cVar9 == ' ') {
    do {
      pcVar33 = pcVar33 + 1;
    } while (*pcVar33 == ' ');
    if (pcVar33 != local_158) {
      sVar25 = strlen(pcVar33);
      __memmove_chk(local_158,pcVar33,sVar25 + 1,0x40);
    }
  }
LAB_00152060:
  cVar9 = pcVar32[1];
  pcVar32 = pcVar32 + 1;
  if (cVar9 != '\0') {
    iVar10 = 0;
    pcVar33 = pcVar32;
    do {
      while (cVar9 != '[') {
        if (cVar9 == ']') {
          iVar10 = iVar10 + -1;
        }
        else if (cVar9 == ',' && iVar10 == 0) {
          sVar25 = (long)pcVar33 - (long)pcVar32;
          pcVar17 = local_158 + 0x40;
          if (0x3f < sVar25) {
            sVar25 = 0x3f;
          }
          __s = local_158 + 0x80;
          memcpy(pcVar17,pcVar32,sVar25);
          pcVar17[sVar25] = '\0';
          snprintf(__s,0x40,"%s",pcVar33 + 1);
          cVar9 = local_158[0x40];
          if (local_158[0x40] == '\0') goto LAB_00152228;
          sVar25 = strlen(pcVar17);
          pcVar33 = pcVar17 + (sVar25 - 1);
          if (pcVar17 < pcVar17 + (sVar25 - 1)) goto LAB_001521d8;
          goto LAB_001521e8;
        }
        pcVar33 = pcVar33 + 1;
        cVar9 = *pcVar33;
        if (cVar9 == '\0') goto LAB_001520a8;
      }
      pcVar33 = pcVar33 + 1;
      cVar9 = *pcVar33;
      iVar10 = iVar10 + 1;
    } while (cVar9 != '\0');
  }
LAB_001520a8:
  pcVar33 = local_158 + 0x40;
  snprintf(pcVar33,0x40,"%s",pcVar32);
  cVar9 = local_158[0x40];
  if (local_158[0x40] != '\0') {
    sVar25 = strlen(pcVar33);
    pcVar32 = pcVar33 + (sVar25 - 1);
    if (pcVar33 < pcVar33 + (sVar25 - 1)) {
      do {
        cVar9 = local_158[0x40];
        if (*pcVar32 != ' ') break;
        pcVar17 = pcVar32 + -1;
        *pcVar32 = '\0';
        pcVar32 = pcVar17;
        cVar9 = local_158[0x40];
      } while (pcVar17 != pcVar33);
    }
    pcVar32 = pcVar33;
    if (cVar9 == ' ') {
      do {
        pcVar32 = pcVar32 + 1;
      } while (*pcVar32 == ' ');
      if (pcVar32 != pcVar33) {
        sVar25 = strlen(pcVar32);
        __memmove_chk(pcVar33,pcVar32,sVar25 + 1,0x40);
      }
    }
  }
  local_298 = 0xfffffffe;
  local_29c = 0xfffffffe;
  local_2a0 = 0xfffffffe;
  local_294 = 4;
  local_290 = 4;
  local_28c = 4;
  iVar10 = arm64_reg_lookup(local_158,&local_2a0,&local_294);
  if (iVar10 == 0) {
    local_2a0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar33,&local_29c,&local_290);
  }
  else {
    iVar10 = arm64_reg_lookup(pcVar33,&local_29c,&local_290);
  }
  if (iVar10 == 0) {
    iVar10 = 2;
    goto LAB_00152470;
  }
  uVar35 = 0;
  iVar10 = 2;
  bVar6 = false;
  uVar38 = 0;
  bVar7 = false;
LAB_0015231c:
  iVar11 = strcmp(pcVar21,"adrp");
  uVar24 = local_2a0;
  if (iVar11 == 0) {
    if ((int)local_2a0 < 0) goto LAB_00151c88;
    if (!bVar6) {
      if (iVar10 == 1) goto LAB_00152344;
      pcVar21 = local_158 + 0x40;
      cVar9 = local_158[0x40];
      while (cVar9 == ' ') {
        pcVar21 = pcVar21 + 1;
        cVar9 = *pcVar21;
      }
      if (cVar9 == '#') {
        pcVar33 = pcVar21 + 1;
        pcVar21 = pcVar21 + 1;
        cVar9 = *pcVar33;
        while (cVar9 == ' ') {
          pcVar21 = pcVar21 + 1;
          cVar9 = *pcVar21;
        }
      }
      iVar10 = __isoc99_sscanf(pcVar21,"0x%lx",&local_280);
      if (iVar10 == 1) {
        uVar35 = CONCAT44(uStack_27c,local_280);
      }
      else {
        iVar10 = __isoc99_sscanf(pcVar21,&DAT_001f84c8,&local_278);
        if (iVar10 != 1) goto LAB_00152344;
        uVar35 = CONCAT44(local_278._4_4_,(int)local_278);
      }
    }
    if (uVar35 != 0) {
      iVar10 = arm_emit_const(puVar2,local_288,uVar35,uVar15);
      if (iVar10 == -1) goto LAB_001525a8;
      lVar28 = lVar28 + 1;
      *(int *)((long)&local_1e8 + (long)(int)uVar24 * 4) = iVar10;
      uVar29 = *(uint *)(lVar1 + 0x18);
      *(undefined4 *)((long)&local_270 + (long)(int)uVar24 * 4) = 5;
      if (uVar29 <= (uint)lVar28) goto LAB_00151c9c;
      goto LAB_00151a90;
    }
LAB_00152344:
    lVar30 = local_288[2];
    lVar28 = lVar28 + 1;
    *(undefined4 *)((long)&local_270 + (long)(int)uVar24 * 4) = 5;
    *(int *)(local_288 + 2) = (int)lVar30 + 1;
    *(int *)((long)&local_1e8 + (long)(int)uVar24 * 4) = (int)lVar30;
    if (*(uint *)(lVar1 + 0x18) <= (uint)lVar28) goto LAB_00151c9c;
    goto LAB_00151a90;
  }
LAB_00151afc:
  iVar11 = strcmp(pcVar21,"mov");
  if (((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"movz"), iVar11 == 0)) ||
     (iVar11 = strcmp(pcVar21,"movk"), iVar11 == 0)) {
    uVar24 = local_2a0;
    if (-1 < (int)local_2a0) {
      uVar29 = *(uint *)(puVar2 + 2);
      uVar37 = *(uint *)((long)puVar2 + 0x14);
      iVar10 = (int)local_288[2];
      pvVar14 = (void *)puVar2[1];
      *(int *)(local_288 + 2) = iVar10 + 1;
      if (uVar37 <= uVar29) {
        if (uVar37 == 0) {
          sVar25 = 0x880;
          uVar37 = 0x10;
        }
        else {
          uVar37 = uVar37 << 1;
          sVar25 = (ulong)uVar37 * 0x88;
        }
        pvVar14 = realloc(pvVar14,sVar25);
        if (pvVar14 == (void *)0x0) goto LAB_001525a8;
        uVar29 = *(uint *)(puVar2 + 2);
        puVar2[1] = pvVar14;
        *(uint *)((long)puVar2 + 0x14) = uVar37;
      }
      *(uint *)(puVar2 + 2) = uVar29 + 1;
      puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar29 * 0x88);
      puVar18[1] = 0;
      *puVar18 = 0;
      puVar18[3] = 0;
      puVar18[2] = 0;
      puVar18[5] = 0;
      puVar18[4] = 0;
      puVar18[7] = 0;
      puVar18[6] = 0;
      puVar18[9] = 0;
      puVar18[8] = 0;
      puVar18[0xb] = 0;
      puVar18[10] = 0;
      puVar18[0xd] = 0;
      puVar18[0xc] = 0;
      puVar18[0xf] = 0;
      puVar18[0xe] = 0;
      puVar18[0x10] = 0;
      if (local_29c < 0x20) {
        iVar11 = *(int *)((long)&local_1e8 + (long)(int)local_29c * 4);
        if (iVar11 == -1) {
          iVar11 = (int)local_288[2];
          *(int *)(local_288 + 2) = iVar11 + 1;
        }
        uVar35 = 0;
        *(int *)(puVar18 + 3) = iVar11;
        *(undefined4 *)((long)puVar18 + 0x1c) = local_290;
        puVar18[4] = 0;
        *(undefined4 *)(puVar18 + 9) = 1;
      }
      else if ((local_29c == 0xffffffff) || (!bVar6)) {
        uVar35 = 0;
        *(undefined4 *)puVar18 = 1;
      }
      else {
        *(undefined4 *)puVar18 = 1;
      }
      *(int *)(puVar18 + 1) = iVar10;
      *(undefined4 *)((long)puVar18 + 0xc) = local_294;
      puVar18[2] = uVar35;
      lVar28 = lVar28 + 1;
      *(int *)((long)&local_1e8 + (long)(int)uVar24 * 4) = iVar10;
      *(undefined4 *)((long)&local_270 + (long)(int)uVar24 * 4) = local_294;
      puVar18[0xe] = uVar15;
      if (*(uint *)(lVar1 + 0x18) <= (uint)lVar28) goto LAB_00151c9c;
      goto LAB_00151a90;
    }
    goto LAB_00151c88;
  }
  iVar11 = strcmp(pcVar21,"add");
  if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"adds"), iVar11 == 0)) {
    uVar13 = 2;
LAB_00151b48:
    uVar43 = local_294;
    uVar24 = local_2a0;
    if (iVar10 == 3) {
      if (-1 < (int)local_2a0) {
        if (local_29c < 0x20) {
          iVar10 = *(int *)((long)&local_1e8 + (long)(int)local_29c * 4);
          if (iVar10 == -1) {
            iVar10 = (int)local_288[2];
            *(int *)(local_288 + 2) = iVar10 + 1;
          }
          uVar36 = 0;
          uVar43 = local_290;
        }
        else if (local_29c == 0xffffffff) {
          auVar44 = arm_emit_const(puVar2,local_288,0,uVar15);
          uVar36 = auVar44._8_8_;
          iVar10 = auVar44._0_4_;
          uVar43 = auVar44._4_4_;
          if (iVar10 == -1) goto LAB_001525a8;
        }
        else {
          iVar10 = (int)local_288[2];
          uVar36 = 0;
          *(int *)(local_288 + 2) = iVar10 + 1;
        }
        if (local_298 < 0x20) {
          iVar3 = (int)local_288[2];
          iVar12 = *(int *)((long)&local_1e8 + (long)(int)local_298 * 4);
          iVar11 = iVar3;
          if (iVar12 == -1) {
            iVar11 = iVar3 + 1;
            *(int *)(local_288 + 2) = iVar11;
            iVar12 = iVar3;
          }
          uVar38 = 0;
          uVar27 = local_28c;
        }
        else {
          if (local_298 == 0xffffffff) {
            uVar38 = 0;
          }
          else if (!bVar7) {
            iVar12 = (int)local_288[2];
            uVar38 = 0;
            iVar11 = iVar12 + 1;
            *(int *)(local_288 + 2) = iVar11;
            uVar27 = local_294;
            goto LAB_00151bc4;
          }
          auVar44 = arm_emit_const(puVar2,local_288,uVar38,uVar15);
          uVar38 = auVar44._8_8_;
          iVar12 = auVar44._0_4_;
          uVar27 = auVar44._4_4_;
          if (iVar12 == -1) goto LAB_001525a8;
          iVar11 = (int)local_288[2];
        }
LAB_00151bc4:
        uVar29 = *(uint *)(puVar2 + 2);
        uVar37 = *(uint *)((long)puVar2 + 0x14);
        *(int *)(local_288 + 2) = iVar11 + 1;
        pvVar14 = (void *)puVar2[1];
        if (uVar37 <= uVar29) {
          if (uVar37 == 0) {
            sVar25 = 0x880;
            uVar37 = 0x10;
          }
          else {
            uVar37 = uVar37 << 1;
            sVar25 = (ulong)uVar37 * 0x88;
          }
          pvVar14 = realloc(pvVar14,sVar25);
          if (pvVar14 == (void *)0x0) goto LAB_001525a8;
          uVar29 = *(uint *)(puVar2 + 2);
          puVar2[1] = pvVar14;
          *(uint *)((long)puVar2 + 0x14) = uVar37;
        }
        puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar29 * 0x88);
        *(uint *)(puVar2 + 2) = uVar29 + 1;
        puVar18[1] = 0;
        *puVar18 = 0;
        puVar18[3] = 0;
        puVar18[2] = 0;
        puVar18[5] = 0;
        puVar18[4] = 0;
        puVar18[7] = 0;
        puVar18[6] = 0;
        puVar18[9] = 0;
        puVar18[8] = 0;
        puVar18[0xb] = 0;
        puVar18[10] = 0;
        puVar18[0xd] = 0;
        puVar18[0xc] = 0;
        puVar18[0xf] = 0;
        puVar18[0xe] = 0;
        puVar18[0x10] = 0;
        *(undefined4 *)((long)pvVar14 + (ulong)uVar29 * 0x88) = uVar13;
        *(int *)((long)&local_1e8 + (long)(int)uVar24 * 4) = iVar11;
        *(undefined4 *)((long)&local_270 + (long)(int)uVar24 * 4) = local_294;
        *(int *)(puVar18 + 1) = iVar11;
        *(undefined4 *)((long)puVar18 + 0xc) = local_294;
        *(int *)(puVar18 + 3) = iVar10;
        *(undefined4 *)((long)puVar18 + 0x1c) = uVar43;
        puVar18[4] = uVar36;
        *(int *)(puVar18 + 5) = iVar12;
        *(undefined4 *)((long)puVar18 + 0x2c) = uVar27;
        puVar18[6] = uVar38;
        *(undefined4 *)(puVar18 + 9) = 2;
        puVar18[0xe] = uVar15;
        goto LAB_00151c88;
      }
    }
    else {
      if (iVar10 != 2) goto LAB_00152720;
      if (-1 < (int)local_2a0) {
        lVar30 = (long)(int)local_2a0;
        iVar10 = *(int *)((long)&local_1e8 + lVar30 * 4);
        if (iVar10 == -1) {
          iVar10 = (int)local_288[2];
          *(int *)(local_288 + 2) = iVar10 + 1;
        }
        if (local_29c < 0x20) {
          iVar3 = (int)local_288[2];
          iVar12 = *(int *)((long)&local_1e8 + (long)(int)local_29c * 4);
          iVar11 = iVar3;
          if (iVar12 == -1) {
            iVar11 = iVar3 + 1;
            *(int *)(local_288 + 2) = iVar11;
            iVar12 = iVar3;
          }
          uVar38 = 0;
          uVar27 = local_290;
        }
        else if (bVar6) {
          auVar44 = arm_emit_const(puVar2,local_288,uVar35,uVar15);
          uVar38 = auVar44._8_8_;
          iVar12 = auVar44._0_4_;
          uVar27 = auVar44._4_4_;
          if (iVar12 == -1) goto LAB_001525a8;
          iVar11 = (int)local_288[2];
        }
        else {
          iVar12 = (int)local_288[2];
          uVar38 = 0;
          iVar11 = iVar12 + 1;
          *(int *)(local_288 + 2) = iVar11;
          uVar27 = local_294;
        }
        uVar24 = *(uint *)(puVar2 + 2);
        uVar29 = *(uint *)((long)puVar2 + 0x14);
        *(int *)(local_288 + 2) = iVar11 + 1;
        pvVar14 = (void *)puVar2[1];
        if (uVar29 <= uVar24) {
          if (uVar29 == 0) {
            sVar25 = 0x880;
            uVar29 = 0x10;
          }
          else {
            uVar29 = uVar29 << 1;
            sVar25 = (ulong)uVar29 * 0x88;
          }
          pvVar14 = realloc(pvVar14,sVar25);
          if (pvVar14 == (void *)0x0) goto LAB_001525a8;
          uVar24 = *(uint *)(puVar2 + 2);
          puVar2[1] = pvVar14;
          *(uint *)((long)puVar2 + 0x14) = uVar29;
        }
        *(int *)((long)&local_1e8 + lVar30 * 4) = iVar11;
        *(uint *)(puVar2 + 2) = uVar24 + 1;
        *(undefined4 *)((long)&local_270 + lVar30 * 4) = uVar43;
        puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar24 * 0x88);
        puVar18[1] = 0;
        *puVar18 = 0;
        puVar18[3] = 0;
        puVar18[2] = 0;
        puVar18[5] = 0;
        puVar18[4] = 0;
        puVar18[7] = 0;
        puVar18[6] = 0;
        puVar18[9] = 0;
        puVar18[8] = 0;
        puVar18[0xb] = 0;
        puVar18[10] = 0;
        puVar18[0xd] = 0;
        puVar18[0xc] = 0;
        puVar18[0xf] = 0;
        puVar18[0xe] = 0;
        puVar18[0x10] = 0;
        *(undefined4 *)((long)pvVar14 + (ulong)uVar24 * 0x88) = uVar13;
        *(int *)(puVar18 + 1) = iVar11;
        *(undefined4 *)((long)puVar18 + 0xc) = uVar43;
        *(int *)(puVar18 + 3) = iVar10;
        *(undefined4 *)((long)puVar18 + 0x1c) = uVar43;
        *(int *)(puVar18 + 5) = iVar12;
        *(undefined4 *)((long)puVar18 + 0x2c) = uVar27;
        puVar18[6] = uVar38;
        *(undefined4 *)(puVar18 + 9) = 2;
        puVar18[0xe] = uVar15;
        goto LAB_00151c88;
      }
    }
    iVar10 = strcmp(pcVar21,"ldr");
    if (iVar10 == 0) goto LAB_00151c88;
LAB_00152b4c:
    iVar10 = strcmp(pcVar21,"ldrb");
    if (iVar10 == 0) {
      uVar13 = 1;
      uVar24 = local_2a0;
    }
    else {
      iVar10 = strcmp(pcVar21,"ldrh");
      if (iVar10 == 0) {
        uVar13 = 2;
        uVar24 = local_2a0;
      }
      else {
        iVar10 = strcmp(pcVar21,"ldrsw");
        uVar24 = local_2a0;
        uVar13 = local_294;
        if (iVar10 != 0) {
          iVar10 = strcmp(pcVar21,"str");
          if (((iVar10 != 0) && (iVar10 = strcmp(pcVar21,"strb"), iVar10 != 0)) &&
             (iVar10 = strcmp(pcVar21,"strh"), iVar10 != 0)) {
            iVar10 = strcmp(pcVar21,"ldp");
            if (iVar10 == 0) {
              arm64_parse_mem_op_isra_0(local_158 + 0x80,&local_280,&local_278);
              uVar35 = (ulong)local_2a0;
              if ((int)local_2a0 < 0) {
                lVar30 = 1;
                goto LAB_001534ec;
              }
              lVar30 = 0;
              uVar13 = local_294;
LAB_001533d0:
              do {
                iVar10 = (int)local_288[2];
                *(int *)(local_288 + 2) = iVar10 + 1;
                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                iVar11 = *(int *)(puVar2 + 2);
                *puVar19 = 0x15;
                puVar19[2] = iVar10;
                puVar19[3] = uVar13;
                *(undefined8 *)(puVar19 + 4) = 0;
                if ((local_280 < 0x20) &&
                   (iVar12 = *(int *)((long)&local_1e8 + (long)(int)local_280 * 4), iVar12 != -1)) {
                  auVar44 = arm_emit_const(puVar2,local_288,
                                           CONCAT44(local_278._4_4_,(int)local_278) + lVar30 * 8,
                                           uVar15);
                  if (auVar44._0_4_ == -1) goto LAB_001525a8;
                  iVar3 = (int)local_288[2];
                  *(int *)(local_288 + 2) = iVar3 + 1;
                  puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                  puVar19 = (undefined4 *)(puVar2[1] + (ulong)(iVar11 - 1) * 0x88);
                  *(long *)(puVar22 + 0xc) = auVar44._8_8_;
                  *puVar22 = 2;
                  puVar22[2] = iVar3;
                  puVar22[3] = 5;
                  *(undefined8 *)(puVar22 + 4) = 0;
                  puVar22[6] = iVar12;
                  puVar22[7] = 5;
                  *(undefined8 *)(puVar22 + 8) = 0;
                  *(long *)(puVar22 + 10) = auVar44._0_8_;
                  puVar22[0x12] = 2;
                  *(undefined8 *)(puVar22 + 0x1c) = uVar15;
                  puVar19[6] = iVar3;
                  puVar19[7] = 5;
                  *(undefined8 *)(puVar19 + 8) = 0;
                }
                else {
                  *(undefined8 *)(puVar19 + 8) = 0;
                  *(undefined8 *)(puVar19 + 6) = DAT_0020a3e8;
                }
                puVar19[0x12] = 1;
                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                if ((int)uVar35 < 0x20) {
                  uVar35 = -(uVar35 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                  *(int *)((long)&local_1e8 + uVar35) = iVar10;
                  *(undefined4 *)((long)&local_270 + uVar35) = uVar13;
                }
                lVar30 = lVar30 + 1;
                if (lVar30 == 2) break;
LAB_001534ec:
                for (; (int)lVar30 == 0; lVar30 = lVar30 + 1) {
                  uVar35 = (ulong)local_2a0;
                  uVar13 = local_294;
                  if (-1 < (int)local_2a0) goto LAB_001533d0;
                }
                uVar35 = (ulong)local_29c;
                uVar13 = local_290;
              } while (-1 < (int)local_29c);
              goto LAB_00151c88;
            }
            iVar10 = strcmp(pcVar21,"stp");
            if (iVar10 == 0) {
              arm64_parse_mem_op_isra_0(local_158 + 0x80,&local_280,&local_278);
              uVar38 = DAT_0020a3e8;
              lVar30 = 0;
              uVar13 = local_294;
              uVar24 = local_2a0;
              do {
                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                uVar29 = local_280;
                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                iVar10 = *(int *)(puVar2 + 2);
                *puVar19 = 0x16;
                *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                if ((local_280 < 0x20) &&
                   (iVar11 = *(int *)((long)&local_1e8 + (long)(int)local_280 * 4), iVar11 != -1)) {
                  auVar44 = arm_emit_const(puVar2,local_288,
                                           CONCAT44(local_278._4_4_,(int)local_278) + lVar30 * 8,
                                           uVar15);
                  iVar12 = (int)local_288[2];
                  *(int *)(local_288 + 2) = iVar12 + 1;
                  puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                  lVar34 = puVar2[1];
                  *(long *)(puVar22 + 0xc) = auVar44._8_8_;
                  puVar19 = (undefined4 *)(lVar34 + (ulong)(iVar10 - 1U) * 0x88);
                  puVar22[2] = iVar12;
                  *(undefined8 *)(puVar22 + 4) = 0;
                  puVar22[6] = iVar11;
                  *puVar22 = 2;
                  *(undefined8 *)(puVar22 + 8) = 0;
                  *(long *)(puVar22 + 10) = auVar44._0_8_;
                  puVar22[3] = 5;
                  puVar22[7] = 5;
                  puVar22[0x12] = 2;
                  *(undefined8 *)(puVar22 + 0x1c) = uVar15;
                  puVar19[6] = iVar12;
                  puVar19[7] = 5;
                  *(undefined8 *)(puVar19 + 8) = 0;
                }
                else {
                  *(undefined8 *)(puVar19 + 6) = uVar38;
                  *(undefined8 *)(puVar19 + 8) = 0;
                }
                if (uVar24 == 0xffffffff) {
                  auVar44 = arm_emit_const(puVar2,local_288,0,uVar15);
                  if (auVar44._0_4_ == -1) goto LAB_001525a8;
                  puVar19 = (undefined4 *)(puVar2[1] + (ulong)(iVar10 - 1U) * 0x88);
                  *(undefined1 (*) [16])(puVar19 + 10) = auVar44;
                }
                else {
                  if (uVar24 < 0x20) {
                    uVar35 = -(ulong)(uVar24 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar24 << 2;
                    iVar10 = *(int *)((long)&local_1e8 + uVar35);
                    if (iVar10 == -1) goto LAB_00153830;
                    uVar13 = *(undefined4 *)((long)&local_270 + uVar35);
                  }
                  else {
LAB_00153830:
                    iVar10 = (int)local_288[2];
                    *(int *)(local_288 + 2) = iVar10 + 1;
                  }
                  puVar19[10] = iVar10;
                  puVar19[0xb] = uVar13;
                  *(undefined8 *)(puVar19 + 0xc) = 0;
                }
                puVar19[0x12] = 2;
                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                if (lVar30 != 0) goto LAB_00153794;
                lVar30 = 1;
                uVar13 = local_290;
                uVar24 = local_29c;
              } while( true );
            }
            iVar10 = strcmp(pcVar21,"cmp");
            if (iVar10 == 0) {
              if (local_2a0 < 0x20) {
                local_2d8 = *(int *)((long)&local_1e8 + (long)(int)local_2a0 * 4);
                uVar13 = local_294;
                if (local_2d8 == -1) {
                  local_2d8 = (int)local_288[2];
                  *(int *)(local_288 + 2) = local_2d8 + 1;
                }
              }
              else {
                local_2d8 = (int)local_288[2];
                *(int *)(local_288 + 2) = local_2d8 + 1;
                uVar13 = 4;
              }
              uVar42 = CONCAT44(uVar13,local_2d8);
              if (local_29c < 0x20) {
                local_2dc = *(int *)((long)&local_1e8 + (long)(int)local_29c * 4);
                if (local_2dc == -1) {
                  local_2dc = (int)local_288[2];
                  *(int *)(local_288 + 2) = local_2dc + 1;
                }
                local_2e8 = 0;
                uVar43 = local_290;
              }
              else {
                if (local_29c == 0xffffffff) {
                  uVar35 = 0;
                }
                else if (!bVar6) {
                  local_2dc = (int)local_288[2];
                  uVar43 = 4;
                  local_2e8 = 0;
                  *(int *)(local_288 + 2) = local_2dc + 1;
                  goto LAB_00152ed0;
                }
                auVar44 = arm_emit_const(puVar2,local_288,uVar35,uVar15);
                local_2e8 = auVar44._8_8_;
                local_2dc = auVar44._0_4_;
                uVar43 = auVar44._4_4_;
                if (local_2dc == -1) goto LAB_001525a8;
              }
LAB_00152ed0:
              local_2d4 = (int)local_288[2];
              uVar24 = *(uint *)(puVar2 + 2);
              uVar29 = *(uint *)((long)puVar2 + 0x14);
              *(int *)(local_288 + 2) = local_2d4 + 1;
              uVar41 = CONCAT44(uVar43,local_2dc);
              if (uVar29 <= uVar24) {
                uVar37 = uVar29 << 1;
                if (uVar29 == 0) {
                  uVar37 = 0x10;
                }
                pvVar14 = realloc((void *)puVar2[1],(ulong)uVar37 * 0x88);
                if (pvVar14 == (void *)0x0) goto LAB_001525a8;
                uVar24 = *(uint *)(puVar2 + 2);
                puVar2[1] = pvVar14;
                *(uint *)((long)puVar2 + 0x14) = uVar37;
              }
              lVar30 = puVar2[1];
              *(uint *)(puVar2 + 2) = uVar24 + 1;
              puVar18 = (undefined8 *)(lVar30 + (ulong)uVar24 * 0x88);
              puVar18[1] = 0;
              *puVar18 = 0;
              puVar18[3] = 0;
              puVar18[2] = 0;
              puVar18[5] = 0;
              puVar18[4] = 0;
              puVar18[7] = 0;
              puVar18[6] = 0;
              puVar18[9] = 0;
              puVar18[8] = 0;
              puVar18[0xb] = 0;
              puVar18[10] = 0;
              puVar18[0xd] = 0;
              puVar18[0xc] = 0;
              puVar18[0xf] = 0;
              puVar18[0xe] = 0;
              puVar18[0x10] = 0;
              *(undefined4 *)(lVar30 + (ulong)uVar24 * 0x88) = 0xb;
              *(int *)(puVar18 + 1) = local_2d4;
              *(undefined4 *)((long)puVar18 + 0xc) = 6;
              *(undefined4 *)((long)puVar18 + 0x1c) = uVar13;
              *(int *)(puVar18 + 3) = local_2d8;
              *(int *)(puVar18 + 5) = local_2dc;
              puVar18[6] = local_2e8;
              *(undefined4 *)((long)puVar18 + 0x2c) = uVar43;
              *(undefined4 *)(puVar18 + 9) = 2;
              puVar18[0xe] = uVar15;
              goto LAB_00151c88;
            }
            iVar10 = strcmp(pcVar21,"cbz");
            if (iVar10 == 0) {
              uVar13 = 0xb;
            }
            else {
              iVar10 = strcmp(pcVar21,"cbnz");
              if (iVar10 != 0) {
                iVar10 = strcmp(pcVar21,"tbz");
                if (iVar10 == 0) {
                  local_2c0 = 0xb;
                }
                else {
                  iVar10 = strcmp(pcVar21,"tbnz");
                  if (iVar10 != 0) {
                    if ((*(char *)(lVar30 + 0x20) == 'b') && (*(char *)(lVar30 + 0x21) == '.')) {
                      if (local_2dc == -1 || local_2d8 == -1) {
LAB_0015409c:
                        iVar10 = local_2d4;
                        if (local_2d4 == -1) {
                          iVar10 = (int)local_288[2];
                          *(int *)(local_288 + 2) = iVar10 + 1;
                        }
                      }
                      else {
                        uVar13 = arm64_cond_suffix_to_cmp(lVar30 + 0x22,&local_278);
                        iVar10 = (int)local_288[2];
                        *(int *)(local_288 + 2) = iVar10 + 1;
                        puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                        *puVar19 = uVar13;
                        puVar19[2] = iVar10;
                        puVar19[3] = 6;
                        *(undefined8 *)(puVar19 + 4) = 0;
                        if ((int)local_278 == 0) {
                          uVar38 = local_2e8;
                          uVar36 = 0;
                          uVar39 = uVar41;
                          uVar40 = uVar42;
                        }
                        else {
                          uVar38 = 0;
                          uVar36 = local_2e8;
                          uVar39 = uVar42;
                          uVar40 = uVar41;
                        }
                        *(undefined8 *)(puVar19 + 0xc) = uVar38;
                        *(undefined8 *)(puVar19 + 6) = uVar40;
                        *(undefined8 *)(puVar19 + 8) = uVar36;
                        *(undefined8 *)(puVar19 + 10) = uVar39;
                        puVar19[0x12] = 2;
                        *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                        if (iVar10 == -1) goto LAB_0015409c;
                      }
                      puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                      if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                      puVar19[0x12] = 1;
                      *puVar19 = 0x17;
                      *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                      puVar19[6] = iVar10;
                      puVar19[7] = 6;
                      *(undefined8 *)(puVar19 + 8) = 0;
                      *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                      goto LAB_00151c88;
                    }
                    iVar10 = strcmp(pcVar21,"csel");
                    uVar24 = local_2a0;
                    if (iVar10 != 0) {
                      iVar10 = strcmp(pcVar21,"cset");
                      uVar24 = local_2a0;
                      if (iVar10 != 0) {
                        iVar10 = strcmp(pcVar21,"bl");
                        if (iVar10 == 0) {
                          iVar10 = (int)local_288[2];
                          *(int *)(local_288 + 2) = iVar10 + 1;
                          puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                          if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                          *puVar19 = 0x19;
                          puVar19[2] = iVar10;
                          puVar19[3] = 4;
                          *(undefined8 *)(puVar19 + 4) = 0;
                          if (local_158[0] == '#') {
                            uVar23 = strtoull(local_158 + 1,(char **)0x0,0);
                          }
                          else if (local_158[0] == '0') {
                            uVar23 = strtoull(local_158,(char **)0x0,0);
                          }
                          else {
                            uVar23 = 0;
                          }
                          puVar19[0x12] = 1;
                          *(ulonglong *)(puVar19 + 8) = uVar23;
                          *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                          uVar35 = 0;
                          *(undefined8 *)(puVar19 + 6) = DAT_0020a3e8;
                          do {
                            if (*(int *)((long)&local_1e8 + uVar35 * 4) == -1) {
                              if ((int)uVar35 == 0) goto LAB_00154474;
                              break;
                            }
                            uVar35 = uVar35 + 1;
                          } while (uVar35 != 8);
                          puVar22 = malloc(-((uVar35 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                           (uVar35 & 0xffffffff) << 4);
                          *(undefined4 **)(puVar19 + 0x14) = puVar22;
                          if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                          lVar30 = 0;
                          *(undefined8 *)(puVar19 + 0x16) = 0;
                          puVar19[0x18] = (int)uVar35;
                          do {
                            uVar13 = *(undefined4 *)((long)&local_270 + lVar30 * 4);
                            lVar34 = lVar30 * 4;
                            lVar30 = lVar30 + 1;
                            *puVar22 = *(undefined4 *)((long)&local_1e8 + lVar34);
                            puVar22[1] = uVar13;
                            *(undefined8 *)(puVar22 + 2) = 0;
                            puVar22 = puVar22 + 4;
                          } while ((int)lVar30 < (int)uVar35);
LAB_00154474:
                          local_270 = CONCAT44(local_270._4_4_,4);
                          local_1e8 = CONCAT44(local_1e8._4_4_,iVar10);
                          goto LAB_00151c88;
                        }
                        iVar10 = strcmp(pcVar21,"blr");
                        if (iVar10 != 0) {
                          iVar10 = strcmp(pcVar21,"b");
                          if (iVar10 == 0) {
                            for (pcVar21 = local_158; cVar9 = *pcVar21, cVar9 == ' ' || cVar9 == '#'
                                ; pcVar21 = pcVar21 + 1) {
                            }
                            if ((cVar9 == '\0') ||
                               (uVar23 = strtoull(pcVar21,(char **)&local_278,0),
                               (char *)CONCAT44(local_278._4_4_,(int)local_278) == pcVar21)) {
LAB_00154220:
                              puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                              if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                              *puVar19 = 0x18;
                              puVar19[0x12] = 0;
                              *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                              *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                            }
                            else {
                              for (lVar30 = 0; (uint)lVar30 < *(uint *)(param_1 + 1);
                                  lVar30 = lVar30 + 1) {
                                if ((*(ulong *)(*param_1 + lVar30 * 0x20) <= uVar23) &&
                                   (uVar23 < *(ulong *)(*param_1 + lVar30 * 0x20 + 8)))
                                goto LAB_00154220;
                              }
                              iVar10 = (int)local_288[2];
                              *(int *)(local_288 + 2) = iVar10 + 1;
                              puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                              if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                              *puVar19 = 0x19;
                              uVar38 = DAT_0020a3e8;
                              puVar19[0x12] = 1;
                              puVar19[2] = iVar10;
                              puVar19[3] = 4;
                              uVar35 = 0;
                              *(undefined8 *)(puVar19 + 4) = 0;
                              *(ulonglong *)(puVar19 + 8) = uVar23;
                              *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                              *(undefined8 *)(puVar19 + 6) = uVar38;
                              do {
                                if (*(int *)((long)&local_1e8 + uVar35 * 4) == -1) {
                                  if ((int)uVar35 == 0) goto LAB_001545ac;
                                  break;
                                }
                                uVar35 = uVar35 + 1;
                              } while (uVar35 != 8);
                              puVar22 = malloc(-((uVar35 & 0xffffffff) >> 0x1f) & 0xfffffff000000000
                                               | (uVar35 & 0xffffffff) << 4);
                              *(undefined4 **)(puVar19 + 0x14) = puVar22;
                              if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                              lVar30 = 0;
                              *(undefined8 *)(puVar19 + 0x16) = 0;
                              puVar19[0x18] = (int)uVar35;
                              do {
                                uVar13 = *(undefined4 *)((long)&local_270 + lVar30 * 4);
                                lVar34 = lVar30 * 4;
                                lVar30 = lVar30 + 1;
                                *puVar22 = *(undefined4 *)((long)&local_1e8 + lVar34);
                                puVar22[1] = uVar13;
                                *(undefined8 *)(puVar22 + 2) = 0;
                                puVar22 = puVar22 + 4;
                              } while ((int)lVar30 < (int)uVar35);
LAB_001545ac:
                              local_270 = CONCAT44(local_270._4_4_,4);
                              local_1e8 = CONCAT44(local_1e8._4_4_,iVar10);
                              puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                              if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                              puVar19[0x12] = 1;
                              *puVar19 = 0x1a;
                              *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                              puVar19[6] = iVar10;
                              puVar19[7] = 4;
                              *(undefined8 *)(puVar19 + 8) = 0;
                              *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                            }
                          }
                          else {
                            iVar10 = strcmp(pcVar21,"ret");
                            if (iVar10 == 0) {
                              puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                              if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                              *puVar19 = 0x1a;
                              *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                              if ((int)local_1e8 == -1) {
                                uVar13 = 4;
                              }
                              else {
                                uVar13 = (undefined4)local_270;
                              }
                              puVar19[6] = (int)local_1e8;
                              puVar19[7] = uVar13;
                              *(undefined8 *)(puVar19 + 8) = 0;
                              puVar19[0x12] = 1;
                              *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                            }
                            else {
                              iVar10 = strcmp(pcVar21,"nop");
                              if ((((((((iVar10 != 0) &&
                                       (iVar10 = strcmp(pcVar21,"hint"), iVar10 != 0)) &&
                                      (iVar10 = strcmp(pcVar21,"yield"), iVar10 != 0)) &&
                                     ((iVar10 = strcmp(pcVar21,"sev"), iVar10 != 0 &&
                                      (iVar10 = strcmp(pcVar21,"sevl"), iVar10 != 0)))) &&
                                    (iVar10 = strcmp(pcVar21,"wfi"), iVar10 != 0)) &&
                                   (((iVar10 = strcmp(pcVar21,"wfe"), iVar10 != 0 &&
                                     (iVar10 = strcmp(pcVar21,"isb"), iVar10 != 0)) &&
                                    ((iVar10 = strcmp(pcVar21,"dsb"), iVar10 != 0 &&
                                     (((iVar10 = strcmp(pcVar21,"dmb"), iVar10 != 0 &&
                                       (iVar10 = strcmp(pcVar21,"paciasp"), iVar10 != 0)) &&
                                      (iVar10 = strcmp(pcVar21,"autiasp"), iVar10 != 0)))))))) &&
                                  ((iVar10 = strcmp(pcVar21,"pacibsp"), iVar10 != 0 &&
                                   (iVar10 = strcmp(pcVar21,"autibsp"), iVar10 != 0)))) &&
                                 (iVar10 = strcmp(pcVar21,"bti"), iVar10 != 0)) {
                                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                                *puVar19 = 0x1d;
                                puVar19[0x12] = 0;
                                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                                *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                                strncpy((char *)(puVar19 + 0x1e),pcVar21,0xf);
                                *(undefined1 *)((long)puVar19 + 0x87) = 0;
                              }
                            }
                          }
                          goto LAB_00151c88;
                        }
                        iVar10 = (int)local_288[2];
                        *(int *)(local_288 + 2) = iVar10 + 1;
                        puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                        *puVar19 = 0x19;
                        puVar19[2] = iVar10;
                        puVar19[3] = 4;
                        *(undefined8 *)(puVar19 + 4) = 0;
                        if (local_2a0 < 0x20) {
                          uVar35 = -(ulong)(local_2a0 >> 0x1f) & 0xfffffffc00000000 |
                                   (ulong)local_2a0 << 2;
                          iVar11 = *(int *)((long)&local_1e8 + uVar35);
                          if (iVar11 == -1) goto LAB_0015458c;
                          uVar13 = *(undefined4 *)((long)&local_270 + uVar35);
                        }
                        else {
LAB_0015458c:
                          uVar13 = 5;
                          iVar11 = (int)local_288[2];
                          *(int *)(local_288 + 2) = iVar11 + 1;
                        }
                        puVar19[6] = iVar11;
                        puVar19[7] = uVar13;
                        uVar35 = 0;
                        *(undefined8 *)(puVar19 + 8) = 0;
                        puVar19[0x12] = 1;
                        *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                        do {
                          if (*(int *)((long)&local_1e8 + uVar35 * 4) == -1) {
                            if ((int)uVar35 == 0) goto LAB_001544bc;
                            break;
                          }
                          uVar35 = uVar35 + 1;
                        } while (uVar35 != 8);
                        puVar22 = malloc(-((uVar35 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                         (uVar35 & 0xffffffff) << 4);
                        *(undefined4 **)(puVar19 + 0x14) = puVar22;
                        if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                        lVar30 = 0;
                        *(undefined8 *)(puVar19 + 0x16) = 0;
                        puVar19[0x18] = (int)uVar35;
                        do {
                          uVar13 = *(undefined4 *)((long)&local_270 + lVar30 * 4);
                          lVar34 = lVar30 * 4;
                          lVar30 = lVar30 + 1;
                          *puVar22 = *(undefined4 *)((long)&local_1e8 + lVar34);
                          puVar22[1] = uVar13;
                          *(undefined8 *)(puVar22 + 2) = 0;
                          puVar22 = puVar22 + 4;
                        } while ((int)lVar30 < (int)uVar35);
LAB_001544bc:
                        local_270 = CONCAT44(local_270._4_4_,4);
                        local_1e8 = CONCAT44(local_1e8._4_4_,iVar10);
                        goto LAB_00151c88;
                      }
                      uVar35 = (ulong)local_2a0;
                      if ((int)local_2a0 < 0) goto LAB_00151c88;
                      if (local_2dc == -1 || local_2d8 == -1) {
LAB_00153cd4:
                        iVar10 = local_2d4;
                        if (local_2d4 == -1) {
                          iVar10 = (int)local_288[2];
                          *(int *)(local_288 + 2) = iVar10 + 1;
                        }
                      }
                      else {
                        plVar16 = local_288;
                        uVar13 = arm64_cond_suffix_to_cmp(local_158 + 0x40,&local_278);
                        iVar10 = (int)plVar16[2];
                        *(int *)(plVar16 + 2) = iVar10 + 1;
                        puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                        *puVar19 = uVar13;
                        puVar19[2] = iVar10;
                        puVar19[3] = 6;
                        *(undefined8 *)(puVar19 + 4) = 0;
                        if ((int)local_278 == 0) {
                          uVar38 = local_2e8;
                          uVar36 = 0;
                          uVar39 = uVar41;
                          uVar40 = uVar42;
                        }
                        else {
                          uVar38 = 0;
                          uVar36 = local_2e8;
                          uVar39 = uVar42;
                          uVar40 = uVar41;
                        }
                        *(undefined8 *)(puVar19 + 0xc) = uVar38;
                        *(undefined8 *)(puVar19 + 6) = uVar40;
                        *(undefined8 *)(puVar19 + 8) = uVar36;
                        *(undefined8 *)(puVar19 + 10) = uVar39;
                        puVar19[0x12] = 2;
                        *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                        if (iVar10 == -1) goto LAB_00153cd4;
                      }
                      auVar44 = arm_emit_const(puVar2,local_288,1,uVar15);
                      if (auVar44._0_4_ == -1) goto LAB_001525a8;
                      auVar45 = arm_emit_const(puVar2,local_288,0,uVar15);
                      if (auVar45._0_4_ == -1) goto LAB_001525a8;
                      iVar11 = (int)local_288[2];
                      *(int *)(local_288 + 2) = iVar11 + 1;
                      puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                      if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                      uVar35 = -(ulong)(uVar24 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                      puVar19[2] = iVar11;
                      *(int *)((long)&local_1e8 + uVar35) = iVar11;
                      *puVar19 = 0x1c;
                      puVar19[7] = 6;
                      *(long *)(puVar19 + 0xc) = auVar44._8_8_;
                      *(long *)(puVar19 + 0xe) = auVar45._0_8_;
                      *(undefined4 *)((long)&local_270 + uVar35) = local_294;
                      puVar19[3] = local_294;
                      *(undefined8 *)(puVar19 + 4) = 0;
                      puVar19[6] = iVar10;
                      *(undefined8 *)(puVar19 + 8) = 0;
                      *(long *)(puVar19 + 10) = auVar44._0_8_;
                      *(long *)(puVar19 + 0x10) = auVar45._8_8_;
                      puVar19[0x12] = 3;
                      *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                      goto LAB_00151c88;
                    }
                    uVar35 = (ulong)local_2a0;
                    if ((int)local_2a0 < 0) goto LAB_00151c88;
                    iVar10 = (int)local_288[2];
                    *(int *)(local_288 + 2) = iVar10 + 1;
                    puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                    if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                    *puVar19 = 0x1c;
                    if (local_2dc == -1 || local_2d8 == -1) {
LAB_00154040:
                      iVar11 = local_2d4;
                      if (local_2d4 == -1) {
                        iVar11 = (int)local_288[2];
                        *(int *)(local_288 + 2) = iVar11 + 1;
                      }
                    }
                    else {
                      local_168 = 0;
                      pcVar21 = strchr(local_158 + 0x80,0x2c);
                      if (pcVar21 != (char *)0x0) {
                        do {
                          pcVar33 = pcVar21 + 1;
                          pcVar21 = pcVar21 + 1;
                        } while (*pcVar33 == ' ');
                        for (lVar30 = 0;
                            (bVar5 = pcVar21[lVar30], bVar5 != 0x2c && (bVar5 & 0xdf) != 0 &&
                            (lVar30 != 7)); lVar30 = lVar30 + 1) {
                          *(byte *)((long)&local_168 + lVar30) = bVar5;
                        }
                        *(undefined1 *)((long)&local_168 + (long)(int)lVar30) = 0;
                      }
                      uVar13 = arm64_cond_suffix_to_cmp(&local_168,&local_278);
                      iVar11 = (int)local_288[2];
                      *(int *)(local_288 + 2) = iVar11 + 1;
                      puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                      if (puVar22 == (undefined4 *)0x0) goto LAB_001525a8;
                      *puVar22 = uVar13;
                      puVar22[2] = iVar11;
                      puVar22[3] = 6;
                      *(undefined8 *)(puVar22 + 4) = 0;
                      if ((int)local_278 == 0) {
                        uVar38 = local_2e8;
                        uVar36 = 0;
                        uVar39 = uVar41;
                        uVar40 = uVar42;
                      }
                      else {
                        uVar38 = 0;
                        uVar36 = local_2e8;
                        uVar39 = uVar42;
                        uVar40 = uVar41;
                      }
                      *(undefined8 *)(puVar22 + 0xc) = uVar38;
                      *(undefined8 *)(puVar22 + 6) = uVar40;
                      *(undefined8 *)(puVar22 + 8) = uVar36;
                      *(undefined8 *)(puVar22 + 10) = uVar39;
                      puVar22[0x12] = 2;
                      *(undefined8 *)(puVar22 + 0x1c) = uVar15;
                      if (iVar11 == -1) goto LAB_00154040;
                    }
                    puVar19[6] = iVar11;
                    puVar19[7] = 6;
                    *(undefined8 *)(puVar19 + 8) = 0;
                    if (local_29c < 0x20) {
                      uVar20 = -(ulong)(local_29c >> 0x1f) & 0xfffffffc00000000 |
                               (ulong)local_29c << 2;
                      iVar11 = *(int *)((long)&local_1e8 + uVar20);
                      if (iVar11 == -1) goto LAB_00153c84;
                      uVar13 = *(undefined4 *)((long)&local_270 + uVar20);
                    }
                    else {
LAB_00153c84:
                      iVar11 = (int)local_288[2];
                      *(int *)(local_288 + 2) = iVar11 + 1;
                      uVar13 = local_290;
                    }
                    puVar19[10] = iVar11;
                    puVar19[0xb] = uVar13;
                    *(undefined8 *)(puVar19 + 0xc) = 0;
                    local_168 = 0;
                    uStack_160 = 0;
                    pcVar21 = strchr(local_158 + 0x40,0x2c);
                    if (pcVar21 != (char *)0x0) {
                      do {
                        pcVar33 = pcVar21 + 1;
                        pcVar21 = pcVar21 + 1;
                      } while (*pcVar33 == ' ');
                      for (lVar30 = 0;
                          (bVar5 = pcVar21[lVar30], bVar5 != 0x2c && (bVar5 & 0xdf) != 0 &&
                          (lVar30 != 0xf)); lVar30 = lVar30 + 1) {
                        *(byte *)((long)&local_168 + lVar30) = bVar5;
                      }
                      *(undefined1 *)((long)&local_168 + (long)(int)lVar30) = 0;
                    }
                    local_280 = 0xfffffffe;
                    local_278._0_4_ = 4;
                    if ((((char)local_168 == '\0') ||
                        (iVar11 = arm64_reg_lookup(&local_168,&local_280,&local_278), iVar11 == 0))
                       || (0x1f < local_280)) {
LAB_00153ba4:
                      iVar11 = (int)local_288[2];
                      *(int *)(local_288 + 2) = iVar11 + 1;
                      uVar13 = local_294;
                    }
                    else {
                      uVar20 = -(ulong)(local_280 >> 0x1f) & 0xfffffffc00000000 |
                               (ulong)local_280 << 2;
                      iVar11 = *(int *)((long)&local_1e8 + uVar20);
                      if (iVar11 == -1) goto LAB_00153ba4;
                      uVar13 = *(undefined4 *)((long)&local_270 + uVar20);
                    }
                    uVar35 = -(ulong)(uVar24 >> 0x1f) & 0xfffffffc00000000 | uVar35 << 2;
                    puVar19[0xe] = iVar11;
                    puVar19[0xf] = uVar13;
                    *(undefined4 *)((long)&local_270 + uVar35) = local_294;
                    *(int *)((long)&local_1e8 + uVar35) = iVar10;
                    puVar19[2] = iVar10;
                    puVar19[3] = local_294;
                    *(undefined8 *)(puVar19 + 4) = 0;
                    *(undefined8 *)(puVar19 + 0x10) = 0;
                    puVar19[0x12] = 3;
                    *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                    goto LAB_00151c88;
                  }
                  local_2c0 = 0xc;
                }
                if (local_2a0 < 0x20) {
                  uVar20 = -(ulong)(local_2a0 >> 0x1f) & 0xfffffffc00000000 | (ulong)local_2a0 << 2;
                  iVar10 = *(int *)((long)&local_1e8 + uVar20);
                  if (iVar10 == -1) goto LAB_00153a14;
                  uVar13 = *(undefined4 *)((long)&local_270 + uVar20);
                }
                else {
LAB_00153a14:
                  uVar13 = 4;
                  iVar10 = (int)local_288[2];
                  *(int *)(local_288 + 2) = iVar10 + 1;
                }
                if (bVar6) {
                  if (-1 < (long)uVar35) goto LAB_001538ec;
                  uVar35 = 0;
                }
                else {
                  uVar35 = 0;
LAB_001538ec:
                  if (0x3f < (long)uVar35) {
                    uVar35 = 0x3f;
                  }
                }
                auVar44 = arm_emit_const(puVar2,local_288,1L << (uVar35 & 0x3f),uVar15);
                if (auVar44._0_4_ == -1) goto LAB_001525a8;
                iVar11 = (int)local_288[2];
                *(int *)(local_288 + 2) = iVar11 + 1;
                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                puVar19[6] = iVar10;
                puVar19[7] = uVar13;
                *puVar19 = 6;
                puVar19[2] = iVar11;
                puVar19[3] = uVar13;
                *(undefined8 *)(puVar19 + 4) = 0;
                *(undefined8 *)(puVar19 + 8) = 0;
                *(undefined1 (*) [16])(puVar19 + 10) = auVar44;
                puVar19[0x12] = 2;
                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                auVar44 = arm_emit_const(puVar2,local_288,0,uVar15);
                if (auVar44._0_4_ == -1) goto LAB_001525a8;
                iVar10 = (int)local_288[2];
                *(int *)(local_288 + 2) = iVar10 + 1;
                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                *puVar19 = local_2c0;
                puVar19[2] = iVar10;
                puVar19[3] = 6;
                *(undefined8 *)(puVar19 + 4) = 0;
                puVar19[6] = iVar11;
                puVar19[7] = uVar13;
                *(undefined8 *)(puVar19 + 8) = 0;
                *(undefined1 (*) [16])(puVar19 + 10) = auVar44;
                puVar19[0x12] = 2;
                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
                *puVar19 = 0x17;
                puVar19[6] = iVar10;
                puVar19[7] = 6;
                *(undefined8 *)(puVar19 + 8) = 0;
                *(undefined8 *)(puVar19 + 2) = 0xffffffff;
                puVar19[0x12] = 1;
                *(undefined8 *)(puVar19 + 0x1c) = uVar15;
                goto LAB_00151c88;
              }
              uVar13 = 0xc;
            }
            if (local_2a0 < 0x20) {
              uVar35 = -(ulong)(local_2a0 >> 0x1f) & 0xfffffffc00000000 | (ulong)local_2a0 << 2;
              iVar10 = *(int *)((long)&local_1e8 + uVar35);
              if (iVar10 == -1) goto LAB_0015377c;
              uVar43 = *(undefined4 *)((long)&local_270 + uVar35);
            }
            else {
LAB_0015377c:
              uVar43 = 4;
              iVar10 = (int)local_288[2];
              *(int *)(local_288 + 2) = iVar10 + 1;
            }
            auVar44 = arm_emit_const(puVar2,local_288,0,uVar15);
            if (auVar44._0_4_ == -1) goto LAB_001525a8;
            iVar11 = (int)local_288[2];
            *(int *)(local_288 + 2) = iVar11 + 1;
            puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
            if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
            *puVar19 = uVar13;
            puVar19[2] = iVar11;
            puVar19[3] = 6;
            *(undefined8 *)(puVar19 + 4) = 0;
            puVar19[6] = iVar10;
            puVar19[7] = uVar43;
            *(undefined8 *)(puVar19 + 8) = 0;
            *(undefined1 (*) [16])(puVar19 + 10) = auVar44;
            puVar19[0x12] = 2;
            *(undefined8 *)(puVar19 + 0x1c) = uVar15;
            puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
            if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
            *puVar19 = 0x17;
            puVar19[6] = iVar11;
            puVar19[7] = 6;
            *(undefined8 *)(puVar19 + 8) = 0;
            *(undefined8 *)(puVar19 + 2) = 0xffffffff;
            puVar19[0x12] = 1;
            *(undefined8 *)(puVar19 + 0x1c) = uVar15;
            goto LAB_00151c88;
          }
          arm64_parse_mem_op_isra_0(local_158 + 0x40,&local_280,&local_278);
          uVar24 = *(uint *)(puVar2 + 2);
          uVar29 = *(uint *)((long)puVar2 + 0x14);
          if (uVar24 < uVar29) {
            pvVar14 = (void *)puVar2[1];
          }
          else {
            if (uVar29 == 0) {
              sVar25 = 0x880;
              uVar29 = 0x10;
            }
            else {
              uVar29 = uVar29 << 1;
              sVar25 = (ulong)uVar29 * 0x88;
            }
            pvVar14 = realloc((void *)puVar2[1],sVar25);
            if (pvVar14 == (void *)0x0) goto LAB_001525a8;
            uVar24 = *(uint *)(puVar2 + 2);
            puVar2[1] = pvVar14;
            *(uint *)((long)puVar2 + 0x14) = uVar29;
          }
          *(uint *)(puVar2 + 2) = uVar24 + 1;
          puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar24 * 0x88);
          puVar18[0x10] = 0;
          puVar18[1] = 0;
          *puVar18 = 0;
          puVar18[3] = 0;
          puVar18[2] = 0;
          puVar18[5] = 0;
          puVar18[4] = 0;
          puVar18[7] = 0;
          puVar18[6] = 0;
          puVar18[9] = 0;
          puVar18[8] = 0;
          puVar18[0xb] = 0;
          puVar18[10] = 0;
          puVar18[0xd] = 0;
          puVar18[0xc] = 0;
          puVar18[0xf] = 0;
          puVar18[0xe] = 0;
          iVar10 = *(int *)(puVar2 + 2);
          *(undefined4 *)((long)pvVar14 + (ulong)uVar24 * 0x88) = 0x16;
          *(undefined4 *)(puVar18 + 1) = 0xffffffff;
          if (local_280 < 0x20) {
            lVar30 = (long)(int)local_280;
            iVar11 = *(int *)((long)&local_1e8 + lVar30 * 4);
            if (iVar11 == -1) goto LAB_001531c0;
            auVar44 = arm_emit_const(puVar2,local_288,CONCAT44(local_278._4_4_,(int)local_278),
                                     uVar15);
            if (auVar44._0_4_ == -1) goto LAB_001525a8;
            uVar24 = *(uint *)(puVar2 + 2);
            uVar29 = *(uint *)((long)puVar2 + 0x14);
            iVar12 = (int)local_288[2];
            *(int *)(local_288 + 2) = iVar12 + 1;
            pvVar14 = (void *)puVar2[1];
            if (uVar29 <= uVar24) {
              if (uVar29 == 0) {
                sVar25 = 0x880;
                uVar29 = 0x10;
              }
              else {
                uVar29 = uVar29 << 1;
                sVar25 = (ulong)uVar29 * 0x88;
              }
              pvVar14 = realloc(pvVar14,sVar25);
              if (pvVar14 == (void *)0x0) goto LAB_001525a8;
              puVar2[1] = pvVar14;
              uVar24 = *(uint *)(puVar2 + 2);
              *(uint *)((long)puVar2 + 0x14) = uVar29;
            }
            *(uint *)(puVar2 + 2) = uVar24 + 1;
            lVar34 = (ulong)uVar24 * 0x88;
            uVar13 = *(undefined4 *)((long)&local_270 + lVar30 * 4);
            *(undefined4 *)((long)pvVar14 + lVar34 + 0x84) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0xc) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 4) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x1c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x14) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x2c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x24) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x3c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x34) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x4c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x44) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x5c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x54) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x6c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 100) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x7c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x74) = 0;
            lVar30 = puVar2[1];
            *(undefined4 *)((long)pvVar14 + lVar34) = 2;
            *(int *)((long)pvVar14 + lVar34 + 8) = iVar12;
            *(undefined4 *)((long)pvVar14 + lVar34 + 0xc) = 5;
            *(int *)((long)pvVar14 + lVar34 + 0x18) = iVar11;
            *(undefined4 *)((long)pvVar14 + lVar34 + 0x1c) = uVar13;
            puVar18 = (undefined8 *)(lVar30 + (ulong)(iVar10 - 1U) * 0x88);
            *(undefined1 (*) [16])((long)pvVar14 + lVar34 + 0x28) = auVar44;
            *(undefined4 *)((long)pvVar14 + lVar34 + 0x48) = 2;
            *(undefined8 *)((long)pvVar14 + lVar34 + 0x70) = uVar15;
            *(int *)(puVar18 + 3) = iVar12;
            *(undefined4 *)((long)puVar18 + 0x1c) = 5;
            puVar18[4] = 0;
          }
          else {
LAB_001531c0:
            puVar18[3] = DAT_0020a3e8;
          }
          if (local_2a0 == 0xffffffff) {
            auVar44 = arm_emit_const(puVar2,local_288,0,uVar15);
            if (auVar44._0_4_ == -1) goto LAB_001525a8;
            puVar18 = (undefined8 *)(puVar2[1] + (ulong)(iVar10 - 1U) * 0x88);
            *(undefined1 (*) [16])(puVar18 + 5) = auVar44;
          }
          else {
            if (local_2a0 < 0x20) {
              iVar10 = *(int *)((long)&local_1e8 + (long)(int)local_2a0 * 4);
              if (iVar10 == -1) goto LAB_00153210;
              uVar13 = *(undefined4 *)((long)&local_270 + (long)(int)local_2a0 * 4);
            }
            else {
LAB_00153210:
              iVar10 = (int)local_288[2];
              *(int *)(local_288 + 2) = iVar10 + 1;
              uVar13 = local_294;
            }
            *(int *)(puVar18 + 5) = iVar10;
            *(undefined4 *)((long)puVar18 + 0x2c) = uVar13;
            puVar18[6] = 0;
          }
          *(undefined4 *)(puVar18 + 9) = 2;
          puVar18[0xe] = uVar15;
          goto LAB_00151c88;
        }
      }
    }
    local_2a0 = uVar24;
    if ((int)uVar24 < 0) {
LAB_00151c88:
      lVar28 = lVar28 + 1;
      if (*(uint *)(lVar1 + 0x18) <= (uint)lVar28) goto LAB_00151c9c;
      goto LAB_00151a90;
    }
  }
  else {
    iVar11 = strcmp(pcVar21,"sub");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"subs"), iVar11 == 0)) {
      uVar13 = 3;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"mul");
    if (iVar11 == 0) {
      uVar13 = 4;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"sdiv");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"udiv"), iVar11 == 0)) {
      uVar13 = 5;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"and");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"ands"), iVar11 == 0)) {
      uVar13 = 6;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"orr");
    if (iVar11 == 0) {
      uVar13 = 7;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"eor");
    if (iVar11 == 0) {
      uVar13 = 8;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"lsl");
    if (iVar11 == 0) {
      uVar13 = 9;
      goto LAB_00151b48;
    }
    iVar11 = strcmp(pcVar21,"lsr");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"asr"), iVar11 == 0)) {
      uVar13 = 10;
      goto LAB_00151b48;
    }
LAB_00152720:
    iVar10 = strcmp(pcVar21,"ldr");
    uVar24 = local_2a0;
    if (iVar10 != 0) goto LAB_00152b4c;
    if ((int)local_2a0 < 0) goto LAB_00151c88;
    iVar10 = strcmp(pcVar21,"ldrb");
    uVar13 = 1;
    if ((iVar10 != 0) && (iVar10 = strcmp(pcVar21,"ldrh"), uVar13 = local_294, iVar10 == 0)) {
      uVar13 = 2;
    }
  }
  arm64_parse_mem_op_isra_0(local_158 + 0x40,&local_280,&local_278);
  uVar29 = *(uint *)(puVar2 + 2);
  uVar37 = *(uint *)((long)puVar2 + 0x14);
  iVar10 = (int)local_288[2];
  *(int *)(local_288 + 2) = iVar10 + 1;
  if (uVar29 < uVar37) {
    pvVar14 = (void *)puVar2[1];
  }
  else {
    if (uVar37 == 0) {
      sVar25 = 0x880;
      uVar37 = 0x10;
    }
    else {
      uVar37 = uVar37 << 1;
      sVar25 = (ulong)uVar37 * 0x88;
    }
    pvVar14 = realloc((void *)puVar2[1],sVar25);
    if (pvVar14 == (void *)0x0) goto LAB_001525a8;
    uVar29 = *(uint *)(puVar2 + 2);
    puVar2[1] = pvVar14;
    *(uint *)((long)puVar2 + 0x14) = uVar37;
  }
  *(uint *)(puVar2 + 2) = uVar29 + 1;
  puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar29 * 0x88);
  puVar18[0x10] = 0;
  puVar18[1] = 0;
  *puVar18 = 0;
  puVar18[3] = 0;
  puVar18[2] = 0;
  puVar18[5] = 0;
  puVar18[4] = 0;
  puVar18[7] = 0;
  puVar18[6] = 0;
  puVar18[9] = 0;
  puVar18[8] = 0;
  puVar18[0xb] = 0;
  puVar18[10] = 0;
  puVar18[0xd] = 0;
  puVar18[0xc] = 0;
  puVar18[0xf] = 0;
  puVar18[0xe] = 0;
  iVar11 = *(int *)(puVar2 + 2);
  *(undefined4 *)((long)pvVar14 + (ulong)uVar29 * 0x88) = 0x15;
  *(int *)(puVar18 + 1) = iVar10;
  *(undefined4 *)((long)puVar18 + 0xc) = uVar13;
  if (local_280 < 0x20) {
    lVar30 = (long)(int)local_280;
    iVar12 = *(int *)((long)&local_1e8 + lVar30 * 4);
    if (iVar12 != -1) {
      auVar44 = arm_emit_const(puVar2,local_288,CONCAT44(local_278._4_4_,(int)local_278),uVar15);
      if (auVar44._0_4_ == -1) goto LAB_001525a8;
      uVar29 = *(uint *)(puVar2 + 2);
      uVar37 = *(uint *)((long)puVar2 + 0x14);
      iVar3 = (int)local_288[2];
      *(int *)(local_288 + 2) = iVar3 + 1;
      pvVar14 = (void *)puVar2[1];
      if (uVar37 <= uVar29) {
        if (uVar37 == 0) {
          sVar25 = 0x880;
          uVar37 = 0x10;
        }
        else {
          uVar37 = uVar37 << 1;
          sVar25 = (ulong)uVar37 * 0x88;
        }
        pvVar14 = realloc(pvVar14,sVar25);
        if (pvVar14 == (void *)0x0) goto LAB_001525a8;
        puVar2[1] = pvVar14;
        uVar29 = *(uint *)(puVar2 + 2);
        *(uint *)((long)puVar2 + 0x14) = uVar37;
      }
      *(uint *)(puVar2 + 2) = uVar29 + 1;
      lVar34 = (ulong)uVar29 * 0x88;
      uVar43 = *(undefined4 *)((long)&local_270 + lVar30 * 4);
      *(undefined4 *)((long)pvVar14 + lVar34 + 0x84) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0xc) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 4) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x1c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x14) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x2c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x24) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x3c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x34) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x4c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x44) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x5c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x54) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x6c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 100) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x7c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x74) = 0;
      lVar30 = puVar2[1];
      *(undefined4 *)((long)pvVar14 + lVar34) = 2;
      *(int *)((long)pvVar14 + lVar34 + 8) = iVar3;
      *(undefined4 *)((long)pvVar14 + lVar34 + 0xc) = 5;
      *(int *)((long)pvVar14 + lVar34 + 0x18) = iVar12;
      *(undefined4 *)((long)pvVar14 + lVar34 + 0x1c) = uVar43;
      puVar18 = (undefined8 *)(lVar30 + (ulong)(iVar11 - 1) * 0x88);
      *(undefined1 (*) [16])((long)pvVar14 + lVar34 + 0x28) = auVar44;
      *(undefined4 *)((long)pvVar14 + lVar34 + 0x48) = 2;
      *(undefined8 *)((long)pvVar14 + lVar34 + 0x70) = uVar15;
      *(int *)(puVar18 + 3) = iVar3;
      *(undefined4 *)((long)puVar18 + 0x1c) = 5;
      puVar18[4] = 0;
      goto LAB_00152c6c;
    }
  }
  puVar18[3] = DAT_0020a3e8;
LAB_00152c6c:
  puVar18[0xe] = uVar15;
  *(undefined4 *)(puVar18 + 9) = 1;
  lVar28 = lVar28 + 1;
  *(int *)((long)&local_1e8 + (long)(int)uVar24 * 4) = iVar10;
  uVar29 = *(uint *)(lVar1 + 0x18);
  *(undefined4 *)((long)&local_270 + (long)(int)uVar24 * 4) = uVar13;
  if (uVar29 <= (uint)lVar28) goto LAB_00151c9c;
  goto LAB_00151a90;
  while( true ) {
    pcVar32 = pcVar33 + -1;
    *pcVar33 = '\0';
    pcVar33 = pcVar32;
    cVar9 = local_158[0x40];
    if (pcVar32 == pcVar17) break;
LAB_001521d8:
    cVar9 = local_158[0x40];
    if (*pcVar33 != ' ') break;
  }
LAB_001521e8:
  pcVar33 = pcVar17;
  if (cVar9 == ' ') {
    do {
      pcVar33 = pcVar33 + 1;
    } while (*pcVar33 == ' ');
    if (pcVar33 != pcVar17) {
      sVar25 = strlen(pcVar33);
      __memmove_chk(pcVar17,pcVar33,sVar25 + 1,0x40);
    }
  }
LAB_00152228:
  cVar9 = local_158[0x80];
  if (local_158[0x80] == '\0') {
LAB_0015242c:
    local_2a0 = 0xfffffffe;
    local_29c = 0xfffffffe;
    local_298 = 0xfffffffe;
    local_294 = 4;
    local_290 = 4;
    local_28c = 4;
    iVar10 = arm64_reg_lookup(local_158,&local_2a0,&local_294);
    if (iVar10 == 0) goto LAB_001522d4;
LAB_00152458:
    iVar10 = arm64_reg_lookup(pcVar17,&local_29c,&local_290);
  }
  else {
    sVar25 = strlen(__s);
    pcVar33 = __s + (sVar25 - 1);
    if (__s < __s + (sVar25 - 1)) {
      do {
        cVar9 = local_158[0x80];
        if (*pcVar33 != ' ') break;
        pcVar32 = pcVar33 + -1;
        *pcVar33 = '\0';
        pcVar33 = pcVar32;
        cVar9 = local_158[0x80];
      } while (pcVar32 != __s);
    }
    pcVar33 = __s;
    if (cVar9 != ' ') goto LAB_0015242c;
    do {
      pcVar33 = pcVar33 + 1;
    } while (*pcVar33 == ' ');
    if (pcVar33 == __s) goto LAB_0015242c;
    sVar25 = strlen(pcVar33);
    __memmove_chk(__s,pcVar33,sVar25 + 1,0x40);
    local_2a0 = 0xfffffffe;
    local_29c = 0xfffffffe;
    local_298 = 0xfffffffe;
    local_294 = 4;
    local_290 = 4;
    local_28c = 4;
    iVar10 = arm64_reg_lookup(local_158,&local_2a0,&local_294);
    if (iVar10 != 0) goto LAB_00152458;
LAB_001522d4:
    local_2a0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar17,&local_29c,&local_290);
  }
  if (iVar10 == 0) {
    iVar10 = 3;
LAB_00152470:
    pcVar33 = local_158 + 0x40;
    cVar9 = local_158[0x40];
    while (cVar9 == ' ') {
      pcVar33 = pcVar33 + 1;
      cVar9 = *pcVar33;
    }
    if (cVar9 == '#') {
      pcVar32 = pcVar33 + 1;
      pcVar33 = pcVar33 + 1;
      cVar9 = *pcVar32;
      while (cVar9 == ' ') {
        pcVar33 = pcVar33 + 1;
        cVar9 = *pcVar33;
      }
    }
    iVar11 = __isoc99_sscanf(pcVar33,"0x%lx",&local_280);
    if (iVar11 == 1) {
      uVar35 = CONCAT44(uStack_27c,local_280);
      bVar6 = true;
    }
    else {
      iVar11 = __isoc99_sscanf(pcVar33,&DAT_001f84c8,&local_278);
      if (iVar11 == 1) {
        uVar35 = CONCAT44(local_278._4_4_,(int)local_278);
        bVar6 = true;
      }
      else {
        uVar35 = 0;
        bVar6 = false;
      }
    }
    if (iVar10 == 3) {
      iVar10 = arm64_reg_lookup(local_158 + 0x80,&local_298,&local_28c);
      if (iVar10 == 0) goto LAB_00152500;
LAB_00152310:
      iVar10 = 3;
      uVar38 = 0;
      bVar7 = false;
    }
    else {
      iVar10 = 2;
      uVar38 = 0;
      bVar7 = false;
    }
  }
  else {
    uVar35 = 0;
    iVar10 = arm64_reg_lookup(__s,&local_298,&local_28c);
    bVar6 = false;
    if (iVar10 != 0) goto LAB_00152310;
LAB_00152500:
    bVar7 = false;
    pcVar33 = local_158 + 0x80;
    cVar9 = local_158[0x80];
    while (cVar9 == ' ') {
      pcVar33 = pcVar33 + 1;
      cVar9 = *pcVar33;
    }
    if (cVar9 == '#') {
      pcVar32 = pcVar33 + 1;
      pcVar33 = pcVar33 + 1;
      cVar9 = *pcVar32;
      while (cVar9 == ' ') {
        pcVar33 = pcVar33 + 1;
        cVar9 = *pcVar33;
      }
    }
    iVar10 = __isoc99_sscanf(pcVar33,"0x%lx",&local_280);
    if (iVar10 == 1) {
      uVar38 = CONCAT44(uStack_27c,local_280);
      iVar10 = 3;
      bVar7 = true;
    }
    else {
      uVar38 = 0;
      iVar10 = __isoc99_sscanf(pcVar33,&DAT_001f84c8,&local_278);
      if (iVar10 == 1) {
        uVar38 = CONCAT44(local_278._4_4_,(int)local_278);
        iVar10 = 3;
        bVar7 = true;
      }
      else {
        iVar10 = 3;
      }
    }
  }
  goto LAB_0015231c;
LAB_00153794:
  if (((uVar29 == 0x1f) && (lVar30 = CONCAT44(local_278._4_4_,(int)local_278), lVar30 != 0)) &&
     (pcVar21 = strchr(local_158 + 0x80,0x21), pcVar21 != (char *)0x0)) {
    auVar44 = arm_emit_const(puVar2,local_288,lVar30,uVar15);
    iVar10 = (int)local_288[2];
    *(int *)(local_288 + 2) = iVar10 + 1;
    puVar19 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
    if (puVar19 == (undefined4 *)0x0) goto LAB_001525a8;
    *puVar19 = 2;
    puVar19[2] = iVar10;
    puVar19[3] = 5;
    *(undefined8 *)(puVar19 + 4) = 0;
    puVar19[6] = uStack_170._4_4_;
    puVar19[7] = 5;
    *(undefined8 *)(puVar19 + 8) = 0;
    *(undefined1 (*) [16])(puVar19 + 10) = auVar44;
    puVar19[0x12] = 2;
    *(undefined8 *)(puVar19 + 0x1c) = uVar15;
    uStack_170 = CONCAT44(iVar10,(undefined4)uStack_170);
  }
  goto LAB_00151c88;
LAB_001525a8:
  ir_func_destroy(&local_288);
  goto LAB_001525d0;
}

