
/* WARNING: Type propagation algorithm not settling */

void FUN_001516fc(long *param_1,undefined8 param_2,char *param_3,long param_4)

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
  ulong uVar19;
  undefined4 *puVar20;
  char *pcVar21;
  undefined4 *puVar22;
  ulong uVar23;
  ulonglong uVar24;
  uint uVar25;
  size_t sVar26;
  int *piVar27;
  undefined8 uVar28;
  int *__ptr;
  long lVar29;
  uint uVar30;
  long lVar31;
  long lVar32;
  char *pcVar33;
  char *pcVar34;
  uint uVar35;
  long lVar36;
  undefined4 uVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  undefined8 uVar40;
  undefined8 uVar41;
  undefined8 uVar42;
  undefined4 uVar43;
  undefined1 auVar44 [16];
  undefined8 uStack_2e8;
  int iStack_2dc;
  int iStack_2d8;
  int iStack_2d4;
  uint uStack_2a0;
  uint uStack_29c;
  uint uStack_298;
  undefined4 uStack_294;
  undefined4 uStack_290;
  undefined4 uStack_28c;
  long *plStack_288;
  uint uStack_280;
  undefined4 uStack_27c;
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
  undefined8 uStack_200;
  undefined8 uStack_1f8;
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
  undefined8 uStack_168;
  undefined8 uStack_160;
  char acStack_158 [192];
  long lStack_98;
  
  lStack_98 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 != (long *)0x0) && (plStack_288 = calloc(1,0xa0), plStack_288 != (long *)0x0)) {
    *(undefined4 *)(plStack_288 + 2) = 0;
    plStack_288[3] = param_4;
    if ((param_3 == (char *)0x0) || (*param_3 == '\0')) {
      __snprintf_chk(plStack_288 + 4,0x80,2,0x80,"sub_%lx",param_4);
    }
    else {
      snprintf((char *)(plStack_288 + 4),0x80,"%s",param_3);
    }
    uVar8 = DAT_00209d68;
    lVar32 = 0;
    if ((int)param_1[1] != 0) {
      do {
        plVar16 = plStack_288;
        uVar25 = *(uint *)(plStack_288 + 1);
        uVar30 = *(uint *)((long)plStack_288 + 0xc);
        pvVar14 = (void *)*plStack_288;
        lVar1 = *param_1 + lVar32 * 0x20;
        if (uVar30 <= uVar25) {
          if (uVar30 == 0) {
            sVar26 = 0x240;
            uVar30 = 8;
          }
          else {
            uVar30 = uVar30 << 1;
            sVar26 = (ulong)uVar30 * 0x48;
          }
          pvVar14 = realloc(pvVar14,sVar26);
          if (pvVar14 == (void *)0x0) goto LAB_00152408;
          uVar25 = *(uint *)(plVar16 + 1);
          *plVar16 = (long)pvVar14;
          *(uint *)((long)plVar16 + 0xc) = uVar30;
        }
        puVar2 = (undefined8 *)((long)pvVar14 + (ulong)uVar25 * 0x48);
        uStack_1e0 = 0xffffffffffffffff;
        uStack_1e8 = 0xffffffffffffffff;
        uStack_1d0 = 0xffffffffffffffff;
        uStack_1d8 = 0xffffffffffffffff;
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
        uStack_1c8 = 0xffffffffffffffff;
        uStack_1b0 = 0xffffffffffffffff;
        uStack_1b8 = 0xffffffffffffffff;
        *(int *)(plVar16 + 1) = iVar10 + 1;
        *(int *)((long)pvVar14 + (ulong)uVar25 * 0x48) = iVar10;
        *(int *)((long)puVar2 + 0x34) = iVar10;
        uStack_1a0 = 0xffffffffffffffff;
        uStack_1a8 = 0xffffffffffffffff;
        uStack_190 = 0xffffffffffffffff;
        uStack_198 = 0xffffffffffffffff;
        uStack_180 = 0xffffffffffffffff;
        uStack_188 = 0xffffffffffffffff;
        uStack_170 = 0xffffffffffffffff;
        uStack_178 = 0xffffffffffffffff;
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
        uStack_1f8 = 0x400000004;
        uStack_200 = 0x400000004;
        if ((int)lVar32 == 0) {
          iVar10 = (int)plStack_288[2];
          *(int *)(plStack_288 + 2) = iVar10 + 8;
          uStack_1e8 = CONCAT44(iVar10 + 1,iVar10);
          uStack_1e0 = CONCAT44(iVar10 + 3,iVar10 + 2);
          uStack_1d8 = CONCAT44(iVar10 + 5,iVar10 + 4);
          uStack_1d0 = CONCAT44(iVar10 + 7,iVar10 + 6);
        }
        iVar10 = arm_emit_const(puVar2,plStack_288,0,param_4);
        if (iVar10 != -1) {
          uStack_1f8 = CONCAT44(5,(undefined4)uStack_1f8);
          uStack_170 = CONCAT44(iVar10,(undefined4)uStack_170);
        }
        if (*(int *)(lVar1 + 0x18) != 0) {
          lVar29 = 0;
          uStack_2e8 = 0;
          iStack_2dc = -1;
          iStack_2d8 = -1;
          iStack_2d4 = -1;
          uVar41 = uVar8;
          uVar42 = uVar8;
LAB_001518f0:
          lVar31 = *(long *)(lVar1 + 0x10) + lVar29 * 0xe0;
          pcVar21 = (char *)(lVar31 + 0x20);
          uVar15 = *(undefined8 *)(*(long *)(lVar1 + 0x10) + lVar29 * 0xe0);
          cVar9 = *(char *)(lVar31 + 0x60);
          acStack_158[0] = '\0';
          acStack_158[0x40] = '\0';
          acStack_158[0x80] = '\0';
          if (cVar9 != '\0') {
            pcVar34 = (char *)(lVar31 + 0x60);
            iVar10 = 0;
            pcVar33 = pcVar34;
            do {
              while (cVar9 != '[') {
                if (cVar9 == ']') {
                  iVar10 = iVar10 + -1;
                }
                else if (cVar9 == ',' && iVar10 == 0) {
                  sVar26 = (long)pcVar33 - (long)pcVar34;
                  if (0x3f < sVar26) {
                    sVar26 = 0x3f;
                  }
                  memcpy(acStack_158,pcVar34,sVar26);
                  acStack_158[sVar26] = '\0';
                  cVar9 = acStack_158[0];
                  if (acStack_158[0] == '\0') goto LAB_00151ec0;
                  sVar26 = strlen(acStack_158);
                  pcVar34 = acStack_158 + (sVar26 - 1);
                  if (acStack_158 < pcVar34) goto LAB_00151e74;
                  goto LAB_00151e84;
                }
                pcVar33 = pcVar33 + 1;
                cVar9 = *pcVar33;
                if (cVar9 == '\0') goto LAB_00151d60;
              }
              pcVar33 = pcVar33 + 1;
              cVar9 = *pcVar33;
              iVar10 = iVar10 + 1;
            } while (cVar9 != '\0');
LAB_00151d60:
            snprintf(acStack_158,0x40,"%s",pcVar34);
            cVar9 = acStack_158[0];
            if (acStack_158[0] != '\0') {
              sVar26 = strlen(acStack_158);
              pcVar34 = acStack_158 + (sVar26 - 1);
              if (acStack_158 < pcVar34) {
                do {
                  cVar9 = acStack_158[0];
                  if (*pcVar34 != ' ') break;
                  pcVar33 = pcVar34 + -1;
                  *pcVar34 = '\0';
                  pcVar34 = pcVar33;
                  cVar9 = acStack_158[0];
                } while (pcVar33 != acStack_158);
              }
              pcVar34 = acStack_158;
              if (cVar9 == ' ') {
                do {
                  pcVar34 = pcVar34 + 1;
                } while (*pcVar34 == ' ');
                if (pcVar34 != acStack_158) {
                  sVar26 = strlen(pcVar34);
                  __memmove_chk(acStack_158,pcVar34,sVar26 + 1,0x40);
                }
              }
            }
            uStack_298 = 0xfffffffe;
            uStack_29c = 0xfffffffe;
            uStack_2a0 = 0xfffffffe;
            uStack_294 = 4;
            uStack_290 = 4;
            uStack_28c = 4;
            iVar10 = arm64_reg_lookup(acStack_158,&uStack_2a0,&uStack_294);
            if (iVar10 == 0) {
              iVar10 = 1;
              goto LAB_0015193c;
            }
            lVar36 = 0;
            iVar10 = 1;
            bVar6 = false;
            uVar38 = 0;
            bVar7 = false;
            goto LAB_0015217c;
          }
          iVar10 = 0;
          uStack_29c = 0xfffffffe;
          uStack_298 = 0xfffffffe;
          uStack_294 = 4;
          uStack_290 = 4;
          uStack_28c = 4;
LAB_0015193c:
          uStack_2a0 = 0xfffffffe;
          iVar11 = strcmp(pcVar21,"adrp");
          if (iVar11 != 0) {
            lVar36 = 0;
            bVar6 = false;
            uVar38 = 0;
            bVar7 = false;
            goto LAB_0015195c;
          }
          goto LAB_00151ae8;
        }
LAB_00151afc:
        lVar32 = lVar32 + 1;
      } while ((uint)lVar32 < *(uint *)(param_1 + 1));
    }
    lVar32 = 0;
    uVar25 = *(uint *)(param_1 + 3);
    plVar16 = plStack_288;
    if (uVar25 != 0) {
      do {
        uVar30 = *(uint *)(param_1[2] + lVar32 * 0xc + 4);
        if (uVar30 != 0xffffffff) {
          uVar4 = *(uint *)(param_1[2] + lVar32 * 0xc);
          uVar35 = uVar30;
          if (uVar30 < uVar4) {
            uVar35 = uVar4;
          }
          if (uVar35 < *(uint *)(plVar16 + 1)) {
            lVar36 = *plVar16;
            lVar31 = (ulong)uVar30 * 0x48;
            lVar1 = lVar36 + (ulong)uVar4 * 0x48;
            lVar29 = lVar36 + lVar31;
            uVar30 = *(uint *)(lVar1 + 0x30);
            __ptr = *(int **)(lVar1 + 0x28);
            if (uVar30 == 0) {
              sVar26 = 4;
            }
            else {
              piVar27 = __ptr;
              do {
                if (*piVar27 == *(int *)(lVar36 + lVar31)) goto LAB_00151b48;
                piVar27 = piVar27 + 1;
              } while (__ptr + uVar30 != piVar27);
              sVar26 = (ulong)(uVar30 + 1) << 2;
            }
            pvVar14 = realloc(__ptr,sVar26);
            if (pvVar14 == (void *)0x0) goto LAB_00152408;
            uVar25 = *(uint *)(lVar1 + 0x30);
            uVar13 = *(undefined4 *)(lVar36 + lVar31);
            *(void **)(lVar1 + 0x28) = pvVar14;
            *(uint *)(lVar1 + 0x30) = uVar25 + 1;
            *(undefined4 *)((long)pvVar14 + (ulong)uVar25 * 4) = uVar13;
            pvVar14 = realloc(*(void **)(lVar29 + 0x18),(ulong)(*(int *)(lVar29 + 0x20) + 1) << 2);
            if (pvVar14 == (void *)0x0) goto LAB_00152408;
            uVar25 = *(uint *)(lVar29 + 0x20);
            uVar13 = *(undefined4 *)(lVar36 + (ulong)uVar4 * 0x48);
            *(void **)(lVar29 + 0x18) = pvVar14;
            *(uint *)(lVar29 + 0x20) = uVar25 + 1;
            *(undefined4 *)((long)pvVar14 + (ulong)uVar25 * 4) = uVar13;
            uVar25 = *(uint *)(param_1 + 3);
            plVar16 = plStack_288;
          }
        }
LAB_00151b48:
        lVar32 = lVar32 + 1;
      } while ((uint)lVar32 < uVar25);
    }
    goto LAB_00152434;
  }
