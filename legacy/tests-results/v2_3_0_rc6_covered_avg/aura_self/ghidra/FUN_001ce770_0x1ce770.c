
undefined1 * FUN_001ce770(long param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  uint uVar14;
  undefined8 uVar15;
  byte *pbVar16;
  long lVar17;
  long lVar18;
  undefined8 *puVar19;
  byte bVar20;
  ulong uVar21;
  char *pcVar22;
  int *piVar23;
  undefined1 *puVar24;
  ulong uVar25;
  ulong uVar26;
  uint *puVar27;
  undefined1 *puVar28;
  ulong uVar29;
  byte *pbVar30;
  ulong uVar31;
  undefined1 auStack_88 [32];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar9 = FUN_0018ffb0(param_1,0);
  iVar11 = 0;
  iVar12 = 0x3e3;
  piVar23 = &DAT_002d3a58;
  while (iVar9 != iVar12) {
    iVar11 = iVar11 + 1;
    if (iVar11 == 0x32b) {
      if (iVar9 != 0x3e3) goto LAB_001ce8c8;
      iVar11 = 0;
      break;
    }
    iVar12 = *piVar23;
    piVar23 = piVar23 + 2;
  }
  uVar2 = (&DAT_002d3a54)[(long)iVar11 * 4];
  uVar29 = (ulong)uVar2;
  uVar14 = (uint)(ushort)(&DAT_002d3a56)[(long)iVar11 * 4] + (uint)uVar2;
  if (uVar2 < uVar14) {
    puVar27 = (uint *)(&DAT_002d0c74 + (ulong)uVar2 * 0xc);
    do {
      uVar10 = FUN_0018ffe0(param_1);
      if (uVar10 != (byte)puVar27[1]) break;
      bVar20 = *(byte *)((long)puVar27 + 5);
      uVar10 = *puVar27;
      if (bVar20 + uVar10 <= uVar10) {
LAB_001cecd8:
        if (*(uint *)(&DAT_002d0c70 +
                     ((-(uVar29 >> 0x1f) & 0xfffffffe00000000 | uVar29 << 1) + (long)(int)uVar29) *
                     4) != 0xffffffff) {
          pbVar16 = (byte *)FUN_00190780(&DAT_002c3700 +
                                         *(uint *)(&DAT_002d0c70 +
                                                  ((-(uVar29 >> 0x1f) & 0xfffffffe00000000 |
                                                   uVar29 << 1) + (long)(int)uVar29) * 4));
          puVar28 = (undefined1 *)FUN_00190780();
          if ((0x24 < *pbVar16) ||
             (uVar29 = 0, puVar24 = puVar28, pbVar30 = pbVar16,
             (-0x1100000202 >> ((ulong)*pbVar16 & 0x3f) & 1U) != 0)) {
            uVar29 = 0;
            do {
              do {
                uVar29 = (ulong)((int)uVar29 + 1);
                pbVar30 = pbVar16 + uVar29;
              } while (0x24 < pbVar16[uVar29]);
            } while ((-0x1100000202 >> ((ulong)pbVar16[uVar29] & 0x3f) & 1U) != 0);
            puVar24 = puVar28 + uVar29;
          }
          *puVar24 = 0;
          FUN_00190370(param_2,puVar28);
          bVar20 = *pbVar30;
          if (bVar20 == 0) goto LAB_001cedf8;
          if (bVar20 == 0x20 || bVar20 == 9) {
            uVar29 = (ulong)((int)uVar29 + 1);
            pbVar30 = pbVar16 + uVar29;
            FUN_00190370(param_2,&DAT_001fe568);
          }
          bVar20 = *pbVar30;
          bVar8 = 0;
          do {
            while( true ) {
              iVar11 = (int)uVar29;
              uVar31 = (ulong)(iVar11 + 1);
              if (bVar20 != 0x24) {
                if (bVar20 == 0x5b) {
                  lVar17 = *(long *)(param_1 + 800);
                  if (pbVar16[iVar11 - 1] == 0x20) {
                    *(undefined1 *)(lVar17 + 0x6c) = 1;
                    if (*(int *)(lVar17 + 0x60) == 3) {
                      uVar13 = FUN_0018ffb0(param_1);
                      bVar20 = *(byte *)(param_1 + 0x366);
                      lVar18 = FUN_001dbcf0(lVar17,uVar13);
                      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                      cVar1 = *(char *)(lVar18 + (ulong)bVar20);
                      if (cVar1 == -0x80) {
                        cVar1 = '\0';
                      }
                      lVar17 = lVar17 + (ulong)*(byte *)(lVar17 + 0x67) * 0x38;
                      *(char *)(lVar17 + 0x98) = cVar1;
                      *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
                      *(undefined4 *)(lVar17 + 0x7c) = 3;
                      *(undefined8 *)(lVar17 + 0x88) = 0;
                      *(undefined4 *)(lVar17 + 0x90) = 0;
                      bVar20 = pbVar16[uVar29];
                    }
                    else {
                      bVar20 = pbVar16[uVar29];
                    }
                  }
                  else {
                    *(undefined1 *)(lVar17 + 0x6d) = 1;
                    if (*(int *)(lVar17 + 0x60) == 3) {
                      bVar8 = 1;
                      uVar26 = (ulong)(*(byte *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x67
                                                ) - 1);
                      FUN_0018ffd0(param_1,uVar26);
                      uVar13 = FUN_00190080();
                      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0) + uVar26 * 0x38;
                      *(undefined4 *)(lVar17 + 0x7c) = 0x48;
                      *(undefined4 *)(lVar17 + 0x88) = uVar13;
                      *(undefined8 *)(lVar17 + 0x8c) = 0;
                      bVar20 = pbVar16[uVar29];
                    }
                    else {
                      bVar20 = pbVar16[uVar29];
                      bVar8 = 1;
                    }
                  }
                }
                else if (bVar20 == 0x5d) {
                  lVar17 = *(long *)(param_1 + 800);
                  if ((bVar8 & 1) == 0) {
                    bVar20 = *(byte *)(lVar17 + 0x6d);
                    if ((bVar20 & 1) == 0) {
                      *(undefined1 *)(lVar17 + 0x6c) = 0;
                      bVar8 = bVar20;
                      if (*(int *)(lVar17 + 0x60) == 3) {
                        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
                        *(char *)(lVar17 + 0x67) = *(char *)(lVar17 + 0x67) + '\x01';
                        bVar20 = pbVar16[uVar29];
                      }
                      else {
                        bVar20 = pbVar16[uVar29];
                      }
                    }
                    else {
                      *(undefined1 *)(lVar17 + 0x6d) = 0;
                      bVar20 = pbVar16[uVar29];
                    }
                  }
                  else {
                    *(undefined1 *)(lVar17 + 0x6d) = 0;
                    bVar20 = pbVar16[uVar29];
                    bVar8 = 0;
                  }
                }
                FUN_001903d0(param_2,bVar20);
                goto LAB_001cedb8;
              }
              uVar14 = iVar11 + 2;
              if (pbVar16[uVar31] == 0xff) break;
              FUN_001ccc60(param_1,pbVar16[uVar31] - 1,param_2);
              bVar20 = pbVar16[uVar14];
              uVar29 = (ulong)uVar14;
              if (bVar20 == 0) goto LAB_001cedf8;
            }
            bVar20 = pbVar16[uVar14];
            iVar12 = bVar20 - 1;
            switch(pbVar16[iVar11 + 3]) {
            case 1:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cded0(param_1,iVar12,param_2);
              break;
            case 2:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cdbe4(param_1,iVar12,param_2);
              break;
            case 3:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cbc00(param_1,iVar12,param_2);
              break;
            case 4:
            case 8:
            case 10:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001ce2b0(param_1,iVar12,param_2);
              break;
            case 5:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001ce3f4(param_1,iVar12,param_2);
              break;
            case 6:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,0x62);
              break;
            case 7:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,0);
              break;
            case 9:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,0x68);
              break;
            case 0xb:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,0x73);
              break;
            case 0xc:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cbf04(param_1,iVar12,param_2);
              break;
            case 0xd:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cbff0(param_1,iVar12,param_2);
              break;
            case 0xe:
              FUN_0018ffd0(param_1,iVar12);
              uVar14 = FUN_001900a0();
              puVar19 = (undefined8 *)FUN_001e7924();
              if (puVar19 != (undefined8 *)0x0) goto LAB_001cf738;
              goto LAB_001cfd08;
            case 0xf:
            case 0x12:
            case 0x13:
              FUN_0018ffd0(param_1,iVar12);
              iVar12 = FUN_001900a0();
              FUN_0018ffd0(param_1,bVar20);
              uVar14 = FUN_001900a0();
              if ((iVar12 == 0) && ((uVar14 & 0x3f) != 0)) {
LAB_001cff64:
                uVar31 = (ulong)(iVar11 + 4);
                FUN_001906d0(param_2,0);
                FUN_001cdbe4(param_1,bVar20,param_2);
              }
              else {
                uVar31 = (ulong)(iVar11 + 4);
                FUN_001906d0(param_2,iVar12 << (ulong)(uVar14 & 0x1f));
              }
              break;
            case 0x10:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,100);
              break;
            case 0x11:
              FUN_0018ffd0(param_1,iVar12);
              iVar12 = FUN_001900a0();
              FUN_0018ffd0(param_1,(uint)bVar20);
              uVar14 = FUN_001900a0();
              if ((iVar12 == 0) && ((uVar14 & 0x3f) != 0)) goto LAB_001cff64;
              uVar31 = (ulong)(iVar11 + 4);
              FUN_00190540(param_2,iVar12 << (ulong)(uVar14 & 0x1f));
              break;
            case 0x14:
              FUN_0018ffd0(param_1,iVar12);
              uVar14 = FUN_001900a0();
              pcVar22 = (char *)0x0;
              switch(uVar14 ^ 1) {
              case 0:
                pcVar22 = "eq";
                break;
              case 1:
                pcVar22 = "ne";
                break;
              case 2:
                pcVar22 = "hs";
                break;
              case 3:
                pcVar22 = "lo";
                break;
              case 4:
                pcVar22 = "mi";
                break;
              case 5:
                pcVar22 = "pl";
                break;
              case 6:
                pcVar22 = "vs";
                break;
              case 7:
                pcVar22 = "vc";
                break;
              case 8:
                pcVar22 = "hi";
                break;
              case 9:
                pcVar22 = "ls";
                break;
              case 10:
                pcVar22 = "ge";
                break;
              case 0xb:
                pcVar22 = "lt";
                break;
              case 0xc:
                pcVar22 = "gt";
                break;
              case 0xd:
                pcVar22 = "le";
                break;
              case 0xe:
                pcVar22 = "al";
                break;
              case 0xf:
                pcVar22 = "nv";
              }
              FUN_00190370(param_2,pcVar22);
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto switchD_001cf3d0_default;
              uVar31 = (ulong)(iVar11 + 4);
              *(uint *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) = (uVar14 ^ 1) + 1;
              break;
            case 0x15:
              FUN_0018ffd0(param_1,iVar12);
              uVar29 = FUN_001900a0();
              uVar14 = (uint)uVar29 & 0x3f;
              uVar3 = 0x1f - (int)LZCOUNT(((uint)(uVar29 >> 0xc) & 1) << 6 | uVar14 ^ 0x3f);
              uVar6 = 1 << (ulong)(uVar3 & 0x1f);
              uVar4 = uVar6 - 1;
              uVar10 = uVar4 & (uint)(uVar29 >> 6);
              uVar29 = (1L << ((ulong)((uVar14 & uVar4) + 1) & 0x3f)) - 1;
              if (uVar10 != 0) {
                uVar14 = 0;
                do {
                  uVar14 = uVar14 + 1;
                  uVar29 = (uVar29 & 1) << ((ulong)uVar4 & 0x3f) | uVar29 >> 1;
                } while (uVar14 != uVar10);
              }
              if (uVar3 != 6) {
                do {
                  uVar31 = (ulong)uVar6;
                  uVar6 = uVar6 << 1;
                  uVar29 = uVar29 | uVar29 << (uVar31 & 0x3f);
                } while (uVar6 != 0x40);
              }
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001906d0(param_2,(int)(short)uVar29);
              break;
            case 0x16:
              FUN_0018ffd0(param_1,iVar12);
              uVar29 = FUN_001900a0();
              uVar14 = (uint)uVar29 & 0x3f;
              uVar3 = 0x1f - (int)LZCOUNT(((uint)(uVar29 >> 0xc) & 1) << 6 | uVar14 ^ 0x3f);
              uVar6 = 1 << (ulong)(uVar3 & 0x1f);
              uVar4 = uVar6 - 1;
              uVar10 = uVar4 & (uint)(uVar29 >> 6);
              uVar29 = (1L << ((ulong)((uVar14 & uVar4) + 1) & 0x3f)) - 1;
              if (uVar10 != 0) {
                uVar14 = 0;
                do {
                  uVar14 = uVar14 + 1;
                  uVar29 = (uVar29 & 1) << ((ulong)uVar4 & 0x3f) | uVar29 >> 1;
                } while (uVar14 != uVar10);
              }
              if (uVar3 != 6) {
                do {
                  uVar31 = (ulong)uVar6;
                  uVar6 = uVar6 << 1;
                  uVar29 = uVar29 | uVar29 << (uVar31 & 0x3f);
                } while (uVar6 != 0x40);
              }
              if ((uVar29 & 0xffff0000) != 0) goto LAB_001cf9d0;
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001906d0(param_2,(int)(short)uVar29);
              break;
            case 0x17:
              FUN_0018ffd0(param_1,iVar12);
              uVar29 = FUN_001900a0();
              uVar14 = (uint)uVar29 & 0x3f;
              uVar3 = 0x1f - (int)LZCOUNT(((uint)(uVar29 >> 0xc) & 1) << 6 | uVar14 ^ 0x3f);
              uVar6 = 1 << (ulong)(uVar3 & 0x1f);
              uVar4 = uVar6 - 1;
              uVar10 = uVar4 & (uint)(uVar29 >> 6);
              uVar29 = (1L << ((ulong)((uVar14 & uVar4) + 1) & 0x3f)) - 1;
              if (uVar10 != 0) {
                uVar14 = 0;
                do {
                  uVar14 = uVar14 + 1;
                  uVar29 = (uVar29 & 1) << ((ulong)uVar4 & 0x3f) | uVar29 >> 1;
                } while (uVar14 != uVar10);
              }
              if (uVar3 != 6) {
                do {
                  uVar31 = (ulong)uVar6;
                  uVar6 = uVar6 << 1;
                  uVar29 = uVar29 | uVar29 << (uVar31 & 0x3f);
                } while (uVar6 != 0x40);
              }
LAB_001cf9d0:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_00190540(param_2,uVar29);
              break;
            case 0x18:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc1d0(param_1,iVar12,param_2,8);
              break;
            case 0x19:
              FUN_00190370(param_2,&DAT_001fdf80);
              FUN_0018ffd0(param_1,iVar12);
              uVar13 = FUN_001900a0();
              FUN_00190670(param_2,uVar13);
              FUN_00190370(param_2,&DAT_001fe598);
              if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto switchD_001cf3d0_default;
              FUN_0018ffd0(param_1,iVar12);
              uVar31 = (ulong)(iVar11 + 4);
              uVar13 = FUN_001900a0();
              lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              uVar14 = *(byte *)(lVar17 + 0x67) - 1;
              *(undefined4 *)
               (lVar17 + ((-(ulong)(uVar14 >> 0x1f) & 0xfffffff800000000 | (ulong)uVar14 << 3) -
                         (long)(int)uVar14) * 8 + 0x68) = uVar13;
              break;
            case 0x1a:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc1d0(param_1,iVar12,param_2,0x40);
              break;
            case 0x1b:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc1d0(param_1,iVar12,param_2,0x10);
              break;
            case 0x1c:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc0c4(param_1,iVar12,param_2,0x71);
              break;
            case 0x1d:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc1d0(param_1,iVar12,param_2,0x80);
              break;
            case 0x1e:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc1d0(param_1,iVar12,param_2,0x20);
              break;
            case 0x1f:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc300(param_1,iVar12,param_2,0);
              break;
            case 0x20:
              FUN_0018ffd0(param_1,iVar12);
              uVar15 = FUN_001900a0();
              FUN_00190564(param_2,uVar15);
              if ((*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) ||
                 ((*(byte *)(*(long *)(param_1 + 800) + 0x6d) & 1) == 0))
              goto switchD_001cf3d0_default;
              uVar31 = (ulong)(iVar11 + 4);
              lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(int *)(lVar17 + (long)(int)(*(byte *)(lVar17 + 0x67) - 1) * 0x38 + 0x90) =
                   (int)uVar15;
              break;
            case 0x21:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc300(param_1,iVar12,param_2,1);
              break;
            case 0x22:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc480(param_1,iVar12,param_2);
              break;
            case 0x23:
            case 0x33:
              FUN_001907d0(auStack_88,0x20,&DAT_001ffc30,100);
              uVar15 = *(undefined8 *)(param_1 + 0x3b0);
              goto LAB_001cf648;
            case 0x24:
            case 0x32:
              FUN_001907d0(auStack_88,0x20,&DAT_001ffc30,0x73);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),0xb);
              break;
            case 0x25:
              FUN_0018ffd0(param_1,iVar12);
              uVar14 = FUN_001900a0();
              uVar14 = uVar14 ^ 0x20;
              puVar19 = (undefined8 *)FUN_001e79f4(uVar14);
              goto joined_r0x001cfd04;
            case 0x26:
              FUN_0018ffd0(param_1,iVar12);
              uVar14 = FUN_001900a0();
              puVar19 = (undefined8 *)FUN_001e77c0();
