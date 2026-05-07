
void FUN_0010f784(char *param_1)

{
  size_t sVar1;
  void *pvVar2;
  
  sVar1 = strlen(param_1);
  sVar1 = sVar1 + 1;
  pvVar2 = malloc(sVar1);
  if (pvVar2 != (void *)0x0) {
    __memcpy_chk(pvVar2,param_1,sVar1,sVar1);
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0010d454();
}

