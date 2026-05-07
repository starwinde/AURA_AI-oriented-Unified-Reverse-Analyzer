
_IO_FILE * FUN_0010c920(byte param_1)

{
  ulong uVar1;
  undefined *puVar2;
  uint uVar3;
  ulong uVar4;
  _IO_FILE *p_Var5;
  byte *pbVar6;
  ulong uVar7;
  ulong uVar8;
  undefined8 uVar9;
  byte bVar10;
  uint uVar11;
  
  puVar2 = PTR_stdout_0013ffc0;
  if (DAT_00140ee0 == 0) {
    p_Var5 = *(_IO_FILE **)PTR_stdout_0013ffc0;
    pbVar6 = (byte *)p_Var5->_IO_write_ptr;
    if (p_Var5->_IO_write_end <= pbVar6) goto LAB_0010cb08;
  }
  else {
    uVar7 = 0;
    uVar8 = 0;
    do {
      while (uVar9 = *(undefined8 *)(DAT_00140ee8 + uVar7 * 8), DAT_00141020 == 0) {
        uVar4 = uVar8;
        if (uVar7 != 0) {
          uVar1 = uVar8 + 2;
LAB_0010ca88:
          uVar4 = uVar1;
          uVar8 = uVar8 + 2;
          p_Var5 = *(_IO_FILE **)puVar2;
          uVar11 = 0x20;
          bVar10 = 0x20;
          pbVar6 = (byte *)p_Var5->_IO_write_ptr;
          uVar3 = 0x20;
          if (pbVar6 < p_Var5->_IO_write_end) goto LAB_0010c9f8;
LAB_0010caa0:
          __overflow(p_Var5,(uint)param_1);
          p_Var5 = *(_IO_FILE **)puVar2;
          pbVar6 = (byte *)p_Var5->_IO_write_ptr;
          if (pbVar6 < p_Var5->_IO_write_end) goto LAB_0010ca14;
LAB_0010cac0:
          __overflow(p_Var5,uVar11);
        }
LAB_0010c978:
        FUN_001168f0(uVar9,uVar8);
        uVar7 = uVar7 + 1;
        uVar8 = uVar4;
        if (DAT_00140ee0 <= uVar7) goto LAB_0010ca3c;
      }
      uVar4 = FUN_0010c730(uVar9);
      if (uVar7 == 0) {
        uVar4 = uVar4 + uVar8;
        goto LAB_0010c978;
      }
      uVar1 = uVar4 + uVar8 + 2;
      if ((DAT_00141020 == 0) || ((uVar1 < DAT_00141020 && (uVar8 <= -uVar4 - 3))))
      goto LAB_0010ca88;
      uVar11 = (uint)DAT_001400cc;
      p_Var5 = *(_IO_FILE **)puVar2;
      uVar8 = 0;
      pbVar6 = (byte *)p_Var5->_IO_write_ptr;
      bVar10 = DAT_001400cc;
      uVar3 = uVar11;
      if (p_Var5->_IO_write_end <= pbVar6) goto LAB_0010caa0;
LAB_0010c9f8:
      uVar11 = uVar3;
      p_Var5->_IO_write_ptr = (char *)(pbVar6 + 1);
      *pbVar6 = param_1;
      p_Var5 = *(_IO_FILE **)puVar2;
      pbVar6 = (byte *)p_Var5->_IO_write_ptr;
      if (p_Var5->_IO_write_end <= pbVar6) goto LAB_0010cac0;
LAB_0010ca14:
      p_Var5->_IO_write_ptr = (char *)(pbVar6 + 1);
      *pbVar6 = bVar10;
      uVar7 = uVar7 + 1;
      FUN_001168f0(uVar9,uVar8);
      uVar8 = uVar4;
    } while (uVar7 < DAT_00140ee0);
LAB_0010ca3c:
    p_Var5 = *(_IO_FILE **)puVar2;
    pbVar6 = (byte *)p_Var5->_IO_write_ptr;
    if (p_Var5->_IO_write_end <= pbVar6) {
LAB_0010cb08:
      uVar3 = __overflow(p_Var5,(uint)DAT_001400cc);
      return (_IO_FILE *)(ulong)uVar3;
    }
  }
  bVar10 = DAT_001400cc;
  p_Var5->_IO_write_ptr = (char *)(pbVar6 + 1);
  *pbVar6 = bVar10;
  return p_Var5;
}