joined_r0x001cfd04:
              if (puVar19 == (undefined8 *)0x0) {
LAB_001cfd08:
                uVar31 = (ulong)(iVar11 + 4);
                FUN_001906d0(param_2,uVar14);
              }
              else {
LAB_001cf738:
                uVar31 = (ulong)(iVar11 + 4);
                FUN_00190370(param_2,*puVar19);
              }
              break;
            case 0x27:
            case 0x31:
              FUN_001907d0(auStack_88,0x20,&DAT_001ffc30,0x68);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),8);
              break;
            case 0x28:
            case 0x34:
              FUN_001907d0(auStack_88,0x20,&DAT_001ffc30,0x62);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),4);
              break;
            case 0x29:
              FUN_001907d0(auStack_88,0x20,".%u%c",0x10,0x62);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),1);
              break;
            case 0x2a:
              FUN_001907d0(auStack_88,0x20,".%u%c",1,100);
              uVar15 = *(undefined8 *)(param_1 + 0x3b0);
LAB_001cf648:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,uVar15,0xd);
              break;
            case 0x2b:
              FUN_001907d0(auStack_88,0x20,".%u%c",2,100);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),0xc);
              break;
            case 0x2c:
              FUN_001907d0(auStack_88,0x20,".%u%c",2,0x73);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),10);
              break;
            case 0x2d:
              FUN_001907d0(auStack_88,0x20,".%u%c",4,0x68);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),6);
              break;
            case 0x2e:
              FUN_001907d0(auStack_88,0x20,".%u%c",4,0x73);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),9);
              break;
            case 0x2f:
              FUN_001907d0(auStack_88,0x20,".%u%c",8,0x62);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),2);
              break;
            case 0x30:
              FUN_001907d0(auStack_88,0x20,".%u%c",8,0x68);
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cc5a4(param_1,iVar12,param_2,auStack_88,*(undefined8 *)(param_1 + 0x3b0),5);
              break;
            case 0x35:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cd8e4(param_1,iVar12,param_2);
              break;
            case 0x36:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001cbff0(param_1,iVar12,param_2);
              break;
            case 0x37:
              FUN_0018ffd0(param_1,iVar12);
              FUN_001900a0();
              puVar19 = (undefined8 *)FUN_001e76f0();
              if (puVar19 != (undefined8 *)0x0) goto LAB_001cf738;
              uVar31 = (ulong)(iVar11 + 4);
              break;
            case 0x38:
              FUN_0018ffd0(param_1,iVar12);
              FUN_001900a0();
              puVar19 = (undefined8 *)FUN_001e7754();
              if (puVar19 != (undefined8 *)0x0) goto LAB_001cf738;
            default:
