
char ZydisGetPhysicalId(uint param_1,int param_2)

{
  char local_1;
  
  if (param_2 == 1) {
    if (0x23 < (ulong)param_1 - 1) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("((ZyanUSize)reg - ZYDIS_REGISTER_AL) < (sizeof(reg8_lookup) / sizeof((reg8_lookup)[0]))"
                    ,"/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x2ef,
                    "ZydisGetPhysicalId");
    }
    local_1 = reg8_lookup_54[param_1 - 1];
  }
  else {
    local_1 = ZydisRegisterGetId(param_1);
    if (local_1 == -1) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("reg_id != 0xFF",
                    "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x2e3,
                    "ZydisGetPhysicalId");
    }
  }
  return local_1;
}

