
void FUN_001b4fd0(long param_1,undefined8 param_2)

{
  byte bVar1;
  code *pcVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  long lVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  long lVar17;
  undefined *puVar18;
  char *pcVar19;
  long lVar20;
  ulong uVar21;
  uint uVar22;
  char cVar23;
  uint uVar24;
  
  uVar12 = FUN_0018ffb0();
  uVar11 = *(uint *)(&DAT_00248ae0 + (uVar12 & 0xffffffff) * 4);
  uVar10 = *(uint *)(&DAT_00245890 + (uVar12 & 0xffffffff) * 4);
  FUN_00190370(param_2,(uVar11 & 0xfff) + 0x2449af);
  uVar12 = (((ulong)uVar11 & 0x1f000) >> 0xc) - 1;
  if (0x1e < uVar12) {
    return;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    FUN_0018ffd0(param_1,5);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 6:
    FUN_001b35e4(param_1,3,param_2);
    break;
  case 1:
    FUN_0018ffd0(param_1,1);
    uVar5 = FUN_001900a0();
    FUN_0018ffd0(param_1,0);
    uVar6 = FUN_001900a0();
    if ((uVar5 != 0) &&
       (uVar24 = (uVar5 & 0xaaaaaaaa) >> 1 | (uVar5 & 0x55555555) << 1,
       uVar24 = (uVar24 & 0xcccccccc) >> 2 | (uVar24 & 0x33333333) << 2,
       uVar24 = (uVar24 & 0xf0f0f0f0) >> 4 | (uVar24 & 0xf0f0f0f) << 4,
       uVar24 = (uVar24 & 0xff00ff00) >> 8 | (uVar24 & 0xff00ff) << 8,
       uVar24 = (uint)LZCOUNT(uVar24 >> 0x10 | uVar24 << 0x10), uVar24 < 3)) {
      uVar22 = 3;
      do {
        if (((uVar5 >> (ulong)(uVar22 & 0x1f) ^ uVar6) & 1) == 0) {
          FUN_00190370(param_2,&DAT_00202558);
        }
        else {
          FUN_00190370(param_2,"e");
        }
        uVar22 = uVar22 - 1;
      } while (uVar24 != uVar22);
    }
    break;
  case 3:
    FUN_0018ffd0(param_1,4);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 2:
    FUN_001b35e4(param_1,2,param_2);
    break;
  case 5:
    FUN_001b35e4(param_1,5,param_2);
    break;
  case 7:
    FUN_0018ffd0(param_1,6);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
  case 4:
    FUN_001b35e4(param_1,4,param_2);
    break;
  case 8:
    FUN_0018ffd0(param_1,7);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    FUN_001b35e4(param_1,5,param_2);
    FUN_00190370(param_2,&DAT_001fe348);
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b0c20(param_1,2,param_2);
    return;
  case 9:
    FUN_001b1900(param_1,0,param_2);
    break;
  case 10:
    FUN_001b35e4(param_1,1,param_2);
    break;
  case 0xb:
    FUN_001b35e4(param_1,0,param_2);
    break;
  case 0xc:
    FUN_001b35e4(param_1,6,param_2);
    break;
  case 0xd:
    FUN_0018ffd0(param_1,0);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    break;
  case 0xe:
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_001900a0();
    if (iVar7 == 2) {
      puVar18 = &DAT_001fe210;
    }
    else {
      puVar18 = &DAT_001fe218;
      if (iVar7 != 3) {
        puVar18 = &DAT_001fe648;
      }
    }
    FUN_00190370(param_2,puVar18);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x6c) = iVar7;
    }
    break;
  case 0xf:
    goto switchD_001b5064_caseD_f;
  case 0x10:
    goto switchD_001b5064_caseD_10;
  case 0x11:
    FUN_0018ffd0(param_1,1);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,3);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,4);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b5740;
  case 0x12:
    FUN_0018ffd0(param_1,2);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,4);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 0x40;
    *(undefined4 *)(lVar13 + 0x98) = uVar4;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x13:
    goto switchD_001b5064_caseD_13;
  case 0x14:
    FUN_001b4540(param_1,0,param_2);
    return;
  case 0x15:
    FUN_0018ffd0(param_1,0);
    lVar13 = FUN_001900a0();
    if (lVar13 == 0) {
      FUN_00190370(param_2,"le");
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = DAT_0020c5a0;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
      return;
    }
    FUN_00190370(param_2,&DAT_001fe230);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = DAT_0020c598;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 0x16:
    FUN_0018ffd0(param_1,8);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    FUN_001b35e4(param_1,6,param_2);
    FUN_00190370(param_2,&DAT_001fe348);
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x17:
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_001900a0();
    pcVar19 = "csync";
    if (iVar7 != 0) {
      pcVar19 = (char *)0x0;
    }
    FUN_00190370(param_2,pcVar19);
    return;
  case 0x18:
    FUN_001b35e4(param_1,7,param_2);
    break;
  case 0x19:
    FUN_001b35e4(param_1,9,param_2);
    break;
  case 0x1a:
    FUN_001b35e4(param_1,0xb,param_2);
    break;
  case 0x1b:
    FUN_001b35e4(param_1,8,param_2);
    break;
  case 0x1c:
    FUN_001b35e4(param_1,0xd,param_2);
    break;
  case 0x1d:
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    break;
  case 0x1e:
    FUN_0018ffd0(param_1,1);
    iVar7 = FUN_00190080();
    if ((iVar7 != 0) && (FUN_00190370(param_2,"s"), *(int *)(*(long *)(param_1 + 800) + 0x60) != 0))
    {
      *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x78) = 1;
    }
    break;
  default:
    goto switchD_001b5064_default;
  }
  uVar12 = (((ulong)uVar11 & 0xfe0000) >> 0x11) - 1;
  if (0x49 < uVar12) {
switchD_001b5298_default:
    FUN_00190370(param_2,&DAT_001fe568);
    goto LAB_001b50e0;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    FUN_00190370(param_2,&DAT_001fe238);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b6d30;
  case 1:
    FUN_00190370(param_2,&DAT_001fe240);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b6d10;
  case 2:
    FUN_00190370(param_2,&DAT_001fe248);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b6cf0;
  case 3:
    FUN_00190370(param_2,&DAT_001fe348);
    goto LAB_001b50e0;
  case 4:
    goto switchD_001b5298_caseD_4;
  case 5:
    goto switchD_001b5064_default;
  case 6:
    FUN_00190370(param_2,&DAT_001fe250);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xa00000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 7:
    FUN_001b1900(param_1,1,param_2);
    goto switchD_001b5298_caseD_4;
  case 8:
    FUN_00190370(param_2,".f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x10;
    }
    goto LAB_001b5d68;
  case 9:
    FUN_00190370(param_2,".f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xe;
    }
    goto LAB_001b5d68;
  case 10:
    FUN_00190370(param_2,".f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xf;
    }
LAB_001b5d68:
    FUN_001b1900(param_1,0,param_2);
    goto LAB_001b50e0;
  case 0xb:
    FUN_00190370(param_2,"\tapsr_nzcv, fpscr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x200000001;
    *(undefined8 *)
     (lVar13 + ((ulong)(byte)(bVar1 + 1) * 2 + (ulong)(byte)(bVar1 + 1)) * 0x10 + 0x94) =
         0x600000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 2;
    return;
  case 0xc:
    FUN_0018ffd0(param_1,1);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    goto LAB_001b50e0;
  case 0xd:
    FUN_00190370(param_2,"\tpc, lr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xb00000001;
    *(undefined8 *)
     (lVar13 + ((ulong)(byte)(bVar1 + 1) * 2 + (ulong)(byte)(bVar1 + 1)) * 0x10 + 0x94) =
         0xa00000001;
    *(byte *)(lVar13 + 0x80) = bVar1 + 2;
    return;
  case 0xe:
    goto switchD_001b9ce0_caseD_1;
  case 0xf:
    FUN_00190370(param_2,".s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 7;
    }
    goto LAB_001b52c8;
  case 0x10:
    FUN_00190370(param_2,".s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 6;
    }
    goto LAB_001b52c8;
  case 0x11:
    FUN_00190370(param_2,&DAT_001fe2a0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 5;
    }
    goto LAB_001b52c8;
  case 0x12:
    FUN_00190370(param_2,".u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xb;
    }
    goto LAB_001b52c8;
  case 0x13:
    FUN_00190370(param_2,".u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 10;
    }
    goto LAB_001b52c8;
  case 0x14:
    FUN_00190370(param_2,&DAT_001fe2b8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 9;
    }
    goto LAB_001b52c8;
  case 0x15:
    FUN_00190370(param_2,".i64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 4;
    }
    goto LAB_001b52c8;
  case 0x16:
    FUN_00190370(param_2,".i32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 3;
    }
    goto LAB_001b52c8;
  case 0x17:
    FUN_00190370(param_2,".i16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 2;
    }
    goto LAB_001b52c8;
  case 0x18:
    FUN_00190370(param_2,&DAT_001fe2d8);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 1;
    }
    goto LAB_001b52c8;
  case 0x19:
    FUN_00190370(param_2,".f16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x11;
    }
    goto LAB_001b5f9c;
  case 0x1a:
    FUN_00190370(param_2,".f64.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x12;
    }
    goto LAB_001b5f9c;
  case 0x1b:
    FUN_00190370(param_2,".f32.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x13;
    }
    goto LAB_001b5f9c;
  case 0x1c:
    FUN_00190370(param_2,".f16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x14;
    }
    goto LAB_001b5f9c;
  case 0x1d:
    FUN_00190370(param_2,".f64.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x15;
    }
    goto LAB_001b5f9c;
  case 0x1e:
    FUN_00190370(param_2,".f32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x16;
    }
LAB_001b5f9c:
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    return;
  case 0x1f:
    FUN_00190370(param_2,&DAT_001fe340);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x17;
    }
    break;
  case 0x20:
    FUN_00190370(param_2,".u32.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x18;
    }
    break;
  case 0x21:
    pcVar19 = ".s16.f16\t";
    goto LAB_001b5e5c;
  case 0x22:
    FUN_00190370(param_2,".u16.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x28;
    }
    break;
  case 0x23:
    FUN_00190370(param_2,".f32.s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x19;
    }
    break;
  case 0x24:
    pcVar19 = ".f16.s16\t";
    goto LAB_001b5e5c;
  case 0x25:
    FUN_00190370(param_2,".f32.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1a;
    }
    break;
  case 0x26:
    FUN_00190370(param_2,".f16.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x27;
    }
    break;
  case 0x27:
    FUN_00190370(param_2,&DAT_001fe3c0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x40;
    }
    goto LAB_001b50e0;
  case 0x28:
    FUN_00190370(param_2,".s32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x20;
    }
    break;
  case 0x29:
    FUN_00190370(param_2,".16\t{");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b6d30:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x10;
    }
    goto LAB_001b50e0;
  case 0x2a:
    FUN_00190370(param_2,".32\t{");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b6d10:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 0x20;
    }
    goto LAB_001b50e0;
  case 0x2b:
    FUN_00190370(param_2,&DAT_001fe3e8);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b6cf0:
    if (iVar7 != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 100) = 8;
    }
    goto LAB_001b50e0;
  case 0x2c:
    FUN_00190370(param_2,"\tfpscr, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x600000001;
    goto LAB_001b62f4;
  case 0x2d:
    FUN_00190370(param_2,"\tfpexc, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x400000001;
    goto LAB_001b62f4;
  case 0x2e:
    FUN_00190370(param_2,"\tfpinst, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x500000001;
    goto LAB_001b62f4;
  case 0x2f:
    FUN_00190370(param_2,"\tfpinst2, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x2e00000001;
    goto LAB_001b62f4;
  case 0x30:
    FUN_00190370(param_2,"\tfpsid, ");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0x800000001;
    goto LAB_001b62f4;
  case 0x31:
    FUN_00190370(param_2,&DAT_001fe440);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xd;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    return;
  case 0x32:
    FUN_00190370(param_2,".s64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 8;
    }
    goto LAB_001b52c8;
  case 0x33:
    FUN_00190370(param_2,".u64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0xc;
    }
LAB_001b52c8:
    FUN_001b1900(param_1,0,param_2);
switchD_001b5298_caseD_4:
    FUN_00190370(param_2,", ");
    goto LAB_001b50e0;
  case 0x34:
    FUN_0018ffd0(param_1,4);
    uVar11 = FUN_001900a0();
    if (uVar11 < 10) {
      FUN_001903f0(param_2,&DAT_001fdfc0,uVar11);
    }
    else {
      FUN_001903f0(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    uVar10 = *(byte *)(lVar13 + 0x80) - 1;
    *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                       (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    return;
  case 0x35:
    FUN_00190370(param_2,".f64.s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1b;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x36:
    FUN_00190370(param_2,".f32.s16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1c;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x37:
    FUN_00190370(param_2,".f64.s32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1d;
    }
    break;
  case 0x38:
    pcVar19 = ".f16.s32\t";
    goto LAB_001b5e5c;
  case 0x39:
    FUN_00190370(param_2,".s16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1e;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3a:
    FUN_00190370(param_2,".s16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x1f;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3b:
    pcVar19 = ".s32.f16\t";
LAB_001b5e5c:
    FUN_00190370(param_2,pcVar19);
    break;
  case 0x3c:
    FUN_00190370(param_2,".u16.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x21;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3d:
    FUN_00190370(param_2,".u16.f32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x22;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x3e:
    FUN_00190370(param_2,".u32.f64\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x23;
    }
    break;
  case 0x3f:
    FUN_00190370(param_2,".u32.f16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x2a;
    }
    break;
  case 0x40:
    FUN_00190370(param_2,".f64.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x24;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x41:
    FUN_00190370(param_2,".f32.u16\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x25;
    }
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x42:
    FUN_00190370(param_2,".f64.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x26;
    }
    break;
  case 0x43:
    FUN_00190370(param_2,".f16.u32\t");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(undefined4 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x68) = 0x29;
    }
    break;
  case 0x44:
    FUN_00190370(param_2,&DAT_001fe548);
    goto LAB_001b50e0;
  case 0x45:
    FUN_00190370(param_2,"\tsp, ");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b62e4;
  case 0x46:
    FUN_00190370(param_2,"\tsp!, ");
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b62e4:
    if (iVar7 == 0) goto LAB_001b6314;
    lVar13 = *(long *)(param_1 + 0x310);
    uVar14 = 0xc00000001;
LAB_001b62f4:
    lVar13 = *(long *)(lVar13 + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = uVar14;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
LAB_001b6314:
    FUN_001b1900(param_1,0,param_2);
    return;
  case 0x47:
    FUN_00190370(param_2,&DAT_001fe560);
    FUN_001b1900(param_1,0,param_2);
    return;
  case 0x48:
    FUN_001b35e4(param_1,4,param_2);
    FUN_00190370(param_2,&DAT_001fe348);
    FUN_001b1900(param_1,0,param_2);
    goto switchD_001b5298_caseD_4;
  case 0x49:
    FUN_001b35e4(param_1,3,param_2);
    FUN_00190370(param_2,&DAT_001fe348);
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    goto LAB_001b50e0;
  default:
    goto switchD_001b5298_default;
  }
  FUN_001b1900(param_1,0,param_2);
  FUN_00190370(param_2,", ");
  FUN_001b1900(param_1,1,param_2);
LAB_001b50e0:
  uVar12 = (((ulong)uVar11 & 0x3f000000) >> 0x18) - 1;
  if (0x3a < uVar12) {
switchD_001b5300_default:
    FUN_001b1900(param_1,0,param_2);
    goto LAB_001b5108;
  }
  switch(uVar12 & 0xffffffff) {
  case 0:
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_001900a0();
    switch(iVar7) {
    case 0:
      pcVar19 = "eq";
      break;
    case 1:
      pcVar19 = "ne";
      break;
    case 2:
      pcVar19 = "hs";
      break;
    case 3:
      pcVar19 = "lo";
      break;
    case 4:
      pcVar19 = "mi";
      break;
    case 5:
      pcVar19 = "pl";
      break;
    case 6:
      pcVar19 = "vs";
      break;
    case 7:
      pcVar19 = "vc";
      break;
    case 8:
      pcVar19 = "hi";
      break;
    case 9:
      pcVar19 = "ls";
      break;
    case 10:
      pcVar19 = "ge";
      break;
    case 0xb:
      pcVar19 = "lt";
      break;
    case 0xc:
      pcVar19 = "gt";
      break;
    case 0xd:
      pcVar19 = "le";
      break;
    case 0xe:
      pcVar19 = "al";
      break;
    default:
      pcVar19 = "";
    }
    FUN_00190370(param_2,pcVar19);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    *(int *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x74) = iVar7 + 1;
    return;
  case 1:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 1);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 1;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 2;
      lVar13 = *(long *)(param_1 + 0x310);
LAB_001b7920:
      lVar17 = *(long *)(lVar13 + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b77a8;
  case 2:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 4;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b7920;
    }
    goto LAB_001b77a8;
  case 3:
    FUN_001b13a0(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 4:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 4;
      lVar13 = *(long *)(param_1 + 0x310);
LAB_001b7f90:
      lVar17 = *(long *)(lVar13 + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto LAB_001b7b20;
  case 5:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 1);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 1;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 3);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 3;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b7920;
    }
    goto LAB_001b77a8;
  case 6:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 6);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 6;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b7920;
    }
LAB_001b77a8:
    FUN_00190370(param_2,&DAT_001fe578);
    cVar23 = *(char *)(param_1 + 0x366);
LAB_001b77c8:
    *(char *)(param_1 + 0x366) = cVar23 + '\x01';
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    break;
  case 7:
    FUN_001b1600(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 8:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 2);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 2;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 4);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(int *)(lVar13 + 0x98) = iVar7 + 4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))(iVar7 + 6);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      iVar7 = FUN_00190080();
      iVar7 = iVar7 + 6;
      lVar13 = *(long *)(param_1 + 0x310);
      goto LAB_001b7f90;
    }
LAB_001b7b20:
    FUN_00190370(param_2,&DAT_001f96c0);
    cVar23 = *(char *)(param_1 + 0x366);
    goto LAB_001b77c8;
  case 9:
    FUN_001b1900(param_1,2,param_2);
    break;
  case 10:
    FUN_001b1900(param_1,1,param_2);
    break;
  case 0xb:
    FUN_0018ffd0(param_1,0);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    goto switchD_001b5300_caseD_e;
  case 0xc:
    FUN_0018ffd0(param_1,2);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,3);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
    goto joined_r0x001b769c;
  case 0xd:
    FUN_0018ffd0(param_1,1);
    uVar5 = FUN_001900a0();
    if ((uVar5 >> 2 & 1) == 0) {
      if ((uVar5 >> 1 & 1) != 0) goto LAB_001ba138;
      if ((uVar5 & 1) != 0) goto LAB_001b6f04;
      if (uVar5 == 0) {
        uVar5 = 0x10;
        FUN_00190370(param_2,&DAT_001fe580);
      }
    }
    else {
      FUN_00190370(param_2,&DAT_00206690);
      if ((uVar5 >> 1 & 1) != 0) {
LAB_001ba138:
        FUN_00190370(param_2,"i");
      }
      if ((uVar5 & 1) != 0) {
LAB_001b6f04:
        FUN_00190370(param_2,&DAT_001fe208);
      }
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      *(uint *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x70) = uVar5;
    }
    break;
  case 0xe:
    goto switchD_001b5300_caseD_e;
  case 0xf:
    FUN_001b2600(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3890(param_1,1,param_2);
    return;
  case 0x10:
    goto switchD_001b8f50_caseD_e;
  case 0x11:
    FUN_001b3890(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 0x12:
    goto switchD_001b8f50_caseD_10;
  case 0x13:
    FUN_0018ffd0(param_1,1);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,3);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    iVar7 = *(int *)(*(long *)(param_1 + 800) + 0x60);
joined_r0x001b769c:
    if (iVar7 != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,4);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
LAB_001b5740:
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,5,param_2);
    return;
  case 0x14:
    FUN_0018ffd0(param_1,2);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fe228,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x41;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_0018ffd0(param_1,4);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 0x40;
    *(undefined4 *)(lVar13 + 0x98) = uVar4;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x15:
    FUN_001b4b30(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 0x16:
    FUN_0018ffd0(param_1,0);
    uVar3 = FUN_001900a0();
    uVar11 = FUN_00190910(&DAT_00244640,0x21,uVar3);
    if (uVar11 != 0xffffffff) {
      uVar11 = *(uint *)(&DAT_00244644 + (ulong)uVar11 * 8);
      FUN_00190370(param_2,(&PTR_s_r8_usr_005ed480)[(ulong)uVar11 * 2]);
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
        uVar4 = *(undefined4 *)(&DAT_005ed488 + (ulong)uVar11 * 0x10);
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        bVar1 = *(byte *)(lVar17 + 0x80);
        lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
        *(undefined4 *)(lVar13 + 0x94) = 0x43;
        *(undefined4 *)(lVar13 + 0x98) = uVar4;
        *(byte *)(lVar17 + 0x80) = bVar1 + 1;
      }
      FUN_00190370(param_2,", ");
      FUN_001b1900(param_1,1,param_2);
      return;
    }
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(1000,0x1bb90c);
    (*pcVar2)();
  case 0x17:
    FUN_0018ffd0(param_1,1);
    uVar6 = FUN_001900a0();
    uVar11 = uVar6 & 0xff;
    uVar5 = uVar6 >> 8 & 0x1f;
    uVar10 = uVar6 >> 8;
    uVar12 = (ulong)uVar11;
    if (uVar5 == 0xe) {
LAB_001ba0e0:
      if (9 < uVar12) {
LAB_001ba0e8:
        FUN_001903f0(param_2,"#0x%lx",uVar12);
        goto LAB_001b7388;
      }
    }
    else {
      if (((uVar10 & 0xc) == 8) || ((uVar6 >> 0xb & 1) == 0)) {
        uVar12 = (ulong)uVar11 << ((uVar5 >> 1 & 3) << 3);
        goto LAB_001ba0e0;
      }
      if ((uVar10 & 0xe) == 0xc) {
        iVar7 = (uVar10 & 1) + 1;
        uVar12 = (ulong)(0xffff >> ((2 - iVar7) * 8 & 0x1fU) | uVar11 << (ulong)(uint)(iVar7 * 8));
        goto LAB_001ba0e8;
      }
      if (uVar5 == 0x1e) {
        uVar21 = 0;
        if ((uVar6 & 1) != 0) {
          uVar21 = 0xff;
        }
        if ((uVar6 >> 1 & 1) != 0) {
          uVar21 = uVar21 | 0xff00;
        }
        if ((uVar6 >> 2 & 1) != 0) {
          uVar21 = uVar21 | 0xff0000;
        }
        if ((uVar6 >> 3 & 1) != 0) {
          uVar21 = uVar21 | 0xff000000;
        }
        if ((uVar6 >> 4 & 1) != 0) {
          uVar21 = uVar21 | 0xff00000000;
        }
        if ((uVar6 >> 5 & 1) != 0) {
          uVar21 = uVar21 | 0xff0000000000;
        }
        if ((uVar6 >> 6 & 1) == 0) {
          uVar12 = uVar21;
          if ((uVar6 >> 7 & 1) == 0) goto LAB_001ba0e0;
          uVar12 = uVar21 | 0xff00000000000000;
        }
        else {
          uVar12 = uVar21 | 0xff000000000000;
          if ((uVar6 >> 7 & 1) != 0) {
            uVar12 = uVar21 | 0xffff000000000000;
          }
        }
        goto LAB_001ba0e8;
      }
      uVar12 = 0;
    }
    FUN_001903f0(param_2,&DAT_001fdd50,uVar12);
LAB_001b7388:
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar17 + 0x80);
    lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined4 *)(lVar13 + 0x94) = 2;
    *(int *)(lVar13 + 0x98) = (int)uVar12;
    *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    return;
  case 0x18:
    FUN_00190370(param_2,&DAT_001fe588);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
      return;
    }
    lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar13 + 0x80);
    *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
    *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    return;
  case 0x19:
    goto switchD_001b5064_default;
  case 0x1a:
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar4 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar4);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    lVar13 = *(long *)(param_1 + 800);
    FUN_0018ffd0(param_1,0);
    FUN_00190080();
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
      FUN_0018ffd0(param_1,0);
      uVar4 = FUN_00190080();
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe578);
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    FUN_00190370(param_2,", ");
    break;
  case 0x1b:
    FUN_0018ffd0(param_1,0);
    uVar4 = FUN_00190080();
    uVar9 = FUN_001e7414(*(undefined8 *)(param_1 + 0x3b0),uVar4,1);
    uVar14 = *(undefined8 *)(param_1 + 0x3b0);
    uVar15 = 2;
    goto LAB_001b7100;
  case 0x1c:
    FUN_001b1270(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 0x1d:
    FUN_001b2760(param_1,0,param_2);
    FUN_00190370(param_2,", ");
    break;
  case 0x1e:
    FUN_0018ffd0(param_1,0);
    uVar4 = FUN_00190080();
    uVar9 = FUN_001e7414(*(undefined8 *)(param_1 + 0x3b0),uVar4,1);
    uVar14 = *(undefined8 *)(param_1 + 0x3b0);
    uVar15 = 3;
LAB_001b7100:
    uVar4 = FUN_001e7414(uVar14,uVar4,uVar15);
    uVar14 = *(undefined8 *)(param_1 + 800);
    uVar8 = FUN_0018ffb0(param_1);
    bVar1 = *(byte *)(param_1 + 0x366);
    lVar13 = FUN_001bddc0(uVar14,uVar8);
    if (lVar13 == 0) {
      cVar23 = '\0';
    }
    else {
      cVar23 = *(char *)(lVar13 + (ulong)bVar1);
      if (cVar23 == -0x80) {
        cVar23 = '\0';
      }
    }
    FUN_00190370(param_2,&DAT_001f95c0);
    uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar9);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 1;
      *(undefined4 *)(lVar13 + 0x98) = uVar9;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe570);
    uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(uVar4);
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 1;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(char *)(lVar13 + 0xb1) = cVar23;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    FUN_00190370(param_2,&DAT_001fe578);
    *(char *)(param_1 + 0x366) = *(char *)(param_1 + 0x366) + '\x01';
    FUN_00190370(param_2,", ");
    break;
  case 0x1f:
    FUN_001b2484(param_1,0,param_2);
    goto switchD_001b5300_caseD_e;
  case 0x20:
    FUN_001b1900(param_1,4,param_2);
    break;
  case 0x21:
    FUN_001b1270(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,0,param_2);
    return;
  case 0x22:
    FUN_001b1600(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,0,param_2);
    return;
  case 0x23:
    FUN_001b1600(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fd610);
    return;
  case 0x24:
    FUN_001b1600(param_1,4,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x25:
    FUN_001b13a0(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,0,param_2);
    return;
  case 0x26:
    FUN_001b13a0(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fd610);
    return;
  case 0x27:
    FUN_001b13a0(param_1,4,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x28:
    FUN_001b1270(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fd610);
    return;
  case 0x29:
    FUN_001b1270(param_1,4,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x2a:
    FUN_001b2760(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,0,param_2);
    return;
  case 0x2b:
    FUN_001b2760(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fd610);
    return;
  case 0x2c:
    FUN_001b2760(param_1,4,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x2d:
    FUN_001b2484(param_1,2,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,0,param_2);
    return;
  case 0x2e:
    FUN_001b2484(param_1,3,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fd610);
    return;
  case 0x2f:
    FUN_001b2484(param_1,4,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b3ad0(param_1,1,param_2);
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x30:
switchD_001b5064_caseD_f:
    FUN_001b2e50(param_1,param_2);
    return;
  case 0x31:
switchD_001b5064_caseD_10:
    FUN_001b2ff0(param_1,param_2);
    return;
  case 0x32:
switchD_001b5064_caseD_13:
    FUN_001b4340(param_1,0,param_2,0);
    return;
  case 0x33:
    FUN_001b3c30(param_1,0,param_2,0);
    return;
  case 0x34:
    FUN_001b3dd0(param_1,0,param_2);
    return;
  case 0x35:
    FUN_001b1e90(param_1,0,param_2);
    return;
  case 0x36:
    uVar14 = FUN_0018ffd0(param_1,0);
    uVar15 = FUN_0018ffd0(param_1,1);
    FUN_00190370(param_2,&DAT_001fdf80);
    FUN_001b3500(param_1,1);
    lVar13 = *(long *)(param_1 + 800);
    FUN_00190080(uVar14);
    uVar16 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar16);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = FUN_00190080(uVar14);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar4;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_00190080(uVar15);
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = FUN_00190080(uVar15);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar4;
    }
    FUN_00190370(param_2,&DAT_001fe598);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 3) {
      return;
    }
    lVar13 = *(long *)(param_1 + 0x310);
    *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
    lVar13 = *(long *)(lVar13 + 0xf0);
    *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
    return;
  case 0x37:
    uVar14 = FUN_0018ffd0(param_1,0);
    uVar15 = FUN_0018ffd0(param_1,1);
    FUN_00190370(param_2,&DAT_001fdf80);
    FUN_001b3500(param_1,1);
    lVar13 = *(long *)(param_1 + 800);
    FUN_00190080(uVar14);
    uVar16 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar16);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = FUN_00190080(uVar14);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) = uVar4;
    }
    FUN_00190370(param_2,", ");
    lVar13 = *(long *)(param_1 + 800);
    FUN_00190080(uVar15);
    uVar14 = (**(code **)(lVar13 + 0x78))();
    FUN_00190370(param_2,uVar14);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      uVar4 = FUN_00190080(uVar15);
      *(undefined4 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x9c) = uVar4;
    }
    FUN_00190370(param_2,&DAT_001fe590);
    lVar13 = *(long *)(param_1 + 800);
    iVar7 = *(int *)(lVar13 + 0x60);
    if (iVar7 == 0) {
      return;
    }
    lVar20 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
    bVar1 = *(byte *)(lVar20 + 0x80);
    lVar17 = lVar20 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
    *(undefined8 *)(lVar17 + 0x8c) = DAT_0020c5a8;
    *(undefined4 *)(lVar17 + 0xa8) = 1;
    if (iVar7 != 3) {
      return;
    }
    *(undefined1 *)(lVar13 + 0x6c) = 0;
    *(byte *)(lVar20 + 0x80) = bVar1 + 1;
    return;
  case 0x38:
    FUN_0018ffd0(param_1,0);
    iVar7 = FUN_001900a0();
    pcVar19 = "csync";
    if (iVar7 != 0) {
      pcVar19 = (char *)0x0;
    }
    FUN_00190370(param_2,pcVar19);
    return;
  case 0x39:
    FUN_001b1900(param_1,3,param_2);
    return;
  case 0x3a:
    FUN_001b10d4(param_1,2,param_2);
    return;
  default:
    goto switchD_001b5300_default;
  }
