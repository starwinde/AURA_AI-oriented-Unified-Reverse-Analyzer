
undefined8 FUN_00190b20(long param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  uVar2 = (**(code **)PTR_PTR_005ffed0)(0x58);
  FUN_001cbb90();
  *(undefined **)(param_1 + 8) = PTR_FUN_005ffef0;
  *(undefined8 *)(param_1 + 0x10) = uVar2;
  *(undefined **)(param_1 + 0x18) = PTR_FUN_005fff38;
  *(undefined8 *)(param_1 + 0x20) = uVar2;
  puVar1 = PTR_FUN_005fff48;
  *(undefined **)(param_1 + 0x28) = PTR_FUN_005ffea0;
  *(undefined **)(param_1 + 0x30) = puVar1;
  puVar1 = PTR_FUN_005fff18;
  *(undefined **)(param_1 + 0x38) = PTR_FUN_005fffe8;
  *(undefined **)(param_1 + 0x40) = puVar1;
  *(undefined **)(param_1 + 0x48) = PTR_FUN_005fff88;
  *(undefined **)(param_1 + 0xa8) = PTR_FUN_005ffe68;
  return 0;
}

