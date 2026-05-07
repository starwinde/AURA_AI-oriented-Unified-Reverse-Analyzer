
void thunk_FUN_0016a024(long *param_1,long param_2)

{
  undefined4 *puVar1;
  undefined *puVar2;
  long *plVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  long lVar8;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  long lStack_68;
  
  lStack_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (long *)0x0) {
    if (param_2 == 0) {
      param_2 = *(long *)PTR_stdout_005fff40;
    }
    puVar2 = &DAT_001fb4b8;
    if ((*(byte *)(param_1 + 0x12) & 1) != 0) {
      puVar2 = &DAT_001fb4b0;
    }
    plVar3 = (long *)&DAT_001fa448;
    if ((char)param_1[2] != '\0') {
      plVar3 = param_1 + 2;
    }
    __fprintf_chk(param_2,2,"Parameter ID: %u params, returns %s (%s)\n",(int)param_1[1],puVar2,
                  plVar3);
    __fprintf_chk(param_2,2,"  %-6s %-16s %-20s %-10s %-6s %s\n","Index",&DAT_001fb518,&DAT_001fb510
                  ,"Source",&DAT_001fb500,"StkOff");
    __fprintf_chk(param_2,2,"  %-6s %-16s %-20s %-10s %-6s %s\n","-----",&DAT_001fb558,&DAT_001fb558
                  ,"------",&DAT_001fb558,"------");
    if ((int)param_1[1] != 0) {
      lVar8 = 0;
      uVar7 = 0;
      do {
        while( true ) {
          puVar1 = (undefined4 *)(*param_1 + lVar8);
          uVar5 = puVar1[0x31];
          if (uVar5 < 5) {
            uStack_88 = 0x2d;
            uStack_80 = 0;
            uStack_78 = 0;
            uStack_70 = 0;
            if (uVar5 == 2) {
              __snprintf_chk(&uStack_88,0x20,2,0x20,"0x%lx",*(undefined8 *)(puVar1 + 0x32));
              pcVar6 = "stack";
            }
            else {
              pcVar6 = (&PTR_s_unknown_005dfe80)[(int)uVar5];
            }
          }
          else {
            pcVar6 = "unknown";
            uStack_88 = 0x2d;
            uStack_80 = 0;
            uStack_78 = 0;
            uStack_70 = 0;
          }
          pcVar4 = "(anon)";
          if (*(char *)(puVar1 + 0x21) != '\0') {
            pcVar4 = (char *)(puVar1 + 0x21);
          }
          if (*(char *)(puVar1 + 1) == '\0') break;
          __fprintf_chk(param_2,2,"  %-6u %-16s %-20s %-10s %-6u %s\n",*puVar1,pcVar4,puVar1 + 1,
                        pcVar6,puVar1[0x34],&uStack_88);
          uVar7 = uVar7 + 1;
          lVar8 = lVar8 + 0xd8;
          if (*(uint *)(param_1 + 1) <= uVar7) goto LAB_0016a254;
        }
        __fprintf_chk(param_2,2,"  %-6u %-16s %-20s %-10s %-6u %s\n",*puVar1,pcVar4,"int",pcVar6,
                      puVar1[0x34],&uStack_88);
        uVar7 = uVar7 + 1;
        lVar8 = lVar8 + 0xd8;
      } while (uVar7 < *(uint *)(param_1 + 1));
    }
  }
LAB_0016a254:
  if (lStack_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     lStack_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

