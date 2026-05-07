
/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_001a5484(undefined4 param_1,undefined4 param_2,ulong param_3,long param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  ulong uVar5;
  undefined *puVar6;
  uint uVar7;
  ulong uVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  undefined2 uVar12;
  ulong uVar13;
  undefined2 uVar14;
  
  uVar8 = param_3 & 0xffffffff;
  uVar7 = (uint)param_3;
  uVar1 = (uint)(uVar8 >> 8);
  uVar10 = (uint)(uVar8 >> 0x10);
  switch(param_2) {
  case 1:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = FUN_001974f4(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar10);
    if (uVar10 == 0xe) {
      FUN_00190100(param_4,0);
    }
    else {
      FUN_00190100(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 2:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = FUN_00196950(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar10);
    if (uVar10 == 0xe) {
      FUN_00190100(param_4,0);
    }
    else {
      FUN_00190100(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 3:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00196950(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 4:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 5:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar14 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar14);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 0xf) * 2));
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar14);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 != 0xc4f) goto LAB_001a70f4;
joined_r0x001ab038:
    if (uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7 >> 0x1c);
    goto LAB_001a580c;
  case 6:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 8 & 0xff0000000000000f;
    goto LAB_001a54d8;
  case 7:
    iVar2 = FUN_001992a0(param_4,uVar8);
    break;
  case 8:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) != 0xf) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
      return param_1;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    return 1;
  case 9:
    iVar2 = FUN_00196224(param_4,uVar8);
    break;
  case 10:
    FUN_00190140(param_4,uVar8 >> 9 & 1);
    goto switchD_001a555c_caseD_33;
  case 0xb:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0xc:
    iVar2 = FUN_0019aac0(param_4,uVar8);
    break;
  case 0xd:
    iVar2 = FUN_0019b680(param_4,uVar8);
    break;
  case 0xe:
    iVar2 = FUN_0019ac10(param_4,uVar8);
    break;
  case 0xf:
    FUN_00190140(param_4,uVar7 & 0xf | (uVar7 & 0xfff00) >> 4);
    goto switchD_001a555c_caseD_33;
  case 0x10:
    iVar2 = FUN_00197b14(param_4,uVar8);
    break;
  case 0x11:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = FUN_001974f4(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x12:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00196950(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x13:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      uVar12 = 0xb;
      iVar2 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      iVar2 = 3;
      uVar12 = *(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2);
      FUN_00190100(param_4,uVar12);
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      uVar14 = 0xb;
      iVar11 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      iVar11 = 3;
      uVar14 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2);
      FUN_00190100(param_4,uVar14);
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    FUN_00190100(param_4,uVar12);
    uVar3 = 1;
    if (iVar2 != 1) {
      uVar3 = param_1;
    }
    FUN_00190100(param_4,uVar14);
    param_1 = 1;
    if (iVar11 != 1) {
      param_1 = uVar3;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x14:
    uVar8 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a5aac;
  case 0x15:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x16:
    uVar5 = uVar8;
    goto LAB_001aadfc;
  case 0x17:
    uVar5 = uVar8 >> 0xc;
LAB_001aadfc:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar5 & 0xf) * 2));
    param_3 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a5908;
  case 0x18:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 0x10 & 0xf;
    goto LAB_001a5908;
  case 0x19:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    iVar2 = FUN_00195d10(param_4,(uVar7 >> 0x16 & 1) << 5 | (uVar7 & 0x100) >> 4 | uVar10 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x1a:
    iVar2 = FUN_0019aa04(param_4,uVar10 & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x1b:
    uVar10 = (uVar7 >> 0x16 & 1) << 5 | (uVar7 & 0x100) >> 4 | uVar10 & 0xf;
    lVar4 = FUN_001bb9e0(uVar10);
    if (lVar4 == 0) {
      return 0;
    }
    FUN_00190140(param_4,uVar10);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x1c:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    goto joined_r0x001a57e4;
  case 0x1d:
    goto switchD_001a555c_caseD_1d;
  case 0x1e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    param_3 = uVar8 >> 8 & 0xf;
    goto LAB_001a5908;
  case 0x1f:
    uVar5 = uVar8 >> 0xc & 0xfff000000000000f;
    goto LAB_001a54c8;
  case 0x20:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc000) == 0) {
      uVar3 = 0x43;
      if ((uVar10 != 1) && (uVar3 = 0x44, uVar10 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar10 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar10 != 0xc) {
        return 0;
      }
      uVar3 = 0x4e;
    }
    FUN_00190100(param_4,uVar3);
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc) == 0) {
      uVar3 = 0x43;
      if ((uVar10 != 1) && (uVar3 = 0x44, uVar10 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar10 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar10 != 0xc) {
        return 0;
      }
      uVar3 = 0x4e;
    }
    FUN_00190100(param_4,uVar3);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x21:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_001974f4(param_4,uVar7 & 0xfef);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar10 = uVar7 >> 0x1c;
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar10 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar10);
    if (uVar10 == 0xe) {
      FUN_00190100(param_4,0);
    }
    else {
      FUN_00190100(param_4,3);
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x22:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x23:
    uVar8 = uVar8 >> 0xc & 0xf;
    goto LAB_001a5aac;
  case 0x24:
    param_3 = param_3 & 0xf;
    goto LAB_001a57d4;
  case 0x25:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    iVar2 = FUN_00196950(param_4,uVar7 & 0xf6f);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 0x100000) != 0) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x26:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    if ((int)uVar5 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    uVar8 = uVar8 >> 0xc & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x27:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 0xf) * 2));
    param_3 = uVar8 >> 0xc & 0xf;
    goto LAB_001a5908;
  case 0x28:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar14 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar14);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 0xf) * 2));
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar14);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a58b8:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a58b8;
      FUN_00190100(param_4,0);
    }
    goto LAB_001a5520;
  case 0x29:
    iVar2 = FUN_00199880(param_4,uVar8);
    break;
  case 0x2a:
    iVar2 = FUN_00197a00(param_4,uVar8);
    break;
  case 0x2b:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,uVar12);
    uVar8 = uVar8 >> 0x17 & 1;
    if ((uVar7 & 0xf) == 0xf) {
      FUN_00190100(param_4,0xb);
      param_1 = 1;
      FUN_00190140(param_4,uVar8);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
      FUN_00190140(param_4,uVar8);
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x2c:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,uVar12);
    FUN_00190140(param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf00) >> 4 | uVar7 & 0xf);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) goto joined_r0x001ab038;
    goto LAB_001a70f4;
  case 0x2d:
    iVar2 = FUN_0019ad70(param_4,uVar8);
    break;
  case 0x2e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190140(param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf00) >> 4 | uVar7 & 0xf);
    goto joined_r0x001abd0c;
  case 0x2f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    goto LAB_001a7148;
  case 0x30:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190140(param_4,uVar7 & 0xfff | (uVar7 & 0xc00000) >> 10);
