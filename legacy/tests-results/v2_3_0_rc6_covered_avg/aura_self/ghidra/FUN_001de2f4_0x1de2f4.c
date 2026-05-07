
void FUN_001de2f4(long param_1,byte param_2)

{
  int iVar1;
  char local_29;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_2 == 0xf0) {
    *(undefined2 *)(param_1 + 0x39) = 1;
  }
  else if (param_2 < 0xf1) {
    if ((((param_2 == 0x66) &&
         (iVar1 = (**(code **)(param_1 + 0x48))
                            (*(undefined8 *)(param_1 + 0x50),&local_29,
                             *(undefined8 *)(param_1 + 0x58)), iVar1 == 0)) &&
        (*(char *)(param_1 + 0x3b) == '\0')) &&
       ((local_29 == '\x0f' ||
        ((*(int *)(param_1 + 0x60) == 2 && ((byte)(local_29 - 0x40U) < 0x10)))))) {
      *(undefined1 *)(param_1 + 0x3b) = 0x66;
    }
  }
  else if (((byte)(param_2 + 0xe) < 2) &&
          (iVar1 = (**(code **)(param_1 + 0x48))
                             (*(undefined8 *)(param_1 + 0x50),&local_29,
                              *(undefined8 *)(param_1 + 0x58)), iVar1 == 0)) {
    if (((*(int *)(param_1 + 0x60) == 2) && ((byte)(local_29 - 0x40U) < 0x10)) ||
       (local_29 == 'f' || local_29 == '\x0f')) {
      *(byte *)(param_1 + 0x3b) = param_2;
    }
    *(undefined1 *)(param_1 + 0x39) = 0;
    *(byte *)(param_1 + 0x3a) = param_2;
  }
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
}

