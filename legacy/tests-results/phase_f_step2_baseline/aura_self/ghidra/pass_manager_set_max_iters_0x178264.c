
void pass_manager_set_max_iters(long param_1,int param_2)

{
  if (param_1 != 0) {
    if (param_2 < 1) {
      param_2 = 5;
    }
    *(int *)(param_1 + 0x10) = param_2;
  }
  return;
}

