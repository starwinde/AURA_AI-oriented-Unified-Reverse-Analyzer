
undefined8 FUN_001f2208(void *param_1,ulong param_2)

{
  size_t __n;
  undefined8 uVar1;
  ulong local_20;
  void *local_10;
  
  local_20 = param_2;
  local_10 = param_1;
  if (param_1 == (void *)0x0) {
    uVar1 = 0x80100004;
  }
  else {
    for (; local_20 != 0; local_20 = local_20 - __n) {
      __n = local_20;
      if (9 < local_20) {
        __n = 9;
      }
      memcpy(local_10,&UNK_00571578 + (__n - 1) * 9,__n);
      local_10 = (void *)((long)local_10 + __n);
    }
    uVar1 = 0x100000;
  }
  return uVar1;
}

