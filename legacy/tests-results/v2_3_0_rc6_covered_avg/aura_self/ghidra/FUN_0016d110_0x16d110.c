
void FUN_0016d110(undefined4 *param_1,long param_2)

{
  if (param_1 == (undefined4 *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"=== Data Archive (%u applicable types) ===\n",*param_1);
  if (*(long *)(param_1 + 2) != 0) {
    __fprintf_chk(param_2,2,"  Archive: %s\n");
    return;
  }
  return;
}

