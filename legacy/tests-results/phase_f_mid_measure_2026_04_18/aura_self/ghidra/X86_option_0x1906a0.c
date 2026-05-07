
undefined8 X86_option(long param_1,int param_2,ulong param_3)

{
  undefined *puVar1;
  undefined *puVar2;
  
  puVar2 = PTR_regsize_map_64_005ffee8;
  puVar1 = PTR_regsize_map_32_005ffeb8;
  if (param_2 == 1) {
    if (param_3 == 2) {
      *(undefined **)(param_1 + 8) = PTR_X86_ATT_printInst_005ffe80;
      *(undefined4 *)(param_1 + 0x68) = 2;
    }
    else if (param_3 < 3) {
      *(undefined **)(param_1 + 8) = PTR_X86_Intel_printInst_005fff08;
      *(undefined4 *)(param_1 + 0x68) = 1;
    }
    else {
      if (param_3 != 4) {
        *(undefined4 *)(param_1 + 0x50) = 6;
        return 6;
      }
      *(undefined **)(param_1 + 8) = PTR_X86_Intel_printInst_005fff08;
      *(undefined4 *)(param_1 + 0x68) = 4;
    }
  }
  else if (param_2 == 3) {
    *(int *)(param_1 + 4) = (int)param_3;
    if (param_3 == 8) {
      puVar1 = puVar2;
    }
    *(undefined **)(param_1 + 0xa0) = puVar1;
  }
  return 0;
}

