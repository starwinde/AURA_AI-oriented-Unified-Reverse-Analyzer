
void printGPR64as32(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  ulong uVar2;
  
  MCInst_getOperand();
  iVar1 = MCOperand_getReg();
  switch(iVar1) {
  case 2:
    uVar2 = 0xac1;
    break;
  case 3:
    uVar2 = 0xdf;
    break;
  default:
    uVar2 = (ulong)*(ushort *)(RegAsmOffsetNoRegAltName_12 + (ulong)(iVar1 - 1) * 2);
    break;
  case 5:
    uVar2 = 0xc76;
    break;
  case 9:
    uVar2 = 0xce4;
    break;
  case 0xda:
    uVar2 = 0x12a;
    break;
  case 0xdb:
    uVar2 = 0x2ab;
    break;
  case 0xdc:
    uVar2 = 0x38e;
    break;
  case 0xdd:
    uVar2 = 0x4c9;
    break;
  case 0xde:
    uVar2 = 0x5ac;
    break;
  case 0xdf:
    uVar2 = 0x6e9;
    break;
  case 0xe0:
    uVar2 = 0x7c8;
    break;
  case 0xe1:
    uVar2 = 0x915;
    break;
  case 0xe2:
    uVar2 = 0x9f4;
    break;
  case 0xe3:
    uVar2 = 0xb21;
    break;
  case 0xe4:
    uVar2 = 0x3f;
    break;
  case 0xe5:
    uVar2 = 0x197;
    break;
  case 0xe6:
    uVar2 = 0x2f9;
    break;
  case 0xe7:
    uVar2 = 0x403;
    break;
  case 0xe8:
    uVar2 = 0x51a;
    break;
  case 0xe9:
    uVar2 = 0x623;
    break;
  case 0xea:
    uVar2 = 0x736;
    break;
  case 0xeb:
    uVar2 = 0x83d;
    break;
  case 0xec:
    uVar2 = 0x962;
    break;
  case 0xed:
    uVar2 = 0xa69;
    break;
  case 0xee:
    uVar2 = 0x8f;
    break;
  case 0xef:
    uVar2 = 0x20f;
    break;
  case 0xf0:
    uVar2 = 0x349;
    break;
  case 0xf1:
    uVar2 = 0x47b;
    break;
  case 0xf2:
    uVar2 = 0x56a;
    break;
  case 0xf3:
    uVar2 = 0x69b;
    break;
  case 0xf4:
    uVar2 = 0x786;
    break;
  case 0xf5:
    uVar2 = 0x8b5;
    break;
  case 0xf6:
    uVar2 = 0x9b2;
  }
  SStream_concat0(param_3,&AsmStrsNoRegAltName_11 + uVar2);
  return;
}

