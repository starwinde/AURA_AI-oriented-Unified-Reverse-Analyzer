
/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_0019c4c4(undefined4 param_1,undefined4 param_2,uint param_3,long param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  ulong uVar6;
  ulong uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined2 uVar10;
  
  uVar1 = param_3 & 0xffff;
  uVar7 = (ulong)uVar1;
  switch(param_2) {
  case 1:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_001974f4(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      FUN_00190100(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 2:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196950(param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      FUN_00190100(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 3:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196950(param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a0cc8:
        FUN_00190100(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a0cc8;
    }
    goto switchD_0019c568_caseD_9;
  case 4:
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 5:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 6:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    break;
  case 7:
    iVar4 = FUN_001992a0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 8:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    break;
  case 9:
    goto switchD_0019c568_caseD_9;
  case 10:
    FUN_00190140(param_4,uVar1 >> 9 & 1);
    break;
  case 0xb:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0xc:
    iVar4 = FUN_0019aac0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xd:
    iVar4 = FUN_0019b680(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xe:
    iVar4 = FUN_0019ac10(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xf:
    FUN_00190140(param_4,param_3 & 0xf | (uVar1 >> 8) << 4);
    break;
  case 0x10:
    iVar4 = FUN_00197b14(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x11:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_001974f4(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x12:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196950(param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x13:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      uVar10 = 0xb;
      iVar4 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      iVar4 = 3;
      uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2);
      FUN_00190100(param_4,uVar10);
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    if ((int)uVar7 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,uVar10);
    uVar3 = 1;
    if (iVar4 != 1) {
      uVar3 = param_1;
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196a40(param_4,0);
    param_1 = uVar3;
    goto joined_r0x001a29a4;
  case 0x14:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x16:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x17:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x18:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x19:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00195d10(param_4,(uVar1 >> 8 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1a:
    iVar4 = FUN_0019aa04(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1b:
    uVar7 = (ulong)(uVar1 >> 8) & 1;
    lVar5 = FUN_001bb9e0((int)uVar7 << 4);
    if (lVar5 != 0) {
      FUN_00190140(param_4,uVar7 << 4);
      if ((param_3 & 0xf) == 0xf) {
        param_1 = 1;
        FUN_00190100(param_4,0xb);
      }
      else {
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
      }
      iVar4 = FUN_00196a40(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x1c:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x1d:
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x1e:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x1f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    break;
  case 0x20:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 3) {
      uVar3 = 0x45;
    }
    else if (uVar1 < 4) {
      uVar3 = 0x43;
      if ((uVar1 != 1) && (uVar3 = 0x44, uVar1 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar1 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar1 != 0xc) goto switchD_0019c568_caseD_9;
      uVar3 = 0x4e;
    }
    FUN_00190100(param_4,uVar3);
    uVar1 = param_3 & 0xf;
    if (uVar1 == 3) {
      uVar3 = 0x45;
    }
    else if ((param_3 & 0xc) == 0) {
      uVar3 = 0x43;
      if ((uVar1 != 1) && (uVar3 = 0x44, uVar1 != 2)) {
        uVar3 = 0x42;
      }
    }
    else if (uVar1 == 9) {
      uVar3 = 0x4b;
    }
    else {
      if (uVar1 != 0xc) goto switchD_0019c568_caseD_9;
      uVar3 = 0x4e;
    }
    FUN_00190100(param_4,uVar3);
    iVar4 = FUN_00196a40(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190100(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x21:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = FUN_001974f4(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      FUN_00190100(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x22:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    break;
  case 0x23:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x24:
    FUN_00190140(param_4,uVar7 & 0xf);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x25:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00196950(param_4,(uVar1 >> 8 & 0xf) << 8 | (uVar1 >> 5 & 3) << 5 | param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a2478:
        FUN_00190100(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a2478;
    }
    goto switchD_0019c568_caseD_9;
  case 0x26:
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0x27:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x28:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    break;
  case 0x29:
    iVar4 = FUN_00199880(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2a:
    iVar4 = FUN_00197a00(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2b:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      FUN_00190100(param_4,0xb);
      param_1 = 1;
      FUN_00190140(param_4,0);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
      FUN_00190140(param_4,0);
    }
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x2c:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,param_3 & 0xf | (uVar1 >> 8 & 0xf) << 4);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x2d:
    iVar4 = FUN_0019ad70(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x2e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,param_3 & 0xf | (uVar1 >> 8 & 0xf) << 4);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x2f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xfff);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    break;
  case 0x30:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,uVar7 & 0xfff);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x31:
    iVar4 = FUN_00198e90(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x32:
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xfff);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x33:
    goto LAB_0019c63c;
  case 0x34:
    iVar4 = FUN_001972b4(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x35:
    iVar4 = FUN_0019aa04(param_4,0);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar7 & 0xfff);
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x36:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,uVar7 & 0xfff);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    break;
  case 0x37:
    iVar4 = FUN_00198900(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x38:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    iVar4 = -(param_3 & 0xfff);
    if (iVar4 == 0) {
      iVar4 = -0x80000000;
    }
    FUN_00190140(param_4,iVar4);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x39:
    FUN_00190100(param_4,0x42);
    iVar4 = -(param_3 & 0xfff);
    if (iVar4 == 0) {
      iVar4 = -0x80000000;
    }
    FUN_00190140(param_4,iVar4);
    break;
  case 0x3a:
    iVar4 = FUN_00198150(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x3b:
    iVar4 = FUN_00198284(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x3c:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00196070(param_4,param_3 & 0xfff);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x3d:
  case 0x3e:
  case 0x114:
    FUN_00190140(param_4,uVar7 & 0xf);
    break;
  case 0x3f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = FUN_00196350(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x40:
    iVar4 = FUN_00196350(param_4,param_3 & 0xfef);
    goto joined_r0x001a29a4;
  case 0x41:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x42:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar1 >> 7 & 0x1f);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x43:
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x44:
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = FUN_00196a40(param_4,0);
    if (iVar4 == 1) {
      return 1;
    }
    goto joined_r0x0019c998;
  case 0x45:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x46:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar1 >> 10 & 3);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x47:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar1 >> 10 & 3);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x48:
    iVar4 = FUN_00197ef0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x49:
    iVar4 = FUN_00198014(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x4a:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190140(param_4,0);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar1 >> 7 & 0x1f | (uVar1 >> 6 & 1) << 5);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4b:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190140(param_4,0);
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4c:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190140(param_4,uVar1 >> 7 & 0x1f);
    FUN_00190140(param_4,0);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x4d:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    iVar4 = FUN_00196350(param_4,param_3 & 0xfef);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x4e:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    if ((param_3 & 0xf80) == 0) {
      FUN_00190140(param_4,0xfffffffe);
    }
    else {
      param_1 = 1;
      FUN_00190140(param_4,0xfffffffe);
    }
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x4f:
    if (uVar1 >> 0xc == 0xf) {
      FUN_00190100(param_4,0xb);
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2);
      FUN_00190100(param_4,uVar10);
      FUN_00190100(param_4,uVar10);
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    iVar4 = FUN_00196400(param_4,uVar1 >> 7 & 0x1f);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x50:
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    iVar4 = FUN_00196470(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x51:
  case 0x113:
    FUN_00190100(param_4,0x42);
    break;
  case 0x52:
    iVar4 = FUN_00198bd0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x53:
    FUN_00190140(param_4,uVar7 & 0x1f);
    break;
  case 0x54:
    iVar4 = FUN_00197370(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x55:
    FUN_00190140(param_4,(uVar7 & 0x7fff) << 1);
    break;
  case 0x56:
    iVar4 = FUN_00195b90(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x57:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,uVar1 >> 4 & 0xf);
      if (uVar1 >> 0xc == 0xf) {
        param_1 = 1;
        FUN_00190100(param_4,0xb);
      }
      else {
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
      }
      FUN_00190100(param_4,0x42);
      FUN_00190140(param_4,uVar7 & 0xf);
      iVar4 = FUN_00196a40(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x58:
    if (uVar1 >> 0xc == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196e24(param_4,uVar1 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 4 & 0xf);
      FUN_00190140(param_4,uVar7 & 0xf);
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x59:
    FUN_00190140(param_4,uVar7);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x5a:
    iVar4 = FUN_00199d00(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x5b:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar1 >> 0xc);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5c:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar1 >> 0xc);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5d:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5e:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      FUN_0018ffb0(param_4);
      FUN_00190140(param_4,0);
      FUN_00190100(param_4,3);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x5f:
    if (uVar1 >> 0xc == 0xf) {
      FUN_00190100(param_4,2);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x60:
    if (uVar1 >> 0xc == 0xf) {
      FUN_00190100(param_4,2);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    }
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,0);
      FUN_00190140(param_4,uVar7 & 0xf);
      FUN_00190140(param_4,uVar1 >> 5 & 7);
      iVar4 = FUN_00196a40(param_4,0);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x61:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x62:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          param_1 = uVar3;
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 99:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 100:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x65:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x66:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
        }
        else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
        iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x67:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
    if ((param_3 & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x68:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x69:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          if ((param_3 & 1) == 0) {
            iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
            goto joined_r0x001a29a4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6b:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 7);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a2c00:
        FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a2c00;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = FUN_00196b50(param_4,param_3 & 7);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a5280:
              FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a5280;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = FUN_00196b50(param_4,param_3 & 7);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a52e8:
              FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a52e8;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x6e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 7);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x6f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        iVar4 = FUN_00196b50(param_4,param_3 & 7);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a0da4:
          FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a0da4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x70:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = FUN_00196b50(param_4,param_3 & 7);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a349c:
          FUN_00190140(param_4,uVar1 >> 3 & 1 | (uVar1 >> 5 & 1) << 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a349c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x71:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a3330:
        FUN_00190140(param_4,uVar1 >> 5 & 1);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a3330;
    }
    goto switchD_0019c568_caseD_9;
  case 0x72:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a51e4:
              FUN_00190140(param_4,uVar1 >> 5 & 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a51e4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x73:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a52a4:
              FUN_00190140(param_4,uVar1 >> 5 & 1);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a52a4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x74:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 5 & 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x75:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a31e4:
          FUN_00190140(param_4,uVar1 >> 5 & 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a31e4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x76:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
        iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a32b4:
          FUN_00190140(param_4,uVar1 >> 5 & 1);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a32b4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x77:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 10 & 1);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x78:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 9 & 3);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x79:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,uVar1 >> 8 & 7);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x7a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a33ac:
            FUN_00190140(param_4,uVar1 >> 0xb & 1);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a33ac;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a2b20:
            FUN_00190140(param_4,uVar1 >> 10 & 3);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a2b20;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_0019ee60:
            FUN_00190140(param_4,uVar1 >> 9 & 7);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_0019ee60;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_0019ede4:
            FUN_00190140(param_4,uVar1 >> 8 & 0xf);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_0019ede4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x7e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    break;
  case 0x7f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        param_1 = uVar3;
        goto joined_r0x001a29a4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x80:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    uVar2 = param_3 & 0xf | (uVar1 >> 5 & 1) << 4;
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar2 * 2));
    iVar4 = FUN_00196b50(param_4,uVar1 >> 0xc);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,uVar2);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x81:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) &&
         (uVar2 = param_3 & 0xf | (uVar1 >> 5 & 1) << 4, (param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,uVar2);
        param_1 = 1;
        if ((iVar4 == 1) || (param_1 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
          if (iVar4 == 1) {
            param_1 = 1;
          }
          else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
          iVar4 = FUN_00195b60(param_4,uVar2);
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x82:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x83:
    iVar4 = FUN_00197970(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x84:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    goto joined_r0x001a29a4;
  case 0x85:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        if (iVar4 == 1) {
          uVar3 = 1;
        }
        else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          param_1 = uVar3;
          goto joined_r0x001a29a4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x86:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x87:
    iVar4 = FUN_0019a440(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x88:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x89:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x8a:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x8b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x8e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,8);
    break;
  case 0x8f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0x10);
    break;
  case 0x90:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0x20);
    break;
  case 0x91:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,8);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x92:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0x10);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x93:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0x20);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x94:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x95:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x96:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x97:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x98:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0x99:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x9a:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190140(param_4,8);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9b:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190140(param_4,0x10);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9c:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    if ((param_3 & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190140(param_4,0x20);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9d:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9e:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x9f:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,*(undefined2 *)
                              (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
        FUN_00190140(param_4,0);
        return uVar3;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa0:
    iVar4 = FUN_0019a8d0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xa1:
    iVar4 = FUN_0019a190(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xa2:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0x40);
    break;
  case 0xa3:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0x40);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0xa4:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190140(param_4,0);
    break;
  case 0xa5:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0xa6:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a352c:
          FUN_00190140(param_4,8);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a352c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa7:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2944:
          FUN_00190140(param_4,0x10);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2944;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa8:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2aa4:
          FUN_00190140(param_4,0x20);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2aa4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xa9:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4f28:
            FUN_00190140(param_4,8);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4f28;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xaa:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4ed4:
            FUN_00190140(param_4,0x10);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4ed4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xab:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4d48:
            FUN_00190140(param_4,0x20);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4d48;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xac:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a1aa8:
          FUN_00190140(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a1aa8;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xad:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4be8:
            FUN_00190140(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4be8;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xae:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a2d74:
          FUN_00190140(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a2d74;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xaf:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4f7c:
            FUN_00190140(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4f7c;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb0:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_001a28e4:
          FUN_00190140(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_001a28e4;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb1:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4da0:
            FUN_00190140(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4da0;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb2:
    iVar4 = FUN_0019a320(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xb3:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_0019f3bc:
          FUN_00190140(param_4,0x40);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_0019f3bc;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb4:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4e88:
            FUN_00190140(param_4,0x40);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4e88;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb5:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if (((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) && ((param_3 & 1) == 0)) {
        iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
        if (iVar4 == 1) {
          uVar3 = 1;
LAB_0019f328:
          FUN_00190140(param_4,0);
          return uVar3;
        }
        if (iVar4 == 3) goto LAB_0019f328;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb6:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if (((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) && ((param_3 & 1) == 0)) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar8 = 1;
LAB_001a4e50:
            FUN_00190140(param_4,0);
            return uVar8;
          }
          if (iVar4 == 3) goto LAB_001a4e50;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xb7:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,0);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0xb8:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    FUN_00190140(param_4,0);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0xb9:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,uVar1 >> 6 & 1);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0xba:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    FUN_00190140(param_4,uVar1 >> 6 & 1);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0xbb:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,uVar1 >> 5 & 3);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0xbc:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    FUN_00190140(param_4,uVar1 >> 5 & 3);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0xbd:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0xbe:
    FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0xbf:
    if ((param_3 & 0xc0) != 0xc0) {
      iVar4 = FUN_0019bc74(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xc0:
    iVar4 = FUN_00198780(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc1:
    iVar4 = FUN_00199b60(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc2:
    iVar4 = FUN_001999e0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc3:
    iVar4 = FUN_0019b1f0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc4:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((uVar2 == 6) || (uVar2 == 7)) {
      if ((uVar1 >> 5 & 1) == 0) goto LAB_0019cc70;
    }
    else if ((uVar1 >> 4 & 3) != 3 || uVar2 != 10) {
LAB_0019cc70:
      iVar4 = FUN_0019bc74(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xc5:
    iVar4 = FUN_0019af00(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc6:
    iVar4 = FUN_0019c0b0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 199:
    if (((param_3 & 0xc0) != 0xc0) &&
       (uVar1 = uVar1 >> 8 & 0xf, (param_3 & 0x30) != 0x30 || uVar1 != 8 && uVar1 != 9)) {
      iVar4 = FUN_0019bc74(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 200:
    iVar4 = FUN_0019b4c0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xc9:
    iVar4 = FUN_0019c290(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xca:
    if (((param_3 & 0xc0) != 0xc0) && ((uVar1 >> 5 & 1) == 0)) {
      iVar4 = FUN_0019bc74(param_4,uVar7);
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0xcb:
    iVar4 = FUN_00199f54(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcc:
    iVar4 = FUN_00198fd0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcd:
    iVar4 = FUN_0019a080(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xce:
    iVar4 = FUN_0019b080(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xcf:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    break;
  case 0xd0:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2));
    FUN_00190140(param_4,uVar7 & 0xff);
    break;
  case 0xd1:
    iVar4 = FUN_00195e10(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xd2:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 7 | (uVar1 >> 7 & 1) << 3) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd3:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f720 + (ulong)(param_3 & 7 | (uVar1 >> 7 & 1) << 3) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd4:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 0xf) * 2));
    break;
  case 0xd5:
    uVar1 = uVar1 >> 3 & 0xf;
    if (uVar1 != 0xf) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
      return param_1;
    }
    goto LAB_001a35e8;
  case 0xd6:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2));
    FUN_00190140(param_4,(uVar7 & 0xff) << 2);
    break;
  case 0xd7:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (((ulong)(uVar1 >> 3) & 0x3f) >> 3) * 2));
    break;
  case 0xd8:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190140(param_4,((ulong)(uVar1 >> 3) & 0xff) >> 3);
    break;
  case 0xd9:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2));
    FUN_00190100(param_4,0xc);
    FUN_00190140(param_4,uVar7 & 0xff);
    break;
  case 0xda:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2));
    iVar4 = FUN_0018ffb0(param_4);
    if (iVar4 == 0xc3e) {
      FUN_00190100(param_4,0xc);
    }
    else if (iVar4 != 0xc42) goto switchD_0019c568_caseD_9;
  case 0xe2:
    FUN_00190140(param_4,uVar7 & 0xff);
    break;
  case 0xdb:
    FUN_00190100(param_4,0xc);
    FUN_00190100(param_4,0xc);
    FUN_00190140(param_4,uVar7 & 0x7f);
    break;
  case 0xdc:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190140(param_4,(ulong)(uVar1 >> 3 & 0x1f | (uVar1 >> 9 & 1) << 5) << 1);
    break;
  case 0xdd:
    iVar4 = FUN_00196470(param_4,param_3 & 0xff | (uVar1 >> 8 & 1) << 0xe);
    goto joined_r0x001a29a4;
  case 0xde:
    FUN_00190140(param_4,uVar1 >> 3 & 1);
    break;
  case 0xdf:
    FUN_00190140(param_4,uVar1 >> 4 & 1 | 2);
    FUN_00190140(param_4,uVar7 & 7);
    break;
  case 0xe0:
    FUN_00190140(param_4,uVar7 & 0x3f);
    break;
  case 0xe1:
    iVar4 = FUN_00196470(param_4,param_3 & 0xff | (uVar1 >> 8 & 1) << 0xf);
    goto joined_r0x001a29a4;
  case 0xe3:
    FUN_00190140(param_4,uVar1 >> 4 & 0xf);
    break;
  case 0xe4:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196470(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xe5:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2));
    iVar4 = FUN_00196470(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xe6:
    uVar2 = uVar1 >> 8 & 0xf;
    FUN_00190140(param_4,(long)(int)(-(uVar1 >> 7 & 1) & 0xfffffe00 | (param_3 & 0xff) << 1));
    if (uVar2 != 0xf) {
      iVar4 = FUN_0018ffb0(param_4);
      if (iVar4 != 0xc4f) {
        FUN_00190140(param_4,uVar2);
        if (uVar2 == 0xe) {
          FUN_00190100(param_4,0);
          return param_1;
        }
LAB_001a1d2c:
        FUN_00190100(param_4,3);
        return param_1;
      }
      if (uVar2 != 0xe) {
        FUN_00190140(param_4,uVar2);
        goto LAB_001a1d2c;
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0xe7:
    FUN_00190140(param_4,-((ulong)(uVar1 >> 10) & 1) & 0xfffffffffffff000 | (uVar7 & 0x7ff) << 1);
    break;
  case 0xe8:
    FUN_00190140(param_4,(param_3 & 0x7fe) << 1 | 0xc00000);
    break;
  case 0xe9:
    FUN_00190140(param_4,(uVar7 & 0x7ff) << 1 | 0xc00000);
    break;
  case 0xea:
    uVar1 = uVar1 >> 4 & 0xf;
    if (uVar1 == 0xf) {
      if ((param_3 & 0xf) != 0) {
        FUN_00190140(param_4,0xe);
        FUN_00190140(param_4,param_3 & 0xf);
        return 1;
      }
    }
    else if ((param_3 & 0xf) != 0) {
      FUN_00190140(param_4,uVar1);
      FUN_00190140(param_4,param_3 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0xeb:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196470(param_4,param_3 & 0x5fff);
    goto joined_r0x001a29a4;
  case 0xec:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196470(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xed:
    param_3 = param_3 & 0xf;
    FUN_00190100(param_4,0x42);
    if (param_3 != 0xd) {
      if (param_3 != 0xf) {
LAB_001a1be0:
        FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
        return param_1;
      }
      goto LAB_001a35e8;
    }
    if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a1be0;
    goto LAB_001a3b78;
  case 0xee:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_001974f4(param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 0xef:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3658;
      FUN_00190100(param_4,0xc);
LAB_0019c9c4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c9c4;
      }
LAB_001a3658:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0xf0:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3700;
      FUN_00190100(param_4,0xc);
LAB_0019c804:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c804;
      }
LAB_001a3700:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_001974f4(param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0xf1:
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0xf2:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_001974f4(param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0xf3:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196470(param_4,param_3 & 0x5fff);
    goto joined_r0x001a29a4;
  case 0xf4:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196470(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xf5:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3974;
      FUN_00190100(param_4,0xc);
LAB_0019c878:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c878;
      }
LAB_001a3974:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    break;
  case 0xf6:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37ac;
      FUN_00190100(param_4,0xc);
LAB_0019c8ac:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c8ac;
      }
LAB_001a37ac:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a443c;
      FUN_00190100(param_4,0xc);
LAB_0019c8d0:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c8d0;
      }
LAB_001a443c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    iVar4 = FUN_00195fe4(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xf7:
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36e4;
      FUN_00190100(param_4,0xc);
LAB_0019c70c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c70c;
      }
LAB_001a36e4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44b8;
      FUN_00190100(param_4,0xc);
LAB_0019c730:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019c730;
      }
LAB_001a44b8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    FUN_00190100(param_4,0x42);
    break;
  case 0xf8:
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a39b0;
      FUN_00190100(param_4,0xc);
LAB_001a199c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a199c;
      }
LAB_001a39b0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a469c;
      FUN_00190100(param_4,0xc);
LAB_001a19c0:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a19c0;
      }
LAB_001a469c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    iVar4 = FUN_00197240(param_4,uVar1 >> 8 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0x42);
    break;
  case 0xf9:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37e4;
      FUN_00190100(param_4,0xc);
LAB_001a1968:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a1968;
      }
LAB_001a37e4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    FUN_00190100(param_4,0x42);
    break;
  case 0xfa:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3638;
      FUN_00190100(param_4,0xc);
LAB_0019e21c:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e21c;
      }
LAB_001a3638:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xff);
    break;
  case 0xfb:
    iVar4 = FUN_00197440(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0xfc:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a361c;
      FUN_00190100(param_4,0xc);
LAB_001a0f20:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a0f20;
      }
LAB_001a361c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44d4;
      FUN_00190100(param_4,0xc);
LAB_001a0f44:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a0f44;
      }
LAB_001a44d4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    break;
  case 0xfd:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3958;
      FUN_00190100(param_4,0xc);
LAB_001a0eb8:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a0eb8;
      }
LAB_001a3958:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a43c4;
      FUN_00190100(param_4,0xc);
LAB_001a0edc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_001a0edc;
      }
LAB_001a43c4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    iVar4 = FUN_00196ad0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0xfe:
    uVar1 = uVar1 >> 8 & 0xf;
    if (uVar1 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    if ((param_3 & 0xf) == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_3 & 0xf) * 2));
    }
    FUN_00190100(param_4,0);
    break;
  case 0xff:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3994;
      FUN_00190100(param_4,0xc);
LAB_0019e25c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e25c;
      }
LAB_001a3994:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4624;
      FUN_00190100(param_4,0xc);
LAB_0019e280:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e280;
      }
LAB_001a4624:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    FUN_00190100(param_4,0);
    break;
  case 0x100:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3674;
      FUN_00190100(param_4,0xc);
LAB_0019e050:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e050;
      }
LAB_001a3674:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a48f0;
      FUN_00190100(param_4,0xc);
LAB_0019e074:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e074;
      }
LAB_001a48f0:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    FUN_00190140(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    FUN_00190100(param_4,0);
    break;
  case 0x101:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38ac;
      FUN_00190100(param_4,0xc);
LAB_0019dfe4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019dfe4;
      }
LAB_001a38ac:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190140(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    break;
  case 0x102:
    FUN_00190100(param_4,0x42);
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a373c;
      FUN_00190100(param_4,0xc);
LAB_0019df7c:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019df7c;
      }
LAB_001a373c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4a60;
      FUN_00190100(param_4,0xc);
LAB_0019dfa0:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019dfa0;
      }
LAB_001a4a60:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xff) == 0) {
      FUN_00190140(param_4,0xffffffff80000000);
    }
    else {
      FUN_00195b40(param_4,param_3 & 0xff);
    }
    break;
  case 0x103:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a393c;
      FUN_00190100(param_4,0xc);
LAB_0019defc:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019defc;
      }
LAB_001a393c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a44f4;
      FUN_00190100(param_4,0xc);
LAB_0019df20:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019df20;
      }
LAB_001a44f4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    if ((param_3 & 0xff) == 0) {
      FUN_00190140(param_4,0xffffffff80000000);
    }
    else {
      FUN_00195b40(param_4,param_3 & 0xff);
    }
    break;
  case 0x104:
    iVar4 = FUN_0019a520(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x105:
    iVar4 = FUN_0019a6f4(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x106:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3790;
      FUN_00190100(param_4,0xc);
LAB_0019db50:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019db50;
      }
LAB_001a3790:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    iVar4 = FUN_001974f4(param_4,(uVar1 >> 0xc & 7) << 9 | (uVar1 >> 4 & 0xf) << 5 | param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0x107:
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00195d60(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    goto joined_r0x001a29a4;
  case 0x108:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a37c8;
      FUN_00190100(param_4,0xc);
LAB_0019de5c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019de5c;
      }
LAB_001a37c8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00195d60(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0x109:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3600;
      FUN_00190100(param_4,0xc);
LAB_0019de00:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019de00;
      }
LAB_001a3600:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    iVar4 = FUN_00195d60(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0x10a:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00195d60(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190100(param_4,0);
    break;
  case 0x10b:
    uVar2 = uVar1 >> 8 & 0xf;
    if (uVar2 == 0xf) {
      param_1 = 1;
      FUN_00190100(param_4,0xb);
    }
    else {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,param_3 & 0xff | (uVar1 >> 0xc & 7) << 8);
    break;
  case 0x10c:
    FUN_00190140(param_4,param_3 & 0xff | (param_3 & 0x7000) >> 4);
    break;
  case 0x10d:
    iVar4 = FUN_00199150(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x10e:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a371c;
      FUN_00190100(param_4,0xc);
LAB_0019e12c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019e12c;
      }
LAB_001a371c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
    }
    FUN_00190140(param_4,uVar7 & 0xf);
    FUN_00190100(param_4,0x42);
    break;
  case 0x10f:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38e4;
      FUN_00190100(param_4,0xc);
LAB_0019d92c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d92c;
      }
LAB_001a38e4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
    }
    FUN_00190140(param_4,uVar7 & 0x1f);
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    break;
  case 0x110:
    uVar6 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar6;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a39cc;
      FUN_00190100(param_4,0xc);
LAB_0019dd58:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019dd58;
      }
LAB_001a39cc:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar6 * 2));
    }
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar1 >> 6 & 3 | (uVar1 >> 0xc & 7) << 2);
    FUN_00190140(param_4,uVar7 & 0x1f);
    break;
  case 0x111:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        FUN_00190100(param_4,0xc);
      }
      else {
        FUN_00190100(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) {
        uVar10 = 0xc;
        goto LAB_001a4080;
      }
      FUN_00190100(param_4,0xc);
LAB_0019dd04:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        FUN_00190100(param_4,0xb);
        goto LAB_0019dd04;
      }
      uVar10 = *(undefined2 *)(&DAT_0022f720 + uVar7 * 2);
      FUN_00190100(param_4,uVar10);
LAB_001a4080:
      FUN_00190100(param_4,uVar10);
    }
    iVar4 = FUN_00196400(param_4,uVar1 >> 6 & 3 | (param_3 & 0x1f) << 5 | (uVar1 >> 0xc & 7) << 2);
    goto joined_r0x001a29a4;
  case 0x112:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
        param_1 = 1;
        FUN_00190100(param_4,0xc);
      }
      else {
        FUN_00190100(param_4,0xc);
      }
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) {
        uVar10 = 0xc;
        goto LAB_001a4050;
      }
      FUN_00190100(param_4,0xc);
LAB_0019e0cc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        FUN_00190100(param_4,0xb);
        goto LAB_0019e0cc;
      }
      uVar10 = *(undefined2 *)(&DAT_0022f720 + uVar7 * 2);
      FUN_00190100(param_4,uVar10);
