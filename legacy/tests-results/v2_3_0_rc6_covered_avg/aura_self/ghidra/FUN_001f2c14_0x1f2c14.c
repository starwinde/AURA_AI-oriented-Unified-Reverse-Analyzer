
void FUN_001f2c14(uint param_1,ushort param_2,undefined8 *param_3)

{
  if (param_1 == 6) {
LAB_001f2cbc:
    *param_3 = &UNK_0058d388 + (long)(int)(uint)param_2 * 0xe;
    return;
  }
  if (param_1 < 7) {
    if (param_1 == 5) {
      *param_3 = &UNK_005ae3b8 + (long)(int)(uint)param_2 * 0xf;
      return;
    }
    if (param_1 < 6) {
      if (param_1 == 4) {
        *param_3 = &UNK_005991e8 + (long)(int)(uint)param_2 * 0x11;
        return;
      }
      if (param_1 < 5) {
        if (param_1 == 3) {
          *param_3 = &UNK_00593790 + (long)(int)(uint)param_2 * 0xe;
          return;
        }
        if (param_1 < 4) {
          if (param_1 == 2) {
            *param_3 = &UNK_005afb78 + (long)(int)(uint)param_2 * 0xd;
            return;
          }
          if (param_1 < 3) {
            if (param_1 == 0) goto LAB_001f2cbc;
            if (param_1 == 1) {
              *param_3 = &UNK_005b0468 + (long)(int)(uint)param_2 * 0xc;
              return;
            }
          }
        }
      }
    }
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/SharedData.c",0x67,
                "ZydisGetInstructionDefinition");
}

