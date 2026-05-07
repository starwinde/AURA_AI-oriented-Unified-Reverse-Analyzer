
undefined8 FUN_001be010(undefined8 param_1,ulong param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_0028e660 + (param_2 & 0xffffffff) * 4);
  if (iVar1 == 9) {
    iVar1 = 5;
  }
  FUN_00190100(param_1,iVar1);
  return 3;
}