LAB_001a4050:
      FUN_00190100(param_4,uVar10);
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00196400(param_4,uVar1 >> 6 & 3 | (param_3 & 0x1f) << 5 | (uVar1 >> 0xc & 7) << 2);
    goto joined_r0x001a29a4;
  case 0x115:
    iVar4 = FUN_001960d4(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x116:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    break;
  case 0x117:
    iVar4 = FUN_0019aa04(param_4,uVar1 >> 8 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190100(param_4,0x42);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x118:
    uVar1 = uVar1 >> 8 & 0xf | (uVar1 >> 4 & 1) << 4;
    lVar5 = FUN_001bb9e0(uVar1);
    if (lVar5 != 0) {
      FUN_00190140(param_4,uVar1);
      FUN_00190100(param_4,0x42);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x119:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3920;
      FUN_00190100(param_4,0xc);
LAB_0019da7c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019da7c;
      }
LAB_001a3920:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 4) & 1;
    lVar5 = FUN_001bb9e0((int)uVar7 << 4);
    if (lVar5 != 0) {
      FUN_00190140(param_4,uVar7 << 4);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x11a:
    FUN_00190140(param_4,uVar7 & 0xfff);
    break;
  case 0x11b:
    FUN_00190140(param_4,0);
    break;
  case 0x11c:
    iVar4 = FUN_0019aa04(param_4,param_3 & 0xcff);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190100(param_4,0x42);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x11d:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a381c;
      FUN_00190100(param_4,0xc);
LAB_0019dbdc:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019dbdc;
      }
LAB_001a381c:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    iVar4 = FUN_0019aa04(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0x11e:
    iVar4 = FUN_00198520(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x11f:
    FUN_00190140(param_4,(((uint)((uVar7 ^ 0x800) >> 0xb) & 1) << 0x15 |
                          ((uint)((uVar7 ^ 0x2000) >> 0xd) & 1) << 0x16 | param_3 & 0x7ff) << 1);
    break;
  case 0x120:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3758;
      FUN_00190100(param_4,0xc);
LAB_0019dc84:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019dc84;
      }
LAB_001a3758:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    iVar4 = FUN_001976d0(param_4,uVar1 >> 4 & 3 | (param_3 & 0xf) << 2);
    goto joined_r0x001a29a4;
  case 0x121:
    iVar4 = FUN_00196c70(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x122:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3838;
      FUN_00190100(param_4,0xc);
LAB_0019d7e0:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d7e0;
      }
LAB_001a3838:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    iVar4 = FUN_00195ee0(param_4,param_3 & 0xff);
    goto joined_r0x001a29a4;
  case 0x123:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3890;
      FUN_00190100(param_4,0xc);
LAB_0019d790:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d790;
      }
LAB_001a3890:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    iVar4 = FUN_00195ee0(param_4,param_3 & 0xff | (uVar1 >> 9 & 1) << 8);
    goto joined_r0x001a29a4;
  case 0x124:
    uVar1 = uVar1 >> 0xc;
    if (uVar1 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3870;
      FUN_00190100(param_4,0xc);
LAB_0019d748:
      param_1 = 1;
    }
    else {
      if (uVar1 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d748;
      }
LAB_001a3870:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    }
    FUN_0018ffb0(param_4);
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xfff);
    break;
  case 0x125:
    iVar4 = FUN_001977b0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x126:
    iVar4 = FUN_00196e80(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x127:
    iVar4 = FUN_001983c0(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x128:
    iVar4 = FUN_00197050(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x129:
    iVar4 = FUN_00196b84(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x12a:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3774;
      FUN_00190100(param_4,0xc);
LAB_0019d8d8:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d8d8;
      }
LAB_001a3774:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 299:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3904;
      FUN_00190100(param_4,0xc);
LAB_0019d880:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d880;
      }
LAB_001a3904:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a43a4;
      FUN_00190100(param_4,0xc);
LAB_0019d8a4:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d8a4;
      }
LAB_001a43a4:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    FUN_00190140(param_4,uVar1 >> 4 & 3);
    break;
  case 300:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a38c8;
      FUN_00190100(param_4,0xc);
LAB_0019da1c:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019da1c;
      }
