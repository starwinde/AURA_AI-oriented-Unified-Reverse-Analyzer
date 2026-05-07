
long FUN_0017dac0(long *param_1,int param_2)

{
  int *piVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  
  if ((param_1 != (long *)0x0) && (*(uint *)(param_1 + 1) != 0)) {
    lVar3 = *param_1;
    lVar4 = lVar3 + (ulong)*(uint *)(param_1 + 1) * 0x28;
    do {
      piVar1 = (int *)(lVar3 + 0x1c);
      lVar2 = lVar3;
      lVar3 = lVar3 + 0x28;
      if (*piVar1 == param_2) {
        return lVar2;
      }
    } while (lVar3 != lVar4);
  }
  return 0;
}

