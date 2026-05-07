
bool pm_wrap_dead_code_eliminate(void)

{
  int iVar1;
  
  iVar1 = ir_dead_code_eliminate();
  return iVar1 != 0;
}

