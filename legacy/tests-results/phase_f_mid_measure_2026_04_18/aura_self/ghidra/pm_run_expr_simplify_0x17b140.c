
bool pm_run_expr_simplify(long param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 != 0) {
    iVar1 = simplify_identities();
    iVar2 = eliminate_double_negation(param_1);
    iVar3 = fold_across_expr(param_1);
    return 0 < iVar1 + iVar2 + iVar3;
  }
  return false;
}

