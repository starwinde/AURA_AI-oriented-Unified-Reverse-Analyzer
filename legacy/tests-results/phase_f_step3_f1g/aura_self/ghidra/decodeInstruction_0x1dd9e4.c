
undefined4
decodeInstruction(char *param_1,code *param_2,undefined8 param_3,long param_4,int param_5)

{
  ushort uVar1;
  ushort uVar2;
  bool bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  ulong uVar8;
  undefined1 *puVar9;
  byte bVar10;
  char cVar11;
  uint uVar12;
  undefined4 uVar13;
  long lVar14;
  char cVar15;
  code *pcVar16;
  long lVar17;
  char cVar18;
  uint uVar19;
  undefined1 *puVar20;
  byte local_6e;
  byte local_6d;
  ushort local_6c;
  ushort local_6a;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  local_6e = 0;
  param_1[0x35] = '\0';
  *(code **)(param_1 + 0x48) = param_2;
  *(undefined8 *)(param_1 + 0x50) = param_3;
  *(long *)(param_1 + 0x58) = param_4;
  *(int *)(param_1 + 0x60) = param_5;
  *(long *)(param_1 + 0x68) = param_4;
joined_r0x001dda40:
  if (param_5 == 2) {
    iVar5 = (*param_2)(param_3,&local_6e);
    if (iVar5 != 0) goto LAB_001dda54;
    param_4 = *(long *)(param_1 + 0x58);
    lVar17 = param_4 + 1;
    *(long *)(param_1 + 0x58) = lVar17;
    if ((local_6e & 0xf0) == 0x40) {
      while( true ) {
        iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6e,lVar17);
        if (iVar5 != 0) goto LAB_001dda54;
        param_2 = *(code **)(param_1 + 0x48);
        param_3 = *(undefined8 *)(param_1 + 0x50);
        param_4 = *(long *)(param_1 + 0x58);
        if ((local_6e & 0xf0) != 0x40) break;
        iVar5 = (*param_2)(param_3,&local_6e);
        if (iVar5 != 0) goto LAB_001dda54;
        lVar17 = *(long *)(param_1 + 0x58) + 1;
        *(long *)(param_1 + 0x58) = lVar17;
      }
      uVar12 = (uint)local_6e;
      if (local_6e < 0x68) {
        if (uVar12 < 0x2e) {
          if (local_6e != 0x26) goto LAB_001dee00;
        }
        else if ((0x3c0000000010101U >> ((ulong)(uVar12 - 0x2e) & 0x3f) & 1) == 0) {
LAB_001dee00:
          param_4 = param_4 + -1;
          *(long *)(param_1 + 0x58) = param_4;
        }
      }
      else if ((local_6e != 0xf0) && (1 < (uVar12 + 0xe & 0xff))) goto LAB_001dee00;
    }
    else {
      param_2 = *(code **)(param_1 + 0x48);
      param_3 = *(undefined8 *)(param_1 + 0x50);
      *(long *)(param_1 + 0x58) = param_4;
    }
  }
  iVar5 = (*param_2)(param_3,&local_6e,param_4);
  if (iVar5 != 0) goto LAB_001dda54;
  lVar14 = *(long *)(param_1 + 0x58);
  uVar12 = (uint)local_6e;
  lVar17 = lVar14 + 1;
  *(long *)(param_1 + 0x58) = lVar17;
  if (lVar14 != *(long *)(param_1 + 0x68)) goto LAB_001ddab8;
  if (1 < (byte)(local_6e + 0xe)) {
    if (0x67 < local_6e) {
      if (local_6e == 0xf0) {
LAB_001deb94:
        uVar12 = 0xf0;
        goto LAB_001dde24;
      }
      goto LAB_001ddb88;
    }
LAB_001ddac0:
    if (uVar12 < 0x2e) {
      if (uVar12 != 0x26) {
        iVar5 = *(int *)(param_1 + 0x60);
        param_1[0x78] = '\0';
        param_1[0x79] = '\0';
        param_1[0x7a] = '\0';
        param_1[0x7b] = '\0';
        lVar17 = *(long *)(param_1 + 0x58);
        goto joined_r0x001dde90;
      }
      uVar13 = 4;
    }
    else {
      uVar13 = 1;
      if ((1L << ((ulong)(uVar12 - 0x2e) & 0x3f) & 0xc0000000010101U) == 0) {
        if (uVar12 == 0x67) {
          param_5 = *(int *)(param_1 + 0x60);
          param_1[4] = 'g';
          param_1[0x37] = '\x01';
        }
        else {
          if (uVar12 != 0x66) {
            param_1[0x78] = '\0';
            param_1[0x79] = '\0';
            param_1[0x7a] = '\0';
            param_1[0x7b] = '\0';
            lVar17 = *(long *)(param_1 + 0x58);
            if (uVar12 != 0x62) {
              iVar5 = *(int *)(param_1 + 0x60);
              if (iVar5 != 2) goto LAB_001dde94;
              if (0xf < (uVar12 - 0x40 & 0xff)) goto LAB_001df35c;
              iVar5 = (**(code **)(param_1 + 0x48))
                                (*(undefined8 *)(param_1 + 0x50),&local_6d,lVar17);
              if (iVar5 != 0) goto switchD_001df078_caseD_10;
              iVar5 = *(int *)(param_1 + 0x60);
              iVar7 = *(int *)(param_1 + 0x78);
              param_1[5] = local_6e;
              goto LAB_001de204;
            }
            iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6c,lVar17);
            if (iVar5 != 0) goto switchD_001df078_caseD_10;
            *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
            iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
            if ((((iVar5 == 0) &&
                 ((*(int *)(param_1 + 0x60) == 2 || (((byte)local_6c & 0xc0) == 0xc0)))) &&
                ((local_6c & 0xc) == 0)) && (((byte)local_6a >> 2 & 1) != 0)) {
              lVar17 = *(long *)(param_1 + 0x58);
              param_1[0x78] = '\x03';
              param_1[0x79] = '\0';
              param_1[0x7a] = '\0';
              param_1[0x7b] = '\0';
            }
            else {
              iVar7 = *(int *)(param_1 + 0x78);
              lVar17 = *(long *)(param_1 + 0x58) + -2;
              *(long *)(param_1 + 0x58) = lVar17;
              if (iVar7 != 3) {
                iVar5 = *(int *)(param_1 + 0x60);
                goto LAB_001de204;
              }
            }
            param_1[0x3d] = (byte)local_6c;
            param_1[0x3c] = local_6e;
            iVar5 = (**(code **)(param_1 + 0x48))
                              (*(undefined8 *)(param_1 + 0x50),param_1 + 0x3e,lVar17);
            if (iVar5 != 0) goto switchD_001df078_caseD_10;
            *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
            iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3f);
            if (iVar5 != 0) goto switchD_001df078_caseD_10;
            iVar5 = *(int *)(param_1 + 0x60);
            *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
            if (iVar5 != 2) goto LAB_001de614;
            bVar10 = param_1[0x3d];
            iVar7 = *(int *)(param_1 + 0x78);
            param_1[5] = (~(bVar10 >> 6) & 1) << 1 | ((byte)param_1[0x3e] >> 7) << 3 |
                         (~(bVar10 >> 7) & 1) << 2 | ~(bVar10 >> 5) & 1 | 0x40;
            goto LAB_001de218;
          }
          param_1[0x38] = '\x01';
          iVar5 = (**(code **)(param_1 + 0x48))
                            (*(undefined8 *)(param_1 + 0x50),&local_6a,
                             *(undefined8 *)(param_1 + 0x58));
          if (iVar5 == 0) {
            param_5 = *(int *)(param_1 + 0x60);
            if ((param_1[0x3b] == '\0') &&
               (((byte)local_6a == '\x0f' ||
                ((param_5 == 2 && ((byte)((byte)local_6a - 0x40) < 0x10)))))) {
              param_1[0x3b] = 'f';
            }
          }
          else {
            param_5 = *(int *)(param_1 + 0x60);
          }
          param_1[3] = local_6e;
        }
        goto LAB_001ddb1c;
      }
      if (uVar12 == 0x3e) {
        uVar13 = 3;
      }
      else if (uVar12 < 0x3f) {
        if (uVar12 == 0x2e) goto LAB_001dde60;
        if (uVar12 != 0x36) goto switchD_001df078_caseD_10;
        uVar13 = 2;
      }
      else if (uVar12 == 100) {
        uVar13 = 5;
      }
      else {
        if (uVar12 != 0x65) goto switchD_001df078_caseD_10;
        uVar13 = 6;
      }
    }
