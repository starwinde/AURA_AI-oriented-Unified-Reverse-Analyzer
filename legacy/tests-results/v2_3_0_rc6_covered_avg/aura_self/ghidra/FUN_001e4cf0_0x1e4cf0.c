
void FUN_001e4cf0(long param_1,undefined8 param_2,undefined8 param_3)

{
  byte bVar1;
  
  FUN_0018ffd0();
  bVar1 = FUN_001900a0();
  switch(bVar1 & 0x1f) {
  case 1:
    FUN_00190370(param_3,&DAT_001fe188);
    FUN_001e6810(param_1,2);
    break;
  case 2:
    FUN_00190370(param_3,"le");
    FUN_001e6810(param_1,3);
    break;
  case 3:
    FUN_00190370(param_3,"unord");
    FUN_001e6810(param_1,4);
    break;
  case 4:
    FUN_00190370(param_3,&DAT_00203a58);
    FUN_001e6810(param_1,5);
    break;
  case 5:
    FUN_00190370(param_3,&DAT_00203a60);
    FUN_001e6810(param_1,6);
    break;
  case 6:
    FUN_00190370(param_3,&DAT_001fa3e8);
    FUN_001e6810(param_1,7);
    break;
  case 7:
    FUN_00190370(param_3,&DAT_00203a68);
    FUN_001e6810(param_1,8);
    break;
  case 8:
    FUN_00190370(param_3,"eq_uq");
    FUN_001e6810(param_1,9);
    break;
  case 9:
    FUN_00190370(param_3,&DAT_001fa3e0);
    FUN_001e6810(param_1,10);
    break;
  case 10:
    FUN_00190370(param_3,&DAT_00203a78);
    FUN_001e6810(param_1,0xb);
    break;
  case 0xb:
    FUN_00190370(param_3,"false");
    FUN_001e6810(param_1,0xc);
    break;
  case 0xc:
    FUN_00190370(param_3,"neq_oq");
    FUN_001e6810(param_1,0xd);
    break;
  case 0xd:
    FUN_00190370(param_3,"ge");
    FUN_001e6810(param_1,0xe);
    break;
  case 0xe:
    FUN_00190370(param_3,&DAT_001fe190);
    FUN_001e6810(param_1,0xf);
    break;
  case 0xf:
    FUN_00190370(param_3,&DAT_00203a90);
    FUN_001e6810(param_1,0x10);
    break;
  case 0x10:
    FUN_00190370(param_3,"eq_os");
    FUN_001e6810(param_1,0x11);
    break;
  case 0x11:
    FUN_00190370(param_3,"lt_oq");
    FUN_001e6810(param_1,0x12);
    break;
  case 0x12:
    FUN_00190370(param_3,"le_oq");
    FUN_001e6810(param_1,0x13);
    break;
  case 0x13:
    FUN_00190370(param_3,"unord_s");
    FUN_001e6810(param_1,0x14);
    break;
  case 0x14:
    FUN_00190370(param_3,"neq_us");
    FUN_001e6810(param_1,0x15);
    break;
  case 0x15:
    FUN_00190370(param_3,"nlt_uq");
    FUN_001e6810(param_1,0x16);
    break;
  case 0x16:
    FUN_00190370(param_3,"nle_uq");
    FUN_001e6810(param_1,0x17);
    break;
  case 0x17:
    FUN_00190370(param_3,"ord_s");
    FUN_001e6810(param_1,0x18);
    break;
  case 0x18:
    FUN_00190370(param_3,"eq_us");
    FUN_001e6810(param_1,0x19);
    break;
  case 0x19:
    FUN_00190370(param_3,"nge_uq");
    FUN_001e6810(param_1,0x1a);
    break;
  case 0x1a:
    FUN_00190370(param_3,"ngt_uq");
    FUN_001e6810(param_1,0x1b);
    break;
  case 0x1b:
    FUN_00190370(param_3,"false_os");
    FUN_001e6810(param_1,0x1c);
    break;
  case 0x1c:
    FUN_00190370(param_3,"neq_os");
    FUN_001e6810(param_1,0x1d);
    break;
  case 0x1d:
    FUN_00190370(param_3,"ge_oq");
    FUN_001e6810(param_1,0x1e);
    break;
  case 0x1e:
    FUN_00190370(param_3,"gt_oq");
    FUN_001e6810(param_1,0x1f);
    break;
  case 0x1f:
    FUN_00190370(param_3,"true_us");
    FUN_001e6810(param_1,0x20);
    break;
  default:
    FUN_00190370(param_3,&DAT_001fe140);
    FUN_001e6810(param_1,1);
  }
  *(byte *)(param_1 + 0x367) = (bVar1 & 0x1f) + 1;
  return;
}

