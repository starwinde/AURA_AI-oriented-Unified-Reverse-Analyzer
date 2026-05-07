
undefined1 ZydisGetAszFromHint(uint param_1)

{
  if (3 < param_1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)hint <= ZYDIS_ADDRESS_SIZE_HINT_MAX_VALUE",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x147,
                  "ZydisGetAszFromHint");
  }
  return *(undefined1 *)((long)&lookup_67 + (ulong)param_1);
}

