
undefined1 FUN_001e9950(long param_1)

{
  uint uVar1;
  undefined1 uVar2;
  
  uVar1 = *(byte *)(*(long *)(param_1 + 8) + 6) & 7;
  if (uVar1 == 5) {
    uVar2 = FUN_001e94f0(param_1);
    return uVar2;
  }
  if (uVar1 < 6) {
    if (uVar1 < 4) {
      if (-1 < (int)uVar1) {
        return 0;
      }
    }
    else if (uVar1 == 4) {
      uVar2 = FUN_001e8fc8(param_1);
      return uVar2;
    }
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x527,
                "ZydisGetCompDispScale");
}

