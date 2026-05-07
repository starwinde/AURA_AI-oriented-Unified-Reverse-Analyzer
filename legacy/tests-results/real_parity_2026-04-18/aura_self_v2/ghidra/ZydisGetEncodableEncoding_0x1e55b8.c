
undefined4 ZydisGetEncodableEncoding(uint param_1)

{
  if (6 < param_1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)encoding <= ZYDIS_INSTRUCTION_ENCODING_MAX_VALUE",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x124,
                  "ZydisGetEncodableEncoding");
  }
  return *(undefined4 *)(encoding_lookup_71 + (ulong)param_1 * 4);
}

