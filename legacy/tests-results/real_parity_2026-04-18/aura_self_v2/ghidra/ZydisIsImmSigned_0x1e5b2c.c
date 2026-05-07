
undefined8 ZydisIsImmSigned(uint param_1)

{
  if (param_1 < 0x23) {
    if (0x14 < param_1) {
      return 1;
    }
    if (param_1 < 0x15) {
      if ((0xd < param_1) || (param_1 == 5)) {
        return 0;
      }
      if ((4 < param_1) && (param_1 - 7 < 7)) {
        return 1;
      }
    }
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x21e,
                "ZydisIsImmSigned");
}

