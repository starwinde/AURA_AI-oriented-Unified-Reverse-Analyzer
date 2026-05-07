
undefined8 * FUN_001f4da0(char *param_1,long *param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  undefined8 *puVar3;
  char **ppcVar4;
  char *local_80;
  ulong local_78;
  ulong local_70;
  undefined8 uStack_68;
  undefined *local_60;
  undefined *puStack_58;
  undefined *local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == (char *)0x0) {
    puVar3 = (undefined8 *)0x0;
    goto LAB_001f4edc;
  }
  sVar2 = strlen(param_1);
  local_78 = sVar2 + 1;
  local_70 = 0;
  uStack_68 = 0;
  local_60 = PTR_malloc_00600598;
  puStack_58 = PTR_free_006005a0;
  local_50 = PTR_realloc_006005a8;
  DAT_006008a0 = (char *)0x0;
  DAT_006008a8 = 0;
  local_80 = param_1;
  puVar3 = (undefined8 *)(*(code *)PTR_malloc_00600598)(0x40);
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
    if (local_80 != (char *)0x0) {
      if (local_70 == 0) {
        if (local_78 < 5) {
          ppcVar4 = &local_80;
          if (local_78 == 0) goto LAB_001f4eb0;
        }
        else if (((*local_80 == -0x11) && (local_80[1] == -0x45)) && (local_80[2] == -0x41)) {
          local_70 = 3;
        }
        do {
          if (0x20 < (byte)local_80[local_70]) {
            ppcVar4 = &local_80;
            if (local_70 != local_78) goto LAB_001f4eb0;
            break;
          }
          local_70 = local_70 + 1;
        } while (local_70 != local_78);
        local_70 = local_78 - 1;
        ppcVar4 = &local_80;
      }
      else {
        ppcVar4 = (char **)(undefined1 *)0x0;
      }
    }
LAB_001f4eb0:
    iVar1 = FUN_001f4480(puVar3,ppcVar4);
    if (iVar1 == 0) goto LAB_001f4f58;
    if (param_3 == 0) {
LAB_001f4ec0:
      if (param_2 != (long *)0x0) {
        *param_2 = (long)(local_80 + local_70);
      }
      goto LAB_001f4edc;
    }
    if (local_80 == (char *)0x0) {
LAB_001f4f48:
      if (local_70 < local_78) {
LAB_001f4f50:
        if (local_80[local_70] == '\0') goto LAB_001f4ec0;
      }
    }
    else if (local_70 < local_78) {
      do {
        if (0x20 < (byte)local_80[local_70]) {
          if (local_70 != local_78) goto LAB_001f4f48;
          break;
        }
        local_70 = local_70 + 1;
      } while (local_70 != local_78);
      local_70 = local_78 - 1;
      goto LAB_001f4f50;
    }
LAB_001f4f58:
    FUN_001f43e0(puVar3);
  }
  DAT_006008a8 = local_70;
  if ((local_78 <= local_70) && (DAT_006008a8 = local_78 - 1, local_78 == 0)) {
    DAT_006008a8 = 0;
  }
  if (param_2 != (long *)0x0) {
    *param_2 = (long)(param_1 + DAT_006008a8);
  }
  puVar3 = (undefined8 *)0x0;
  DAT_006008a0 = param_1;
LAB_001f4edc:
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return puVar3;
}

