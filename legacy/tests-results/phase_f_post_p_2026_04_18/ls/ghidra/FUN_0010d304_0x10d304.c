
undefined8 FUN_0010d304(undefined8 *param_1)

{
  int iVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  undefined8 uVar5;
  
  piVar2 = __errno_location();
  iVar4 = *piVar2;
  if (*(char *)(param_1 + 1) == '\0') {
    iVar1 = unsetenv("TZ");
  }
  else {
    iVar1 = setenv("TZ",(char *)((long)param_1 + 9),1);
  }
  if (iVar1 == 0) {
    uVar5 = 1;
    tzset();
  }
  else {
    iVar4 = *piVar2;
    uVar5 = 0;
  }
  do {
    pvVar3 = (void *)*param_1;
    free(param_1);
    param_1 = pvVar3;
  } while (pvVar3 != (void *)0x0);
  *piVar2 = iVar4;
  return uVar5;
}

