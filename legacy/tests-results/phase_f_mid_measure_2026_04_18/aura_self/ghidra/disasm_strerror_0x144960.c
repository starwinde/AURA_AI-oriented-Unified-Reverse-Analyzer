
char * disasm_strerror(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  if (-1 < param_1) {
    pcVar1 = (char *)cs_strerror();
    pcVar2 = "Unknown error";
    if (pcVar1 != (char *)0x0) {
      pcVar2 = pcVar1;
    }
    return pcVar2;
  }
  pcVar2 = (char *)aura_error_str();
  return pcVar2;
}

