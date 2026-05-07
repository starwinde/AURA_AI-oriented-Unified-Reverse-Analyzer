
void ZydisEncodeVexCommons
               (ulong *param_1,char *param_2,undefined1 *param_3,byte *param_4,undefined1 *param_5)

{
  undefined1 uVar1;
  
  if (*(uint *)((long)param_1 + 0xc) < 8) {
    *param_2 = (char)*(undefined4 *)((long)param_1 + 0xc);
  }
  else {
    if (2 < *(uint *)((long)param_1 + 0xc) - 9) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xe37,
                    "ZydisEncodeVexCommons");
    }
    *param_2 = (char)*(undefined4 *)((long)param_1 + 0xc) + -1;
  }
  *(undefined4 *)((long)param_1 + 0xc) = 0;
  *param_3 = 0;
  if ((*param_1 & 0x80000000000) == 0) {
    if ((*param_1 & 0x10000000) == 0) {
      if ((*param_1 & 0x40000000) != 0) {
        *param_3 = 3;
      }
    }
    else {
      *param_3 = 2;
    }
  }
  else {
    *param_3 = 1;
  }
  *param_4 = ~*(byte *)((long)param_1 + 0x11);
  uVar1 = ZydisEncodeRex2(param_1);
  *param_5 = uVar1;
  return;
}

