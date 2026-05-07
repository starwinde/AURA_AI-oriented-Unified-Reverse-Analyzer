
undefined8 AArch64_global_init(long param_1)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  uVar2 = (**(code **)PTR_cs_mem_malloc_005ffed0)(0x58);
  AArch64_init();
  *(undefined **)(param_1 + 8) = PTR_AArch64_printInst_005ffef0;
  *(undefined8 *)(param_1 + 0x10) = uVar2;
  *(undefined **)(param_1 + 0x18) = PTR_AArch64_getInstruction_005fff38;
  *(undefined8 *)(param_1 + 0x20) = uVar2;
  puVar1 = PTR_AArch64_insn_name_005fff48;
  *(undefined **)(param_1 + 0x28) = PTR_AArch64_reg_name_005ffea0;
  *(undefined **)(param_1 + 0x30) = puVar1;
  puVar1 = PTR_AArch64_get_insn_id_005fff18;
  *(undefined **)(param_1 + 0x38) = PTR_AArch64_group_name_005fffe8;
  *(undefined **)(param_1 + 0x40) = puVar1;
  *(undefined **)(param_1 + 0x48) = PTR_AArch64_post_printer_005fff88;
  *(undefined **)(param_1 + 0xa8) = PTR_AArch64_reg_access_005ffe68;
  return 0;
}

