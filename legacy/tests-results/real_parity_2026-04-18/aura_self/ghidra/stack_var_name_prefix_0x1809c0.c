
char * stack_var_name_prefix(long param_1)

{
  long *plVar1;
  long lVar2;
  char *pcVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  
  if (s_emit_stack_frame != 0) {
    if (*(uint *)(s_emit_stack_frame + 0x20) != 0) {
      plVar5 = *(long **)(s_emit_stack_frame + 0x18);
      plVar7 = plVar5 + (ulong)*(uint *)(s_emit_stack_frame + 0x20) * 6;
      if (*(long *)(s_emit_stack_frame + 8) < 1) {
        do {
          lVar6 = *plVar5;
          plVar1 = plVar5 + 6;
          lVar2 = -lVar6;
          if (-1 < lVar6) {
            lVar2 = lVar6;
          }
          if (param_1 == lVar2) {
LAB_00180a20:
            uVar4 = *(uint *)(plVar5 + 4);
            if (uVar4 == 2) {
              return "arg_stack_";
            }
            if (2 < uVar4) {
              pcVar3 = "var_";
              if (uVar4 == 3) {
                pcVar3 = "retaddr_";
              }
              return pcVar3;
            }
            pcVar3 = "local_";
            if (uVar4 != 0) {
              pcVar3 = "saved_";
            }
            return pcVar3;
          }
          plVar5 = plVar1;
        } while (plVar1 != plVar7);
      }
      else {
        do {
          lVar6 = *plVar5;
          plVar1 = plVar5 + 6;
          lVar2 = -lVar6;
          if (-1 < lVar6) {
            lVar2 = lVar6;
          }
          if ((param_1 == lVar2) || (param_1 == *(long *)(s_emit_stack_frame + 8) - lVar2))
          goto LAB_00180a20;
          plVar5 = plVar1;
        } while (plVar1 != plVar7);
      }
    }
  }
  return "var_";
}

