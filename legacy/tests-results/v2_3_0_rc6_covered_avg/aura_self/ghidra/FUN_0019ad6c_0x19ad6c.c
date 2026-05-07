
undefined4 FUN_0019ad6c(undefined8 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  
  uVar1 = param_2 >> 0xc & 0xf;
  uVar2 = param_2 >> 0x10 & 0xf;
  uVar6 = 1;
  uVar4 = uVar6;
  if ((param_2 & 0xf00) == 0 && uVar2 != uVar1) {
    uVar4 = 3;
  }
  if (uVar1 == 0xf) {
    FUN_00190100(param_1,0xb);
    if (uVar2 != 0xf) goto LAB_0019adcc;
LAB_0019ae9c:
    uVar6 = 1;
    uVar5 = 0xb;
    FUN_00190100(param_1,0xb);
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)uVar1 * 2));
    uVar6 = uVar4;
    if (uVar2 == 0xf) goto LAB_0019ae9c;
LAB_0019adcc:
    uVar5 = *(undefined2 *)(&DAT_0022f720 + (ulong)uVar2 * 2);
    FUN_00190100(param_1,uVar5);
  }
  FUN_00190100(param_1,uVar5);
  uVar1 = (param_2 & 0x800000) >> 0x17;
  if ((param_2 & 0xf) == 0xf) {
    FUN_00190100(param_1,0xb);
    uVar6 = 1;
    FUN_00190140(param_1,uVar1);
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 & 0xf) * 2));
    FUN_00190140(param_1,uVar1);
  }
  param_2 = param_2 >> 0x1c;
  if (param_2 == 0xf) {
LAB_0019aed4:
    uVar6 = 0;
  }
  else {
    iVar3 = FUN_0018ffb0(param_1);
    if (iVar3 == 0xc4f) {
      if (param_2 == 0xe) goto LAB_0019aed4;
      FUN_00190140(param_1,param_2);
    }
    else {
      FUN_00190140(param_1,param_2);
      if (param_2 == 0xe) {
        FUN_00190100(param_1,0);
        return uVar6;
      }
    }
    FUN_00190100(param_1,3);
  }
  return uVar6;
}

