
void printf64mem(long param_1,undefined4 param_2,undefined8 param_3)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 6) == '\x10') &&
     ((iVar1 = MCInst_getOpcode(), iVar1 == 0x2c9 || (iVar1 == 0x68b)))) {
    SStream_concat0(param_3,"xmmword ptr ");
    *(undefined1 *)(param_1 + 0x328) = 0x10;
    printMemReference(param_1,param_2,param_3);
    return;
  }
  SStream_concat0(param_3,"qword ptr ");
  *(undefined1 *)(param_1 + 0x328) = 8;
  printMemReference(param_1,param_2,param_3);
  return;
}

