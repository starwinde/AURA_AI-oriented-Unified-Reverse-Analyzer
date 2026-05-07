
undefined8 ARM_option(long param_1,int param_2,uint param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar1 = PTR_ARM_getInstruction_005fffa8;
  puVar2 = PTR_Thumb_getInstruction_005ffe90;
  if (param_2 == 1) {
    ARM_getRegName(param_1,param_3);
    *(uint *)(param_1 + 0x68) = param_3;
    return 0;
  }
  if (param_2 != 3) {
    return 0;
  }
  *(uint *)(param_1 + 4) = param_3;
  if ((param_3 & 0x10) != 0) {
    puVar1 = puVar2;
  }
  *(undefined **)(param_1 + 0x18) = puVar1;
  return 0;
}

