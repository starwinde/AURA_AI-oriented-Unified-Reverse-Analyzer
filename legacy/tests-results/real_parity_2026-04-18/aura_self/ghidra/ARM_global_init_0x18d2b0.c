
undefined8 ARM_global_init(long param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined8 uVar6;
  
  uVar6 = (**(code **)PTR_cs_mem_malloc_005ffed0)(0x58);
  ARM_init();
  ARM_getRegName(param_1,0);
  puVar4 = PTR_ARM_printInst_005fffb8;
  puVar2 = PTR_ARM_reg_name_005fff90;
  puVar1 = PTR_ARM_getInstruction_005fffa8;
  if ((*(uint *)(param_1 + 4) & 0x10) != 0) {
    puVar1 = PTR_Thumb_getInstruction_005ffe90;
  }
  *(undefined **)(param_1 + 0x18) = puVar1;
  puVar5 = PTR_ARM_insn_name_005fffc0;
  puVar3 = PTR_ARM_group_name_005fff78;
  *(undefined **)(param_1 + 8) = puVar4;
  *(undefined8 *)(param_1 + 0x10) = uVar6;
  puVar1 = PTR_ARM_post_printer_005ffe98;
  *(undefined **)(param_1 + 0x28) = puVar2;
  puVar2 = PTR_ARM_get_insn_id_005fff50;
  *(undefined **)(param_1 + 0x30) = puVar5;
  puVar4 = PTR_ARM_reg_access_005fffb0;
  *(undefined **)(param_1 + 0x38) = puVar3;
  *(undefined **)(param_1 + 0x40) = puVar2;
  *(undefined **)(param_1 + 0x48) = puVar1;
  *(undefined **)(param_1 + 0xa8) = puVar4;
  return 0;
}

