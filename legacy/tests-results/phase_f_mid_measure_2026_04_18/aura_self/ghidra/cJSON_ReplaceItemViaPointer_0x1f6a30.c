
undefined8 cJSON_ReplaceItemViaPointer(long param_1,long *param_2,long *param_3)

{
  undefined8 *puVar1;
  long *plVar2;
  long lVar3;
  
  if ((param_1 == 0) || (plVar2 = *(long **)(param_1 + 0x10), plVar2 == (long *)0x0)) {
    return 0;
  }
  if (param_3 == (long *)0x0 || param_2 == (long *)0x0) {
    return 0;
  }
  if (param_3 == param_2) {
    return 1;
  }
  lVar3 = *param_2;
  param_3[1] = param_2[1];
  *param_3 = lVar3;
  if (lVar3 == 0) {
    if (plVar2 == param_2) goto LAB_001f6ab8;
    puVar1 = (undefined8 *)param_3[1];
    if (puVar1 != (undefined8 *)0x0) goto LAB_001f6a84;
  }
  else {
    *(long **)(lVar3 + 8) = param_3;
    if (plVar2 == param_2) {
LAB_001f6ab8:
      plVar2 = param_3;
      if ((long *)param_2[1] != param_2) {
        plVar2 = (long *)param_3[1];
      }
      param_3[1] = (long)plVar2;
      *(long **)(param_1 + 0x10) = param_3;
      *param_2 = 0;
      param_2[1] = 0;
      cJSON_Delete(param_2);
      return 1;
    }
    puVar1 = (undefined8 *)param_3[1];
    if (puVar1 == (undefined8 *)0x0) goto LAB_001f6a90;
LAB_001f6a84:
    *puVar1 = param_3;
    if (*param_3 != 0) goto LAB_001f6a90;
  }
  plVar2[1] = (long)param_3;
LAB_001f6a90:
  *param_2 = 0;
  param_2[1] = 0;
  cJSON_Delete(param_2);
  return 1;
}

