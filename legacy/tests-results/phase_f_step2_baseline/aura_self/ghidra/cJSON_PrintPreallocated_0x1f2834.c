
undefined4 cJSON_PrintPreallocated(undefined8 param_1,long param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long local_58;
  long lStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined8 local_38;
  undefined *puStack_30;
  undefined *puStack_28;
  undefined *local_20;
  long local_18;
  
  local_18 = *(long *)PTR___stack_chk_guard_005ffe88;
  lStack_50 = 0;
  local_58 = 0;
  uStack_40 = 0;
  uStack_48 = 0;
  puStack_30 = (undefined *)0x0;
  local_38 = 0;
  local_20 = (undefined *)0x0;
  puStack_28 = (undefined *)0x0;
  if (param_3 < 0 || param_2 == 0) {
    uVar1 = 0;
  }
  else {
    lStack_50 = (long)param_3;
    local_38 = CONCAT44(param_4,1);
    puStack_30 = global_hooks;
    puStack_28 = PTR_free_006005a0;
    local_20 = PTR_realloc_006005a8;
    local_58 = param_2;
    uVar1 = print_value(param_1,&local_58);
  }
  if (local_18 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar1;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,uVar1,0,
                   local_18 - *(long *)PTR___stack_chk_guard_005ffe88);
}

