
undefined8 ir_reg_coalesce(long param_1)

{
  undefined8 uVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 8) != 0)) {
    uVar1 = ir_reg_coalesce_part_0();
    return uVar1;
  }
  return 0;
}

