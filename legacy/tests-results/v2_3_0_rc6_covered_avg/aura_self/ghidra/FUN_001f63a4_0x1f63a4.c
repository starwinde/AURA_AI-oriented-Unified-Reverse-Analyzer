
undefined8 * FUN_001f63a4(double param_1,undefined8 *param_2,char *param_3)

{
  uint uVar1;
  int iVar2;
  undefined8 *puVar3;
  size_t sVar4;
  void *__dest;
  long lVar5;
  undefined8 *puVar6;
  
  puVar3 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
  if (puVar3 != (undefined8 *)0x0) {
    iVar2 = 0x7fffffff;
    puVar3[1] = 0;
    *puVar3 = 0;
    puVar3[3] = 0;
    puVar3[2] = 0;
    puVar3[5] = 0;
    puVar3[4] = 0;
    puVar3[7] = 0;
    puVar3[6] = 0;
    if ((param_1 < 2147483647.0) && (iVar2 = -0x80000000, -2147483648.0 < param_1)) {
      iVar2 = (int)param_1;
    }
    *(undefined4 *)(puVar3 + 3) = 8;
    *(int *)(puVar3 + 5) = iVar2;
    puVar3[6] = param_1;
    if ((param_2 != (undefined8 *)0x0 && param_3 != (char *)0x0) && (param_2 != puVar3)) {
      sVar4 = strlen(param_3);
      __dest = (void *)(*(code *)PTR_malloc_00600598)(sVar4 + 1);
      if (__dest != (void *)0x0) {
        memcpy(__dest,param_3,sVar4 + 1);
        uVar1 = *(uint *)(puVar3 + 3);
        if (((uVar1 >> 9 & 1) == 0) && (puVar3[7] != 0)) {
          (*(code *)PTR_free_006005a0)();
        }
        lVar5 = param_2[2];
        *(uint *)(puVar3 + 3) = uVar1 & 0xfffffdff;
        puVar3[7] = __dest;
        if (lVar5 != 0) {
          puVar6 = *(undefined8 **)(lVar5 + 8);
          if (puVar6 == (undefined8 *)0x0) {
            return puVar3;
          }
          *puVar6 = puVar3;
          puVar3[1] = puVar6;
          *(undefined8 **)(lVar5 + 8) = puVar3;
          return puVar3;
        }
        param_2[2] = puVar3;
        *puVar3 = 0;
        puVar3[1] = puVar3;
        return puVar3;
      }
    }
  }
  FUN_001f43e0(puVar3);
  return (undefined8 *)0x0;
}

