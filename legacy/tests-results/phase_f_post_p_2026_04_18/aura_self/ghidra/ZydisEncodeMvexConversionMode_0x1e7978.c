
undefined8 ZydisEncodeMvexConversionMode(uint param_1)

{
  undefined8 uVar1;
  
  if (param_1 == 5) {
    uVar1 = 6;
  }
  else {
    if (5 < param_1) {
LAB_001e7a30:
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x413,
                    "ZydisEncodeMvexConversionMode");
    }
    if (param_1 == 4) {
      uVar1 = 7;
    }
    else {
      if (4 < param_1) goto LAB_001e7a30;
      if (param_1 == 3) {
        uVar1 = 4;
      }
      else {
        if (3 < param_1) goto LAB_001e7a30;
        if (param_1 == 2) {
          uVar1 = 5;
        }
        else {
          if (2 < param_1) goto LAB_001e7a30;
          if (param_1 == 0) {
            uVar1 = 0;
          }
          else {
            if (param_1 != 1) goto LAB_001e7a30;
            uVar1 = 3;
          }
        }
      }
    }
  }
  return uVar1;
}

