
bool pm_run_cond_simplify(long param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = ir_cond_simplify_part_0();
    return 0 < iVar1;
  }
  return false;
}

