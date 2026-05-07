
void * cJSON_PrintUnformatted(undefined8 param_1)

{
  long lVar1;
  int iVar2;
  size_t sVar3;
  void *pvVar4;
  void *local_78;
  ulong uStack_70;
  long local_68;
  undefined8 uStack_60;
  ulong local_58;
  undefined *puStack_50;
  undefined *puStack_48;
  undefined *local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  uStack_70 = 0;
  local_78 = (void *)0x0;
  uStack_60 = 0;
  local_68 = 0;
  puStack_50 = (undefined *)0x0;
  local_58 = 0;
  local_40 = (undefined *)0x0;
  puStack_48 = (undefined *)0x0;
  local_78 = (void *)(*(code *)global_hooks)(0x100,PTR___stack_chk_guard_005ffe88,global_hooks,0);
  uStack_70 = 0x100;
  local_58 = local_58 & 0xffffffff;
  puStack_50 = global_hooks;
  puStack_48 = PTR_free_006005a0;
  local_40 = PTR_realloc_006005a8;
  if (local_78 != (void *)0x0) {
    iVar2 = print_value(param_1,&local_78);
    lVar1 = local_68;
    pvVar4 = local_78;
    if (iVar2 != 0) {
      if (local_78 != (void *)0x0) {
        sVar3 = strlen((char *)((long)local_78 + local_68));
        local_68 = lVar1 + sVar3;
      }
      if (PTR_realloc_006005a8 == (undefined *)0x0) {
        pvVar4 = (void *)(*(code *)global_hooks)(local_68 + 1);
        if (pvVar4 != (void *)0x0) {
          sVar3 = local_68 + 1U;
          if (uStack_70 < local_68 + 1U) {
            sVar3 = uStack_70;
          }
          memcpy(pvVar4,local_78,sVar3);
          *(undefined1 *)((long)pvVar4 + local_68) = 0;
          (*(code *)PTR_free_006005a0)(local_78);
          goto LAB_001f467c;
        }
      }
      else {
        pvVar4 = (void *)(*(code *)PTR_realloc_006005a8)(pvVar4);
        if (pvVar4 != (void *)0x0) goto LAB_001f467c;
      }
    }
    if (local_78 != (void *)0x0) {
      (*(code *)PTR_free_006005a0)();
    }
  }
  pvVar4 = (void *)0x0;
LAB_001f467c:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return pvVar4;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
}

