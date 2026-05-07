
undefined8 FUN_001e86f4(long param_1,ushort param_2)

{
  undefined8 uVar1;
  
  if (0xff < param_2) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("reg_width <= (255)",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0x2ae,
                  "ZydisCheckOsz");
  }
  if (*(char *)(param_1 + 0x28) == '\0') {
    if (param_2 == 8) {
      uVar1 = 0;
    }
    else {
      *(char *)(param_1 + 0x28) = (char)param_2;
      uVar1 = 1;
    }
  }
  else if ((ushort)*(byte *)(param_1 + 0x28) == (param_2 & 0xff)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