switchD_001cf3d0_default:
              uVar31 = (ulong)(iVar11 + 4);
              break;
            case 0x39:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001ce130(param_1,iVar12,param_2);
              break;
            case 0x3a:
              uVar31 = (ulong)(iVar11 + 4);
              FUN_001ccb80(param_1,iVar12,param_2);
            }
LAB_001cedb8:
            bVar20 = pbVar16[uVar31];
            uVar29 = uVar31;
          } while (bVar20 != 0);
LAB_001cedf8:
          (**(code **)PTR_PTR_005fff60)(pbVar16);
          goto LAB_001ce8cc;
        }
        break;
      }
      piVar23 = (int *)(&DAT_002c7420 + (long)(int)uVar10 * 8);
      uVar31 = 0;
      bVar7 = true;
      do {
        uVar15 = FUN_0018ffd0(param_1,uVar31 & 0xffffffff);
        iVar11 = *piVar23;
        if (iVar11 == 8) {
          if ((bVar7 == false) || (uVar26 = FUN_00190030(), (uVar26 & 1) == 0)) goto LAB_001ce890;
          uVar26 = FUN_001900a0(uVar15);
          bVar7 = (uint)piVar23[1] == uVar26;
        }
        else if (iVar11 < 9) {
          if (iVar11 == 6) {
            if ((bVar7 == false) || (uVar26 = FUN_00190020(), (uVar26 & 1) == 0)) goto LAB_001ce890;
            iVar11 = FUN_00190080(uVar15);
            bVar7 = piVar23[1] == iVar11;
          }
          else if (iVar11 == 7) {
            if ((bVar7 == false) || (uVar26 = FUN_00190020(), (uVar26 & 1) == 0)) goto LAB_001ce890;
            iVar11 = FUN_00190080(uVar15);
            FUN_0018ffd0(param_1,piVar23[1]);
            iVar12 = FUN_00190080();
            bVar7 = iVar11 == iVar12;
          }
        }
        else if (iVar11 == 9) {
          if ((bVar7 == false) || (uVar26 = FUN_00190020(), (uVar26 & 1) == 0)) goto LAB_001ce890;
          uVar15 = FUN_001e7490(param_3,piVar23[1]);
          FUN_0018ffd0(param_1,uVar31 & 0xffffffff);
          uVar13 = FUN_00190080();
          bVar8 = FUN_001e74b4(uVar15,uVar13);
          bVar7 = (bool)(bVar8 & 1);
        }
        else if (iVar11 == 10) {
          if (bVar7 != false) {
            uVar10 = piVar23[1];
            if (uVar10 == 5) {
              uVar26 = FUN_00190030();
              if ((uVar26 & 1) != 0) {
                uVar26 = FUN_001900a0(uVar15);
                uVar10 = (uint)uVar26 & 0x3f;
                uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                if (uVar4 == 0) {
                  uVar6 = 0xffffffff;
                }
                uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                uVar5 = uVar3 - 1;
                uVar4 = uVar5 & (uint)(uVar26 >> 6);
                uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                if (uVar4 != 0) {
                  uVar10 = 0;
                  do {
                    uVar10 = uVar10 + 1;
                    uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                  } while (uVar10 != uVar4);
                }
                if (uVar6 != 6) {
                  do {
                    uVar21 = (ulong)uVar3;
                    uVar3 = uVar3 << 1;
                    uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                  } while (uVar3 != 0x40);
                }
                iVar11 = (int)uVar26;
                uVar2 = (ushort)uVar26;
                uVar21 = (ulong)(short)uVar2;
                if ((((int)(short)uVar2 == iVar11 >> 0x10) &&
                    ((int)(short)(uVar26 >> 0x20) == (int)(short)uVar2)) &&
                   (uVar2 == (ushort)(uVar26 >> 0x30))) {
                  cVar1 = (char)uVar26;
                  if (((uVar26 != (long)(short)(uVar2 & 0xff00) && (long)cVar1 != uVar26) &&
                      ((iVar11 != (int)(uVar26 >> 0x20) ||
                       ((long)(short)(uVar2 & 0xff00) != (long)iVar11 && (long)cVar1 != (long)iVar11
                       )))) && (((uVar21 != (long)(short)(uVar2 & 0xff00) && (long)cVar1 != uVar21
                                 && ((uVar21 & 0xffffffffffff00ff) != 0)) &&
                                (((cVar1 != (char)(uVar26 >> 8) || (cVar1 != (char)(uVar26 >> 0x10))
                                  ) || ((iVar12 = (int)cVar1, iVar12 != iVar11 >> 0x18 ||
                                        (((((char)(uVar26 >> 0x20) != iVar12 ||
                                           ((char)(uVar26 >> 0x28) != iVar12)) ||
                                          ((char)(uVar26 >> 0x30) != iVar12)) ||
                                         (cVar1 != (char)(uVar26 >> 0x38)))))))))))
                  goto LAB_001cec48;
                }
              }
            }
            else if (uVar10 < 6) {
              if (uVar10 == 3) {
                uVar26 = FUN_00190030();
                if ((uVar26 & 1) != 0) {
                  uVar26 = FUN_001900a0(uVar15);
                  uVar10 = (uint)uVar26 & 0x3f;
                  uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                  uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                  if (uVar4 == 0) {
                    uVar6 = 0xffffffff;
                  }
                  uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                  uVar5 = uVar3 - 1;
                  uVar4 = uVar5 & (uint)(uVar26 >> 6);
                  uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                  if (uVar4 != 0) {
                    uVar10 = 0;
                    do {
                      uVar10 = uVar10 + 1;
                      uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                    } while (uVar10 != uVar4);
                  }
                  if (uVar6 != 6) {
                    do {
                      uVar21 = (ulong)uVar3;
                      uVar3 = uVar3 << 1;
                      uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                    } while (uVar3 != 0x40);
                  }
                  bVar7 = (int)(uVar26 >> 0x20) == (int)uVar26;
                  goto LAB_001ce894;
                }
              }
              else if (uVar10 == 4) {
                uVar26 = FUN_00190030();
                if (((uVar26 & 1) != 0) && (lVar17 = FUN_001900a0(uVar15), lVar17 != 0xe)) {
                  lVar17 = FUN_001900a0(uVar15);
                  bVar7 = lVar17 != 0xf;
                  goto LAB_001ce894;
                }
              }
              else if (uVar10 == 1) {
                uVar26 = FUN_00190030();
                if ((uVar26 & 1) != 0) {
                  uVar26 = FUN_001900a0(uVar15);
                  uVar10 = (uint)uVar26 & 0x3f;
                  uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                  uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                  if (uVar4 == 0) {
                    uVar6 = 0xffffffff;
                  }
                  uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                  uVar5 = uVar3 - 1;
                  uVar4 = uVar5 & (uint)(uVar26 >> 6);
                  uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                  if (uVar4 != 0) {
                    uVar10 = 0;
                    do {
                      uVar10 = uVar10 + 1;
                      uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                    } while (uVar10 != uVar4);
                  }
                  if (uVar6 != 6) {
                    do {
                      uVar21 = (ulong)uVar3;
                      uVar3 = uVar3 << 1;
                      uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                    } while (uVar3 != 0x40);
                  }
                  iVar11 = (int)(char)(uVar26 >> 8);
                  if (((((iVar11 == (char)uVar26) &&
                        (iVar12 = (int)(char)(uVar26 >> 0x10), iVar12 == iVar11)) &&
                       (iVar11 = (int)uVar26 >> 0x18, iVar11 == iVar12)) &&
                      ((iVar12 = (int)(char)(uVar26 >> 0x20), iVar12 == iVar11 &&
                       (iVar11 = (int)(char)(uVar26 >> 0x28), iVar11 == iVar12)))) &&
                     (iVar12 = (int)(char)(uVar26 >> 0x30), iVar12 == iVar11)) {
                    bVar7 = (char)(uVar26 >> 0x38) == iVar12;
                    goto LAB_001ce894;
                  }
                }
              }
              else if ((uVar10 == 2) && (uVar26 = FUN_00190030(), (uVar26 & 1) != 0)) {
                uVar26 = FUN_001900a0(uVar15);
                uVar10 = (uint)uVar26 & 0x3f;
                uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                if (uVar4 == 0) {
                  uVar6 = 0xffffffff;
                }
                uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                uVar5 = uVar3 - 1;
                uVar4 = uVar5 & (uint)(uVar26 >> 6);
                uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                if (uVar4 != 0) {
                  uVar10 = 0;
                  do {
                    uVar10 = uVar10 + 1;
                    uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                  } while (uVar10 != uVar4);
                }
                if (uVar6 != 6) {
                  do {
                    uVar21 = (ulong)uVar3;
                    uVar3 = uVar3 << 1;
                    uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                  } while (uVar3 != 0x40);
                }
                iVar11 = (int)uVar26 >> 0x10;
                if ((iVar11 == (short)uVar26) &&
                   (iVar12 = (int)(short)(uVar26 >> 0x20), iVar12 == iVar11)) {
                  bVar7 = (short)(uVar26 >> 0x30) == iVar12;
                  goto LAB_001ce894;
                }
              }
            }
            else if (uVar10 == 8) {
              uVar26 = FUN_00190030();
              if ((uVar26 & 1) != 0) {
                uVar10 = FUN_001900a0(uVar15);
                lVar17 = FUN_001e79f4(uVar10 ^ 0x20);
                bVar7 = lVar17 != 0;
                goto LAB_001ce894;
              }
            }
            else if (uVar10 < 9) {
              if (uVar10 == 6) {
                uVar26 = FUN_00190030();
                if ((uVar26 & 1) != 0) {
                  uVar26 = FUN_001900a0(uVar15);
                  uVar10 = (uint)uVar26 & 0x3f;
                  uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                  uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                  if (uVar4 == 0) {
                    uVar6 = 0xffffffff;
                  }
                  uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                  uVar5 = uVar3 - 1;
                  uVar4 = uVar5 & (uint)(uVar26 >> 6);
                  uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                  if (uVar4 != 0) {
                    uVar10 = 0;
                    do {
                      uVar10 = uVar10 + 1;
                      uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                    } while (uVar10 != uVar4);
                  }
                  if (uVar6 != 6) {
                    do {
                      uVar21 = (ulong)uVar3;
                      uVar3 = uVar3 << 1;
                      uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                    } while (uVar3 != 0x40);
                  }
                  iVar11 = (int)uVar26;
                  if (iVar11 == (int)(uVar26 >> 0x20)) {
                    uVar2 = (ushort)uVar26;
                    cVar1 = (char)uVar26;
                    if (((uVar26 != (long)cVar1 && uVar26 != (long)(short)(uVar2 & 0xff00)) &&
                        ((long)iVar11 != (long)(short)(uVar2 & 0xff00) &&
                         (long)cVar1 != (long)iVar11)) &&
                       ((((iVar11 >> 0x10 != (int)(short)uVar2 ||
                          ((iVar12 = (int)(short)(uVar26 >> 0x20), iVar12 != iVar11 >> 0x10 ||
                           (iVar12 != (short)(uVar26 >> 0x30))))) ||
                         ((uVar21 = (ulong)iVar12,
                          (long)cVar1 != uVar21 && (long)(short)(uVar2 & 0xff00) != uVar21 &&
                          ((uVar21 & 0xffffffffffff00ff) != 0)))) &&
                        ((((cVar1 != (char)(uVar26 >> 8) || (cVar1 != (char)(uVar26 >> 0x10))) ||
                          (iVar12 = (int)cVar1, iVar12 != iVar11 >> 0x18)) ||
                         ((((char)(uVar26 >> 0x20) != iVar12 || ((char)(uVar26 >> 0x28) != iVar12))
                          || (((char)(uVar26 >> 0x30) != iVar12 || (cVar1 != (char)(uVar26 >> 0x38))
                              ))))))))) goto LAB_001cec48;
                  }
                }
              }
              else {
                uVar26 = FUN_00190030();
                if ((uVar26 & 1) != 0) {
                  uVar26 = FUN_001900a0(uVar15);
                  uVar10 = (uint)uVar26 & 0x3f;
                  uVar4 = ((uint)(uVar26 >> 0xc) & 1) << 6 | uVar10 ^ 0x3f;
                  uVar6 = 0x1f - (int)LZCOUNT(uVar4);
                  if (uVar4 == 0) {
                    uVar6 = 0xffffffff;
                  }
                  uVar3 = 1 << (ulong)(uVar6 & 0x1f);
                  uVar5 = uVar3 - 1;
                  uVar4 = uVar5 & (uint)(uVar26 >> 6);
                  uVar26 = (1L << ((ulong)((uVar10 & uVar5) + 1) & 0x3f)) - 1;
                  if (uVar4 != 0) {
                    uVar10 = 0;
                    do {
                      uVar10 = uVar10 + 1;
                      uVar26 = (uVar26 & 1) << ((ulong)uVar5 & 0x3f) | uVar26 >> 1;
                    } while (uVar10 != uVar4);
                  }
                  if (uVar6 != 6) {
                    do {
                      uVar21 = (ulong)uVar3;
                      uVar3 = uVar3 << 1;
                      uVar26 = uVar26 | uVar26 << (uVar21 & 0x3f);
                    } while (uVar3 != 0x40);
                  }
                  iVar11 = (int)uVar26;
                  uVar2 = (ushort)uVar26;
                  uVar21 = (ulong)(short)uVar2;
                  cVar1 = (char)uVar26;
                  if (((uVar26 != (long)cVar1 && uVar26 != (long)(short)(uVar2 & 0xff00)) &&
                      ((iVar11 != (int)(uVar26 >> 0x20) ||
                       ((long)(short)(uVar2 & 0xff00) != (long)iVar11 && (long)cVar1 != (long)iVar11
                       )))) && (((((int)(short)uVar2 != iVar11 >> 0x10 ||
                                  (((ushort)(uVar26 >> 0x20) != uVar2 ||
                                   (uVar2 != (ushort)(uVar26 >> 0x30))))) ||
                                 (((long)cVar1 != uVar21 && (long)(short)(uVar2 & 0xff00) != uVar21
                                  && ((uVar21 & 0xffffffffffff00ff) != 0)))) &&
                                ((((cVar1 != (char)(uVar26 >> 8) ||
                                   (cVar1 != (char)(uVar26 >> 0x10))) ||
                                  (iVar12 = (int)cVar1, iVar12 != iVar11 >> 0x18)) ||
                                 (((((char)(uVar26 >> 0x20) != iVar12 ||
                                    ((char)(uVar26 >> 0x28) != iVar12)) ||
                                   ((char)(uVar26 >> 0x30) != iVar12)) ||
                                  (cVar1 != (char)(uVar26 >> 0x38))))))))) {
LAB_001cec48:
                    if (uVar26 - 1 < 0xfffffffffffffffe) {
                      if ((int)uVar26 == (int)(uVar26 >> 0x20)) {
                        if (((uVar26 ^ uVar26 >> 0x10) & 0xffff) == 0) {
                          if (((uVar26 ^ uVar26 >> 8) & 0xff) == 0) {
                            if (((uVar26 ^ uVar26 >> 4) & 0xf) == 0) {
                              iVar11 = 2;
                              if (((uVar26 ^ uVar26 >> 2) & 3) != 0) {
                                iVar11 = 4;
                              }
                            }
                            else {
                              iVar11 = 8;
                            }
                          }
                          else {
                            iVar11 = 0x10;
                          }
                        }
                        else {
                          iVar11 = 0x20;
                        }
                        uVar25 = 0xffffffffffffffff >> ((ulong)(uint)-iVar11 & 0x3f);
                        uVar21 = (uVar25 & uVar26) - 1 | uVar25 & uVar26;
                        if (uVar21 != 0) goto LAB_001cf684;
                      }
                      else {
                        uVar21 = uVar26 - 1 | uVar26;
                        uVar25 = 0xffffffffffffffff;
LAB_001cf684:
                        if ((uVar21 + 1 & uVar21) == 0) goto LAB_001ce894;
                      }
                      uVar26 = uVar25 & (uVar26 ^ 0xffffffffffffffff) |
                               -(uVar26 | uVar25 ^ 0xffffffffffffffff) - 2;
                      if (uVar26 != 0) {
                        bVar7 = (uVar26 + 1 & uVar26) == 0;
                        goto LAB_001ce894;
                      }
                    }
                  }
                }
              }
            }
            else if ((uVar10 == 9) && (uVar26 = FUN_00190030(), (uVar26 & 1) != 0)) {
              FUN_001900a0(uVar15);
              lVar17 = FUN_001e77c0();
              bVar7 = lVar17 != 0;
              goto LAB_001ce894;
            }
          }
LAB_001ce890:
          bVar7 = false;
        }
LAB_001ce894:
        uVar31 = uVar31 + 1;
        piVar23 = piVar23 + 2;
      } while (uVar31 != bVar20);
      if (bVar7 != false) goto LAB_001cecd8;
      uVar10 = (int)uVar29 + 1;
      uVar29 = (ulong)uVar10;
      puVar27 = puVar27 + 3;
    } while (uVar10 != uVar14);
  }
LAB_001ce8c8:
  puVar28 = (undefined1 *)0x0;
LAB_001ce8cc:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return puVar28;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
}

