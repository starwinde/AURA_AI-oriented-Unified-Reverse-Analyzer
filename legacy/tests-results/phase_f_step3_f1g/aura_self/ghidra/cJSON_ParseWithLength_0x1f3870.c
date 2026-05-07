
undefined8 * cJSON_ParseWithLength(char *param_1,ulong param_2)

{
  byte bVar1;
  int iVar2;
  undefined8 *puVar3;
  char **ppcVar4;
  char *local_70;
  ulong uStack_68;
  ulong local_60;
  undefined8 uStack_58;
  undefined *local_50;
  undefined *puStack_48;
  undefined *local_40;
  long local_38;
  
  local_38 = *(long *)PTR___stack_chk_guard_005ffe88;
  global_error = (char *)0x0;
  local_40 = (undefined *)0x0;
  DAT_006008a8 = 0;
  uStack_68 = 0;
  local_70 = (char *)0x0;
  uStack_58 = 0;
  local_60 = 0;
  puStack_48 = (undefined *)0x0;
  local_50 = (undefined *)0x0;
  if (param_1 == (char *)0x0 || param_2 == 0) {
    if (param_1 == (char *)0x0) {
      puVar3 = (undefined8 *)0x0;
      goto LAB_001f3994;
    }
  }
  else {
    local_50 = global_hooks;
    puStack_48 = PTR_free_006005a0;
    local_40 = PTR_realloc_006005a8;
    local_70 = param_1;
    uStack_68 = param_2;
    puVar3 = (undefined8 *)(*(code *)global_hooks)(0x40);
    if (puVar3 != (undefined8 *)0x0) {
      puVar3[1] = 0;
      *puVar3 = 0;
      puVar3[3] = 0;
      puVar3[2] = 0;
      puVar3[5] = 0;
      puVar3[4] = 0;
      puVar3[7] = 0;
      puVar3[6] = 0;
      ppcVar4 = (char **)(undefined1 *)0x0;
      if (local_70 != (char *)0x0) {
        if (local_60 == 0) {
          if (uStack_68 < 5) {
            ppcVar4 = &local_70;
            if (uStack_68 != 0) goto LAB_001f3970;
          }
          else {
            if (*local_70 != -0x11) goto LAB_001f3970;
            if (local_70[1] != -0x45) goto LAB_001f3970;
            if (local_70[2] != -0x41) goto LAB_001f3970;
            local_60 = 3;
            bVar1 = local_70[3];
            while (bVar1 < 0x21) {
              local_60 = local_60 + 1;
              if (local_60 == uStack_68) goto LAB_001f3a24;
LAB_001f3970:
              bVar1 = local_70[local_60];
            }
            ppcVar4 = &local_70;
            if (uStack_68 == local_60) {
LAB_001f3a24:
              local_60 = uStack_68 - 1;
              ppcVar4 = &local_70;
            }
          }
        }
        else {
          ppcVar4 = (char **)(undefined1 *)0x0;
        }
      }
      iVar2 = parse_value(puVar3,ppcVar4);
      if (iVar2 != 0) goto LAB_001f3994;
      cJSON_Delete(puVar3);
    }
  }
  if (local_60 < uStack_68) {
    DAT_006008a8 = local_60;
  }
  else {
    DAT_006008a8 = uStack_68 - 1;
    if (uStack_68 == 0) {
      DAT_006008a8 = 0;
    }
  }
  puVar3 = (undefined8 *)0x0;
  global_error = param_1;
LAB_001f3994:
  if (local_38 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_38 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return puVar3;
}

