
bool pm_run_phi_elimination(void)

{
  int iVar1;
  
  iVar1 = ir_phi_elimination();
  return 0 < iVar1;
}

