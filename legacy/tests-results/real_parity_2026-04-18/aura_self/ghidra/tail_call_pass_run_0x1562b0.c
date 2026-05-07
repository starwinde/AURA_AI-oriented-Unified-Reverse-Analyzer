
bool tail_call_pass_run(void)

{
  int iVar1;
  
  iVar1 = ir_detect_tail_calls();
  return iVar1 != 0;
}

