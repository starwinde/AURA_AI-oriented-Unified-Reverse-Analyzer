
int ZydisEncoderEncodeInstructionInternal
              (undefined8 param_1,undefined8 param_2,ulong *param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 local_68;
  ulong local_60;
  ulong local_58;
  undefined1 auStack_50 [56];
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  iVar1 = ZydisFindMatchingDefinition(param_1,auStack_50);
  if (-1 < iVar1) {
    local_60 = *param_3;
    if (0xf < local_60) {
      local_60 = 0xf;
    }
    local_58 = 0;
    local_68 = param_2;
    iVar1 = ZydisBuildInstruction(auStack_50,param_4);
    if (-1 < iVar1) {
      iVar1 = ZydisEmitInstruction(param_4,&local_68);
      if ((iVar1 == -0x7feffff7) && (local_60 == 0xf)) {
        iVar1 = -0x7fdffffe;
      }
      else if (-1 < iVar1) {
        *param_3 = local_58;
        iVar1 = 0x100000;
      }
    }
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return iVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,iVar1,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