LAB_001a38c8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    if (iVar4 == 1) {
      param_1 = 1;
    }
    else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
    FUN_00190140(param_4,uVar1 >> 4 & 3);
    break;
  case 0x12d:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36ac;
      FUN_00190100(param_4,0xc);
LAB_0019d828:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d828;
      }
LAB_001a36ac:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4910;
      FUN_00190100(param_4,0xc);
LAB_0019d84c:
      param_1 = 1;
    }
    else {
      if (param_3 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d84c;
      }
LAB_001a4910:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    }
    FUN_00190100(param_4,0x42);
    break;
  case 0x12e:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3690;
      FUN_00190100(param_4,0xc);
LAB_0019d9c8:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d9c8;
      }
LAB_001a3690:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    param_3 = param_3 & 0xf;
    if (param_3 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0) {
LAB_001a3b78:
        FUN_00190100(param_4,0xc);
        return 1;
      }
    }
    else if (param_3 == 0xf) {
LAB_001a35e8:
      FUN_00190100(param_4,0xb);
      return 1;
    }
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)param_3 * 2));
    break;
  case 0x12f:
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3800;
      FUN_00190100(param_4,0xc);
LAB_0019d5a4:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d5a4;
      }
LAB_001a3800:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00197240(param_4,uVar1 >> 0xc);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x130:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a36c8;
      FUN_00190100(param_4,0xc);