LAB_001b5108:
  uVar12 = (CONCAT44(uVar10,uVar11) >> 0x1e & 0x1f) - 1;
  if (0x1c < uVar12) goto switchD_001b5318_default;
  switch(uVar12 & 0xffffffff) {
  case 0:
    break;
  case 1:
    goto switchD_001b9ce0_caseD_1;
  case 2:
    FUN_001b3ad0(param_1,1,param_2);
    goto LAB_001b5130;
  case 3:
    FUN_001b1900(param_1,1,param_2);
    goto LAB_001b5130;
  case 4:
    uVar14 = FUN_0018ffd0(param_1,1);
    uVar10 = FUN_001900a0();
    uVar11 = (uVar10 >> 7) << 0x1f;
    uVar5 = 0x3e000000;
    if ((uVar10 >> 6 & 1) == 0) {
      uVar11 = uVar11 | 0x40000000;
      uVar5 = 0;
    }
    FUN_001903f0((double)(float)((uVar10 >> 4 & 3) << 0x17 | (uVar10 & 0xf) << 0x13 | uVar5 | uVar11
                                ),param_2,&DAT_001fe5a0);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 4;
      uVar10 = FUN_001900a0(uVar14);
      uVar5 = 0x3e000000;
      uVar11 = (uVar10 >> 7) << 0x1f;
      if ((uVar10 >> 6 & 1) == 0) {
        uVar11 = uVar11 | 0x40000000;
        uVar5 = 0;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(double *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x98) =
           (double)(float)((uVar10 >> 4 & 3) << 0x17 | (uVar10 & 0xf) << 0x13 | uVar11 | uVar5);
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 5:
    FUN_00190370(param_2,&DAT_001fe5a8);
    FUN_001b10d4(param_1,4,param_2);
    goto LAB_001b5130;
  case 6:
    FUN_0018ffd0(param_1,3);
    uVar11 = FUN_001900a0();
    if (uVar11 < 10) {
      FUN_001903f0(param_2,&DAT_001fe0f8,uVar11);
    }
    else {
      FUN_001903f0(param_2,"{0x%x}",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(uint *)(lVar13 + 0x98) = uVar11;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    break;
  case 7:
    goto switchD_001ba944_caseD_6;
  case 8:
    FUN_0018ffd0(param_1,1);
    uVar4 = FUN_001900a0();
    FUN_001903f0(param_2,&DAT_001fdfc8,uVar4);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 0x40;
      *(undefined4 *)(lVar13 + 0x98) = uVar4;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
  default:
switchD_001b5318_default:
    FUN_00190370(param_2,", ");
LAB_001b5130:
    uVar12 = ((ulong)(uVar10 >> 3) & 0x7f) - 1;
    if (uVar12 < 0x40) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        FUN_001b3890(param_1,1,param_2);
        return;
      case 1:
        FUN_001b3ad0(param_1,2,param_2);
        break;
      case 2:
        FUN_001b1900(param_1,3,param_2);
        break;
      case 3:
        goto switchD_001b5064_default;
      case 4:
        goto switchD_001b9ce0_caseD_1;
      case 5:
        FUN_00190370(param_2,", ");
        break;
      case 6:
        FUN_001b2d64(param_1,1,param_2);
        return;
      case 7:
        FUN_001b0c20(param_1,1,param_2);
        return;
      case 8:
        FUN_001b3100(param_1,param_2,0);
        return;
      case 9:
        FUN_001b28e0(param_1,2,param_2);
        return;
      case 10:
        FUN_001b1900(param_1,2,param_2);
        break;
      case 0xb:
switchD_001b8f50_caseD_b:
        FUN_001b1f80(param_1,1,param_2);
        return;
      case 0xc:
        FUN_001b2c50(param_1,1,param_2);
        return;
      case 0xd:
        FUN_001b10d4(param_1,3,param_2);
        break;
      case 0xe:
switchD_001b8f50_caseD_e:
        FUN_001b1c40(param_1,2,param_2,0);
        return;
      case 0xf:
        FUN_001b3890(param_1,2,param_2);
        break;
      case 0x10:
switchD_001b8f50_caseD_10:
        FUN_001b1c40(param_1,2,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x11:
        FUN_001b4340(param_1,2,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x12:
        FUN_001b4540(param_1,2,param_2);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x13:
        FUN_001b4340(param_1,1,param_2,0);
        return;
      case 0x14:
        FUN_001b4540(param_1,1,param_2);
        return;
      case 0x15:
        FUN_001b4834(param_1,1,param_2,0);
        return;
      case 0x16:
        FUN_001b4834(param_1,2,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x17:
        goto switchD_001b51d4_caseD_1;
      case 0x18:
        FUN_001b37d0(param_1,1,param_2);
        return;
      case 0x19:
        FUN_001b1060(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,2,param_2);
        break;
      case 0x1a:
        FUN_001b2600(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b3890(param_1,2,param_2);
        return;
      case 0x1b:
        FUN_00190370(param_2,&DAT_001fe588);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        FUN_001b3770(*(undefined8 *)(param_1 + 0x310),0);
        return;
      case 0x1c:
        FUN_001b29d0(param_1,4,param_2);
        break;
      case 0x1d:
        FUN_001b29d0(param_1,6,param_2);
        break;
      case 0x1e:
        FUN_001b29d0(param_1,8,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        break;
      case 0x20:
        FUN_001b29d0(param_1,10,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,1,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,10,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,2,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,10,param_2);
        break;
      case 0x21:
        FUN_00190370(param_2,&DAT_001fe570);
        FUN_001b1900(param_1,3,param_2);
      case 0x1f:
        FUN_00190370(param_2,"[]}, ");
        break;
      case 0x22:
        FUN_001b29d0(param_1,0xc,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,1,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,0xc,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,2,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,0xc,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,3,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,0xc,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,5,param_2);
        FUN_001b0e70(param_1,7,param_2);
        return;
      case 0x23:
        FUN_001b1c40(param_1,1,param_2,0);
        return;
      case 0x24:
        uVar14 = FUN_0018ffd0(param_1,1);
        uVar15 = FUN_0018ffd0(param_1,2);
        uVar11 = FUN_001900a0();
        uVar10 = FUN_001900a0(uVar15);
        uVar12 = FUN_00190020(uVar14);
        if ((uVar12 & 1) == 0) goto LAB_001bb08c;
        FUN_00190370(param_2,&DAT_001fdf80);
        lVar13 = *(long *)(param_1 + 800);
        FUN_00190080(uVar14);
        uVar15 = (**(code **)(lVar13 + 0x78))();
        FUN_00190370(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          lVar13 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
          *(undefined4 *)(lVar13 + 0x94) = 3;
          uVar4 = FUN_00190080(uVar14);
          lVar17 = *(long *)(param_1 + 0x310);
          *(undefined4 *)(lVar13 + 0x98) = uVar4;
          uVar14 = DAT_0020c578;
          lVar13 = *(long *)(lVar17 + 0xf0);
          lVar13 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
          *(undefined4 *)(lVar13 + 0x9c) = 0;
          *(undefined8 *)(lVar13 + 0xa0) = uVar14;
          *(undefined1 *)(lVar13 + 0xb1) = 1;
        }
        uVar11 = uVar11 & 0xff;
        uVar10 = uVar10 & 0x100;
        if (uVar11 == 0) {
          if (uVar10 == 0) goto LAB_001b9770;
          uVar5 = 0;
          puVar18 = &DAT_001faa60;
LAB_001b9734:
          FUN_001903f0(param_2,", #%s%u",puVar18,uVar5);
        }
        else {
          uVar5 = uVar11 << 1;
          if (uVar5 < 10) {
            puVar18 = &DAT_001fe648;
            if (uVar10 != 0) {
              puVar18 = &DAT_001faa60;
            }
            goto LAB_001b9734;
          }
          puVar18 = &DAT_001fe648;
          if (uVar10 != 0) {
            puVar18 = &DAT_001faa60;
          }
          FUN_001903f0(param_2,&DAT_001fdf88,puVar18,uVar5);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
          lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
          if (uVar10 == 0) {
            *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0xa4) = uVar5;
          }
          else {
            *(uint *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0xa4) = uVar11 * -2;
          }
        }
LAB_001b9770:
        FUN_00190370(param_2,&DAT_001fe598);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
        return;
      case 0x25:
        FUN_001b29d0(param_1,3,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 0x26:
        FUN_001b29d0(param_1,5,param_2);
        break;
      case 0x27:
        FUN_001b29d0(param_1,7,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,7,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,7,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,1,param_2);
        FUN_001b0e70(param_1,3,param_2);
        return;
      case 0x28:
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,6,param_2);
        break;
      case 0x29:
        FUN_001b1270(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,2,param_2);
        return;
      case 0x2a:
        FUN_001b2760(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,2,param_2);
        return;
      case 0x2b:
        FUN_001b13a0(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,2,param_2);
        return;
      case 0x2c:
        FUN_001b1600(param_1,1,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,2,param_2);
        return;
      case 0x2d:
        FUN_001b1270(param_1,2,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,3,param_2);
        return;
      case 0x2e:
        FUN_001b2760(param_1,2,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,3,param_2);
        return;
      case 0x2f:
        FUN_001b13a0(param_1,2,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,3,param_2);
        return;
      case 0x30:
        FUN_001b1600(param_1,2,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,3,param_2);
        return;
      case 0x31:
        FUN_00190370(param_2,&DAT_001fe628);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        FUN_001b34f0(*(undefined8 *)(param_1 + 0x310));
        return;
      case 0x32:
        FUN_001b3c30(param_1,1,param_2,0);
        return;
      case 0x33:
        FUN_001b3c30(param_1,2,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x34:
        FUN_001b1e90(param_1,1,param_2);
        return;
      case 0x35:
        FUN_001b3dd0(param_1,1,param_2);
        return;
      case 0x36:
        FUN_001b3970(param_1,1,param_2);
        return;
      case 0x37:
        FUN_001b4b30(param_1,1,param_2);
        return;
      case 0x38:
        goto switchD_001ba944_caseD_24;
      case 0x39:
        FUN_001b3100(param_1,param_2,2);
        return;
      case 0x3a:
        FUN_001b0f64(param_1,3,param_2);
        return;
      case 0x3b:
        FUN_001b3fa0(param_1,param_2,1);
        return;
      case 0x3c:
        uVar14 = FUN_0018ffd0(param_1,1);
        uVar15 = FUN_0018ffd0(param_1,2);
        uVar12 = FUN_00190020(uVar14);
        if ((uVar12 & 1) != 0) {
          FUN_00190370(param_2,&DAT_001fdf80);
          FUN_001b3500(param_1,1);
          lVar13 = *(long *)(param_1 + 800);
          FUN_00190080(uVar14);
          uVar16 = (**(code **)(lVar13 + 0x78))();
          FUN_00190370(param_2,uVar16);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
            lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            bVar1 = *(byte *)(lVar13 + 0x80);
            uVar4 = FUN_00190080(uVar14);
            *(undefined4 *)(lVar13 + (long)(int)(uint)bVar1 * 0x30 + 0x98) = uVar4;
          }
          iVar7 = FUN_00190080(uVar15);
          if (iVar7 != 0) {
            FUN_00190370(param_2,", ");
            uVar14 = (**(code **)(*(long *)(param_1 + 800) + 0x78))(iVar7);
            FUN_00190370(param_2,uVar14);
            if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
              lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
              *(int *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x9c) = iVar7;
            }
          }
          FUN_00190370(param_2,&DAT_001fe598);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 3) {
            return;
          }
          lVar13 = *(long *)(param_1 + 0x310);
          *(undefined1 *)(*(long *)(param_1 + 800) + 0x6c) = 0;
          lVar13 = *(long *)(lVar13 + 0xf0);
          *(char *)(lVar13 + 0x80) = *(char *)(lVar13 + 0x80) + '\x01';
          return;
        }
LAB_001bb08c:
        FUN_001b1900(param_1,1,param_2);
        return;
      case 0x3d:
        FUN_001b3fa0(param_1,param_2,2);
        return;
      case 0x3e:
      case 0x3f:
        FUN_001b3fa0(param_1,param_2,4);
        return;
      default:
        goto switchD_001b8f50_default;
      }
    }
    else {
switchD_001b8f50_default:
      FUN_001b1900(param_1,1,param_2);
    }
    uVar12 = ((ulong)(uVar10 >> 10) & 0x1f) - 1;
    if (uVar12 < 0x16) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        return;
      case 1:
switchD_001b9ce0_caseD_1:
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 2:
        FUN_001b1900(param_1,3,param_2);
        break;
      case 3:
        FUN_001b2240(param_1,2,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b2240(param_1,3,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b2240(param_1,4,param_2);
        FUN_00190370(param_2,", ");
        FUN_001b1900(param_1,5,param_2);
        return;
      case 4:
        FUN_001b1900(param_1,2,param_2);
        break;
      case 5:
        goto switchD_001b51d4_caseD_6;
      case 6:
        FUN_001b0b50(param_1,2,param_2);
        return;
      case 7:
        FUN_001b21b0(param_1,4,param_2);
        break;
      case 8:
        FUN_001b21b0(param_1,2,param_2);
        return;
      case 9:
        FUN_001b1900(param_1,4,param_2);
        return;
      case 10:
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        break;
      case 0xb:
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        break;
      case 0xc:
        FUN_001b1900(param_1,1,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,8,param_2);
        break;
      case 0xd:
        goto switchD_001b9ce0_caseD_d;
      case 0xe:
        FUN_001b3ad0(param_1,4,param_2);
        break;
      case 0xf:
        FUN_001b3ad0(param_1,5,param_2);
        FUN_001b0e70(param_1,7,param_2);
        return;
      case 0x10:
        goto switchD_001ba944_caseD_1c;
      case 0x11:
        FUN_00190370(param_2,&DAT_001fe630);
        FUN_001b3ad0(param_1,1,param_2);
        FUN_001b0e70(param_1,3,param_2);
        return;
      case 0x12:
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,8,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,8,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,7,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,8,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,1,param_2);
        FUN_001b0e70(param_1,3,param_2);
        return;
      case 0x13:
        FUN_00190370(param_2,&DAT_001fe628);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        *(undefined1 *)(*(long *)(*(long *)(param_1 + 0x310) + 0xf0) + 0x60) = 1;
        return;
      case 0x14:
        FUN_001b1b60(param_1,3,param_2);
        return;
      case 0x15:
        FUN_00190370(param_2,&DAT_001fe638);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        FUN_001b3770(*(undefined8 *)(param_1 + 0x310),1);
        return;
      default:
        goto switchD_001b9ce0_default;
      }
    }
    else {
switchD_001b9ce0_default:
      FUN_00190370(param_2,", ");
    }
    uVar12 = ((ulong)(uVar10 >> 0xf) & 0x3f) - 1;
    if (uVar12 < 0x25) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        FUN_001b1900(param_1,4,param_2);
        break;
      case 1:
        return;
      case 2:
        FUN_001b1f80(param_1,2,param_2);
        return;
      case 3:
        FUN_001b2c50(param_1,2,param_2);
        return;
      case 4:
        FUN_001b28e0(param_1,3,param_2);
        return;
      case 5:
        FUN_001b3214(param_1,param_2);
        return;
      case 6:
switchD_001ba944_caseD_6:
        FUN_001b32b0(param_1,param_2);
        return;
      case 7:
        uVar14 = FUN_0018ffd0(param_1,3);
        uVar15 = FUN_0018ffd0(param_1,4);
        uVar11 = FUN_001900a0();
        uVar11 = uVar11 & 0x1000;
        iVar7 = FUN_00190080(uVar14);
        if (iVar7 != 0) {
          puVar18 = &DAT_001fe648;
          if (uVar11 != 0) {
            puVar18 = &DAT_001faa60;
          }
          FUN_00190370(param_2,puVar18);
          lVar13 = *(long *)(param_1 + 800);
          FUN_00190080(uVar14);
          uVar16 = (**(code **)(lVar13 + 0x78))();
          FUN_00190370(param_2,uVar16);
          if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
            lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
            uVar4 = FUN_00190080(uVar14);
            lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
            cVar23 = *(char *)(lVar17 + 0x80);
            lVar13 = lVar17 + (ulong)*(byte *)(lVar17 + 0x80) * 0x30;
            *(undefined4 *)(lVar13 + 0x98) = uVar4;
            *(bool *)(lVar13 + 0xb0) = uVar11 != 0;
            *(undefined1 *)(lVar13 + 0xb1) = 1;
            *(char *)(lVar17 + 0x80) = cVar23 + '\x01';
          }
          uVar11 = FUN_001900a0(uVar15);
          uVar11 = uVar11 >> 0xd & 7;
          uVar10 = FUN_001900a0(uVar15);
          if (uVar11 == 0) {
            return;
          }
          if ((uVar10 & 0xfff) == 0 && uVar11 == 2) {
            return;
          }
          FUN_001b2a84(param_1,param_2,uVar11,uVar10 & 0xfff);
          return;
        }
        uVar10 = FUN_001900a0(uVar15);
        uVar10 = uVar10 & 0xfff;
        puVar18 = &DAT_001fe648;
        if (uVar11 != 0) {
          puVar18 = &DAT_001faa60;
        }
        if (uVar10 < 10) {
          FUN_001903f0(param_2,"#%s%u",puVar18,uVar10);
        }
        else {
          FUN_001903f0(param_2,"#%s0x%x",puVar18,uVar10);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar17 + 0x80);
        lVar13 = lVar17 + (ulong)*(byte *)(lVar17 + 0x80) * 0x30;
        *(undefined4 *)(lVar13 + 0x94) = 2;
        *(uint *)(lVar13 + 0x98) = uVar10;
        *(bool *)(lVar13 + 0xb0) = uVar11 != 0;
        *(char *)(lVar17 + 0x80) = cVar23 + '\x01';
        return;
      case 8:
        FUN_001b4834(param_1,2,param_2,0);
        return;
      case 9:
        FUN_001b3890(param_1,3,param_2);
        break;
      case 10:
        FUN_001b4834(param_1,3,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0xb:
        FUN_0018ffd0(param_1,3);
        uVar10 = FUN_001900a0();
        uVar11 = uVar10 & 0xff;
        puVar18 = &DAT_001faa60;
        if ((uVar10 & 0x100) != 0) {
          puVar18 = &DAT_001fe648;
        }
        if (uVar11 < 10) {
          FUN_001903f0(param_2,"#%s%u",puVar18,uVar11);
        }
        else {
          FUN_001903f0(param_2,"#%s0x%x",puVar18,uVar11);
        }
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar13 + 0x80);
        lVar17 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
        *(undefined4 *)(lVar17 + 0x94) = 2;
        *(uint *)(lVar17 + 0x98) = uVar11;
        *(char *)(lVar13 + 0x80) = cVar23 + '\x01';
        return;
      case 0xc:
        uVar14 = FUN_0018ffd0(param_1,3);
        FUN_0018ffd0(param_1,4);
        lVar13 = FUN_001900a0();
        puVar18 = &DAT_001faa60;
        if (lVar13 != 0) {
          puVar18 = &DAT_001fe648;
        }
        FUN_00190370(param_2,puVar18);
        lVar13 = *(long *)(param_1 + 800);
        FUN_00190080(uVar14);
        uVar15 = (**(code **)(lVar13 + 0x78))();
        FUN_00190370(param_2,uVar15);
        if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
          return;
        }
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        *(undefined4 *)(lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30 + 0x94) = 1;
        uVar4 = FUN_00190080(uVar14);
        lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
        cVar23 = *(char *)(lVar13 + 0x80);
        lVar17 = lVar13 + (ulong)*(byte *)(lVar13 + 0x80) * 0x30;
        *(undefined4 *)(lVar17 + 0x98) = uVar4;
        *(undefined1 *)(lVar17 + 0xb1) = 1;
        *(char *)(lVar13 + 0x80) = cVar23 + '\x01';
        return;
      case 0xd:
        FUN_001b22c0(param_1,3,param_2);
        return;
      case 0xe:
        FUN_00190370(param_2,", ");
        break;
      case 0xf:
        FUN_001b2240(param_1,4,param_2);
        return;
      case 0x10:
        FUN_001b3890(param_1,2,param_2);
        return;
      case 0x11:
        FUN_001b1900(param_1,3,param_2);
        break;
      case 0x12:
        FUN_001b0fe0(param_1,3,param_2,0xb4,0x5a);
        return;
      case 0x13:
        FUN_001b0fe0(param_1,4,param_2,0x5a,0);
        return;
      case 0x14:
        FUN_001b3ad0(param_1,1,param_2);
        break;
      case 0x15:
        FUN_001b3ad0(param_1,2,param_2);
        FUN_001b0e70(param_1,4,param_2);
        return;
      case 0x16:
        FUN_001b1900(param_1,1,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,2,param_2);
        return;
      case 0x17:
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,3,param_2);
        FUN_001b0e70(param_1,5,param_2);
        return;
      case 0x18:
        FUN_001b0e70(param_1,6,param_2);
        return;
      case 0x19:
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,2,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,8,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,3,param_2);
        return;
      case 0x1a:
        goto switchD_001ba944_caseD_1a;
      case 0x1b:
        FUN_001b21b0(param_1,4,param_2);
        return;
      case 0x1c:
