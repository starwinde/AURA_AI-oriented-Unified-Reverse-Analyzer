
ulong AArch64_map_insn(char *param_1)

{
  int iVar1;
  ulong uVar2;
  
  uVar2 = 1;
  do {
    iVar1 = strcmp(param_1,*(char **)(insn_name_maps + uVar2 * 8));
    if (iVar1 == 0) {
      return uVar2 & 0xffffffff;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 != 0x50b);
  return 0;
}

