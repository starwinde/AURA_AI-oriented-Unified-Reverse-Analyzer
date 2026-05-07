
void cJSON_DeleteItemFromArray(long param_1,int param_2)

{
  long *plVar1;
  long lVar2;
  long *plVar3;
  long *plVar4;
  
  if ((param_2 < 0) || (lVar2 = (long)param_2, param_1 == 0)) {
LAB_001f5ac8:
    cJSON_Delete(0);
    return;
  }
  plVar4 = *(long **)(param_1 + 0x10);
  plVar1 = plVar4;
  if (plVar4 == (long *)0x0 || lVar2 == 0) {
    if (plVar4 == (long *)0x0) goto LAB_001f5ac8;
  }
  else {
    do {
      plVar1 = (long *)*plVar1;
      lVar2 = lVar2 + -1;
    } while (plVar1 != (long *)0x0 && lVar2 != 0);
    if (plVar1 == (long *)0x0) goto LAB_001f5ac4;
    if (plVar4 != plVar1) {
      plVar3 = (long *)plVar1[1];
      if (plVar3 == (long *)0x0) goto LAB_001f5ac8;
      lVar2 = *plVar1;
      *plVar3 = lVar2;
      if (lVar2 == 0) {
        plVar4[1] = (long)plVar3;
        *plVar1 = 0;
        plVar1[1] = 0;
      }
      else {
        *(long **)(lVar2 + 8) = plVar3;
        *plVar1 = 0;
        plVar1[1] = 0;
      }
      goto LAB_001f5ac4;
    }
  }
  lVar2 = *plVar1;
  if (lVar2 != 0) {
    *(long *)(lVar2 + 8) = plVar1[1];
  }
  *(long *)(param_1 + 0x10) = lVar2;
  *plVar1 = 0;
  plVar1[1] = 0;
LAB_001f5ac4:
  cJSON_Delete();
  return;
}

