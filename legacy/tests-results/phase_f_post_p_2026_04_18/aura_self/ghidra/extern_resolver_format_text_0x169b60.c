
void extern_resolver_format_text(long *param_1,FILE *param_2)

{
  long lVar1;
  char *pcVar2;
  ulong uVar3;
  char *pcVar4;
  long lVar5;
  ulong uVar6;
  
  if (param_1 == (long *)0x0 || param_2 == (FILE *)0x0) {
    return;
  }
  __fprintf_chk(param_2,2,"External Symbol Resolver: %u imports, %u libraries\n",(int)param_1[1],
                (int)param_1[3]);
  if (((int)param_1[3] != 0) &&
     (fwrite("  DT_NEEDED libraries:\n",1,0x17,param_2), (int)param_1[3] != 0)) {
    uVar6 = 0;
    do {
      uVar3 = uVar6 & 0xffffffff;
      lVar5 = uVar6 * 8;
      uVar6 = uVar6 + 1;
      __fprintf_chk(param_2,2,"    [%u] %s\n",uVar3,*(undefined8 *)(param_1[2] + lVar5));
    } while ((uint)uVar6 < *(uint *)(param_1 + 3));
  }
  fwrite("  Imported symbols (JUMP_SLOT):\n",1,0x20,param_2);
  if ((int)param_1[1] != 0) {
    lVar5 = 0;
    do {
      lVar1 = *param_1 + lVar5 * 0x20;
      pcVar4 = *(char **)(*param_1 + lVar5 * 0x20);
      pcVar2 = "(null)";
      if (pcVar4 != (char *)0x0) {
        pcVar2 = pcVar4;
      }
      __fprintf_chk(param_2,2,"    GOT 0x%lx  %s",*(undefined8 *)(lVar1 + 0x10),pcVar2);
      if (*(long *)(lVar1 + 0x18) != 0) {
        __fprintf_chk(param_2,2,"  [%s]");
      }
      fputc(10,param_2);
      lVar5 = lVar5 + 1;
    } while ((uint)lVar5 < *(uint *)(param_1 + 1));
  }
  return;
}

