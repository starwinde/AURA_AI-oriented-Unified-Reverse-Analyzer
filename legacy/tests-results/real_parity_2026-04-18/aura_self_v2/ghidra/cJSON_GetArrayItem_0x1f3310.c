
long * cJSON_GetArrayItem(long param_1,int param_2)

{
  long *plVar1;
  long lVar2;
  
  if ((-1 < param_2) && (lVar2 = (long)param_2, param_1 != 0)) {
    plVar1 = *(long **)(param_1 + 0x10);
    if (plVar1 != (long *)0x0 && lVar2 != 0) {
      do {
        plVar1 = (long *)*plVar1;
        lVar2 = lVar2 + -1;
      } while (plVar1 != (long *)0x0 && lVar2 != 0);
    }
    return plVar1;
  }
  return (long *)0x0;
}

