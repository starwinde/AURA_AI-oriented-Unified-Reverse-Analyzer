
undefined8 FUN_00196ad0(undefined8 param_1,ulong param_2)

{
  uint uVar1;
  uint uVar2;
  
  FUN_00190100(param_1,*(undefined2 *)(&DAT_0022f720 + (param_2 >> 9 & 0x7fffff) * 2));
  if ((param_2 & 0x1ff) != 0) {
    uVar1 = (uint)param_2 & 0xff;
    uVar2 = -uVar1;
    if ((param_2 & 0x100) != 0) {
      uVar2 = uVar1;
    }
    FUN_00190140(param_1,(long)(int)(uVar2 << 2));
    return 3;
  }
  FUN_00190140(param_1,0xffffffff80000000);
  return 3;
}

