
undefined8 FUN_00158334(long *param_1,uint param_2,uint param_3)

{
  long lVar1;
  
  if (((param_1 != (long *)0x0) && (param_2 < *(uint *)(param_1 + 1))) &&
     (lVar1 = *param_1 + (ulong)param_2 * 0x60, param_3 < *(uint *)(lVar1 + 0x10))) {
    return *(undefined8 *)(*(long *)(lVar1 + 8) + (ulong)param_3 * 0x18);
  }
  return 0xffffffffffffffff;
}

