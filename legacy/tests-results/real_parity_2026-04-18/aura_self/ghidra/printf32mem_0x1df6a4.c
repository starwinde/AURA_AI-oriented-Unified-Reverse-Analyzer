
void printf32mem(long param_1,undefined4 param_2,undefined8 param_3)

{
  int iVar1;
  
  iVar1 = MCInst_getOpcode();
  if ((iVar1 != 0x39b) && (iVar1 != 0x3b2)) {
    SStream_concat0(param_3,"dword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 4;
    printMemReference(param_1,param_2,param_3);
    return;
  }
  iVar1 = *(int *)(*(long *)(param_1 + 800) + 4);
  if ((iVar1 - 4U & 0xfffffffb) == 0) {
    *(undefined1 *)(param_1 + 0x328) = 0x1c;
    printMemReference(param_1,param_2,param_3);
    return;
  }
  if (iVar1 != 2) {
    printMemReference(param_1,param_2,param_3);
    return;
  }
  *(undefined1 *)(param_1 + 0x328) = 0xe;
  printMemReference(param_1,param_2,param_3);
  return;
}

