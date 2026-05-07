
void FUN_001d8d60(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  char *pcVar2;
  char cVar3;
  ushort uVar4;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  int iVar9;
  uint uVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  long lVar18;
  undefined8 uVar19;
  ulong uVar20;
  ulong uVar21;
  long lVar22;
  undefined8 *puVar23;
  ulong uVar24;
  undefined8 uVar25;
  undefined *puVar26;
  long lVar27;
  undefined *puVar28;
  byte bVar29;
  undefined *local_b8;
  char acStack_a8 [64];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar9 = FUN_0018ffb0(param_1,0);
  if (iVar9 == 0x1540) {
    uVar25 = FUN_0018ffd0(param_1,0);
    uVar19 = FUN_0018ffd0(param_1,1);
    uVar16 = FUN_0018ffd0(param_1,2);
    uVar17 = FUN_0018ffd0(param_1,3);
    iVar9 = FUN_001900a0(uVar25);
    uVar10 = FUN_001900a0(uVar19);
    uVar24 = FUN_001900a0(uVar16);
    uVar12 = FUN_001900a0(uVar17);
    uVar12 = (uVar12 | iVar9 << 0xb) & 0xffff | (uVar10 & 0x1ff) << 7 | ((uint)uVar24 & 0x1fff) << 3
    ;
    if (uVar10 == 7) {
      if ((uint)uVar24 < 0xf) {
        uVar24 = 1L << (uVar24 & 0x3f);
        if ((uVar24 & 0x5c50) == 0) {
          if ((uVar24 & 0x300) == 0) {
            if (((uVar24 & 0x22) != 0) &&
               (puVar23 = (undefined8 *)FUN_001e7620(uVar12), puVar23 != (undefined8 *)0x0)) {
              bVar29 = *(byte *)((long)puVar23 + 10);
              puVar28 = &DAT_001ffec0;
              strncpy(acStack_a8,(char *)*puVar23,0x3f);
              goto LAB_001d9ca0;
            }
          }
          else {
            puVar23 = (undefined8 *)FUN_001e74f0(uVar12);
            if (puVar23 != (undefined8 *)0x0) {
              puVar28 = &DAT_001ffed8;
              strncpy(acStack_a8,(char *)*puVar23,0x3f);
              goto LAB_001da8b8;
            }
          }
        }
        else {
          puVar23 = (undefined8 *)FUN_001e75b4(uVar12);
          if (puVar23 != (undefined8 *)0x0) {
            puVar28 = &DAT_001ffed0;
            strncpy(acStack_a8,(char *)*puVar23,0x3f);
LAB_001da8b8:
            FUN_001903f0(param_2,"%s\t%s",puVar28,acStack_a8);
            goto LAB_001da8cc;
          }
        }
      }
    }
    else if ((uVar10 == 8) &&
            (puVar23 = (undefined8 *)FUN_001e7684(uVar12), puVar23 != (undefined8 *)0x0)) {
      bVar29 = *(byte *)((long)puVar23 + 10);
      puVar28 = &DAT_001ffec8;
      strncpy(acStack_a8,(char *)*puVar23,0x3f);
LAB_001d9ca0:
      FUN_001903f0(param_2,"%s\t%s",puVar28,acStack_a8);
      if ((bVar29 & 1) != 0) {
LAB_001da8cc:
        FUN_0018ffd0(param_1,4);
        bVar29 = 1;
        iVar9 = FUN_00190080();
        FUN_001903f0(param_2,&DAT_001ffc28,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
      }
      uVar11 = FUN_001dbb40(puVar28);
      FUN_0018ffa0(param_1,uVar11);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
        *(undefined4 *)(lVar18 + 0x7c) = 0x44;
        uVar11 = FUN_001dbbd4(acStack_a8);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar18 + 0x88) = uVar11;
        bVar1 = *(char *)(lVar27 + 0x67) + 1;
        *(byte *)(lVar27 + 0x67) = bVar1;
        if ((bVar29 & 1) != 0) {
          *(undefined4 *)(lVar27 + ((ulong)bVar1 * 8 - (ulong)bVar1) * 8 + 0x7c) = 1;
          FUN_0018ffd0(param_1,4);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar29 = *(byte *)(lVar27 + 0x67);
          uVar11 = FUN_00190080();
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) = uVar11;
          *(char *)(lVar18 + 0x67) = *(char *)(lVar18 + 0x67) + '\x01';
        }
      }
      goto switchD_001d9694_caseD_662;
    }
    goto LAB_001d960c;
  }
  uVar12 = iVar9 - 0xfd9;
  bVar8 = uVar12 < 2;
  bVar6 = iVar9 == 0x15e3;
  if (bVar8 || bVar6) {
LAB_001d8e88:
    bVar7 = iVar9 == 0xfda;
    uVar25 = FUN_0018ffd0(param_1,0);
    uVar19 = FUN_0018ffd0(param_1,1);
    uVar16 = FUN_0018ffd0(param_1,2);
    uVar17 = FUN_0018ffd0(param_1,3);
    uVar24 = FUN_00190030(uVar16);
    if ((((uVar24 & 1) != 0) && (lVar18 = FUN_001900a0(uVar16), lVar18 == 0)) &&
       (uVar24 = FUN_00190030(uVar17), (uVar24 & 1) != 0)) {
      lVar18 = FUN_001900a0(uVar17);
      if (lVar18 == 0xf) {
        if (uVar12 < 2) {
          puVar28 = &DAT_001ff320;
        }
        else {
          if (bVar7 || bVar6) goto LAB_001d8ef0;
          puVar28 = &DAT_001ff460;
        }
        goto LAB_001d99d0;
      }
      if (lVar18 == 0x1f) {
        if ((bVar7 || bVar6) && bVar8) {
          puVar28 = &DAT_001ffc08;
          goto LAB_001d99d0;
        }
      }
      else if (lVar18 == 7) {
        if (uVar12 < 2) {
          puVar28 = &DAT_001ff310;
        }
        else {
          if (bVar7 || bVar6) goto LAB_001d8ef0;
          puVar28 = &DAT_001ff450;
        }
LAB_001d99d0:
        iVar9 = FUN_00190080(uVar25);
        uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2);
        iVar9 = FUN_00190080(uVar19);
        switch(iVar9) {
        case 2:
          iVar9 = 0xd8;
          break;
        case 3:
          iVar9 = 0xd9;
          break;
        case 5:
          iVar9 = 7;
          break;
        case 9:
          iVar9 = 8;
          break;
        case 0xda:
          iVar9 = 0xbb;
          break;
        case 0xdb:
          iVar9 = 0xbc;
          break;
        case 0xdc:
          iVar9 = 0xbd;
          break;
        case 0xdd:
          iVar9 = 0xbe;
          break;
        case 0xde:
          iVar9 = 0xbf;
          break;
        case 0xdf:
          iVar9 = 0xc0;
          break;
        case 0xe0:
          iVar9 = 0xc1;
          break;
        case 0xe1:
          iVar9 = 0xc2;
          break;
        case 0xe2:
          iVar9 = 0xc3;
          break;
        case 0xe3:
          iVar9 = 0xc4;
          break;
        case 0xe4:
          iVar9 = 0xc5;
          break;
        case 0xe5:
          iVar9 = 0xc6;
          break;
        case 0xe6:
          iVar9 = 199;
          break;
        case 0xe7:
          iVar9 = 200;
          break;
        case 0xe8:
          iVar9 = 0xc9;
          break;
        case 0xe9:
          iVar9 = 0xca;
          break;
        case 0xea:
          iVar9 = 0xcb;
          break;
        case 0xeb:
          iVar9 = 0xcc;
          break;
        case 0xec:
          iVar9 = 0xcd;
          break;
        case 0xed:
          iVar9 = 0xce;
          break;
        case 0xee:
          iVar9 = 0xcf;
          break;
        case 0xef:
          iVar9 = 0xd0;
          break;
        case 0xf0:
          iVar9 = 0xd1;
          break;
        case 0xf1:
          iVar9 = 0xd2;
          break;
        case 0xf2:
          iVar9 = 0xd3;
          break;
        case 0xf3:
          iVar9 = 0xd4;
          break;
        case 0xf4:
          iVar9 = 0xd5;
          break;
        case 0xf5:
          iVar9 = 0xd6;
          break;
        case 0xf6:
          iVar9 = 0xd7;
        }
        FUN_001903f0(param_2,"%s\t%s, %s",puVar28,&DAT_002b3bf0 + uVar4,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(uVar25,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar19);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar29 = *(byte *)(lVar18 + 0x67);
          switch(uVar11) {
          case 2:
            uVar11 = 0xd8;
            break;
          case 3:
            uVar11 = 0xd9;
            break;
          case 5:
            uVar11 = 7;
            break;
          case 9:
            uVar11 = 8;
            break;
          case 0xda:
            uVar11 = 0xbb;
            break;
          case 0xdb:
            uVar11 = 0xbc;
            break;
          case 0xdc:
            uVar11 = 0xbd;
            break;
          case 0xdd:
            uVar11 = 0xbe;
            break;
          case 0xde:
            uVar11 = 0xbf;
            break;
          case 0xdf:
            uVar11 = 0xc0;
            break;
          case 0xe0:
            uVar11 = 0xc1;
            break;
          case 0xe1:
            uVar11 = 0xc2;
            break;
          case 0xe2:
            uVar11 = 0xc3;
            break;
          case 0xe3:
            uVar11 = 0xc4;
            break;
          case 0xe4:
            uVar11 = 0xc5;
            break;
          case 0xe5:
            uVar11 = 0xc6;
            break;
          case 0xe6:
            uVar11 = 199;
            break;
          case 0xe7:
            uVar11 = 200;
            break;
          case 0xe8:
            uVar11 = 0xc9;
            break;
          case 0xe9:
            uVar11 = 0xca;
            break;
          case 0xea:
            uVar11 = 0xcb;
            break;
          case 0xeb:
            uVar11 = 0xcc;
            break;
          case 0xec:
            uVar11 = 0xcd;
            break;
          case 0xed:
            uVar11 = 0xce;
            break;
          case 0xee:
            uVar11 = 0xcf;
            break;
          case 0xef:
            uVar11 = 0xd0;
            break;
          case 0xf0:
            uVar11 = 0xd1;
            break;
          case 0xf1:
            uVar11 = 0xd2;
            break;
          case 0xf2:
            uVar11 = 0xd3;
            break;
          case 0xf3:
            uVar11 = 0xd4;
            break;
          case 0xf4:
            uVar11 = 0xd5;
            break;
          case 0xf5:
            uVar11 = 0xd6;
            break;
          case 0xf6:
            uVar11 = 0xd7;
          }
          *(undefined4 *)(lVar18 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) = uVar11;
          *(byte *)(lVar18 + 0x67) = bVar29 + 1;
        }
        goto LAB_001d8e34;
      }
    }
