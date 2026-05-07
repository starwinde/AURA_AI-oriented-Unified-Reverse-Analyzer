
void disasm_arch_from_string(char *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (char *)0x0) {
    iVar2 = 1;
    iVar1 = strcmp(param_1,"x86");
    if ((iVar1 != 0) && (iVar1 = strcmp(param_1,"i386"), iVar1 != 0)) {
      iVar2 = 2;
      iVar1 = strcmp(param_1,"x86_64");
      if ((iVar1 != 0) &&
         ((iVar1 = strcmp(param_1,"amd64"), iVar1 != 0 &&
          (iVar1 = strcmp(param_1,"x86-64"), iVar1 != 0)))) {
        iVar2 = 3;
        iVar1 = strcmp(param_1,"arm");
        if ((iVar1 != 0) && (iVar1 = strcmp(param_1,"a32"), iVar1 != 0)) {
          iVar2 = 4;
          iVar1 = strcmp(param_1,"aarch64");
          if (iVar1 != 0) {
            iVar2 = strcmp(param_1,"arm64");
            iVar2 = (uint)(iVar2 == 0) << 2;
          }
        }
      }
    }
    disasm_init(iVar2);
    return;
  }
  return;
}

