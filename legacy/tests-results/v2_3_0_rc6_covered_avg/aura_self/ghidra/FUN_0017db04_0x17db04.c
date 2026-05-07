
void FUN_0017db04(undefined8 *param_1)

{
  long lVar1;
  long *plVar2;
  uint uVar3;
  long lVar4;
  
  if (param_1 == (undefined8 *)0x0) {
    return;
  }
  plVar2 = (long *)*param_1;
  if (plVar2 != (long *)0x0) {
    if ((int)plVar2[1] != 0) {
      lVar4 = 0;
      uVar3 = 0;
      do {
        uVar3 = uVar3 + 1;
        lVar1 = *plVar2 + lVar4;
        lVar4 = lVar4 + 0x28;
        free(*(void **)(lVar1 + 8));
        plVar2 = (long *)*param_1;
      } while (uVar3 < *(uint *)(plVar2 + 1));
    }
    free((void *)*plVar2);
    free((void *)*param_1);
    *param_1 = 0;
  }
  return;
}

