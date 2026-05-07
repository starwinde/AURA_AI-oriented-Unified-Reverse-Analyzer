
undefined4 FUN_00158494(long param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_1 != 0) {
    uVar1 = 0xffffffff;
    if (param_2 < *(uint *)(param_1 + 0x18)) {
      uVar1 = *(undefined4 *)(*(long *)(param_1 + 0x10) + (ulong)param_2 * 0x10);
    }
    return uVar1;
  }
  return 0xffffffff;
}

