
byte FUN_00108d80(void)

{
  int iVar1;
  
  if (-1 < (char)DAT_001400c0) {
    return DAT_001400c0 & 1;
  }
  iVar1 = isatty(1);
  DAT_001400c0 = (byte)iVar1;
  return (byte)iVar1 & 1;
}