LAB_00152430:
  plVar16 = (long *)0x0;
LAB_00152434:
  if (lStack_98 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(plVar16,PTR___stack_chk_guard_005ffe88,0,
                     lStack_98 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
  while( true ) {
    pcVar17 = pcVar34 + -1;
    *pcVar34 = '\0';
    pcVar34 = pcVar17;
    cVar9 = acStack_158[0];
    if (pcVar17 == acStack_158) break;
LAB_00151e74:
    cVar9 = acStack_158[0];
    if (*pcVar34 != ' ') break;
  }
LAB_00151e84:
  pcVar34 = acStack_158;
  if (cVar9 == ' ') {
    do {
      pcVar34 = pcVar34 + 1;
    } while (*pcVar34 == ' ');
    if (pcVar34 != acStack_158) {
      sVar26 = strlen(pcVar34);
      __memmove_chk(acStack_158,pcVar34,sVar26 + 1,0x40);
    }
  }
LAB_00151ec0:
  cVar9 = pcVar33[1];
  pcVar33 = pcVar33 + 1;
  if (cVar9 != '\0') {
    iVar10 = 0;
    pcVar34 = pcVar33;
    do {
      while (cVar9 != '[') {
        if (cVar9 == ']') {
          iVar10 = iVar10 + -1;
        }
        else if (cVar9 == ',' && iVar10 == 0) {
          sVar26 = (long)pcVar34 - (long)pcVar33;
          pcVar17 = acStack_158 + 0x40;
          if (0x3f < sVar26) {
            sVar26 = 0x3f;
          }
          __s = acStack_158 + 0x80;
          memcpy(pcVar17,pcVar33,sVar26);
          pcVar17[sVar26] = '\0';
          snprintf(__s,0x40,"%s",pcVar34 + 1);
          cVar9 = acStack_158[0x40];
          if (acStack_158[0x40] == '\0') goto LAB_00152088;
          sVar26 = strlen(pcVar17);
          pcVar34 = pcVar17 + (sVar26 - 1);
          if (pcVar17 < pcVar17 + (sVar26 - 1)) goto LAB_00152038;
          goto LAB_00152048;
        }
        pcVar34 = pcVar34 + 1;
        cVar9 = *pcVar34;
        if (cVar9 == '\0') goto LAB_00151f08;
      }
      pcVar34 = pcVar34 + 1;
      cVar9 = *pcVar34;
      iVar10 = iVar10 + 1;
    } while (cVar9 != '\0');
  }
LAB_00151f08:
  pcVar34 = acStack_158 + 0x40;
  snprintf(pcVar34,0x40,"%s",pcVar33);
  cVar9 = acStack_158[0x40];
  if (acStack_158[0x40] != '\0') {
    sVar26 = strlen(pcVar34);
    pcVar33 = pcVar34 + (sVar26 - 1);
    if (pcVar34 < pcVar34 + (sVar26 - 1)) {
      do {
        cVar9 = acStack_158[0x40];
        if (*pcVar33 != ' ') break;
        pcVar17 = pcVar33 + -1;
        *pcVar33 = '\0';
        pcVar33 = pcVar17;
        cVar9 = acStack_158[0x40];
      } while (pcVar17 != pcVar34);
    }
    pcVar33 = pcVar34;
    if (cVar9 == ' ') {
      do {
        pcVar33 = pcVar33 + 1;
      } while (*pcVar33 == ' ');
      if (pcVar33 != pcVar34) {
        sVar26 = strlen(pcVar33);
        __memmove_chk(pcVar34,pcVar33,sVar26 + 1,0x40);
      }
    }
  }
  uStack_298 = 0xfffffffe;
  uStack_29c = 0xfffffffe;
  uStack_2a0 = 0xfffffffe;
  uStack_294 = 4;
  uStack_290 = 4;
  uStack_28c = 4;
  iVar10 = arm64_reg_lookup(acStack_158,&uStack_2a0,&uStack_294);
  if (iVar10 == 0) {
    uStack_2a0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar34,&uStack_29c,&uStack_290);
  }
  else {
    iVar10 = arm64_reg_lookup(pcVar34,&uStack_29c,&uStack_290);
  }
  if (iVar10 == 0) {
    iVar10 = 2;
    goto LAB_001522d0;
  }
  lVar36 = 0;
  iVar10 = 2;
  bVar6 = false;
  uVar38 = 0;
  bVar7 = false;
LAB_0015217c:
  iVar11 = strcmp(pcVar21,"adrp");
  uVar25 = uStack_2a0;
  if (iVar11 == 0) {
    if ((int)uStack_2a0 < 0) goto LAB_00151ae8;
    if (!bVar6) {
      if (iVar10 == 1) goto LAB_001521a4;
      pcVar21 = acStack_158 + 0x40;
      cVar9 = acStack_158[0x40];
      while (cVar9 == ' ') {
        pcVar21 = pcVar21 + 1;
        cVar9 = *pcVar21;
      }
      if (cVar9 == '#') {
        pcVar34 = pcVar21 + 1;
        pcVar21 = pcVar21 + 1;
        cVar9 = *pcVar34;
        while (cVar9 == ' ') {
          pcVar21 = pcVar21 + 1;
          cVar9 = *pcVar21;
        }
      }
      iVar10 = __isoc99_sscanf(pcVar21,"0x%lx",&uStack_280);
      if (iVar10 == 1) {
        lVar36 = CONCAT44(uStack_27c,uStack_280);
      }
      else {
        iVar10 = __isoc99_sscanf(pcVar21,&DAT_001f7eb0,&uStack_278);
        if (iVar10 != 1) goto LAB_001521a4;
        lVar36 = CONCAT44(uStack_278._4_4_,(int)uStack_278);
      }
    }
    if (lVar36 != 0) {
      iVar10 = arm_emit_const(puVar2,plStack_288,lVar36,uVar15);
      if (iVar10 == -1) goto LAB_00152408;
      lVar29 = lVar29 + 1;
      *(int *)((long)&uStack_1e8 + (long)(int)uVar25 * 4) = iVar10;
      uVar30 = *(uint *)(lVar1 + 0x18);
      *(undefined4 *)((long)&uStack_270 + (long)(int)uVar25 * 4) = 5;
      if (uVar30 <= (uint)lVar29) goto LAB_00151afc;
      goto LAB_001518f0;
    }
LAB_001521a4:
    lVar31 = plStack_288[2];
    lVar29 = lVar29 + 1;
    *(undefined4 *)((long)&uStack_270 + (long)(int)uVar25 * 4) = 5;
    *(int *)(plStack_288 + 2) = (int)lVar31 + 1;
    *(int *)((long)&uStack_1e8 + (long)(int)uVar25 * 4) = (int)lVar31;
    if (*(uint *)(lVar1 + 0x18) <= (uint)lVar29) goto LAB_00151afc;
    goto LAB_001518f0;
  }
LAB_0015195c:
  iVar11 = strcmp(pcVar21,"mov");
  if (((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"movz"), iVar11 == 0)) ||
     (iVar11 = strcmp(pcVar21,"movk"), iVar11 == 0)) {
    uVar25 = uStack_2a0;
    if (-1 < (int)uStack_2a0) {
      uVar30 = *(uint *)(puVar2 + 2);
      uVar35 = *(uint *)((long)puVar2 + 0x14);
      iVar10 = (int)plStack_288[2];
      pvVar14 = (void *)puVar2[1];
      *(int *)(plStack_288 + 2) = iVar10 + 1;
      if (uVar35 <= uVar30) {
        if (uVar35 == 0) {
          sVar26 = 0x880;
          uVar35 = 0x10;
        }
        else {
          uVar35 = uVar35 << 1;
          sVar26 = (ulong)uVar35 * 0x88;
        }
        pvVar14 = realloc(pvVar14,sVar26);
        if (pvVar14 == (void *)0x0) goto LAB_00152408;
        uVar30 = *(uint *)(puVar2 + 2);
        puVar2[1] = pvVar14;
        *(uint *)((long)puVar2 + 0x14) = uVar35;
      }
      *(uint *)(puVar2 + 2) = uVar30 + 1;
      puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar30 * 0x88);
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
      if (uStack_29c < 0x20) {
        iVar11 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_29c * 4);
        if (iVar11 == -1) {
          iVar11 = (int)plStack_288[2];
          *(int *)(plStack_288 + 2) = iVar11 + 1;
        }
        lVar36 = 0;
        *(int *)(puVar18 + 3) = iVar11;
        *(undefined4 *)((long)puVar18 + 0x1c) = uStack_290;
        puVar18[4] = 0;
        *(undefined4 *)(puVar18 + 9) = 1;
      }
      else if ((uStack_29c == 0xffffffff) || (!bVar6)) {
        lVar36 = 0;
        *(undefined4 *)puVar18 = 1;
      }
      else {
        *(undefined4 *)puVar18 = 1;
      }
      *(int *)(puVar18 + 1) = iVar10;
      *(undefined4 *)((long)puVar18 + 0xc) = uStack_294;
      puVar18[2] = lVar36;
      lVar29 = lVar29 + 1;
      *(int *)((long)&uStack_1e8 + (long)(int)uVar25 * 4) = iVar10;
      *(undefined4 *)((long)&uStack_270 + (long)(int)uVar25 * 4) = uStack_294;
      puVar18[0xe] = uVar15;
      if (*(uint *)(lVar1 + 0x18) <= (uint)lVar29) goto LAB_00151afc;
      goto LAB_001518f0;
    }
    goto LAB_00151ae8;
  }
  iVar11 = strcmp(pcVar21,"add");
  if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"adds"), iVar11 == 0)) {
    uVar13 = 2;
LAB_001519a8:
    uVar43 = uStack_294;
    uVar25 = uStack_2a0;
    if (iVar10 == 3) {
      if (-1 < (int)uStack_2a0) {
        if (uStack_29c < 0x20) {
          iVar10 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_29c * 4);
          if (iVar10 == -1) {
            iVar10 = (int)plStack_288[2];
            *(int *)(plStack_288 + 2) = iVar10 + 1;
          }
          uVar28 = 0;
          uVar43 = uStack_290;
        }
        else if (uStack_29c == 0xffffffff) {
          auVar44 = arm_emit_const(puVar2,plStack_288,0,uVar15);
          uVar28 = auVar44._8_8_;
          iVar10 = auVar44._0_4_;
          uVar43 = auVar44._4_4_;
          if (iVar10 == -1) goto LAB_00152408;
        }
        else {
          iVar10 = (int)plStack_288[2];
          uVar28 = 0;
          *(int *)(plStack_288 + 2) = iVar10 + 1;
        }
        if (uStack_298 < 0x20) {
          iVar3 = (int)plStack_288[2];
          iVar12 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_298 * 4);
          iVar11 = iVar3;
          if (iVar12 == -1) {
            iVar11 = iVar3 + 1;
            *(int *)(plStack_288 + 2) = iVar11;
            iVar12 = iVar3;
          }
          uVar38 = 0;
          uVar37 = uStack_28c;
        }
        else {
          if (uStack_298 == 0xffffffff) {
            uVar38 = 0;
          }
          else if (!bVar7) {
            iVar12 = (int)plStack_288[2];
            uVar38 = 0;
            iVar11 = iVar12 + 1;
            *(int *)(plStack_288 + 2) = iVar11;
            uVar37 = uStack_294;
            goto LAB_00151a24;
          }
          auVar44 = arm_emit_const(puVar2,plStack_288,uVar38,uVar15);
          uVar38 = auVar44._8_8_;
          iVar12 = auVar44._0_4_;
          uVar37 = auVar44._4_4_;
          if (iVar12 == -1) goto LAB_00152408;
          iVar11 = (int)plStack_288[2];
        }
LAB_00151a24:
        uVar30 = *(uint *)(puVar2 + 2);
        uVar35 = *(uint *)((long)puVar2 + 0x14);
        *(int *)(plStack_288 + 2) = iVar11 + 1;
        pvVar14 = (void *)puVar2[1];
        if (uVar35 <= uVar30) {
          if (uVar35 == 0) {
            sVar26 = 0x880;
            uVar35 = 0x10;
          }
          else {
            uVar35 = uVar35 << 1;
            sVar26 = (ulong)uVar35 * 0x88;
          }
          pvVar14 = realloc(pvVar14,sVar26);
          if (pvVar14 == (void *)0x0) goto LAB_00152408;
          puVar2[1] = pvVar14;
          uVar30 = *(uint *)(puVar2 + 2);
          *(uint *)((long)puVar2 + 0x14) = uVar35;
        }
        puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar30 * 0x88);
        *(uint *)(puVar2 + 2) = uVar30 + 1;
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
        *(undefined4 *)((long)pvVar14 + (ulong)uVar30 * 0x88) = uVar13;
        *(int *)((long)&uStack_1e8 + (long)(int)uVar25 * 4) = iVar11;
        *(undefined4 *)((long)&uStack_270 + (long)(int)uVar25 * 4) = uStack_294;
        *(int *)(puVar18 + 1) = iVar11;
        *(undefined4 *)((long)puVar18 + 0xc) = uStack_294;
        *(int *)(puVar18 + 3) = iVar10;
        *(undefined4 *)((long)puVar18 + 0x1c) = uVar43;
        puVar18[4] = uVar28;
        *(int *)(puVar18 + 5) = iVar12;
        *(undefined4 *)((long)puVar18 + 0x2c) = uVar37;
        puVar18[6] = uVar38;
        *(undefined4 *)(puVar18 + 9) = 2;
        puVar18[0xe] = uVar15;
        goto LAB_00151ae8;
      }
    }
    else {
      if (iVar10 != 2) goto LAB_00152580;
      if (-1 < (int)uStack_2a0) {
        lVar31 = (long)(int)uStack_2a0;
        iVar10 = *(int *)((long)&uStack_1e8 + lVar31 * 4);
        if (iVar10 == -1) {
          iVar10 = (int)plStack_288[2];
          *(int *)(plStack_288 + 2) = iVar10 + 1;
        }
        if (uStack_29c < 0x20) {
          iVar3 = (int)plStack_288[2];
          iVar12 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_29c * 4);
          iVar11 = iVar3;
          if (iVar12 == -1) {
            iVar11 = iVar3 + 1;
            *(int *)(plStack_288 + 2) = iVar11;
            iVar12 = iVar3;
          }
          uVar38 = 0;
          uVar37 = uStack_290;
        }
        else if (bVar6) {
          auVar44 = arm_emit_const(puVar2,plStack_288,lVar36,uVar15);
          uVar38 = auVar44._8_8_;
          iVar12 = auVar44._0_4_;
          uVar37 = auVar44._4_4_;
          if (iVar12 == -1) goto LAB_00152408;
          iVar11 = (int)plStack_288[2];
        }
        else {
          iVar12 = (int)plStack_288[2];
          uVar38 = 0;
          iVar11 = iVar12 + 1;
          *(int *)(plStack_288 + 2) = iVar11;
          uVar37 = uStack_294;
        }
        uVar25 = *(uint *)(puVar2 + 2);
        uVar30 = *(uint *)((long)puVar2 + 0x14);
        *(int *)(plStack_288 + 2) = iVar11 + 1;
        pvVar14 = (void *)puVar2[1];
        if (uVar30 <= uVar25) {
          if (uVar30 == 0) {
            sVar26 = 0x880;
            uVar30 = 0x10;
          }
          else {
            uVar30 = uVar30 << 1;
            sVar26 = (ulong)uVar30 * 0x88;
          }
          pvVar14 = realloc(pvVar14,sVar26);
          if (pvVar14 == (void *)0x0) goto LAB_00152408;
          uVar25 = *(uint *)(puVar2 + 2);
          puVar2[1] = pvVar14;
          *(uint *)((long)puVar2 + 0x14) = uVar30;
        }
        *(int *)((long)&uStack_1e8 + lVar31 * 4) = iVar11;
        *(uint *)(puVar2 + 2) = uVar25 + 1;
        *(undefined4 *)((long)&uStack_270 + lVar31 * 4) = uVar43;
        puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar25 * 0x88);
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
        *(undefined4 *)((long)pvVar14 + (ulong)uVar25 * 0x88) = uVar13;
        *(int *)(puVar18 + 1) = iVar11;
        *(undefined4 *)((long)puVar18 + 0xc) = uVar43;
        *(int *)(puVar18 + 3) = iVar10;
        *(undefined4 *)((long)puVar18 + 0x1c) = uVar43;
        *(int *)(puVar18 + 5) = iVar12;
        *(undefined4 *)((long)puVar18 + 0x2c) = uVar37;
        puVar18[6] = uVar38;
        *(undefined4 *)(puVar18 + 9) = 2;
        puVar18[0xe] = uVar15;
        goto LAB_00151ae8;
      }
    }
    iVar10 = strcmp(pcVar21,"ldr");
    if (iVar10 == 0) goto LAB_00151ae8;
