
undefined8 * cJSON_CreateDoubleArray(double *param_1,int param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  int iVar5;
  ulong uVar6;
  double dVar7;
  
  if ((-1 < param_2 && param_1 != (double *)0x0) &&
     (puVar2 = (undefined8 *)(*(code *)global_hooks)(0x40), puVar2 != (undefined8 *)0x0)) {
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2[3] = 0;
    puVar2[2] = 0;
    *(undefined4 *)(puVar2 + 3) = 0x20;
    puVar2[5] = 0;
    puVar2[4] = 0;
    puVar2[7] = 0;
    puVar2[6] = 0;
    if (param_2 == 0) {
      return puVar2;
    }
    uVar6 = 0;
    dVar7 = *param_1;
    puVar3 = (undefined8 *)(*(code *)global_hooks)(0x40);
    puVar1 = (undefined8 *)0x0;
    while (puVar3 != (undefined8 *)0x0) {
      iVar5 = 0x7fffffff;
      puVar3[1] = 0;
      *puVar3 = 0;
      puVar3[3] = 0;
      puVar3[2] = 0;
      puVar3[5] = 0;
      puVar3[4] = 0;
      puVar3[7] = 0;
      puVar3[6] = 0;
      if ((dVar7 < 2147483647.0) && (iVar5 = -0x80000000, -2147483648.0 < dVar7)) {
        iVar5 = (int)dVar7;
      }
      *(undefined4 *)(puVar3 + 3) = 8;
      *(int *)(puVar3 + 5) = iVar5;
      puVar3[6] = dVar7;
      if (uVar6 == 0) {
        puVar2[2] = puVar3;
        uVar6 = 1;
        if ((long)param_2 == 1) {
          puVar3[1] = puVar3;
          return puVar2;
        }
      }
      else {
        *puVar1 = puVar3;
        uVar6 = uVar6 + 1;
        puVar3[1] = puVar1;
        if ((ulong)(long)param_2 <= uVar6) {
          if (puVar2[2] != 0) {
            *(undefined8 **)(puVar2[2] + 8) = puVar3;
            return puVar2;
          }
          return puVar2;
        }
      }
      dVar7 = param_1[uVar6];
      puVar4 = (undefined8 *)(*(code *)global_hooks)(0x40);
      puVar1 = puVar3;
      puVar3 = puVar4;
    }
    cJSON_Delete(puVar2);
  }
  return (undefined8 *)0x0;
}