LAB_001d8ef0:
    uVar24 = FUN_00190030(uVar16);
    if (((uVar24 & 1) == 0) || (uVar24 = FUN_00190030(uVar17), (uVar24 & 1) == 0)) {
LAB_001d8efc:
      lVar18 = FUN_001900a0(uVar16);
      lVar27 = FUN_001900a0(uVar17);
      if (lVar27 < lVar18) {
        pcVar2 = "ubfiz";
        if (uVar12 < 2) {
          pcVar2 = "sbfiz";
        }
        iVar9 = FUN_00190080(uVar25);
        uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2);
        iVar9 = FUN_00190080(uVar19);
        FUN_001903f0(param_2,"%s\t%s, %s, ",pcVar2,&DAT_002b3bf0 + uVar4,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
        iVar15 = 0x20;
        iVar9 = iVar15;
        if ((bool)(bVar7 | bVar6)) {
          iVar9 = 0x40;
        }
        iVar13 = FUN_001900a0(uVar16);
        FUN_00190614(param_2,iVar9 - iVar13);
        FUN_00190370(param_2,", ");
        iVar9 = FUN_001900a0(uVar17);
        FUN_00190614(param_2,iVar9 + 1);
        uVar11 = FUN_001dbb40(pcVar2);
        FUN_0018ffa0(param_1,uVar11);
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar19);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(uVar25,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          if ((bool)(bVar7 | bVar6)) {
            iVar15 = 0x40;
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          iVar9 = FUN_001900a0(uVar16);
          uVar25 = *(undefined8 *)(param_1 + 800);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar29 = *(byte *)(lVar18 + 0x67);
          *(long *)(lVar18 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) =
               (long)(iVar15 - iVar9);
          *(byte *)(lVar18 + 0x67) = bVar29 + 1;
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(uVar25,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          lVar18 = FUN_001900a0(uVar17);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar29 = *(byte *)(lVar27 + 0x67);
          *(long *)(lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) = lVar18 + 1;
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
        }
      }
      else {
        puVar28 = &DAT_001ff378;
        if (uVar12 < 2) {
          puVar28 = &DAT_001feff8;
        }
        iVar9 = FUN_00190080(uVar25);
        uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2);
        iVar9 = FUN_00190080(uVar19);
        FUN_001903f0(param_2,"%s\t%s, %s, ",puVar28,&DAT_002b3bf0 + uVar4,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
        uVar11 = FUN_001900a0(uVar16);
        FUN_00190614(param_2,uVar11);
        FUN_00190370(param_2,", ");
        iVar9 = FUN_001900a0(uVar17);
        iVar15 = FUN_001900a0(uVar16);
        FUN_00190614(param_2,(iVar9 - iVar15) + 1);
        uVar11 = FUN_001dbb40(puVar28);
        FUN_0018ffa0(param_1,uVar11);
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar19);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          uVar25 = FUN_001900a0(uVar16);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined8 *)(lVar18 + 0x88) = uVar25;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(uVar25,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          lVar18 = FUN_001900a0(uVar17);
          lVar27 = FUN_001900a0(uVar16);
          lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          bVar29 = *(byte *)(lVar22 + 0x67);
          *(long *)(lVar22 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) = (lVar18 - lVar27) + 1
          ;
          *(byte *)(lVar22 + 0x67) = bVar29 + 1;
        }
      }
    }
    else {
      iVar15 = FUN_001900a0(uVar16);
      iVar13 = FUN_001900a0(uVar17);
      bVar8 = iVar9 != 0x15e2;
      if (bVar8 || iVar13 == 0x1f) {
        if (iVar13 == 0x3f || !bVar6) {
          local_b8 = &DAT_001fa828;
          if (((bVar8 || iVar13 != 0x1f) && (iVar13 != 0x3f || !bVar6)) &&
             (local_b8 = &DAT_001fa830, iVar9 != 0xfd9 || iVar13 != 0x1f)) {
LAB_001dadfc:
            if (!bVar7 || iVar13 != 0x3f) goto LAB_001d8efc;
LAB_001da488:
            local_b8 = &DAT_001fa830;
          }
        }
        else {
          if (iVar13 + 1 == iVar15) {
            iVar15 = 0x3f;
            goto LAB_001db05c;
          }
          local_b8 = &DAT_001fa828;
          if (bVar8 || iVar13 != 0x1f) {
            if (iVar9 != 0xfd9 || iVar13 != 0x1f) goto LAB_001d8efc;
            goto LAB_001da488;
          }
        }
      }
      else {
        if (iVar13 + 1 != iVar15) {
          if (iVar13 == 0x3f || !bVar6) {
            local_b8 = &DAT_001fa828;
            if (iVar13 != 0x3f || !bVar6) goto LAB_001dadfc;
            goto LAB_001d90b8;
          }
          goto LAB_001d8efc;
        }
        iVar15 = 0x1f;
LAB_001db05c:
        iVar15 = iVar15 - iVar13;
        local_b8 = &DAT_001fa820;
      }
LAB_001d90b8:
      iVar9 = FUN_00190080(uVar25);
      uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2);
      iVar9 = FUN_00190080(uVar19);
      FUN_001903f0(param_2,"%s\t%s, %s, ",local_b8,&DAT_002b3bf0 + uVar4,
                   &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
      FUN_00190614(param_2,iVar15);
      uVar11 = FUN_001dbb40(local_b8);
      FUN_0018ffa0(param_1,uVar11);
      lVar18 = *(long *)(param_1 + 800);
      if (*(int *)(lVar18 + 0x60) != 0) {
        uVar11 = FUN_0018ffb0(param_1);
        bVar29 = *(byte *)(param_1 + 0x366);
        lVar27 = FUN_001dbcf0(lVar18,uVar11);
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar3 = *(char *)(lVar27 + (ulong)bVar29);
        if (cVar3 == -0x80) {
          cVar3 = '\0';
        }
        lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
        *(char *)(lVar18 + 0x98) = cVar3;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar18 + 0x7c) = 1;
        uVar11 = FUN_00190080(uVar25);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar3 = *(char *)(lVar27 + 0x67);
        *(undefined4 *)(lVar18 + 0x88) = uVar11;
        uVar25 = *(undefined8 *)(param_1 + 800);
        *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
        uVar11 = FUN_0018ffb0(param_1);
        bVar29 = *(byte *)(param_1 + 0x366);
        lVar18 = FUN_001dbcf0(uVar25,uVar11);
        cVar3 = *(char *)(lVar18 + (ulong)bVar29);
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        if (cVar3 == -0x80) {
          cVar3 = '\0';
        }
        lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
        *(char *)(lVar18 + 0x98) = cVar3;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar18 + 0x7c) = 1;
        uVar11 = FUN_00190080(uVar19);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar3 = *(char *)(lVar27 + 0x67);
        *(undefined4 *)(lVar18 + 0x88) = uVar11;
        uVar25 = *(undefined8 *)(param_1 + 800);
        *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
        uVar11 = FUN_0018ffb0(param_1);
        bVar29 = *(byte *)(param_1 + 0x366);
        lVar18 = FUN_001dbcf0(uVar25,uVar11);
        lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar3 = *(char *)(lVar18 + (ulong)bVar29);
        bVar29 = *(byte *)(lVar27 + 0x67);
        if (cVar3 == -0x80) {
          cVar3 = '\0';
        }
        lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
        *(char *)(lVar18 + 0x98) = cVar3;
        *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
        *(undefined4 *)(lVar18 + 0x7c) = 2;
        *(long *)(lVar18 + 0x88) = (long)iVar15;
        *(byte *)(lVar27 + 0x67) = bVar29 + 1;
      }
    }
  }
  else {
    if (iVar9 == 0x15e2) {
      uVar12 = 0x609;
      bVar6 = false;
      bVar8 = false;
      goto LAB_001d8e88;
    }
    if (iVar9 - 0x489U < 2) {
      uVar25 = FUN_0018ffd0(param_1,0);
      uVar19 = FUN_0018ffd0(param_1,2);
      FUN_0018ffd0(param_1,3);
      iVar15 = FUN_001900a0();
      FUN_0018ffd0(param_1,4);
      iVar13 = FUN_001900a0();
      iVar14 = FUN_00190080(uVar19);
      if ((iVar14 == 8) || (iVar14 = FUN_00190080(uVar19), iVar14 == 9)) {
        if (iVar15 != 0 && iVar15 <= iVar13) goto LAB_001d9e68;
        iVar14 = 0x20;
        if (iVar9 == 0x48a) {
          iVar14 = 0x40;
        }
        iVar9 = 0;
        if (iVar14 != 0) {
          iVar9 = (iVar14 - iVar15) / iVar14;
        }
        iVar9 = (iVar14 - iVar15) - iVar9 * iVar14;
        iVar15 = FUN_00190080(uVar25);
        FUN_001903f0(param_2,"bfc\t%s, ",
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar15 - 1) * 2));
        FUN_00190614(param_2,iVar9);
        FUN_00190370(param_2,", ");
        FUN_00190614(param_2,iVar13 + 1);
        uVar11 = FUN_001dbb40(&DAT_001fec80);
        FUN_0018ffa0(param_1,uVar11);
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          uVar25 = *(undefined8 *)(param_1 + 800);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)iVar9;
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)(iVar13 + 1);
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
        }
      }
      else if (iVar13 < iVar15) {
        iVar14 = 0x20;
        if (iVar9 == 0x48a) {
          iVar14 = 0x40;
        }
        iVar9 = 0;
        if (iVar14 != 0) {
          iVar9 = (iVar14 - iVar15) / iVar14;
        }
        iVar9 = (iVar14 - iVar15) - iVar9 * iVar14;
        iVar15 = FUN_00190080(uVar25);
        uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar15 - 1) * 2);
        iVar15 = FUN_00190080(uVar19);
        FUN_001903f0(param_2,"bfi\t%s, %s, ",&DAT_002b3bf0 + uVar4,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar15 - 1) * 2));
        FUN_00190614(param_2,iVar9);
        FUN_00190370(param_2,", ");
        FUN_00190614(param_2,iVar13 + 1);
        uVar11 = FUN_001dbb40(&DAT_001fec88);
        FUN_0018ffa0(param_1,uVar11);
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar19);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          uVar25 = *(undefined8 *)(param_1 + 800);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)iVar9;
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)(iVar13 + 1);
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
        }
      }
      else {
LAB_001d9e68:
        iVar9 = FUN_00190080(uVar25);
        uVar4 = *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2);
        iVar14 = FUN_00190080(uVar19);
        iVar9 = (iVar13 - iVar15) + 1;
        FUN_001903f0(param_2,"bfxil\t%s, %s, ",&DAT_002b3bf0 + uVar4,
                     &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar14 - 1) * 2));
        FUN_00190614(param_2,iVar15);
        FUN_00190370(param_2,", ");
        FUN_00190614(param_2,iVar9);
        uVar11 = FUN_001dbb40("bfxil");
        FUN_0018ffa0(param_1,uVar11);
        lVar18 = *(long *)(param_1 + 800);
        if (*(int *)(lVar18 + 0x60) != 0) {
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar27 = FUN_001dbcf0(lVar18,uVar11);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar25);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 1;
          uVar11 = FUN_00190080(uVar19);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar27 + 0x67);
          *(undefined4 *)(lVar18 + 0x88) = uVar11;
          uVar25 = *(undefined8 *)(param_1 + 800);
          *(char *)(lVar27 + 0x67) = cVar3 + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          uVar25 = *(undefined8 *)(param_1 + 800);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)iVar15;
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          bVar29 = *(byte *)(lVar27 + 0x67);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          lVar18 = lVar27 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
          *(char *)(lVar18 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 2;
          *(long *)(lVar18 + 0x88) = (long)iVar9;
          *(byte *)(lVar27 + 0x67) = bVar29 + 1;
        }
      }
      goto switchD_001d9694_caseD_662;
    }
    if (1 < iVar9 - 0xe5fU) {
      if (iVar9 - 0xe54U < 2) {
        FUN_0018ffd0(param_1,1);
        uVar24 = FUN_00190030();
        if ((uVar24 & 1) != 0) {
          FUN_0018ffd0(param_1,2);
          uVar24 = FUN_00190030();
          if ((uVar24 & 1) != 0) {
            if (iVar9 == 0xe55) {
              FUN_0018ffd0(param_1,2);
              iVar9 = 0x40;
              uVar24 = FUN_001900a0();
              FUN_0018ffd0(param_1,1);
              lVar18 = FUN_001900a0();
              uVar12 = 0x31;
              uVar20 = ~(lVar18 << (uVar24 & 0x3f));
            }
            else {
              FUN_0018ffd0(param_1,2);
              iVar9 = 0x20;
              uVar24 = FUN_001900a0();
              FUN_0018ffd0(param_1,1);
              lVar18 = FUN_001900a0();
              uVar20 = (ulong)~(uint)(lVar18 << (uVar24 & 0x3f));
              uVar12 = 0x11;
            }
            if (((0xffff < uVar20) && ((uVar20 & 0xffffffff0000ffff) != 0)) &&
               ((uVar12 < 0x21 ||
                (((uVar20 & 0xffff0000ffffffff) != 0 && ((uVar20 & 0xffffffffffff) != 0)))))) {
              uVar21 = (ulong)~(uint)uVar20;
              if (iVar9 != 0x20) {
                uVar21 = ~uVar20;
              }
              if ((uVar21 != 0 || (int)uVar24 == 0) &&
                 ((uVar21 & (0xffffL << (uVar24 & 0x3f) ^ 0xffffffffffffffffU)) == 0)) {
                FUN_0018ffd0(param_1,0);
                iVar15 = FUN_00190080();
                FUN_001903f0(param_2,"mov\t%s, ",
                             &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar15 - 1) * 2));
                lVar18 = (long)(uVar20 << ((ulong)(0x40 - iVar9) & 0x3f)) >>
                         ((ulong)(0x40 - iVar9) & 0x3f);
                FUN_001904e0(param_2,lVar18);
                lVar27 = *(long *)(param_1 + 800);
                if (*(int *)(lVar27 + 0x60) != 0) {
                  uVar11 = FUN_0018ffb0(param_1);
                  bVar29 = *(byte *)(param_1 + 0x366);
                  lVar27 = FUN_001dbcf0(lVar27,uVar11);
                  lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                  cVar3 = *(char *)(lVar27 + (ulong)bVar29);
                  if (cVar3 == -0x80) {
                    cVar3 = '\0';
                  }
                  lVar22 = lVar22 + (ulong)*(byte *)(lVar22 + 0x67) * 0x38;
                  *(char *)(lVar22 + 0x98) = cVar3;
                  *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
                  *(undefined4 *)(lVar22 + 0x7c) = 1;
                  FUN_0018ffd0(param_1,0);
                  lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                  bVar29 = *(byte *)(lVar27 + 0x67);
                  uVar11 = FUN_00190080();
                  lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                  *(undefined4 *)(lVar27 + (long)(int)(uint)bVar29 * 0x38 + 0x88) = uVar11;
                  cVar3 = *(char *)(lVar22 + 0x67);
                  lVar27 = lVar22 + (ulong)(byte)(cVar3 + 1) * 0x38;
                  *(undefined4 *)(lVar27 + 0x7c) = 2;
                  *(long *)(lVar27 + 0x88) = lVar18;
                  *(char *)(lVar22 + 0x67) = cVar3 + '\x02';
                }
                goto LAB_001da1b8;
              }
            }
          }
        }
        goto LAB_001d960c;
      }
      if ((iVar9 - 0xeabU & 0xfffffffd) == 0) {
        FUN_0018ffd0(param_1,1);
        iVar15 = FUN_00190080();
        if (iVar15 != 9) {
          FUN_0018ffd0(param_1,1);
          iVar15 = FUN_00190080();
          if (iVar15 != 8) goto LAB_001d960c;
        }
        FUN_0018ffd0(param_1,2);
        uVar24 = FUN_00190030();
        if ((uVar24 & 1) != 0) {
          iVar15 = 0x20;
          if (iVar9 == 0xead) {
            iVar15 = 0;
          }
          iVar13 = 0x20;
          if (iVar9 == 0xead) {
            iVar13 = 0x40;
          }
          FUN_0018ffd0(param_1,2);
          uVar24 = FUN_001900a0();
          uVar12 = (uint)uVar24 & 0x3f;
          uVar5 = ((uint)(uVar24 >> 0xc) & 1) << 6 | uVar12 ^ 0x3f;
          uVar10 = 0x1f - (int)LZCOUNT(uVar5);
          if (uVar5 == 0) {
            uVar10 = 0xffffffff;
          }
          uVar5 = 1 << (ulong)(uVar10 & 0x1f);
          uVar20 = (ulong)uVar5;
          uVar5 = uVar5 - 1;
          uVar10 = uVar5 & (uint)(uVar24 >> 6);
          uVar24 = (1L << ((ulong)((uVar12 & uVar5) + 1) & 0x3f)) - 1;
          uVar12 = 0;
          if (uVar10 != 0) {
            do {
              uVar12 = uVar12 + 1;
              uVar24 = (uVar24 & 1) << ((ulong)uVar5 & 0x3f) | uVar24 >> 1;
            } while (uVar12 != uVar10);
          }
          for (; (int)uVar20 != iVar13; uVar20 = (ulong)(uint)((int)uVar20 << 1)) {
            uVar24 = uVar24 | uVar24 << (uVar20 & 0x3f);
          }
          FUN_0018ffd0(param_1,0);
          iVar9 = FUN_00190080();
          lVar27 = (long)(uVar24 << iVar15) >> iVar15;
          FUN_001903f0(param_2,"mov\t%s, ",
                       &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
          FUN_001904e0(param_2,lVar27);
          lVar18 = *(long *)(param_1 + 800);
          if (*(int *)(lVar18 + 0x60) != 0) {
            uVar11 = FUN_0018ffb0(param_1);
            bVar29 = *(byte *)(param_1 + 0x366);
            lVar22 = FUN_001dbcf0(lVar18,uVar11);
            lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            cVar3 = *(char *)(lVar22 + (ulong)bVar29);
            if (cVar3 == -0x80) {
              cVar3 = '\0';
            }
            lVar18 = lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38;
            *(char *)(lVar18 + 0x98) = cVar3;
            *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
            *(undefined4 *)(lVar18 + 0x7c) = 1;
            FUN_0018ffd0(param_1,0);
            lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            bVar29 = *(byte *)(lVar18 + 0x67);
            uVar11 = FUN_00190080();
            lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            *(undefined4 *)(lVar18 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8 + 0x88) = uVar11;
            cVar3 = *(char *)(lVar22 + 0x67);
            bVar29 = cVar3 + 1;
            lVar18 = lVar22 + ((ulong)bVar29 * 8 - (ulong)bVar29) * 8;
            *(undefined4 *)(lVar18 + 0x7c) = 2;
            *(long *)(lVar18 + 0x88) = lVar27;
            *(char *)(lVar22 + 0x67) = cVar3 + '\x02';
          }
LAB_001da1b8:
          puVar28 = &DAT_001fa078;
          goto LAB_001d8e34;
        }
        goto LAB_001d960c;
      }
      if (iVar9 != 0x1583) goto LAB_001d960c;
      FUN_00190370(param_2,"tsb\tcsync");
      puVar28 = &DAT_001ff340;
LAB_001d8e34:
      iVar9 = FUN_001dbb40(puVar28);
      puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      puVar26 = PTR___stack_chk_guard_005ffe88;
      if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
        FUN_0018ffa0(param_1,iVar9,PTR___stack_chk_guard_005ffe88,0);
        return;
      }
      goto LAB_001dac64;
    }
    FUN_0018ffd0(param_1,1);
    uVar24 = FUN_00190030();
    if ((uVar24 & 1) != 0) {
      FUN_0018ffd0(param_1,2);
      uVar24 = FUN_00190030();
      if ((uVar24 & 1) != 0) {
        if (iVar9 == 0xe60) {
          FUN_0018ffd0(param_1,2);
          uVar20 = FUN_001900a0();
          FUN_0018ffd0(param_1,1);
          lVar18 = FUN_001900a0();
          uVar24 = lVar18 << (uVar20 & 0x3f);
          if ((int)uVar20 == 0 || uVar24 != 0) {
            lVar18 = 0;
            uVar21 = uVar24;
            goto LAB_001da140;
          }
        }
        else {
          FUN_0018ffd0(param_1,2);
          uVar20 = FUN_001900a0();
          FUN_0018ffd0(param_1,1);
          lVar18 = FUN_001900a0();
          uVar21 = lVar18 << (uVar20 & 0x3f);
          uVar24 = uVar21 & 0xffffffff;
          lVar18 = 0x20;
          if (uVar24 != 0 || (int)uVar20 == 0) {
LAB_001da140:
            if ((uVar24 & (0xffffL << (uVar20 & 0x3f) ^ 0xffffffffffffffffU)) == 0) {
              FUN_0018ffd0(param_1,0);
              iVar9 = FUN_00190080();
              lVar18 = (long)(uVar21 << lVar18) >> lVar18;
              FUN_001903f0(param_2,"mov\t%s, ",
                           &DAT_002b3bf0 + *(ushort *)(&DAT_002b4900 + (ulong)(iVar9 - 1) * 2));
              FUN_001904e0(param_2,lVar18);
              lVar27 = *(long *)(param_1 + 800);
              if (*(int *)(lVar27 + 0x60) != 0) {
                uVar11 = FUN_0018ffb0(param_1);
                bVar29 = *(byte *)(param_1 + 0x366);
                lVar27 = FUN_001dbcf0(lVar27,uVar11);
                lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                cVar3 = *(char *)(lVar27 + (ulong)bVar29);
                if (cVar3 == -0x80) {
                  cVar3 = '\0';
                }
                lVar22 = lVar22 + (ulong)*(byte *)(lVar22 + 0x67) * 0x38;
                *(char *)(lVar22 + 0x98) = cVar3;
                *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
                *(undefined4 *)(lVar22 + 0x7c) = 1;
                FUN_0018ffd0(param_1,0);
                lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                bVar29 = *(byte *)(lVar27 + 0x67);
                uVar11 = FUN_00190080();
                lVar22 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar27 + (long)(int)(uint)bVar29 * 0x38 + 0x88) = uVar11;
                cVar3 = *(char *)(lVar22 + 0x67);
                lVar27 = lVar22 + (ulong)(byte)(cVar3 + 1) * 0x38;
                *(undefined4 *)(lVar27 + 0x7c) = 2;
                *(long *)(lVar27 + 0x88) = lVar18;
                *(char *)(lVar22 + 0x67) = cVar3 + '\x02';
              }
              goto LAB_001da1b8;
            }
          }
        }
      }
    }
