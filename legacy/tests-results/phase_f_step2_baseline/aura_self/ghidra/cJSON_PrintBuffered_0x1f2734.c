
void cJSON_PrintBuffered(undefined8 param_1,int param_2,uint param_3)

{
  int iVar1;
  long lVar2;
  long local_88;
  long lStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long local_68;
  undefined *puStack_60;
  undefined *puStack_58;
  undefined *local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  lStack_80 = 0;
  local_88 = 0;
  uStack_70 = 0;
  uStack_78 = 0;
  puStack_60 = (undefined *)0x0;
  local_68 = 0;
  local_50 = (undefined *)0x0;
  puStack_58 = (undefined *)0x0;
  if (-1 < param_2) {
    local_88 = (*(code *)global_hooks)((long)param_2);
    if (local_88 != 0) {
      uStack_78 = 0;
      local_68 = (ulong)param_3 << 0x20;
      puStack_60 = global_hooks;
      puStack_58 = PTR_free_006005a0;
      local_50 = PTR_realloc_006005a8;
      lStack_80 = (long)param_2;
      iVar1 = print_value(param_1,&local_88);
      lVar2 = local_88;
      if (iVar1 == 0) {
        (*(code *)PTR_free_006005a0)(local_88);
        lVar2 = 0;
      }
      goto LAB_001f27d0;
    }
  }
  lVar2 = 0;
LAB_001f27d0:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(lVar2,PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

