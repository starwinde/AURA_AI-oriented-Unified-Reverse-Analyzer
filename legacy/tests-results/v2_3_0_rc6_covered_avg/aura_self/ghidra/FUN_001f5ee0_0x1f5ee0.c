
undefined8 * FUN_001f5ee0(undefined8 *param_1,char *param_2)

{
  uint uVar1;
  undefined8 *puVar2;
  size_t sVar3;
  void *__dest;
  long lVar4;
  undefined8 *puVar5;
  
  puVar2 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
  if (puVar2 != (undefined8 *)0x0) {
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2[3] = 0;
    puVar2[2] = 0;
    *(undefined4 *)(puVar2 + 3) = 4;
    puVar2[5] = 0;
    puVar2[4] = 0;
    puVar2[7] = 0;
    puVar2[6] = 0;
    if ((param_2 != (char *)0x0 && param_1 != (undefined8 *)0x0) && (param_1 != puVar2)) {
      sVar3 = strlen(param_2);
      __dest = (void *)(*(code *)PTR_malloc_00600598)(sVar3 + 1);
      if (__dest != (void *)0x0) {
        memcpy(__dest,param_2,sVar3 + 1);
        uVar1 = *(uint *)(puVar2 + 3);
        if (((uVar1 >> 9 & 1) == 0) && (puVar2[7] != 0)) {
          (*(code *)PTR_free_006005a0)();
        }
        lVar4 = param_1[2];
        *(uint *)(puVar2 + 3) = uVar1 & 0xfffffdff;
        puVar2[7] = __dest;
        if (lVar4 != 0) {
          puVar5 = *(undefined8 **)(lVar4 + 8);
          if (puVar5 == (undefined8 *)0x0) {
            return puVar2;
          }
          *puVar5 = puVar2;
          puVar2[1] = puVar5;
          *(undefined8 **)(lVar4 + 8) = puVar2;
          return puVar2;
        }
        param_1[2] = puVar2;
        *puVar2 = 0;
        puVar2[1] = puVar2;
        return puVar2;
      }
    }
  }
  FUN_001f43e0(puVar2);
  return (undefined8 *)0x0;
}