joined_r0x001abd0c:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    goto joined_r0x001a57e4;
  case 0x31:
    iVar2 = FUN_00198e90(param_4,uVar8);
    break;
  case 0x32:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    param_3 = param_3 & 0xfff;
    goto LAB_001a57d4;
  case 0x33:
    goto switchD_001a555c_caseD_33;
  case 0x34:
    iVar2 = FUN_001972b4(param_4,uVar8);
    break;
  case 0x35:
    iVar2 = FUN_0019aa04(param_4,uVar10 & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    FUN_00190140(param_4,param_3 & 0xfff);
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x36:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2);
LAB_001a7148:
    FUN_00190100(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar10;
    FUN_00190140(param_4,param_3 & 0xfff);
    goto joined_r0x001a7160;
  case 0x37:
    iVar2 = FUN_00198900(param_4,uVar8);
    break;
  case 0x38:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar10 = uVar7 & 0xfff;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if (((uVar7 >> 0x17 & 1) == 0) && (uVar10 = -uVar10, (param_3 & 0xfff) == 0)) {
      uVar10 = 0x80000000;
    }
    FUN_00190140(param_4,uVar10);
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
LAB_001a70f4:
    uVar7 = uVar7 >> 0x1c;
    FUN_00190140(param_4,uVar7);
    goto joined_r0x001a6ae4;
  case 0x39:
    uVar10 = uVar7 & 0xfff;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if (((uVar7 >> 0x17 & 1) == 0) && (uVar10 = -uVar10, (param_3 & 0xfff) == 0)) {
      uVar10 = 0x80000000;
    }
    FUN_00190140(param_4,uVar10);
    goto switchD_001a555c_caseD_33;
  case 0x3a:
    iVar2 = FUN_00198150(param_4,uVar8);
    break;
  case 0x3b:
    iVar2 = FUN_00198284(param_4,uVar8);
    break;
  case 0x3c:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    iVar2 = FUN_00196070(param_4,(uVar7 >> 0x17 & 1) << 0xc | (uVar7 & 0xf0000) >> 3 | uVar7 & 0xfff
                        );
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x3d:
  case 0x3e:
  case 0x114:
    FUN_00190140(param_4,param_3 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0x3f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_00196350(param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                                 uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0x40:
    iVar2 = FUN_00196350(param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                                 uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    break;
  case 0x41:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x42:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar8 >> 7 & 0x1f);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x43:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar8 = uVar8 >> 8 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x44:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    if ((int)uVar5 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x45:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar8 = uVar8 >> 0x10 & 0xf;
LAB_001a5aac:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    param_3 = param_3 & 0xf;
LAB_001a5908:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + param_3 * 2));
joined_r0x001a57e4:
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if ((int)uVar8 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar8);
    }
    else {
LAB_001a6ad4:
      FUN_00190140(param_4,uVar8);
      uVar7 = (uint)uVar8;
joined_r0x001a6ae4:
      if (uVar7 == 0xe) {
LAB_001a5524:
        FUN_00190100(param_4,0);
        goto switchD_001a555c_caseD_33;
      }
    }
LAB_001a580c:
    FUN_00190100(param_4,3);
    goto switchD_001a555c_caseD_33;
  case 0x46:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar8 >> 10 & 3);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x47:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar8 >> 10 & 3);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x48:
    iVar2 = FUN_00197ef0(param_4,uVar8);
    break;
  case 0x49:
    iVar2 = FUN_00198014(param_4,uVar8);
    break;
  case 0x4a:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 7) & 0x1f | (uVar7 & 0x40) >> 1);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x4b:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x4c:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar8 >> 7 & 0x1f);
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x4d:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    iVar2 = FUN_00196350(param_4,uVar7 & 0xfe0 | (uVar7 & 0xf0000) >> 3 |
                                 uVar7 & 0xf | (uVar7 & 0x800000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x4e:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    uVar1 = (uint)(uVar8 >> 7) & 0x1f;
    uVar10 = (uVar7 & 0x1f0000) >> 0x10;
    if (uVar10 < uVar1) {
      param_1 = 1;
      FUN_00190140(param_4,(1 << (ulong)(uVar10 + 1 & 0x1f)) - 1U ^
                           (1 << (ulong)uVar10) - 1U ^ 0xffffffff);
    }
    else if (uVar10 == 0x1f) {
      FUN_00190140(param_4,(1 << (ulong)uVar1) + -1);
    }
    else {
      FUN_00190140(param_4,(1 << (ulong)(uVar10 + 1 & 0x1f)) - 1U ^
                           (1 << (ulong)uVar1) - 1U ^ 0xffffffff);
    }
    uVar7 = uVar7 >> 0x1c;
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x4f:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      FUN_00190100(param_4,0xb);
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      uVar12 = *(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2);
      FUN_00190100(param_4,uVar12);
      FUN_00190100(param_4,uVar12);
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    iVar2 = FUN_00196400(param_4,(uint)(uVar8 >> 7) & 0x1f | (uVar7 & 0x1f0000) >> 0xb);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x50:
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a64d0:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a64d0;
      FUN_00190100(param_4,0);
    }
    iVar2 = FUN_00196470(param_4,uVar7 & 0xffff);
    break;
  case 0x51:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x52:
    iVar2 = FUN_00198bd0(param_4,uVar8);
    break;
  case 0x53:
    FUN_00190140(param_4,param_3 & 0x1f);
    goto switchD_001a555c_caseD_33;
  case 0x54:
    iVar2 = FUN_00197370(param_4,uVar8);
    break;
  case 0x55:
    FUN_00190140(param_4,(uVar7 & 0xffffff) << 1 | (uint)(uVar8 >> 0x18) & 1);
    goto switchD_001a555c_caseD_33;
  case 0x56:
    iVar2 = FUN_00195b90(param_4,uVar8);
    break;
  case 0x57:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 4 & 0xf);
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    if ((int)uVar8 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    FUN_00190140(param_4,param_3 & 0xf);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    goto joined_r0x001a7f44;
  case 0x58:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00196e24(param_4,uVar8 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 4 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x59:
    param_3 = param_3 & 0xffffff;
LAB_001a57d4:
    FUN_00190140(param_4,param_3);
switchD_001a555c_caseD_1d:
joined_r0x001a57e4:
    uVar7 = uVar7 >> 0x1c;
    uVar8 = (ulong)uVar7;
    goto joined_r0x001a57e4;
  case 0x5a:
    iVar2 = FUN_00199d00(param_4,uVar8);
    break;
  case 0x5b:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x14 & 0xf);
    FUN_00190140(param_4,uVar8 >> 0xc & 0xf);
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    FUN_00190140(param_4,uVar8 >> 5 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x5c:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x14 & 0xf);
    FUN_00190140(param_4,uVar8 >> 0xc & 0xf);
    goto LAB_001a6a90;
  case 0x5d:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x15 & 7);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    FUN_00190140(param_4,uVar8 >> 5 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x5e:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x15 & 7);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
