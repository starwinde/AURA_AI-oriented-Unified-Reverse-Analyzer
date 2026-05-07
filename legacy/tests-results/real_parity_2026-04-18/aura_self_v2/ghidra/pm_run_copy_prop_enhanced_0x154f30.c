
bool pm_run_copy_prop_enhanced(long param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar1 = phi_through_prop();
    iVar2 = chain_copy_prop(param_1);
    return 0 < iVar1 + iVar2;
  }
  return false;
}

