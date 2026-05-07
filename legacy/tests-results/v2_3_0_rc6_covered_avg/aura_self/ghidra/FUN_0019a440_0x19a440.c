
undefined8 FUN_0019a440(undefined8 param_1,uint param_2)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = *(undefined2 *)
           (&DAT_0022f4e0 + (ulong)(param_2 >> 0xc & 0xf | (param_2 & 0x400000) >> 0x12) * 2);
  FUN_00190100(param_1,uVar1);
  if ((param_2 >> 6 & 1) != 0) {
    FUN_00190100(param_1,uVar1);
  }
  uVar2 = param_2 >> 0x10 & 0xf | (param_2 & 0x80) >> 3;
  iVar3 = FUN_0018ffb0(param_1);
  if ((iVar3 == 0xa70) || (iVar3 == 0xa76)) {
    if (uVar2 == 0x1f) {
      return 0;
    }
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f230 + (ulong)uVar2 * 2));
  }
  else {
    FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f4e0 + (ulong)uVar2 * 2));
  }
  FUN_00190100(param_1,*(undefined2 *)
                        (&DAT_0022f4e0 + (ulong)(param_2 & 0xf | (param_2 & 0x20) >> 1) * 2));
  return 3;
}

