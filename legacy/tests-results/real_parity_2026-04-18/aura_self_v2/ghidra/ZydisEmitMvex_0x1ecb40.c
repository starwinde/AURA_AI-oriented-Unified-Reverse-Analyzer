
int ZydisEmitMvex(long param_1,undefined8 param_2)

{
  int iVar1;
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
  ZydisEncodeEvexCommons(param_1,&local_2c,&local_2b,&local_2a);
  local_29 = *(char *)(param_1 + 0x12) << 4 | (byte)((int)(uint)local_2a >> 1) & 8 |
             *(byte *)(param_1 + 0x13);
  if (*(char *)(param_1 + 0x20) != '\0') {
    local_29 = local_29 | 0x80;
  }
  if ((*(byte *)(param_1 + 0x19) & 0x10) != 0) {
    local_29 = local_29 & 0xf7;
  }
  iVar1 = ZydisEmitByte(0x62,param_2);
  local_28 = iVar1;
  if ((((-1 < iVar1) && (iVar1 = ZydisEmitByte(local_2c,param_2), local_24 = iVar1, -1 < iVar1)) &&
      (iVar1 = ZydisEmitByte(local_2b & 0xfb,param_2), local_20 = iVar1, -1 < iVar1)) &&
     (local_1c = ZydisEmitByte(local_29,param_2), iVar1 = local_1c, -1 < local_1c)) {
    iVar1 = 0x100000;
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar1,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