LAB_001529b4:
    iVar10 = strcmp(pcVar21,"ldrb");
    if (iVar10 == 0) {
      uVar13 = 1;
      uVar25 = uStack_2a0;
    }
    else {
      iVar10 = strcmp(pcVar21,"ldrh");
      if (iVar10 == 0) {
        uVar13 = 2;
        uVar25 = uStack_2a0;
      }
      else {
        iVar10 = strcmp(pcVar21,"ldrsw");
        uVar25 = uStack_2a0;
        uVar13 = uStack_294;
        if (iVar10 != 0) {
          iVar10 = strcmp(pcVar21,"str");
          if (((iVar10 != 0) && (iVar10 = strcmp(pcVar21,"strb"), iVar10 != 0)) &&
             (iVar10 = strcmp(pcVar21,"strh"), iVar10 != 0)) {
            iVar10 = strcmp(pcVar21,"ldp");
            if (iVar10 == 0) {
              arm64_parse_mem_op_isra_0(acStack_158 + 0x80,&uStack_280,&uStack_278);
              uVar19 = (ulong)uStack_2a0;
              if ((int)uStack_2a0 < 0) {
                lVar31 = 1;
                goto LAB_0015335c;
              }
              lVar31 = 0;
              uVar13 = uStack_294;
LAB_00153240:
              do {
                iVar10 = (int)plStack_288[2];
                *(int *)(plStack_288 + 2) = iVar10 + 1;
                puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                iVar11 = *(int *)(puVar2 + 2);
                *puVar20 = 0x15;
                puVar20[2] = iVar10;
                puVar20[3] = uVar13;
                *(undefined8 *)(puVar20 + 4) = 0;
                if ((uStack_280 < 0x20) &&
                   (iVar12 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_280 * 4), iVar12 != -1))
                {
                  auVar44 = arm_emit_const(puVar2,plStack_288,
                                           CONCAT44(uStack_278._4_4_,(int)uStack_278) + lVar31 * 8,
                                           uVar15);
                  if (auVar44._0_4_ == -1) goto LAB_00152408;
                  iVar3 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar3 + 1;
                  puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                  puVar20 = (undefined4 *)(puVar2[1] + (ulong)(iVar11 - 1) * 0x88);
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
                  puVar20[6] = iVar3;
                  puVar20[7] = 5;
                  *(undefined8 *)(puVar20 + 8) = 0;
                }
                else {
                  *(undefined8 *)(puVar20 + 8) = 0;
                  *(undefined8 *)(puVar20 + 6) = DAT_00209d70;
                }
                puVar20[0x12] = 1;
                *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                if ((int)uVar19 < 0x20) {
                  uVar19 = -(uVar19 >> 0x1f) & 0xfffffffc00000000 | uVar19 << 2;
                  *(int *)((long)&uStack_1e8 + uVar19) = iVar10;
                  *(undefined4 *)((long)&uStack_270 + uVar19) = uVar13;
                }
                lVar31 = lVar31 + 1;
                if (lVar31 == 2) break;
LAB_0015335c:
                for (; (int)lVar31 == 0; lVar31 = lVar31 + 1) {
                  uVar19 = (ulong)uStack_2a0;
                  uVar13 = uStack_294;
                  if (-1 < (int)uStack_2a0) goto LAB_00153240;
                }
                uVar19 = (ulong)uStack_29c;
                uVar13 = uStack_290;
              } while (-1 < (int)uStack_29c);
              goto LAB_00151ae8;
            }
            iVar10 = strcmp(pcVar21,"stp");
            if (iVar10 == 0) {
              arm64_parse_mem_op_isra_0(acStack_158 + 0x80,&uStack_280,&uStack_278);
              uVar38 = DAT_00209d70;
              lVar31 = 0;
              uVar13 = uStack_294;
              uVar25 = uStack_2a0;
              do {
                puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                uVar30 = uStack_280;
                if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                iVar10 = *(int *)(puVar2 + 2);
                *puVar20 = 0x16;
                *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                if ((uStack_280 < 0x20) &&
                   (iVar11 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_280 * 4), iVar11 != -1))
                {
                  auVar44 = arm_emit_const(puVar2,plStack_288,
                                           CONCAT44(uStack_278._4_4_,(int)uStack_278) + lVar31 * 8,
                                           uVar15);
                  iVar12 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar12 + 1;
                  puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                  lVar36 = puVar2[1];
                  *(long *)(puVar22 + 0xc) = auVar44._8_8_;
                  puVar20 = (undefined4 *)(lVar36 + (ulong)(iVar10 - 1U) * 0x88);
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
                  puVar20[6] = iVar12;
                  puVar20[7] = 5;
                  *(undefined8 *)(puVar20 + 8) = 0;
                }
                else {
                  *(undefined8 *)(puVar20 + 6) = uVar38;
                  *(undefined8 *)(puVar20 + 8) = 0;
                }
                if (uVar25 == 0xffffffff) {
                  auVar44 = arm_emit_const(puVar2,plStack_288,0,uVar15);
                  if (auVar44._0_4_ == -1) goto LAB_00152408;
                  puVar20 = (undefined4 *)(puVar2[1] + (ulong)(iVar10 - 1U) * 0x88);
                  *(undefined1 (*) [16])(puVar20 + 10) = auVar44;
                }
                else {
                  if (uVar25 < 0x20) {
                    uVar19 = -(ulong)(uVar25 >> 0x1f) & 0xfffffffc00000000 | (ulong)uVar25 << 2;
                    iVar10 = *(int *)((long)&uStack_1e8 + uVar19);
                    if (iVar10 == -1) goto LAB_001536a0;
                    uVar13 = *(undefined4 *)((long)&uStack_270 + uVar19);
                  }
                  else {
LAB_001536a0:
                    iVar10 = (int)plStack_288[2];
                    *(int *)(plStack_288 + 2) = iVar10 + 1;
                  }
                  puVar20[10] = iVar10;
                  puVar20[0xb] = uVar13;
                  *(undefined8 *)(puVar20 + 0xc) = 0;
                }
                puVar20[0x12] = 2;
                *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                if (lVar31 != 0) goto LAB_00153604;
                lVar31 = 1;
                uVar13 = uStack_290;
                uVar25 = uStack_29c;
              } while( true );
            }
            iVar10 = strcmp(pcVar21,"cmp");
            if (iVar10 == 0) {
              if (uStack_2a0 < 0x20) {
                iStack_2d8 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_2a0 * 4);
                uVar13 = uStack_294;
                if (iStack_2d8 == -1) {
                  iStack_2d8 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iStack_2d8 + 1;
                }
              }
              else {
                iStack_2d8 = (int)plStack_288[2];
                *(int *)(plStack_288 + 2) = iStack_2d8 + 1;
                uVar13 = 4;
              }
              uVar42 = CONCAT44(uVar13,iStack_2d8);
              if (uStack_29c < 0x20) {
                iStack_2dc = *(int *)((long)&uStack_1e8 + (long)(int)uStack_29c * 4);
                if (iStack_2dc == -1) {
                  iStack_2dc = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iStack_2dc + 1;
                }
                uStack_2e8 = 0;
                uVar43 = uStack_290;
              }
              else {
                if (uStack_29c == 0xffffffff) {
                  lVar36 = 0;
                }
                else if (!bVar6) {
                  iStack_2dc = (int)plStack_288[2];
                  uVar43 = 4;
                  uStack_2e8 = 0;
                  *(int *)(plStack_288 + 2) = iStack_2dc + 1;
                  goto LAB_00152d40;
                }
                auVar44 = arm_emit_const(puVar2,plStack_288,lVar36,uVar15);
                uStack_2e8 = auVar44._8_8_;
                iStack_2dc = auVar44._0_4_;
                uVar43 = auVar44._4_4_;
                if (iStack_2dc == -1) goto LAB_00152408;
              }
LAB_00152d40:
              iStack_2d4 = (int)plStack_288[2];
              uVar25 = *(uint *)(puVar2 + 2);
              uVar30 = *(uint *)((long)puVar2 + 0x14);
              *(int *)(plStack_288 + 2) = iStack_2d4 + 1;
              uVar41 = CONCAT44(uVar43,iStack_2dc);
              if (uVar30 <= uVar25) {
                uVar35 = uVar30 << 1;
                if (uVar30 == 0) {
                  uVar35 = 0x10;
                }
                pvVar14 = realloc((void *)puVar2[1],(ulong)uVar35 * 0x88);
                if (pvVar14 == (void *)0x0) goto LAB_00152408;
                uVar25 = *(uint *)(puVar2 + 2);
                puVar2[1] = pvVar14;
                *(uint *)((long)puVar2 + 0x14) = uVar35;
              }
              lVar31 = puVar2[1];
              *(uint *)(puVar2 + 2) = uVar25 + 1;
              puVar18 = (undefined8 *)(lVar31 + (ulong)uVar25 * 0x88);
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
              *(undefined4 *)(lVar31 + (ulong)uVar25 * 0x88) = 0xb;
              *(int *)(puVar18 + 1) = iStack_2d4;
              *(undefined4 *)((long)puVar18 + 0xc) = 6;
              *(undefined4 *)((long)puVar18 + 0x1c) = uVar13;
              *(int *)(puVar18 + 3) = iStack_2d8;
              *(int *)(puVar18 + 5) = iStack_2dc;
              puVar18[6] = uStack_2e8;
              *(undefined4 *)((long)puVar18 + 0x2c) = uVar43;
              *(undefined4 *)(puVar18 + 9) = 2;
              puVar18[0xe] = uVar15;
              goto LAB_00151ae8;
            }
            iVar10 = strcmp(pcVar21,"cbz");
            if (iVar10 == 0) {
              uVar13 = 0xb;
            }
            else {
              iVar10 = strcmp(pcVar21,"cbnz");
              if (iVar10 != 0) {
                if ((*(char *)(lVar31 + 0x20) == 'b') && (*(char *)(lVar31 + 0x21) == '.')) {
                  if (iStack_2d8 == -1 || iStack_2dc == -1) {
LAB_00153ad8:
                    iVar10 = iStack_2d4;
                    if (iStack_2d4 == -1) {
                      iVar10 = (int)plStack_288[2];
                      *(int *)(plStack_288 + 2) = iVar10 + 1;
                    }
                  }
                  else {
                    uVar13 = arm64_cond_suffix_to_cmp(lVar31 + 0x22,&uStack_278);
                    iVar10 = (int)plStack_288[2];
                    *(int *)(plStack_288 + 2) = iVar10 + 1;
                    puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                    if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                    *puVar20 = uVar13;
                    puVar20[2] = iVar10;
                    puVar20[3] = 6;
                    *(undefined8 *)(puVar20 + 4) = 0;
                    if ((int)uStack_278 == 0) {
                      uVar38 = uStack_2e8;
                      uVar28 = 0;
                      uVar39 = uVar41;
                      uVar40 = uVar42;
                    }
                    else {
                      uVar38 = 0;
                      uVar28 = uStack_2e8;
                      uVar39 = uVar42;
                      uVar40 = uVar41;
                    }
                    *(undefined8 *)(puVar20 + 0xc) = uVar38;
                    *(undefined8 *)(puVar20 + 6) = uVar40;
                    *(undefined8 *)(puVar20 + 8) = uVar28;
                    *(undefined8 *)(puVar20 + 10) = uVar39;
                    puVar20[0x12] = 2;
                    *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                    if (iVar10 == -1) goto LAB_00153ad8;
                  }
                  puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                  puVar20[0x12] = 1;
                  *puVar20 = 0x17;
                  *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                  puVar20[6] = iVar10;
                  puVar20[7] = 6;
                  *(undefined8 *)(puVar20 + 8) = 0;
                  *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                  goto LAB_00151ae8;
                }
                iVar10 = strcmp(pcVar21,"csel");
                uVar25 = uStack_2a0;
                if (iVar10 != 0) {
                  iVar10 = strcmp(pcVar21,"bl");
                  if (iVar10 == 0) {
                    iVar10 = (int)plStack_288[2];
                    *(int *)(plStack_288 + 2) = iVar10 + 1;
                    puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                    if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                    *puVar20 = 0x19;
                    puVar20[2] = iVar10;
                    puVar20[3] = 4;
                    *(undefined8 *)(puVar20 + 4) = 0;
                    if (acStack_158[0] == '#') {
                      uVar24 = strtoull(acStack_158 + 1,(char **)0x0,0);
                    }
                    else if (acStack_158[0] == '0') {
                      uVar24 = strtoull(acStack_158,(char **)0x0,0);
                    }
                    else {
                      uVar24 = 0;
                    }
                    puVar20[0x12] = 1;
                    *(ulonglong *)(puVar20 + 8) = uVar24;
                    *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                    uVar19 = 0;
                    *(undefined8 *)(puVar20 + 6) = DAT_00209d70;
                    do {
                      if (*(int *)((long)&uStack_1e8 + uVar19 * 4) == -1) {
                        if ((int)uVar19 == 0) goto LAB_0015400c;
                        break;
                      }
                      uVar19 = uVar19 + 1;
                    } while (uVar19 != 8);
                    puVar22 = malloc(-((uVar19 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                     (uVar19 & 0xffffffff) << 4);
                    *(undefined4 **)(puVar20 + 0x14) = puVar22;
                    if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                    lVar31 = 0;
                    *(undefined8 *)(puVar20 + 0x16) = 0;
                    puVar20[0x18] = (int)uVar19;
                    do {
                      uVar13 = *(undefined4 *)((long)&uStack_270 + lVar31 * 4);
                      lVar36 = lVar31 * 4;
                      lVar31 = lVar31 + 1;
                      *puVar22 = *(undefined4 *)((long)&uStack_1e8 + lVar36);
                      puVar22[1] = uVar13;
                      *(undefined8 *)(puVar22 + 2) = 0;
                      puVar22 = puVar22 + 4;
                    } while ((int)lVar31 < (int)uVar19);
LAB_0015400c:
                    uStack_270 = CONCAT44(uStack_270._4_4_,4);
                    uStack_1e8 = CONCAT44(uStack_1e8._4_4_,iVar10);
                    goto LAB_00151ae8;
                  }
                  iVar10 = strcmp(pcVar21,"blr");
                  if (iVar10 != 0) {
                    iVar10 = strcmp(pcVar21,"b");
                    if (iVar10 == 0) {
                      for (pcVar21 = acStack_158; cVar9 = *pcVar21, cVar9 == ' ' || cVar9 == '#';
                          pcVar21 = pcVar21 + 1) {
                      }
                      if ((cVar9 == '\0') ||
                         (uVar24 = strtoull(pcVar21,(char **)&uStack_278,0),
                         (char *)CONCAT44(uStack_278._4_4_,(int)uStack_278) == pcVar21)) {
LAB_00153c1c:
                        puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                        *puVar20 = 0x18;
                        puVar20[0x12] = 0;
                        *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                        *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                      }
                      else {
                        for (lVar31 = 0; (uint)lVar31 < *(uint *)(param_1 + 1); lVar31 = lVar31 + 1)
                        {
                          if ((*(ulong *)(*param_1 + lVar31 * 0x20) <= uVar24) &&
                             (uVar24 < *(ulong *)(*param_1 + lVar31 * 0x20 + 8))) goto LAB_00153c1c;
                        }
                        iVar10 = (int)plStack_288[2];
                        *(int *)(plStack_288 + 2) = iVar10 + 1;
                        puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                        *puVar20 = 0x19;
                        uVar38 = DAT_00209d70;
                        puVar20[0x12] = 1;
                        puVar20[2] = iVar10;
                        puVar20[3] = 4;
                        uVar19 = 0;
                        *(undefined8 *)(puVar20 + 4) = 0;
                        *(ulonglong *)(puVar20 + 8) = uVar24;
                        *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                        *(undefined8 *)(puVar20 + 6) = uVar38;
                        do {
                          if (*(int *)((long)&uStack_1e8 + uVar19 * 4) == -1) {
                            if ((int)uVar19 == 0) goto LAB_00153fc0;
                            break;
                          }
                          uVar19 = uVar19 + 1;
                        } while (uVar19 != 8);
                        puVar22 = malloc(-((uVar19 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                         (uVar19 & 0xffffffff) << 4);
                        *(undefined4 **)(puVar20 + 0x14) = puVar22;
                        if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                        lVar31 = 0;
                        *(undefined8 *)(puVar20 + 0x16) = 0;
                        puVar20[0x18] = (int)uVar19;
                        do {
                          uVar13 = *(undefined4 *)((long)&uStack_270 + lVar31 * 4);
                          lVar36 = lVar31 * 4;
                          lVar31 = lVar31 + 1;
                          *puVar22 = *(undefined4 *)((long)&uStack_1e8 + lVar36);
                          puVar22[1] = uVar13;
                          *(undefined8 *)(puVar22 + 2) = 0;
                          puVar22 = puVar22 + 4;
                        } while ((int)lVar31 < (int)uVar19);
LAB_00153fc0:
                        uStack_270 = CONCAT44(uStack_270._4_4_,4);
                        uStack_1e8 = CONCAT44(uStack_1e8._4_4_,iVar10);
                        puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                        puVar20[0x12] = 1;
                        *puVar20 = 0x1a;
                        *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                        puVar20[6] = iVar10;
                        puVar20[7] = 4;
                        *(undefined8 *)(puVar20 + 8) = 0;
                        *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                      }
                    }
                    else {
                      iVar10 = strcmp(pcVar21,"ret");
                      if (iVar10 == 0) {
                        puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                        if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                        *puVar20 = 0x1a;
                        *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                        if ((int)uStack_1e8 == -1) {
                          uVar13 = 4;
                        }
                        else {
                          uVar13 = (undefined4)uStack_270;
                        }
                        puVar20[6] = (int)uStack_1e8;
                        puVar20[7] = uVar13;
                        *(undefined8 *)(puVar20 + 8) = 0;
                        puVar20[0x12] = 1;
                        *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                      }
                      else {
                        iVar10 = strcmp(pcVar21,"nop");
                        if (((((((iVar10 != 0) && (iVar10 = strcmp(pcVar21,"hint"), iVar10 != 0)) &&
                               (iVar10 = strcmp(pcVar21,"yield"), iVar10 != 0)) &&
                              ((iVar10 = strcmp(pcVar21,"sev"), iVar10 != 0 &&
                               (iVar10 = strcmp(pcVar21,"sevl"), iVar10 != 0)))) &&
                             ((iVar10 = strcmp(pcVar21,"wfi"), iVar10 != 0 &&
                              ((iVar10 = strcmp(pcVar21,"wfe"), iVar10 != 0 &&
                               (iVar10 = strcmp(pcVar21,"isb"), iVar10 != 0)))))) &&
                            (iVar10 = strcmp(pcVar21,"dsb"), iVar10 != 0)) &&
                           (iVar10 = strcmp(pcVar21,"dmb"), iVar10 != 0)) {
                          puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                          if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                          *puVar20 = 0x1d;
                          puVar20[0x12] = 0;
                          *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                          *(undefined8 *)(puVar20 + 2) = 0xffffffff;
                          strncpy((char *)(puVar20 + 0x1e),pcVar21,0xf);
                          *(undefined1 *)((long)puVar20 + 0x87) = 0;
                        }
                      }
                    }
                    goto LAB_00151ae8;
                  }
                  iVar10 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar10 + 1;
                  puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                  *puVar20 = 0x19;
                  puVar20[2] = iVar10;
                  puVar20[3] = 4;
                  *(undefined8 *)(puVar20 + 4) = 0;
                  if (uStack_2a0 < 0x20) {
                    uVar19 = -(ulong)(uStack_2a0 >> 0x1f) & 0xfffffffc00000000 |
                             (ulong)uStack_2a0 << 2;
                    iVar11 = *(int *)((long)&uStack_1e8 + uVar19);
                    if (iVar11 == -1) goto LAB_00154084;
                    uVar13 = *(undefined4 *)((long)&uStack_270 + uVar19);
                  }
                  else {
LAB_00154084:
                    uVar13 = 5;
                    iVar11 = (int)plStack_288[2];
                    *(int *)(plStack_288 + 2) = iVar11 + 1;
                  }
                  puVar20[6] = iVar11;
                  puVar20[7] = uVar13;
                  uVar19 = 0;
                  *(undefined8 *)(puVar20 + 8) = 0;
                  puVar20[0x12] = 1;
                  *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                  do {
                    if (*(int *)((long)&uStack_1e8 + uVar19 * 4) == -1) {
                      if ((int)uVar19 == 0) goto LAB_00154074;
                      break;
                    }
                    uVar19 = uVar19 + 1;
                  } while (uVar19 != 8);
                  puVar22 = malloc(-((uVar19 & 0xffffffff) >> 0x1f) & 0xfffffff000000000 |
                                   (uVar19 & 0xffffffff) << 4);
                  *(undefined4 **)(puVar20 + 0x14) = puVar22;
                  if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                  lVar31 = 0;
                  *(undefined8 *)(puVar20 + 0x16) = 0;
                  puVar20[0x18] = (int)uVar19;
                  do {
                    uVar13 = *(undefined4 *)((long)&uStack_270 + lVar31 * 4);
                    lVar36 = lVar31 * 4;
                    lVar31 = lVar31 + 1;
                    *puVar22 = *(undefined4 *)((long)&uStack_1e8 + lVar36);
                    puVar22[1] = uVar13;
                    *(undefined8 *)(puVar22 + 2) = 0;
                    puVar22 = puVar22 + 4;
                  } while ((int)lVar31 < (int)uVar19);
LAB_00154074:
                  uStack_270 = CONCAT44(uStack_270._4_4_,4);
                  uStack_1e8 = CONCAT44(uStack_1e8._4_4_,iVar10);
                  goto LAB_00151ae8;
                }
                uVar19 = (ulong)uStack_2a0;
                if ((int)uStack_2a0 < 0) goto LAB_00151ae8;
                iVar10 = (int)plStack_288[2];
                *(int *)(plStack_288 + 2) = iVar10 + 1;
                puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
                *puVar20 = 0x1c;
                if (iStack_2d8 == -1 || iStack_2dc == -1) {
LAB_0015404c:
                  iVar11 = iStack_2d4;
                  if (iStack_2d4 == -1) {
                    iVar11 = (int)plStack_288[2];
                    *(int *)(plStack_288 + 2) = iVar11 + 1;
                  }
                }
                else {
                  uStack_168 = 0;
                  pcVar21 = strchr(acStack_158 + 0x80,0x2c);
                  if (pcVar21 != (char *)0x0) {
                    do {
                      pcVar34 = pcVar21 + 1;
                      pcVar21 = pcVar21 + 1;
                    } while (*pcVar34 == ' ');
                    for (lVar31 = 0;
                        (bVar5 = pcVar21[lVar31], bVar5 != 0x2c && (bVar5 & 0xdf) != 0 &&
                        (lVar31 != 7)); lVar31 = lVar31 + 1) {
                      *(byte *)((long)&uStack_168 + lVar31) = bVar5;
                    }
                    *(undefined1 *)((long)&uStack_168 + (long)(int)lVar31) = 0;
                  }
                  uVar13 = arm64_cond_suffix_to_cmp(&uStack_168,&uStack_278);
                  iVar11 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar11 + 1;
                  puVar22 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
                  if (puVar22 == (undefined4 *)0x0) goto LAB_00152408;
                  *puVar22 = uVar13;
                  puVar22[2] = iVar11;
                  puVar22[3] = 6;
                  *(undefined8 *)(puVar22 + 4) = 0;
                  if ((int)uStack_278 == 0) {
                    uVar38 = uStack_2e8;
                    uVar28 = 0;
                    uVar39 = uVar41;
                    uVar40 = uVar42;
                  }
                  else {
                    uVar38 = 0;
                    uVar28 = uStack_2e8;
                    uVar39 = uVar42;
                    uVar40 = uVar41;
                  }
                  *(undefined8 *)(puVar22 + 0xc) = uVar38;
                  *(undefined8 *)(puVar22 + 6) = uVar40;
                  *(undefined8 *)(puVar22 + 8) = uVar28;
                  *(undefined8 *)(puVar22 + 10) = uVar39;
                  puVar22[0x12] = 2;
                  *(undefined8 *)(puVar22 + 0x1c) = uVar15;
                  if (iVar11 == -1) goto LAB_0015404c;
                }
                puVar20[6] = iVar11;
                puVar20[7] = 6;
                *(undefined8 *)(puVar20 + 8) = 0;
                if (uStack_29c < 0x20) {
                  uVar23 = -(ulong)(uStack_29c >> 0x1f) & 0xfffffffc00000000 |
                           (ulong)uStack_29c << 2;
                  iVar11 = *(int *)((long)&uStack_1e8 + uVar23);
                  if (iVar11 == -1) goto LAB_00153940;
                  uVar13 = *(undefined4 *)((long)&uStack_270 + uVar23);
                }
                else {
LAB_00153940:
                  iVar11 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar11 + 1;
                  uVar13 = uStack_290;
                }
                puVar20[10] = iVar11;
                puVar20[0xb] = uVar13;
                *(undefined8 *)(puVar20 + 0xc) = 0;
                uStack_168 = 0;
                uStack_160 = 0;
                pcVar21 = strchr(acStack_158 + 0x40,0x2c);
                if (pcVar21 != (char *)0x0) {
                  do {
                    pcVar34 = pcVar21 + 1;
                    pcVar21 = pcVar21 + 1;
                  } while (*pcVar34 == ' ');
                  for (lVar31 = 0;
                      (bVar5 = pcVar21[lVar31], bVar5 != 0x2c && (bVar5 & 0xdf) != 0 &&
                      (lVar31 != 0xf)); lVar31 = lVar31 + 1) {
                    *(byte *)((long)&uStack_168 + lVar31) = bVar5;
                  }
                  *(undefined1 *)((long)&uStack_168 + (long)(int)lVar31) = 0;
                }
                uStack_280 = 0xfffffffe;
                uStack_278._0_4_ = 4;
                if ((((char)uStack_168 == '\0') ||
                    (iVar11 = arm64_reg_lookup(&uStack_168,&uStack_280,&uStack_278), iVar11 == 0))
                   || (0x1f < uStack_280)) {
LAB_00153864:
                  iVar11 = (int)plStack_288[2];
                  *(int *)(plStack_288 + 2) = iVar11 + 1;
                  uVar13 = uStack_294;
                }
                else {
                  uVar23 = -(ulong)(uStack_280 >> 0x1f) & 0xfffffffc00000000 |
                           (ulong)uStack_280 << 2;
                  iVar11 = *(int *)((long)&uStack_1e8 + uVar23);
                  if (iVar11 == -1) goto LAB_00153864;
                  uVar13 = *(undefined4 *)((long)&uStack_270 + uVar23);
                }
                uVar19 = -(ulong)(uVar25 >> 0x1f) & 0xfffffffc00000000 | uVar19 << 2;
                puVar20[0xe] = iVar11;
                puVar20[0xf] = uVar13;
                *(undefined4 *)((long)&uStack_270 + uVar19) = uStack_294;
                *(int *)((long)&uStack_1e8 + uVar19) = iVar10;
                puVar20[2] = iVar10;
                puVar20[3] = uStack_294;
                *(undefined8 *)(puVar20 + 4) = 0;
                *(undefined8 *)(puVar20 + 0x10) = 0;
                puVar20[0x12] = 3;
                *(undefined8 *)(puVar20 + 0x1c) = uVar15;
                goto LAB_00151ae8;
              }
              uVar13 = 0xc;
            }
            if (uStack_2a0 < 0x20) {
              uVar19 = -(ulong)(uStack_2a0 >> 0x1f) & 0xfffffffc00000000 | (ulong)uStack_2a0 << 2;
              iVar10 = *(int *)((long)&uStack_1e8 + uVar19);
              if (iVar10 == -1) goto LAB_001535ec;
              uVar43 = *(undefined4 *)((long)&uStack_270 + uVar19);
            }
            else {
LAB_001535ec:
              uVar43 = 4;
              iVar10 = (int)plStack_288[2];
              *(int *)(plStack_288 + 2) = iVar10 + 1;
            }
            auVar44 = arm_emit_const(puVar2,plStack_288,0,uVar15);
            if (auVar44._0_4_ == -1) goto LAB_00152408;
            iVar11 = (int)plStack_288[2];
            *(int *)(plStack_288 + 2) = iVar11 + 1;
            puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
            if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
            *puVar20 = uVar13;
            puVar20[2] = iVar11;
            puVar20[3] = 6;
            *(undefined8 *)(puVar20 + 4) = 0;
            puVar20[6] = iVar10;
            puVar20[7] = uVar43;
            *(undefined8 *)(puVar20 + 8) = 0;
            *(undefined1 (*) [16])(puVar20 + 10) = auVar44;
            puVar20[0x12] = 2;
            *(undefined8 *)(puVar20 + 0x1c) = uVar15;
            puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
            if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
            *puVar20 = 0x17;
            puVar20[6] = iVar11;
            puVar20[7] = 6;
            *(undefined8 *)(puVar20 + 8) = 0;
            *(undefined8 *)(puVar20 + 2) = 0xffffffff;
            puVar20[0x12] = 1;
            *(undefined8 *)(puVar20 + 0x1c) = uVar15;
            goto LAB_00151ae8;
          }
          arm64_parse_mem_op_isra_0(acStack_158 + 0x40,&uStack_280,&uStack_278);
          uVar25 = *(uint *)(puVar2 + 2);
          uVar30 = *(uint *)((long)puVar2 + 0x14);
          if (uVar25 < uVar30) {
            pvVar14 = (void *)puVar2[1];
          }
          else {
            if (uVar30 == 0) {
              sVar26 = 0x880;
              uVar30 = 0x10;
            }
            else {
              uVar30 = uVar30 << 1;
              sVar26 = (ulong)uVar30 * 0x88;
            }
            pvVar14 = realloc((void *)puVar2[1],sVar26);
            if (pvVar14 == (void *)0x0) goto LAB_00152408;
            uVar25 = *(uint *)(puVar2 + 2);
            puVar2[1] = pvVar14;
            *(uint *)((long)puVar2 + 0x14) = uVar30;
          }
          *(uint *)(puVar2 + 2) = uVar25 + 1;
          puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar25 * 0x88);
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
          *(undefined4 *)((long)pvVar14 + (ulong)uVar25 * 0x88) = 0x16;
          *(undefined4 *)(puVar18 + 1) = 0xffffffff;
          if (uStack_280 < 0x20) {
            lVar31 = (long)(int)uStack_280;
            iVar11 = *(int *)((long)&uStack_1e8 + lVar31 * 4);
            if (iVar11 == -1) goto LAB_00153030;
            auVar44 = arm_emit_const(puVar2,plStack_288,CONCAT44(uStack_278._4_4_,(int)uStack_278),
                                     uVar15);
            if (auVar44._0_4_ == -1) goto LAB_00152408;
            uVar25 = *(uint *)(puVar2 + 2);
            uVar30 = *(uint *)((long)puVar2 + 0x14);
            iVar12 = (int)plStack_288[2];
            *(int *)(plStack_288 + 2) = iVar12 + 1;
            pvVar14 = (void *)puVar2[1];
            if (uVar30 <= uVar25) {
              if (uVar30 == 0) {
                sVar26 = 0x880;
                uVar30 = 0x10;
              }
              else {
                uVar30 = uVar30 << 1;
                sVar26 = (ulong)uVar30 * 0x88;
              }
              pvVar14 = realloc(pvVar14,sVar26);
              if (pvVar14 == (void *)0x0) goto LAB_00152408;
              uVar25 = *(uint *)(puVar2 + 2);
              puVar2[1] = pvVar14;
              *(uint *)((long)puVar2 + 0x14) = uVar30;
            }
            *(uint *)(puVar2 + 2) = uVar25 + 1;
            lVar36 = (ulong)uVar25 * 0x88;
            uVar13 = *(undefined4 *)((long)&uStack_270 + lVar31 * 4);
            *(undefined4 *)((long)pvVar14 + lVar36 + 0x84) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0xc) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 4) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x1c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x14) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x2c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x24) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x3c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x34) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x4c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x44) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x5c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x54) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x6c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 100) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x7c) = 0;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x74) = 0;
            lVar31 = puVar2[1];
            *(undefined4 *)((long)pvVar14 + lVar36) = 2;
            *(int *)((long)pvVar14 + lVar36 + 8) = iVar12;
            *(undefined4 *)((long)pvVar14 + lVar36 + 0xc) = 5;
            *(int *)((long)pvVar14 + lVar36 + 0x18) = iVar11;
            *(undefined4 *)((long)pvVar14 + lVar36 + 0x1c) = uVar13;
            puVar18 = (undefined8 *)(lVar31 + (ulong)(iVar10 - 1U) * 0x88);
            *(undefined1 (*) [16])((long)pvVar14 + lVar36 + 0x28) = auVar44;
            *(undefined4 *)((long)pvVar14 + lVar36 + 0x48) = 2;
            *(undefined8 *)((long)pvVar14 + lVar36 + 0x70) = uVar15;
            *(int *)(puVar18 + 3) = iVar12;
            *(undefined4 *)((long)puVar18 + 0x1c) = 5;
            puVar18[4] = 0;
          }
          else {
LAB_00153030:
            puVar18[3] = DAT_00209d70;
          }
          if (uStack_2a0 == 0xffffffff) {
            auVar44 = arm_emit_const(puVar2,plStack_288,0,uVar15);
            if (auVar44._0_4_ == -1) goto LAB_00152408;
            puVar18 = (undefined8 *)(puVar2[1] + (ulong)(iVar10 - 1U) * 0x88);
            *(undefined1 (*) [16])(puVar18 + 5) = auVar44;
          }
          else {
            if (uStack_2a0 < 0x20) {
              iVar10 = *(int *)((long)&uStack_1e8 + (long)(int)uStack_2a0 * 4);
              if (iVar10 == -1) goto LAB_00153080;
              uVar13 = *(undefined4 *)((long)&uStack_270 + (long)(int)uStack_2a0 * 4);
            }
            else {
LAB_00153080:
              iVar10 = (int)plStack_288[2];
              *(int *)(plStack_288 + 2) = iVar10 + 1;
              uVar13 = uStack_294;
            }
            *(int *)(puVar18 + 5) = iVar10;
            *(undefined4 *)((long)puVar18 + 0x2c) = uVar13;
            puVar18[6] = 0;
          }
          *(undefined4 *)(puVar18 + 9) = 2;
          puVar18[0xe] = uVar15;
          goto LAB_00151ae8;
        }
      }
    }
    uStack_2a0 = uVar25;
    if ((int)uVar25 < 0) {
LAB_00151ae8:
      lVar29 = lVar29 + 1;
      if (*(uint *)(lVar1 + 0x18) <= (uint)lVar29) goto LAB_00151afc;
      goto LAB_001518f0;
    }
  }
  else {
    iVar11 = strcmp(pcVar21,"sub");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"subs"), iVar11 == 0)) {
      uVar13 = 3;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"mul");
    if (iVar11 == 0) {
      uVar13 = 4;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"sdiv");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"udiv"), iVar11 == 0)) {
      uVar13 = 5;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"and");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"ands"), iVar11 == 0)) {
      uVar13 = 6;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"orr");
    if (iVar11 == 0) {
      uVar13 = 7;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"eor");
    if (iVar11 == 0) {
      uVar13 = 8;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"lsl");
    if (iVar11 == 0) {
      uVar13 = 9;
      goto LAB_001519a8;
    }
    iVar11 = strcmp(pcVar21,"lsr");
    if ((iVar11 == 0) || (iVar11 = strcmp(pcVar21,"asr"), iVar11 == 0)) {
      uVar13 = 10;
      goto LAB_001519a8;
    }
