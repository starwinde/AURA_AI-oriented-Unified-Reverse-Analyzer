
undefined1 ZydisGetOszFromHint(uint param_1)

{
  if (4 < param_1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)hint <= ZYDIS_OPERAND_SIZE_HINT_MAX_VALUE",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x155,
                  "ZydisGetOszFromHint");
  }
  return *(undefined1 *)((long)&lookup_65 + (ulong)param_1);
}