LAB_001dde60:
    param_1[2] = (char)uVar12;
    *(undefined4 *)(param_1 + 8) = uVar13;
    setPrefixPresent(param_1);
    param_5 = *(int *)(param_1 + 0x60);
    goto LAB_001ddb1c;
  }
  iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6d);
  if (iVar5 != 0) goto switchD_001df078_caseD_10;
  uVar12 = (uint)local_6e;
  if (((local_6d == 0xf0) || ((local_6d & 0xfe) == 0x86)) || ((local_6d & 0xf8) == 0x90)) {
    param_1[0x36] = local_6e;
LAB_001ddab8:
    if (uVar12 < 0x68) goto LAB_001ddac0;
    if (uVar12 == 0xf0) goto LAB_001deb94;
  }
  else {
    if (local_6e != 0xf3) {
      if ((*(int *)(param_1 + 0x60) == 2) && ((byte)(local_6d - 0x40) < 0x10)) {
LAB_001ddd9c:
        iVar5 = (**(code **)(param_1 + 0x48))
                          (*(undefined8 *)(param_1 + 0x50),&local_6a,*(undefined8 *)(param_1 + 0x58)
                          );
        if (iVar5 == 0) {
          *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
          iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
          if (iVar5 == 0) {
            uVar12 = (uint)local_6e;
            *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + -1;
            goto LAB_001ddab8;
          }
        }
        goto switchD_001df078_caseD_10;
      }
      goto LAB_001ddab8;
    }
    if ((byte)(local_6d + 0x78) < 2 || (local_6d == 0xc6 || local_6d == 199)) {
      param_1[0x36] = -0xd;
      goto LAB_001dde24;
    }
    if (*(int *)(param_1 + 0x60) != 2) goto LAB_001dde24;
    if ((byte)(local_6d - 0x40) < 0x10) goto LAB_001ddd9c;
  }
  if (1 < (uVar12 + 0xe & 0xff)) goto LAB_001df2d4;
LAB_001dde24:
  setPrefixPresent(param_1,uVar12);
  param_5 = *(int *)(param_1 + 0x60);
  param_1[1] = local_6e;
LAB_001ddb1c:
  param_2 = *(code **)(param_1 + 0x48);
  param_3 = *(undefined8 *)(param_1 + 0x50);
  param_4 = *(long *)(param_1 + 0x58);
  goto joined_r0x001dda40;
code_r0x001de2ac:
  if (uVar12 == 0) {
LAB_001de2b0:
    uVar13 = 0;
    *(long *)(param_1 + 0x70) = *(long *)(param_1 + 0x58) - *(long *)(param_1 + 0x68);
    if ((ulong)(*(long *)(param_1 + 0x58) - *(long *)(param_1 + 0x68)) < 0x10) {
      if (*param_1 == '\0') {
        *param_1 = param_1[0x7c];
      }
      *(undefined1 **)(param_1 + 0xd0) = x86OperandSets + (ulong)**(ushort **)(param_1 + 0x90) * 0xc
      ;
      goto LAB_001dda58;
    }
  }
  goto switchD_001df078_caseD_10;
LAB_001df2d4:
  lVar17 = *(long *)(param_1 + 0x58);
