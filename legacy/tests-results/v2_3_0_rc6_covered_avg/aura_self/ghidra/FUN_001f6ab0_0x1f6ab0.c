
long * FUN_001f6ab0(long param_1,long *param_2)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  
  if (param_1 == 0 || param_2 == (long *)0x0) {
    return (long *)0x0;
  }
  plVar3 = *(long **)(param_1 + 0x10);
  if (plVar3 == param_2) {
    lVar2 = *param_2;
    if (lVar2 != 0) {
      *(long *)(lVar2 + 8) = param_2[1];
    }
    *(long *)(param_1 + 0x10) = lVar2;
  }
  else {
    plVar1 = (long *)param_2[1];
    if (plVar1 == (long *)0x0) {
      return (long *)0x0;
    }
    lVar2 = *param_2;
    *plVar1 = lVar2;
    if (lVar2 == 0) {
      plVar3[1] = (long)plVar1;
    }
    else {
      *(long **)(lVar2 + 8) = plVar1;
    }
  }
  *param_2 = 0;
  param_2[1] = 0;
  return param_2;
}

