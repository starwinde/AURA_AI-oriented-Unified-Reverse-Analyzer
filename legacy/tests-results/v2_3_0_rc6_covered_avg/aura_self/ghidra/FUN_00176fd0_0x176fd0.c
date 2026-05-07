
long * FUN_00176fd0(long param_1,ulong param_2,long param_3,int param_4,undefined4 *param_5,
                   long *param_6)

{
  bool bVar1;
  undefined4 uVar2;
  char cVar3;
  byte bVar4;
  bool bVar5;
  bool bVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  long *__ptr;
  ulong uVar10;
  char *pcVar11;
  char *pcVar12;
  long lVar13;
  ulong *puVar14;
  void *pvVar15;
  char *pcVar16;
  long *plVar17;
  long *plVar18;
  undefined8 *puVar19;
  long *plVar20;
  ulong uVar21;
  long *plVar22;
  size_t sVar23;
  long lVar24;
  ulong uVar25;
  long *plVar26;
  undefined8 *puVar27;
  long *plVar28;
  uint uVar29;
  size_t __nmemb;
  size_t sVar30;
  char *pcVar31;
  byte *__s1;
  ulong *puVar32;
  long lVar33;
  long lVar34;
  uint local_2138;
  ulong local_2130;
  int local_2128;
  long local_2120;
  char *local_2118;
  char *local_2110;
  uint local_2108;
  long local_2100;
  int local_20f0;
  uint local_20ec;
  long local_20e8;
  int local_20dc;
  char *local_20d8;
  long lStack_20d0;
  long lStack_20c8;
  long lStack_20c0;
  long local_20b8;
  long lStack_20b0;
  ulong local_20a8;
  uint local_20a0 [216];
  undefined8 local_1d40;
  char acStack_a8 [64];
  long local_68;
  
  local_1d40 = 0;
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if ((param_1 == 0 || param_2 == 0) || (__ptr = calloc(1,0x28), __ptr == (long *)0x0)) {
LAB_00177348:
    __ptr = (long *)0x0;
    goto LAB_00177ae8;
  }
  *__ptr = param_3;
  if (param_4 == 3) {
    uVar25 = param_2;
    if (0x20 < param_2) {
      uVar25 = 0x20;
    }
    pcVar16 = (char *)(param_1 + 0x60);
    uVar10 = 0;
    local_20dc = 0;
    do {
      pcVar12 = pcVar16 + -0x40;
      iVar9 = strcmp(pcVar12,"push");
      if (((iVar9 == 0) || (iVar9 = strcmp(pcVar12,"stmdb"), iVar9 == 0)) &&
         ((pcVar31 = strstr(pcVar16,"fp"), pcVar31 != (char *)0x0 ||
          (pcVar31 = strstr(pcVar16,"r11"), pcVar31 != (char *)0x0)))) {
        local_20dc = 1;
      }
      iVar9 = strcmp(pcVar12,"sub");
      if (((iVar9 == 0) && (pcVar31 = strstr(pcVar16,"sp"), pcVar31 != (char *)0x0)) &&
         (pcVar31 = strrchr(pcVar16,0x23), pcVar31 != (char *)0x0)) {
        local_20d8 = (char *)0x0;
        uVar21 = strtol(pcVar31 + 1,&local_20d8,0);
        if ((pcVar31 + 1 != local_20d8) && (uVar21 - 1 < 0xfffff)) {
          uVar10 = uVar21;
        }
      }
      if (*pcVar12 == 'b') {
        if ((pcVar16[-0x3f] == 'l') && (pcVar16[-0x3e] == '\0')) break;
        if ((pcVar16[-0x3f] == 'x') && (pcVar16[-0x3e] == '\0')) {
          local_2130 = 4;
          local_2128 = 4;
          local_20f0 = 4;
          goto LAB_0017709c;
        }
      }
      pcVar16 = pcVar16 + 0xe0;
    } while (pcVar16 != (char *)(param_1 + uVar25 * 0xe0 + 0x60));
LAB_00177f24:
    local_2130 = 4;
    local_2128 = 4;
    local_20f0 = 4;
  }
  else {
    if (param_4 == 4) {
      uVar25 = param_2;
      if (0x20 < param_2) {
        uVar25 = 0x20;
      }
      pcVar16 = (char *)(param_1 + 0x60);
      local_2120 = 0;
      local_2110 = (char *)0x0;
      local_20dc = 0;
      do {
        pcVar12 = pcVar16 + -0x40;
        iVar9 = strcmp(pcVar12,"stp");
        lVar24 = local_2120;
        if (iVar9 == 0) {
          pcVar31 = strstr(pcVar16,"x29");
          if ((pcVar31 != (char *)0x0) || (pcVar31 = strstr(pcVar16,"fp"), pcVar31 != (char *)0x0))
          {
            local_20dc = 1;
            iVar9 = strcmp(pcVar12,"stp");
            if (iVar9 != 0) goto LAB_001773a4;
          }
LAB_001773b8:
          pcVar31 = strstr(pcVar16,"[sp");
          if (((pcVar31 != (char *)0x0) && (pcVar31 = strstr(pcVar16,"]!"), pcVar31 != (char *)0x0))
             && (pcVar31 = strrchr(pcVar16,0x23), pcVar31 != (char *)0x0)) {
            local_20d8 = (char *)0x0;
            lVar13 = strtol(pcVar31 + 1,&local_20d8,0);
            if (pcVar31 + 1 != local_20d8) {
              lVar33 = -lVar13;
              if (-1 < lVar13) {
                lVar33 = lVar13;
              }
              lVar24 = local_2120 + lVar33;
              if (0xffffe < lVar33 - 1U) {
                lVar24 = local_2120;
              }
            }
          }
        }
        else {
LAB_001773a4:
          iVar9 = strcmp(pcVar12,"str");
          if (iVar9 == 0) goto LAB_001773b8;
        }
        local_2120 = lVar24;
        iVar9 = strcmp(pcVar12,"mov");
        pcVar31 = local_2110;
        if ((iVar9 == 0) &&
           ((pcVar11 = strstr(pcVar16,"x29"), pcVar11 != (char *)0x0 ||
            (pcVar11 = strstr(pcVar16,"fp"), pcVar11 != (char *)0x0)))) {
          pcVar11 = strstr(pcVar16,"sp");
          if (pcVar11 != (char *)0x0) {
            local_20dc = 1;
            goto LAB_0017747c;
          }
        }
        else {
LAB_0017747c:
          iVar9 = strcmp(pcVar12,"sub");
          if (((iVar9 == 0) && (pcVar11 = strstr(pcVar16,"sp"), pcVar11 != (char *)0x0)) &&
             (pcVar11 = strrchr(pcVar16,0x23), pcVar11 != (char *)0x0)) {
            local_20d8 = (char *)0x0;
            lVar24 = strtol(pcVar11 + 1,&local_20d8,0);
            if ((pcVar11 + 1 != local_20d8) &&
               (pcVar31 = (char *)((long)local_2110 + lVar24), 0xffffe < lVar24 - 1U)) {
              pcVar31 = local_2110;
            }
          }
        }
        local_2110 = pcVar31;
      } while ((((*pcVar12 != 'b') || (pcVar16[-0x3f] != 'l')) || (pcVar16[-0x3e] != '\0')) &&
              ((iVar9 = strcmp(pcVar12,"ret"), iVar9 != 0 &&
               (pcVar16 = pcVar16 + 0xe0, pcVar16 != (char *)(param_1 + uVar25 * 0xe0 + 0x60)))));
      uVar10 = local_2120 + (long)local_2110;
    }
    else {
      if (param_4 == 1) {
        uVar10 = FUN_00176dc0(param_1,param_2,0,&local_20dc);
        goto LAB_00177f24;
      }
      uVar10 = FUN_00176dc0(param_1,param_2,1,&local_20dc);
    }
    local_2130 = 8;
    local_2128 = 8;
    local_20f0 = 8;
  }
LAB_0017709c:
  iVar9 = local_20dc;
  __ptr[1] = uVar10;
  *(int *)(__ptr + 2) = local_20dc;
  if (param_5 != (undefined4 *)0x0) {
    *(undefined4 *)((long)__ptr + 0x14) = *param_5;
  }
  bVar1 = 0 < (long)uVar10;
  bVar5 = local_20dc != 0;
  if (bVar1 || bVar5) {
    if (param_4 == 2) {
      if (0x800 < param_2) {
        param_2 = 0x800;
      }
      pcVar16 = (char *)(param_1 + 0x60);
      __nmemb = 0;
      do {
        pcVar12 = strstr(pcVar16,"rbp");
        if (pcVar12 != (char *)0x0) {
          pcVar31 = pcVar16 + -0x40;
          iVar7 = strcmp(pcVar31,"mov");
          if (((iVar7 != 0) || (pcVar11 = strstr(pcVar16,"rsp"), pcVar11 == (char *)0x0)) &&
             ((iVar7 = strcmp(pcVar31,"push"), iVar7 != 0 &&
              ((iVar7 = strcmp(pcVar31,"pop"), iVar7 != 0 &&
               (pcVar11 = strchr(pcVar16,0x5b), pcVar11 != (char *)0x0 && pcVar11 <= pcVar12)))))) {
            pcVar11 = pcVar12 + 3;
            cVar3 = pcVar12[3];
            while (cVar3 == ' ') {
              pcVar11 = pcVar11 + 1;
              cVar3 = *pcVar11;
            }
            if (cVar3 == ']') {
              uVar25 = 0;
            }
            else {
              if (cVar3 == '-') {
                local_2100 = -1;
              }
              else {
                if (cVar3 != '+') goto LAB_0017820c;
                local_2100 = 1;
              }
              pcVar11 = pcVar11 + 1;
              cVar3 = *pcVar11;
              while (cVar3 == ' ') {
                pcVar11 = pcVar11 + 1;
                cVar3 = *pcVar11;
              }
              local_20d8 = (char *)0x0;
              lVar24 = strtol(pcVar11,&local_20d8,0);
              if (local_20d8 == pcVar11) goto LAB_0017820c;
              uVar25 = lVar24 * local_2100;
            }
            pcVar12 = strstr(pcVar16,"xmmword");
            local_2100._0_4_ = 0x10;
            if (pcVar12 == (char *)0x0) {
              pcVar12 = strstr(pcVar16,"qword");
              local_2100._0_4_ = 8;
              if (pcVar12 == (char *)0x0) {
                pcVar12 = strstr(pcVar16,"dword");
                local_2100._0_4_ = 4;
                if (pcVar12 == (char *)0x0) {
                  pcVar12 = strstr(pcVar16,"byte");
                  local_2100._0_4_ = 1;
                  if (pcVar12 == (char *)0x0) {
                    pcVar12 = strstr(pcVar16,"word ptr");
                    local_2100._0_4_ = 2;
                    if (pcVar12 == (char *)0x0) {
                      iVar7 = strcmp(pcVar31,"movzx");
                      local_2100._0_4_ = 4;
                      if (iVar7 != 0) {
                        iVar7 = strcmp(pcVar31,"movsx");
                        local_2100._0_4_ = 4;
                        if (iVar7 != 0) {
                          local_2100._0_4_ = 8;
                        }
                      }
                    }
                  }
                }
              }
            }
            uVar8 = (uint)__nmemb;
            sVar23 = 0;
            if (uVar8 != 0) {
              puVar14 = &local_20a8;
              do {
                if (*puVar14 == uVar25) {
                  if ((uint)puVar14[1] < (uint)local_2100) {
                    *(uint *)(puVar14 + 1) = (uint)local_2100;
                  }
                  *(int *)((long)puVar14 + 0xc) = *(int *)((long)puVar14 + 0xc) + 1;
                  goto LAB_0017820c;
                }
                puVar14 = puVar14 + 2;
              } while (&local_20a8 + __nmemb * 2 != puVar14);
              sVar23 = __nmemb;
              if (0x1ff < uVar8) goto LAB_0017820c;
            }
            __nmemb = (size_t)(uVar8 + 1);
            (&local_20a8)[sVar23 * 2] = uVar25;
            local_20a0[sVar23 * 4] = (uint)local_2100;
            local_20a0[sVar23 * 4 + 1] = 1;
          }
        }
LAB_0017820c:
        pcVar16 = pcVar16 + 0xe0;
      } while ((char *)(param_1 + param_2 * 0xe0 + 0x60) != pcVar16);
LAB_00177758:
      uVar8 = (uint)__nmemb;
      local_2108 = uVar8 + 4;
      if (1 < uVar8) {
        qsort(&local_20a8,__nmemb,0x10,FUN_00176da0);
      }
      pvVar15 = calloc((ulong)(uVar8 + 4),0x30);
      __ptr[3] = (long)pvVar15;
      if (pvVar15 == (void *)0x0) goto LAB_00177320;
      uVar25 = (ulong)*(uint *)(__ptr + 4);
      if (uVar8 != 0) {
        if (iVar9 == 0) {
          puVar32 = &local_20a8;
          puVar14 = puVar32 + __nmemb * 2;
          local_2118 = "__m128";
          do {
            lVar24 = uVar25 * 0x30;
            uVar21 = *puVar32;
            uVar25 = puVar32[1];
            *(ulong *)((long)pvVar15 + lVar24) = uVar21;
            *(int *)((long)pvVar15 + lVar24 + 8) = (int)uVar25;
            uVar2 = *(undefined4 *)((long)puVar32 + 0xc);
            *(undefined4 *)((long)pvVar15 + lVar24 + 0x24) = 0;
            *(undefined4 *)((long)pvVar15 + lVar24 + 0x28) = uVar2;
            pcVar16 = "uint32_t";
            if ((long)uVar10 < 1) {
              if ((long)uVar21 < 0) {
LAB_00177d50:
                uVar21 = (ulong)(uint)-(int)uVar21;
                *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 0;
                goto LAB_00177c0c;
              }
              if (uVar21 != 0) {
                if (uVar21 == local_2130) {
                  *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 3;
                  pcVar12 = strdup("return_address");
                  goto LAB_00177ce0;
                }
                if ((long)uVar21 <= (long)local_2130) {
                  pcVar12 = "saved_%x";
                  *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 1;
                  goto LAB_00177c20;
                }
                *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 2;
                __snprintf_chk(acStack_a8,0x40,2,0x40,"arg_%x");
                pcVar12 = strdup(acStack_a8);
                *(char **)((long)pvVar15 + lVar24 + 0x10) = pcVar12;
                uVar8 = *(uint *)((long)pvVar15 + lVar24 + 8);
                goto joined_r0x00177c44;
              }
              *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 1;
              if (param_4 - 1U < 2) {
                pcVar12 = strdup("saved_rbp");
              }
              else {
                pcVar12 = strdup("saved_fp");
              }
LAB_00177ce0:
              *(int *)((long)pvVar15 + lVar24 + 8) = local_2128;
              *(char **)((long)pvVar15 + lVar24 + 0x10) = pcVar12;
              if (local_2128 != 4) {
LAB_00177cf4:
                pcVar16 = "uint64_t";
              }
LAB_00177c68:
              pcVar16 = strdup(pcVar16);
              lVar13 = __ptr[4];
              *(char **)((long)pvVar15 + lVar24 + 0x18) = pcVar16;
              uVar8 = (int)lVar13 + 1;
              *(uint *)(__ptr + 4) = uVar8;
            }
            else {
              if ((long)uVar21 < 0) goto LAB_00177d50;
              *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 0;
LAB_00177c0c:
              pcVar12 = "var_%x";
LAB_00177c20:
              __snprintf_chk(acStack_a8,0x40,2,0x40,pcVar12,uVar21);
              pcVar12 = strdup(acStack_a8);
              *(char **)((long)pvVar15 + lVar24 + 0x10) = pcVar12;
              uVar8 = *(uint *)((long)pvVar15 + lVar24 + 8);
joined_r0x00177c44:
              if (uVar8 == 4) goto LAB_00177c68;
              if (3 < uVar8) {
                if (uVar8 == 8) goto LAB_00177cf4;
                pcVar16 = "unknown";
                if (uVar8 == 0x10) {
                  pcVar16 = local_2118;
                }
                goto LAB_00177c68;
              }
              if (uVar8 == 1) {
                pcVar16 = "uint8_t";
                goto LAB_00177c68;
              }
              pcVar16 = "unknown";
              if (uVar8 == 2) {
                pcVar16 = "uint16_t";
              }
              pcVar16 = strdup(pcVar16);
              lVar13 = __ptr[4];
              *(char **)((long)pvVar15 + lVar24 + 0x18) = pcVar16;
              uVar8 = (int)lVar13 + 1;
              *(uint *)(__ptr + 4) = uVar8;
            }
            uVar25 = (ulong)uVar8;
            if (puVar14 == puVar32 + 2) goto LAB_00177d40;
            puVar32 = puVar32 + 2;
            pvVar15 = (void *)__ptr[3];
          } while( true );
        }
        puVar32 = &local_20a8;
        puVar14 = puVar32 + __nmemb * 2;
        local_2118 = "uint64_t";
        local_2110 = "uint32_t";
        do {
          lVar24 = uVar25 * 0x30;
          uVar21 = *puVar32;
          uVar25 = puVar32[1];
          *(ulong *)((long)pvVar15 + lVar24) = uVar21;
          *(int *)((long)pvVar15 + lVar24 + 8) = (int)uVar25;
          uVar2 = *(undefined4 *)((long)puVar32 + 0xc);
          *(undefined4 *)((long)pvVar15 + lVar24 + 0x24) = 0;
          *(undefined4 *)((long)pvVar15 + lVar24 + 0x28) = uVar2;
          pcVar16 = local_2110;
          if (bVar1 && param_4 == 4) {
            if ((long)uVar21 < (long)uVar10) {
              if ((long)uVar21 < 0) goto LAB_00177b94;
              *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 0;
LAB_00177b2c:
              pcVar12 = "var_%x";
            }
            else {
LAB_00177848:
              if (uVar21 == local_2130) {
                *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 3;
                pcVar12 = strdup("return_address");
                goto LAB_00177b70;
              }
              if ((long)uVar21 < (long)local_2130) {
                pcVar12 = "saved_%x";
                *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 1;
              }
              else {
                pcVar12 = "arg_%x";
                *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 2;
              }
            }
            __snprintf_chk(acStack_a8,0x40,2,0x40,pcVar12,uVar21);
            pcVar12 = strdup(acStack_a8);
            *(char **)((long)pvVar15 + lVar24 + 0x10) = pcVar12;
            uVar8 = *(uint *)((long)pvVar15 + lVar24 + 8);
            if (uVar8 == 4) goto LAB_001777f8;
            if (uVar8 < 5) {
              if (uVar8 == 1) {
                pcVar16 = "uint8_t";
              }
              else {
                pcVar16 = "uint16_t";
                if (uVar8 != 2) goto LAB_00177e60;
              }
              goto LAB_001777f8;
            }
            if (uVar8 == 8) goto LAB_00177b84;
            if (uVar8 != 0x10) {
LAB_00177e60:
              pcVar16 = "unknown";
              goto LAB_001777f8;
            }
            pcVar16 = strdup("__m128");
            lVar13 = __ptr[4];
            *(char **)((long)pvVar15 + lVar24 + 0x18) = pcVar16;
            uVar8 = (int)lVar13 + 1;
            *(uint *)(__ptr + 4) = uVar8;
          }
          else {
            if ((long)uVar21 < 0) {
LAB_00177b94:
              uVar21 = (ulong)(uint)-(int)uVar21;
              *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 0;
              goto LAB_00177b2c;
            }
            if (uVar21 != 0) goto LAB_00177848;
            *(undefined4 *)((long)pvVar15 + lVar24 + 0x20) = 1;
            if (param_4 - 1U < 2) {
              pcVar12 = strdup("saved_rbp");
            }
            else {
              pcVar12 = strdup("saved_fp");
            }
LAB_00177b70:
            *(int *)((long)pvVar15 + lVar24 + 8) = local_2128;
            *(char **)((long)pvVar15 + lVar24 + 0x10) = pcVar12;
            if (local_2128 != 4) {
LAB_00177b84:
              pcVar16 = local_2118;
            }
LAB_001777f8:
            pcVar16 = strdup(pcVar16);
            lVar13 = __ptr[4];
            *(char **)((long)pvVar15 + lVar24 + 0x18) = pcVar16;
            uVar8 = (int)lVar13 + 1;
            *(uint *)(__ptr + 4) = uVar8;
          }
          uVar25 = (ulong)uVar8;
          if (puVar14 == puVar32 + 2) goto LAB_001778e8;
          puVar32 = puVar32 + 2;
          pvVar15 = (void *)__ptr[3];
        } while( true );
      }
    }
    else {
      if (param_4 == 4) {
        pcVar16 = (char *)(param_1 + 0x20);
        if (0x800 < param_2) {
          param_2 = 0x800;
        }
        uVar25 = 0;
        do {
          if ((*pcVar16 != '\0') && (iVar7 = strcmp(pcVar16,"ret"), iVar7 == 0)) {
            param_2 = uVar25 + 1;
            break;
          }
          uVar25 = uVar25 + 1;
          pcVar16 = pcVar16 + 0xe0;
        } while (param_2 != uVar25);
        pcVar16 = (char *)(param_1 + 0x60);
        pcVar12 = pcVar16 + param_2 * 0xe0;
        __nmemb = 0;
        do {
          bVar4 = pcVar16[-0x40];
          uVar8 = (uint)bVar4;
          __s1 = (byte *)(pcVar16 + -0x40);
          if (((((((bVar4 == 0x6c) && (pcVar16[-0x3f] == 'd')) && (pcVar16[-0x3e] == 'r')) ||
                (((bVar4 == 0x73 && (pcVar16[-0x3f] == 't')) && (pcVar16[-0x3e] == 'r')))) ||
               ((iVar7 = strncmp((char *)__s1,"ldur",4), iVar7 == 0 ||
                (iVar7 = strncmp((char *)__s1,"stur",4), iVar7 == 0)))) ||
              (((uVar8 == 0x6c && ((pcVar16[-0x3f] == 'd' && (pcVar16[-0x3e] == 'p')))) ||
               ((uVar8 == 0x73 && ((pcVar16[-0x3f] == 't' && (pcVar16[-0x3e] == 'p')))))))) &&
             (((pcVar31 = strstr(pcVar16,"x29"), pcVar31 != (char *)0x0 ||
               ((pcVar31 = strstr(pcVar16,"fp"), pcVar31 != (char *)0x0 ||
                (pcVar31 = strstr(pcVar16,"sp"), pcVar31 != (char *)0x0)))) &&
              (pcVar11 = strchr(pcVar16,0x5b), pcVar11 != (char *)0x0 && pcVar11 <= pcVar31)))) {
            pcVar31 = strchr(pcVar31,0x23);
            if (pcVar31 == (char *)0x0) {
              uVar25 = 0;
            }
            else {
              local_20d8 = (char *)0x0;
              uVar25 = strtol(pcVar31 + 1,&local_20d8,0);
              if (pcVar31 + 1 == local_20d8) goto LAB_00177748;
              uVar8 = (uint)*__s1;
            }
            pcVar31 = strstr((char *)__s1,"ldrb");
            local_20e8 = 1;
            local_20ec = 1;
            if (pcVar31 == (char *)0x0) {
              local_20ec = 1;
              local_20e8 = 1;
              pcVar31 = strstr((char *)__s1,"strb");
              if (pcVar31 == (char *)0x0) {
                pcVar31 = strstr((char *)__s1,"ldurb");
                local_20e8 = 1;
                local_20ec = 1;
                if (pcVar31 == (char *)0x0) {
                  pcVar31 = strstr((char *)__s1,"sturb");
                  local_20e8 = 1;
                  local_20ec = 1;
                  if (pcVar31 == (char *)0x0) {
                    pcVar31 = strstr((char *)__s1,"ldrh");
                    if ((((pcVar31 == (char *)0x0) &&
                         (pcVar31 = strstr((char *)__s1,"strh"), pcVar31 == (char *)0x0)) &&
                        (pcVar31 = strstr((char *)__s1,"ldurh"), pcVar31 == (char *)0x0)) &&
                       (pcVar31 = strstr((char *)__s1,"sturh"), pcVar31 == (char *)0x0)) {
                      if (*pcVar16 == 'w') {
                        local_20ec = 4;
                        local_20e8 = 4;
                      }
                      else {
                        pcVar31 = strstr(pcVar16,", w");
                        local_20e8 = 4;
                        if (pcVar31 == (char *)0x0) {
                          local_20e8 = 8;
                        }
                        local_20ec = 8;
                        if (pcVar31 != (char *)0x0) {
                          local_20ec = 4;
                        }
                      }
                    }
                    else {
                      local_20e8 = 2;
                      local_20ec = 2;
                    }
                  }
                }
              }
            }
            if (((uVar8 != 0x6c) || (pcVar16[-0x3f] != 'd')) ||
               (bVar6 = bVar1 || bVar5, pcVar16[-0x3e] != 'p')) {
              iVar7 = uVar8 - 0x73;
              if ((iVar7 == 0) && (iVar7 = (byte)pcVar16[-0x3f] - 0x74, iVar7 == 0)) {
                iVar7 = (byte)pcVar16[-0x3e] - 0x70;
              }
              bVar6 = iVar7 == 0;
            }
            uVar8 = (uint)__nmemb;
            sVar23 = 0;
            if (uVar8 != 0) {
              puVar14 = &local_20a8;
              do {
                if (*puVar14 == uVar25) {
                  if ((uint)puVar14[1] < local_20ec) {
                    *(uint *)(puVar14 + 1) = local_20ec;
                  }
                  *(int *)((long)puVar14 + 0xc) = *(int *)((long)puVar14 + 0xc) + 1;
                  sVar30 = __nmemb;
                  goto joined_r0x00177744;
                }
                puVar14 = puVar14 + 2;
              } while (&local_20a8 + __nmemb * 2 != puVar14);
              sVar23 = __nmemb;
              if (0x1ff < uVar8) goto LAB_00177748;
            }
            uVar8 = uVar8 + 1;
            sVar30 = (size_t)uVar8;
            (&local_20a8)[sVar23 * 2] = uVar25;
            local_20a0[sVar23 * 4] = local_20ec;
            local_20a0[sVar23 * 4 + 1] = 1;
joined_r0x00177744:
            __nmemb = sVar30;
            if (uVar8 < 0x200 && bVar6) {
              puVar14 = &local_20a8;
              do {
                if (uVar25 + local_20e8 == *puVar14) {
                  *(int *)((long)puVar14 + 0xc) = *(int *)((long)puVar14 + 0xc) + 1;
                  goto LAB_00177748;
                }
                puVar14 = puVar14 + 2;
              } while (puVar14 != &local_20a8 + sVar30 * 2);
              (&local_20a8)[sVar30 * 2] = uVar25 + local_20e8;
              __nmemb = (size_t)((int)sVar30 + 1);
              local_20a0[sVar30 * 4] = local_20ec;
              local_20a0[sVar30 * 4 + 1] = 1;
            }
          }
LAB_00177748:
          pcVar16 = pcVar16 + 0xe0;
        } while (pcVar16 != pcVar12);
        goto LAB_00177758;
      }
      if (param_4 == 1) {
        if (0x800 < param_2) {
          param_2 = 0x800;
        }
        pcVar16 = (char *)(param_1 + 0x60);
        __nmemb = 0;
        do {
          pcVar12 = strstr(pcVar16,"ebp");
          if (pcVar12 != (char *)0x0) {
            pcVar31 = pcVar16 + -0x40;
            iVar7 = strcmp(pcVar31,"mov");
            if ((((iVar7 != 0) || (pcVar11 = strstr(pcVar16,"esp"), pcVar11 == (char *)0x0)) &&
                (iVar7 = strcmp(pcVar31,"push"), iVar7 != 0)) &&
               ((iVar7 = strcmp(pcVar31,"pop"), iVar7 != 0 &&
                (pcVar31 = strchr(pcVar16,0x5b), pcVar31 != (char *)0x0 && pcVar31 <= pcVar12)))) {
              pcVar31 = pcVar12 + 3;
              cVar3 = pcVar12[3];
              while (cVar3 == ' ') {
                pcVar31 = pcVar31 + 1;
                cVar3 = *pcVar31;
              }
              if (cVar3 == ']') {
                uVar25 = 0;
              }
              else {
                if (cVar3 == '-') {
                  lVar24 = -1;
                }
                else {
                  if (cVar3 != '+') goto LAB_0017714c;
                  lVar24 = 1;
                }
                pcVar31 = pcVar31 + 1;
                cVar3 = *pcVar31;
                while (cVar3 == ' ') {
                  pcVar31 = pcVar31 + 1;
                  cVar3 = *pcVar31;
                }
                local_20d8 = (char *)0x0;
                lVar13 = strtol(pcVar31,&local_20d8,0);
                if (pcVar31 == local_20d8) goto LAB_0017714c;
                uVar25 = lVar13 * lVar24;
              }
              pcVar12 = strstr(pcVar16,"xmmword");
              uVar8 = 0x10;
              if (pcVar12 == (char *)0x0) {
                pcVar12 = strstr(pcVar16,"qword");
                uVar8 = 8;
                if (pcVar12 == (char *)0x0) {
                  pcVar12 = strstr(pcVar16,"dword");
                  uVar8 = 4;
                  if (pcVar12 == (char *)0x0) {
                    pcVar12 = strstr(pcVar16,"byte");
                    uVar8 = 1;
                    if (pcVar12 == (char *)0x0) {
                      pcVar12 = strstr(pcVar16,"word ptr");
                      uVar8 = 2;
                      if (pcVar12 == (char *)0x0) {
                        uVar8 = 4;
                      }
                    }
                  }
                }
              }
              uVar29 = (uint)__nmemb;
              sVar23 = 0;
              if (uVar29 != 0) {
                puVar14 = &local_20a8;
                do {
                  if (*puVar14 == uVar25) {
                    if ((uint)puVar14[1] < uVar8) {
                      *(uint *)(puVar14 + 1) = uVar8;
                    }
                    *(int *)((long)puVar14 + 0xc) = *(int *)((long)puVar14 + 0xc) + 1;
                    goto LAB_0017714c;
                  }
                  puVar14 = puVar14 + 2;
                } while (puVar14 != &local_20a8 + __nmemb * 2);
                sVar23 = __nmemb;
                if (0x1ff < uVar29) goto LAB_0017714c;
              }
              __nmemb = (size_t)(uVar29 + 1);
              (&local_20a8)[sVar23 * 2] = uVar25;
              local_20a0[sVar23 * 4] = uVar8;
              local_20a0[sVar23 * 4 + 1] = 1;
            }
          }
LAB_0017714c:
          pcVar16 = pcVar16 + 0xe0;
        } while ((char *)(param_1 + param_2 * 0xe0 + 0x60) != pcVar16);
        goto LAB_00177758;
      }
      pvVar15 = calloc(4,0x30);
      __ptr[3] = (long)pvVar15;
      if (pvVar15 == (void *)0x0) goto LAB_00177320;
      uVar25 = (ulong)*(uint *)(__ptr + 4);
    }
    if (iVar9 == 0) goto LAB_00177d40;
    local_2108 = 4;
LAB_001778e8:
    local_2138 = param_4 - 1;
    plVar26 = (long *)__ptr[3];
    uVar8 = (uint)uVar25;
    if (uVar8 != 0) {
      plVar28 = plVar26;
      do {
        if ((*plVar28 == 0) && ((int)plVar28[4] == 1)) goto LAB_0017792c;
        plVar28 = plVar28 + 6;
      } while (plVar26 + uVar25 * 6 != plVar28);
      if (uVar8 < local_2108) {
        uVar8 = uVar8 + 1;
        plVar28 = plVar26 + uVar25 * 6;
        goto LAB_001785b4;
      }
LAB_0017792c:
      if (local_2138 < 2) goto LAB_00178564;
      plVar28 = plVar26;
      if (uVar8 != 1) goto LAB_00177940;
      if (param_6 == (long *)0x0) goto LAB_001785a4;
      if (plVar26 != (long *)0x0) goto LAB_001779cc;
      uVar25 = 1;
      goto LAB_00177aa4;
    }
    uVar8 = 1;
    plVar28 = plVar26;
LAB_001785b4:
    *plVar28 = 0;
    *(undefined4 *)(plVar28 + 5) = 0;
    lVar24 = DAT_0020c578;
    *(int *)(plVar28 + 1) = local_2128;
    plVar28[4] = lVar24;
    if (1 < local_2138) {
      pcVar16 = strdup("saved_fp");
      plVar28[2] = (long)pcVar16;
      if (local_20f0 == 4) {
        pcVar16 = strdup("uint32_t");
      }
      else {
        pcVar16 = strdup("uint64_t");
      }
      uVar25 = (ulong)uVar8;
      plVar28[3] = (long)pcVar16;
      *(uint *)(__ptr + 4) = uVar8;
      if (uVar8 != 1) {
        plVar28 = (long *)__ptr[3];
        goto LAB_00177940;
      }
LAB_00178598:
      if ((param_6 == (long *)0x0) || (plVar26 = (long *)__ptr[3], plVar26 == (long *)0x0)) {
LAB_001785a4:
        uVar25 = 1;
        goto LAB_00177aa4;
      }
      goto LAB_001779cc;
    }
    pcVar16 = strdup("saved_rbp");
    plVar28[2] = (long)pcVar16;
    if (local_20f0 == 4) {
      pcVar16 = strdup("uint32_t");
      uVar25 = (ulong)uVar8;
      plVar28[3] = (long)pcVar16;
      *(uint *)(__ptr + 4) = uVar8;
    }
    else {
      pcVar16 = strdup("uint64_t");
      uVar25 = (ulong)uVar8;
      plVar28[3] = (long)pcVar16;
      *(uint *)(__ptr + 4) = uVar8;
    }
LAB_00178564:
    lVar24 = DAT_0020c580;
    plVar28 = plVar26 + 4;
    plVar18 = plVar28 + uVar25 * 6;
    do {
      uVar8 = (uint)uVar25;
      if ((int)*plVar28 == 3) goto LAB_00178590;
      plVar28 = plVar28 + 6;
    } while (plVar18 != plVar28);
    if (local_2108 <= uVar8) {
LAB_00178590:
      if (uVar8 == 1) goto LAB_00178598;
      goto LAB_00177d48;
    }
    plVar26[uVar25 * 6] = local_2130;
    *(int *)(plVar26 + uVar25 * 6 + 1) = local_2128;
    *(undefined4 *)(plVar26 + uVar25 * 6 + 5) = 0;
    plVar26[uVar25 * 6 + 4] = lVar24;
    pcVar16 = strdup("return_address");
    plVar26[uVar25 * 6 + 2] = (long)pcVar16;
    pcVar16 = strdup("void*");
    plVar28 = (long *)__ptr[3];
    plVar26[uVar25 * 6 + 3] = (long)pcVar16;
    uVar25 = (ulong)(uVar8 + 1);
    *(uint *)(__ptr + 4) = uVar8 + 1;
LAB_00177940:
    iVar7 = 1;
    plVar26 = plVar28;
    do {
      plVar22 = plVar26 + 6;
      lStack_20d0 = plVar26[7];
      local_20d8 = (char *)*plVar22;
      lStack_20c0 = plVar26[9];
      lStack_20c8 = plVar26[8];
      lStack_20b0 = plVar26[0xb];
      local_20b8 = plVar26[10];
      lVar24 = *plVar22;
      plVar18 = plVar22;
      plVar26 = plVar22;
      do {
        plVar17 = plVar26 + -6;
        plVar20 = plVar18;
        if (*plVar17 <= lVar24) break;
        lVar13 = *plVar17;
        lVar34 = plVar26[-3];
        lVar33 = plVar26[-4];
        plVar18[1] = plVar26[-5];
        *plVar18 = lVar13;
        plVar18[3] = lVar34;
        plVar18[2] = lVar33;
        lVar13 = plVar26[-2];
        plVar18[5] = plVar26[-1];
        plVar18[4] = lVar13;
        plVar18 = plVar18 + -6;
        plVar20 = plVar28;
        plVar26 = plVar17;
      } while (plVar28 != plVar17);
      iVar7 = iVar7 + 1;
      plVar20[1] = lStack_20d0;
      *plVar20 = (long)local_20d8;
      plVar20[3] = lStack_20c0;
      plVar20[2] = lStack_20c8;
      plVar20[5] = lStack_20b0;
      plVar20[4] = local_20b8;
      plVar26 = plVar22;
    } while (iVar7 != (int)uVar25);
    if ((param_6 != (long *)0x0) && (plVar26 = plVar28, plVar28 != (long *)0x0)) {
LAB_001779cc:
      plVar28 = plVar26 + (ulong)((int)uVar25 - 1) * 6;
      while (*(uint *)(param_6 + 3) != 0) {
        puVar27 = (undefined8 *)param_6[2];
        puVar19 = puVar27 + (ulong)*(uint *)(param_6 + 3) * 7;
        do {
          if (((param_3 == puVar27[4]) &&
              (uVar8 = *(uint *)((long)puVar27 + 0xc), (uVar8 & 0xfffffffd) == 0)) &&
             (puVar27[3] == *plVar26)) {
            if (((char *)*puVar27 != (char *)0x0) && (*(char *)*puVar27 != '\0')) {
              free((void *)plVar26[2]);
              pcVar16 = strdup((char *)*puVar27);
              uVar8 = *(uint *)((long)puVar27 + 0xc);
              plVar26[2] = (long)pcVar16;
            }
            *(undefined4 *)((long)plVar26 + 0x24) = 1;
            if (uVar8 == 2) {
              *(undefined4 *)(plVar26 + 4) = 2;
            }
            if (*(uint *)(puVar27 + 1) < *(uint *)(param_6 + 1)) {
              lVar24 = *param_6 + (ulong)*(uint *)(puVar27 + 1) * 0x50;
              if ((*(char **)(lVar24 + 8) != (char *)0x0) && (**(char **)(lVar24 + 8) != '\0')) {
                free((void *)plVar26[3]);
                pcVar16 = strdup(*(char **)(lVar24 + 8));
                plVar26[3] = (long)pcVar16;
              }
              if (*(long *)(lVar24 + 0x10) - 1U < 0xffff) {
                *(int *)(plVar26 + 1) = (int)*(long *)(lVar24 + 0x10);
              }
            }
            break;
          }
          puVar27 = puVar27 + 7;
        } while (puVar19 != puVar27);
        if (plVar28 == plVar26) break;
        plVar26 = plVar26 + 6;
      }
      uVar25 = (ulong)*(uint *)(__ptr + 4);
    }
  }
  else {
    pvVar15 = calloc(4,0x30);
    __ptr[3] = (long)pvVar15;
    if (pvVar15 == (void *)0x0) {
LAB_00177320:
      free(__ptr);
      goto LAB_00177348;
    }
    uVar25 = (ulong)*(uint *)(__ptr + 4);
LAB_00177d40:
    if (1 < (uint)uVar25) {
LAB_00177d48:
      plVar28 = (long *)__ptr[3];
      goto LAB_00177940;
    }
    if ((param_6 != (long *)0x0) &&
       ((plVar26 = (long *)__ptr[3], plVar26 != (long *)0x0 && ((uint)uVar25 != 0)))) {
      uVar25 = 1;
      goto LAB_001779cc;
    }
  }
LAB_00177aa4:
  FUN_00140820(1,0,0,"stack: func 0x%lx frame=%d fp=%d vars=%u",param_3,uVar10 & 0xffffffff,iVar9,
               uVar25);
LAB_00177ae8:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return __ptr;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