LAB_001ddb88:
  param_1[0x78] = '\0';
  param_1[0x79] = '\0';
  param_1[0x7a] = '\0';
  param_1[0x7b] = '\0';
  if (uVar12 == 0xc4) {
    iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
    if (iVar5 != 0) goto switchD_001df078_caseD_10;
    iVar5 = *(int *)(param_1 + 0x60);
    if ((iVar5 == 2) || (((byte)local_6a & 0xc0) == 0xc0)) {
      param_1[0x78] = '\x02';
      param_1[0x79] = '\0';
      param_1[0x7a] = '\0';
      param_1[0x7b] = '\0';
LAB_001ded34:
      param_1[0x3c] = local_6e;
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3d);
      if (iVar5 == 0) {
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3e);
      if (iVar5 == 0) {
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
      iVar5 = *(int *)(param_1 + 0x60);
      if (iVar5 == 2) {
        uVar12 = ~(uint)(byte)param_1[0x3d];
        iVar7 = *(int *)(param_1 + 0x78);
        param_1[5] = (byte)(((int)uVar12 >> 6 & 1U) << 1) | ((byte)param_1[0x3e] >> 7) << 3 |
                     (byte)(uVar12 >> 5) & 1 | (byte)((uVar12 & 0x80) >> 5) | 0x40;
        goto LAB_001de218;
      }
LAB_001de614:
      iVar7 = *(int *)(param_1 + 0x78);
    }
    else {
      iVar7 = *(int *)(param_1 + 0x78);
      *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + -1;
      if (iVar7 == 2) goto LAB_001ded34;
    }
joined_r0x001de618:
    if (iVar5 == 0) {
LAB_001ddbe0:
      bVar10 = param_1[0x38];
      cVar11 = '\x02';
      bVar4 = param_1[0x37];
      cVar15 = '\x04';
    }
    else {
      if (iVar5 != 1) goto LAB_001ddc14;
LAB_001de624:
      bVar10 = param_1[0x38];
      cVar11 = '\x04';
      bVar4 = param_1[0x37];
      cVar15 = '\x02';
    }
    cVar18 = cVar11;
    if ((bVar10 & 1) != 0) {
      cVar18 = cVar15;
    }
    if ((bVar4 & 1) != 0) {
      cVar11 = cVar15;
    }
    param_1[0x7c] = cVar18;
    param_1[0x7d] = cVar11;
    param_1[0x7e] = cVar11;
    param_1[0x7f] = cVar18;
    param_1[0x80] = cVar18;
LAB_001ddc14:
    param_1[0x84] = '\0';
    param_1[0x85] = '\0';
    param_1[0x86] = '\0';
    param_1[0x87] = '\0';
    if (iVar7 == 3) {
      uVar12 = (byte)param_1[0x3d] & 3;
      if (uVar12 != 2) {
        if (uVar12 == 3) goto LAB_001ddc58;
LAB_001de698:
        bVar3 = uVar12 != 1;
        uVar12 = 1;
        if (bVar3) goto switchD_001df078_caseD_10;
      }
LAB_001de6a0:
      pcVar16 = *(code **)(param_1 + 0x48);
      *(uint *)(param_1 + 0x84) = uVar12;
LAB_001ddc60:
      iVar5 = (*pcVar16)(*(undefined8 *)(param_1 + 0x50),param_1 + 0x81,
                         *(undefined8 *)(param_1 + 0x58));
    }
    else {
      if (iVar7 == 2) {
        uVar12 = (byte)param_1[0x3d] & 0x1f;
        if (uVar12 != 2) {
          if (uVar12 != 3) goto LAB_001de698;
          uVar12 = 3;
          goto LAB_001de6a0;
        }
LAB_001ddc58:
        pcVar16 = *(code **)(param_1 + 0x48);
        *(int *)(param_1 + 0x84) = iVar7;
        goto LAB_001ddc60;
      }
      if (iVar7 == 1) goto LAB_001ddc58;
      if (iVar7 != 4) goto LAB_001ddeb0;
      bVar10 = param_1[0x3d] & 0x1f;
      if (bVar10 == 9) {
        pcVar16 = *(code **)(param_1 + 0x48);
        uVar13 = 5;
      }
      else {
        if (bVar10 != 10) {
          if (bVar10 != 8) goto switchD_001df078_caseD_10;
          goto LAB_001ddc58;
        }
        pcVar16 = *(code **)(param_1 + 0x48);
        uVar13 = 6;
      }
      *(undefined4 *)(param_1 + 0x84) = uVar13;
      iVar5 = (*pcVar16)(*(undefined8 *)(param_1 + 0x50),param_1 + 0x81,
                         *(undefined8 *)(param_1 + 0x58));
    }
    if (iVar5 != 0) goto switchD_001df078_caseD_10;
    iVar5 = *(int *)(param_1 + 0x78);
    iVar7 = *(int *)(param_1 + 0x60);
    *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
  }
  else {
    if (uVar12 == 0xc5) {
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
      if (iVar5 != 0) goto switchD_001df078_caseD_10;
      iVar5 = *(int *)(param_1 + 0x60);
      if ((iVar5 == 2) || (((byte)local_6a & 0xc0) == 0xc0)) {
        param_1[0x78] = '\x01';
        param_1[0x79] = '\0';
        param_1[0x7a] = '\0';
        param_1[0x7b] = '\0';
      }
      else {
        iVar7 = *(int *)(param_1 + 0x78);
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + -1;
        if (iVar7 != 1) goto joined_r0x001de618;
      }
      param_1[0x3c] = local_6e;
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3d);
      if (iVar5 == 0) {
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
      iVar5 = *(int *)(param_1 + 0x60);
      bVar10 = param_1[0x3d];
      if (iVar5 == 2) {
        bVar4 = (~(bVar10 >> 7) & 1) << 2;
        goto LAB_001def14;
      }
LAB_001dec90:
      iVar7 = *(int *)(param_1 + 0x78);
      if ((bVar10 & 3) == 1) {
        param_1[0x38] = '\x01';
      }
LAB_001de204:
      if (iVar5 == 0) goto LAB_001ddbe0;
      if (iVar5 == 1) goto LAB_001de624;
      if (iVar5 == 2) goto LAB_001de218;
      goto LAB_001ddc14;
    }
    if (uVar12 == 0x8f) {
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
      if (iVar5 != 0) goto switchD_001df078_caseD_10;
      if ((local_6a & 0x38) == 0) {
        iVar7 = *(int *)(param_1 + 0x78);
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + -1;
        if (iVar7 == 4) goto LAB_001dee98;
        iVar5 = *(int *)(param_1 + 0x60);
        goto LAB_001de204;
      }
      param_1[0x78] = '\x04';
      param_1[0x79] = '\0';
      param_1[0x7a] = '\0';
      param_1[0x7b] = '\0';
LAB_001dee98:
      param_1[0x3c] = local_6e;
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3d);
      if (iVar5 == 0) {
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),param_1 + 0x3e);
      if (iVar5 == 0) {
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      }
      iVar5 = *(int *)(param_1 + 0x60);
      bVar10 = param_1[0x3e];
      if (iVar5 != 2) goto LAB_001dec90;
      uVar12 = ~(uint)(byte)param_1[0x3d];
      bVar4 = (byte)(((int)uVar12 >> 6 & 1U) << 1) | (bVar10 >> 7) << 3 |
              (byte)(uVar12 >> 5) & 1 | (byte)((uVar12 & 0x80) >> 5);
