
_IO_FILE * FUN_00107250(long *param_1,long param_2,long param_3)

{
  _IO_FILE *p_Var1;
  char *pcVar2;
  byte bVar3;
  ulong uVar4;
  ulong uVar5;
  undefined *puVar6;
  uint uVar7;
  long *plVar8;
  ulong uVar9;
  _IO_FILE *p_Var10;
  _IO_FILE *p_Var11;
  code *pcVar12;
  long lVar13;
  _IO_FILE *p_Var14;
  long lVar15;
  undefined1 auVar16 [16];
  
  if (param_3 == 0) {
    bVar3 = *(byte *)(param_1 + 10);
    lVar15 = 0xf;
    if (param_2 == 0) {
      param_2 = 0xfe0;
    }
    *param_1 = param_2;
    param_1[6] = 0xf;
    param_3 = 0x10;
    pcVar12 = (code *)param_1[7];
  }
  else {
    bVar3 = *(byte *)(param_1 + 10);
    lVar15 = param_3 + -1;
    if (param_2 == 0) {
      param_2 = 0xfe0;
    }
    *param_1 = param_2;
    param_1[6] = lVar15;
    pcVar12 = (code *)param_1[7];
  }
  if ((bVar3 & 1) == 0) {
    plVar8 = (long *)(*pcVar12)(param_2);
  }
  else {
    plVar8 = (long *)(*pcVar12)(param_1[9]);
  }
  param_1[1] = (long)plVar8;
  if (plVar8 != (long *)0x0) {
    lVar13 = *param_1;
    uVar9 = (long)plVar8 + lVar15 + 0x10 & -param_3;
    param_1[2] = uVar9;
    param_1[3] = uVar9;
    bVar3 = *(byte *)(param_1 + 10);
    *plVar8 = (long)plVar8 + lVar13;
    param_1[4] = (long)plVar8 + lVar13;
    plVar8[1] = 0;
    *(byte *)(param_1 + 10) = bVar3 & 0xf9;
    return (_IO_FILE *)0x1;
  }
  auVar16 = (**(code **)PTR_obstack_alloc_failed_handler_0013ff80)();
  puVar6 = PTR_stdout_0013ffc0;
  p_Var11 = auVar16._8_8_;
  p_Var14 = auVar16._0_8_;
  if (p_Var11 <= p_Var14) {
    return p_Var14;
  }
  do {
    while( true ) {
      uVar9 = DAT_001402b8;
      p_Var10 = *(_IO_FILE **)puVar6;
      p_Var1 = (_IO_FILE *)((long)&p_Var14->_flags + 1);
      pcVar2 = p_Var10->_IO_write_ptr;
      if (DAT_001402b8 != 0) break;
LAB_001073d0:
      if (pcVar2 < p_Var10->_IO_write_end) {
        p_Var10->_IO_write_ptr = pcVar2 + 1;
        *pcVar2 = ' ';
      }
      else {
        uVar7 = __overflow(p_Var10,0x20);
        p_Var10 = (_IO_FILE *)(ulong)uVar7;
      }
      p_Var14 = p_Var1;
      if (p_Var11 <= p_Var1) {
        return p_Var10;
      }
    }
    uVar4 = 0;
    if (DAT_001402b8 != 0) {
      uVar4 = (ulong)p_Var11 / DAT_001402b8;
    }
    uVar5 = 0;
    if (DAT_001402b8 != 0) {
      uVar5 = (ulong)p_Var1 / DAT_001402b8;
    }
    if (uVar4 <= uVar5) goto LAB_001073d0;
    if (pcVar2 < p_Var10->_IO_write_end) {
      p_Var10->_IO_write_ptr = pcVar2 + 1;
      *pcVar2 = '\t';
    }
    else {
      uVar7 = __overflow(p_Var10,9);
      p_Var10 = (_IO_FILE *)(ulong)uVar7;
      uVar9 = DAT_001402b8;
    }
    uVar4 = 0;
    if (uVar9 != 0) {
      uVar4 = (ulong)p_Var14 / uVar9;
    }
    p_Var14 = (_IO_FILE *)(uVar9 + uVar4 * uVar9);
    if (p_Var11 <= p_Var14) {
      return p_Var10;
    }
  } while( true );
}

