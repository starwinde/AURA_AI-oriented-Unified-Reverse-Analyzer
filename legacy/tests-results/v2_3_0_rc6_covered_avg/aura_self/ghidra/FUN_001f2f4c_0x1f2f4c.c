
void FUN_001f2f4c(uint param_1,undefined4 *param_2,undefined2 *param_3)

{
  if (0x1d < param_1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("(ZyanUSize)element < (sizeof(lookup) / sizeof((lookup)[0]))",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/SharedData.c",0xb4,
                  "ZydisGetElementInfo");
  }
  *param_2 = *(undefined4 *)(&DAT_005bb8e0 + (ulong)param_1 * 8);
  *param_3 = *(undefined2 *)(&DAT_005bb8e4 + (ulong)param_1 * 8);
  return;
}