LAB_001d960c:
    *(undefined8 *)(param_1 + 0x3b0) = param_3;
    lVar18 = FUN_001ce770(param_1,param_2,param_3);
    if (lVar18 == 0) {
      iVar9 = 0;
      puVar28 = PTR___stack_chk_guard_005ffe88;
      puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
      if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
        FUN_001d0080(param_1,param_2,0);
        return;
      }
      goto LAB_001dac64;
    }
    uVar11 = FUN_001dbb40();
    FUN_0018ffa0(param_1,uVar11);
    (**(code **)PTR_PTR_005fff60)(lVar18);
    uVar12 = FUN_0018ffb0(param_1);
    puVar28 = PTR___stack_chk_guard_005ffe88;
    if (uVar12 < 0xbe1) {
      if (uVar12 < 0xbd2) {
        if (uVar12 < 0x6c1) {
          if (uVar12 < 0x652) {
            if ((uVar12 == 0x42b) || (uVar12 == 0x434)) goto switchD_001d9694_caseD_6b3;
          }
          else {
            switch(uVar12) {
            case 0x652:
            case 0x656:
            case 0x65a:
            case 0x65e:
            case 0x68c:
            case 0x690:
switchD_001d9694_caseD_652:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = 4;
              }
              break;
            case 0x653:
            case 0x657:
            case 0x65b:
            case 0x65f:
            case 0x68d:
            case 0x691:
              goto switchD_001d9694_caseD_653;
            case 0x654:
            case 0x658:
            case 0x65c:
            case 0x660:
            case 0x68e:
            case 0x692:
              goto switchD_001d9694_caseD_654;
            case 0x655:
            case 0x659:
            case 0x65d:
            case 0x661:
            case 0x68f:
            case 0x693:
              goto switchD_001d9694_caseD_655;
            case 0x694:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                uVar11 = 4;
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 4;
                if (*(char *)(lVar18 + 0x67) == '\x01') {
                  FUN_0018ffd0(param_1);
                  iVar9 = FUN_00190080();
                  iVar9 = iVar9 + -0xec;
                  puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
                  puVar26 = PTR___stack_chk_guard_005ffe88;
                  if (puVar28 != (undefined *)0x0) goto LAB_001dac64;
                  goto LAB_001dabe8;
                }
LAB_001dabb0:
                *(undefined4 *)(lVar18 + 0xa4) = uVar11;
              }
              break;
            case 0x695:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                uVar11 = 0xd;
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 0xd;
                if (*(char *)(lVar18 + 0x67) == '\x01') {
                  FUN_0018ffd0(param_1);
                  iVar9 = FUN_00190080();
                  iVar9 = iVar9 + -0xcc;
                  puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
joined_r0x001dad18:
                  puVar26 = PTR___stack_chk_guard_005ffe88;
                  if (puVar28 == (undefined *)0x0) {
LAB_001dabe8:
                    FUN_001dbc04(param_1,iVar9,PTR___stack_chk_guard_005ffe88,0);
                    return;
                  }
                  goto LAB_001dac64;
                }
                goto LAB_001dabb0;
              }
              break;
            case 0x696:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                uVar11 = 8;
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 8;
                if (*(char *)(lVar18 + 0x67) == '\x01') {
                  FUN_0018ffd0(param_1);
                  iVar9 = FUN_00190080();
                  iVar9 = iVar9 + -0xac;
                  puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
                  goto joined_r0x001dad18;
                }
                goto LAB_001dabb0;
              }
              break;
            case 0x697:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                uVar11 = 0xe;
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 0xe;
                if (*(char *)(lVar18 + 0x67) == '\x01') {
                  FUN_0018ffd0(param_1);
                  iVar9 = FUN_00190080();
                  iVar9 = iVar9 + -0x7c;
                  puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
                  goto joined_r0x001dad18;
                }
                goto LAB_001dabb0;
              }
              break;
            case 0x698:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                uVar11 = 0xb;
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 0xb;
                if (*(char *)(lVar18 + 0x67) == '\x01') {
                  FUN_0018ffd0(param_1);
                  iVar9 = FUN_00190080();
                  iVar9 = iVar9 + -0x5c;
                  puVar28 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
                  goto joined_r0x001dad18;
                }
                goto LAB_001dabb0;
              }
              break;
            case 0x6b3:
            case 0x6c0:
