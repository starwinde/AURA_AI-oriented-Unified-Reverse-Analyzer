
undefined8 ZydisEmitUInt(undefined8 param_1,byte param_2,long *param_3)

{
  undefined8 uVar1;
  long lVar2;
  undefined4 local_18;
  
  if ((((param_2 != 1) && (param_2 != 2)) && (param_2 != 4)) && (param_2 != 8)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("size == 1 || size == 2 || size == 4 || size == 8",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xd2f,
                  "ZydisEmitUInt");
  }
  lVar2 = param_3[2];
  if ((ulong)param_3[1] < lVar2 + (ulong)param_2) {
    uVar1 = 0x80100009;
  }
  else {
    if (param_2 == 1) {
      local_18._0_1_ = (undefined1)param_1;
      *(undefined1 *)(*param_3 + param_3[2]) = (undefined1)local_18;
    }
    else if (param_2 == 2) {
      local_18._0_2_ = (undefined2)param_1;
      *(undefined2 *)(*param_3 + param_3[2]) = (undefined2)local_18;
    }
    else if (param_2 == 4) {
      local_18 = (undefined4)param_1;
      *(undefined4 *)(*param_3 + param_3[2]) = local_18;
    }
    else {
      if (param_2 != 8) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xd5d,
                      "ZydisEmitUInt");
      }
      *(undefined8 *)(*param_3 + param_3[2]) = param_1;
    }
    param_3[2] = lVar2 + (ulong)param_2;
    uVar1 = 0x100000;
  }
  return uVar1;
}

