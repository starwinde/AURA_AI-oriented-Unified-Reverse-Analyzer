
undefined8 FUN_0015a3b0(uint param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (DAT_006005f0 != (long *)0x0) {
    if (*(uint *)(DAT_006005f0 + 1) <= param_1) {
      return 0;
    }
    uVar1 = *(undefined8 *)(*DAT_006005f0 + (ulong)param_1 * 8);
  }
  return uVar1;
}

