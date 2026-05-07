
undefined8 FUN_00190bd0(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  uVar4 = (**(code **)PTR_PTR_005ffed0)(0x58);
  FUN_001dbf50();
  *(undefined8 *)(param_1 + 0x48) = 0;
  puVar2 = PTR_DAT_005ffee8;
  puVar1 = PTR_DAT_005ffeb8;
  *(undefined4 *)(param_1 + 0x68) = 1;
  puVar3 = PTR_FUN_005fffc8;
  if (*(int *)(param_1 + 4) == 8) {
    puVar1 = puVar2;
  }
  *(undefined **)(param_1 + 0x18) = PTR_FUN_005fff20;
  puVar2 = PTR_FUN_005fff08;
  *(undefined **)(param_1 + 0x28) = puVar3;
  puVar3 = PTR_FUN_005ffe78;
  *(undefined **)(param_1 + 8) = puVar2;
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  puVar2 = PTR_FUN_005ffe60;
  *(undefined **)(param_1 + 0x30) = puVar3;
  *(undefined **)(param_1 + 0x38) = puVar2;
  *(undefined **)(param_1 + 0x40) = PTR_FUN_005fff28;
  puVar2 = PTR_FUN_005fff58;
  *(undefined **)(param_1 + 0xa0) = puVar1;
  *(undefined **)(param_1 + 0xa8) = puVar2;
  return 0;
}

