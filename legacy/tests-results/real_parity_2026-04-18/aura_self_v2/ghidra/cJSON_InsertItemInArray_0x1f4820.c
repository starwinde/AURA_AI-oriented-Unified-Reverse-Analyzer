
undefined8 cJSON_InsertItemInArray(long *param_1,int param_2,long *param_3)

{
  undefined8 *puVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  
  if ((param_2 < 0 || param_3 == (long *)0x0) || (lVar2 = (long)param_2, param_1 == (long *)0x0)) {
    return 0;
  }
  plVar4 = (long *)param_1[2];
  plVar3 = plVar4;
  if (lVar2 == 0 || plVar4 == (long *)0x0) {
    if (plVar4 == (long *)0x0) {
      if (param_3 == param_1) {
        return 0;
      }
      param_1[2] = (long)param_3;
      *param_3 = 0;
      param_3[1] = (long)param_3;
      return 1;
    }
  }
  else {
    do {
      plVar3 = (long *)*plVar3;
      lVar2 = lVar2 + -1;
    } while (plVar3 != (long *)0x0 && lVar2 != 0);
    if (plVar3 == (long *)0x0) {
      if (param_3 == param_1) {
        return 0;
      }
      puVar1 = (undefined8 *)plVar4[1];
      if (puVar1 == (undefined8 *)0x0) {
        return 1;
      }
      *puVar1 = param_3;
      param_3[1] = (long)puVar1;
      plVar4[1] = (long)param_3;
      return 1;
    }
    if (plVar4 != plVar3) {
      lVar2 = plVar3[1];
      if (lVar2 != 0) {
        *param_3 = (long)plVar3;
        param_3[1] = lVar2;
        plVar3[1] = (long)param_3;
        *(long **)param_3[1] = param_3;
        return 1;
      }
      return 0;
    }
  }
  lVar2 = plVar4[1];
  *param_3 = (long)plVar4;
  param_3[1] = lVar2;
  plVar4[1] = (long)param_3;
  param_1[2] = (long)param_3;
  return 1;
}