LAB_001a6a90:
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    uVar8 = uVar8 >> 5 & 7;
LAB_001a6aac:
    FUN_00190140(param_4,uVar8);
    goto joined_r0x001a849c;
  case 0x5f:
    uVar7 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar7 == 0xf) {
      FUN_00190100(param_4,2);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x15 & 7);
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    FUN_00190140(param_4,uVar8 >> 5 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x60:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf;
    if (uVar10 == 0xf) {
      FUN_00190100(param_4,2);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 0x15 & 7);
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    FUN_00190140(param_4,uVar8 >> 5 & 7);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0x61:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x62:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 99:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 100:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x65:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    break;
  case 0x66:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x67:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    if ((uVar8 >> 0x10 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x68:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto joined_r0x001a7f44;
  case 0x69:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x6a:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto joined_r0x001a7f44;
  case 0x6b:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6c:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6d:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6e:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x6f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar9;
  case 0x70:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 7);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 3) & 1 | (uVar7 & 0x20) >> 4);
    return uVar3;
  case 0x71:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x72:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x73:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x74:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x75:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar9;
  case 0x76:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    return uVar3;
  case 0x77:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 10 & 1);
    return uVar3;
  case 0x78:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 9 & 3);
    return uVar3;
  case 0x79:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 8 & 7);
    return uVar3;
  case 0x7a:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0xb & 1);
    return uVar9;
  case 0x7b:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 10 & 3);
    return uVar9;
  case 0x7c:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 9 & 7);
    return uVar9;
  case 0x7d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 8 & 0xf);
    return uVar9;
  case 0x7e:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x7f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x80:
    uVar8 = (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + uVar8 * 2));
    uVar5 = (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + uVar5 * 2));
    iVar2 = FUN_00196b50(param_4,uVar8);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar5);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x81:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 & 0xf | (uVar7 & 0x20) >> 1;
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7);
    goto joined_r0x001a7f44;
  case 0x82:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x83:
    iVar2 = FUN_00197970(param_4,uVar8);
    break;
  case 0x84:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    break;
  case 0x85:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x86:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    return uVar3;
  case 0x87:
    iVar2 = FUN_0019a440(param_4,uVar8);
    break;
  case 0x88:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x13 & 1);
    goto switchD_001a555c_caseD_33;
  case 0x89:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x12 & 3);
    goto switchD_001a555c_caseD_33;
  case 0x8a:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x11 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x8b:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x13 & 1);
    return uVar3;
  case 0x8c:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x12 & 3);
    return uVar3;
  case 0x8d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x11 & 7);
    return uVar3;
  case 0x8e:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,8 - (uVar10 & 7));
    goto switchD_001a555c_caseD_33;
  case 0x8f:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,0x10 - (uVar10 & 0xf));
    goto switchD_001a555c_caseD_33;
  case 0x90:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,0x20 - (uVar10 & 0x1f));
    goto switchD_001a555c_caseD_33;
  case 0x91:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0x92:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0x93:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0x94:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x95:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0x96:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0x97:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0x98:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    goto switchD_001a555c_caseD_33;
  case 0x99:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0x9a:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0x9b:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0x9c:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0x9d:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0x9e:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0x9f:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0xa0:
    iVar2 = FUN_0019a8d0(param_4,uVar8);
    break;
  case 0xa1:
    iVar2 = FUN_0019a190(param_4,uVar8);
    break;
  case 0xa2:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,0x40 - (uVar10 & 0x3f));
    goto switchD_001a555c_caseD_33;
  case 0xa3:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,0x40 - (uVar10 & 0x3f));
    return uVar3;
  case 0xa4:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x3f);
    goto switchD_001a555c_caseD_33;
  case 0xa5:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar3;
  case 0xa6:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,8 - (uVar10 & 7));
    return uVar3;
  case 0xa7:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x10 - (uVar10 & 0xf));
    return uVar3;
  case 0xa8:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x20 - (uVar10 & 0x1f));
    return uVar3;
  case 0xa9:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,8 - (uVar10 & 7));
    return uVar9;
  case 0xaa:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x10 - (uVar10 & 0xf));
    return uVar9;
  case 0xab:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x20 - (uVar10 & 0x1f));
    return uVar9;
  case 0xac:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 7);
    return uVar3;
  case 0xad:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 7);
    return uVar9;
  case 0xae:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    return uVar3;
  case 0xaf:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    return uVar9;
  case 0xb0:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar3;
  case 0xb1:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x1f);
    return uVar9;
  case 0xb2:
    iVar2 = FUN_0019a320(param_4,uVar8);
    break;
  case 0xb3:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x40 - (uVar10 & 0x3f));
    return uVar3;
  case 0xb4:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,0x40 - (uVar10 & 0x3f));
    return uVar9;
  case 0xb5:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar3;
  case 0xb6:
    uVar10 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x10 & 0x3f);
    return uVar9;
  case 0xb7:
    uVar12 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190140(param_4,uVar8 >> 0x15 & 1);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0xb8:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    uVar8 = uVar8 >> 0x15 & 1;
    goto LAB_001a6aac;
  case 0xb9:
    uVar12 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190140(param_4,(uint)(uVar8 >> 6) & 1 | (uVar7 & 0x200000) >> 0x14);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0xba:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    FUN_00190140(param_4,(uint)(uVar8 >> 6) & 1 | (uVar7 & 0x200000) >> 0x14);
    goto joined_r0x001a849c;
  case 0xbb:
    uVar12 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190140(param_4,(uint)(uVar8 >> 5) & 3 | (uVar7 & 0x200000) >> 0x13);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0xbc:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    FUN_00190140(param_4,(uint)(uVar8 >> 5) & 3 | (uVar7 & 0x200000) >> 0x13);
    goto joined_r0x001a849c;
  case 0xbd:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
