
void FUN_00166c30(long *param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if ((int)param_1[1] != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      uVar2 = uVar2 + 1;
      lVar1 = *param_1 + lVar3;
      lVar3 = lVar3 + 0x18;
      free(*(void **)(lVar1 + 0x10));
    } while (uVar2 < *(uint *)(param_1 + 1));
  }
  free((void *)*param_1);
  free(param_1);
  return;
}

