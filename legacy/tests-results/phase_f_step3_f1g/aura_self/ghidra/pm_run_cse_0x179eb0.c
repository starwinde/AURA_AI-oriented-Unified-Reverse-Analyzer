
bool pm_run_cse(long param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = ir_cse_part_0();
    return 0 < iVar1;
  }
  return false;
}

