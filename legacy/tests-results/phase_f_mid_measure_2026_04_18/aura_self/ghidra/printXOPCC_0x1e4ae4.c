
void printXOPCC(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  long lVar1;
  
  MCInst_getOperand();
  lVar1 = MCOperand_getImm();
  if (lVar1 == 4) {
    SStream_concat0(param_3,&DAT_001fdb00);
    op_addXopCC(param_1,5);
    return;
  }
  if (lVar1 < 5) {
    if (lVar1 == 2) {
      SStream_concat0(param_3,&DAT_001fdb50);
      op_addXopCC(param_1,3);
      return;
    }
    if (lVar1 == 3) {
      SStream_concat0(param_3,"ge");
      op_addXopCC(param_1,4);
      return;
    }
    if (lVar1 == 1) {
      SStream_concat0(param_3,"le");
      op_addXopCC(param_1,2);
      return;
    }
  }
  else {
    if (lVar1 == 6) {
      SStream_concat0(param_3,"false");
      op_addXopCC(param_1,7);
      return;
    }
    if (lVar1 == 7) {
      SStream_concat0(param_3,&DAT_00203450);
      op_addXopCC(param_1,8);
      return;
    }
    if (lVar1 == 5) {
      SStream_concat0(param_3,&DAT_00203418);
      op_addXopCC(param_1,6);
      return;
    }
  }
  SStream_concat0(param_3,&DAT_001fdb48);
  op_addXopCC(param_1,1);
  return;
}