joined_r0x001a849c:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    uVar8 = (ulong)(uVar7 >> 0x1c);
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    goto LAB_001a6ad4;
  case 0xbe:
    if ((uVar8 >> 0x10 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar7 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    if (uVar7 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    if (uVar7 != 0xe) {
      FUN_00190100(param_4,3);
      return uVar3;
    }
    FUN_00190100(param_4,0);
    return uVar3;
  case 0xbf:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = FUN_0019bc74(param_4,uVar8);
    }
    else {
      iVar2 = FUN_0019b800();
    }
    break;
  case 0xc0:
    iVar2 = FUN_00198780(param_4,uVar8);
    break;
  case 0xc1:
    iVar2 = FUN_00199b60(param_4,uVar8);
    break;
  case 0xc2:
    iVar2 = FUN_001999e0(param_4,uVar8);
    break;
  case 0xc3:
    iVar2 = FUN_0019b1f0(param_4,uVar8);
    break;
  case 0xc4:
    uVar1 = uVar1 & 0xf;
    if ((uVar1 == 6) || (uVar1 == 7)) {
      if ((uVar7 >> 5 & 1) != 0) {
        return 0;
      }
    }
    else if ((uVar7 >> 4 & 3) == 3 && uVar1 == 10) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = FUN_0019bc74(param_4,uVar8);
    }
    else {
      iVar2 = FUN_0019b800();
    }
    break;
  case 0xc5:
    iVar2 = FUN_0019af00(param_4,uVar8);
    break;
  case 0xc6:
    iVar2 = FUN_0019c0b0(param_4,uVar8);
    break;
  case 199:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 & 0x30) == 0x30 && ((uVar1 & 0xf) == 8 || (uVar1 & 0xf) == 9)) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = FUN_0019bc74(param_4,uVar8);
    }
    else {
      iVar2 = FUN_0019b800();
    }
    break;
  case 200:
    iVar2 = FUN_0019b4c0(param_4,uVar8);
    break;
  case 0xc9:
    iVar2 = FUN_0019c290(param_4,uVar8);
    break;
  case 0xca:
    if ((uVar7 & 0xc0) == 0xc0) {
      return 0;
    }
    if ((uVar7 >> 5 & 1) != 0) {
      return 0;
    }
    if ((uVar7 >> 0x15 & 1) == 0) {
      iVar2 = FUN_0019bc74(param_4,uVar8);
    }
    else {
      iVar2 = FUN_0019b800();
    }
    break;
  case 0xcb:
    iVar2 = FUN_00199f54(param_4,uVar8);
    break;
  case 0xcc:
    iVar2 = FUN_00198fd0(param_4,uVar8);
    break;
  case 0xcd:
    iVar2 = FUN_0019a080(param_4,uVar8);
    break;
  case 0xce:
    iVar2 = FUN_0019b080(param_4,uVar8);
    break;
  case 0xcf:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd0:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2));
    FUN_00190140(param_4,param_3 & 0xff);
    goto switchD_001a555c_caseD_33;
  case 0xd1:
    iVar2 = FUN_00195e10(param_4,uVar8);
    break;
  case 0xd2:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 7 | (uVar7 & 0x80) >> 4) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd3:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f720 + (ulong)(uVar7 & 7 | (uVar7 & 0x80) >> 4) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd4:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd5:
    uVar7 = (uint)(uVar8 >> 3) & 0xf;
    if (uVar7 == 0xf) goto LAB_001acba0;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd6:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2));
    FUN_00190140(param_4,(param_3 & 0xff) << 2);
    goto switchD_001a555c_caseD_33;
  case 0xd7:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 6 & 7) * 2));
    goto switchD_001a555c_caseD_33;
  case 0xd8:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190140(param_4,uVar8 >> 6 & 0x1f);
    goto switchD_001a555c_caseD_33;
  case 0xd9:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2));
    FUN_00190100(param_4,0xc);
    FUN_00190140(param_4,param_3 & 0xff);
    goto switchD_001a555c_caseD_33;
  case 0xda:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2));
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc3e) {
      FUN_00190100(param_4,0xc);
    }
    else if (iVar2 != 0xc42) {
      return 0;
    }
    FUN_00190140(param_4,uVar7 & 0xff);
    goto switchD_001a555c_caseD_33;
  case 0xdb:
    FUN_00190100(param_4,0xc);
    FUN_00190100(param_4,0xc);
    FUN_00190140(param_4,param_3 & 0x7f);
    goto switchD_001a555c_caseD_33;
  case 0xdc:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190140(param_4,(ulong)((uint)(uVar8 >> 3) & 0x1f | (uVar7 & 0x200) >> 4) << 1);
    goto switchD_001a555c_caseD_33;
  case 0xdd:
    iVar2 = FUN_00196470(param_4,(uVar7 >> 8 & 1) << 0xe | uVar7 & 0xff);
    break;
  case 0xde:
    FUN_00190140(param_4,uVar8 >> 3 & 1);
    goto switchD_001a555c_caseD_33;
  case 0xdf:
    FUN_00190140(param_4,uVar8 >> 4 & 1 | 2);
    FUN_00190140(param_4,uVar7 & 7);
    goto switchD_001a555c_caseD_33;
  case 0xe0:
    FUN_00190140(param_4,param_3 & 0x3f);
    goto switchD_001a555c_caseD_33;
  case 0xe1:
    iVar2 = FUN_00196470(param_4,(uVar7 >> 8 & 1) << 0xf | uVar7 & 0xff);
    break;
  case 0xe2:
    FUN_00190140(param_4,param_3 & 0xff);
    goto switchD_001a555c_caseD_33;
  case 0xe3:
    FUN_00190140(param_4,uVar8 >> 4 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0xe4:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196470(param_4,uVar7 & 0xff);
    break;
  case 0xe5:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2));
    iVar2 = FUN_00196470(param_4,uVar7 & 0xff);
    break;
  case 0xe6:
    uVar8 = uVar8 >> 8 & 0xf;
    FUN_00190140(param_4,(long)(int)(-(uVar7 >> 7 & 1) & 0xfffffe00 | (uVar7 & 0xff) << 1));
    uVar7 = (uint)uVar8;
    goto joined_r0x001a57e4;
  case 0xe7:
    FUN_00190140(param_4,-(uVar8 >> 10 & 1) & 0xfffffffffffff000 | (param_3 & 0x7ff) << 1);
    goto switchD_001a555c_caseD_33;
  case 0xe8:
    uVar10 = uVar7 & 0x4000000;
    FUN_00190140(param_4,-(ulong)(uVar10 >> 0x1a) & 0xfffffffffe000000 |
                         (ulong)((uint)((uVar7 >> 0xb & 1) == uVar10 >> 0x1a) << 0x15 |
                                 (uint)((uVar7 >> 0xd & 1) == uVar10 >> 0x1a) << 0x16 |
                                uVar7 & 0x7fe | (uVar7 & 0x3ff0000) >> 5 | uVar10 >> 3) << 1);
    goto switchD_001a555c_caseD_33;
  case 0xe9:
    uVar10 = uVar7 >> 0x1a;
    FUN_00190140(param_4,-(ulong)(uVar10 & 1) & 0xfffffffffe000000 |
                         (ulong)((uint)((uVar7 >> 0xb & 1) == (uVar10 & 1)) << 0x15 |
                                 (uint)((uVar7 >> 0xd & 1) == (uVar10 & 1)) << 0x16 |
                                (uVar10 & 1) << 0x17 | (uVar7 & 0x3ff0000) >> 5 | uVar7 & 0x7ff) <<
                         1);
    goto switchD_001a555c_caseD_33;
  case 0xea:
    uVar8 = uVar8 >> 4 & 0xf;
    if ((int)uVar8 == 0xf) {
      if ((param_3 & 0xf) == 0) {
        return 0;
      }
      FUN_00190140(param_4,0xe);
      FUN_00190140(param_4,uVar7 & 0xf);
      return 1;
    }
    if ((param_3 & 0xf) == 0) {
      return 0;
    }
    FUN_00190140(param_4,uVar8);
    FUN_00190140(param_4,uVar7 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0xeb:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = FUN_00196470(param_4,uVar7 & 0x5fff);
    break;
  case 0xec:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    iVar2 = FUN_00196470(param_4,uVar7 & 0xffff);
    break;
  case 0xed:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    goto joined_r0x001a7f44;
  case 0xee:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_001974f4(param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    goto joined_r0x001a7f44;
  case 0xef:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac468;
      }
LAB_001acffc:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acffc;
      FUN_00190100(param_4,0xb);
LAB_001ac468:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac48c;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ac48c:
      param_1 = 1;
      goto LAB_001ac490;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001ac490:
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0xf0:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aab20;
      }
LAB_001ad018:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad018;
      FUN_00190100(param_4,0xb);
LAB_001aab20:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aab44;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aab44:
      param_1 = 1;
      goto LAB_001aab48;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001aab48:
    iVar2 = FUN_001974f4(param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0xf1:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0xf2:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_001974f4(param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0xf3:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196470(param_4,uVar7 & 0x5fff);
    break;
  case 0xf4:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196470(param_4,uVar7 & 0xffff);
    break;
  case 0xf5:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a7b60;
      }
LAB_001acfdc:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acfdc;
      FUN_00190100(param_4,0xb);
LAB_001a7b60:
      param_1 = 1;
    }
    if ((uVar10 & 0xf) != 0xf) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
      return param_1;
    }
LAB_001acba0:
    FUN_00190100(param_4,0xb);
    return 1;
  case 0xf6:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac288;
      }
LAB_001acd04:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acd04;
      FUN_00190100(param_4,0xb);
LAB_001ac288:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac2ac;
      }
LAB_001adc00:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001adc00;
      FUN_00190100(param_4,0xb);
LAB_001ac2ac:
      param_1 = 1;
    }
    iVar2 = FUN_00195fe4(param_4,uVar7 & 0xff | (uVar7 & 0xf0000) >> 8);
    goto joined_r0x001a7f44;
  case 0xf7:
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac220;
      }
LAB_001acf88:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001acf88;
      FUN_00190100(param_4,0xb);
LAB_001ac220:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac248;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ac248:
      param_1 = 1;
      goto LAB_001ac24c;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001ac24c:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xf8:
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac19c;
      }
LAB_001acfa4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001acfa4;
      FUN_00190100(param_4,0xb);
LAB_001ac19c:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac1c0;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ac1c0:
      param_1 = 1;
      goto LAB_001ac1c4;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001ac1c4:
    iVar2 = FUN_00197240(param_4,uVar8 >> 8 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xf9:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac158;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ac158:
      param_1 = 1;
      goto LAB_001ac160;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001ac160:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xfa:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001acb54;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001acb54:
      param_1 = 1;
      goto LAB_001acb58;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001acb58:
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    if (uVar10 != 0xf) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
      FUN_00190140(param_4,uVar7 & 0xff);
      return param_1;
    }
    FUN_00190100(param_4,0xb);
    FUN_00190140(param_4,uVar7 & 0xff);
    return 1;
  case 0xfb:
    iVar2 = FUN_00197440(param_4,uVar8);
    break;
  case 0xfc:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac0c8;
      }
LAB_001ace54:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ace54;
      FUN_00190100(param_4,0xb);
LAB_001ac0c8:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac0f0;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ac0f0:
      param_1 = 1;
      goto LAB_001ac0f4;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001ac0f4:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    return param_1;
  case 0xfd:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac044;
      }
LAB_001acf4c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acf4c;
      FUN_00190100(param_4,0xb);
LAB_001ac044:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac068;
      }
LAB_001ae5a4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ae5a4;
      FUN_00190100(param_4,0xb);
LAB_001ac068:
      param_1 = 1;
    }
    iVar2 = FUN_00196ad0(param_4,(uVar7 >> 0x17 & 1) << 8 | (uVar7 & 0xf0000) >> 7 | uVar7 & 0xff);
    goto joined_r0x001a7f44;
  case 0xfe:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar7 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar7 & 0xf) * 2));
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0xff:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa66c;
      }
