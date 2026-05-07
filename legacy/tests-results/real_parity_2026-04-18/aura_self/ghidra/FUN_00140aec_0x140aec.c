
undefined8 FUN_00140aec(undefined8 param_1)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  
  lVar2 = mapped_file_open();
  if (lVar2 != 0) {
    iVar1 = aura_detect_format(*(undefined8 *)(lVar2 + 8),*(undefined8 *)(lVar2 + 0x10));
    mapped_file_destroy(lVar2);
    if (iVar1 == 2) {
      uVar3 = pe_parser_load(param_1);
      return uVar3;
    }
    if (iVar1 == 3) {
      uVar3 = macho_parser_load(param_1);
      return uVar3;
    }
    if (iVar1 == 1) {
      uVar3 = elf_parser_load(param_1);
      return uVar3;
    }
    __fprintf_chk(*(undefined8 *)PTR_stderr_005fffd8,2,
                  "aura: unsupported or unknown file format: \'%s\'\n",param_1);
  }
  return 0;
}

