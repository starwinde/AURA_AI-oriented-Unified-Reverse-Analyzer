
undefined8 FUN_0017d490(long param_1,uint param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  long *plVar3;
  
  if ((param_1 != 0) && (plVar3 = *(long **)(param_1 + 8), plVar3 != (long *)0x0)) {
    if ((*(uint *)(plVar3 + 3) <= param_2) ||
       (((uVar1 = *(uint *)(plVar3[2] + (ulong)param_2 * 4), uVar1 == 0xffffffff ||
         (*(uint *)(plVar3 + 1) <= uVar1)) ||
        (piVar2 = (int *)(*plVar3 + (ulong)uVar1 * 0x60), piVar2 == (int *)0x0)))) {
      return 3;
    }
    do {
      if (*piVar2 == param_3) {
        return 2;
      }
      if (piVar2[5] == param_3) {
        return 1;
      }
      piVar2 = *(int **)(piVar2 + 0x12);
    } while (piVar2 != (int *)0x0);
  }
  return 3;
}

