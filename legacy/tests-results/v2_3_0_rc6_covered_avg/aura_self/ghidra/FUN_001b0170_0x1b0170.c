
bool FUN_001b0170(long param_1,uint *param_2,ulong param_3,long param_4,undefined2 *param_5)

{
  uint uVar1;
  undefined4 *puVar2;
  ushort uVar3;
  byte bVar4;
  ushort uVar5;
  uint uVar6;
  bool bVar7;
  undefined2 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  void *__s;
  ulong uVar14;
  undefined8 uVar15;
  undefined4 *puVar16;
  byte bVar17;
  long lVar18;
  ulong uVar19;
  undefined *puVar20;
  uint uVar21;
  char cVar22;
  undefined1 auVar23 [16];
  
  if (param_3 < 2) {
LAB_001b03b4:
    iVar9 = 0;
    goto LAB_001b03ec;
  }
  __s = *(void **)(*(long *)(param_4 + 0x310) + 0xf0);
  if (__s != (void *)0x0) {
    memset(__s,0,0x748);
    lVar18 = *(long *)(*(long *)(param_4 + 0x310) + 0xf0);
    puVar16 = (undefined4 *)(lVar18 + 0x88);
    do {
      puVar2 = puVar16 + 0xc;
      *puVar16 = 0xffffffff;
      *(undefined1 *)((long)puVar16 + 0x2a) = 0xff;
      puVar16 = puVar2;
    } while (puVar2 != (undefined4 *)(lVar18 + 0x748));
  }
  uVar5 = (ushort)*param_2;
  uVar3 = uVar5 >> 8 | uVar5 << 8;
  if (-1 < *(int *)(param_1 + 4)) {
    uVar3 = uVar5;
  }
  iVar9 = FUN_001af960(&DAT_0022c040,param_4,uVar3);
  if (iVar9 != 0) {
    uVar8 = 2;
    goto LAB_001b03c0;
  }
  FUN_0018ff00(param_4);
  iVar10 = FUN_001af960(&DAT_0022c510,param_4,uVar3);
  if (iVar10 != 0) {
    iVar9 = *(int *)(param_1 + 0x5c);
    *param_5 = 2;
    bVar7 = iVar9 != 0;
    iVar9 = FUN_001958a0(param_1,param_4);
    if ((iVar9 != 0) && (iVar9 != 1)) {
      iVar9 = iVar10;
    }
LAB_001b0458:
    FUN_001957c0(param_4,bVar7);
    goto LAB_001b03ec;
  }
  FUN_0018ff00(param_4);
  iVar10 = FUN_001af960(&DAT_0022c680,param_4,uVar3);
  if (iVar10 == 0) {
    if (3 < param_3) {
      if (*(int *)(param_1 + 4) < 0) {
        uVar21 = (*param_2 & 0xff00ff00) >> 8 | (*param_2 & 0xff00ff) << 8;
        uVar21 = uVar21 >> 0x10 | uVar21 << 0x10;
      }
      else {
        uVar21 = (uint)*(ushort *)((long)param_2 + 2) | (uint)*(byte *)((long)param_2 + 1) << 0x18 |
                 (uint)(byte)*param_2 << 0x10;
      }
      FUN_0018ff00(param_4);
      iVar10 = FUN_001afcf0(&DAT_0022c6a0,param_4,uVar21);
      if (iVar10 != 0) {
        iVar9 = *(int *)(param_1 + 0x5c);
        *param_5 = 4;
        bVar7 = iVar9 != 0;
        iVar9 = FUN_001958a0(param_1,param_4);
        if ((iVar9 != 0) && (iVar9 != 1)) {
          iVar9 = iVar10;
        }
        goto LAB_001b0458;
      }
      FUN_0018ff00(param_4);
      iVar9 = FUN_001afcf0(&DAT_002344e0,param_4,uVar21);
      if (iVar9 == 0) {
        if (uVar21 >> 0x1c == 0xe) {
          FUN_0018ff00(param_4);
          iVar9 = FUN_001afcf0(&DAT_002333c0,param_4,uVar21);
          if (iVar9 != 0) {
            *param_5 = 4;
            cVar22 = '\x0e';
            if (*(int *)(param_1 + 0x5c) != 0) {
              uVar21 = *(int *)(param_1 + 0x5c) - 1;
              cVar22 = *(char *)(param_1 + 0x54 + (ulong)uVar21);
              *(uint *)(param_1 + 0x5c) = uVar21;
            }
            uVar14 = FUN_0018ffb0(param_4);
            puVar20 = (&PTR_DAT_005e0b78)[(uVar14 & 0xffffffff) * 2];
            auVar23 = FUN_0018ffb0(param_4);
            bVar4 = (&DAT_005e0b70)[(auVar23._0_8_ & 0xffffffff) * 0x10];
            uVar21 = 0;
            uVar14 = auVar23._8_8_;
            if (bVar4 != 0) {
              do {
                uVar19 = (ulong)uVar21;
                uVar14 = FUN_001902e0(puVar20,uVar14);
                uVar21 = uVar21 + 1;
                if ((uVar14 & 1) != 0) {
                  uVar15 = FUN_0018ffd0(param_4);
                  FUN_001900b0(uVar15,cVar22);
                  if (cVar22 == '\x0e') {
                    uVar15 = FUN_0018ffd0(param_4,uVar21);
                    FUN_00190090(uVar15,0);
                  }
                  else {
                    uVar15 = FUN_0018ffd0(param_4,uVar21);
                    FUN_00190090(uVar15,3);
                  }
                  break;
                }
                puVar20 = puVar20 + 8;
                uVar14 = uVar19;
              } while (bVar4 != uVar21);
            }
            goto LAB_001b03ec;
          }
          FUN_0018ff00(param_4);
          iVar9 = FUN_001afcf0(&DAT_0022d670,param_4,uVar21);
          if (iVar9 == 0) {
            FUN_0018ff00(param_4);
            iVar9 = FUN_001afcf0(&DAT_0022c6f0,param_4,uVar21);
            if (iVar9 != 0) {
              uVar8 = 4;
              goto LAB_001b03c0;
            }
            goto LAB_001b0310;
          }
        }
        else {
          FUN_0018ff00(param_4);
          iVar9 = FUN_001afcf0(&DAT_0022d670,param_4,uVar21);
          if (iVar9 == 0) {
            if (uVar21 >> 0x18 == 0xf9) {
              FUN_0018ff00(param_4);
              iVar9 = FUN_001afcf0(&DAT_002364e0,param_4,uVar21 & 0xf0ffffff | 0x4000000);
              uVar11 = uVar21 & 0xf0ffffff | 0x13000000;
              if (iVar9 == 0) goto LAB_001b0330;
              uVar8 = 4;
              goto LAB_001b03c0;
            }
LAB_001b0310:
            uVar11 = uVar21 & 0xf0ffffff | (uVar21 & 0x10000000) >> 4 | 0x12000000;
            if ((uVar21 >> 0x18 & 0xf) == 0xf) {
              FUN_0018ff00(param_4);
              iVar9 = FUN_001afcf0(&DAT_00237f10,param_4,uVar11);
              if (iVar9 != 0) goto LAB_001b0694;
            }
LAB_001b0330:
            FUN_0018ff00(param_4);
            iVar9 = FUN_001afcf0(&DAT_0022c8d0,param_4,uVar11);
            if (iVar9 == 0) {
              FUN_0018ff00(param_4);
              iVar9 = FUN_001afcf0(&DAT_0022cb00,param_4,uVar21 & 0xf3ffffff);
              if (iVar9 == 0) {
                FUN_0018ff00(param_4);
                iVar9 = FUN_001afcf0(&DAT_0022d390,param_4,uVar21);
                if (iVar9 == 0) {
                  FUN_0018ff00(param_4);
                  *param_5 = 0;
                  goto LAB_001b03b4;
                }
                goto LAB_001b0694;
              }
            }
          }
        }
        *param_5 = 4;
        goto LAB_001b03ec;
      }
LAB_001b0694:
      uVar8 = 4;
LAB_001b03c0:
      *param_5 = uVar8;
      iVar10 = FUN_001958a0(param_1,param_4);
      if (iVar10 != 0) {
        if (iVar10 != 1) goto LAB_001b03ec;
        goto LAB_001b05c0;
      }
    }
    iVar9 = 0;
    goto LAB_001b03ec;
  }
  *param_5 = 2;
  iVar9 = FUN_0018ffb0(param_4);
  if ((iVar9 == 0xafa) && (*(int *)(param_1 + 0x5c) != 0)) {
LAB_001b05c0:
    iVar9 = 1;
    goto LAB_001b03ec;
  }
  iVar9 = FUN_001958a0(param_1,param_4);
  if ((iVar9 != 0) && (iVar9 != 1)) {
    iVar9 = iVar10;
  }
  iVar10 = FUN_0018ffb0(param_4);
  if (iVar10 != 0xafa) goto LAB_001b03ec;
  FUN_0018ffd0(param_4,0);
  uVar11 = FUN_001900a0();
  FUN_0018ffd0(param_4,1);
  uVar12 = FUN_001900a0();
  uVar21 = uVar12 & 0xff;
  lVar18 = param_1 + 0x54;
  if ((uVar12 & 0xff) == 0) {
    uVar12 = *(uint *)(param_1 + 0x5c);
LAB_001b0708:
    iVar10 = 1;
    uVar14 = 0;
    if (uVar12 < 8) {
      uVar14 = (ulong)uVar12;
      goto LAB_001b0594;
    }
  }
  else {
    uVar12 = (uVar12 & 0xaa) >> 1 | (uVar12 & 0x55) << 1;
    uVar6 = (uVar12 & 0xcccccccc) >> 2 | (uVar12 & 0x33333333) << 2;
    uVar12 = *(uint *)(param_1 + 0x5c);
    bVar4 = (byte)uVar11 & 0xf;
    iVar10 = (int)LZCOUNT((uVar6 >> 4 | (uVar6 & 0xf0f0f0f) << 4) << 0x18);
    if (3 < iVar10 + 1U) goto LAB_001b0708;
    uVar6 = uVar11 & 1;
    if (((int)uVar21 >> (iVar10 + 1U & 0x1f) & 1U) == uVar6) {
      bVar17 = bVar4;
      if (uVar12 < 8) goto LAB_001b07d8;
      *(byte *)(param_1 + 0x54) = bVar4;
LAB_001b0538:
      *(undefined4 *)(param_1 + 0x5c) = 1;
      if (iVar10 == 2) goto LAB_001b089c;
      if (uVar6 == ((int)uVar21 >> (iVar10 + 2U & 0x1f) & 1U)) {
        uVar14 = 1;
LAB_001b0878:
        *(byte *)(lVar18 + uVar14) = bVar4;
        iVar13 = (int)uVar14;
      }
      else {
        uVar14 = 1;
LAB_001b0564:
        *(byte *)(lVar18 + uVar14) = bVar4 ^ 1;
        iVar13 = (int)uVar14;
      }
      uVar12 = iVar13 + 1;
      *(uint *)(param_1 + 0x5c) = uVar12;
      if (iVar10 != 0) goto LAB_001b0708;
      if ((uVar21 >> 3 & 1) == uVar6) {
        if (uVar12 != 8) {
          *(byte *)(lVar18 + (ulong)uVar12) = bVar4;
          uVar12 = iVar13 + 2;
          goto LAB_001b0708;
        }
        uVar14 = 1;
        *(byte *)(param_1 + 0x54) = bVar4;
      }
      else {
        if (uVar12 != 8) {
          *(byte *)(lVar18 + (ulong)uVar12) = bVar4 ^ 1;
          uVar12 = iVar13 + 2;
          goto LAB_001b0708;
        }
        uVar14 = 1;
        *(byte *)(param_1 + 0x54) = bVar4 ^ 1;
      }
    }
    else {
      bVar17 = bVar4 ^ 1;
      if (7 < uVar12) {
        *(byte *)(param_1 + 0x54) = bVar17;
        goto LAB_001b0538;
      }
LAB_001b07d8:
      uVar1 = uVar12 + 1;
      uVar14 = (ulong)uVar1;
      *(byte *)(lVar18 + (ulong)uVar12) = bVar17;
      *(uint *)(param_1 + 0x5c) = uVar1;
      uVar12 = uVar1;
      if (iVar10 == 2) goto LAB_001b0708;
      if (((int)uVar21 >> (iVar10 + 2U & 0x1f) & 1U) == uVar6) {
        if (uVar1 != 8) goto LAB_001b0878;
        *(byte *)(param_1 + 0x54) = bVar4;
        *(undefined4 *)(param_1 + 0x5c) = 1;
        if (iVar10 != 0) goto LAB_001b089c;
LAB_001b0818:
        if (uVar6 == (uVar21 >> 3 & 1)) {
          uVar14 = 2;
          *(byte *)(param_1 + 0x55) = bVar4;
        }
        else {
          uVar14 = 2;
          *(byte *)(param_1 + 0x55) = bVar4 ^ 1;
        }
        goto LAB_001b0594;
      }
      if (uVar1 != 8) goto LAB_001b0564;
      *(byte *)(param_1 + 0x54) = bVar4 ^ 1;
      *(undefined4 *)(param_1 + 0x5c) = 1;
      if (iVar10 == 0) goto LAB_001b0818;
LAB_001b089c:
      uVar14 = 1;
    }
LAB_001b0594:
    iVar10 = (int)uVar14 + 1;
  }
  *(byte *)(lVar18 + uVar14) = (byte)uVar11 & 0xf;
  *(int *)(param_1 + 0x5c) = iVar10;
LAB_001b03ec:
  return *(int *)(param_4 + 8) != 0xc90 && iVar9 != 0;
}

