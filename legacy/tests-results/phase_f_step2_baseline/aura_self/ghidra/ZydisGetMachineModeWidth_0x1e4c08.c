
undefined1 ZydisGetMachineModeWidth(uint param_1)

{
  if (5 < param_1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)machine_mode <= ZYDIS_MACHINE_MODE_MAX_VALUE",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x131,
                  "ZydisGetMachineModeWidth");
  }
  return *(undefined1 *)((long)&lookup_69 + (ulong)param_1);
}

