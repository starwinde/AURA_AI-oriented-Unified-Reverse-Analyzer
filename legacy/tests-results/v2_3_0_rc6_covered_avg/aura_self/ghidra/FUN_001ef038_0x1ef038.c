
int FUN_001ef038(undefined8 *param_1,undefined8 param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined1 local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  FUN_001eee7c(param_1,&local_2c,&local_2b,&local_2a);
  if (*(int *)(param_1 + 7) == 0) {
    if (*(char *)((long)param_1 + 0x1f) == '\0') {
      bVar1 = 0;
    }
    else {
      bVar1 = 0x80;
    }
    if (*(char *)((long)param_1 + 0x1e) == '\0') {
      bVar2 = 0;
    }
    else {
      bVar2 = 4;
    }
    local_29 = bVar2 | bVar1 | *(char *)((long)param_1 + 0x14) << 5 |
                       (byte)(uint)((ulong)*param_1 >> 0x29) & 0x10 |
                       (byte)((int)(uint)local_2a >> 1) & 8 | *(byte *)((long)param_1 + 0x13);
    if ((*(char *)((long)param_1 + 0x1b) != '\0') && ((*(byte *)((long)param_1 + 0x19) & 0x10) != 0)
       ) {
      local_2b = local_2b | 4;
      local_29 = local_29 & 0xf7;
    }
  }
  else {
    local_2b = local_2b ^ 0x78;
    local_29 = (char)*(undefined4 *)(param_1 + 7) - 1;
  }
  iVar3 = FUN_001ee2b4(0x62,param_2);
  local_28 = iVar3;
  if ((((-1 < iVar3) && (iVar3 = FUN_001ee2b4(local_2c,param_2), local_24 = iVar3, -1 < iVar3)) &&
      (iVar3 = FUN_001ee2b4(local_2b,param_2), local_20 = iVar3, -1 < iVar3)) &&
     (local_1c = FUN_001ee2b4(local_29,param_2), iVar3 = local_1c, -1 < local_1c)) {
    iVar3 = 0x100000;
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar3;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar3,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

