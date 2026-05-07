
undefined8 ZydisCheckAsz(undefined8 *param_1,ushort param_2)

{
  undefined8 uVar1;
  
  if (0xff < param_2) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("reg_width <= (255)",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x2c6,
                  "ZydisCheckAsz");
  }
  if (*(char *)((long)param_1 + 0x29) == '\0') {
    if ((*(int *)*param_1 == 0) && (param_2 == 0x10)) {
      uVar1 = 0;
    }
    else {
      *(char *)((long)param_1 + 0x29) = (char)param_2;
      uVar1 = 1;
    }
  }
  else if ((ushort)*(byte *)((long)param_1 + 0x29) == (param_2 & 0xff)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

