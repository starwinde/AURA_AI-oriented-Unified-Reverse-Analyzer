
void FUN_001f43e0(long *param_1)

{
  uint uVar1;
  long *plVar2;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  do {
    uVar1 = *(uint *)(param_1 + 3);
    plVar2 = (long *)*param_1;
    if ((uVar1 >> 8 & 1) == 0) {
      if (param_1[2] != 0) {
        FUN_001f43e0();
        uVar1 = *(uint *)(param_1 + 3);
        if ((uVar1 >> 8 & 1) != 0) goto LAB_001f443c;
      }
      if (param_1[4] != 0) {
        (*(code *)PTR_free_006005a0)();
        param_1[4] = 0;
        uVar1 = *(uint *)(param_1 + 3);
      }
    }
LAB_001f443c:
    if (((uVar1 >> 9 & 1) == 0) && (param_1[7] != 0)) {
      (*(code *)PTR_free_006005a0)();
      param_1[7] = 0;
    }
    (*(code *)PTR_free_006005a0)(param_1);
    param_1 = plVar2;
    if (plVar2 == (long *)0x0) {
      return;
    }
  } while( true );
}

