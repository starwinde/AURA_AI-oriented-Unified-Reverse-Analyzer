
undefined4 FUN_00158400(long *param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 != (long *)0x0) {
    uVar1 = 0xffffffff;
    if (param_2 < *(uint *)(param_1 + 1)) {
      uVar1 = *(undefined4 *)(*param_1 + (ulong)param_2 * 0x60);
    }
    return uVar1;
  }
  return 0xffffffff;
}

