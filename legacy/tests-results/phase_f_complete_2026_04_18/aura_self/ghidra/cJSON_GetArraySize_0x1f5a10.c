
long cJSON_GetArraySize(long param_1)

{
  long lVar1;
  long *plVar2;
  
  if ((param_1 != 0) && (plVar2 = *(long **)(param_1 + 0x10), plVar2 != (long *)0x0)) {
    lVar1 = 0;
    do {
      plVar2 = (long *)*plVar2;
      lVar1 = lVar1 + 1;
    } while (plVar2 != (long *)0x0);
    return lVar1;
  }
  return 0;
}

