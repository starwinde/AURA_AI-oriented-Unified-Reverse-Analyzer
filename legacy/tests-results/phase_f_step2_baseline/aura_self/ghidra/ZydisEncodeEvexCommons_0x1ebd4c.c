
void ZydisEncodeEvexCommons(long param_1,byte *param_2,byte *param_3,byte *param_4)

{
  byte local_1c;
  byte local_1b;
  byte local_1a;
  byte local_19;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  ZydisEncodeVexCommons(param_1,&local_1c,&local_1b,param_4,&local_1a);
  local_19 = ~local_1a;
  *param_2 = local_19 << 5 | (byte)((int)(uint)local_19 >> 2) & 0x10 | local_1c;
  if (*(char *)(param_1 + 0x1c) == '\0') {
    *param_2 = *param_2 | (byte)((int)(uint)local_1a >> 1) & 8;
  }
  else if ((*(byte *)(param_1 + 0x17) & 0x10) != 0) {
    *param_2 = *param_2 & 0xbf;
  }
  *param_3 = (local_1a & 8) << 4 | (*param_4 & 0xf) << 3 | (byte)((int)(uint)local_19 >> 3) & 4 |
             local_1b;
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

