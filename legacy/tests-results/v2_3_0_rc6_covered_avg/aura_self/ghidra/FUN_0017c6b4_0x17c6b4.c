
undefined8 FUN_0017c6b4(long param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != 0) {
    piVar3 = *(int **)(param_1 + 8);
    if (*(uint *)(param_1 + 0x10) != 0) {
      piVar1 = piVar3 + *(uint *)(param_1 + 0x10);
      do {
        iVar2 = *piVar3;
        piVar3 = piVar3 + 1;
        if (param_2 == iVar2) {
          return 1;
        }
      } while (piVar3 != piVar1);
    }
  }
  return 0;
}

