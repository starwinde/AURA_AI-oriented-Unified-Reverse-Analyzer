
void cJSON_DeleteItemFromObject(long param_1,undefined8 param_2)

{
  long *plVar1;
  long *plVar2;
  long lVar3;
  long *plVar4;
  
  plVar1 = (long *)get_object_item(param_1,param_2,0);
  if (param_1 != 0 && plVar1 != (long *)0x0) {
    plVar4 = *(long **)(param_1 + 0x10);
    if (plVar1 == plVar4) {
      lVar3 = *plVar1;
      if (lVar3 != 0) {
        *(long *)(lVar3 + 8) = plVar1[1];
      }
      *(long *)(param_1 + 0x10) = lVar3;
    }
    else {
      plVar2 = (long *)plVar1[1];
      if (plVar2 == (long *)0x0) goto LAB_001f6850;
      lVar3 = *plVar1;
      *plVar2 = lVar3;
      if (lVar3 == 0) {
        plVar4[1] = (long)plVar2;
      }
      else {
        *(long **)(lVar3 + 8) = plVar2;
      }
    }
    *plVar1 = 0;
    plVar1[1] = 0;
    cJSON_Delete();
    return;
  }
LAB_001f6850:
  cJSON_Delete(0);
  return;
}

