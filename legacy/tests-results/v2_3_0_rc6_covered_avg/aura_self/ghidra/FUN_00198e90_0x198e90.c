
undefined8 FUN_00198e90(undefined8 param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined2 uVar3;
  ulong uVar4;
  undefined8 uVar5;
  
  uVar4 = (ulong)(param_2 >> 0xc) & 0xf;
  iVar2 = FUN_0018ffb0();
  if (iVar2 == 0x2ab) {
    if ((int)uVar4 != 0xf) {
      uVar3 = *(undefined2 *)(&DAT_0022f720 + uVar4 * 2);
      FUN_00190100(param_1,uVar3);
      goto LAB_00198ed0;
    }
    FUN_00190100(param_1,0xb);
  }
  else if ((int)uVar4 != 0xf) {
    uVar3 = *(undefined2 *)(&DAT_0022f720 + uVar4 * 2);
LAB_00198ed0:
    uVar5 = 3;
    FUN_00190100(param_1,uVar3);
    goto LAB_00198ee0;
  }
  uVar5 = 1;
  FUN_00190100(param_1,0xb);
LAB_00198ee0:
  uVar1 = param_2 >> 0x1c;
  FUN_00190140(param_1,param_2 & 0xfff | (param_2 & 0xf0000) >> 4);
  if (uVar1 == 0xf) {
    return 0;
  }
  iVar2 = FUN_0018ffb0(param_1);
  if (iVar2 == 0xc4f) {
    if (uVar1 == 0xe) {
      return 0;
    }
    FUN_00190140(param_1,uVar1);
  }
  else {
    FUN_00190140(param_1,uVar1);
    if (uVar1 == 0xe) {
      FUN_00190100(param_1,0);
      return uVar5;
    }
  }
  FUN_00190100(param_1,3);
  return uVar5;
}