LAB_001acdc8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acdc8;
      FUN_00190100(param_4,0xb);
LAB_001aa66c:
      param_1 = 1;
    }
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa690;
      }
    }
    else if (uVar10 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aa690:
      param_1 = 1;
      goto LAB_001aa694;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
LAB_001aa694:
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x100:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aca70;
      }
LAB_001acd3c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acd3c;
      FUN_00190100(param_4,0xb);
LAB_001aca70:
      param_1 = 1;
    }
    uVar10 = uVar7 & 0xf;
    if (uVar10 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aca94;
      }
    }
    else if (uVar10 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aca94:
      param_1 = 1;
      goto LAB_001aca98;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
LAB_001aca98:
    FUN_00190140(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x101:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa5ec;
      }
LAB_001ad034:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad034;
      FUN_00190100(param_4,0xb);
LAB_001aa5ec:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa610;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aa610:
      param_1 = 1;
      goto LAB_001aa614;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001aa614:
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    return param_1;
  case 0x102:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa578;
      }
LAB_001acee0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acee0;
      FUN_00190100(param_4,0xb);
LAB_001aa578:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa59c;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aa59c:
      param_1 = 1;
      goto LAB_001aa5a0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001aa5a0:
    FUN_00190100(param_4,uVar12);
    if ((param_3 & 0xff) != 0 || (param_3 & 0x800000) != 0) {
      FUN_00195b40();
      return param_1;
    }
    FUN_00190140(param_4,0xffffffff80000000);
    return param_1;
  case 0x103:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa4c8;
      }
LAB_001ace1c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ace1c;
      FUN_00190100(param_4,0xb);
LAB_001aa4c8:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa4f0;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aa4f0:
      param_1 = 1;
      goto LAB_001aa4f4;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001aa4f4:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    if ((param_3 & 0xff) != 0 || (param_3 & 0x800000) != 0) {
      FUN_00195b40();
      return param_1;
    }
    FUN_00190140(param_4,0xffffffff80000000);
    return param_1;
  case 0x104:
    iVar2 = FUN_0019a520(param_4,uVar8);
    break;
  case 0x105:
    iVar2 = FUN_0019a6f4(param_4,uVar8);
    break;
  case 0x106:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab4cc;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ab4cc:
      param_1 = 1;
      goto LAB_001ab4d0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001ab4d0:
    iVar2 = FUN_001974f4(param_4,(uVar7 >> 4 & 0xf) << 5 | (uVar7 & 0x7000) >> 3 | uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x107:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00195d60(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    goto joined_r0x001a7f44;
  case 0x108:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab440;
      }
LAB_001ad06c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad06c;
      FUN_00190100(param_4,0xb);
LAB_001ab440:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab464;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ab464:
      param_1 = 1;
      goto LAB_001ab468;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001ab468:
    iVar2 = FUN_00195d60(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x109:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab378;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ab378:
      param_1 = 1;
      goto LAB_001ab37c;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001ab37c:
    iVar2 = FUN_00195d60(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x10a:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 & 0xf) * 2));
    }
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00195d60(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    if ((uVar7 >> 0x14 & 1) != 0) {
      FUN_00190100(param_4,3);
      return param_1;
    }
    FUN_00190100(param_4,0);
    return param_1;
  case 0x10b:
    if ((uVar1 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 & 0xf) * 2));
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190140(param_4,(uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 | uVar7 & 0xff);
    return param_1;
  case 0x10c:
    uVar10 = (uint)(uVar8 >> 0x15) & 1;
    if (uVar10 != ((uint)(uVar8 >> 0x17) & 1)) {
      return 0;
    }
    FUN_00190140(param_4,(long)((ulong)((uVar7 >> 0x1a & 1) << 0xb | (uVar7 & 0x7000) >> 4 |
                                       uVar7 & 0xff | uVar10 << 0xc) << 0x33) >> 0x33);
    goto switchD_001a555c_caseD_33;
  case 0x10d:
    iVar2 = FUN_00199150(param_4,uVar8);
    break;
  case 0x10e:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab620;
      }
LAB_001acd20:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acd20;
      FUN_00190100(param_4,0xb);
LAB_001ab620:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    FUN_00190140(param_4,param_3 & 0xf);
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
LAB_001ae738:
        FUN_00190100(param_4,0xc);
        return 1;
      }
LAB_001ab644:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
      return param_1;
    }
    if (iVar2 != 0xf) goto LAB_001ab644;
    goto LAB_001acba0;
  case 0x10f:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab59c;
      }
LAB_001acd58:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acd58;
      FUN_00190100(param_4,0xb);
LAB_001ab59c:
      param_1 = 1;
    }
    FUN_00190140(param_4,param_3 & 0x1f);
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab5cc;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001ab5cc:
      param_1 = 1;
      goto LAB_001ab5d0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001ab5d0:
    uVar7 = (uVar7 >> 0x15 & 1) << 5 | (uVar7 & 0x7000) >> 10 | (uint)(uVar8 >> 6) & 3;
    if (uVar7 == 0x20) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    return param_1;
  case 0x110:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001acae4;
      }
LAB_001ace38:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ace38;
      FUN_00190100(param_4,0xb);
LAB_001acae4:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001acb08;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001acb08:
      param_1 = 1;
      goto LAB_001acb0c;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001acb0c:
    FUN_00190140(param_4,(uint)(uVar8 >> 6) & 3 | (uVar7 & 0x7000) >> 10);
    FUN_00190140(param_4,param_3 & 0x1f);
    return param_1;
  case 0x111:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        FUN_00190100(param_4,0xc);
      }
      else {
        FUN_00190100(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab544;
      }
      uVar12 = 0xc;
LAB_001ad6b0:
      FUN_00190100(param_4,uVar12);
    }
    else {
      if (iVar2 != 0xf) {
        uVar12 = *(undefined2 *)(&DAT_0022f720 + uVar5 * 2);
        FUN_00190100(param_4,uVar12);
        goto LAB_001ad6b0;
      }
      FUN_00190100(param_4,0xb);
      FUN_00190100(param_4,0xb);
LAB_001ab544:
      param_1 = 1;
    }
    iVar2 = FUN_00196400(param_4,(uVar7 & 0x1f) << 5 | (uint)(uVar8 >> 6) & 3 |
                                 (uVar7 & 0x7000) >> 10);
    goto joined_r0x001a7f44;
  case 0x112:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        FUN_00190100(param_4,0xc);
      }
      else {
        FUN_00190100(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac744;
      }
      uVar12 = 0xc;
LAB_001ad680:
      FUN_00190100(param_4,uVar12);
    }
    else {
      if (iVar2 != 0xf) {
        uVar12 = *(undefined2 *)(&DAT_0022f720 + uVar5 * 2);
        FUN_00190100(param_4,uVar12);
        goto LAB_001ad680;
      }
      FUN_00190100(param_4,0xb);
      FUN_00190100(param_4,0xb);
LAB_001ac744:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar8 >> 0x10 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00196400(param_4,(uVar7 & 0x1f) << 5 | (uint)(uVar8 >> 6) & 3 |
                                 (uVar7 & 0x7000) >> 10);
    goto joined_r0x001a7f44;
  case 0x113:
    if ((uVar10 & 0xf) == 0xf) goto LAB_001acba0;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x115:
    iVar2 = FUN_001960d4(param_4,uVar8);
    break;
  case 0x116:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x117:
    iVar2 = FUN_0019aa04(param_4,uVar1 & 0xf | (uVar7 & 0x100000) >> 0x10);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 != 0xd) {
      if (iVar2 == 0xf) goto LAB_001acba0;
LAB_001a8cdc:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
      return uVar3;
    }
    if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a8cdc;
    goto LAB_001ae738;
  case 0x118:
    uVar7 = uVar7 & 0x10 | (uVar7 & 0x100000) >> 0xf | uVar1 & 0xf;
    lVar4 = FUN_001bb9e0(uVar7);
    if (lVar4 == 0) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    FUN_00190140(param_4,uVar7);
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) goto LAB_001ae738;
    }
    else if (iVar2 == 0xf) goto LAB_001acba0;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    goto switchD_001a555c_caseD_33;
  case 0x119:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8c08;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001a8c08:
      param_1 = 1;
      goto LAB_001a8c0c;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001a8c0c:
    uVar7 = uVar7 & 0x10 | (uVar7 & 0x100000) >> 0xf | uVar10 & 0xf;
    lVar4 = FUN_001bb9e0(uVar7);
    if (lVar4 == 0) {
      return 0;
    }
    FUN_00190140(param_4,uVar7);
    return param_1;
  case 0x11a:
    FUN_00190140(param_4,uVar7 & 0xfff | (uVar7 & 0xf0000) >> 4);
    goto switchD_001a555c_caseD_33;
  case 0x11b:
    FUN_00190140(param_4,uVar8 >> 0x10 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0x11c:
    iVar2 = FUN_0019aa04(param_4,uVar7 & 0xcff);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) goto LAB_001ae738;
    }
    else if (iVar2 == 0xf) goto LAB_001acba0;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    return uVar3;
  case 0x11d:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac37c;
      }
