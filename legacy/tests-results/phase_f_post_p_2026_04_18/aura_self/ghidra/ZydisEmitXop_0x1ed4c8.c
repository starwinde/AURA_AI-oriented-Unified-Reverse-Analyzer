
int ZydisEmitXop(long param_1,undefined8 param_2)

{
  int iVar1;
  byte local_2a;
  byte local_29;
  byte local_28;
  byte local_27;
  byte local_26;
  byte local_25;
  int local_24;
  int local_20;
  int local_1c;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  ZydisEncodeVexCommons(param_1,&local_2a,&local_29,&local_28,&local_27);
  if (1 < *(byte *)(param_1 + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("instruction->vector_length <= 1",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xe59,
                  "ZydisEmitXop");
  }
  local_26 = ~local_27 << 5 | local_2a;
  local_25 = (local_27 & 8) << 4 | (local_28 & 0xf) << 3 | *(char *)(param_1 + 0x14) << 2 | local_29
  ;
  iVar1 = ZydisEmitByte(0xffffff8f,param_2);
  local_24 = iVar1;
  if (((-1 < iVar1) && (iVar1 = ZydisEmitByte(local_26,param_2), local_20 = iVar1, -1 < iVar1)) &&
     (local_1c = ZydisEmitByte(local_25,param_2), iVar1 = local_1c, -1 < local_1c)) {
    iVar1 = 0x100000;
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar1,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

