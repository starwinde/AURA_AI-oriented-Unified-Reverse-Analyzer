
undefined8 FUN_00197370(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  
  uVar4 = param_2 >> 0x1c & 0xf;
  uVar1 = (uint)param_2 & 0xffffff;
  iVar3 = (int)uVar4;
  if (iVar3 == 0xf) {
    FUN_0018ff90(param_1,0x22c);
    FUN_00190140(param_1,(long)((ulong)(((uint)(param_2 >> 0x18) & 1) << 1 | uVar1 << 2) << 0x26) >>
                         0x26);
  }
  else {
    FUN_00190140(param_1,-(ulong)(uVar1 >> 0x17) & 0xfffffffffc000000 | (ulong)uVar1 << 2);
    iVar2 = FUN_0018ffb0(param_1);
    if (iVar2 == 0xc4f) {
      if (iVar3 == 0xe) {
        return 0;
      }
      FUN_00190140(param_1,uVar4);
    }
    else {
      FUN_00190140(param_1,uVar4);
      if (iVar3 == 0xe) {
        FUN_00190100(param_1,0);
        return 3;
      }
    }
    FUN_00190100(param_1,3);
  }
  return 3;
}

