
undefined4 aura_xref_file(long param_1,undefined8 param_2)

{
  undefined *puVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  void *__ptr;
  undefined8 *puVar5;
  undefined4 uVar6;
  undefined8 *puVar7;
  long lVar8;
  long local_60;
  long local_58;
  
  local_58 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar6 = 0xfffffffc;
  }
  else {
    lVar3 = load_any_format(param_1,0);
    if (lVar3 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
LAB_001445e0:
      uVar6 = 0xfffffff9;
    }
    else {
      puVar5 = *(undefined8 **)(lVar3 + 0x18);
      if (*(uint *)(lVar3 + 0x20) != 0) {
        puVar7 = puVar5 + (ulong)*(uint *)(lVar3 + 0x20) * 7;
        do {
          if (((char *)*puVar5 != (char *)0x0) &&
             (iVar2 = strcmp((char *)*puVar5,".text"), iVar2 == 0)) {
            lVar8 = puVar5[5];
            if (lVar8 == 0) {
              __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                            "aura: cannot map .text data from \'%s\'\n",param_1);
              file_info_destroy(lVar3);
              goto LAB_001445e0;
            }
            lVar4 = disasm_init(*(undefined4 *)(lVar3 + 0xc));
            if (lVar4 == 0) {
              fwrite("aura: disassembler init failed\n",1,0x1f,*(FILE **)PTR_stderr_005fffd8);
              file_info_destroy(lVar3);
LAB_00144574:
              uVar6 = 0xfffffff8;
            }
            else {
              __ptr = malloc(0x3800000);
              if (__ptr == (void *)0x0) {
                disasm_destroy(lVar4);
                file_info_destroy(lVar3);
              }
              else {
                iVar2 = disasm_run(lVar4,lVar8,puVar5[3],puVar5[1],__ptr,0x40000);
                disasm_destroy(lVar4);
                file_info_destroy(lVar3);
                if (iVar2 < 1) {
                  __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                                "aura: disasm_run failed on .text of \'%s\'\n",param_1);
                  free(__ptr);
                  goto LAB_00144574;
                }
                lVar3 = xref_build(__ptr,(long)iVar2);
                local_60 = lVar3;
                free(__ptr);
                puVar1 = PTR_stdout_005fff40;
                if (lVar3 != 0) {
                  __printf_chk(2,"=== Cross-references for 0x%lx ===\n\n",param_2);
                  xref_print_to(local_60,param_2,*(undefined8 *)puVar1);
                  putchar(10);
                  xref_print_from(local_60,param_2,*(undefined8 *)puVar1);
                  __printf_chk(2,"\n--- Xref table summary: %u total entries ---\n",
                               *(undefined4 *)(local_60 + 8));
                  xref_table_destroy(&local_60);
                  uVar6 = 0;
                  goto LAB_00144420;
                }
                fwrite("aura: xref_build failed\n",1,0x18,*(FILE **)PTR_stderr_005fffd8);
              }
              uVar6 = 0xfffffffe;
            }
            goto LAB_00144420;
          }
          puVar5 = puVar5 + 7;
        } while (puVar5 != puVar7);
      }
      uVar6 = 0xfffffffa;
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: .text section not found in \'%s\'\n"
                    ,param_1);
      file_info_destroy(lVar3);
    }
  }
LAB_00144420:
  if (local_58 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                     local_58 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return uVar6;
}

