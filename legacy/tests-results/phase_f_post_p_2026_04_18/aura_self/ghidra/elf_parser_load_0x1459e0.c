
long elf_parser_load(long param_1)

{
  int iVar1;
  long lVar2;
  long local_30;
  long local_28;
  
  local_28 = *(long *)PTR___stack_chk_guard_005ffe88;
  if (param_1 != 0) {
    local_30 = mapped_file_open(param_1,PTR___stack_chk_guard_005ffe88,0);
    if (local_30 != 0) {
      lVar2 = file_info_create(&local_30);
      if (lVar2 == 0) {
        lVar2 = 0;
        mapped_file_destroy(local_30);
        goto LAB_00145a2c;
      }
      iVar1 = elf_parse();
      if (iVar1 == 0) goto LAB_00145a2c;
      file_info_destroy(lVar2);
    }
  }
  lVar2 = 0;
LAB_00145a2c:
  if (local_28 - *(long *)PTR___stack_chk_guard_005ffe88 == 0) {
    return lVar2;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(PTR___stack_chk_guard_005ffe88,0,
                   local_28 - *(long *)PTR___stack_chk_guard_005ffe88);
}

