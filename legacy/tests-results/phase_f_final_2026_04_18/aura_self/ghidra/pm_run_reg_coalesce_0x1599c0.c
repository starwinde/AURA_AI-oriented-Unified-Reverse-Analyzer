
bool pm_run_reg_coalesce(long param_1)

{
  int iVar1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 8) != 0)) {
    iVar1 = ir_reg_coalesce_part_0();
    return 0 < iVar1;
  }
  return false;
}

