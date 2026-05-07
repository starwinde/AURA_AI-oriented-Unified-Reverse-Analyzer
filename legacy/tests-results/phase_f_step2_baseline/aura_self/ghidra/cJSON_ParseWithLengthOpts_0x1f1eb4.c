
void cJSON_ParseWithLengthOpts(char *param_1,undefined8 *param_2,long *param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  undefined8 *puVar3;
  char **ppcVar4;
  undefined8 *extraout_x1;
  char *local_80;
  undefined8 *puStack_78;
  undefined8 *local_70;
  undefined8 uStack_68;
  undefined *local_60;
  undefined *puStack_58;
  undefined *local_50;
  undefined8 local_48;
  
  local_48 = *(undefined8 *)PTR___stack_chk_guard_005ffe88;
  global_error = (char *)0x0;
  DAT_006008a8 = (undefined8 *)0x0;
  local_50 = (undefined *)0x0;
  puStack_78 = (undefined8 *)0x0;
  local_80 = (char *)0x0;
  uStack_68 = 0;
  local_70 = (undefined8 *)0x0;
  puStack_58 = (undefined *)0x0;
  local_60 = (undefined *)0x0;
  if (param_1 == (char *)0x0 || param_2 == (undefined8 *)0x0) {
    if (param_1 == (char *)0x0) goto LAB_001f1ffc;
  }
  else {
    local_60 = global_hooks;
    puStack_58 = PTR_free_006005a0;
    local_50 = PTR_realloc_006005a8;
    local_80 = param_1;
    puStack_78 = param_2;
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
      if (local_80 != (char *)0x0) {
        if (local_70 == (undefined8 *)0x0) {
          if (puStack_78 < (undefined8 *)0x5) {
            ppcVar4 = &local_80;
            if (puStack_78 != (undefined8 *)0x0) goto LAB_001f1fc0;
          }
          else {
            if (*local_80 != -0x11) goto LAB_001f1fc0;
            if (local_80[1] != -0x45) goto LAB_001f1fc0;
            if (local_80[2] != -0x41) goto LAB_001f1fc0;
            local_70 = (undefined8 *)0x3;
            bVar1 = local_80[3];
            while (bVar1 < 0x21) {
              local_70 = (undefined8 *)((long)local_70 + 1);
              if (local_70 == puStack_78) goto LAB_001f20e0;
LAB_001f1fc0:
              bVar1 = local_80[(long)local_70];
            }
            ppcVar4 = &local_80;
            if (puStack_78 == local_70) {
LAB_001f20e0:
              local_70 = (undefined8 *)((long)puStack_78 + -1);
              ppcVar4 = &local_80;
            }
          }
        }
        else {
          ppcVar4 = (char **)(undefined1 *)0x0;
        }
      }
      iVar2 = parse_value(puVar3,ppcVar4);
      if (iVar2 == 0) goto LAB_001f2080;
      param_2 = extraout_x1;
      if (param_4 == 0) {
LAB_001f1fe8:
        if (param_3 != (long *)0x0) {
          *param_3 = (long)(local_80 + (long)local_70);
          param_2 = local_70;
        }
        goto LAB_001f1ffc;
      }
      if (local_80 == (char *)0x0) {
LAB_001f2070:
        if (local_70 < puStack_78) {
LAB_001f2078:
          param_2 = local_70;
          if (local_80[(long)local_70] == '\0') goto LAB_001f1fe8;
        }
      }
      else if (local_70 < puStack_78) {
        do {
          if (0x20 < (byte)local_80[(long)local_70]) {
            if (local_70 != puStack_78) goto LAB_001f2070;
            break;
          }
          local_70 = (undefined8 *)((long)local_70 + 1);
        } while (local_70 != puStack_78);
        local_70 = (undefined8 *)((long)puStack_78 + -1);
        goto LAB_001f2078;
      }
LAB_001f2080:
      cJSON_Delete(puVar3);
    }
  }
  DAT_006008a8 = local_70;
  if ((puStack_78 <= local_70) &&
     (DAT_006008a8 = (undefined8 *)((long)puStack_78 + -1), puStack_78 == (undefined8 *)0x0)) {
    DAT_006008a8 = (undefined8 *)0x0;
  }
  if (param_3 != (long *)0x0) {
    *param_3 = (long)(param_1 + (long)DAT_006008a8);
  }
  param_2 = &global_error;
  global_error = param_1;
LAB_001f1ffc:
  e843419_0077_00000398_20b8(PTR___stack_chk_guard_005ffe88,param_2,local_48);
  return;
}

