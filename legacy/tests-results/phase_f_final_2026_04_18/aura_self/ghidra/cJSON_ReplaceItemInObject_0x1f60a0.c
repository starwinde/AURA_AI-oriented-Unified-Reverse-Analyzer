
undefined8 cJSON_ReplaceItemInObject(long param_1,char *param_2,long *param_3)

{
  size_t sVar1;
  void *__dest;
  long *plVar2;
  long *plVar3;
  undefined8 *puVar4;
  long *plVar5;
  long lVar6;
  
  if (param_3 == (long *)0x0 || param_2 == (char *)0x0) {
    return 0;
  }
  if (((*(uint *)(param_3 + 3) >> 9 & 1) == 0) && (param_3[7] != 0)) {
    (*(code *)PTR_free_006005a0)();
  }
  sVar1 = strlen(param_2);
  __dest = (void *)(*(code *)global_hooks)(sVar1 + 1);
  if (__dest == (void *)0x0) {
    param_3[7] = 0;
    return 0;
  }
  memcpy(__dest,param_2,sVar1 + 1);
  param_3[7] = (long)__dest;
  *(uint *)(param_3 + 3) = *(uint *)(param_3 + 3) & 0xfffffdff;
  plVar2 = (long *)get_object_item(param_1,param_2,0);
  if (param_1 == 0) {
    return 0;
  }
  plVar3 = *(long **)(param_1 + 0x10);
  if (plVar3 == (long *)0x0) {
    return 0;
  }
  if (plVar2 == (long *)0x0) {
    return 0;
  }
  if (param_3 == plVar2) {
    return 1;
  }
  lVar6 = *plVar2;
  param_3[1] = plVar2[1];
  *param_3 = lVar6;
  if (lVar6 == 0) {
    if (plVar2 == plVar3) goto LAB_001f61b0;
    puVar4 = (undefined8 *)param_3[1];
    if (puVar4 != (undefined8 *)0x0) goto LAB_001f6174;
  }
  else {
    *(long **)(lVar6 + 8) = param_3;
    if (plVar2 == plVar3) {
LAB_001f61b0:
      plVar5 = param_3;
      if (plVar3 != (long *)plVar3[1]) {
        plVar5 = (long *)param_3[1];
      }
      param_3[1] = (long)plVar5;
      *(long **)(param_1 + 0x10) = param_3;
      goto LAB_001f6180;
    }
    puVar4 = (undefined8 *)param_3[1];
    if (puVar4 == (undefined8 *)0x0) goto LAB_001f6180;
LAB_001f6174:
    *puVar4 = param_3;
    if (*param_3 != 0) goto LAB_001f6180;
  }
  plVar3[1] = (long)param_3;
LAB_001f6180:
  *plVar2 = 0;
  plVar2[1] = 0;
  cJSON_Delete();
  return 1;
}

