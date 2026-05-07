
void FUN_0010e560(long param_1)

{
  bool bVar1;
  ulong *puVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  bool bVar7;
  byte bVar8;
  int iVar9;
  int iVar10;
  ulong uVar11;
  char *pcVar12;
  size_t sVar13;
  long lVar14;
  undefined1 *puVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  undefined1 uVar18;
  undefined1 uVar19;
  _IO_FILE *p_Var20;
  ulong uVar21;
  undefined *puVar22;
  undefined1 uVar23;
  undefined1 uVar24;
  uint uVar25;
  byte *pbVar26;
  undefined1 uVar27;
  undefined1 uVar28;
  char *pcVar29;
  uint uVar30;
  ulong uVar31;
  ulong uVar32;
  long lVar33;
  char *pcVar34;
  char *pcVar35;
  char *pcVar36;
  undefined8 local_1348;
  ulong local_1340;
  ulong uStack_1338;
  undefined1 auStack_1330 [16];
  int local_1320;
  undefined1 auStack_12f8 [16];
  int local_12e8;
  char local_12c0;
  undefined8 local_12bf;
  undefined1 local_12b7;
  undefined2 uStack_12b6;
  char local_129d [5];
  undefined1 auStack_1298 [18];
  char local_1286 [790];
  undefined8 local_f70;
  char local_ea8 [3648];
  long local_68;
  
  local_f70 = 0;
  bVar8 = *(byte *)(param_1 + 0xa8);
  local_68 = *(long *)PTR___stack_chk_guard_0013ffd0;
  if ((bVar8 & 1) == 0) {
    local_12c0 = "?pcdb-lswd"[*(uint *)(param_1 + 0x98)];
    local_12bf = 0x3f3f3f3f3f3f3f3f;
    _local_12b7 = 0x3f3f;
    if ((DAT_00140ef1 & 1) == 0) goto LAB_0010e750;
LAB_0010e6ec:
    iVar9 = *(int *)(param_1 + 0xac);
    if (iVar9 == 2) {
      _local_12b7 = CONCAT11(0x2e,local_12b7);
      _local_12b7 = (uint3)_local_12b7;
    }
    else if (iVar9 == 3) {
      _local_12b7 = CONCAT11(0x2b,local_12b7);
      _local_12b7 = (uint3)_local_12b7;
    }
    else if (iVar9 == 1) {
      _local_12b7 = CONCAT11(0x3f,local_12b7);
      _local_12b7 = (uint3)_local_12b7;
    }
  }
  else {
    uVar30 = *(uint *)(param_1 + 0x28);
    local_12c0 = '-';
    uVar25 = uVar30 & 0xf000;
    if (((((uVar25 != 0x8000) && (local_12c0 = 'd', uVar25 != 0x4000)) &&
         (local_12c0 = 'b', uVar25 != 0x6000)) &&
        ((local_12c0 = 'c', uVar25 != 0x2000 && (local_12c0 = 'l', uVar25 != 0xa000)))) &&
       ((local_12c0 = 'p', uVar25 != 0x1000 && (local_12c0 = 's', uVar25 != 0xc000)))) {
      local_12c0 = '?';
    }
    uVar16 = 0x2d;
    uVar19 = uVar16;
    if ((uVar30 & 0x100) != 0) {
      uVar19 = 0x72;
    }
    if ((uVar30 & 0x80) != 0) {
      uVar16 = 0x77;
    }
    if ((uVar30 >> 0xb & 1) == 0) {
      uVar23 = 0x2d;
      if ((uVar30 & 0x40) != 0) {
        uVar23 = 0x78;
      }
    }
    else {
      uVar23 = 0x53;
      if ((uVar30 & 0x40) != 0) {
        uVar23 = 0x73;
      }
    }
    uVar17 = 0x2d;
    uVar27 = uVar17;
    if ((uVar30 & 0x20) != 0) {
      uVar27 = 0x72;
    }
    if ((uVar30 & 0x10) != 0) {
      uVar17 = 0x77;
    }
    if ((uVar30 >> 10 & 1) == 0) {
      uVar24 = 0x2d;
      if ((uVar30 & 8) != 0) {
        uVar24 = 0x78;
      }
    }
    else {
      uVar24 = 0x53;
      if ((uVar30 & 8) != 0) {
        uVar24 = 0x73;
      }
    }
    uVar18 = 0x2d;
    uVar28 = uVar18;
    if ((uVar30 & 4) != 0) {
      uVar28 = 0x72;
    }
    if ((uVar30 & 2) != 0) {
      uVar18 = 0x77;
    }
    local_12bf = CONCAT17(uVar18,CONCAT16(uVar28,CONCAT15(uVar24,CONCAT14(uVar17,CONCAT13(uVar27,
                                                  CONCAT12(uVar23,CONCAT11(uVar16,uVar19)))))));
    if ((uVar30 >> 9 & 1) == 0) {
      uVar19 = 0x2d;
      if ((uVar30 & 1) != 0) {
        uVar19 = 0x78;
      }
    }
    else {
      uVar19 = 0x54;
      if ((uVar30 & 1) != 0) {
        uVar19 = 0x74;
      }
    }
    _local_12b7 = CONCAT21(0x20,uVar19);
    if ((DAT_00140ef1 & 1) != 0) goto LAB_0010e6ec;
LAB_0010e750:
    _local_12b7 = _local_12b7 & 0xff;
  }
  if (DAT_00140f34 == 2) {
    uStack_1338 = *(ulong *)(param_1 + 0x68);
    local_1340 = *(ulong *)(param_1 + 0x60);
LAB_0010e77c:
    bVar7 = true;
  }
  else {
    if (DAT_00140f34 < 3) {
      puVar2 = (ulong *)(param_1 + 0x70);
      if (DAT_00140f34 != 0) {
        puVar2 = (ulong *)(param_1 + 0x80);
      }
      uStack_1338 = puVar2[1];
      local_1340 = *puVar2;
      goto LAB_0010e77c;
    }
    local_1340 = *(ulong *)(param_1 + 0x70);
    uStack_1338 = *(ulong *)(param_1 + 0x78);
    bVar7 = (local_1340 & uStack_1338) != 0xffffffffffffffff;
  }
  if ((DAT_00140f30 & 1) == 0) {
    pcVar29 = local_ea8;
    uVar31 = 0xe3b;
    uVar11 = uVar31;
  }
  else {
    if ((bVar8 & 1) == 0) {
      pcVar29 = "?";
    }
    else {
      pcVar29 = "?";
      if (*(ulong *)(param_1 + 0x20) != 0) {
        pcVar29 = local_1286 + 2;
        local_1286[2] = 0;
        uVar31 = *(ulong *)(param_1 + 0x20);
        do {
          pcVar29 = pcVar29 + -1;
          *pcVar29 = (char)uVar31 + (char)(uVar31 / 10) * -10 + '0';
          bVar1 = 9 < uVar31;
          uVar31 = uVar31 / 10;
        } while (bVar1);
      }
    }
    iVar9 = __sprintf_chk(local_ea8,2,0xe3b,&DAT_0011bcf0,DAT_00140ef4,pcVar29);
    uVar11 = (ulong)iVar9;
    pcVar29 = local_ea8 + uVar11;
    uVar31 = uVar11;
    if (uVar11 < 0xe3b) {
      uVar31 = 0xe3b;
    }
    bVar8 = *(byte *)(param_1 + 0xa8);
    uVar31 = uVar31 - uVar11;
    uVar11 = uVar31;
    if (uVar31 < 0xe3b) {
      uVar11 = 0xe3b;
    }
  }
  bVar8 = bVar8 & 1;
  if ((DAT_00140f28 & 1) != 0) {
    if (bVar8 == 0) {
      pcVar12 = "?";
      sVar13 = 1;
    }
    else {
      pcVar12 = (char *)FUN_0010beb0(*(undefined8 *)(param_1 + 0x58),auStack_1298,DAT_00141018,0x200
                                     ,DAT_00141010);
      sVar13 = strlen(pcVar12);
    }
    iVar9 = DAT_00140ef8;
    iVar10 = FUN_00112a50(pcVar12,sVar13);
    pcVar34 = pcVar29;
    if (0 < iVar9 - iVar10) {
      pcVar35 = pcVar29;
      do {
        uVar11 = uVar31;
        if (uVar31 < 0xe3b) {
          uVar11 = 0xe3b;
        }
        pcVar36 = pcVar35 + 1;
        *pcVar35 = ' ';
        uVar32 = (uVar11 - uVar31) + 1;
        if (uVar32 < uVar11) {
          uVar32 = uVar11;
        }
        uVar31 = (uVar32 - uVar11) + (uVar31 - 1);
        pcVar34 = pcVar29 + (uint)(iVar9 - iVar10);
        pcVar35 = pcVar36;
      } while (pcVar36 != pcVar29 + (uint)(iVar9 - iVar10));
    }
    do {
      pcVar35 = pcVar34;
      uVar11 = uVar31;
      if (uVar31 < 0xe3b) {
        uVar11 = 0xe3b;
      }
      cVar4 = *pcVar12;
      uVar32 = (uVar11 - uVar31) + 1;
      pcVar29 = pcVar35 + 1;
      *pcVar35 = cVar4;
      if (uVar32 < uVar11) {
        uVar32 = uVar11;
      }
      uVar31 = (uVar32 - uVar11) + (uVar31 - 1);
      pcVar34 = pcVar29;
      pcVar12 = pcVar12 + 1;
    } while (cVar4 != '\0');
    *pcVar35 = ' ';
    uVar11 = uVar31;
    if (uVar31 < 0xe3b) {
      uVar11 = 0xe3b;
    }
    bVar8 = *(byte *)(param_1 + 0xa8) & 1;
  }
  pcVar12 = "?";
  if (bVar8 != 0) {
    pcVar12 = local_1286 + 2;
    local_1286[2] = 0;
    uVar32 = (ulong)*(uint *)(param_1 + 0x2c);
    do {
      pcVar12 = pcVar12 + -1;
      *pcVar12 = (char)uVar32 + (char)(uVar32 / 10) * -10 + '0';
      bVar1 = 9 < uVar32;
      uVar32 = uVar32 / 10;
    } while (bVar1);
  }
  iVar9 = __sprintf_chk(pcVar29,2,uVar31,"%s %*s ",&local_12c0,DAT_00140efc,pcVar12);
  pcVar29 = pcVar29 + iVar9;
  if ((DAT_00141290 & 1) != 0) {
    FUN_00107430(&DAT_0011bd00,2);
  }
  if ((((DAT_001400ca & 1) == 0) && ((DAT_001400cb & 1) == 0)) &&
     (((DAT_00140f38 & 1) == 0 && ((DAT_0014101c & 1) == 0)))) {
    lVar14 = (long)iVar9 + uVar11;
    uVar32 = lVar14 - uVar31;
    if (uVar32 < uVar11) {
      uVar32 = uVar11;
    }
    uVar32 = uVar32 + (uVar31 - lVar14);
    uVar31 = uVar32;
    if (uVar32 < 0xe3b) {
      uVar31 = 0xe3b;
    }
  }
  else {
    FUN_00107430(local_ea8,(long)pcVar29 - (long)local_ea8);
    uVar5 = DAT_00140f00;
    if ((DAT_001400ca & 1) != 0) {
      uVar3 = *(undefined4 *)(param_1 + 0x30);
      if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
        puVar15 = &DAT_0011bce8;
      }
      else {
        puVar15 = (undefined1 *)0x0;
        if ((DAT_001412c0 & 1) == 0) {
          puVar15 = (undefined1 *)FUN_0010e300(uVar3);
        }
      }
      FUN_0010a040(puVar15,uVar3,uVar5);
    }
    uVar5 = DAT_00140f04;
    if ((DAT_001400cb & 1) != 0) {
      uVar3 = *(undefined4 *)(param_1 + 0x34);
      if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
        puVar15 = &DAT_0011bce8;
      }
      else {
        puVar15 = (undefined1 *)0x0;
        if ((DAT_001412c0 & 1) == 0) {
          puVar15 = (undefined1 *)FUN_0010e474(uVar3);
        }
      }
      FUN_0010a040(puVar15,uVar3,uVar5);
    }
    uVar5 = DAT_00140f08;
    if ((DAT_00140f38 & 1) != 0) {
      uVar3 = *(undefined4 *)(param_1 + 0x30);
      if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
        puVar15 = &DAT_0011bce8;
      }
      else {
        puVar15 = (undefined1 *)0x0;
        if ((DAT_001412c0 & 1) == 0) {
          puVar15 = (undefined1 *)FUN_0010e300(uVar3);
        }
      }
      FUN_0010a040(puVar15,uVar3,uVar5);
    }
    if ((DAT_0014101c & 1) != 0) {
      FUN_0010a040(*(undefined8 *)(param_1 + 0xa0),0,DAT_00140f0c);
    }
    uVar32 = 0xe3b;
    pcVar29 = local_ea8;
    uVar31 = 0xe3b;
  }
  if ((*(byte *)(param_1 + 0xa8) & 1) == 0) {
    pcVar12 = "?";
    sVar13 = 1;
LAB_0010ea18:
    iVar9 = DAT_00140f18;
    iVar10 = FUN_00112a50(pcVar12,sVar13);
    pcVar34 = pcVar29;
    if (0 < iVar9 - iVar10) {
      pcVar35 = pcVar29;
      do {
        uVar31 = uVar32;
        if (uVar32 < 0xe3b) {
          uVar31 = 0xe3b;
        }
        pcVar36 = pcVar35 + 1;
        *pcVar35 = ' ';
        uVar11 = (uVar31 - uVar32) + 1;
        if (uVar11 < uVar31) {
          uVar11 = uVar31;
        }
        uVar32 = (uVar11 - uVar31) + (uVar32 - 1);
        pcVar34 = pcVar29 + (uint)(iVar9 - iVar10);
        pcVar35 = pcVar36;
      } while (pcVar36 != pcVar29 + (uint)(iVar9 - iVar10));
    }
    do {
      pcVar29 = pcVar34;
      cVar4 = *pcVar12;
      uVar31 = uVar32;
      if (uVar32 < 0xe3b) {
        uVar31 = 0xe3b;
      }
      pcVar34 = pcVar29 + 1;
      *pcVar29 = cVar4;
      uVar11 = (uVar31 - uVar32) + 1;
      if (uVar11 < uVar31) {
        uVar11 = uVar31;
      }
      uVar32 = (uVar11 - uVar31) + (uVar32 - 1);
      pcVar12 = pcVar12 + 1;
    } while (cVar4 != '\0');
    *pcVar29 = ' ';
    *pcVar34 = '\x01';
    if ((bVar7 & *(byte *)(param_1 + 0xa8)) == 0) goto LAB_0010eac0;
LAB_0010efc8:
    uVar6 = DAT_001412d8;
    lVar14 = FUN_0010d394(DAT_001412d8,&local_1340,auStack_1330);
    if (lVar14 == 0) {
LAB_0010f0ec:
      if (*pcVar34 == '\0') goto LAB_0010f0b8;
      if (DAT_001400d8 < 0) goto LAB_0010eacc;
      goto LAB_0010eb4c;
    }
    uVar30 = (uint)((long)uStack_1338 < DAT_001412e8);
    uVar25 = (uint)(DAT_001412e8 < (long)uStack_1338);
    iVar9 = (uint)((long)uStack_1338 < DAT_001412e8) - (uint)(DAT_001412e8 < (long)uStack_1338);
    if ((int)(iVar9 + ((uint)((long)local_1340 < DAT_001412e0) -
                      (uint)(DAT_001412e0 < (long)local_1340)) * 2) < 0) {
      clock_gettime(0,(timespec *)&DAT_001412e0);
      uVar25 = (uint)(DAT_001412e8 < (long)uStack_1338);
      uVar30 = (uint)((long)uStack_1338 < DAT_001412e8);
      iVar9 = uVar30 - uVar25;
    }
    uVar25 = -((int)((uVar25 - uVar30) +
                     ((uint)(DAT_001412e0 < (long)local_1340) -
                     (uint)((long)local_1340 < DAT_001412e0)) * 2 &
                    iVar9 + ((uint)((long)local_1340 < DAT_001412e0 + -0xf0c2ac) -
                            (uint)(DAT_001412e0 + -0xf0c2ac < (long)local_1340)) * 2) >> 0x1f);
    if ((DAT_00140ed0 & 1) == 0) {
      puVar22 = (&PTR_DAT_001400e0)[uVar25];
    }
    else {
      lVar14 = 0xc;
      if (uVar25 == 0) {
        lVar14 = 0;
      }
      puVar22 = &DAT_001402d0 + (lVar14 + local_1320) * 0x80;
    }
    lVar14 = FUN_00113110(pcVar34,0x3e9,puVar22,auStack_1330,0,0,0xffffffff,uVar6,(int)uStack_1338);
    if (lVar14 == 0) goto LAB_0010f0ec;
    pcVar34 = pcVar34 + lVar14;
LAB_0010f0b8:
    pcVar29 = pcVar34 + 1;
    *pcVar34 = ' ';
  }
  else {
    if ((*(uint *)(param_1 + 0x28) & 0xb000) != 0x2000) {
      pcVar12 = (char *)FUN_0010beb0(*(undefined8 *)(param_1 + 0x48),auStack_1298,DAT_001412d0,1,
                                     DAT_001400d0);
      sVar13 = strlen(pcVar12);
      goto LAB_0010ea18;
    }
    uVar11 = *(ulong *)(param_1 + 0x38);
    pcVar12 = local_1286 + 2;
    iVar9 = DAT_00140f18 - (DAT_00140f10 + 2 + DAT_00140f14);
    local_1286[2] = 0;
    if (iVar9 < 0) {
      iVar9 = 0;
    }
    uVar21 = (ulong)((uint)(uVar11 >> 0x20) & 0xfffff000 | (uint)uVar11 >> 8 & 0xfff);
    do {
      pcVar12 = pcVar12 + -1;
      *pcVar12 = (char)uVar21 + (char)(uVar21 / 10) * -10 + '0';
      bVar1 = 9 < uVar21;
      uVar21 = uVar21 / 10;
    } while (bVar1);
    pcVar34 = local_129d + 1;
    local_129d[1] = 0;
    uVar11 = (ulong)((uint)(uVar11 >> 0xc) & 0xffffff00 | (uint)uVar11 & 0xff);
    do {
      pcVar34 = pcVar34 + -1;
      *pcVar34 = (char)uVar11 + (char)(uVar11 / 10) * -10 + '0';
      bVar1 = 9 < uVar11;
      uVar11 = uVar11 / 10;
    } while (bVar1);
    iVar9 = __sprintf_chk(pcVar29,2,uVar32,"%*s, %*s ",iVar9 + DAT_00140f10,pcVar12,DAT_00140f14);
    lVar14 = (long)iVar9 + uVar31;
    pcVar34 = pcVar29 + iVar9;
    uVar11 = lVar14 - uVar32;
    if (uVar11 < uVar31) {
      uVar11 = uVar31;
    }
    uVar32 = uVar11 + (uVar32 - lVar14);
    *pcVar34 = '\x01';
    if ((bVar7 & *(byte *)(param_1 + 0xa8)) != 0) goto LAB_0010efc8;
LAB_0010eac0:
    if (DAT_001400d8 < 0) {
LAB_0010eacc:
      uVar6 = DAT_001412d8;
      local_1348 = 0;
      lVar14 = FUN_0010d394(DAT_001412d8,&local_1348,auStack_12f8);
      if (lVar14 != 0) {
        puVar22 = PTR_DAT_001400e0;
        if ((DAT_00140ed0 & 1) != 0) {
          puVar22 = &DAT_001402d0 + (long)local_12e8 * 0x80;
        }
        lVar14 = FUN_00113110(auStack_1298,0x3e9,puVar22,auStack_12f8,0,0,0xffffffff,uVar6,0);
        if ((lVar14 != 0) && (DAT_001400d8 = FUN_00112a50(auStack_1298,lVar14), -1 < DAT_001400d8))
        goto LAB_0010eb4c;
      }
      DAT_001400d8 = 0;
LAB_0010eb4c:
      if ((bVar7 & *(byte *)(param_1 + 0xa8)) == 0) goto LAB_0010ecf4;
      local_1286[2] = 0;
      if ((long)local_1340 < 0) {
        uVar31 = local_1340;
        pcVar29 = local_1286 + 2;
        do {
          pcVar12 = pcVar29;
          uVar11 = (long)uVar31 / 10;
          pcVar12[-1] = '0' - ((char)uVar31 + (char)uVar11 * -10);
          uVar31 = uVar11;
          pcVar29 = pcVar12 + -1;
        } while (uVar11 != 0);
        pcVar29 = pcVar12 + -2;
        pcVar12[-2] = '-';
      }
      else {
        pcVar29 = local_1286 + 2;
        uVar31 = local_1340;
        do {
          uVar11 = (long)uVar31 / 10;
          pcVar29 = pcVar29 + -1;
          *pcVar29 = (char)uVar31 + (char)uVar11 * -10 + '0';
          uVar31 = uVar11;
        } while (uVar11 != 0);
      }
    }
    else {
LAB_0010ecf4:
      pcVar29 = "?";
    }
    iVar9 = __sprintf_chk(pcVar34,2,uVar32,&DAT_0011bcf0,DAT_001400d8,pcVar29);
    pcVar29 = pcVar34 + iVar9;
  }
  lVar33 = (long)pcVar29 - (long)local_ea8;
  FUN_00107430(local_ea8,lVar33);
  lVar14 = FUN_0010dc40(param_1,0,&DAT_001412f0,lVar33);
  if (*(int *)(param_1 + 0x98) == 6) {
    if (*(long *)(param_1 + 8) == 0) goto LAB_0010ed5c;
    FUN_00107430(&DAT_0011bd18,4);
    FUN_0010dc40(param_1,1,0,lVar14 + 4 + lVar33);
    if (DAT_00140f80 == 0) goto LAB_0010ed5c;
    bVar8 = FUN_0010af10(1,*(undefined4 *)(param_1 + 0x9c),0);
  }
  else {
    if (DAT_00140f80 == 0) goto LAB_0010ed5c;
    bVar8 = FUN_0010af10(*(undefined1 *)(param_1 + 0xa8),*(undefined4 *)(param_1 + 0x28));
  }
  if (bVar8 != 0) {
    p_Var20 = *(_IO_FILE **)PTR_stdout_0013ffc0;
    DAT_001402c0 = DAT_001402c0 + 1;
    pbVar26 = (byte *)p_Var20->_IO_write_ptr;
    if (pbVar26 < p_Var20->_IO_write_end) {
      p_Var20->_IO_write_ptr = (char *)(pbVar26 + 1);
      *pbVar26 = bVar8;
    }
    else {
      __overflow(p_Var20,(uint)bVar8);
    }
  }
LAB_0010ed5c:
  if (local_68 - *(long *)PTR___stack_chk_guard_0013ffd0 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_0013ffd0,0,
                   local_68 - *(long *)PTR___stack_chk_guard_0013ffd0);
}

