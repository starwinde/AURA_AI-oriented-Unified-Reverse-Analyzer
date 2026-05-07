
/* WARNING: Restarted to delay deadcode elimination for space: ram */

_IO_FILE * FUN_0010f220(void)

{
  long lVar1;
  byte *pbVar2;
  ulong uVar3;
  undefined *puVar4;
  byte bVar5;
  uint uVar6;
  _IO_FILE *p_Var7;
  _IO_FILE *p_Var8;
  ulong uVar9;
  long lVar10;
  _IO_FILE *p_Var11;
  long lVar12;
  undefined8 uVar13;
  long lVar14;
  long lVar15;
  
  puVar4 = PTR_stdout_0013ffc0;
  if (DAT_00140f2c == 2) {
    if (DAT_00141020 == 0) {
LAB_0010f60c:
      p_Var7 = (_IO_FILE *)FUN_0010c920(0x20);
      return p_Var7;
    }
    uVar9 = FUN_0010e040(1);
    puVar4 = PTR_stdout_0013ffc0;
    p_Var7 = (_IO_FILE *)0x0;
    if (uVar9 != 0) {
      p_Var7 = (_IO_FILE *)((ulong)DAT_00140ee0 / uVar9);
    }
    lVar1 = DAT_001412b0 + uVar9 * 0x18;
    p_Var11 = (_IO_FILE *)((long)DAT_00140ee0 - (long)p_Var7 * uVar9);
    if (p_Var11 != (_IO_FILE *)0x0) {
      p_Var7 = (_IO_FILE *)((long)&p_Var7->_flags + 1);
    }
    if (p_Var7 != (_IO_FILE *)0x0) {
      p_Var11 = (_IO_FILE *)0x0;
      do {
        lVar10 = 0;
        lVar12 = 0;
        p_Var8 = p_Var11;
        while( true ) {
          uVar13 = DAT_00140ee8[(long)p_Var8];
          p_Var8 = (_IO_FILE *)((long)&p_Var7->_flags + (long)&p_Var8->_flags);
          lVar15 = FUN_0010c730(uVar13);
          lVar14 = *(long *)(*(long *)(lVar1 + -8) + lVar10);
          FUN_001168f0(uVar13,lVar12);
          bVar5 = DAT_001400cc;
          lVar15 = lVar15 + lVar12;
          lVar10 = lVar10 + 8;
          lVar12 = lVar12 + lVar14;
          if (DAT_00140ee0 <= p_Var8) break;
          FUN_00107340(lVar15,lVar12);
        }
        p_Var8 = *(_IO_FILE **)puVar4;
        pbVar2 = (byte *)p_Var8->_IO_write_ptr;
        if (pbVar2 < p_Var8->_IO_write_end) {
          p_Var8->_IO_write_ptr = (char *)(pbVar2 + 1);
          *pbVar2 = bVar5;
        }
        else {
          uVar6 = __overflow(p_Var8,(uint)DAT_001400cc);
          p_Var8 = (_IO_FILE *)(ulong)uVar6;
        }
        p_Var11 = (_IO_FILE *)((long)&p_Var11->_flags + 1);
      } while (p_Var7 != p_Var11);
      return p_Var8;
    }
  }
  else if (DAT_00140f2c < 3) {
    p_Var11 = DAT_00140ee0;
    if (DAT_00140f2c == 0) {
      if (DAT_00140ee0 != (_IO_FILE *)0x0) {
        p_Var7 = (_IO_FILE *)0x0;
        do {
          if (((DAT_00141291 & 1) != 0) && (uVar9 = FUN_0010aca0(4), (uVar9 & 1) != 0)) {
            FUN_0010b000(&DAT_001400f0);
            FUN_0010b000(&DAT_00140130);
            FUN_0010b000(&DAT_00140100);
          }
          FUN_0010e560(DAT_00140ee8[(long)p_Var7]);
          bVar5 = DAT_001400cc;
          p_Var11 = *(_IO_FILE **)puVar4;
          pbVar2 = (byte *)p_Var11->_IO_write_ptr;
          DAT_001402c0 = DAT_001402c0 + 1;
          if (pbVar2 < p_Var11->_IO_write_end) {
            p_Var11->_IO_write_ptr = (char *)(pbVar2 + 1);
            *pbVar2 = bVar5;
          }
          else {
            __overflow(p_Var11,(uint)DAT_001400cc);
          }
          p_Var7 = (_IO_FILE *)((long)&p_Var7->_flags + 1);
        } while (p_Var7 < DAT_00140ee0);
        return DAT_00140ee0;
      }
    }
    else if (DAT_00140ee0 != (_IO_FILE *)0x0) {
      p_Var7 = (_IO_FILE *)0x0;
      do {
        FUN_001168f0(DAT_00140ee8[(long)p_Var7],0);
        bVar5 = DAT_001400cc;
        p_Var11 = *(_IO_FILE **)puVar4;
        pbVar2 = (byte *)p_Var11->_IO_write_ptr;
        if (pbVar2 < p_Var11->_IO_write_end) {
          p_Var11->_IO_write_ptr = (char *)(pbVar2 + 1);
          *pbVar2 = bVar5;
        }
        else {
          __overflow(p_Var11,(uint)DAT_001400cc);
        }
        p_Var7 = (_IO_FILE *)((long)&p_Var7->_flags + 1);
        p_Var11 = DAT_00140ee0;
      } while (p_Var7 < DAT_00140ee0);
    }
  }
  else if (DAT_00140f2c == 3) {
    if (DAT_00141020 == 0) goto LAB_0010f60c;
    uVar9 = FUN_0010e040(0);
    uVar13 = *DAT_00140ee8;
    lVar1 = DAT_001412b0 + uVar9 * 0x18 + -0x18;
    lVar10 = FUN_0010c730(uVar13);
    lVar12 = **(long **)(lVar1 + 0x10);
    FUN_001168f0(uVar13,0);
    puVar4 = PTR_stdout_0013ffc0;
    if ((_IO_FILE *)0x1 < DAT_00140ee0) {
      lVar15 = 0;
      p_Var7 = (_IO_FILE *)0x1;
      do {
        bVar5 = DAT_001400cc;
        uVar3 = 0;
        if (uVar9 != 0) {
          uVar3 = (ulong)p_Var7 / uVar9;
        }
        lVar14 = (long)p_Var7 - uVar3 * uVar9;
        if (lVar14 == 0) {
          p_Var11 = *(_IO_FILE **)puVar4;
          pbVar2 = (byte *)p_Var11->_IO_write_ptr;
          if (pbVar2 < p_Var11->_IO_write_end) {
            p_Var11->_IO_write_ptr = (char *)(pbVar2 + 1);
            *pbVar2 = bVar5;
          }
          else {
            __overflow(p_Var11,(uint)DAT_001400cc);
          }
          lVar15 = 0;
        }
        else {
          lVar10 = lVar15 + lVar10;
          lVar15 = lVar15 + lVar12;
          FUN_00107340(lVar10,lVar15);
        }
        uVar13 = DAT_00140ee8[(long)p_Var7];
        p_Var7 = (_IO_FILE *)((long)&p_Var7->_flags + 1);
        FUN_001168f0(uVar13,lVar15);
        lVar10 = FUN_0010c730(uVar13);
        lVar12 = *(long *)(*(long *)(lVar1 + 0x10) + lVar14 * 8);
      } while (p_Var7 < DAT_00140ee0);
    }
    bVar5 = DAT_001400cc;
    p_Var11 = *(_IO_FILE **)puVar4;
    pbVar2 = (byte *)p_Var11->_IO_write_ptr;
    if (p_Var11->_IO_write_end <= pbVar2) {
      uVar6 = __overflow(p_Var11,(uint)DAT_001400cc);
      return (_IO_FILE *)(ulong)uVar6;
    }
    p_Var11->_IO_write_ptr = (char *)(pbVar2 + 1);
    *pbVar2 = bVar5;
  }
  else {
    p_Var11 = (_IO_FILE *)(ulong)DAT_00140f2c;
    if (DAT_00140f2c == 4) {
      p_Var7 = (_IO_FILE *)FUN_0010c920(0x2c);
      return p_Var7;
    }
  }
  return p_Var11;
}