LAB_001acf30:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acf30;
      FUN_00190100(param_4,0xb);
LAB_001ac37c:
      param_1 = 1;
    }
    iVar2 = FUN_0019aa04(param_4,uVar7 & 0xff);
    goto joined_r0x001a7f44;
  case 0x11e:
    iVar2 = FUN_00198520(param_4,param_3 & 0xffffffff);
    break;
  case 0x11f:
    uVar10 = (uint)(uVar8 >> 0x1a) & 1;
    FUN_00190140(param_4,-(ulong)uVar10 & 0xfffffffffe000000 |
                         (ulong)((uint)(((uint)(uVar8 >> 0xb) & 1) == uVar10) << 0x15 |
                                 (uint)(((uint)(uVar8 >> 0xd) & 1) == uVar10) << 0x16 |
                                 (uVar7 >> 0x10 & 0x3ff) << 0xb | uVar10 << 0x17 | uVar7 & 0x7ff) <<
                         1);
    goto switchD_001a555c_caseD_33;
  case 0x120:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac66c;
      }
LAB_001ad050:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ad050;
      FUN_00190100(param_4,0xb);
LAB_001ac66c:
      param_1 = 1;
    }
    iVar2 = FUN_001976d0(param_4,(uVar7 & 0xf) << 2 | (uint)(uVar8 >> 4) & 3 |
                                 (uVar7 & 0xf0000) >> 10);
    goto joined_r0x001a7f44;
  case 0x121:
    iVar2 = FUN_00196c70(param_4,param_3 & 0xffffffff);
    break;
  case 0x122:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac61c;
      }
LAB_001acf14:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acf14;
      FUN_00190100(param_4,0xb);
LAB_001ac61c:
      param_1 = 1;
    }
    iVar2 = FUN_00195ee0(param_4,uVar7 & 0xff | (uVar7 & 0xf0000) >> 7);
    goto joined_r0x001a7f44;
  case 0x123:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa960;
      }
LAB_001acfc0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acfc0;
      FUN_00190100(param_4,0xb);
LAB_001aa960:
      param_1 = 1;
    }
    iVar2 = FUN_00195ee0(param_4,(uVar7 >> 0x10 & 0xf) << 9 | (uVar7 & 0x200) >> 1 | uVar7 & 0xff);
    goto joined_r0x001a7f44;
  case 0x124:
    uVar8 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001aa8d8;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001aa8d8:
      param_1 = 1;
      goto LAB_001aa8dc;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
LAB_001aa8dc:
    iVar2 = FUN_0018ffb0(param_4);
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    if (((iVar2 - 0xbe9U < 0x14) && ((0x82001UL >> ((ulong)(iVar2 - 0xbe9U) & 0x3f) & 1) != 0)) &&
       (uVar10 == 0xf)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    FUN_00190140(param_4,uVar7 & 0xfff);
    return param_1;
  case 0x125:
    iVar2 = FUN_001977b0(param_4,param_3 & 0xffffffff);
    break;
  case 0x126:
    iVar2 = FUN_00196e80(param_4,param_3 & 0xffffffff);
    break;
  case 0x127:
    iVar2 = FUN_001983c0(param_4,param_3 & 0xffffffff);
    break;
  case 0x128:
    iVar2 = FUN_00197050(param_4,param_3 & 0xffffffff);
    break;
  case 0x129:
    iVar2 = FUN_00196b84(param_4,param_3 & 0xffffffff);
    break;
  case 0x12a:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab798;
      }
LAB_001ace8c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ace8c;
      FUN_00190100(param_4,0xb);
LAB_001ab798:
      param_1 = 1;
    }
    uVar8 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ab7bc;
      }
LAB_001ae13c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ae13c;
      FUN_00190100(param_4,0xb);
LAB_001ab7bc:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    goto joined_r0x001a7f44;
  case 299:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a88f4;
      }
LAB_001acde4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acde4;
      FUN_00190100(param_4,0xb);
LAB_001a88f4:
      param_1 = 1;
    }
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8918;
      }
    }
    else if (uVar7 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001a8918:
      param_1 = 1;
      goto LAB_001a891c;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
LAB_001a891c:
    FUN_00190140(param_4,uVar8 >> 4 & 3);
    return param_1;
  case 300:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8880;
      }
LAB_001acec4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acec4;
      FUN_00190100(param_4,0xb);
LAB_001a8880:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a88a4;
      }
    }
    else if (iVar2 == 0xf) {
      FUN_00190100(param_4,0xb);
LAB_001a88a4:
      param_1 = 1;
      goto LAB_001a88a8;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
LAB_001a88a8:
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 4 & 3);
    return param_1;
  case 0x12d:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac5b0;
      }
LAB_001acd74:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acd74;
      FUN_00190100(param_4,0xb);
LAB_001ac5b0:
      param_1 = 1;
    }
    uVar7 = uVar7 & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001ac5d4;
      }
LAB_001adbe0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
    }
    else {
      if (uVar7 != 0xf) goto LAB_001adbe0;
      FUN_00190100(param_4,0xb);
LAB_001ac5d4:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar8 >> 0x10 & 0xf);
    goto joined_r0x001a7f44;
  case 0x12e:
    uVar8 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar8;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8824;
      }
LAB_001acef8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar8 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acef8;
      FUN_00190100(param_4,0xb);
LAB_001a8824:
      param_1 = 1;
    }
    uVar7 = (uVar7 | uVar7 >> 0x10) & 0xf;
    if (uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a8840;
      goto LAB_001ae738;
    }
    if (uVar7 != 0xf) {
LAB_001a8840:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar7 * 2));
      return param_1;
    }
    goto LAB_001acba0;
  case 0x12f:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a879c;
      }
LAB_001acea8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acea8;
      FUN_00190100(param_4,0xb);
LAB_001a879c:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 0x10 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a87c0;
      }
LAB_001ae1a4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ae1a4;
      FUN_00190100(param_4,0xb);
LAB_001a87c0:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00197240(param_4,uVar8 >> 0xc & 0xf);
    goto joined_r0x001a7f44;
  case 0x130:
    uVar5 = uVar8 >> 0xc & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8714;
      }
LAB_001acce8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001acce8;
      FUN_00190100(param_4,0xb);
LAB_001a8714:
      param_1 = 1;
    }
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8738;
      }
LAB_001ae3b0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if (iVar2 != 0xf) goto LAB_001ae3b0;
      FUN_00190100(param_4,0xb);
