
void aura_strings_file(long param_1)

{
  int iVar1;
  long lVar2;
  long lVar3;
  undefined8 uVar4;
  long lVar5;
  void *__ptr;
  long lVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  long local_58;
  long local_50;
  long local_48;
  
  local_48 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 == 0) {
    uVar4 = 0xfffffffc;
  }
  else {
    lVar2 = load_any_format(param_1,PTR___stack_chk_guard_005ffe88,0);
    if (lVar2 == 0) {
      __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,"aura: failed to parse \'%s\'\n",param_1);
      uVar4 = 0xfffffff9;
    }
    else {
      lVar3 = strref_scan();
      local_58 = lVar3;
      if (lVar3 == 0) {
        fwrite("aura: string scan failed\n",1,0x19,*(FILE **)PTR_stderr_005fffd8);
        file_info_destroy(lVar2);
        uVar4 = 0xfffffffe;
      }
      else {
        local_50 = 0;
        puVar7 = *(undefined8 **)(lVar2 + 0x18);
        if (*(uint *)(lVar2 + 0x20) != 0) {
          puVar8 = puVar7 + (ulong)*(uint *)(lVar2 + 0x20) * 7;
          do {
            if (((char *)*puVar7 != (char *)0x0) &&
               (iVar1 = strcmp((char *)*puVar7,".text"), iVar1 == 0)) {
              lVar6 = 0;
              if ((puVar7[5] != 0) &&
                 (lVar5 = disasm_init(*(undefined4 *)(lVar2 + 0xc)), lVar6 = local_50,
                 lVar3 = local_58, lVar5 != 0)) {
                __ptr = malloc(0x3800000);
                if (__ptr != (void *)0x0) {
                  iVar1 = disasm_run(lVar5,puVar7[5],puVar7[3],puVar7[1],__ptr,0x40000);
                  if (0 < iVar1) {
                    local_50 = xref_build(__ptr,(long)iVar1);
                  }
                  free(__ptr);
                }
                disasm_destroy(lVar5);
                lVar6 = local_50;
                lVar3 = local_58;
              }
              goto LAB_00144274;
            }
            puVar7 = puVar7 + 7;
          } while (puVar7 != puVar8);
        }
        lVar6 = 0;
LAB_00144274:
        strref_print(lVar3,lVar6,*(undefined8 *)PTR_stdout_005fff40);
        if (local_50 != 0) {
          xref_table_destroy(&local_50);
        }
        strref_destroy(&local_58);
        file_info_destroy(lVar2);
        uVar4 = 0;
      }
    }
  }
  if (local_48 - *(long *)PTR___stack_chk_guard_005ffe88 != 0) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail(uVar4,PTR___stack_chk_guard_005ffe88,0,
                     local_48 - *(long *)PTR___stack_chk_guard_005ffe88);
  }
  return;
}