LAB_00152580:
    iVar10 = strcmp(pcVar21,"ldr");
    uVar25 = uStack_2a0;
    if (iVar10 != 0) goto LAB_001529b4;
    if ((int)uStack_2a0 < 0) goto LAB_00151ae8;
    iVar10 = strcmp(pcVar21,"ldrb");
    uVar13 = 1;
    if ((iVar10 != 0) && (iVar10 = strcmp(pcVar21,"ldrh"), uVar13 = uStack_294, iVar10 == 0)) {
      uVar13 = 2;
    }
  }
  arm64_parse_mem_op_isra_0(acStack_158 + 0x40,&uStack_280,&uStack_278);
  uVar30 = *(uint *)(puVar2 + 2);
  uVar35 = *(uint *)((long)puVar2 + 0x14);
  iVar10 = (int)plStack_288[2];
  *(int *)(plStack_288 + 2) = iVar10 + 1;
  if (uVar30 < uVar35) {
    pvVar14 = (void *)puVar2[1];
  }
  else {
    if (uVar35 == 0) {
      sVar26 = 0x880;
      uVar35 = 0x10;
    }
    else {
      uVar35 = uVar35 << 1;
      sVar26 = (ulong)uVar35 * 0x88;
    }
    pvVar14 = realloc((void *)puVar2[1],sVar26);
    if (pvVar14 == (void *)0x0) goto LAB_00152408;
    uVar30 = *(uint *)(puVar2 + 2);
    puVar2[1] = pvVar14;
    *(uint *)((long)puVar2 + 0x14) = uVar35;
  }
  *(uint *)(puVar2 + 2) = uVar30 + 1;
  puVar18 = (undefined8 *)((long)pvVar14 + (ulong)uVar30 * 0x88);
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
  *(undefined4 *)((long)pvVar14 + (ulong)uVar30 * 0x88) = 0x15;
  *(int *)(puVar18 + 1) = iVar10;
  *(undefined4 *)((long)puVar18 + 0xc) = uVar13;
  if (uStack_280 < 0x20) {
    lVar31 = (long)(int)uStack_280;
    iVar12 = *(int *)((long)&uStack_1e8 + lVar31 * 4);
    if (iVar12 != -1) {
      auVar44 = arm_emit_const(puVar2,plStack_288,CONCAT44(uStack_278._4_4_,(int)uStack_278),uVar15)
      ;
      if (auVar44._0_4_ == -1) goto LAB_00152408;
      uVar30 = *(uint *)(puVar2 + 2);
      uVar35 = *(uint *)((long)puVar2 + 0x14);
      iVar3 = (int)plStack_288[2];
      *(int *)(plStack_288 + 2) = iVar3 + 1;
      pvVar14 = (void *)puVar2[1];
      if (uVar35 <= uVar30) {
        if (uVar35 == 0) {
          sVar26 = 0x880;
          uVar35 = 0x10;
        }
        else {
          uVar35 = uVar35 << 1;
          sVar26 = (ulong)uVar35 * 0x88;
        }
        pvVar14 = realloc(pvVar14,sVar26);
        if (pvVar14 == (void *)0x0) goto LAB_00152408;
        puVar2[1] = pvVar14;
        uVar30 = *(uint *)(puVar2 + 2);
        *(uint *)((long)puVar2 + 0x14) = uVar35;
      }
      *(uint *)(puVar2 + 2) = uVar30 + 1;
      lVar36 = (ulong)uVar30 * 0x88;
      uVar43 = *(undefined4 *)((long)&uStack_270 + lVar31 * 4);
      *(undefined4 *)((long)pvVar14 + lVar36 + 0x84) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0xc) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 4) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x1c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x14) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x2c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x24) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x3c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x34) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x4c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x44) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x5c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x54) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x6c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 100) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x7c) = 0;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x74) = 0;
      lVar31 = puVar2[1];
      *(undefined4 *)((long)pvVar14 + lVar36) = 2;
      *(int *)((long)pvVar14 + lVar36 + 8) = iVar3;
      *(undefined4 *)((long)pvVar14 + lVar36 + 0xc) = 5;
      *(int *)((long)pvVar14 + lVar36 + 0x18) = iVar12;
      *(undefined4 *)((long)pvVar14 + lVar36 + 0x1c) = uVar43;
      puVar18 = (undefined8 *)(lVar31 + (ulong)(iVar11 - 1) * 0x88);
      *(undefined1 (*) [16])((long)pvVar14 + lVar36 + 0x28) = auVar44;
      *(undefined4 *)((long)pvVar14 + lVar36 + 0x48) = 2;
      *(undefined8 *)((long)pvVar14 + lVar36 + 0x70) = uVar15;
      *(int *)(puVar18 + 3) = iVar3;
      *(undefined4 *)((long)puVar18 + 0x1c) = 5;
      puVar18[4] = 0;
      goto LAB_00152ad4;
    }
  }
  puVar18[3] = DAT_00209d70;
