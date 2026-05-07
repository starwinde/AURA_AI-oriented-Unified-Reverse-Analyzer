
ulong FUN_0010e3f0(undefined4 param_1)

{
  uint uVar1;
  ulong uVar2;
  char *__s;
  size_t sVar3;
  
  if (((DAT_001412c0 & 1) == 0) && (__s = (char *)FUN_0010e300(), __s != (char *)0x0)) {
    sVar3 = strlen(__s);
    uVar1 = FUN_00112a50(__s,sVar3);
    if ((int)uVar1 < 0) {
      uVar1 = 0;
    }
    return (ulong)uVar1;
  }
  uVar2 = __snprintf_chk(0,0,2,0xffffffffffffffff,&DAT_0011bce0,param_1);
  return uVar2;
}

