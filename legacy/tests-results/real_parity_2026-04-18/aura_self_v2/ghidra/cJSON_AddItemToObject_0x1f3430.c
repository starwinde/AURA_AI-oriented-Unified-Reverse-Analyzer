
undefined8 cJSON_AddItemToObject(undefined8 *param_1,char *param_2,undefined8 *param_3)

{
  uint uVar1;
  size_t sVar2;
  void *__dest;
  long lVar3;
  undefined8 *puVar4;
  
  if (param_1 == (undefined8 *)0x0 || param_2 == (char *)0x0) {
    return 0;
  }
  if (param_3 != (undefined8 *)0x0 && param_1 != param_3) {
    sVar2 = strlen(param_2);
    __dest = (void *)(*(code *)global_hooks)(sVar2 + 1);
    if (__dest != (void *)0x0) {
      memcpy(__dest,param_2,sVar2 + 1);
      uVar1 = *(uint *)(param_3 + 3);
      if (((uVar1 >> 9 & 1) == 0) && (param_3[7] != 0)) {
        (*(code *)PTR_free_006005a0)();
      }
      lVar3 = param_1[2];
      *(uint *)(param_3 + 3) = uVar1 & 0xfffffdff;
      param_3[7] = __dest;
      if (lVar3 == 0) {
        param_1[2] = param_3;
        *param_3 = 0;
        param_3[1] = param_3;
      }
      else {
        puVar4 = *(undefined8 **)(lVar3 + 8);
        if (puVar4 != (undefined8 *)0x0) {
          *puVar4 = param_3;
          param_3[1] = puVar4;
          *(undefined8 **)(lVar3 + 8) = param_3;
        }
      }
      return 1;
    }
  }
  return 0;
}