LAB_00152ad4:
  puVar18[0xe] = uVar15;
  *(undefined4 *)(puVar18 + 9) = 1;
  lVar29 = lVar29 + 1;
  *(int *)((long)&uStack_1e8 + (long)(int)uVar25 * 4) = iVar10;
  uVar30 = *(uint *)(lVar1 + 0x18);
  *(undefined4 *)((long)&uStack_270 + (long)(int)uVar25 * 4) = uVar13;
  if (uVar30 <= (uint)lVar29) goto LAB_00151afc;
  goto LAB_001518f0;
  while( true ) {
    pcVar33 = pcVar34 + -1;
    *pcVar34 = '\0';
    pcVar34 = pcVar33;
    cVar9 = acStack_158[0x40];
    if (pcVar33 == pcVar17) break;
LAB_00152038:
    cVar9 = acStack_158[0x40];
    if (*pcVar34 != ' ') break;
  }
LAB_00152048:
  pcVar34 = pcVar17;
  if (cVar9 == ' ') {
    do {
      pcVar34 = pcVar34 + 1;
    } while (*pcVar34 == ' ');
    if (pcVar34 != pcVar17) {
      sVar26 = strlen(pcVar34);
      __memmove_chk(pcVar17,pcVar34,sVar26 + 1,0x40);
    }
  }
