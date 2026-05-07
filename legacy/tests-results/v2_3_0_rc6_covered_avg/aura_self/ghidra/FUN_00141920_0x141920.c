
undefined4 FUN_00141920(long param_1,ulong param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  long lVar4;
  void *__ptr;
  long lVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  ulong uVar8;
  long lVar9;
  long local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar2 = 0xfffffffc;
  }
  else {
    lVar3 = FUN_00140cb0();
    if (lVar3 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_00141b98:
      uVar2 = 0xfffffff9;
    }
    else {
      puVar6 = *(undefined8 **)(lVar3 + 0x18);
      if (*(uint *)(lVar3 + 0x20) != 0) {
        puVar7 = puVar6 + (ulong)*(uint *)(lVar3 + 0x20) * 7;
        do {
          if (((char *)*puVar6 != (char *)0x0) &&
             (iVar1 = strcmp((char *)*puVar6,".text"), iVar1 == 0)) {
            lVar9 = puVar6[5];
            if (lVar9 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              FUN_00144de4(lVar3);
              goto LAB_00141b98;
            }
            uVar8 = puVar6[1];
            if (param_2 < uVar8 || uVar8 + puVar6[3] <= param_2) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: func_addr 0x%016lx is outside .text [0x%lx..0x%lx]\n",param_2,
                            uVar8);
              FUN_00144de4(lVar3);
              goto LAB_001419d4;
            }
            lVar4 = FUN_001446e0(*(undefined4 *)(lVar3 + 0xc));
            if (lVar4 == 0) {
              fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
              FUN_00144de4(lVar3);
LAB_00141b64:
              uVar2 = 0xfffffff8;
              goto LAB_001419e0;
            }
            lVar5 = puVar6[3];
            __ptr = malloc(0x1c000);
            if (__ptr == (void *)0x0) {
              FUN_001447a4(lVar4);
              FUN_00144de4(lVar3);
            }
            else {
              iVar1 = FUN_001447f0(lVar4,lVar9 + (param_2 - uVar8),(uVar8 + lVar5) - param_2,param_2
                                   ,__ptr,0x200);
              FUN_001447a4(lVar4);
              FUN_00144de4(lVar3);
              if (iVar1 < 1) {
                __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                              "aura: disasm_run failed at 0x%016lx\n",param_2);
                free(__ptr);
                goto LAB_00141b64;
              }
              lVar3 = FUN_00147b50(__ptr,(long)iVar1,param_2);
              local_60 = lVar3;
              free(__ptr);
              if (lVar3 != 0) {
                if (param_3 == 0) {
                  uVar2 = FUN_00148694();
                }
                else {
                  uVar2 = FUN_001489e0(lVar3,*(undefined8 *)PTR_stdout_005fff40);
                }
                FUN_00148610(&local_60);
                goto LAB_001419e0;
              }
              fwrite("aura: cfg_build failed\n",1,0x17,*(FILE **)PTR_stderr_005fffd8);
            }
            uVar2 = 0xfffffffe;
            goto LAB_001419e0;
          }
          puVar6 = puVar6 + 7;
        } while (puVar7 != puVar6);
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      FUN_00144de4(lVar3);
LAB_001419d4:
      uVar2 = 0xfffffffa;
    }
  }
LAB_001419e0:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

