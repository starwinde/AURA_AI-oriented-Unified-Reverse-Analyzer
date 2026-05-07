
undefined4 FUN_001583d0(long param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = 0;
    if (param_2 < *(uint *)(param_1 + 0x18)) {
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)param_2 * 0x10 + 4);
    }
    return uVar1;
  }
  return 0;
}

