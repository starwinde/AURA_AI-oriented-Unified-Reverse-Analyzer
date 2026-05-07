
undefined8 ZydisEncodeMvexBroadcastMode(uint param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0xc) {
    if (param_1 < 10) {
      if (param_1 == 0) {
        uVar1 = 0;
      }
      else {
        if (1 < param_1 - 3) goto LAB_001e8ec0;
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 2;
    }
    return uVar1;
  }
LAB_001e8ec0:
                    /* WARNING: Subroutine does not return */
  __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x3f7,
                "ZydisEncodeMvexBroadcastMode");
}

