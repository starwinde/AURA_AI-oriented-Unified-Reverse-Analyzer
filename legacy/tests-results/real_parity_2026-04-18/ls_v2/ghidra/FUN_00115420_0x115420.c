
undefined8 FUN_00115420(char *param_1,ulong param_2,uint param_3,char *param_4)

{
  bool bVar1;
  undefined8 *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 *puVar7;
  char *pcVar8;
  byte bVar9;
  undefined1 *puVar10;
  uint uVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  char *pcVar17;
  undefined8 uVar18;
  undefined8 *puVar19;
  ssize_t sVar20;
  long lVar21;
  size_t sVar22;
  size_t sVar23;
  ulong uVar24;
  char *pcVar25;
  char *pcVar26;
  void *pvVar27;
  int *piVar28;
  uint uVar29;
  uint uVar30;
  uint *__s;
  char *pcVar31;
  char *pcVar32;
  uint *__s_00;
  uint uVar33;
  undefined8 uVar34;
  long lVar35;
  uint *puVar36;
  char cVar37;
  ulong uVar38;
  long lVar39;
  char cVar40;
  uint *puVar41;
  undefined1 auStack_350 [16];
  uint *local_340;
  uint *local_338;
  undefined8 local_330;
  undefined *local_328;
  uint local_320;
  uint local_31c;
  undefined8 local_318;
  char local_2fd [5];
  uint local_2f8;
  uint local_2f4 [3];
  undefined4 local_2e8;
  char local_2e4 [636];
  long local_68;
  undefined1 *puVar11;
  
  lVar39 = DAT_00141038;
  lVar35 = DAT_00140ee0;
  iVar16 = (int)param_2;
  uVar4 = param_3 & 0xff;
  puVar10 = auStack_350;
  puVar11 = auStack_350;
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if (DAT_00140ee0 == DAT_00141448) {
    lVar21 = reallocarray(DAT_00141038,DAT_00140ee0,0x180);
    if ((lVar21 == 0) && (lVar39 == 0 || lVar35 != 0)) {
                    /* WARNING: Subroutine does not return */
      FUN_0010d454();
    }
    DAT_00141448 = DAT_00141448 << 1;
    DAT_00141038 = lVar21;
  }
  bVar9 = DAT_00140ef0;
  puVar2 = (undefined8 *)(DAT_00141038 + DAT_00140ee0 * 0xc0);
  puVar2[0x11] = 0;
  puVar2[0x10] = 0;
  puVar2[0x13] = 0;
  puVar2[0x12] = 0;
  puVar2[0x15] = 0;
  puVar2[0x14] = 0;
  puVar2[0x17] = 0;
  puVar2[0x16] = 0;
  *(int *)(puVar2 + 0x13) = iVar16;
  *(undefined4 *)((long)puVar2 + 0xb4) = 0xffffffff;
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
  puVar2[0xb] = 0;
  puVar2[10] = 0;
  puVar2[0xd] = 0;
  puVar2[0xc] = 0;
  puVar2[0xf] = 0;
  puVar2[0xe] = 0;
  if (((bVar9 & 1) == 0) && ((DAT_00141280 & 1) != 0)) {
    uVar33 = FUN_0010ae30(param_1);
    *(uint *)((long)puVar2 + 0xb4) = uVar33 & 0xff;
    if ((uVar33 & 1) != 0) {
      DAT_00140ef0 = 1;
    }
  }
  local_31c = param_3 & 1;
  pcVar17 = param_1;
  if ((param_3 & 1) != 0) {
    cVar37 = *param_1;
    if (cVar37 == '/') {
      uVar33 = DAT_001413b2 & 1;
    }
    else {
      cVar40 = *param_4;
      uVar33 = DAT_001413b2 & 1;
      if (cVar40 != '\0') goto LAB_00115ea8;
    }
LAB_0011553c:
    if (uVar33 != 0) {
LAB_00115d24:
      lVar35 = FUN_00114d14(pcVar17);
      puVar2[2] = lVar35;
      if (lVar35 == 0) {
        uVar34 = dcgettext(0,"error canonicalizing %s",5);
        FUN_0010ad30(uVar4,uVar34,pcVar17);
      }
    }
LAB_00115540:
    uVar33 = DAT_0014142c;
    uVar13 = FUN_0010aa54();
    if (uVar33 < 4) {
      if ((uVar33 < 2) || (local_31c == 0)) {
LAB_00115564:
        local_318 = puVar2 + 3;
LAB_00115570:
        uVar13 = FUN_0010aa54();
        uVar33 = 0;
        iVar14 = FUN_0010ab50(0xffffff9c,pcVar17,local_318,0x100,uVar13);
        goto joined_r0x00115834;
      }
      local_318 = puVar2 + 3;
      iVar14 = FUN_0010ab50(0xffffff9c,pcVar17,local_318,0,uVar13);
      if (DAT_0014142c != 2) {
        if (iVar14 < 0) {
          piVar28 = __errno_location();
          if (*piVar28 == 0x28 || *piVar28 == 2) goto LAB_00115570;
          goto LAB_001163a8;
        }
        if ((*(uint *)(puVar2 + 5) & 0xf000) == 0x4000) goto LAB_0011626c;
        goto LAB_00115570;
      }
LAB_0011626c:
      uVar33 = uVar4;
      if (iVar14 != 0) {
LAB_001163a8:
        uVar34 = dcgettext(0,"cannot access %s",5);
        FUN_0010ad30(1,uVar34,pcVar17);
        uVar34 = 0;
        puVar2[0x14] = &DAT_001400c8;
        goto LAB_001157c0;
      }
    }
    else {
      if (uVar33 != 4) goto LAB_00115564;
LAB_0011580c:
      local_318 = puVar2 + 3;
      uVar33 = 1;
      iVar14 = FUN_0010ab50(0xffffff9c,pcVar17,local_318,0,uVar13);
joined_r0x00115834:
      if (iVar14 != 0) {
        uVar34 = dcgettext(0,"cannot access %s",5);
        FUN_0010ad30(uVar4,uVar34,pcVar17);
        puVar2[0x14] = &DAT_001400c8;
        if (local_31c == 0) {
          uVar34 = FUN_0010f784(param_1);
          *puVar2 = uVar34;
          uVar34 = 0;
          DAT_00140ee0 = DAT_00140ee0 + 1;
        }
        else {
          uVar34 = 0;
        }
        goto LAB_001157c0;
      }
    }
    *(undefined1 *)(puVar2 + 0x15) = 1;
    if ((((iVar16 == 5) || ((*(uint *)(puVar2 + 5) & 0xf000) == 0x8000)) &&
        ((DAT_00141291 & 1) != 0)) && (uVar24 = FUN_0010aca0(0x15), (uVar24 & 1) != 0)) {
      piVar28 = __errno_location();
      lVar35 = DAT_00141550;
      lVar39 = puVar2[3];
      *piVar28 = 0x5f;
      if (lVar39 != lVar35) {
        DAT_00141550 = lVar39;
      }
      *(undefined1 *)(puVar2 + 0x16) = 0;
    }
    if ((DAT_00140f2c == 0) || (local_328 = &DAT_00141000, (DAT_0014101c & 1) != 0)) {
      local_328 = &DAT_00141000;
      lVar35 = puVar2[3];
      if (lVar35 != DAT_00141558) {
        puVar19 = puVar2 + 0x14;
        if ((uVar33 & 1) == 0) {
          uVar34 = lgetfilecon(pcVar17,puVar19);
          iVar16 = FUN_0010cfd4(uVar34,puVar19);
          piVar28 = __errno_location();
          lVar35 = puVar2[3];
          if (iVar16 < 0) goto LAB_00115de0;
LAB_0011597c:
          lVar39 = DAT_00141560;
          iVar16 = strcmp("unlabeled",(char *)puVar2[0x14]);
          local_320 = (uint)(iVar16 != 0);
          if (lVar39 != lVar35) {
            *piVar28 = 0;
            goto LAB_001159ac;
          }
          *piVar28 = 0x5f;
          uVar33 = 0;
          uVar29 = 0;
          local_330 = (uint *)((ulong)local_330 & 0xffffffff00000000);
          uVar15 = local_320;
          puVar41 = local_330;
          uVar12 = local_320;
          goto joined_r0x00116130;
        }
        uVar34 = getfilecon();
        iVar16 = FUN_0010cfd4(uVar34,puVar19);
        piVar28 = __errno_location();
        lVar35 = puVar2[3];
        if (-1 < iVar16) goto LAB_0011597c;
LAB_00115de0:
        iVar16 = *piVar28;
        uVar33 = (uint)(iVar16 == 0x5f || iVar16 == 0x3d);
        if ((iVar16 - 0x16U & 0xffffffef) == 0 || iVar16 == 0x5f) {
          DAT_00141558 = lVar35;
        }
        puVar2[0x14] = &DAT_001400c8;
        if (DAT_00141560 != lVar35) {
          *piVar28 = 0;
          local_330 = (uint *)(CONCAT44(local_330._4_4_,uVar33) ^ 1);
          if ((*(uint *)(local_318 + 2) & 0xf000) != 0xa000) {
            local_320 = 0;
LAB_001159c4:
            local_338 = &local_2f8;
            puVar36 = (uint *)0x0;
            sVar22 = 0x98;
            puVar41 = local_338;
LAB_00115a44:
            puVar19 = (undefined8 *)listxattr(pcVar17,(char *)puVar41,sVar22);
            if ((long)puVar19 < 0) {
              iVar16 = *piVar28;
              if (iVar16 == 0x22) {
                free(puVar36);
                sVar23 = listxattr(pcVar17,(char *)0x0,0);
                if (0 < (long)sVar23) {
                  bVar1 = false;
                  uVar24 = sVar22 + ((long)sVar22 >> 1);
                  if (((long)uVar24 < 0) || (uVar24 < (ulong)((long)sVar22 >> 1))) {
                    bVar1 = true;
                  }
                  sVar22 = uVar24;
                  if ((long)uVar24 < (long)sVar23) {
                    sVar22 = sVar23;
                  }
                  if (!bVar1) goto code_r0x00115a30;
                  *piVar28 = 0xc;
                  uVar33 = 1;
                  if ((uint)local_330 == 0) {
                    uVar33 = (uint)(DAT_00140f2c == 0);
                  }
                  goto LAB_0011646c;
                }
                uVar12 = (uint)sVar23;
                goto LAB_00115b98;
              }
              uVar12 = (uint)puVar19;
              local_318 = puVar19;
              free(puVar36);
              if ((int)local_318 < 0) goto LAB_001167d0;
              goto LAB_00115b98;
            }
            if (puVar19 != (undefined8 *)0x0) {
              puVar3 = (uint *)((long)puVar41 + (long)puVar19);
              __s = puVar41;
              if (puVar41 < puVar3) {
                do {
                  pcVar32 = "system.nfs4_acl";
                  if ((char)*__s == 's') {
                    while( true ) {
                      pcVar32 = pcVar32 + 1;
                      __s = (uint *)((long)__s + 1);
                      if (*(char *)__s != *pcVar32) break;
                      if (*(char *)__s == '\0') {
                        free(puVar36);
                        sVar20 = getxattr(pcVar17,"system.nfs4_acl",local_338,0x98);
                        iVar16 = (int)sVar20;
                        if (iVar16 < 0) {
                          iVar16 = *piVar28;
                          if (iVar16 == 0x22) goto LAB_00115ba0;
                          if (iVar16 == 0x3d) goto LAB_001164d8;
                          goto LAB_001167d0;
                        }
                        if (iVar16 < 4) goto LAB_0011643c;
                        uVar33 = (local_2f8 & 0xff00ff00) >> 8 | (local_2f8 & 0xff00ff) << 8;
                        uVar33 = uVar33 >> 0x10 | uVar33 << 0x10;
                        if (6 < uVar33) {
                          *piVar28 = 0;
                          goto LAB_00115ba0;
                        }
                        if (local_2f8 == 0) {
                          *piVar28 = 0;
                          uVar12 = 0;
                          iVar16 = *piVar28;
                          goto LAB_0011670c;
                        }
                        lVar35 = (long)iVar16 + -0x14;
                        if (lVar35 < 0) goto LAB_0011643c;
                        puVar41 = local_2f4;
                        uVar15 = 0;
                        uVar29 = 0;
                        goto LAB_00115b28;
                      }
                    }
                  }
                  local_340 = __s;
                  sVar22 = strlen((char *)__s);
                  __s = (uint *)((long)local_340 + sVar22 + 1);
                  __s_00 = puVar41;
                } while (__s < puVar3);
                do {
                  pcVar32 = "system.posix_acl_access";
                  if ((char)*__s_00 == 's') {
                    while( true ) {
                      pcVar32 = pcVar32 + 1;
                      __s_00 = (uint *)((long)__s_00 + 1);
                      if (*(char *)__s_00 != *pcVar32) break;
                      if (*(char *)__s_00 == '\0') goto LAB_0011655c;
                    }
                  }
                  local_338 = __s_00;
                  sVar22 = strlen((char *)__s_00);
                  __s_00 = (uint *)((long)local_338 + sVar22 + 1);
                } while (__s_00 < puVar3);
                if ((*(uint *)(local_318 + 2) & 0xf000) == 0x4000) {
                  do {
                    pcVar32 = "system.posix_acl_default";
                    if ((char)*puVar41 == 's') {
                      while( true ) {
                        pcVar32 = pcVar32 + 1;
                        puVar41 = (uint *)((long)puVar41 + 1);
                        if (*(char *)puVar41 != *pcVar32) break;
                        if (*(char *)puVar41 == '\0') goto LAB_0011655c;
                      }
                    }
                    sVar22 = strlen((char *)puVar41);
                    puVar41 = (uint *)((long)puVar41 + sVar22 + 1);
                  } while (puVar41 < puVar3);
                }
              }
              free(puVar36);
              iVar16 = *piVar28;
              uVar12 = 0;
              goto LAB_0011670c;
            }
            uVar12 = 0;
            free(puVar36);
            goto LAB_0011677c;
          }
          local_320 = 0;
LAB_001164d8:
          if ((uint)local_330 != 0) goto LAB_001164e4;
          goto LAB_00116568;
        }
        *piVar28 = 0x5f;
        if (uVar33 != 0) goto LAB_001168cc;
        *(undefined4 *)((long)puVar2 + 0xac) = 0;
        goto LAB_00116288;
      }
      piVar28 = __errno_location();
      lVar39 = DAT_00141560;
      puVar2[0x14] = &DAT_001400c8;
      if (lVar39 != lVar35) {
        *piVar28 = 0;
        local_320 = 0;
LAB_001159ac:
        local_330 = (uint *)((ulong)local_330 & 0xffffffff00000000);
        if ((*(uint *)(local_318 + 2) & 0xf000) != 0xa000) goto LAB_001159c4;
LAB_00116568:
        uVar33 = 0;
        uVar29 = 0;
        local_330 = (uint *)((ulong)local_330 & 0xffffffff00000000);
        uVar15 = local_320;
        goto LAB_00115bc0;
      }
      *piVar28 = 0x5f;
LAB_001168cc:
      *(undefined4 *)((long)puVar2 + 0xac) = 0;
      goto LAB_00115bf4;
    }
    uVar33 = *(uint *)(puVar2 + 5) & 0xf000;
    if (uVar33 == 0xa000) goto LAB_00116144;
    goto LAB_001155e8;
  }
  uVar12 = (uint)DAT_001413b2;
  uVar33 = uVar12 & 1;
  if ((DAT_001413b2 & 1) != 0) {
    cVar37 = *param_1;
    if ((cVar37 != '/') && (cVar40 = *param_4, cVar40 != '\0')) {
LAB_00115ea8:
      local_318 = (undefined8 *)CONCAT44(local_318._4_4_,uVar33);
      sVar22 = strlen(param_1);
      sVar23 = strlen(param_4);
      uVar24 = sVar22 + sVar23 + 0x11;
      puVar7 = auStack_350;
      while (puVar11 != auStack_350 + -(uVar24 & 0xffffffffffff0000)) {
        puVar10 = puVar7 + -0x10000;
        *(undefined8 *)(puVar7 + -0xfc00) = 0;
        puVar11 = puVar7 + -0x10000;
        puVar7 = puVar7 + -0x10000;
      }
      uVar24 = uVar24 & 0xfff0;
      lVar35 = -uVar24;
      *(undefined8 *)(puVar10 + lVar35) = 0;
      if (0x3ff < uVar24) {
        *(undefined8 *)(puVar10 + lVar35 + 0x400) = 0;
      }
      pcVar17 = puVar10 + lVar35 + 0x10;
      pcVar26 = param_4;
      pcVar32 = pcVar17;
      pcVar8 = param_1;
      if ((cVar40 != '.') || (param_4[1] != '\0')) {
        do {
          pcVar31 = pcVar32;
          pcVar25 = pcVar26;
          pcVar32 = pcVar31 + 1;
          *pcVar31 = cVar40;
          pcVar26 = pcVar25 + 1;
          cVar40 = *pcVar26;
        } while (cVar40 != '\0');
        if ((param_4 < pcVar26) && (*pcVar25 != '/')) {
          *pcVar32 = '/';
          pcVar32 = pcVar31 + 2;
        }
      }
      while (cVar37 != '\0') {
        *pcVar32 = cVar37;
        cVar37 = pcVar8[1];
        pcVar32 = pcVar32 + 1;
        pcVar8 = pcVar8 + 1;
      }
      *pcVar32 = '\0';
      uVar33 = (uint)local_318;
      goto LAB_0011553c;
    }
    goto LAB_00115d24;
  }
  if ((DAT_00141441 & 1) != 0) {
LAB_00115500:
    cVar37 = *param_1;
    if (cVar37 != '/') {
      cVar40 = *param_4;
joined_r0x00116818:
      if (cVar40 != '\0') goto LAB_00115ea8;
    }
    goto LAB_00115540;
  }
  if (iVar16 == 3) {
    if ((DAT_00141291 & 1) == 0) {
LAB_00116618:
      if ((DAT_00140f30 & 1) == 0) goto LAB_00116624;
    }
    else {
      local_318 = (undefined8 *)(CONCAT44(local_318._4_4_,uVar12) & 0xffffffff00000001);
      uVar24 = FUN_0010aca0(0x13);
      uVar33 = (uint)local_318;
      if ((uVar24 & 1) == 0) {
        uVar24 = FUN_0010aca0(0x12);
        uVar33 = (uint)local_318;
        if ((uVar24 & 1) == 0) {
          uVar24 = FUN_0010aca0(0x14);
          uVar33 = (uint)local_318;
          if ((uVar24 & 1) == 0) goto LAB_00116618;
        }
      }
    }
    goto LAB_00115500;
  }
  if ((DAT_00140f30 & 1) != 0) {
    if ((0x41UL >> (param_2 & 0x3f) & 1) == 0) goto LAB_00115500;
LAB_00115fc4:
    if (DAT_0014142c != 4) {
      if ((((DAT_00141292 & 1) == 0) && ((DAT_00141440 & 1) == 0)) && ((DAT_00140f30 & 1) == 0)) {
        if ((DAT_00141442 & 1) == 0) goto LAB_00116768;
        if (iVar16 != 0) goto LAB_00116000;
      }
      goto LAB_00115500;
    }
    cVar37 = *param_1;
    if (cVar37 != '/') {
      cVar40 = *param_4;
      goto joined_r0x00116818;
    }
    uVar13 = FUN_0010aa54();
    goto LAB_0011580c;
  }
  if ((DAT_00141442 & 1) != 0) {
    if ((0x41UL >> (param_2 & 0x3f) & 1) != 0) goto LAB_00115fc4;
LAB_00116000:
    if (iVar16 == 5) {
      if (DAT_00140f80 != 3) {
        local_318 = (undefined8 *)(CONCAT44(local_318._4_4_,uVar12) & 0xffffffff00000001);
        if ((DAT_00141291 & 1) == 0) goto LAB_00116624;
        uVar24 = FUN_0010aca0(0xe);
        uVar33 = (uint)local_318;
        if ((uVar24 & 1) == 0) {
          uVar24 = FUN_0010aca0(0x10);
          uVar33 = (uint)local_318;
          if ((uVar24 & 1) == 0) {
            uVar24 = FUN_0010aca0(0x11);
            uVar33 = (uint)local_318;
            if ((uVar24 & 1) == 0) {
              uVar24 = FUN_0010aca0(0x15);
              if ((uVar24 & 1) == 0) goto LAB_00116624;
              uVar33 = (uint)local_318;
            }
          }
        }
      }
      goto LAB_00115500;
    }
LAB_00116624:
    uVar34 = 0;
    goto LAB_001157a4;
  }
LAB_00116768:
  uVar34 = 0;
  goto LAB_001157a8;
LAB_0011655c:
  free(puVar36);
LAB_00115ba0:
  if ((uint)local_330 == 0) {
    if (DAT_00140f2c == 0) {
      uVar29 = 1;
      uVar33 = 0;
      uVar15 = 1;
    }
    else {
LAB_00116648:
      uVar33 = 0;
      uVar29 = 0;
      uVar15 = local_320;
    }
  }
  else {
LAB_001164e4:
    uVar33 = 1;
    uVar29 = 0;
    local_330 = (uint *)((ulong)local_330 & 0xffffffff00000000);
    uVar15 = local_320;
  }
  goto LAB_00115bc0;
code_r0x00115a30:
  puVar36 = malloc(sVar22);
  puVar41 = puVar36;
  if (puVar36 == (uint *)0x0) goto LAB_00116898;
  goto LAB_00115a44;
LAB_00116898:
  iVar16 = *piVar28;
  uVar12 = 0xffffffff;
LAB_0011670c:
  if (iVar16 == 0x5f || (iVar16 - 0x16U & 0xffffffef) == 0) goto LAB_00116448;
  goto LAB_00116458;
LAB_001167d0:
  if (iVar16 == 0x26) {
LAB_001167fc:
    uVar12 = 0;
    goto LAB_00116448;
  }
  if (0x26 < iVar16) {
    if (iVar16 == 0x5f) goto LAB_001167fc;
LAB_001167ec:
    uVar12 = 0xffffffff;
    goto LAB_0011670c;
  }
  if (iVar16 != 0x10) {
    if (iVar16 == 0x16) goto LAB_001167fc;
    goto LAB_001167ec;
  }
  if ((uint)local_330 != 0) goto LAB_001164e4;
  if (DAT_00140f2c != 0) goto LAB_00116648;
  uVar12 = 0;
  uVar33 = 0;
  goto LAB_00116468;
code_r0x00115cac:
  sVar22 = 0x7fffffffffffffff;
LAB_00115cb0:
  puVar36 = malloc(sVar22);
  puVar41 = puVar36;
  if (puVar36 != (uint *)0x0) goto LAB_00115c70;
LAB_001166a4:
  piVar28 = __errno_location();
  *piVar28 = 0xc;
LAB_001162c0:
  puVar2[1] = 0;
  uVar34 = dcgettext(0,"cannot read symbolic link %s",5);
  FUN_0010ad30(uVar4,uVar34,pcVar17);
  if (puVar2[1] != 0) {
LAB_001162f0:
    if (*(int *)((long)puVar2 + 0xb4) == 0) {
      uVar24 = FUN_0010ae30();
      if ((uVar24 & 1) != 0) {
        *(undefined4 *)((long)puVar2 + 0xb4) = 0xffffffff;
      }
      if (puVar2[1] == 0) goto LAB_00116344;
    }
    if (((1 < DAT_00140f80) || ((DAT_00141440 & 1) != 0)) &&
       (iVar16 = FUN_0010ab50(0xffffff9c,pcVar17,&local_2f8,0,2), iVar16 == 0)) {
      *(undefined4 *)((long)puVar2 + 0x9c) = local_2e8;
      *(undefined1 *)((long)puVar2 + 0xa9) = 1;
    }
  }
LAB_00116344:
  uVar33 = *(uint *)(puVar2 + 5) & 0xf000;
  if (uVar33 != 0xa000) goto LAB_001155e8;
  uVar13 = 6;
  goto LAB_001155f4;
  while( true ) {
    if (uVar5 == 0x6000000) {
      if ((*puVar36 != 0x454e574f) || ((short)puVar41[5] != 0x4052)) {
        if ((*puVar36 != 0x554f5247) || ((short)puVar41[5] != 0x4050)) goto LAB_00115b8c;
        uVar30 = uVar30 | 2;
      }
    }
    else {
      if (((uVar5 != 0x9000000) || (*(long *)puVar36 != 0x454e4f5952455645)) ||
         ((char)puVar41[6] != '@')) goto LAB_00115b8c;
      uVar30 = uVar30 | 4;
    }
    uVar5 = 1 << (ulong)(uVar30 & 0x1f);
    if ((uVar5 & uVar29) != 0) goto LAB_00115b8c;
    uVar15 = uVar15 + 1;
    uVar29 = uVar29 | uVar5;
    puVar41 = puVar36 + uVar12;
    uVar12 = 0;
    if (uVar33 <= uVar15) goto LAB_00115b90;
    lVar35 = lVar35 + -0x10;
    if (lVar35 < 0) break;
LAB_00115b28:
    uVar5 = puVar41[3];
    puVar36 = puVar41 + 4;
    uVar12 = (uVar5 & 0xff00ff00) >> 8 | (uVar5 & 0xff00ff) << 8;
    uVar30 = (*puVar41 & 0xff00ff00) >> 8 | (*puVar41 & 0xff00ff) << 8;
    uVar30 = uVar30 >> 0x10 | uVar30 << 0x10;
    uVar12 = (uVar12 >> 0x10 | uVar12 << 0x10) >> 2;
    if ((uVar5 & 0x3000000) != 0) {
      uVar12 = uVar12 + 1;
    }
    uVar6 = (puVar41[1] & 0xff00ff00) >> 8 | (puVar41[1] & 0xff00ff) << 8;
    if ((1 < uVar30) || ((uVar6 >> 0x10 & 0xffffffbf) != 0 || (uVar6 & 0xffff) != 0)) {
LAB_00115b8c:
      uVar12 = 1;
LAB_00115b90:
      *piVar28 = 0;
LAB_00115b98:
      if (0 < (int)uVar12) goto LAB_00115ba0;
LAB_0011677c:
      iVar16 = *piVar28;
      goto LAB_0011670c;
    }
    lVar35 = lVar35 + (ulong)uVar12 * -4;
    if (lVar35 < 0) break;
  }
LAB_0011643c:
  uVar12 = 0xffffffff;
  *piVar28 = 0x16;
LAB_00116448:
  DAT_00141560 = puVar2[3];
LAB_00116458:
  uVar33 = 1;
  if (((uint)local_330 == 0) && (uVar33 = 0, DAT_00140f2c == 0)) {
    uVar33 = uVar12 >> 0x1f;
  }
LAB_00116468:
  if (uVar12 == 0) {
    local_330 = (uint *)((ulong)local_330 & 0xffffffff00000000);
    uVar29 = 0;
    uVar15 = local_320;
  }
  else {
LAB_0011646c:
    uVar29 = 0;
    uVar12 = (uint)(*piVar28 == 0xd || *piVar28 == 2);
    local_330 = (uint *)CONCAT44(local_330._4_4_,uVar12);
    uVar33 = uVar33 & (uVar12 ^ 1);
    uVar15 = local_320;
  }
LAB_00115bc0:
  uVar12 = uVar15 & 1;
  puVar41 = local_330;
joined_r0x00116130:
  if (uVar12 == 0) {
    local_330._0_4_ = (uint)puVar41;
    uVar15 = (uint)local_330;
  }
  else {
    local_330._0_4_ = 3 - (local_320 & (uVar29 ^ 1));
  }
  *(uint *)((long)puVar2 + 0xac) = (uint)local_330;
  DAT_00140ef1 = (byte)uVar15 | DAT_00140ef1;
  local_330 = puVar41;
  if (uVar33 != 0) {
LAB_00116288:
    piVar28 = __errno_location();
    iVar16 = *piVar28;
    uVar34 = FUN_001129a0(pcVar17);
    error(0,iVar16,"%s",uVar34);
  }
LAB_00115bf4:
  uVar33 = *(uint *)(puVar2 + 5) & 0xf000;
  if (uVar33 == 0xa000) {
    if (DAT_00140f2c == 0) {
LAB_00115c0c:
      uVar24 = puVar2[9];
      sVar22 = 0x80;
      if (uVar24 != 0) {
        uVar38 = uVar24;
        if (0x400 < uVar24) {
          uVar38 = 0x400;
        }
        sVar22 = uVar38 + 1;
      }
      local_330 = &local_2f8;
      local_318 = (undefined8 *)CONCAT44(local_318._4_4_,(uint)(uVar24 != 0));
      do {
        if (sVar22 != 0x80 || (uint)local_318 != 0) goto LAB_00115cb0;
        sVar22 = 0x80;
        puVar36 = (uint *)0x0;
        puVar41 = local_330;
LAB_00115c70:
        uVar24 = __readlink_chk(pcVar17,puVar41,sVar22,sVar22);
        if ((long)uVar24 < 0) {
          free(puVar36);
          goto LAB_001162c0;
        }
        if (uVar24 < sVar22) {
          *(undefined1 *)((long)puVar41 + uVar24) = 0;
          sVar23 = uVar24 + 1;
          if (puVar36 == (uint *)0x0) {
            pvVar27 = malloc(sVar23);
            if (pvVar27 == (void *)0x0) goto LAB_001162c0;
            uVar34 = __memcpy_chk(pvVar27,puVar41,sVar23,sVar23);
            puVar2[1] = uVar34;
          }
          else if ((sVar23 < sVar22) && (pvVar27 = realloc(puVar36,sVar23), pvVar27 != (void *)0x0))
          {
            puVar2[1] = pvVar27;
          }
          else {
            puVar2[1] = puVar36;
          }
          goto LAB_001162f0;
        }
        free(puVar36);
        if (0x3fffffffffffffff < sVar22) {
          if (sVar22 != 0x7fffffffffffffff) goto code_r0x00115cac;
          goto LAB_001166a4;
        }
        sVar22 = sVar22 << 1;
      } while( true );
    }
LAB_00116144:
    if ((DAT_00141440 & 1) != 0) goto LAB_00115c0c;
    uVar13 = 6;
  }
  else {
LAB_001155e8:
    uVar13 = 5;
    if (((uVar33 == 0x4000) && (uVar13 = 3, local_31c != 0)) &&
       (uVar13 = 9, (DAT_00141428 & 1) != 0)) {
      uVar13 = 3;
    }
  }
LAB_001155f4:
  iVar16 = DAT_00140f2c;
  *(undefined4 *)(puVar2 + 0x13) = uVar13;
  uVar34 = puVar2[0xb];
  if ((iVar16 == 0) || ((DAT_00140f28 & 1) != 0)) {
    pcVar17 = (char *)FUN_0010beb0(uVar34,&local_2f8,DAT_00141018,0x200,DAT_00141010);
    sVar22 = strlen(pcVar17);
    iVar16 = FUN_00112a50(pcVar17,sVar22);
    if (DAT_00140ef8 < iVar16) {
      DAT_00140ef8 = iVar16;
    }
    if (DAT_00140f2c != 0) goto LAB_00115610;
    if (((DAT_001400ca & 1) != 0) &&
       (iVar16 = FUN_0010e3f0(*(undefined4 *)(puVar2 + 6)), DAT_00140f00 < iVar16)) {
      DAT_00140f00 = iVar16;
    }
    if ((DAT_001400cb & 1) != 0) {
      uVar13 = *(undefined4 *)((long)puVar2 + 0x34);
      if (((DAT_001412c0 & 1) == 0) &&
         (pcVar17 = (char *)FUN_0010e474(uVar13), pcVar17 != (char *)0x0)) {
        sVar22 = strlen(pcVar17);
        iVar16 = FUN_00112a50(pcVar17,sVar22);
        if (iVar16 < 0) {
          iVar16 = 0;
        }
      }
      else {
        iVar16 = __snprintf_chk(0,0,2,0xffffffffffffffff,&DAT_0011bce0,uVar13);
      }
      if (DAT_00140f04 < iVar16) {
        DAT_00140f04 = iVar16;
      }
    }
    if (((DAT_00140f38 & 1) != 0) &&
       (iVar16 = FUN_0010e3f0(*(undefined4 *)(puVar2 + 6)), DAT_00140f08 < iVar16)) {
      DAT_00140f08 = iVar16;
    }
    if ((local_328[0x1c] & 1) != 0) {
      sVar22 = strlen((char *)puVar2[0x14]);
      iVar16 = (int)sVar22;
      if (iVar16 <= DAT_00140f0c) goto LAB_00115638;
      goto LAB_00115f8c;
    }
LAB_00115638:
    if (DAT_00140f2c == 0) {
      pcVar17 = local_2fd + 1;
      local_2fd[1] = 0;
      uVar24 = (ulong)*(uint *)((long)puVar2 + 0x2c);
      do {
        pcVar17 = pcVar17 + -1;
        *pcVar17 = (char)uVar24 + (char)(uVar24 / 10) * -10 + '0';
        bVar1 = 9 < uVar24;
        uVar24 = uVar24 / 10;
      } while (bVar1);
      sVar22 = strlen(pcVar17);
      if (DAT_00140efc < (int)sVar22) {
        DAT_00140efc = (int)sVar22;
      }
      if ((*(uint *)(puVar2 + 5) & 0xb000) == 0x2000) {
        uVar38 = puVar2[7];
        pcVar32 = local_2e4;
        local_2e4[0] = '\0';
        pcVar17 = pcVar32;
        uVar24 = (ulong)((uint)(uVar38 >> 0x20) & 0xfffff000 | (uint)uVar38 >> 8 & 0xfff);
        do {
          pcVar17 = pcVar17 + -1;
          *pcVar17 = (char)uVar24 + (char)(uVar24 / 10) * -10 + '0';
          bVar1 = 9 < uVar24;
          uVar24 = uVar24 / 10;
        } while (bVar1);
        sVar22 = strlen(pcVar17);
        if (DAT_00140f10 < (int)sVar22) {
          DAT_00140f10 = (int)sVar22;
        }
        iVar16 = DAT_00140f10;
        local_2e4[0] = '\0';
        uVar24 = (ulong)((uint)(uVar38 >> 0xc) & 0xffffff00 | (uint)uVar38 & 0xff);
        do {
          pcVar32 = pcVar32 + -1;
          *pcVar32 = (char)uVar24 + (char)(uVar24 / 10) * -10 + '0';
          bVar1 = 9 < uVar24;
          uVar24 = uVar24 / 10;
        } while (bVar1);
        sVar22 = strlen(pcVar32);
        if (DAT_00140f14 < (int)sVar22) {
          DAT_00140f14 = (int)sVar22;
        }
        iVar16 = iVar16 + 2 + DAT_00140f14;
        if (DAT_00140f18 < iVar16) {
          DAT_00140f18 = iVar16;
        }
      }
      else {
        pcVar17 = (char *)FUN_0010beb0(puVar2[9],&local_2f8,DAT_001412d0,1,DAT_001400d0);
        sVar22 = strlen(pcVar17);
        iVar16 = FUN_00112a50(pcVar17,sVar22);
        if (DAT_00140f18 < iVar16) {
          DAT_00140f18 = iVar16;
        }
      }
    }
  }
  else {
LAB_00115610:
    if ((local_328[0x1c] & 1) != 0) {
      sVar22 = strlen((char *)puVar2[0x14]);
      iVar16 = (int)sVar22;
      if (DAT_00140f0c < iVar16) {
LAB_00115f8c:
        DAT_00140f0c = iVar16;
      }
      goto LAB_00115638;
    }
  }
LAB_001157a4:
  if ((DAT_00140f30 & 1) != 0) {
    pcVar17 = local_2e4;
    local_2e4[0] = '\0';
    uVar24 = puVar2[4];
    do {
      pcVar17 = pcVar17 + -1;
      *pcVar17 = (char)uVar24 + (char)(uVar24 / 10) * -10 + '0';
      bVar1 = 9 < uVar24;
      uVar24 = uVar24 / 10;
    } while (bVar1);
    sVar22 = strlen(pcVar17);
    if (DAT_00140ef4 < (int)sVar22) {
      DAT_00140ef4 = (int)sVar22;
    }
  }
LAB_001157a8:
  uVar18 = FUN_0010f784(param_1);
  *puVar2 = uVar18;
  DAT_00140ee0 = DAT_00140ee0 + 1;
LAB_001157c0:
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return uVar34;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

