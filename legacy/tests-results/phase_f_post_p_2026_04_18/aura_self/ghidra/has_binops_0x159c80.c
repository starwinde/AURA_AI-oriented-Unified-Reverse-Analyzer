
undefined8 has_binops(long *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  if (*(uint *)(param_1 + 1) != 0) {
    puVar4 = (undefined8 *)(*param_1 + 8);
    puVar5 = puVar4 + (ulong)*(uint *)(param_1 + 1) * 10;
    do {
      if (*(uint *)(puVar4 + 1) != 0) {
        piVar2 = (int *)*puVar4;
        piVar3 = piVar2 + (ulong)*(uint *)(puVar4 + 1) * 0x22;
        do {
          iVar1 = *piVar2;
          piVar2 = piVar2 + 0x22;
          if (iVar1 - 2U < 9) {
            return 1;
          }
        } while (piVar3 != piVar2);
      }
      puVar4 = puVar4 + 10;
    } while (puVar4 != puVar5);
  }
  return 0;
}

