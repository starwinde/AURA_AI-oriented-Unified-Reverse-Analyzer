
void ZydisGetInstructionDefinition(uint param_1,ushort param_2,long *param_3)

{
  if (param_1 == 6) {
LAB_001f058c:
    *param_3 = (long)(&ISTR_DEFINITIONS_LEGACY + (long)(int)(uint)param_2 * 0xe);
    return;
  }
  if (param_1 < 7) {
    if (param_1 == 5) {
      *param_3 = (long)(ISTR_DEFINITIONS_MVEX + (long)(int)(uint)param_2 * 0xf);
      return;
    }
    if (param_1 < 6) {
      if (param_1 == 4) {
        *param_3 = (long)(ISTR_DEFINITIONS_EVEX + (long)(int)(uint)param_2 * 0x11);
        return;
      }
      if (param_1 < 5) {
        if (param_1 == 3) {
          *param_3 = (long)(ISTR_DEFINITIONS_VEX + (long)(int)(uint)param_2 * 0xe);
          return;
        }
        if (param_1 < 4) {
          if (param_1 == 2) {
            *param_3 = (long)(ISTR_DEFINITIONS_XOP + (long)(int)(uint)param_2 * 0xd);
            return;
          }
          if (param_1 < 3) {
            if (param_1 == 0) goto LAB_001f058c;
            if (param_1 == 1) {
              *param_3 = (long)(ISTR_DEFINITIONS_3DNOW + (long)(int)(uint)param_2 * 0xc);
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

