
char * FUN_001449e0(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  if (-1 < param_1) {
    pcVar1 = (char *)FUN_0018c5d4();
    pcVar2 = "Unknown error";
    if (pcVar1 != (char *)0x0) {
      pcVar2 = pcVar1;
    }
    return pcVar2;
  }
  pcVar2 = (char *)FUN_00140720();
  return pcVar2;
}

