
void stack_frame_print(undefined8 *param_1,long param_2)

{
  long lVar1;
  undefined *puVar2;
  char *pcVar3;
  char *pcVar4;
  uint uVar5;
  undefined8 uVar6;
  char *pcVar7;
  long lVar8;
  char *pcVar9;
  uint uVar10;
  long lVar11;
  undefined1 auStack_88 [32];
  long local_68;
  
  local_68 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != (undefined8 *)0x0) {
    if (param_2 == 0) {
      param_2 = *(long *)PTR_stdout_005fff40;
    }
    __fprintf_chk(param_2,2,"=== Stack Frame: 0x%016lx ===\n",*param_1);
    __fprintf_chk(param_2,2,"  Frame size:   %ld bytes\n",param_1[1]);
    puVar2 = &DAT_001fae78;
    if (*(int *)(param_1 + 2) != 0) {
      puVar2 = &DAT_001fae70;
    }
    __fprintf_chk(param_2,2,"  Frame pointer: %s\n",puVar2);
    uVar6 = cc_name(*(undefined4 *)((long)param_1 + 0x14));
    __fprintf_chk(param_2,2,"  Convention:   %s\n",uVar6);
    __fprintf_chk(param_2,2,"  Variables:    %u\n\n",*(undefined4 *)(param_1 + 4));
    __fprintf_chk(param_2,2,"  %-14s %-6s %-20s %-14s %-10s %s\n","Offset",&DAT_001faec0,
                  &DAT_001faed8,&DAT_001faed0,&DAT_001fccb8,"Source");
    __fprintf_chk(param_2,2,"  %-14s %-6s %-20s %-14s %-10s %s\n",&DAT_001fcd00,&DAT_001fccf0,
                  &DAT_001fccf0,&DAT_001fccf0,&DAT_001fccf0,&DAT_001fcd00);
    if (*(int *)(param_1 + 4) != 0) {
      lVar11 = 0;
      uVar10 = 0;
      do {
        lVar1 = param_1[3] + lVar11;
        lVar8 = *(long *)(param_1[3] + lVar11);
        if (lVar8 < 0) {
          __snprintf_chk(auStack_88,0x20,2,0x20,"fp-0x%x",-(int)lVar8);
        }
        else {
          __snprintf_chk(auStack_88,0x20,2,0x20,"fp+0x%x");
        }
        uVar5 = *(uint *)(lVar1 + 0x20);
        pcVar3 = "(unnamed)";
        if (*(char **)(lVar1 + 0x10) != (char *)0x0) {
          pcVar3 = *(char **)(lVar1 + 0x10);
        }
        pcVar4 = "unknown";
        if (*(char **)(lVar1 + 0x18) != (char *)0x0) {
          pcVar4 = *(char **)(lVar1 + 0x18);
        }
        if (uVar5 == 2) {
          pcVar9 = "arg";
LAB_00179208:
          if (*(int *)(lVar1 + 0x24) == 1) goto LAB_001792c4;
LAB_00179214:
          pcVar7 = "heuristic";
        }
        else {
          if (uVar5 < 3) {
            pcVar9 = "local";
            if (uVar5 != 0) {
              pcVar9 = "saved_reg";
            }
            goto LAB_00179208;
          }
          if (uVar5 == 3) {
            pcVar9 = "retaddr";
            goto LAB_00179208;
          }
          pcVar9 = "padding";
          if (uVar5 != 4) {
            pcVar9 = "unknown";
          }
          if (*(int *)(lVar1 + 0x24) != 1) goto LAB_00179214;
LAB_001792c4:
          pcVar7 = "DWARF";
        }
        __fprintf_chk(param_2,2,"  %-14s %-6u %-20s %-14s %-10s %s\n",auStack_88,
                      *(undefined4 *)(lVar1 + 8),pcVar3,pcVar4,pcVar9,pcVar7);
        uVar10 = uVar10 + 1;
        lVar11 = lVar11 + 0x30;
      } while (uVar10 < *(uint *)(param_1 + 4));
    }
  }
  if (local_68 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_68 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