LAB_0019d530:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d530;
      }
LAB_001a36c8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    iVar4 = (int)uVar7;
    if (iVar4 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a4514;
      FUN_00190100(param_4,0xc);
LAB_0019d554:
      param_1 = 1;
    }
    else {
      if (iVar4 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d554;
      }
LAB_001a4514:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    goto joined_r0x001a29a4;
  case 0x131:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 0xf) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    break;
  case 0x132:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = FUN_001976d0(param_4,uVar1 >> 4 & 3 | (param_3 & 0xf) << 2);
    goto joined_r0x001a29a4;
  case 0x133:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    iVar4 = FUN_00195ee0(param_4,param_3 & 0xff | (uVar1 >> 9 & 1) << 8);
    goto joined_r0x001a29a4;
  case 0x134:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xfff);
    break;
  case 0x135:
    uVar2 = uVar1 >> 0xc;
    if (uVar2 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a3854;
      FUN_00190100(param_4,0xc);
LAB_0019d3b0:
      param_1 = 1;
    }
    else {
      if (uVar2 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d3b0;
      }
LAB_001a3854:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2));
    }
    uVar7 = (ulong)(uVar1 >> 8) & 0xf;
    if ((int)uVar7 == 0xd) {
      if ((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) != 0) goto LAB_001a47e8;
      FUN_00190100(param_4,0xc);
LAB_0019d3d4:
      param_1 = 1;
    }
    else {
      if ((int)uVar7 == 0xf) {
        FUN_00190100(param_4,0xb);
        goto LAB_0019d3d4;
      }
LAB_001a47e8:
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + uVar7 * 2));
    }
    FUN_00190100(param_4,0x42);
    iVar4 = FUN_00197240(param_4,param_3 & 0xf);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00197240(param_4,uVar2);
      if (iVar4 == 1) {
        uVar3 = 1;
      }
      else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
      iVar4 = FUN_00197240(param_4,uVar7);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x136:
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,uVar1 >> 4 & 0xf);
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
      FUN_00190100(param_4,0x42);
      FUN_00190140(param_4,uVar7 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x137:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    uVar2 = uVar1 >> 8 & 0xf;
    if ((1 < uVar2 - 10) &&
       (((*(uint *)(*(long *)(param_4 + 800) + 4) >> 6 & 1) == 0 || (uVar2 - 0xe < 2)))) {
      FUN_00190140(param_4,uVar2);
      FUN_00190140(param_4,uVar1 >> 4 & 0xf);
      FUN_00190140(param_4,uVar7 & 0xf);
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x138:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190140(param_4,uVar1 >> 6 & 0x1f);
    break;
  case 0x139:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 6) & 7) * 2));
    break;
  case 0x13a:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190140(param_4,uVar1 >> 6 & 7);
    break;
  case 0x13b:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 8) & 7) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190140(param_4,uVar7 & 0xff);
    break;
  case 0x13c:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    break;
  case 0x13d:
    uVar10 = *(undefined2 *)(&DAT_0022f720 + (uVar7 & 7) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + ((ulong)(uVar1 >> 3) & 7) * 2));
    FUN_00190100(param_4,uVar10);
    break;
  case 0x13e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xff | 0x100);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x13f:
    uVar10 = *(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x140:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x141:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x142:
    iVar4 = FUN_00197c30(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x143:
    FUN_00190100(param_4,0x42);
    uVar2 = param_3 & 0xff;
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    uVar1 = ((uVar1 >> 0xc) << 9) >> 8;
    if ((param_3 & 0xff) == 0) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
      return 1;
    }
    if (uVar1 + uVar2 < 0x21) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
      uVar9 = uVar2 - 1;
      iVar4 = 3;
      if (uVar2 == 1) {
        return param_1;
      }
    }
    else {
      uVar9 = 0x1f - uVar1;
      iVar4 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
    }
    uVar7 = (ulong)(uVar1 + 2);
    do {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f79e + uVar7 * 2));
      if (uVar9 <= ((int)uVar7 - uVar1) - 1) {
joined_r0x001a5108:
        if (iVar4 == 1) {
          return 1;
        }
        return param_1;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 != (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1));
    goto switchD_0019c568_caseD_9;
  case 0x144:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xff | 0x100);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x145:
    uVar10 = *(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x146:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x147:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x148:
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x149:
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    iVar4 = FUN_001975b0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x14a:
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    iVar4 = FUN_001975b0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x14b:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190140(param_4,uVar7 & 0xff | 0x100);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x14c:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      if (iVar4 == 1) {
        uVar3 = 1;
      }
      else if (iVar4 != 3) goto switchD_0019c568_caseD_9;
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x14d:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196a40(param_4,0);
      param_1 = uVar3;
      goto joined_r0x001a29a4;
    }
    goto switchD_0019c568_caseD_9;
  case 0x14e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x14f:
    iVar4 = FUN_00197d94(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x150:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x151:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x152:
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x153:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    uVar2 = param_3 & 0xff;
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    uVar1 = ((uVar1 >> 0xc) << 9) >> 8;
    if ((param_3 & 0xff) == 0) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
      return 1;
    }
    if (uVar1 + uVar2 < 0x21) {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
      uVar9 = uVar2 - 1;
      iVar4 = 3;
      if (uVar2 == 1) {
        return param_1;
      }
    }
    else {
      uVar9 = 0x1f - uVar1;
      iVar4 = 1;
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)uVar1 * 2));
    }
    uVar7 = (ulong)(uVar1 + 2);
    do {
      FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f79e + uVar7 * 2));
      if (uVar9 <= ((int)uVar7 - uVar1) - 1) goto joined_r0x001a5108;
      uVar7 = uVar7 + 1;
    } while (uVar7 != (ulong)(uVar1 + 3) + (ulong)(0x1e - uVar1));
    goto switchD_0019c568_caseD_9;
  case 0x154:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    iVar4 = FUN_001975b0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x155:
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,0x42);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    iVar4 = FUN_001975b0(param_4,(uVar1 >> 0xc) << 8 | (uVar1 >> 1 & 0x7f) << 1);
    goto joined_r0x001a29a4;
  case 0x156:
    iVar4 = FUN_00198620(param_4,uVar7);
    goto joined_r0x001a29a4;
  case 0x157:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190140(param_4,uVar7 & 0xf);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x158:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x159:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15a:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15b:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15c:
    uVar10 = *(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190140(param_4,uVar1 >> 5 & 1 | (param_3 & 0xf) << 1);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15d:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190140(param_4,uVar7 & 0xf);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x15f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x160:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x161:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190140(param_4,uVar7 & 0xf);
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x162:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x163:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x164:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    break;
  case 0x165:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    FUN_00190140(param_4,uVar1 >> 5 & 1 | (param_3 & 0xf) << 1);
    iVar4 = FUN_00196a40(param_4,0);
    goto joined_r0x001a29a4;
  case 0x166:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f4e0 + ((ulong)(uVar1 >> 7) & 1) * 0x20));
    iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      FUN_00190140(param_4,0);
      return uVar3;
    }
    goto switchD_0019c568_caseD_9;
  case 0x167:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a02c0:
        FUN_00190140(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a02c0;
    }
    goto switchD_0019c568_caseD_9;
  case 0x168:
    uVar10 = *(undefined2 *)(&DAT_0022f4e0 + (ulong)(uVar1 >> 0xc) * 2);
    FUN_00190100(param_4,uVar10);
    FUN_00190100(param_4,uVar10);
    iVar4 = FUN_00196b50(param_4,(uVar1 >> 7 & 1) << 4);
    uVar3 = 1;
    if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
      iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
      if (iVar4 == 1) {
        uVar3 = 1;
LAB_001a0230:
        FUN_00190140(param_4,uVar1 >> 5 & 1);
        FUN_00190140(param_4,0);
        return uVar3;
      }
      if (iVar4 == 3) goto LAB_001a0230;
    }
    goto switchD_0019c568_caseD_9;
  case 0x169:
    iVar4 = FUN_0019b3a4(param_4,uVar7);
