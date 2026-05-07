
long FUN_001f5a90(long param_1,char *param_2)

{
  int iVar1;
  long *plVar2;
  
  if (param_1 != 0 && param_2 != (char *)0x0) {
    for (plVar2 = *(long **)(param_1 + 0x10);
        (plVar2 != (long *)0x0 && ((char *)plVar2[7] != (char *)0x0)); plVar2 = (long *)*plVar2) {
      iVar1 = strcmp(param_2,(char *)plVar2[7]);
      if (iVar1 == 0) {
        return (long)plVar2;
      }
    }
  }
  return 0;
}

