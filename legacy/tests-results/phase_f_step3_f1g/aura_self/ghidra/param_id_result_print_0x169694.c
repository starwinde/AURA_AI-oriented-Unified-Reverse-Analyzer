
void param_id_result_print(long *param_1,long param_2)

{
  undefined4 *puVar1;
  undefined *puVar2;
  long *plVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  long lVar8;
  undefined8 local_88;
  undefined8 uStack_80;
  undefined8 local_78;
  undefined8 uStack_70;
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (long *)0x0) {
    if (param_2 == 0) {
      param_2 = *(long *)PTR_stdout_005fff40;
    }
    puVar2 = &DAT_001f98f8;
    if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
      puVar2 = &DAT_001f98f0;
    }
    plVar3 = (long *)&DAT_001f8878;
    if ((char)param_1[2] != '\0') {
      plVar3 = param_1 + 2;
    }
    __fprintf_chk(param_2,2,"Parameter ID: %u params, returns %s (%s)\n",(int)param_1[1],puVar2,
                  plVar3);
    __fprintf_chk(param_2,2,"  %-6s %-16s %-20s %-10s %-6s %s\n","Index",&DAT_001f9958,&DAT_001f9950
                  ,"Source",&DAT_001f9940,"StkOff");
    __fprintf_chk(param_2,2,"  %-6s %-16s %-20s %-10s %-6s %s\n","-----",&DAT_001f9998,&DAT_001f9998
                  ,"------",&DAT_001f9998,"------");
    if ((int)param_1[1] != 0) {
      lVar8 = 0;
      uVar7 = 0;
      do {
        while( true ) {
          puVar1 = (undefined4 *)(*param_1 + lVar8);
          uVar5 = puVar1[0x31];
          if (uVar5 < 5) {
            local_88 = 0x2d;
            uStack_80 = 0;
            local_78 = 0;
            uStack_70 = 0;
            if (uVar5 == 2) {
              __snprintf_chk(&local_88,0x20,2,0x20,"0x%lx",*(undefined8 *)(puVar1 + 0x32));
              pcVar6 = "stack";
            }
            else {
              pcVar6 = *(char **)(src_names_0 + (long)(int)uVar5 * 8);
            }
          }
          else {
            pcVar6 = "unknown";
            local_88 = 0x2d;
            uStack_80 = 0;
            local_78 = 0;
            uStack_70 = 0;
          }
          pcVar4 = "(anon)";
          if (*(char *)(puVar1 + 0x21) != '\0') {
            pcVar4 = (char *)(puVar1 + 0x21);
          }
          if (*(char *)(puVar1 + 1) == '\0') break;
          __fprintf_chk(param_2,2,"  %-6u %-16s %-20s %-10s %-6u %s\n",*puVar1,pcVar4,puVar1 + 1,
                        pcVar6,puVar1[0x34],&local_88);
          uVar7 = uVar7 + 1;
          lVar8 = lVar8 + 0xd8;
          if (*(uint *)(param_1 + 1) <= uVar7) goto LAB_001698c4;
        }
        __fprintf_chk(param_2,2,"  %-6u %-16s %-20s %-10s %-6u %s\n",*puVar1,pcVar4,"int",pcVar6,
                      puVar1[0x34],&local_88);
        uVar7 = uVar7 + 1;
        lVar8 = lVar8 + 0xd8;
      } while (uVar7 < *(uint *)(param_1 + 1));
    }
  }
LAB_001698c4:
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