switchD_001ba944_caseD_1c:
        FUN_001b21b0(param_1,3,param_2);
        return;
      case 0x1d:
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,1,param_2);
        FUN_001b0e70(param_1,3,param_2);
        return;
      case 0x1e:
        FUN_001b1900(param_1,7,param_2);
        FUN_00190370(param_2,&DAT_001fe630);
        FUN_001b3ad0(param_1,1,param_2);
        FUN_001b0e70(param_1,3,param_2);
        return;
      case 0x1f:
        FUN_001b2d64(param_1,2,param_2);
        return;
      case 0x20:
        FUN_001b0f64(param_1,2,param_2);
        return;
      case 0x21:
        FUN_001b4160(param_1,3,param_2,1);
        FUN_00190370(param_2,&DAT_001fd610);
        return;
      case 0x22:
        FUN_001b4160(param_1,2,param_2,0);
        return;
      case 0x23:
        FUN_001b3970(param_1,2,param_2);
        return;
      case 0x24:
switchD_001ba944_caseD_24:
        FUN_001b3370(param_1,param_2);
        return;
      default:
        goto switchD_001ba944_default;
      }
    }
    else {
switchD_001ba944_default:
      FUN_001b1900(param_1,2,param_2);
    }
    uVar12 = ((ulong)(uVar10 >> 0x15) & 0xf) - 1;
    if (0xb < uVar12) {
      return;
    }
    switch(uVar12 & 0xffffffff) {
    case 0:
      FUN_00190370(param_2,", ");
      break;
    case 1:
switchD_001b51d4_caseD_1:
      FUN_001b2240(param_1,3,param_2);
      FUN_00190370(param_2,", ");
      FUN_001b2240(param_1,4,param_2);
      FUN_00190370(param_2,", ");
      FUN_001b1900(param_1,5,param_2);
      return;
    case 2:
      FUN_001b1900(param_1,3,param_2);
      FUN_00190370(param_2,", ");
      FUN_001b2240(param_1,4,param_2);
      return;
    case 3:
      FUN_0018ffd0(param_1,3);
      uVar11 = FUN_001900a0();
      if (uVar11 == 0) {
        return;
      }
      if (uVar11 < 10) {
        FUN_001903f0(param_2,", lsl #%u",uVar11);
      }
      else {
        FUN_001903f0(param_2,", lsl #0x%x",uVar11);
      }
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar13 = lVar13 + (long)(int)(*(byte *)(lVar13 + 0x80) - 1) * 0x30;
      *(undefined4 *)(lVar13 + 0x8c) = 2;
      *(uint *)(lVar13 + 0x90) = uVar11;
      return;
    case 4:
      FUN_0018ffd0(param_1,3);
      uVar12 = FUN_001900a0();
      uVar21 = uVar12 & 0xffffffff;
      uVar11 = (uint)uVar12;
      if (uVar11 == 0) {
        uVar21 = 0x20;
      }
      else if (uVar11 < 10) {
        FUN_001903f0(param_2,", asr #%u",uVar12);
        goto LAB_001bb2e4;
      }
      uVar11 = (uint)uVar21;
      FUN_001903f0(param_2,", asr #0x%x",uVar21);
LAB_001bb2e4:
      if (*(int *)(*(long *)(param_1 + 800) + 0x60) == 0) {
        return;
      }
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      lVar13 = lVar13 + (long)(int)(*(byte *)(lVar13 + 0x80) - 1) * 0x30;
      *(undefined4 *)(lVar13 + 0x8c) = 1;
      *(uint *)(lVar13 + 0x90) = uVar11;
      return;
    case 5:
      FUN_001b0b50(param_1,3,param_2);
      return;
    case 6:
switchD_001b51d4_caseD_6:
      FUN_001b33f0(param_1,param_2);
      return;
    case 7:
      FUN_001b0fe0(param_1,5,param_2,0x5a,0);
      return;
    case 8:
      FUN_00190370(param_2,&DAT_001fe630);
      break;
    case 9:
      FUN_00190370(param_2,&DAT_001fdf80);
      FUN_001b3500(param_1,1);
      break;
    case 10:
      FUN_001b0e70(param_1,3,param_2);
      return;
    case 0xb:
      FUN_001b1b60(param_1,4,param_2);
      return;
    default:
      goto switchD_001b5064_default;
    }
    uVar12 = ((ulong)(uVar10 >> 0x19) & 0xf) - 1;
    if (uVar12 < 0xb) {
      switch(uVar12 & 0xffffffff) {
      case 0:
        FUN_001b1900(param_1,3,param_2);
        if ((uVar10 >> 0x1d & 1) == 0) {
          return;
        }
        FUN_00190370(param_2,&DAT_001fe630);
        if ((uVar10 >> 0x1e & 1) != 0) {
          FUN_001b3ad0(param_1,5,param_2);
          FUN_001b0e70(param_1,7,param_2);
          return;
        }
        FUN_001b3ad0(param_1,4,param_2);
        return;
      case 1:
        FUN_001b1060(param_1,3,param_2);
        return;
      case 2:
switchD_001b9ce0_caseD_d:
        FUN_001b3ad0(param_1,3,param_2);
        return;
      case 3:
switchD_001ba944_caseD_1a:
        FUN_001b3ad0(param_1,4,param_2);
        FUN_001b0e70(param_1,6,param_2);
        return;
      case 4:
        FUN_001b29d0(param_1,10,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,4,param_2);
        return;
      case 5:
        FUN_001b29d0(param_1,4,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 6:
        FUN_001b29d0(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,4,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 7:
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 8:
        FUN_001b29d0(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,4,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fe610);
        FUN_001b37a0(param_1);
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fdf80);
        FUN_001b3500(param_1,1);
        FUN_001b29d0(param_1,6,param_2);
        FUN_00190370(param_2,&DAT_001fe620);
        FUN_001b37a0(param_1);
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 9:
        FUN_001b1900(param_1,5,param_2);
        FUN_00190370(param_2,&DAT_001fe630);
        FUN_001b3ad0(param_1,0,param_2);
        return;
      case 10:
        FUN_001b3890(param_1,3,param_2);
        return;
      }
    }
    FUN_001b22c0(param_1,4,param_2);
    return;
  case 9:
    FUN_00190370(param_2,", apsr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x100000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 10:
    FUN_00190370(param_2,", spsr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0xd00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0xb:
    goto switchD_001b8f50_caseD_b;
  case 0xc:
    FUN_00190370(param_2,&DAT_001fe588);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 2;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0xd:
    FUN_001b1900(param_1,2,param_2);
    goto LAB_001b5130;
  case 0xe:
    FUN_0018ffd0(param_1,2);
    uVar11 = FUN_001900a0();
    if (uVar11 < 10) {
      FUN_001903f0(param_2,&DAT_001fdfc0,uVar11);
    }
    else {
      FUN_001903f0(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar10 = *(byte *)(lVar13 + 0x80) - 1;
      *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                         (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    }
    break;
  case 0xf:
    FUN_001b3ad0(param_1,2,param_2);
    goto LAB_001b5130;
  case 0x10:
    FUN_00190370(param_2,&DAT_001fdf80);
    FUN_001b3500(param_1,1);
    goto LAB_001b5130;
  case 0x11:
    FUN_00190370(param_2,&DAT_001fe570);
    FUN_001b1900(param_1,1,param_2);
    FUN_00190370(param_2,&DAT_001fe570);
    FUN_001b1900(param_1,2,param_2);
    goto LAB_001b5130;
  case 0x12:
    FUN_00190370(param_2,", fpscr");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x600000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x13:
    FUN_00190370(param_2,", fpexc");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x400000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x14:
    FUN_00190370(param_2,", fpinst");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x500000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x15:
    FUN_00190370(param_2,", fpinst2");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x2e00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x16:
    FUN_00190370(param_2,", fpsid");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x800000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x17:
    FUN_00190370(param_2,", mvfr0");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x2f00000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x18:
    FUN_00190370(param_2,", mvfr1");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x3000000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x19:
    FUN_00190370(param_2,", mvfr2");
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar13 + 0x80);
      *(undefined8 *)(lVar13 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10 + 0x94) = 0x3100000001;
      *(byte *)(lVar13 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x1a:
    FUN_0018ffd0(param_1,3);
    uVar11 = FUN_001900a0();
    if (uVar11 < 10) {
      FUN_001903f0(param_2,&DAT_001fdfc0,uVar11);
    }
    else {
      FUN_001903f0(param_2,"[0x%x]",uVar11);
    }
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar13 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      uVar10 = *(byte *)(lVar13 + 0x80) - 1;
      *(uint *)(lVar13 + ((-(ulong)(uVar10 >> 0x1f) & 0xfffffffe00000000 | (ulong)uVar10 << 1) +
                         (long)(int)uVar10) * 0x10 + 0x88) = uVar11;
    }
    FUN_00190370(param_2,", ");
    FUN_001b1900(param_1,2,param_2);
    return;
  case 0x1b:
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x10 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(int *)(lVar13 + 0x98) = 0x10 - iVar7;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
    break;
  case 0x1c:
    FUN_0018ffd0(param_1,2);
    iVar7 = FUN_001900a0();
    FUN_001906d0(param_2,0x20 - iVar7);
    if (*(int *)(*(long *)(param_1 + 800) + 0x60) != 0) {
      lVar17 = *(long *)(*(long *)(param_1 + 0x310) + 0xf0);
      bVar1 = *(byte *)(lVar17 + 0x80);
      lVar13 = lVar17 + ((ulong)bVar1 * 2 + (ulong)bVar1) * 0x10;
      *(undefined4 *)(lVar13 + 0x94) = 2;
      *(int *)(lVar13 + 0x98) = 0x20 - iVar7;
      *(byte *)(lVar17 + 0x80) = bVar1 + 1;
    }
  }
switchD_001b5064_default:
  return;
switchD_001b5300_caseD_e:
  FUN_00190370(param_2,", ");
  goto LAB_001b5108;
}

