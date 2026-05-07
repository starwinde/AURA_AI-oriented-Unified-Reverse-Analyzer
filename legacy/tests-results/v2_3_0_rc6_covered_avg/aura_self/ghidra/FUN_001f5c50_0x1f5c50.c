
undefined8 FUN_001f5c50(undefined8 *param_1,long param_2,undefined8 *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 *puVar4;
  
  if (param_1 != (undefined8 *)0x0 && param_2 != 0) {
    uVar2 = 0;
    if (param_3 != (undefined8 *)0x0 && param_1 != param_3) {
      uVar1 = *(uint *)(param_3 + 3);
      if (((uVar1 >> 9 & 1) == 0) && (param_3[7] != 0)) {
        (*(code *)PTR_free_006005a0)();
      }
      lVar3 = param_1[2];
      *(uint *)(param_3 + 3) = uVar1 | 0x200;
      param_3[7] = param_2;
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
      uVar2 = 1;
    }
    return uVar2;
  }
  return 0;
}

