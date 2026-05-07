
undefined8 * FUN_001f7910(int *param_1,int param_2)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  ulong uVar6;
  
  if ((-1 < param_2 && param_1 != (int *)0x0) &&
     (puVar3 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40), puVar3 != (undefined8 *)0x0)) {
    puVar3[1] = 0;
    *puVar3 = 0;
    puVar3[3] = 0;
    puVar3[2] = 0;
    *(undefined4 *)(puVar3 + 3) = 0x20;
    puVar3[5] = 0;
    puVar3[4] = 0;
    puVar3[7] = 0;
    puVar3[6] = 0;
    if (param_2 == 0) {
      return puVar3;
    }
    uVar6 = 0;
    iVar1 = *param_1;
    puVar4 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
    puVar2 = (undefined8 *)0x0;
    while (puVar4 != (undefined8 *)0x0) {
      puVar4[1] = 0;
      *puVar4 = 0;
      puVar4[3] = 0;
      puVar4[2] = 0;
      puVar4[5] = 0;
      puVar4[4] = 0;
      puVar4[7] = 0;
      puVar4[6] = 0;
      *(undefined4 *)(puVar4 + 3) = 8;
      *(int *)(puVar4 + 5) = iVar1;
      puVar4[6] = (double)iVar1;
      if (uVar6 == 0) {
        puVar3[2] = puVar4;
        uVar6 = 1;
        if ((long)param_2 == 1) {
          puVar4[1] = puVar4;
          return puVar3;
        }
      }
      else {
        *puVar2 = puVar4;
        uVar6 = uVar6 + 1;
        puVar4[1] = puVar2;
        if ((ulong)(long)param_2 <= uVar6) {
          if (puVar3[2] != 0) {
            *(undefined8 **)(puVar3[2] + 8) = puVar4;
            return puVar3;
          }
          return puVar3;
        }
      }
      iVar1 = param_1[uVar6];
      puVar5 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
      puVar2 = puVar4;
      puVar4 = puVar5;
    }
    FUN_001f43e0(puVar3);
  }
  return (undefined8 *)0x0;
}

