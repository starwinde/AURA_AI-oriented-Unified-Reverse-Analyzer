
bool pm_run_expr_reassoc(void)

{
  int iVar1;
  
  iVar1 = ir_expr_reassoc();
  return 0 < iVar1;
}

