
undefined4 dfg_get_use(long *param_1,uint param_2,uint param_3)

{
  long lVar1;
  undefined4 uVar2;
  
  if (param_1 != (long *)0x0) {
    uVar2 = 0;
    if ((param_2 < *(uint *)(param_1 + 1)) &&
       (lVar1 = *param_1 + (ulong)param_2 * 0x20, param_3 < *(uint *)(lVar1 + 0x18))) {
      uVar2 = *(undefined4 *)(*(long *)(lVar1 + 0x10) + (ulong)param_3 * 8 + 4);
    }
    return uVar2;
  }
  return 0;
}

