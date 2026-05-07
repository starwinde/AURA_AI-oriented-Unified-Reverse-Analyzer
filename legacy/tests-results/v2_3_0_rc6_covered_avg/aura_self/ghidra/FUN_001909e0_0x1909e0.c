
undefined8 FUN_001909e0(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 uVar6;
  
  uVar6 = (**(code **)PTR_PTR_005ffed0)(0x58);
  FUN_001b0100();
  FUN_001bba40(param_1,0);
  puVar4 = PTR_FUN_005fffb8;
  puVar2 = PTR_FUN_005fff90;
  puVar1 = PTR_FUN_005fffa8;
  if ((*(uint *)(param_1 + 4) & 0x10) != 0) {
    puVar1 = PTR_FUN_005ffe90;
  }
  *(undefined **)(param_1 + 0x18) = puVar1;
  puVar5 = PTR_FUN_005fffc0;
  puVar3 = PTR_FUN_005fff78;
  *(undefined **)(param_1 + 8) = puVar4;
  *(undefined8 *)(param_1 + 0x10) = uVar6;
  puVar1 = PTR_FUN_005ffe98;
  *(undefined **)(param_1 + 0x28) = puVar2;
  puVar2 = PTR_FUN_005fff50;
  *(undefined **)(param_1 + 0x30) = puVar5;
  puVar4 = PTR_FUN_005fffb0;
  *(undefined **)(param_1 + 0x38) = puVar3;
  *(undefined **)(param_1 + 0x40) = puVar2;
  *(undefined **)(param_1 + 0x48) = puVar1;
  *(undefined **)(param_1 + 0xa8) = puVar4;
  return 0;
}

