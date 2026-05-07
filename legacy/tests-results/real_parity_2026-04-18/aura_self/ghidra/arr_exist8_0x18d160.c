
undefined8 arr_exist8(long param_1,byte param_2,uint param_3)

{
  byte *pbVar1;
  long lVar2;
  
  if (param_2 != 0) {
    lVar2 = 0;
    do {
      pbVar1 = (byte *)(param_1 + lVar2);
      lVar2 = lVar2 + 1;
      if (*pbVar1 == param_3) {
        return 1;
      }
    } while ((int)lVar2 < (int)(uint)param_2);
  }
  return 0;
}