LAB_001def14:
      param_1[5] = bVar4 | 0x40;
      iVar7 = *(int *)(param_1 + 0x78);
      if ((bVar10 & 3) == 1) {
        param_1[0x38] = '\x01';
      }
LAB_001de218:
      bVar10 = param_1[0x37];
      if ((param_1[5] == 0) || (((byte)param_1[5] >> 3 & 1) == 0)) {
        if ((param_1[0x38] & 1U) == 0) {
          if ((bVar10 & 1) == 0) {
            cVar15 = '\x04';
            cVar11 = '\b';
            cVar18 = '\b';
          }
          else {
            cVar18 = '\b';
            cVar11 = '\x04';
            cVar15 = '\x04';
          }
        }
        else if ((bVar10 & 1) == 0) {
          cVar15 = '\x02';
          cVar11 = '\b';
          cVar18 = '\x04';
        }
        else {
          cVar11 = '\x04';
          cVar15 = '\x02';
          cVar18 = '\x04';
        }
        param_1[0x7c] = cVar15;
        param_1[0x7d] = cVar11;
        param_1[0x7e] = cVar15;
        param_1[0x7f] = cVar15;
        param_1[0x80] = cVar18;
      }
      else {
        cVar11 = '\b';
        if ((bVar10 & 1) != 0) {
          cVar11 = '\x04';
        }
        param_1[0x7c] = '\b';
        param_1[0x7d] = cVar11;
        param_1[0x7e] = '\x04';
        param_1[0x7f] = '\x04';
        param_1[0x80] = '\x04';
      }
      goto LAB_001ddc14;
    }
    iVar5 = *(int *)(param_1 + 0x60);
joined_r0x001dde90:
    if (iVar5 == 2) {
LAB_001df35c:
      iVar7 = 0;
      *(long *)(param_1 + 0x58) = lVar17 + -1;
      goto LAB_001de218;
    }
LAB_001dde94:
    *(long *)(param_1 + 0x58) = lVar17 + -1;
    iVar7 = 0;
    if (iVar5 == 0) goto LAB_001ddbe0;
    if (iVar5 == 1) {
      iVar7 = 0;
      goto LAB_001de624;
    }
    param_1[0x84] = '\0';
    param_1[0x85] = '\0';
    param_1[0x86] = '\0';
    param_1[0x87] = '\0';
