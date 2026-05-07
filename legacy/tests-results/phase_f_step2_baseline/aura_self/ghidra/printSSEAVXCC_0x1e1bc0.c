
void printSSEAVXCC(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  
  MCInst_getOperand();
  bVar1 = MCOperand_getImm();
  switch(bVar1 & 0x1f) {
  case 1:
    SStream_concat0(param_3,&DAT_001fbf68);
    op_addAvxCC(param_1,2);
    break;
  case 2:
    SStream_concat0(param_3,"le");
    op_addAvxCC(param_1,3);
    break;
  case 3:
    SStream_concat0(param_3,"unord");
    op_addAvxCC(param_1,4);
    break;
  case 4:
    SStream_concat0(param_3,&DAT_002018d8);
    op_addAvxCC(param_1,5);
    break;
  case 5:
    SStream_concat0(param_3,&DAT_002018e0);
    op_addAvxCC(param_1,6);
    break;
  case 6:
    SStream_concat0(param_3,&DAT_001f8258);
    op_addAvxCC(param_1,7);
    break;
  case 7:
    SStream_concat0(param_3,&DAT_002018e8);
    op_addAvxCC(param_1,8);
    break;
  case 8:
    SStream_concat0(param_3,"eq_uq");
    op_addAvxCC(param_1,9);
    break;
  case 9:
    SStream_concat0(param_3,&DAT_001f8250);
    op_addAvxCC(param_1,10);
    break;
  case 10:
    SStream_concat0(param_3,&DAT_002018f8);
    op_addAvxCC(param_1,0xb);
    break;
  case 0xb:
    SStream_concat0(param_3,"false");
    op_addAvxCC(param_1,0xc);
    break;
  case 0xc:
    SStream_concat0(param_3,"neq_oq");
    op_addAvxCC(param_1,0xd);
    break;
  case 0xd:
    SStream_concat0(param_3,"ge");
    op_addAvxCC(param_1,0xe);
    break;
  case 0xe:
    SStream_concat0(param_3,&DAT_001fbf70);
    op_addAvxCC(param_1,0xf);
    break;
  case 0xf:
    SStream_concat0(param_3,&DAT_00201910);
    op_addAvxCC(param_1,0x10);
    break;
  case 0x10:
    SStream_concat0(param_3,"eq_os");
    op_addAvxCC(param_1,0x11);
    break;
  case 0x11:
    SStream_concat0(param_3,"lt_oq");
    op_addAvxCC(param_1,0x12);
    break;
  case 0x12:
    SStream_concat0(param_3,"le_oq");
    op_addAvxCC(param_1,0x13);
    break;
  case 0x13:
    SStream_concat0(param_3,"unord_s");
    op_addAvxCC(param_1,0x14);
    break;
  case 0x14:
    SStream_concat0(param_3,"neq_us");
    op_addAvxCC(param_1,0x15);
    break;
  case 0x15:
    SStream_concat0(param_3,"nlt_uq");
    op_addAvxCC(param_1,0x16);
    break;
  case 0x16:
    SStream_concat0(param_3,"nle_uq");
    op_addAvxCC(param_1,0x17);
    break;
  case 0x17:
    SStream_concat0(param_3,"ord_s");
    op_addAvxCC(param_1,0x18);
    break;
  case 0x18:
    SStream_concat0(param_3,"eq_us");
    op_addAvxCC(param_1,0x19);
    break;
  case 0x19:
    SStream_concat0(param_3,"nge_uq");
    op_addAvxCC(param_1,0x1a);
    break;
  case 0x1a:
    SStream_concat0(param_3,"ngt_uq");
    op_addAvxCC(param_1,0x1b);
    break;
  case 0x1b:
    SStream_concat0(param_3,"false_os");
    op_addAvxCC(param_1,0x1c);
    break;
  case 0x1c:
    SStream_concat0(param_3,"neq_os");
    op_addAvxCC(param_1,0x1d);
    break;
  case 0x1d:
    SStream_concat0(param_3,"ge_oq");
    op_addAvxCC(param_1,0x1e);
    break;
  case 0x1e:
    SStream_concat0(param_3,"gt_oq");
    op_addAvxCC(param_1,0x1f);
    break;
  case 0x1f:
    SStream_concat0(param_3,"true_us");
    op_addAvxCC(param_1,0x20);
    break;
  default:
    SStream_concat0(param_3,&DAT_001fbf20);
    op_addAvxCC(param_1,1);
  }
  *(byte *)(param_1 + 0x367) = (bVar1 & 0x1f) + 1;
  return;
}

