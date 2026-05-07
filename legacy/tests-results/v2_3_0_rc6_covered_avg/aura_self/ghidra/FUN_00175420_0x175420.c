
void FUN_00175420(long *param_1,FILE *param_2)

{
  long lVar1;
  char *pcVar2;
  char *pcVar3;
  long lVar4;
  
  if (param_1 == (long *)0x0) {
    return;
  }
  if (param_2 == (FILE *)0x0) {
    param_2 = *(FILE **)PTR_stdout_005fff40;
  }
  __fprintf_chk(param_2,2,"=== Relocation Table (%u entries) ===\n",(int)param_1[1]);
  if ((int)param_1[1] != 0) {
    lVar4 = 0;
    do {
      lVar1 = *param_1 + lVar4 * 0x20;
      switch(*(undefined4 *)(lVar1 + 0x18)) {
      case 1:
        pcVar3 = "ABS64";
        break;
      case 2:
        pcVar3 = "ABS32";
        break;
      case 3:
        pcVar3 = "GLOB_DAT";
        break;
      case 4:
        pcVar3 = "JUMP_SLOT";
        break;
      case 5:
        pcVar3 = "RELATIVE";
        break;
      case 6:
        pcVar3 = "PC32";
        break;
      case 7:
        pcVar3 = "PLT32";
        break;
      case 8:
        pcVar3 = "COPY";
        break;
      case 9:
        pcVar3 = "TPOFF";
        break;
      case 10:
        pcVar3 = "IRELATIVE";
        break;
      case 0xb:
        pcVar3 = "PE_HIGH";
        break;
      case 0xc:
        pcVar3 = "PE_LOW";
        break;
      default:
        pcVar3 = "UNKNOWN";
      }
      pcVar2 = "(none)";
      if (*(char **)(lVar1 + 8) != (char *)0x0) {
        pcVar2 = *(char **)(lVar1 + 8);
      }
      __fprintf_chk(param_2,2,"  0x%016lx  %-16s  %s",*(undefined8 *)(*param_1 + lVar4 * 0x20),
                    pcVar3,pcVar2);
      if (*(long *)(lVar1 + 0x10) != 0) {
        __fprintf_chk(param_2,2," + 0x%lx");
      }
      fputc(10,param_2);
      lVar4 = lVar4 + 1;
    } while ((uint)lVar4 < *(uint *)(param_1 + 1));
  }
  return;
}