LAB_00152088:
  cVar9 = acStack_158[0x80];
  if (acStack_158[0x80] == '\0') {
LAB_0015228c:
    uStack_2a0 = 0xfffffffe;
    uStack_29c = 0xfffffffe;
    uStack_298 = 0xfffffffe;
    uStack_294 = 4;
    uStack_290 = 4;
    uStack_28c = 4;
    iVar10 = arm64_reg_lookup(acStack_158,&uStack_2a0,&uStack_294);
    if (iVar10 == 0) goto LAB_00152134;
LAB_001522b8:
    iVar10 = arm64_reg_lookup(pcVar17,&uStack_29c,&uStack_290);
  }
  else {
    sVar26 = strlen(__s);
    pcVar34 = __s + (sVar26 - 1);
    if (__s < __s + (sVar26 - 1)) {
      do {
        cVar9 = acStack_158[0x80];
        if (*pcVar34 != ' ') break;
        pcVar33 = pcVar34 + -1;
        *pcVar34 = '\0';
        pcVar34 = pcVar33;
        cVar9 = acStack_158[0x80];
      } while (pcVar33 != __s);
    }
    pcVar34 = __s;
    if (cVar9 != ' ') goto LAB_0015228c;
    do {
      pcVar34 = pcVar34 + 1;
    } while (*pcVar34 == ' ');
    if (pcVar34 == __s) goto LAB_0015228c;
    sVar26 = strlen(pcVar34);
    __memmove_chk(__s,pcVar34,sVar26 + 1,0x40);
    uStack_2a0 = 0xfffffffe;
    uStack_29c = 0xfffffffe;
    uStack_298 = 0xfffffffe;
    uStack_294 = 4;
    uStack_290 = 4;
    uStack_28c = 4;
    iVar10 = arm64_reg_lookup(acStack_158,&uStack_2a0,&uStack_294);
    if (iVar10 != 0) goto LAB_001522b8;
LAB_00152134:
    uStack_2a0 = 0xfffffffe;
    iVar10 = arm64_reg_lookup(pcVar17,&uStack_29c,&uStack_290);
  }
  if (iVar10 == 0) {
    iVar10 = 3;
LAB_001522d0:
    pcVar34 = acStack_158 + 0x40;
    cVar9 = acStack_158[0x40];
    while (cVar9 == ' ') {
      pcVar34 = pcVar34 + 1;
      cVar9 = *pcVar34;
    }
    if (cVar9 == '#') {
      pcVar33 = pcVar34 + 1;
      pcVar34 = pcVar34 + 1;
      cVar9 = *pcVar33;
      while (cVar9 == ' ') {
        pcVar34 = pcVar34 + 1;
        cVar9 = *pcVar34;
      }
    }
    iVar11 = __isoc99_sscanf(pcVar34,"0x%lx",&uStack_280);
    if (iVar11 == 1) {
      lVar36 = CONCAT44(uStack_27c,uStack_280);
      bVar6 = true;
    }
    else {
      iVar11 = __isoc99_sscanf(pcVar34,&DAT_001f7eb0,&uStack_278);
      if (iVar11 == 1) {
        lVar36 = CONCAT44(uStack_278._4_4_,(int)uStack_278);
        bVar6 = true;
      }
      else {
        lVar36 = 0;
        bVar6 = false;
      }
    }
    if (iVar10 == 3) {
      iVar10 = arm64_reg_lookup(acStack_158 + 0x80,&uStack_298,&uStack_28c);
      if (iVar10 == 0) goto LAB_00152360;
LAB_00152170:
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
    lVar36 = 0;
    iVar10 = arm64_reg_lookup(__s,&uStack_298,&uStack_28c);
    bVar6 = false;
    if (iVar10 != 0) goto LAB_00152170;
LAB_00152360:
    bVar7 = false;
    pcVar34 = acStack_158 + 0x80;
    cVar9 = acStack_158[0x80];
    while (cVar9 == ' ') {
      pcVar34 = pcVar34 + 1;
      cVar9 = *pcVar34;
    }
    if (cVar9 == '#') {
      pcVar33 = pcVar34 + 1;
      pcVar34 = pcVar34 + 1;
      cVar9 = *pcVar33;
      while (cVar9 == ' ') {
        pcVar34 = pcVar34 + 1;
        cVar9 = *pcVar34;
      }
    }
    iVar10 = __isoc99_sscanf(pcVar34,"0x%lx",&uStack_280);
    if (iVar10 == 1) {
      uVar38 = CONCAT44(uStack_27c,uStack_280);
      iVar10 = 3;
      bVar7 = true;
    }
    else {
      uVar38 = 0;
      iVar10 = __isoc99_sscanf(pcVar34,&DAT_001f7eb0,&uStack_278);
      if (iVar10 == 1) {
        uVar38 = CONCAT44(uStack_278._4_4_,(int)uStack_278);
        iVar10 = 3;
        bVar7 = true;
      }
      else {
        iVar10 = 3;
      }
    }
  }
  goto LAB_0015217c;
LAB_00153604:
  if (((uVar30 == 0x1f) && (lVar31 = CONCAT44(uStack_278._4_4_,(int)uStack_278), lVar31 != 0)) &&
     (pcVar21 = strchr(acStack_158 + 0x80,0x21), pcVar21 != (char *)0x0)) {
    auVar44 = arm_emit_const(puVar2,plStack_288,lVar31,uVar15);
    iVar10 = (int)plStack_288[2];
    *(int *)(plStack_288 + 2) = iVar10 + 1;
    puVar20 = (undefined4 *)arm_irblock_alloc_instr(puVar2);
    if (puVar20 == (undefined4 *)0x0) goto LAB_00152408;
    *puVar20 = 2;
    puVar20[2] = iVar10;
    puVar20[3] = 5;
    *(undefined8 *)(puVar20 + 4) = 0;
    puVar20[6] = uStack_170._4_4_;
    puVar20[7] = 5;
    *(undefined8 *)(puVar20 + 8) = 0;
    *(undefined1 (*) [16])(puVar20 + 10) = auVar44;
    puVar20[0x12] = 2;
    *(undefined8 *)(puVar20 + 0x1c) = uVar15;
    uStack_170 = CONCAT44(iVar10,(undefined4)uStack_170);
  }
  goto LAB_00151ae8;
LAB_00152408:
  ir_func_destroy(&plStack_288);
  goto LAB_00152430;
}

