
char * FUN_00107470(char *param_1,long param_2)

{
  long lVar1;
  long lVar2;
  char *pcVar3;
  long lVar4;
  undefined *puVar5;
  uint uVar6;
  _IO_FILE *p_Var7;
  FILE *__stream;
  ulong uVar8;
  
  lVar2 = *(long *)(param_2 + 0x10);
  lVar4 = *(long *)(param_2 + 0x18);
  if (7 < (ulong)(lVar4 - lVar2)) {
    if (lVar4 == lVar2) {
      *(byte *)(param_2 + 0x50) = *(byte *)(param_2 + 0x50) | 2;
    }
    puVar5 = PTR_stdout_0013ffc0;
    uVar8 = lVar4 + *(ulong *)(param_2 + 0x30) & (*(ulong *)(param_2 + 0x30) ^ 0xffffffffffffffff);
    __stream = *(FILE **)PTR_stdout_0013ffc0;
    if (*(ulong *)(param_2 + 0x20) - *(long *)(param_2 + 8) < uVar8 - *(long *)(param_2 + 8)) {
      uVar8 = *(ulong *)(param_2 + 0x20);
    }
    *(ulong *)(param_2 + 0x10) = uVar8;
    *(ulong *)(param_2 + 0x18) = uVar8;
    uVar8 = 0;
    fputs_unlocked(param_1,__stream);
    do {
      lVar1 = uVar8 * 8;
      uVar8 = uVar8 + 1;
      __printf_chk(2,&DAT_00119bd0,*(undefined8 *)(lVar2 + lVar1));
    } while (uVar8 < (ulong)(lVar4 - lVar2) >> 3);
    p_Var7 = *(_IO_FILE **)puVar5;
    pcVar3 = p_Var7->_IO_write_ptr;
    if (p_Var7->_IO_write_end <= pcVar3) {
      uVar6 = __overflow(p_Var7,10);
      return (char *)(ulong)uVar6;
    }
    p_Var7->_IO_write_ptr = pcVar3 + 1;
    param_1 = (char *)0xa;
    *pcVar3 = '\n';
  }
  return param_1;
}

