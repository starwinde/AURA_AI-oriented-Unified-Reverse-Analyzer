
undefined8 FUN_001f5cf4(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if (param_1 == (undefined8 *)0x0 || param_2 == (undefined8 *)0x0) {
    return 0;
  }
  puVar1 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
  if (puVar1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
    *puVar1 = 0;
    puVar1[3] = 0;
    puVar1[2] = 0;
    puVar1[5] = 0;
    puVar1[4] = 0;
    puVar1[7] = 0;
    puVar1[6] = 0;
    uVar4 = *param_2;
    uVar6 = param_2[3];
    uVar5 = param_2[2];
    puVar1[1] = param_2[1];
    *puVar1 = uVar4;
    puVar1[3] = uVar6;
    puVar1[2] = uVar5;
    uVar5 = param_2[5];
    uVar4 = param_2[4];
    uVar7 = param_2[7];
    uVar6 = param_2[6];
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[5] = uVar5;
    puVar1[4] = uVar4;
    puVar1[7] = uVar7;
    puVar1[6] = uVar6;
    *(uint *)(puVar1 + 3) = *(uint *)(puVar1 + 3) | 0x100;
    puVar1[7] = 0;
    if (param_1 != puVar1) {
      lVar2 = param_1[2];
      if (lVar2 != 0) {
        puVar3 = *(undefined8 **)(lVar2 + 8);
        if (puVar3 != (undefined8 *)0x0) {
          *puVar3 = puVar1;
          puVar1[1] = puVar3;
          *(undefined8 **)(lVar2 + 8) = puVar1;
        }
        return 1;
      }
      param_1[2] = puVar1;
      *puVar1 = 0;
      puVar1[1] = puVar1;
      return 1;
    }
  }
  return 0;
}