LAB_001a8738:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar8 >> 0x10 & 0xf);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    goto joined_r0x001a7f44;
  case 0x131:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x132:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_001976d0(param_4,(uVar7 & 0xf) << 2 | (uint)(uVar8 >> 4) & 3 |
                                 (uVar7 & 0xf0000) >> 10);
    break;
  case 0x133:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_00195ee0(param_4,(uVar7 >> 0x10 & 0xf) << 9 | (uVar7 & 0x200) >> 1 | uVar7 & 0xff);
    break;
  case 0x134:
    uVar10 = (uVar7 & 0xf0000) >> 0x10;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    iVar2 = FUN_0018ffb0(param_4);
    if (((iVar2 - 0xbe9U < 0x14) && ((0x82001UL >> ((ulong)(iVar2 - 0xbe9U) & 0x3f) & 1) != 0)) &&
       (uVar10 == 0xf)) {
      return 0;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar10 * 2));
    FUN_00190140(param_4,uVar7 & 0xfff);
    goto switchD_001a555c_caseD_33;
  case 0x135:
    uVar5 = uVar8 >> 0xc & 0xf;
    if ((int)uVar5 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a8548;
      }
LAB_001ace70:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar5 * 2));
    }
    else {
      if ((int)uVar5 != 0xf) goto LAB_001ace70;
      FUN_00190100(param_4,0xb);
LAB_001a8548:
      param_1 = 1;
    }
    uVar13 = uVar8 >> 8 & 0xf;
    if ((int)uVar13 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        FUN_00190100(param_4,0xc);
        goto LAB_001a856c;
      }
LAB_001ae5e0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar13 * 2));
    }
    else {
      if ((int)uVar13 != 0xf) goto LAB_001ae5e0;
      FUN_00190100(param_4,0xb);
LAB_001a856c:
      param_1 = 1;
    }
    iVar2 = FUN_00197240(param_4,uVar8 >> 0x10 & 0xf);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00197240(param_4,uVar7 & 0xf);
    param_1 = 1;
    if ((iVar2 != 1) && (param_1 = uVar3, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00197240(param_4,uVar5);
    if (iVar2 == 1) {
      param_1 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00197240(param_4,uVar13);
    goto joined_r0x001a7f44;
  case 0x136:
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 4 & 0xf);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    FUN_00190140(param_4,param_3 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0x137:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    uVar5 = uVar8 >> 8 & 0xf;
    iVar2 = (int)uVar5;
    if (iVar2 - 10U < 2) {
      return 0;
    }
    if (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) && (1 < iVar2 - 0xeU)) {
      return 0;
    }
    FUN_00190140(param_4,uVar5);
    FUN_00190140(param_4,uVar8 >> 4 & 0xf);
    FUN_00190140(param_4,param_3 & 0xf);
    goto switchD_001a555c_caseD_33;
  case 0x138:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190140(param_4,uVar8 >> 6 & 0x1f);
    goto switchD_001a555c_caseD_33;
  case 0x139:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 6 & 7) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x13a:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190140(param_4,uVar8 >> 6 & 7);
    goto switchD_001a555c_caseD_33;
  case 0x13b:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 8 & 7) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190140(param_4,param_3 & 0xff);
    goto switchD_001a555c_caseD_33;
  case 0x13c:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    goto switchD_001a555c_caseD_33;
  case 0x13d:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (param_3 & 7) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 3 & 7) * 2));
    FUN_00190100(param_4,uVar12);
    goto switchD_001a555c_caseD_33;
  case 0x13e:
  case 0x144:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if ((uVar7 >> 0x17 & 1) == 0) {
      FUN_00190140(param_4,uVar7 & 0xff | 0x100);
    }
    else {
      FUN_00190140(param_4,uVar7 & 0xff);
    }
    goto joined_r0x001a9a98;
  case 0x13f:
    uVar12 = *(undefined2 *)
              (&DAT_0022f7a0 + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 != 0xc4f) goto LAB_001ad0a4;
joined_r0x001a9b28:
    if (uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    FUN_00190140(param_4,uVar7 >> 0x1c);
    goto LAB_001a55c8;
  case 0x140:
  case 0x146:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    uVar10 = (uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf;
    goto LAB_001a5578;
  case 0x141:
  case 0x147:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    goto joined_r0x001a5684;
  case 0x142:
    iVar2 = FUN_00197c30(param_4,param_3 & 0xffffffff);
    break;
  case 0x143:
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a602c:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a602c;
      FUN_00190100(param_4,0);
    }
    uVar10 = uVar7 & 0xff;
    uVar7 = (uVar7 >> 0x16 & 1) << 8 | (uVar7 & 0xf000) >> 3;
    uVar1 = uVar7 >> 8;
    uVar12 = *(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar7 >> 8) * 2);
    if ((param_3 & 0xff) != 0) {
      if (uVar1 + uVar10 < 0x21) {
        FUN_00190100(param_4,uVar12);
        if (uVar10 == 1) goto switchD_001a555c_caseD_33;
        if (uVar1 == 0x1f) {
          return 0;
        }
        uVar10 = uVar10 - 1;
        iVar2 = 3;
      }
      else {
        FUN_00190100(param_4,uVar12);
        iVar2 = 1;
        uVar10 = 0x1f - uVar1;
        if (uVar1 == 0x1f) {
          return 1;
        }
      }
      uVar8 = (ulong)(uVar1 + 2);
      while (FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f79e + uVar8 * 2)),
            ((int)uVar8 - uVar1) - 1 < uVar10) {
        uVar8 = uVar8 + 1;
        if (uVar8 == (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1)) {
          return 0;
        }
      }
      if (iVar2 == 1) {
        return 1;
      }
      goto switchD_001a555c_caseD_33;
    }
    FUN_00190100(param_4,uVar12);
    goto LAB_001a6070;
  case 0x145:
    uVar12 = *(undefined2 *)
              (&DAT_0022f7a0 + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) goto joined_r0x001a9b28;