switchD_001d9694_caseD_6b3:
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                *(undefined4 *)(lVar18 + 0x6c) = 4;
                *(undefined4 *)(lVar18 + 0xdc) = 4;
              }
            }
          }
        }
        else if (uVar12 == 0xb50) {
LAB_001db1d8:
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
            lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            *(undefined4 *)(lVar18 + 0x6c) = 0xd;
            *(undefined4 *)(lVar18 + 0xa4) = 0xd;
          }
        }
        else if (uVar12 < 0xb51) {
          if (uVar12 == 0xb4c) {
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(undefined4 *)(lVar18 + 0x6c) = 8;
              *(undefined4 *)(lVar18 + 0xa4) = 8;
            }
          }
          else if (uVar12 < 0xb4d) {
            if (uVar12 == 0x899) goto switchD_001d9694_caseD_653;
            if (uVar12 < 0x89a) {
              if (uVar12 != 0x7b3) {
                if (uVar12 == 0x7b4) goto switchD_001d9694_caseD_655;
                if (uVar12 != 0x7b2) goto switchD_001d9694_caseD_662;
                goto switchD_001d9694_caseD_653;
              }
            }
            else {
              if (uVar12 == 0x89b) {
switchD_001d9694_caseD_655:
                if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
                  *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = 0xb;
                }
                goto switchD_001d9694_caseD_662;
              }
              if ((uVar12 != 0xb4b) && (uVar12 != 0x89a)) goto switchD_001d9694_caseD_662;
            }
