
long * FUN_00166470(long param_1,long param_2,long param_3)

{
  long *plVar1;
  
  if (param_1 != 0 && param_2 != 0) {
    plVar1 = calloc(1,0x18);
    if (plVar1 != (long *)0x0) {
      *plVar1 = param_1;
      plVar1[1] = param_2;
      plVar1[2] = param_3;
    }
    return plVar1;
  }
  return (long *)0x0;
}

