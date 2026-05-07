
char * FUN_001830f0(long param_1)

{
  long *plVar1;
  long lVar2;
  char *pcVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  long *plVar7;
  
  if (DAT_00600888 != 0) {
    if (*(uint *)(DAT_00600888 + 0x20) != 0) {
      plVar5 = *(long **)(DAT_00600888 + 0x18);
      plVar7 = plVar5 + (ulong)*(uint *)(DAT_00600888 + 0x20) * 6;
      if (*(long *)(DAT_00600888 + 8) < 1) {
        do {
          lVar6 = *plVar5;
          plVar1 = plVar5 + 6;
          lVar2 = -lVar6;
          if (-1 < lVar6) {
            lVar2 = lVar6;
          }
          if (param_1 == lVar2) {
LAB_00183150:
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
          if ((param_1 == lVar2) || (param_1 == *(long *)(DAT_00600888 + 8) - lVar2))
          goto LAB_00183150;
          plVar5 = plVar1;
        } while (plVar1 != plVar7);
      }
    }
  }
  return "var_";
}

