
char * hir_build(long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                long *param_5)

{
  undefined8 *puVar1;
  ulong uVar2;
  long *__haystack;
  uint uVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  char *__s;
  char *pcVar7;
  uint *puVar8;
  char *pcVar9;
  size_t sVar10;
  void *pvVar11;
  void *pvVar12;
  char *pcVar13;
  int *piVar14;
  undefined8 uVar15;
  undefined8 *puVar16;
  long lVar17;
  uint *puVar18;
  long lVar19;
  uint uVar20;
  uint *puVar21;
  char *pcVar22;
  uint uVar23;
  long lVar24;
  uint uVar25;
  size_t sVar26;
  size_t sVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  undefined8 uVar31;
  undefined8 uVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  undefined8 uVar37;
  undefined8 uVar38;
  undefined8 uVar39;
  long *local_1b8;
  undefined8 uStack_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  char *local_198;
  void *local_190;
  void *local_188;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 uStack_170;
  undefined8 uStack_168;
  undefined8 uStack_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  undefined8 uStack_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined8 uStack_128;
  undefined8 uStack_120;
  undefined8 uStack_118;
  undefined8 local_110;
  undefined8 uStack_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined8 uStack_e0;
  undefined8 uStack_d8;
  undefined8 local_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 local_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 local_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (((param_1 == (long *)0x0) || ((int)param_1[1] == 0)) ||
     (__s = calloc(1,0xef0), __s == (char *)0x0)) {
    pcVar22 = (char *)0x0;
    goto LAB_0017f188;
  }
  pcVar22 = __s + 0x88;
  snprintf(__s,0x80,"%s",param_1 + 4);
  local_178 = 0x745f3436746e69;
  uStack_108 = 0;
  local_110 = 0;
  uStack_100 = 0;
  local_f8 = 0x10000000008;
  uStack_168 = 0;
  uStack_170 = 0;
  uStack_158 = 0;
  uStack_160 = 0;
  uStack_148 = 0;
  local_150 = 0;
  uStack_138 = 0;
  uStack_140 = 0;
  uStack_128 = 0;
  local_130 = 0;
  uStack_118 = 0;
  uStack_120 = 0;
  uStack_e8 = 0;
  local_f0 = 0x745f3436746e69;
  uStack_d8 = 0;
  uStack_e0 = 0;
  uStack_c8 = 0;
  local_d0 = 0;
  uStack_b8 = 0;
  uStack_c0 = 0;
  *(long *)(__s + 0x80) = param_1[3];
  local_70 = 0x10000000008;
  uStack_a8 = 0;
  local_b0 = 0;
  uStack_98 = 0;
  uStack_a0 = 0;
  uStack_88 = 0;
  local_90 = 0;
  uStack_78 = 0;
  uStack_80 = 0;
  __s[0x90] = '\0';
  __s[0x91] = '\0';
  __s[0x92] = '\0';
  __s[0x93] = '\0';
  __s[0x94] = '\0';
  __s[0x95] = '\0';
  __s[0x96] = '\0';
  __s[0x97] = '\0';
  pcVar22[0] = 'i';
  pcVar22[1] = 'n';
  pcVar22[2] = 't';
  pcVar22[3] = '6';
  pcVar22[4] = '4';
  pcVar22[5] = '_';
  pcVar22[6] = 't';
  pcVar22[7] = '\0';
  __s[0xa0] = '\0';
  __s[0xa1] = '\0';
  __s[0xa2] = '\0';
  __s[0xa3] = '\0';
  __s[0xa4] = '\0';
  __s[0xa5] = '\0';
  __s[0xa6] = '\0';
  __s[0xa7] = '\0';
  __s[0x98] = '\0';
  __s[0x99] = '\0';
  __s[0x9a] = '\0';
  __s[0x9b] = '\0';
  __s[0x9c] = '\0';
  __s[0x9d] = '\0';
  __s[0x9e] = '\0';
  __s[0x9f] = '\0';
  __s[0x108] = '\b';
  __s[0x109] = '\0';
  __s[0x10a] = '\0';
  __s[0x10b] = '\0';
  __s[0x10c] = '\0';
  __s[0x10d] = '\x01';
  __s[0x10e] = '\0';
  __s[0x10f] = '\0';
  __s[0xb0] = '\0';
  __s[0xb1] = '\0';
  __s[0xb2] = '\0';
  __s[0xb3] = '\0';
  __s[0xb4] = '\0';
  __s[0xb5] = '\0';
  __s[0xb6] = '\0';
  __s[0xb7] = '\0';
  __s[0xa8] = '\0';
  __s[0xa9] = '\0';
  __s[0xaa] = '\0';
  __s[0xab] = '\0';
  __s[0xac] = '\0';
  __s[0xad] = '\0';
  __s[0xae] = '\0';
  __s[0xaf] = '\0';
  __s[0xc0] = '\0';
  __s[0xc1] = '\0';
  __s[0xc2] = '\0';
  __s[0xc3] = '\0';
  __s[0xc4] = '\0';
  __s[0xc5] = '\0';
  __s[0xc6] = '\0';
  __s[199] = '\0';
  __s[0xb8] = '\0';
  __s[0xb9] = '\0';
  __s[0xba] = '\0';
  __s[0xbb] = '\0';
  __s[0xbc] = '\0';
  __s[0xbd] = '\0';
  __s[0xbe] = '\0';
  __s[0xbf] = '\0';
  __s[0xd0] = '\0';
  __s[0xd1] = '\0';
  __s[0xd2] = '\0';
  __s[0xd3] = '\0';
  __s[0xd4] = '\0';
  __s[0xd5] = '\0';
  __s[0xd6] = '\0';
  __s[0xd7] = '\0';
  __s[200] = '\0';
  __s[0xc9] = '\0';
  __s[0xca] = '\0';
  __s[0xcb] = '\0';
  __s[0xcc] = '\0';
  __s[0xcd] = '\0';
  __s[0xce] = '\0';
  __s[0xcf] = '\0';
  __s[0xe0] = '\0';
  __s[0xe1] = '\0';
  __s[0xe2] = '\0';
  __s[0xe3] = '\0';
  __s[0xe4] = '\0';
  __s[0xe5] = '\0';
  __s[0xe6] = '\0';
  __s[0xe7] = '\0';
  __s[0xd8] = '\0';
  __s[0xd9] = '\0';
  __s[0xda] = '\0';
  __s[0xdb] = '\0';
  __s[0xdc] = '\0';
  __s[0xdd] = '\0';
  __s[0xde] = '\0';
  __s[0xdf] = '\0';
  __s[0xf0] = '\0';
  __s[0xf1] = '\0';
  __s[0xf2] = '\0';
  __s[0xf3] = '\0';
  __s[0xf4] = '\0';
  __s[0xf5] = '\0';
  __s[0xf6] = '\0';
  __s[0xf7] = '\0';
  __s[0xe8] = '\0';
  __s[0xe9] = '\0';
  __s[0xea] = '\0';
  __s[0xeb] = '\0';
  __s[0xec] = '\0';
  __s[0xed] = '\0';
  __s[0xee] = '\0';
  __s[0xef] = '\0';
  __s[0x100] = '\0';
  __s[0x101] = '\0';
  __s[0x102] = '\0';
  __s[0x103] = '\0';
  __s[0x104] = '\0';
  __s[0x105] = '\0';
  __s[0x106] = '\0';
  __s[0x107] = '\0';
  __s[0xf8] = '\0';
  __s[0xf9] = '\0';
  __s[0xfa] = '\0';
  __s[0xfb] = '\0';
  __s[0xfc] = '\0';
  __s[0xfd] = '\0';
  __s[0xfe] = '\0';
  __s[0xff] = '\0';
  if (param_5 != (long *)0x0) {
    uVar23 = *(uint *)(param_5 + 1);
    if (uVar23 != 0) {
      pcVar13 = __s + 0x110;
      lVar24 = 0;
      if (0x10 < uVar23) {
        uVar23 = 0x10;
      }
      uVar25 = 0;
      *(uint *)(__s + 0xdd0) = uVar23;
      do {
        while( true ) {
          lVar19 = *param_5 + lVar24;
          snprintf(pcVar13,0x40,"%s",lVar19 + 0x84);
          snprintf(pcVar13 + 0x40,0x80,"%s",(char *)(lVar19 + 4));
          *(undefined4 *)(pcVar13 + 0xc0) = *(undefined4 *)(lVar19 + 0xd0);
          pcVar7 = strchr((char *)(lVar19 + 4),0x2a);
          if (pcVar7 != (char *)0x0) {
            pcVar13[0xc4] = '\x01';
          }
          if (*(int *)(lVar19 + 0xc4) == 1 && uVar25 < 8) break;
          pcVar13[200] = -1;
          pcVar13[0xc9] = -1;
          pcVar13[0xca] = -1;
          pcVar13[0xcb] = -1;
          uVar25 = uVar25 + 1;
          lVar24 = lVar24 + 0xd8;
          pcVar13 = pcVar13 + 0xcc;
          if (*(uint *)(__s + 0xdd0) <= uVar25) goto LAB_0017eee8;
        }
        *(uint *)(pcVar13 + 200) = uVar25;
        uVar25 = uVar25 + 1;
        lVar24 = lVar24 + 0xd8;
        pcVar13 = pcVar13 + 0xcc;
      } while (uVar25 < *(uint *)(__s + 0xdd0));
    }
LAB_0017eee8:
    cVar4 = DAT_001f82bc;
    if ((*(byte *)(param_5 + 0x12) & 1) == 0) {
      *(undefined4 *)(__s + 0x88) = DAT_001f82b8;
      __s[0x8c] = cVar4;
      __s[0x108] = '\0';
      __s[0x109] = '\0';
      __s[0x10a] = '\0';
      __s[0x10b] = '\0';
      __s[0x10c] = '\0';
    }
    else if ((char)param_5[2] != '\0') {
      __haystack = param_5 + 2;
      snprintf(pcVar22,0x80,"%s",__haystack);
      pcVar13 = strstr((char *)__haystack,"64");
      if (pcVar13 == (char *)0x0) {
        pcVar13 = strstr((char *)__haystack,"32");
        if (pcVar13 == (char *)0x0) {
          pcVar13 = strstr((char *)__haystack,"16");
          if (pcVar13 == (char *)0x0) {
            pcVar13 = strchr((char *)__haystack,0x38);
            if (pcVar13 == (char *)0x0) {
              pcVar13 = strchr((char *)__haystack,0x2a);
              if (pcVar13 == (char *)0x0) {
                iVar6 = strcmp((char *)__haystack,"int");
                if (iVar6 == 0) goto LAB_0017f3d8;
                iVar6 = strcmp((char *)__haystack,"void");
                if (iVar6 == 0) {
                  __s[0x108] = '\0';
                  __s[0x109] = '\0';
                  __s[0x10a] = '\0';
                  __s[0x10b] = '\0';
                }
              }
              else {
                __s[0x108] = '\b';
                __s[0x109] = '\0';
                __s[0x10a] = '\0';
                __s[0x10b] = '\0';
                __s[0x10c] = '\x01';
              }
            }
            else {
              __s[0x108] = '\x01';
              __s[0x109] = '\0';
              __s[0x10a] = '\0';
              __s[0x10b] = '\0';
            }
          }
          else {
            __s[0x108] = '\x02';
            __s[0x109] = '\0';
            __s[0x10a] = '\0';
            __s[0x10b] = '\0';
          }
        }
        else {
LAB_0017f3d8:
          __s[0x108] = '\x04';
          __s[0x109] = '\0';
          __s[0x10a] = '\0';
          __s[0x10b] = '\0';
        }
      }
      else {
        __s[0x108] = '\b';
        __s[0x109] = '\0';
        __s[0x10a] = '\0';
        __s[0x10b] = '\0';
      }
    }
  }
  pcVar13 = __s + 0xdf0;
  if (*(uint *)(param_1 + 1) != 0) {
    sVar26 = 0;
    puVar21 = (uint *)(*param_1 + 0x10);
    puVar8 = puVar21 + (ulong)*(uint *)(param_1 + 1) * 0x12;
    do {
      uVar23 = *puVar21;
      if (uVar23 != 0) {
        lVar24 = 0;
        uVar25 = 0;
        do {
          while (((lVar19 = *(long *)(puVar21 + -2) + lVar24,
                  *(int *)(*(long *)(puVar21 + -2) + lVar24) == 0x1d &&
                  (*(char *)(lVar19 + 0x78) != '\0')) &&
                 ((pcVar7 = (char *)(lVar19 + 0x78), __s[0xdf0] == '\0' ||
                  (pcVar9 = strstr(pcVar13,pcVar7), pcVar9 == (char *)0x0))))) {
            sVar10 = strlen(pcVar7);
            if (sVar26 == 0) {
              if (0xff < sVar10 + 4) {
                pcVar7 = "";
                lVar24 = 0x100;
LAB_0017f32c:
                __snprintf_chk(pcVar13,lVar24,2,lVar24,"%s...",pcVar7);
                goto LAB_0017eff0;
              }
              lVar17 = 0x100;
              pcVar9 = pcVar13;
              sVar27 = sVar10;
            }
            else {
              lVar19 = sVar26 + 2;
              if (0xff < sVar26 + 6 + sVar10) {
                if (sVar26 + 4 < 0x100) {
                  pcVar13 = pcVar13 + sVar26;
                  lVar24 = 0x100 - sVar26;
                  pcVar7 = ", ";
                  goto LAB_0017f32c;
                }
                goto LAB_0017eff0;
              }
              uVar2 = sVar26 + 0xdf2;
              if (uVar2 < 0xef0) {
                uVar2 = 0xef0;
              }
              pcVar13[sVar26] = ',';
              pcVar9 = pcVar13 + lVar19;
              lVar17 = uVar2 + (-0xdf0 - lVar19);
              sVar27 = sVar10 + lVar19;
              pcVar13[sVar26 + 1] = ' ';
            }
            __memcpy_chk(pcVar9,pcVar7,sVar10,lVar17);
            pcVar13[sVar27] = '\0';
            uVar25 = uVar25 + 1;
            lVar24 = lVar24 + 0x88;
            uVar23 = *puVar21;
            sVar26 = sVar27;
            if (uVar23 <= uVar25) goto LAB_0017efe0;
          }
          uVar25 = uVar25 + 1;
          lVar24 = lVar24 + 0x88;
        } while (uVar25 < uVar23);
      }
LAB_0017efe0:
      puVar21 = puVar21 + 0x12;
    } while (puVar21 != puVar8);
  }
LAB_0017eff0:
  uVar23 = *(uint *)(param_1 + 2);
  lVar24 = *param_1;
  uVar25 = *(uint *)(param_1 + 1);
  local_190 = (void *)0x0;
  local_188 = (void *)0x0;
  local_180 = 0;
  local_1b8 = param_1;
  uStack_1b0 = param_2;
  local_1a8 = param_3;
  local_1a0 = param_4;
  local_198 = __s;
  pvVar11 = calloc((ulong)uVar23,4);
  if (pvVar11 == (void *)0x0) {
    pvVar12 = calloc((ulong)uVar25,1);
  }
  else {
    if (uVar25 != 0) {
      puVar21 = (uint *)(lVar24 + 0x10);
      puVar8 = puVar21 + (ulong)uVar25 * 0x12;
      do {
        if (*puVar21 != 0) {
          uVar20 = 0;
          puVar18 = (uint *)(*(long *)(puVar21 + -2) + 0x18);
          do {
            while( true ) {
              uVar5 = puVar18[0xc];
              if (uVar5 != 0) {
                uVar3 = *puVar18;
                if (uVar3 < uVar23) {
                  *(int *)((long)pvVar11 + (ulong)uVar3 * 4) =
                       *(int *)((long)pvVar11 + (ulong)uVar3 * 4) + 1;
                  uVar5 = puVar18[0xc];
                }
                if (1 < uVar5) {
                  uVar3 = puVar18[4];
                  if (uVar3 < uVar23) {
                    *(int *)((long)pvVar11 + (ulong)uVar3 * 4) =
                         *(int *)((long)pvVar11 + (ulong)uVar3 * 4) + 1;
                    uVar5 = puVar18[0xc];
                  }
                  if ((2 < uVar5) && (uVar5 = puVar18[8], uVar5 < uVar23)) {
                    *(int *)((long)pvVar11 + (ulong)uVar5 * 4) =
                         *(int *)((long)pvVar11 + (ulong)uVar5 * 4) + 1;
                  }
                }
              }
              uVar5 = puVar18[0x12];
              if (uVar5 != 0) break;
LAB_0017f0cc:
              uVar20 = uVar20 + 1;
              puVar18 = puVar18 + 0x22;
              if (*puVar21 <= uVar20) goto LAB_0017f0e0;
            }
            lVar19 = *(long *)(puVar18 + 0xe);
            lVar24 = 0;
            do {
              while (uVar3 = *(uint *)(lVar19 + lVar24 * 0x10), uVar23 <= uVar3) {
                lVar24 = lVar24 + 1;
                if (uVar5 <= (uint)lVar24) goto LAB_0017f0cc;
              }
              lVar24 = lVar24 + 1;
              *(int *)((long)pvVar11 + (ulong)uVar3 * 4) =
                   *(int *)((long)pvVar11 + (ulong)uVar3 * 4) + 1;
              uVar5 = puVar18[0x12];
            } while ((uint)lVar24 < uVar5);
            uVar20 = uVar20 + 1;
            puVar18 = puVar18 + 0x22;
          } while (uVar20 < *puVar21);
        }
LAB_0017f0e0:
        puVar21 = puVar21 + 0x12;
      } while (puVar21 != puVar8);
    }
    local_190 = pvVar11;
    local_188 = calloc((ulong)uVar25,1);
    pvVar12 = (void *)0x0;
    if (local_188 != (void *)0x0) {
      pvVar11 = calloc(1,0x130);
      if (pvVar11 == (void *)0x0) {
        __s[0xde8] = '\0';
        __s[0xde9] = '\0';
        __s[0xdea] = '\0';
        __s[0xdeb] = '\0';
        __s[0xdec] = '\0';
        __s[0xded] = '\0';
        __s[0xdee] = '\0';
        __s[0xdef] = '\0';
      }
      else {
        pvVar12 = calloc(8,8);
        *(void **)((long)pvVar11 + 0x98) = pvVar12;
        *(undefined4 *)((long)pvVar11 + 0xa4) = 8;
        *(void **)(__s + 0xde8) = pvVar11;
        emit_region(&local_1b8,0,uVar25,pvVar11);
      }
      collect_locals_walk(*(undefined8 *)(__s + 0xde8),__s,param_1);
      if ((((param_5 == (long *)0x0) && (piVar14 = *(int **)(__s + 0xde8), piVar14 != (int *)0x0))
          && (*piVar14 == 0)) && (piVar14[0x28] != 0)) {
        puVar16 = *(undefined8 **)(piVar14 + 0x26);
        puVar1 = puVar16 + (uint)piVar14[0x28];
        do {
          piVar14 = (int *)*puVar16;
          if (((piVar14 != (int *)0x0) && (*piVar14 == 0xb)) &&
             (lVar24 = *(long *)(piVar14 + 0x26), lVar24 != 0)) {
            uVar15 = *(undefined8 *)(lVar24 + 4);
            uVar29 = *(undefined8 *)(lVar24 + 0x1c);
            uVar28 = *(undefined8 *)(lVar24 + 0x14);
            uVar37 = *(undefined8 *)(lVar24 + 0x2c);
            uVar36 = *(undefined8 *)(lVar24 + 0x24);
            uVar39 = *(undefined8 *)(lVar24 + 0x3c);
            uVar38 = *(undefined8 *)(lVar24 + 0x34);
            uVar33 = *(undefined8 *)(lVar24 + 0x4c);
            uVar32 = *(undefined8 *)(lVar24 + 0x44);
            uVar35 = *(undefined8 *)(lVar24 + 0x5c);
            uVar34 = *(undefined8 *)(lVar24 + 0x54);
            *(undefined8 *)(__s + 0x90) = *(undefined8 *)(lVar24 + 0xc);
            *(undefined8 *)pcVar22 = uVar15;
            *(undefined8 *)(__s + 0xa0) = uVar29;
            *(undefined8 *)(__s + 0x98) = uVar28;
            uVar29 = *(undefined8 *)(lVar24 + 0x6c);
            uVar28 = *(undefined8 *)(lVar24 + 100);
            uVar31 = *(undefined8 *)(lVar24 + 0x7c);
            uVar30 = *(undefined8 *)(lVar24 + 0x74);
            *(undefined8 *)(__s + 0xb0) = uVar37;
            *(undefined8 *)(__s + 0xa8) = uVar36;
            *(undefined8 *)(__s + 0xc0) = uVar39;
            *(undefined8 *)(__s + 0xb8) = uVar38;
            uVar15 = *(undefined8 *)(lVar24 + 0x84);
            *(undefined8 *)(__s + 0xd0) = uVar33;
            *(undefined8 *)(__s + 200) = uVar32;
            *(undefined8 *)(__s + 0xe0) = uVar35;
            *(undefined8 *)(__s + 0xd8) = uVar34;
            *(undefined8 *)(__s + 0xf0) = uVar29;
            *(undefined8 *)(__s + 0xe8) = uVar28;
            *(undefined8 *)(__s + 0x100) = uVar31;
            *(undefined8 *)(__s + 0xf8) = uVar30;
            *(undefined8 *)(__s + 0x108) = uVar15;
            break;
          }
          puVar16 = puVar16 + 1;
        } while (puVar1 != puVar16);
      }
      free(local_190);
      free(local_188);
      pcVar22 = __s;
      goto LAB_0017f188;
    }
  }
  free(pvVar11);
  free(pvVar12);
  pcVar22 = (char *)0x0;
  free(__s);
LAB_0017f188:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return pcVar22;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

