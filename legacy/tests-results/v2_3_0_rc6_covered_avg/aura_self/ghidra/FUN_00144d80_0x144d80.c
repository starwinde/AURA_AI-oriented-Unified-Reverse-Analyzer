
long * FUN_00144d80(long *param_1)

{
  long *plVar1;
  long lVar2;
  
  if (param_1 == (long *)0x0) {
    plVar1 = (long *)0x0;
  }
  else {
    lVar2 = *param_1;
    plVar1 = (long *)0x0;
    if ((lVar2 != 0) && (plVar1 = (long *)aligned_alloc(0x40), plVar1 != (long *)0x0)) {
      plVar1[7] = 0;
      *param_1 = 0;
      plVar1[2] = 0;
      plVar1[1] = 0;
      plVar1[4] = 0;
      plVar1[3] = 0;
      plVar1[6] = 0;
      plVar1[5] = 0;
      *plVar1 = lVar2;
    }
  }
  return plVar1;
}