joined_r0x001a29a4:
    if (iVar4 == 1) {
      return 1;
    }
joined_r0x0019c998:
    if (iVar4 == 3) {
      return param_1;
    }
    goto switchD_0019c568_caseD_9;
  case 0x16a:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        FUN_00190100(param_4,L"23456789:;<=>?@A"[((ulong)(uVar1 >> 7) & 1) * 8]);
        if ((param_3 & 1) == 0) {
          iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
          if (iVar4 == 1) {
            uVar3 = 1;
LAB_001a03b4:
            FUN_00190140(param_4,0);
            return uVar3;
          }
          if (iVar4 == 3) goto LAB_001a03b4;
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x16b:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if (((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) && ((param_3 & 1) == 0)) {
            iVar4 = FUN_00195b60(param_4,param_3 & 0xf | (uVar1 >> 5 & 1) << 4);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a51c4:
              FUN_00190140(param_4,0);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a51c4;
          }
        }
      }
    }
    goto switchD_0019c568_caseD_9;
  case 0x16c:
    if ((uVar1 >> 0xc & 1) == 0) {
      iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
      uVar3 = 1;
      if ((iVar4 == 1) || (uVar3 = param_1, iVar4 == 3)) {
        iVar4 = FUN_00195b60(param_4,uVar1 >> 0xc);
        uVar8 = 1;
        if ((iVar4 == 1) || (uVar8 = uVar3, iVar4 == 3)) {
          iVar4 = FUN_00195b60(param_4,(uVar1 >> 7 & 1) << 4);
          uVar3 = 1;
          if ((iVar4 == 1) || (uVar3 = uVar8, iVar4 == 3)) {
            iVar4 = FUN_00196b50(param_4,param_3 & 0xf);
            if (iVar4 == 1) {
              uVar3 = 1;
LAB_001a535c:
              FUN_00190140(param_4,uVar1 >> 5 & 1);
              FUN_00190140(param_4,0);
              return uVar3;
            }
            if (iVar4 == 3) goto LAB_001a535c;
          }
        }
      }
    }
switchD_0019c568_caseD_9:
    param_1 = 0;
    break;
  case 0x16d:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x16e:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x16f:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x170:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + ((ulong)(uVar1 >> 7) & 1) * 2));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f7a0 + (ulong)(uVar1 >> 5 & 1 | (param_3 & 0xf) << 1) * 2));
    break;
  case 0x171:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f7a0 + (ulong)(uVar1 >> 0xc) * 4));
    FUN_00190100(param_4,*(undefined2 *)
                          (&DAT_0022f4e0 + (ulong)(param_3 & 0xf | (uVar1 >> 5 & 1) << 4) * 2));
    break;
  default:
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (ulong)(uVar1 >> 0xc) * 2));
    FUN_00190100(param_4,0x42);
    FUN_00190100(param_4,*(undefined2 *)(&DAT_0022f720 + (uVar7 & 0xf) * 2));
    FUN_0018ffb0(param_4);
    FUN_00190140(param_4,0);
    FUN_00190100(param_4,3);
    FUN_00190100(param_4,0);
    goto LAB_0019c63c;
  }
  return param_1;
LAB_0019c63c:
  return param_1;
}

