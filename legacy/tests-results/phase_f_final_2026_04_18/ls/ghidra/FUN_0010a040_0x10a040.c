
_IO_FILE * FUN_0010a040(char *param_1,undefined8 param_2,undefined8 param_3)

{
  char *pcVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  size_t sVar5;
  _IO_FILE *p_Var6;
  
  if (param_1 != (char *)0x0) {
    sVar5 = strlen(param_1);
    iVar3 = FUN_00112a50(param_1,sVar5);
    puVar2 = PTR_stdout_0013ffc0;
    iVar3 = (int)param_3 - iVar3;
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    sVar5 = strlen(param_1);
    FUN_00107430(param_1,sVar5);
    do {
      p_Var6 = *(_IO_FILE **)puVar2;
      pcVar1 = p_Var6->_IO_write_ptr;
      DAT_001402c0 = (_IO_FILE *)((long)DAT_001402c0 + 1);
      if (pcVar1 < p_Var6->_IO_write_end) {
        p_Var6->_IO_write_ptr = pcVar1 + 1;
        *pcVar1 = ' ';
      }
      else {
        uVar4 = __overflow(p_Var6,0x20);
        p_Var6 = (_IO_FILE *)(ulong)uVar4;
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != -1);
    return p_Var6;
  }
  iVar3 = __printf_chk(2,"%*lu ",param_3,param_2);
  DAT_001402c0 = (_IO_FILE *)((long)DAT_001402c0 + (long)iVar3);
  return DAT_001402c0;
}

