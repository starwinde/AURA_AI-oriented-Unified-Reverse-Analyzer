
undefined8 cJSON_AddItemToArray(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  long lVar2;
  
  if ((param_1 != (undefined8 *)0x0 && param_1 != param_2) && param_2 != (undefined8 *)0x0) {
    lVar2 = param_1[2];
    if (lVar2 == 0) {
      param_1[2] = param_2;
      *param_2 = 0;
      param_2[1] = param_2;
    }
    else {
      puVar1 = *(undefined8 **)(lVar2 + 8);
      if (puVar1 != (undefined8 *)0x0) {
        *puVar1 = param_2;
        param_2[1] = puVar1;
        *(undefined8 **)(lVar2 + 8) = param_2;
      }
    }
    return 1;
  }
  return 0;
}

