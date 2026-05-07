
undefined8 cJSON_ReplaceItemInArray(long param_1,int param_2,long *param_3)

{
  undefined8 *puVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  
  if ((param_2 < 0) || (lVar2 = (long)param_2, param_1 == 0)) {
    return 0;
  }
  plVar4 = *(long **)(param_1 + 0x10);
  plVar3 = plVar4;
  if (lVar2 == 0 || plVar4 == (long *)0x0) {
    if (plVar4 == (long *)0x0) {
      return 0;
    }
  }
  else {
    do {
      plVar3 = (long *)*plVar3;
      lVar2 = lVar2 + -1;
    } while (plVar3 != (long *)0x0 && lVar2 != 0);
  }
  if (param_3 == (long *)0x0 || plVar3 == (long *)0x0) {
    return 0;
  }
  if (param_3 == plVar3) {
    return 1;
  }
  lVar2 = *plVar3;
  param_3[1] = plVar3[1];
  *param_3 = lVar2;
  if (lVar2 == 0) {
    if (plVar4 == plVar3) goto LAB_001f71c0;
    puVar1 = (undefined8 *)param_3[1];
    if (puVar1 != (undefined8 *)0x0) goto LAB_001f7170;
  }
  else {
    *(long **)(lVar2 + 8) = param_3;
    if (plVar4 == plVar3) {
LAB_001f71c0:
      plVar4 = param_3;
      if ((long *)plVar3[1] != plVar3) {
        plVar4 = (long *)param_3[1];
      }
      param_3[1] = (long)plVar4;
      *(long **)(param_1 + 0x10) = param_3;
      goto LAB_001f717c;
    }
    puVar1 = (undefined8 *)param_3[1];
    if (puVar1 == (undefined8 *)0x0) goto LAB_001f717c;
LAB_001f7170:
    *puVar1 = param_3;
    if (*param_3 != 0) goto LAB_001f717c;
  }
  plVar4[1] = (long)param_3;
LAB_001f717c:
  *plVar3 = 0;
  plVar3[1] = 0;
  cJSON_Delete(plVar3);
  return 1;
}

