
undefined4 aura_cfg_func(long param_1,ulong param_2,int param_3)

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
    lVar3 = load_any_format();
    if (lVar3 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_001419d8:
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
              file_info_destroy(lVar3);
              goto LAB_001419d8;
            }
            uVar8 = puVar6[1];
            if (param_2 < uVar8 || uVar8 + puVar6[3] <= param_2) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: func_addr 0x%016lx is outside .text [0x%lx..0x%lx]\n",param_2,
                            uVar8);
              file_info_destroy(lVar3);
              goto LAB_00141814;
            }
            lVar4 = disasm_init(*(undefined4 *)(lVar3 + 0xc));
            if (lVar4 == 0) {
              fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
              file_info_destroy(lVar3);
LAB_001419a4:
              uVar2 = 0xfffffff8;
              goto LAB_00141820;
            }
            lVar5 = puVar6[3];
            __ptr = malloc(0x1c000);
            if (__ptr == (void *)0x0) {
              disasm_destroy(lVar4);
              file_info_destroy(lVar3);
            }
            else {
              iVar1 = disasm_run(lVar4,lVar9 + (param_2 - uVar8),(uVar8 + lVar5) - param_2,param_2,
                                 __ptr,0x200);
              disasm_destroy(lVar4);
              file_info_destroy(lVar3);
              if (iVar1 < 1) {
                __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                              "aura: disasm_run failed at 0x%016lx\n",param_2);
                free(__ptr);
                goto LAB_001419a4;
              }
              lVar3 = cfg_build(__ptr,(long)iVar1,param_2);
              local_60 = lVar3;
              free(__ptr);
              if (lVar3 != 0) {
                if (param_3 == 0) {
                  uVar2 = cfg_print_text();
                }
                else {
                  uVar2 = cfg_print_dot(lVar3,*(undefined8 *)PTR_stdout_005fff40);
                }
                cfg_destroy(&local_60);
                goto LAB_00141820;
              }
              fwrite("aura: cfg_build failed\n",1,0x17,*(FILE **)PTR_stderr_005fffd8);
            }
            uVar2 = 0xfffffffe;
            goto LAB_00141820;
          }
          puVar6 = puVar6 + 7;
        } while (puVar7 != puVar6);
      }
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      file_info_destroy(lVar3);
LAB_00141814:
      uVar2 = 0xfffffffa;
    }
  }
LAB_00141820:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return uVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
}

