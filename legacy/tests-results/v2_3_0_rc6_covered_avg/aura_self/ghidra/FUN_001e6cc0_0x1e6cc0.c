
undefined4 FUN_001e6cc0(undefined4 *param_1,int param_2,char *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (param_2 < 1) {
    return 0xffffffff;
  }
  puVar1 = param_1 + (long)param_2 * 4;
  do {
    iVar2 = strcmp(*(char **)(param_1 + 2),param_3);
    if (iVar2 == 0) {
      return *param_1;
    }
    param_1 = param_1 + 4;
  } while (param_1 != puVar1);
  return 0xffffffff;
}

