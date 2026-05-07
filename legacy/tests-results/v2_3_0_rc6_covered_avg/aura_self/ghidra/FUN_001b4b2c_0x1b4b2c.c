
void FUN_001b4b2c(long param_1,undefined8 param_2,undefined8 param_3)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  long lVar8;
  undefined4 uVar9;
  long lVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  
  uVar6 = FUN_0018ffd0();
  uVar3 = FUN_001900a0();
  uVar4 = FUN_001900a0(uVar6);
  uVar7 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x3e);
  if ((uVar7 & 1) == 0) {
    uVar1 = uVar4 & 0xf;
    if (uVar3 >> 4 == 0) {
      if ((0x1110UL >> uVar1 & 1) != 0) {
        FUN_00190370(param_3,"apsr_");
        if (uVar1 == 8) {
          FUN_00190370(param_3,"nzcvq");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10200000043;
        }
        else if (uVar1 == 0xc) {
          FUN_00190370(param_3,"nzcvqg");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10300000043;
        }
        else {
          FUN_00190370(param_3,"g");
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
            return;
          }
          lVar8 = *(long *)(param_1 + 0x310);
          uVar6 = 0x10100000043;
        }
        lVar8 = *(long *)(lVar8 + 0xf0);
        bVar2 = *(byte *)(lVar8 + 0x80);
        *(undefined8 *)(lVar8 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10 + 0x94) = uVar6;
        *(byte *)(lVar8 + 0x80) = bVar2 + 1;
        return;
      }
      FUN_00190370(param_3,&DAT_001fe1f8);
    }
    else {
      FUN_00190370(param_3,&DAT_001fe1f0);
    }
    if ((uVar4 & 0xf) == 0) {
      return;
    }
    FUN_00190370(param_3,&DAT_001fe200);
    if ((uVar4 >> 3 & 1) == 0) {
      uVar9 = 0;
      uVar11 = 1;
      uVar13 = 2;
      uVar12 = 3;
      uVar17 = 4;
      uVar16 = 5;
      uVar15 = 6;
      uVar14 = 7;
    }
    else {
      FUN_00190370(param_3,&DAT_001fe208);
      uVar9 = 8;
      uVar11 = 9;
      uVar13 = 10;
      uVar12 = 0xb;
      uVar17 = 0xc;
      uVar16 = 0xd;
      uVar15 = 0xe;
      uVar14 = 0xf;
    }
    if ((uVar4 >> 2 & 1) != 0) {
      FUN_00190370(param_3,"s");
      uVar9 = uVar17;
      uVar13 = uVar15;
      uVar11 = uVar16;
      uVar12 = uVar14;
    }
    if ((uVar4 >> 1 & 1) != 0) {
      FUN_00190370(param_3,&DAT_001fdf90);
      uVar11 = uVar12;
      uVar9 = uVar13;
    }
    if ((uVar4 & 1) != 0) {
      FUN_00190370(param_3,"c");
      uVar9 = uVar11;
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar8 + 0x94) = 0x43;
    *(undefined4 *)(lVar8 + 0x98) = uVar9;
    *(byte *)(lVar10 + 0x80) = bVar2 + 1;
    return;
  }
  uVar3 = FUN_001900a0(uVar6);
  iVar5 = FUN_0018ffb0(param_1);
  if (iVar5 == 0xb5b) {
    uVar7 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x2c);
    if (((uVar7 & 1) != 0) &&
       (uVar4 = FUN_00190910(&DAT_00244750,0x25,uVar3 & 0xfff), uVar4 != 0xffffffff)) {
      uVar7 = (ulong)*(uint *)(&DAT_00244754 + (ulong)uVar4 * 8);
      if ((*(int *)(&DAT_005ed6a4 + uVar7 * 0x20) == 0x2c) ||
         (*(int *)(&DAT_005ed6a8 + uVar7 * 0x20) == 0x2c)) {
        FUN_00190370(param_3,(&PTR_s_apsr_g_005ed690)[uVar7 * 4]);
        uVar9 = *(undefined4 *)(&DAT_005ed698 + uVar7 * 0x20);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar2 = *(byte *)(lVar10 + 0x80);
        lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
        *(undefined4 *)(lVar8 + 0x94) = 0x43;
        *(undefined4 *)(lVar8 + 0x98) = uVar9;
        *(byte *)(lVar10 + 0x80) = bVar2 + 1;
        return;
      }
    }
    uVar7 = FUN_001b0080(*(undefined4 *)(*(long *)(param_1 + 800) + 4),0x6e);
    if (((uVar7 & 1) != 0) &&
       (uVar4 = FUN_00190910(&DAT_00244880,0x25,uVar3 & 0xff | 0x200), uVar4 != 0xffffffff))
    goto LAB_001b4c54;
  }
  uVar3 = uVar3 & 0xff;
  uVar4 = FUN_00190910(&DAT_00244880,0x25,uVar3 | 0x100);
  if (uVar4 == 0xffffffff) {
    if (uVar3 < 10) {
      FUN_001903f0(param_3,&DAT_001fdda0,uVar3);
    }
    else {
      FUN_001903f0(param_3,&DAT_001fe1d0,uVar3);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    FUN_00190140(param_1,uVar3);
    return;
  }
LAB_001b4c54:
  uVar3 = *(uint *)(&DAT_00244884 + (ulong)uVar4 * 8);
  FUN_00190370(param_3,(&PTR_s_apsr_g_005ed690)[(ulong)uVar3 * 4]);
  uVar9 = *(undefined4 *)(&DAT_005ed698 + (ulong)uVar3 * 0x20);
  if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
    lVar10 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar2 = *(byte *)(lVar10 + 0x80);
    lVar8 = lVar10 + ((ulong)bVar2 * 2 + (ulong)bVar2) * 0x10;
    *(undefined4 *)(lVar8 + 0x94) = 0x43;
    *(undefined4 *)(lVar8 + 0x98) = uVar9;
    *(byte *)(lVar10 + 0x80) = bVar2 + 1;
  }
  return;
}