switchD_001d9694_caseD_654:
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = 8;
            }
          }
          else if (uVar12 == 0xb4e) {
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(undefined4 *)(lVar18 + 0x6c) = 0xb;
              *(undefined4 *)(lVar18 + 0xa4) = 0xb;
            }
          }
          else {
            if (uVar12 != 0xb4f) goto switchD_001d9694_caseD_655;
switchD_001d9694_caseD_653:
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = 0xd;
            }
          }
        }
        else if (uVar12 < 0xb7d) {
          if (uVar12 == 0xb51) goto switchD_001d9694_caseD_652;
          uVar24 = 1L << ((ulong)(uVar12 - 0xb52) & 0x3f);
          if ((uVar24 & 0x45100000000) != 0) {
LAB_001db358:
            iVar9 = 0;
            puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                (undefined *)0x0) {
              uVar25 = 0x20;
              goto LAB_001da548;
            }
            goto LAB_001dac64;
          }
          if ((uVar24 & 0x10440000000) != 0) {
LAB_001dae74:
            iVar9 = 0;
            puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                (undefined *)0x0) {
              uVar25 = 0x40;
LAB_001da548:
              FUN_001dbcb0(param_1,uVar25,0);
              return;
            }
            goto LAB_001dac64;
          }
          if ((uVar24 & 1) != 0) goto LAB_001db258;
        }
        else if (uVar12 - 0xb7e < 0x17) {
          uVar24 = 1L << ((ulong)(uVar12 - 0xb7e) & 0x3f);
          if ((uVar24 & 0x441100) != 0) {
LAB_001db220:
            iVar9 = 0;
            puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                (undefined *)0x0) {
              uVar25 = 0x10;
              goto LAB_001da548;
            }
            goto LAB_001dac64;
          }
          if ((uVar24 & 0x114400) != 0) goto LAB_001db0ec;
          if ((uVar24 & 1) != 0) goto LAB_001dae74;
        }
      }
      else {
        uVar24 = 1L << ((ulong)(uVar12 - 0xbd2) & 0x3f);
        if ((uVar24 & 0x4411) != 0) {
          iVar9 = 0;
          puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
          if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) != (undefined *)0x0)
          goto LAB_001dac64;
          uVar25 = 0x30;
          goto LAB_001da548;
        }
        if ((uVar24 & 0x1144) != 0) {
          iVar9 = 0;
          puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
          if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0)
          {
            uVar25 = 0x18;
            goto LAB_001da548;
          }
          goto LAB_001dac64;
        }
      }
    }
    else if (uVar12 == 0xeaf) {
LAB_001db258:
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar18 + 0x6c) = 4;
        *(undefined4 *)(lVar18 + 0xa4) = 4;
      }
    }
    else if (uVar12 < 0xeb0) {
      if (uVar12 == 0xc06) {
        iVar9 = 0;
        puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
        if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
          uVar25 = 1;
          goto LAB_001da548;
        }
        goto LAB_001dac64;
      }
      if (uVar12 < 0xc07) {
        if (uVar12 < 0xc01) {
          if (uVar12 != 0xbe1) {
            uVar24 = 1L << ((ulong)(uVar12 - 0xbe2) & 0x3f);
            if ((uVar24 & 0x4411) != 0) goto LAB_001db358;
            if ((uVar24 & 0x1144) != 0) goto LAB_001db220;
            if (uVar12 == 0xc00) {
              iVar9 = 0;
              puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
              if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                  (undefined *)0x0) {
                uVar25 = 2;
                goto LAB_001da548;
              }
              goto LAB_001dac64;
            }
          }
        }
        else {
          if (uVar12 == 0xc02) {
            iVar9 = 0;
            puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                (undefined *)0x0) {
              uVar25 = 4;
              goto LAB_001da548;
            }
            goto LAB_001dac64;
          }
          if (uVar12 == 0xc04) {
LAB_001db0ec:
            iVar9 = 0;
            puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
            if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) ==
                (undefined *)0x0) {
              uVar25 = 8;
              goto LAB_001da548;
            }
            goto LAB_001dac64;
          }
        }
      }
      else if (uVar12 == 0xea2) {
LAB_001db18c:
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar18 + 0x6c) = 1;
          *(undefined4 *)(lVar18 + 0xa4) = 1;
        }
      }
      else if (uVar12 < 0xea3) {
        if ((uVar12 == 0xe69) && (lVar18 = *(long *)(param_1 + 800), *(int *)(lVar18 + 0x60) != 0))
        {
          *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x67) = 2;
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(lVar18,uVar11);
          uVar25 = *(undefined8 *)(param_1 + 800);
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          *(char *)(lVar27 + (ulong)*(byte *)(lVar27 + 0x67) * 0x38 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          uVar11 = FUN_0018ffb0(param_1);
          bVar29 = *(byte *)(param_1 + 0x366);
          lVar18 = FUN_001dbcf0(uVar25,uVar11);
          cVar3 = *(char *)(lVar18 + (ulong)bVar29);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (cVar3 == -0x80) {
            cVar3 = '\0';
          }
          *(char *)(lVar18 + (ulong)*(byte *)(lVar18 + 0x67) * 0x38 + 0x98) = cVar3;
          *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
          *(undefined4 *)(lVar18 + 0x7c) = 0x45;
          *(undefined4 *)(lVar18 + 0x88) = 0xda12;
          FUN_0018ffd0(param_1,0);
          FUN_001900a0();
          lVar18 = FUN_001e7990();
          lVar27 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(uint *)(lVar27 + 0x80) = (uint)*(ushort *)(lVar18 + 8);
          *(undefined4 *)(lVar27 + 0xb4) = 2;
          FUN_0018ffd0(param_1,1);
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          uVar25 = FUN_001900a0();
          *(undefined8 *)(lVar18 + 0xc0) = uVar25;
        }
      }
      else {
        if (uVar12 == 0xea3) goto LAB_001db334;
        if (uVar12 == 0xeaa) goto LAB_001db258;
      }
    }
    else if (uVar12 == 0x1013) {
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar18 + 0x6c) = 8;
        *(undefined4 *)(lVar18 + 0xdc) = 8;
      }
    }
    else if (uVar12 < 0x1014) {
      if (uVar12 == 0xebb) {
LAB_001db334:
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar18 + 0x6c) = 2;
          *(undefined4 *)(lVar18 + 0xa4) = 2;
        }
      }
      else if (uVar12 < 0xebc) {
        if (uVar12 == 0xeb5) goto LAB_001db1d8;
        if (uVar12 == 0xeb6) goto LAB_001db18c;
      }
      else if (uVar12 == 0x1012) {
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          *(undefined4 *)(lVar18 + 0x6c) = 0xd;
          *(undefined4 *)(lVar18 + 0xdc) = 0xd;
        }
      }
      else if (0x100f < uVar12) goto switchD_001d9694_caseD_6b3;
    }
    else {
      if (uVar12 == 0x16a5) {
        iVar9 = 0;
        puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
        if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
          uVar25 = 0xb;
LAB_001db2c4:
          FUN_001dbc40(param_1,uVar25,0);
          return;
        }
        goto LAB_001dac64;
      }
      if (uVar12 == 0x16a7) {
        iVar9 = 0;
        puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
        if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
          uVar25 = 0xd;
          goto LAB_001db2c4;
        }
        goto LAB_001dac64;
      }
      if ((uVar12 == 0x1014) && (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0)) {
        lVar18 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar18 + 0x6c) = 0xb;
        *(undefined4 *)(lVar18 + 0xdc) = 0xb;
      }
    }
  }
switchD_001d9694_caseD_662:
  iVar9 = 0;
  puVar28 = PTR___stack_chk_guard_005ffe88;
  puVar26 = (undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  if ((undefined *)(local_68 - *(long *)PTR___stack_chk_guard_005ffe88) == (undefined *)0x0) {
    return;
  }
LAB_001dac64:
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(puVar28,iVar9,puVar26);
}