LAB_001ddeb0:
    iVar5 = (**(code **)(param_1 + 0x48))
                      (*(undefined8 *)(param_1 + 0x50),&local_6a,*(undefined8 *)(param_1 + 0x58));
    if (iVar5 != 0) goto switchD_001df078_caseD_10;
    *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
    param_1[0xa1] = (byte)local_6a;
    if ((byte)local_6a == '\x0f') {
      param_1[0x20] = '\x0f';
      iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
      if (iVar5 != 0) goto switchD_001df078_caseD_10;
      *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
      if ((byte)local_6a == '8') {
        iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
        if (iVar5 != 0) goto switchD_001df078_caseD_10;
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
        param_1[0x84] = '\x02';
        param_1[0x85] = '\0';
        param_1[0x86] = '\0';
        param_1[0x87] = '\0';
      }
      else if ((byte)local_6a == ':') {
        iVar5 = (**(code **)(param_1 + 0x48))(*(undefined8 *)(param_1 + 0x50),&local_6a);
        if (iVar5 != 0) goto switchD_001df078_caseD_10;
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
        param_1[0x84] = '\x03';
        param_1[0x85] = '\0';
        param_1[0x86] = '\0';
        param_1[0x87] = '\0';
      }
      else if ((byte)local_6a == '\x0f') {
        iVar5 = readModRM(param_1);
        if ((iVar5 != 0) ||
           (iVar5 = (**(code **)(param_1 + 0x48))
                              (*(undefined8 *)(param_1 + 0x50),&local_6a,
                               *(undefined8 *)(param_1 + 0x58)), iVar5 != 0))
        goto switchD_001df078_caseD_10;
        *(long *)(param_1 + 0x58) = *(long *)(param_1 + 0x58) + 1;
        param_1[0x84] = '\a';
        param_1[0x85] = '\0';
        param_1[0x86] = '\0';
        param_1[0x87] = '\0';
      }
      else {
        param_1[0x84] = '\x01';
        param_1[0x85] = '\0';
        param_1[0x86] = '\0';
        param_1[0x87] = '\0';
      }
    }
    else if (param_1[0x3b] != '\0') {
      param_1[0x3b] = '\0';
    }
    iVar5 = *(int *)(param_1 + 0x78);
    iVar7 = *(int *)(param_1 + 0x60);
    param_1[0x81] = (byte)local_6a;
  }
  uVar12 = (uint)(iVar7 == 2);
  if (iVar5 == 0) {
    bVar10 = param_1[0x3b];
    if (bVar10 == 0) {
      cVar11 = param_1[0x3a];
      uVar12 = uVar12 | -(uint)(byte)param_1[0x37] & 0x20 |
               (uint)(byte)(iVar7 != 0 & param_1[0x38]) << 4;
      if (*(int *)(param_1 + 0x84) == 0) {
        uVar19 = uVar12;
        if ((cVar11 == -0xd) && (uVar19 = uVar12 | 2, param_1[0x81] != -0x70)) {
          uVar19 = uVar12;
        }
      }
      else {
        if (cVar11 == -0xe) goto LAB_001de990;
        uVar19 = uVar12 | 2;
        if (cVar11 != -0xd) {
          uVar19 = uVar12;
        }
      }
      goto LAB_001ddf68;
    }
    if (bVar10 == 0xf2) {
LAB_001de990:
      uVar19 = uVar12 | 4;
      goto LAB_001ddf68;
    }
    if (0xf2 < bVar10) {
      uVar19 = uVar12 | 2;
      if (bVar10 != 0xf3) {
        uVar19 = uVar12;
      }
      goto LAB_001ddf68;
    }
    if (bVar10 != 0x66) {
      uVar19 = uVar12 | 0x20;
      if (bVar10 != 0x67) {
        uVar19 = uVar12;
      }
      goto LAB_001ddf68;
    }
    if (iVar7 != 0) {
      if ((param_1[5] & 8U) != 0) {
        uVar12 = 0x19;
        if (iVar7 != 2) {
          iVar5 = *(int *)(param_1 + 0x84);
          uVar12 = 0x18;
          goto LAB_001ddfb0;
        }
        goto LAB_001de640;
      }
      uVar12 = 0x11;
      if (iVar7 == 2) goto LAB_001de640;
      iVar5 = *(int *)(param_1 + 0x84);
      uVar12 = 0x10;
      goto LAB_001ddfb0;
    }
    uVar6 = (uint)((param_1[5] & 8U) != 0) << 3;
    if ((*(ulong *)(param_1 + 0x80) & 0xffffffff0000ff00) == 0xe300) {
      uVar12 = uVar6 ^ 0x20;
      iVar5 = *(int *)(param_1 + 0x84);
      goto LAB_001ddfb0;
    }
LAB_001ddfa8:
    iVar5 = *(int *)(param_1 + 0x84);
    uVar12 = uVar6;
LAB_001ddfb0:
    if ((iVar5 == 0) && ((param_1[0x81] & 0xfcU) == 0xa0)) {
      uVar6 = uVar12 | -(uint)(byte)param_1[0x38] & 0x10 | -(uint)(byte)param_1[0x37] & 0x20;
      if (*(int *)(param_1 + 0x60) == 0) {
        uVar6 = uVar6 ^ 0x30;
      }
    }
    else {
LAB_001ddfc4:
      if ((*(ulong *)(param_1 + 0x80) & 0xffffffff0000ff00) != 0x20000f800 &&
          (*(ulong *)(param_1 + 0x80) & 0xffffffff0000ff00) != 0x10000ae00) {
        iVar5 = getIDWithAttrMask(&local_6c,param_1,uVar12);
        if (iVar5 != 0) goto switchD_001df078_caseD_10;
        if ((*(int *)(param_1 + 0x60) == 0) || ((param_1[0x38] & 1U) != 0)) {
          uVar6 = (uint)local_6c;
          puVar20 = x86DisassemblerInstrSpecifiers + (ulong)local_6c * 2;
          if ((uVar12 >> 4 & 1) != 0) goto LAB_001de6f8;
          iVar5 = getIDWithAttrMask(&local_6a,param_1,uVar12 | 0x10);
          if (iVar5 == 0) {
            uVar1 = *(ushort *)(x86_16_bit_eq_lookup + (ulong)local_6c * 2);
            if ((uVar1 - 1 & 0xffff) < 0x62b) {
              puVar9 = x86_16_bit_eq_tbl + (ulong)uVar1 * 4;
              while (local_6c == *(ushort *)(puVar9 + -4)) {
                if ((uint)*(ushort *)(puVar9 + -2) == (uint)local_6a) {
                  if ((*(int *)(param_1 + 0x60) == 0) != (bool)param_1[0x38]) {
                    puVar20 = x86DisassemblerInstrSpecifiers + (ulong)local_6a * 2;
                    uVar6 = (uint)local_6a;
                  }
                  break;
                }
                puVar9 = puVar9 + 4;
                if (puVar9 == x86Disassembler3DNowOpcodes +
                              ((long)(int)-(uint)uVar1 + (ulong)uVar1) * 4) break;
              }
            }
          }
        }
        else {
LAB_001de6f8:
          uVar6 = (uint)local_6c;
          puVar20 = x86DisassemblerInstrSpecifiers + (ulong)local_6c * 2;
          if (((*(ulong *)(param_1 + 0x80) & 0xffffffff0000ff00) != 0x9000) ||
             ((param_1[5] & 1U) == 0)) {
            *(ushort *)(param_1 + 0x88) = local_6c;
            *(undefined1 **)(param_1 + 0x90) = puVar20;
            goto LAB_001de04c;
          }
          param_1[0x81] = -0x6f;
          iVar5 = getIDWithAttrMask(&local_6a,param_1,uVar12);
          if (iVar5 == 0) {
            uVar6 = (uint)local_6a;
            puVar20 = x86DisassemblerInstrSpecifiers + (ulong)local_6a * 2;
          }
          param_1[0x81] = -0x70;
        }
        *(short *)(param_1 + 0x88) = (short)uVar6;
        *(undefined1 **)(param_1 + 0x90) = puVar20;
        goto LAB_001de04c;
      }
      uVar12 = uVar12 | -(uint)(byte)param_1[0x38] & 0x10 | -(uint)(byte)param_1[0x37] & 0x20;
      uVar6 = uVar12;
      if (((*(int *)(param_1 + 0x60) == 0) && (uVar6 = uVar12 ^ 0x20, iVar5 == 0)) &&
         ((param_1[0x81] & 0xfcU) == 0xa0)) {
        uVar6 = uVar12 ^ 0x30;
      }
    }
    iVar5 = getIDWithAttrMask(&local_6c,param_1,uVar6);
    if (iVar5 != 0) goto switchD_001df078_caseD_10;
    uVar6 = (uint)local_6c;
    *(ushort *)(param_1 + 0x88) = local_6c;
    *(undefined1 **)(param_1 + 0x90) = x86DisassemblerInstrSpecifiers + (ulong)local_6c * 2;
  }
  else {
    if (iVar5 == 3) {
      bVar10 = param_1[0x3e] & 3;
      if (bVar10 == 2) {
        uVar6 = uVar12 | 0x102;
      }
      else if (bVar10 == 3) {
        uVar6 = uVar12 | 0x104;
      }
      else {
        uVar6 = uVar12 | 0x110;
        if (bVar10 != 1) {
          uVar6 = uVar12 | 0x100;
        }
      }
      bVar10 = param_1[0x3f];
      uVar12 = uVar6 | 0x1000;
      if ((bVar10 & 0x80) == 0) {
        uVar12 = uVar6;
      }
      uVar6 = uVar12 | 0x2000;
      if ((bVar10 & 0x10) == 0) {
        uVar6 = uVar12;
      }
      uVar12 = uVar6 | 0x800;
      if ((bVar10 & 7) == 0) {
        uVar12 = uVar6;
      }
      uVar6 = uVar12 | 0x200;
      if ((bVar10 & 0x20) == 0) {
        uVar6 = uVar12;
      }
      uVar19 = uVar6 | 0x400;
      if ((bVar10 & 0x40) == 0) {
        uVar19 = uVar6;
      }
      goto LAB_001ddf68;
    }
    if (iVar5 == 2) {
LAB_001ddf2c:
      bVar4 = param_1[0x3e];
      bVar10 = bVar4 & 3;
      if (bVar10 != 2) goto LAB_001ddf3c;
LAB_001de9d8:
      uVar6 = uVar12 | 0x42;
    }
    else {
      if (iVar5 != 1) {
        if (iVar5 != 4) goto switchD_001df078_caseD_10;
        goto LAB_001ddf2c;
      }
      bVar4 = param_1[0x3d];
      bVar10 = bVar4 & 3;
      if (bVar10 == 2) goto LAB_001de9d8;
LAB_001ddf3c:
      if (bVar10 == 3) {
        uVar6 = uVar12 | 0x44;
      }
      else {
        uVar6 = uVar12 | 0x50;
        if (bVar10 != 1) {
          uVar6 = uVar12 | 0x40;
        }
      }
    }
    uVar19 = uVar6 | 0x80;
    if ((bVar4 & 4) == 0) {
      uVar19 = uVar6;
    }
LAB_001ddf68:
    uVar12 = uVar19 & 0xffffffdf | 8;
    if ((param_1[5] & 8U) == 0) {
      uVar12 = uVar19;
    }
    if (iVar7 != 0) {
      uVar6 = uVar12;
      if (iVar7 != 2) goto LAB_001ddfa4;
LAB_001de640:
      iVar5 = *(int *)(param_1 + 0x84);
      if ((param_1[0x38] & 1U) == 0) goto LAB_001ddfb0;
      bVar10 = param_1[0x81];
      if (bVar10 < 0x90) {
        if ((bVar10 < 0x82) || (iVar5 != 1)) goto LAB_001ddfb0;
LAB_001de66c:
        uVar12 = uVar12 ^ 0x10;
        param_1[0x7e] = '\x04';
        param_1[0x7f] = '\x04';
      }
      else {
        if (1 < (byte)(bVar10 + 0x18)) goto LAB_001ddfb0;
        if (iVar5 == 0) goto LAB_001de66c;
      }
      goto LAB_001ddfc4;
    }
    uVar6 = uVar12 ^ 0x20;
    if ((*(ulong *)(param_1 + 0x80) & 0xffffffff0000ff00) != 0xe300) {
      uVar6 = uVar12;
    }
LAB_001ddfa4:
    if (iVar5 == 0) goto LAB_001ddfa8;
    iVar5 = getIDWithAttrMask(&local_6c,param_1,uVar6);
    if (iVar5 != 0) goto switchD_001df078_caseD_10;
    if (((2 < *(int *)(param_1 + 0x78) - 2U) || (-1 < param_1[0x3e])) ||
       ((iVar5 = getIDWithAttrMask(&local_6a,param_1,uVar6 | 8), uVar2 = local_6a, uVar1 = local_6c,
        iVar5 == 0 &&
        ((uVar12 = find_insn(local_6a), uVar1 = uVar2, uVar12 != 0xffffffff &&
         (PTR_insns_005ffee0[((ulong)uVar12 * 4 + (ulong)uVar12) * 0x10 + 4] != '\0')))))) {
      iVar5 = *(int *)(param_1 + 0x84);
      uVar12 = uVar6;
      goto LAB_001ddfb0;
    }
    uVar6 = (uint)uVar1;
    *(ushort *)(param_1 + 0x88) = uVar1;
    *(undefined1 **)(param_1 + 0x90) = x86DisassemblerInstrSpecifiers + (ulong)uVar1 * 2;
  }
