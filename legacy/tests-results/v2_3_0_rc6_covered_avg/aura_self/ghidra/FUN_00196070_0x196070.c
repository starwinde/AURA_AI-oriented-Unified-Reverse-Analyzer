
undefined8 FUN_00196070(undefined8 param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  
  uVar2 = param_2 & 0xfff;
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (ulong)(param_2 >> 0xd) * 2));
  if (((param_2 >> 0xc & 1) == 0) && (bVar1 = uVar2 == 0, uVar2 = -uVar2, bVar1)) {
    uVar2 = 0x80000000;
  }
  FUN_00190140(param_1,uVar2);
  return 3;
}

