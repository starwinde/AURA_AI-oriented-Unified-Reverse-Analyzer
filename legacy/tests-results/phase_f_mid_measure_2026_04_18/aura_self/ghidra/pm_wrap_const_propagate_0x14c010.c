
bool pm_wrap_const_propagate(void)

{
  int iVar1;
  
  iVar1 = ir_const_propagate();
  return iVar1 != 0;
}

