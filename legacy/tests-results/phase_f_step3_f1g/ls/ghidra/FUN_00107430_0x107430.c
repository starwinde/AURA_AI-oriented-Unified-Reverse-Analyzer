
void FUN_00107430(void *param_1,size_t param_2)

{
  DAT_001402c0 = DAT_001402c0 + param_2;
  fwrite_unlocked(param_1,1,param_2,*(FILE **)PTR_stdout_0013ffc0);
  return;
}