LAB_001ad0a4:
    FUN_00190140(param_4,uVar7 >> 0x1c);
    if (uVar7 >> 0x1c != 0xe) goto LAB_001a55c8;
    goto LAB_001a575c;
  case 0x148:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    goto joined_r0x001a9a98;
  case 0x149:
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001aa304:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001aa304;
      FUN_00190100(param_4,0);
    }
    iVar2 = FUN_001975b0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4 | (uVar7 & 0x400000) >> 10);
    break;
  case 0x14a:
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2));
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a7b08:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a7b08;
      FUN_00190100(param_4,0);
    }
    iVar2 = FUN_001975b0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4);
    break;
  case 0x14b:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)((uVar7 & 0xf0000) >> 0x10) * 2));
    if ((uVar7 >> 0x17 & 1) == 0) {
      FUN_00190140(param_4,uVar7 & 0xff | 0x100);
    }
    else {
      FUN_00190140(param_4,uVar7 & 0xff);
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0x14c:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x14d:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    param_1 = uVar3;
    goto joined_r0x001a7f44;
  case 0x14e:
  case 0x150:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar10 = (uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf;
    goto LAB_001a5614;
  case 0x14f:
    iVar2 = FUN_00197d94(param_4,param_3 & 0xffffffff);
    break;
  case 0x151:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    goto LAB_001a5d9c;
  case 0x152:
    if ((uVar10 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar10 & 0xf) * 2));
    }
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
joined_r0x001a7f44:
    if (iVar2 != 1) {
      if (iVar2 == 3) {
        return param_1;
      }
      return 0;
    }
    goto LAB_001a6070;
  case 0x153:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a9f74:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a9f74;
      FUN_00190100(param_4,0);
    }
    uVar10 = uVar7 & 0xff;
    uVar7 = (uVar7 >> 0x16 & 1) << 8 | (uVar7 & 0xf000) >> 3;
    uVar1 = uVar7 >> 8;
    uVar12 = *(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar7 >> 8) * 2);
    if ((param_3 & 0xff) == 0) {
      FUN_00190100(param_4,uVar12);
      return 1;
    }
    if (uVar1 + uVar10 < 0x21) {
      FUN_00190100(param_4,uVar12);
      if (uVar10 == 1) goto switchD_001a555c_caseD_33;
      if (uVar1 == 0x1f) {
        return 0;
      }
      uVar10 = uVar10 - 1;
      iVar2 = 3;
    }
    else {
      FUN_00190100(param_4,uVar12);
      iVar2 = 1;
      uVar10 = 0x1f - uVar1;
      if (uVar1 == 0x1f) {
        return 1;
      }
    }
    uVar8 = (ulong)(uVar1 + 2);
    while (FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f79e + uVar8 * 2)),
          ((int)uVar8 - uVar1) - 1 < uVar10) {
      uVar8 = uVar8 + 1;
      if (uVar8 == (ulong)(0x1e - uVar1) + (ulong)(uVar1 + 3)) {
        return 0;
      }
    }
    if (iVar2 == 1) {
      return 1;
    }
    goto switchD_001a555c_caseD_33;
  case 0x154:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a9ed8:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a9ed8;
      FUN_00190100(param_4,0);
    }
    iVar2 = FUN_001975b0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4 | (uVar7 & 0x400000) >> 10);
    break;
  case 0x155:
    uVar12 = *(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0x10 & 0xf) * 2);
    FUN_00190100(param_4,uVar12);
    uVar10 = uVar7 >> 0x1c;
    FUN_00190100(param_4,uVar12);
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar10 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar10);
LAB_001a99d0:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar10);
      if (uVar10 != 0xe) goto LAB_001a99d0;
      FUN_00190100(param_4,0);
    }
    iVar2 = FUN_001975b0(param_4,uVar7 & 0xfe | (uVar7 & 0xf000) >> 4);
    break;
  case 0x156:
    iVar2 = FUN_00198620(param_4,param_3 & 0xffffffff);
    break;
  case 0x157:
  case 0x15e:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190140(param_4,uVar7 & 0xf | (uVar7 & 0xf0000) >> 0xc);
    goto joined_r0x001a5684;
  case 0x158:
  case 0x15a:
  case 0x15b:
  case 0x15d:
    uVar10 = (uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb;
LAB_001a5578:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar10 * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    goto joined_r0x001a5684;
  case 0x159:
  case 0x15f:
    uVar10 = (uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb;
LAB_001a5614:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar10 * 2));
    goto joined_r0x001a5684;
  case 0x15c:
    uVar12 = *(undefined2 *)
              (&DAT_0022f7a0 + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2);
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190140(param_4,(uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
joined_r0x001a5684:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if (uVar7 >> 0x1c == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar7 >> 0x1c);
    }
    else {
LAB_001a5748:
      FUN_00190140(param_4,uVar7 >> 0x1c);
      if (uVar7 >> 0x1c == 0xe) {
LAB_001a575c:
        FUN_00190100(param_4,0);
        goto switchD_001a555c_caseD_33;
      }
    }
LAB_001a55c8:
    FUN_00190100(param_4,3);
    goto switchD_001a555c_caseD_33;
  case 0x160:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    uVar8 = (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
    puVar6 = &DAT_0022f7a0;
    goto LAB_001a5db4;
  case 0x161:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190140(param_4,uVar7 & 0xf | (uVar7 & 0xf0000) >> 0xc);
    goto joined_r0x001a9a98;
  case 0x162:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0x163:
    uVar12 = *(undefined2 *)
              (&DAT_0022f7a0 + (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2);
LAB_001a5d9c:
    FUN_00190100(param_4,uVar12);
    puVar6 = &DAT_0022f4e0;
    uVar8 = (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    goto LAB_001a5db4;
  case 0x164:
    puVar6 = &DAT_0022f4e0;
    uVar8 = (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
LAB_001a5db4:
    FUN_00190100(param_4,*(undefined2 *)(puVar6 + uVar8 * 2));
joined_r0x001a9a98:
    if (uVar7 >> 0x1c == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f && uVar7 >> 0x1c == 0xe) {
      return 0;
    }
    goto LAB_001a5748;
  case 0x165:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    FUN_00190140(param_4,(uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1);
    iVar2 = FUN_00196a40(param_4,uVar7 >> 0x1c);
    break;
  case 0x166:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 +
                          (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar10 & 0xf | (uVar7 & 0x80) >> 3) * 2));
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x18 & 1);
    return uVar3;
  case 0x167:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x17 & 3);
    return uVar3;
  case 0x168:
    uVar12 = *(undefined2 *)
              (&DAT_0022f4e0 + (ulong)((uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12) * 2)
    ;
    FUN_00190100(param_4,uVar12);
    FUN_00190100(param_4,uVar12);
    iVar2 = FUN_00196b50(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    FUN_00190140(param_4,uVar8 >> 0x14 & 3);
    return uVar3;
  case 0x169:
    iVar2 = FUN_0019b3a4(param_4,param_3 & 0xffffffff);
    break;
  case 0x16a:
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,(uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar9 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x18 & 1);
    return uVar9;
  case 0x16b:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar7 & 0xf | (uVar7 & 0x20) >> 1);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 0x17 & 3);
    return uVar3;
  case 0x16c:
    uVar1 = (uint)(uVar8 >> 0xc) & 0xf | (uVar7 & 0x400000) >> 0x12;
    if ((uVar8 >> 0xc & 1) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = param_1, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar1);
    uVar9 = 1;
    if ((iVar2 != 1) && (uVar9 = uVar3, iVar2 != 3)) {
      return 0;
    }
    if ((param_3 & 0x10000) != 0) {
      return 0;
    }
    iVar2 = FUN_00195b60(param_4,uVar10 & 0xf | (uVar7 & 0x80) >> 3);
    uVar3 = 1;
    if ((iVar2 != 1) && (uVar3 = uVar9, iVar2 != 3)) {
      return 0;
    }
    iVar2 = FUN_00196b50(param_4,uVar7 & 0xf);
    if (iVar2 == 1) {
      uVar3 = 1;
    }
    else if (iVar2 != 3) {
      return 0;
    }
    FUN_00190140(param_4,uVar8 >> 5 & 1);
    FUN_00190140(param_4,uVar8 >> 0x14 & 3);
    return uVar3;
  case 0x16d:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    goto switchD_001a555c_caseD_33;
  case 0x16e:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    goto switchD_001a555c_caseD_33;
  case 0x16f:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    goto switchD_001a555c_caseD_33;
  case 0x170:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 7) & 1 | (uVar7 & 0xf0000) >> 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)((uVar7 & 0xf) << 1 | (uint)(uVar8 >> 5) & 1) * 2)
                );
    goto switchD_001a555c_caseD_33;
  case 0x171:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 +
                          (ulong)((uint)(uVar8 >> 0x16) & 1 | (uVar7 & 0xf000) >> 0xb) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(uVar7 & 0xf | (uVar7 & 0x20) >> 1) * 2));
    goto switchD_001a555c_caseD_33;
  default:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar8 >> 0xc & 0xf) * 2));
    uVar5 = uVar8 >> 0x10;
LAB_001a54c8:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar5 & 0xf) * 2));
LAB_001a54d8:
    uVar8 = uVar8 >> 0x1c;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (param_3 & 0xf) * 2));
    uVar10 = (uint)uVar8;
joined_r0x001a7160:
    if (uVar10 == 0xf) {
      return 0;
    }
    iVar2 = FUN_0018ffb0(param_4);
    if (iVar2 == 0xc4f) {
      if ((int)uVar8 == 0xe) {
        return 0;
      }
      FUN_00190140(param_4,uVar8);
LAB_001a5514:
      FUN_00190100(param_4,3);
    }
    else {
      FUN_00190140(param_4,uVar8);
      if ((int)uVar8 != 0xe) goto LAB_001a5514;
      FUN_00190100(param_4,0);
    }
LAB_001a5520:
    if ((uVar7 >> 0x14 & 1) == 0) goto LAB_001a5524;
    goto LAB_001a580c;
  }
  if (iVar2 == 1) {
LAB_001a6070:
    param_1 = 1;
  }
  else {
    if (iVar2 != 3) {
      return 0;
    }
switchD_001a555c_caseD_33:
  }
  return param_1;
}

