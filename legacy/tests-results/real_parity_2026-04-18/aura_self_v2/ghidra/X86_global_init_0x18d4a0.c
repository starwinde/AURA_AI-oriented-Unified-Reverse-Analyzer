
undefined8 X86_global_init(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  uVar4 = (**(code **)PTR_cs_mem_malloc_005ffed0)(0x58);
  X86_init();
  *(undefined8 *)(param_1 + 0x48) = 0;
  puVar2 = PTR_regsize_map_64_005ffee8;
  puVar1 = PTR_regsize_map_32_005ffeb8;
  *(undefined4 *)(param_1 + 0x68) = 1;
  puVar3 = PTR_X86_reg_name_005fffc8;
  if (*(int *)(param_1 + 4) == 8) {
    puVar1 = puVar2;
  }
  *(undefined **)(param_1 + 0x18) = PTR_X86_getInstruction_005fff20;
  puVar2 = PTR_X86_Intel_printInst_005fff08;
  *(undefined **)(param_1 + 0x28) = puVar3;
  puVar3 = PTR_X86_insn_name_005ffe78;
  *(undefined **)(param_1 + 8) = puVar2;
  *(undefined8 *)(param_1 + 0x10) = uVar4;
  puVar2 = PTR_X86_group_name_005ffe60;
  *(undefined **)(param_1 + 0x30) = puVar3;
  *(undefined **)(param_1 + 0x38) = puVar2;
  *(undefined **)(param_1 + 0x40) = PTR_X86_get_insn_id_005fff28;
  puVar2 = PTR_X86_reg_access_005fff58;
  *(undefined **)(param_1 + 0xa0) = puVar1;
  *(undefined **)(param_1 + 0xa8) = puVar2;
  return 0;
}

