
void FUN_00147930(byte *param_1,ulonglong *param_2)

{
  byte bVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  byte *local_30;
  long local_28;
  
  bVar1 = *param_1;
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (bVar1 == 0x20 || bVar1 == 9) {
    do {
      param_1 = param_1 + 1;
      bVar1 = *param_1;
    } while (bVar1 == 0x20 || bVar1 == 9);
  }
  if (bVar1 != 0) {
    if (bVar1 == 0x23) {
      bVar1 = param_1[1];
      param_1 = param_1 + 1;
      if (bVar1 == 0x20 || bVar1 == 9) {
        do {
          param_1 = param_1 + 1;
          bVar1 = *param_1;
        } while (bVar1 == 0x20 || bVar1 == 9);
      }
      if (bVar1 == 0) goto LAB_001479a0;
    }
    if ((0x1a < (byte)((bVar1 & 0xdf) + 0xbf)) &&
       (uVar3 = strtoull((char *)param_1,(char **)&local_30,0), param_1 != local_30)) {
      uVar2 = 1;
      *param_2 = uVar3;
      goto LAB_001479a4;
    }
  }
LAB_001479a0:
  uVar2 = 0;
LAB_001479a4:
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar2,PTR___stack_chk_guard_005ffe88,0,
                     local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