LAB_001de04c:
  if (uVar6 != 0) {
    if ((param_1[0x39] & 1U) != 0) {
      if (uVar6 < 0x703) {
        if (uVar6 < 0x6fc) {
          if (uVar6 < 0x13d) {
            if (0x11b < uVar6) {
              iVar5 = -0x11c;
              goto LAB_001ddde8;
            }
            if (uVar6 < 0xa7) {
              if (0x9a < uVar6) {
                uVar8 = 0xe27L >> ((ulong)(uVar6 - 0x9b) & 0x3f);
                goto joined_r0x001de7a0;
              }
            }
            else {
              uVar12 = uVar6 - 0xa9 & 0xffff;
              if (uVar12 < 0x3b) {
                uVar8 = 0x4e271389c04e271 >> ((ulong)uVar12 & 0x3f);
                goto joined_r0x001dedc8;
              }
            }
          }
          else {
            if (uVar6 < 0x2c8) {
              if (uVar6 < 0x2bf) {
                uVar12 = uVar6 - 0x1b8 & 0xffff;
                if (0x21 < uVar12) goto switchD_001df078_caseD_10;
                uVar8 = 0x333333333 >> ((ulong)uVar12 & 0x3f);
              }
              else {
                uVar8 = 0x1abL >> ((ulong)(uVar6 - 0x2bf) & 0x3f);
              }
              goto joined_r0x001de7a0;
            }
            if (uVar6 < 0x333) {
              if (0x329 < uVar6) {
                uVar8 = 0x149L >> ((ulong)(uVar6 - 0x32a) & 0x3f);
                goto joined_r0x001de7a0;
              }
            }
            else {
              uVar12 = uVar6 - 0x3ff & 0xffff;
              if (uVar12 < 9) {
                uVar8 = 0x149L >> ((ulong)uVar12 & 0x3f);
                goto joined_r0x001dedc8;
              }
            }
          }
          goto switchD_001df078_caseD_10;
        }
        uVar8 = 0x55L >> ((ulong)(uVar6 - 0x6fc) & 0x3f);
      }
      else if (uVar6 < 0xabf) {
        if (uVar6 < 0xa9e) {
          if (uVar6 < 0x74d) {
            if (0x715 < uVar6) {
              uVar8 = 0x4e271389caa001 >> ((ulong)(uVar6 - 0x716) & 0x3f);
joined_r0x001de7a0:
              if ((uVar8 & 1) != 0) goto LAB_001de0a8;
            }
          }
          else {
            uVar12 = uVar6 - 0x9ad & 0xffff;
            if (uVar12 < 0x1e) {
              uVar8 = 0x381c0e07L >> ((ulong)uVar12 & 0x3f);
              goto joined_r0x001de7a0;
            }
          }
          goto switchD_001df078_caseD_10;
        }
        iVar5 = -0xa9e;
LAB_001ddde8:
        uVar8 = 0x1389c4e27 >> ((ulong)(uVar6 + iVar5) & 0x3f);
      }
      else {
        if (uVar6 == 0x3b5d) goto LAB_001de0a8;
        uVar12 = uVar6 - 0x3b5f & 0xffff;
        if (0x3d < uVar12) goto switchD_001df078_caseD_10;
        uVar8 = 0x271389c4e0029215 >> ((ulong)uVar12 & 0x3f);
      }
joined_r0x001dedc8:
      if ((uVar8 & 1) == 0) goto switchD_001df078_caseD_10;
    }
LAB_001de0a8:
    iVar5 = *(int *)(param_1 + 0x78);
    if (iVar5 == 3) {
      uVar12 = (~(uint)((byte)param_1[0x3f] >> 3) & 1) << 4 |
               ~(uint)((byte)param_1[0x3e] >> 3) & 0xf;
    }
    else {
      if (iVar5 != 2) {
        if (iVar5 == 1) {
          uVar12 = ~(uint)((byte)param_1[0x3d] >> 3) & 0xf;
          goto LAB_001de0d8;
        }
        if (iVar5 != 4) {
          bVar3 = false;
          lVar17 = 0;
LAB_001df040:
          iVar5 = (int)lVar17;
          uVar1 = **(ushort **)(param_1 + 0x90);
          uVar8 = (ulong)uVar1;
          bVar10 = x86OperandSets[((uVar8 * 2 + (ulong)uVar1) * 2 + (long)iVar5) * 2];
          if (0x21 < bVar10) goto switchD_001df078_caseD_10;
          uVar12 = (uint)bVar10;
          switch(bVar10) {
          case 0:
          case 0x1a:
          case 0x1f:
          case 0x20:
          case 0x21:
            goto switchD_001df078_caseD_0;
          default:
            iVar5 = readModRM(param_1);
            if ((iVar5 == 0) &&
               (iVar5 = fixupReg(param_1,x86OperandSets + (lVar17 + (ulong)uVar1 * 6) * 2),
               iVar5 == 0)) {
              if ((uVar12 != 1) && (*(int *)(param_1 + 200) == 1)) {
                *(long *)(param_1 + 0x18) =
                     *(long *)(param_1 + 0x18) * (long)(1 << (ulong)(uVar12 - 2 & 0x1f));
              }
              goto switchD_001df078_caseD_0;
            }
            goto switchD_001df078_caseD_10;
          case 9:
          case 10:
          case 0xb:
          case 0xc:
          case 0xd:
          case 0xe:
          case 0xf:
            iVar7 = readModRM(param_1);
            if ((iVar7 == 0) && ((*(int *)(param_1 + 0xc4) - 0x15U & 0xffffffef) == 0)) {
              iVar7 = *(int *)(param_1 + 0x28);
              if (iVar7 == 0) {
                iVar7 = *(int *)(param_1 + 0x24) + 4;
                *(int *)(param_1 + 0x28) = iVar7;
              }
              if (((*(int *)(param_1 + 0x78) == 3) && (*(int *)(param_1 + 0x60) == 2)) &&
                 (((byte)param_1[0x3f] >> 3 & 1) == 0)) {
                iVar7 = iVar7 + 0x10;
                *(int *)(param_1 + 0x28) = iVar7;
              }
              cVar11 = x86OperandSets[(uVar8 * 6 + (long)iVar5) * 2 + 1];
              if (cVar11 == '\r') {
                iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x51;
              }
              else if (cVar11 == '\x0e') {
                iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x71;
              }
              else {
                if (cVar11 != '\f') goto switchD_001df078_caseD_10;
                iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x31;
              }
              *(int *)(param_1 + 0x28) = iVar5;
              if (*(int *)(param_1 + 200) == 1) {
                *(long *)(param_1 + 0x18) =
                     *(long *)(param_1 + 0x18) * (long)(1 << (ulong)(uVar12 - 9 & 0x1f));
              }
              goto switchD_001df078_caseD_0;
            }
          case 0x10:
            goto switchD_001df078_caseD_10;
          case 0x11:
            if (*(int *)(param_1 + 0x78) == 3) {
              *(uint *)(param_1 + 0x9c) = (byte)param_1[0x3f] & 7;
              goto switchD_001df078_caseD_0;
            }
            goto switchD_001df078_caseD_10;
          case 0x12:
            if (bVar3) {
              bVar10 = param_1[0x35];
              *(ulong *)(param_1 + (ulong)bVar10 * 8 + 0xa8) =
                   *(ulong *)(param_1 + (ulong)bVar10 * 8 + 0xa0) & 0xf;
              param_1[0x35] = bVar10 + 1;
              goto switchD_001df078_caseD_0;
            }
            iVar7 = readImmediate(param_1,1);
            if (iVar7 != 0) goto switchD_001df078_caseD_10;
            bVar3 = (byte)(x86OperandSets[(uVar8 * 6 + (long)iVar5) * 2 + 1] - 0x14) < 2;
            goto switchD_001df078_caseD_0;
          case 0x13:
            iVar5 = readImmediate(param_1,2);
            break;
          case 0x14:
            iVar5 = readImmediate(param_1,4);
            break;
          case 0x15:
            iVar5 = readImmediate(param_1,8);
            break;
          case 0x16:
            iVar5 = readOpcodeRegister(param_1,1);
            break;
          case 0x17:
            iVar5 = readOpcodeRegister(param_1,2);
            break;
          case 0x18:
            iVar5 = readOpcodeRegister(param_1,4);
            break;
          case 0x19:
            iVar5 = readOpcodeRegister(param_1,8);
            break;
          case 0x1b:
            iVar5 = readImmediate(param_1,param_1[0x7f]);
            break;
          case 0x1c:
            iVar5 = readImmediate(param_1,param_1[0x7d]);
            if (iVar5 == 0) {
              param_1[0x40] = param_1[0x41];
              param_1[0x7e] = param_1[0x7f];
              param_1[0x10] = '\x01';
              *(undefined8 *)(param_1 + 0x18) =
                   *(undefined8 *)(param_1 + (long)(int)((byte)param_1[0x35] - 1) * 8 + 0xa8);
              param_1[0x41] = '\0';
              param_1[0x7f] = '\0';
              goto switchD_001df078_caseD_0;
            }
            goto switchD_001df078_caseD_10;
          case 0x1d:
            param_1[0x34] = (byte)param_1[0x3f] >> 5 & 3;
            goto switchD_001df078_caseD_0;
          case 0x1e:
            iVar5 = readOpcodeRegister(param_1,0);
          }
          if (iVar5 != 0) goto switchD_001df078_caseD_10;
switchD_001df078_caseD_0:
          lVar17 = lVar17 + 1;
          if (lVar17 == 6) goto LAB_001de2b0;
          goto LAB_001df040;
        }
      }
      uVar12 = ~(uint)((byte)param_1[0x3e] >> 3) & 0xf;
    }
LAB_001de0d8:
    uVar6 = uVar12 & 0xf;
    if (*(int *)(param_1 + 0x60) == 2) {
      uVar6 = uVar12;
    }
    lVar17 = 0;
    uVar12 = (uint)(uVar6 != 0);
    *(uint *)(param_1 + 0x98) = uVar6;
    bVar3 = false;
LAB_001de10c:
    uVar1 = **(ushort **)(param_1 + 0x90);
    uVar8 = (ulong)uVar1;
    iVar5 = (int)lVar17;
    bVar10 = x86OperandSets[((uVar8 * 2 + (ulong)uVar1) * 2 + (long)iVar5) * 2];
    if (0x21 < bVar10) goto switchD_001df078_caseD_10;
    uVar6 = (uint)bVar10;
    switch(bVar10) {
    case 0:
    case 0x1a:
    case 0x1f:
    case 0x20:
    case 0x21:
      goto switchD_001de14c_caseD_0;
    default:
      iVar5 = readModRM(param_1);
      if ((iVar5 == 0) &&
         (iVar5 = fixupReg(param_1,x86OperandSets + (lVar17 + (ulong)uVar1 * 6) * 2), iVar5 == 0)) {
        if ((uVar6 != 1) && (*(int *)(param_1 + 200) == 1)) {
          *(long *)(param_1 + 0x18) =
               *(long *)(param_1 + 0x18) * (long)(1 << (ulong)(uVar6 - 2 & 0x1f));
        }
        goto switchD_001de14c_caseD_0;
      }
      goto switchD_001df078_caseD_10;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
      if (uVar12 != 0) {
        uVar12 = (uint)((*(uint *)(param_1 + 0x98) & 0xf) != 0);
      }
      iVar7 = readModRM(param_1);
      if ((iVar7 == 0) && ((*(int *)(param_1 + 0xc4) - 0x15U & 0xffffffef) == 0)) {
        iVar7 = *(int *)(param_1 + 0x28);
        if (iVar7 == 0) {
          iVar7 = *(int *)(param_1 + 0x24) + 4;
          *(int *)(param_1 + 0x28) = iVar7;
        }
        if (((*(int *)(param_1 + 0x78) == 3) && (*(int *)(param_1 + 0x60) == 2)) &&
           (((byte)param_1[0x3f] >> 3 & 1) == 0)) {
          iVar7 = iVar7 + 0x10;
          *(int *)(param_1 + 0x28) = iVar7;
        }
        cVar11 = x86OperandSets[(uVar8 * 6 + (long)iVar5) * 2 + 1];
        if (cVar11 == '\r') {
          iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x51;
        }
        else if (cVar11 == '\x0e') {
          iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x71;
        }
        else {
          if (cVar11 != '\f') goto switchD_001df078_caseD_10;
          iVar5 = (iVar7 - *(int *)(param_1 + 0x24)) + 0x31;
        }
        *(int *)(param_1 + 0x28) = iVar5;
        if (*(int *)(param_1 + 200) == 1) {
          *(long *)(param_1 + 0x18) =
               *(long *)(param_1 + 0x18) * (long)(1 << (ulong)(uVar6 - 9 & 0x1f));
        }
        goto switchD_001de14c_caseD_0;
      }
      goto switchD_001df078_caseD_10;
    case 0x10:
      if (*(int *)(param_1 + 0x60) != 2) {
        *(uint *)(param_1 + 0x98) = *(uint *)(param_1 + 0x98) & 7;
      }
      uVar12 = fixupReg(param_1);
      uVar6 = uVar12;
      break;
    case 0x11:
      if (*(int *)(param_1 + 0x78) == 3) {
        *(uint *)(param_1 + 0x9c) = (byte)param_1[0x3f] & 7;
        goto switchD_001de14c_caseD_0;
      }
      goto switchD_001df078_caseD_10;
    case 0x12:
      if (bVar3) {
        bVar10 = param_1[0x35];
        *(ulong *)(param_1 + (ulong)bVar10 * 8 + 0xa8) =
             *(ulong *)(param_1 + (ulong)bVar10 * 8 + 0xa0) & 0xf;
        param_1[0x35] = bVar10 + 1;
        goto switchD_001de14c_caseD_0;
      }
      iVar7 = readImmediate(param_1,1);
      if (iVar7 != 0) goto switchD_001df078_caseD_10;
      bVar3 = (byte)(x86OperandSets[(uVar8 * 6 + (long)iVar5) * 2 + 1] - 0x14) < 2;
      goto switchD_001de14c_caseD_0;
    case 0x13:
      uVar6 = readImmediate(param_1,2);
      break;
    case 0x14:
      uVar6 = readImmediate(param_1,4);
      break;
    case 0x15:
      uVar6 = readImmediate(param_1,8);
      break;
    case 0x16:
      uVar6 = readOpcodeRegister(param_1,1);
      break;
    case 0x17:
      uVar6 = readOpcodeRegister(param_1,2);
      break;
    case 0x18:
      uVar6 = readOpcodeRegister(param_1,4);
      break;
    case 0x19:
      uVar6 = readOpcodeRegister(param_1,8);
      break;
    case 0x1b:
      uVar6 = readImmediate(param_1,param_1[0x7f]);
      break;
    case 0x1c:
      iVar5 = readImmediate(param_1,param_1[0x7d]);
      if (iVar5 == 0) {
        param_1[0x40] = param_1[0x41];
        param_1[0x7e] = param_1[0x7f];
        param_1[0x10] = '\x01';
        *(undefined8 *)(param_1 + 0x18) =
             *(undefined8 *)(param_1 + (long)(int)((byte)param_1[0x35] - 1) * 8 + 0xa8);
        param_1[0x41] = '\0';
        param_1[0x7f] = '\0';
        goto switchD_001de14c_caseD_0;
      }
      goto switchD_001df078_caseD_10;
    case 0x1d:
      param_1[0x34] = (byte)param_1[0x3f] >> 5 & 3;
      goto switchD_001de14c_caseD_0;
    case 0x1e:
      uVar6 = readOpcodeRegister(param_1,0);
    }
    if (uVar6 != 0) goto switchD_001df078_caseD_10;
switchD_001de14c_caseD_0:
    lVar17 = lVar17 + 1;
    if (lVar17 == 6) goto code_r0x001de2ac;
    goto LAB_001de10c;
  }
switchD_001df078_caseD_10:
LAB_001dda54:
  uVar13 = 0xffffffff;
LAB_001dda58:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar13;
}

