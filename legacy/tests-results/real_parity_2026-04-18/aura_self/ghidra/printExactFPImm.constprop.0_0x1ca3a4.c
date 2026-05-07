
void printExactFPImm_constprop_0
               (undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = lookupExactFPImmByEnum(param_3);
  lVar3 = lookupExactFPImmByEnum(param_4);
  MCInst_getOperand(param_1,3);
  iVar1 = MCOperand_getImm();
  if (iVar1 != 0) {
    SStream_concat0(param_2,*(undefined8 *)(lVar3 + 0x10));
    return;
  }
  SStream_concat0(param_2,*(undefined8 *)(lVar2 + 0x10));
  return;
}

