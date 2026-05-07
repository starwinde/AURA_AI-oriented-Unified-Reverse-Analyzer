
void FUN_001e3cdc(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong uVar1;
  
  MCInst_getOperand();
  uVar1 = MCOperand_getImm();
  uVar1 = uVar1 & 3;
  if (uVar1 == 2) {
    SStream_concat0(param_3,"{ru-sae}");
    op_addAvxSae(param_1);
    op_addAvxRoundingMode(param_1,3);
    return;
  }
  if (uVar1 != 3) {
    if (uVar1 != 1) {
      SStream_concat0(param_3,"{rn-sae}");
      op_addAvxSae(param_1);
      op_addAvxRoundingMode(param_1,1);
      return;
    }
    SStream_concat0(param_3,"{rd-sae}");
    op_addAvxSae(param_1);
    op_addAvxRoundingMode(param_1,2);
    return;
  }
  SStream_concat0(param_3,"{rz-sae}");
  op_addAvxSae(param_1);
  op_addAvxRoundingMode(param_1,4);
  return;
}

