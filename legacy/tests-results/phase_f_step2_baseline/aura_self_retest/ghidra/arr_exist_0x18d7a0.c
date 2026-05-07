
undefined8 arr_exist(ushort *param_1,byte param_2,uint param_3)

{
  ushort *puVar1;
  ushort uVar2;
  
  if (param_2 != 0) {
    puVar1 = param_1 + (ulong)(param_2 - 1) + 1;
    do {
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      if (uVar2 == param_3) {
        return 1;
      }
    } while (param_1 != puVar1);
  }
  return 0;
}

