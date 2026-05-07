
_IO_FILE * FUN_00107340(_IO_FILE *param_1,_IO_FILE *param_2)

{
  _IO_FILE *p_Var1;
  char *pcVar2;
  ulong uVar3;
  ulong uVar4;
  undefined *puVar5;
  uint uVar6;
  _IO_FILE *p_Var7;
  ulong uVar8;
  
  puVar5 = PTR_stdout_0013ffc0;
  if (param_2 <= param_1) {
    return param_1;
  }
  do {
    while( true ) {
      uVar8 = DAT_001402b8;
      p_Var7 = *(_IO_FILE **)puVar5;
      p_Var1 = (_IO_FILE *)((long)&param_1->_flags + 1);
      pcVar2 = p_Var7->_IO_write_ptr;
      if (DAT_001402b8 != 0) break;
LAB_001073d0:
      if (pcVar2 < p_Var7->_IO_write_end) {
        p_Var7->_IO_write_ptr = pcVar2 + 1;
        *pcVar2 = ' ';
      }
      else {
        uVar6 = __overflow(p_Var7,0x20);
        p_Var7 = (_IO_FILE *)(ulong)uVar6;
      }
      param_1 = p_Var1;
      if (param_2 <= p_Var1) {
        return p_Var7;
      }
    }
    uVar3 = 0;
    if (DAT_001402b8 != 0) {
      uVar3 = (ulong)param_2 / DAT_001402b8;
    }
    uVar4 = 0;
    if (DAT_001402b8 != 0) {
      uVar4 = (ulong)p_Var1 / DAT_001402b8;
    }
    if (uVar3 <= uVar4) goto LAB_001073d0;
    if (pcVar2 < p_Var7->_IO_write_end) {
      p_Var7->_IO_write_ptr = pcVar2 + 1;
      *pcVar2 = '\t';
    }
    else {
      uVar6 = __overflow(p_Var7,9);
      p_Var7 = (_IO_FILE *)(ulong)uVar6;
      uVar8 = DAT_001402b8;
    }
    uVar3 = 0;
    if (uVar8 != 0) {
      uVar3 = (ulong)param_1 / uVar8;
    }
    param_1 = (_IO_FILE *)(uVar8 + uVar3 * uVar8);
    if (param_2 <= param_1) {
      return p_Var7;
    }
  } while( true );
}

