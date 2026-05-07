
bool FUN_001e8900(undefined8 *param_1,uint param_2,int param_3)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  
  cVar1 = FUN_001f2720(param_2);
  if (cVar1 < '\0') {
                    /* WARNING: Subroutine does not return */
    __assert_fail("reg_id >= 0","/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",
                  0x302,"ZydisIsRegisterAllowed");
  }
  if (*(int *)*param_1 == 0) {
    bVar2 = *(byte *)(param_1[1] + 6) & 7;
    if (bVar2 == 5) {
      bVar3 = true;
    }
    else {
      if (bVar2 < 6) {
        if ((*(byte *)(param_1[1] + 6) & 7) == 0) {
          if (3 < param_3 - 1U) {
            return cVar1 < '\x10';
          }
          if (((*(byte *)(param_1[1] + 8) & 0x18) == 0) &&
             (bVar2 = FUN_001e8850(param_2,param_3), 0xf < bVar2)) {
            return false;
          }
          return true;
        }
        if (bVar2 == 4) {
          if ((4 < param_2) && (param_2 < 9)) {
            return false;
          }
          return true;
        }
      }
      bVar3 = cVar1 < '\x10';
    }
  }
  else if ((param_3 == 4) || ('\a' < cVar1)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  return bVar3;
}

