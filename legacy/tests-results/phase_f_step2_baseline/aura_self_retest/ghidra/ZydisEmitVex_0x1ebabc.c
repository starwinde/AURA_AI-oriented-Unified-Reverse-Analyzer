
int ZydisEmitVex(long param_1,undefined8 param_2)

{
  int iVar1;
  byte local_33;
  byte local_32;
  byte local_31;
  byte local_30;
  byte local_2f;
  byte local_2e;
  byte local_2d;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  ZydisEncodeVexCommons(param_1,&local_33,&local_32,&local_31,&local_30);
  if (1 < *(byte *)(param_1 + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("instruction->vector_length <= 1",
                  "/home/str_dgx_spark/Desktop/AURA/third_party/zydis/src/Encoder.c",0xe71,
                  "ZydisEmitVex");
  }
  if ((local_33 == 1) && ((local_30 & 0xb) == 0)) {
    local_2f = (~local_30 & 4) << 5 | (local_31 & 0xf) << 3 | *(char *)(param_1 + 0x14) << 2 |
               local_32;
    iVar1 = ZydisEmitByte(0xffffffc5,param_2);
    local_2c = iVar1;
    if (iVar1 < 0) goto LAB_001ebd18;
    iVar1 = ZydisEmitByte(local_2f,param_2);
    local_28 = iVar1;
  }
  else {
    local_2e = ~local_30 << 5 | local_33;
    local_2d = (local_30 & 8) << 4 | (local_31 & 0xf) << 3 | *(char *)(param_1 + 0x14) << 2 |
               local_32;
    iVar1 = ZydisEmitByte(0xffffffc4,param_2);
    local_24 = iVar1;
    if ((iVar1 < 0) || (iVar1 = ZydisEmitByte(local_2e,param_2), local_20 = iVar1, iVar1 < 0))
    goto LAB_001ebd18;
    iVar1 = ZydisEmitByte(local_2d,param_2);
    local_1c = iVar1;
  }
  if (-1 < iVar1) {
    iVar1 = 0x100000;
  }
LAB_001ebd18:
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar1,0,
                     local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return iVar1;
}

