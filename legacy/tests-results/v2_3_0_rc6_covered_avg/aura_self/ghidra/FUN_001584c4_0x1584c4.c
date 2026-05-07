
undefined4 FUN_001584c4(long *param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  long lVar2;
  
  if (param_1 != (long *)0x0) {
    uVar1 = 4;
    if ((param_2 < *(uint *)(param_1 + 1)) &&
       (lVar2 = *param_1 + (ulong)param_2 * 0x60, param_3 < *(uint *)(lVar2 + 0x10))) {
      uVar1 = *(undefined4 *)(*(long *)(lVar2 + 8) + (ulong)param_3 * 0x18 + 0xc);
    }
    return uVar1;
  }
  return 4;
}

