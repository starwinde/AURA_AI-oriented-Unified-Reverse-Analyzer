
void elf_scalar_refs_format_text(long *param_1,long param_2)

{
  long lVar1;
  char *pcVar2;
  char *pcVar3;
  undefined8 uVar4;
  long lVar5;
  uint uVar6;
  
  if (param_1 == (long *)0x0 || param_2 == 0) {
    return;
  }
  __fprintf_chk(param_2,2,"ELF Scalar Operand References: %u entries\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar5 = 0;
    uVar6 = 0;
    do {
      while( true ) {
        lVar1 = *param_1 + lVar5;
        uVar4 = *(undefined8 *)(*param_1 + lVar5);
        pcVar2 = "section";
        if (*(int *)(lVar1 + 0x20) == 1) {
          pcVar2 = "reloc";
        }
        pcVar3 = "(null)";
        if (*(char **)(lVar1 + 0x10) != (char *)0x0) {
          pcVar3 = *(char **)(lVar1 + 0x10);
        }
        if (*(long *)(lVar1 + 0x18) != 0) break;
        __fprintf_chk(param_2,2,"  0x%lx: operand 0x%lx -> %s [%s] (%s)\n",uVar4,
                      *(undefined8 *)(lVar1 + 8),pcVar3,&DAT_001f8920,pcVar2);
        uVar6 = uVar6 + 1;
        lVar5 = lVar5 + 0x28;
        if (*(uint *)(param_1 + 1) <= uVar6) {
          return;
        }
      }
      __fprintf_chk(param_2,2,"  0x%lx: operand 0x%lx -> %s [%s] (%s)\n",uVar4,
                    *(undefined8 *)(lVar1 + 8),pcVar3,*(long *)(lVar1 + 0x18),pcVar2);
      uVar6 = uVar6 + 1;
      lVar5 = lVar5 + 0x28;
    } while (uVar6 < *(uint *)(param_1 + 1));
  }
  return;
}

